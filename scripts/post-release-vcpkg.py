#!/usr/bin/env python3
"""
Post-release helper: submit a TA-Lib update PR to microsoft/vcpkg.

What this script does
---------------------
1) Fetches the latest PUBLISHED TA-Lib release from GitHub (version + source tarball).
2) Computes the SHA512 of the tarball (required by vcpkg).
3) Prints the update plan.
4) With confirmation, updates a local microsoft/vcpkg checkout and opens a PR.

Usage
-----
  # Default: interactive full pipeline (clone vcpkg, update files, open PR)
  python post-release-vcpkg.py

  # Plan-only / non-interactive (used by CI, no side-effects)
  python post-release-vcpkg.py --plan

  # Use an existing local vcpkg checkout instead of auto-cloning
  python post-release-vcpkg.py --vcpkg-root /path/to/vcpkg

Safety guards (applied before performing any write operations)
-------------------------------------------------------------
- Must run from the original TA-Lib repository (not a fork).
- Must be on the 'main' branch.
- Checks for an existing open PR in microsoft/vcpkg to avoid duplicates.

Idempotency
-----------
Safe to run multiple times for the same release:
- If an open PR already exists for this version, the script exits cleanly.
- Updating the vcpkg port files is idempotent (re-sets the same version/SHA512).
- git checkout -B + "no changes to commit" guard prevents duplicate commits.

Version source
--------------
The authoritative version is the LATEST PUBLISHED RELEASE from the GitHub API.
The local VERSION file is used as a cross-check; a mismatch produces a warning
(not an error), since 'main' is often bumped ahead of the most recent release.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import shutil
import subprocess
import sys
from pathlib import Path
from urllib.parse import urlencode
from urllib.request import Request, urlopen

from utilities.common import run_command, verify_git_repo_original
from utilities.files import path_join
from utilities.versions import get_version_string

API_RELEASE_LATEST = "https://api.github.com/repos/TA-Lib/ta-lib/releases/latest"
ASSET_PATTERN = re.compile(r"ta-lib-(\d+\.\d+\.\d+)-src\.tar\.gz$")
VCPKG_PORT_NAME = "talib"


def sha512_file(path: Path) -> str:
    h = hashlib.sha512()
    with path.open("rb") as f:
        for chunk in iter(lambda: f.read(1024 * 1024), b""):
            h.update(chunk)
    return h.hexdigest()


def download(url: str, out: Path) -> None:
    out.parent.mkdir(parents=True, exist_ok=True)
    req = Request(url, headers={"User-Agent": "ta-lib-post-release-script"})
    with urlopen(req) as r, out.open("wb") as f:
        while True:
            chunk = r.read(1024 * 1024)
            if not chunk:
                break
            f.write(chunk)


def fetch_json(url: str) -> dict:
    req = Request(url, headers={"Accept": "application/vnd.github+json", "User-Agent": "ta-lib-post-release-script"})
    with urlopen(req) as r:
        return json.loads(r.read().decode("utf-8"))


def version_key(v: str) -> tuple[int, int, int]:
    m = re.fullmatch(r"(\d+)\.(\d+)\.(\d+)", v)
    if not m:
        raise ValueError(f"Invalid version: {v}")
    return int(m.group(1)), int(m.group(2)), int(m.group(3))


def read_latest_release_src_tarball() -> tuple[str, str, str]:
    """Return (version, tarball_name, download_url) for the latest published release."""
    data = fetch_json(API_RELEASE_LATEST)
    if data.get("draft"):
        raise RuntimeError("Latest GitHub release is still a draft (not yet published).")
    assets = data.get("assets", [])
    for a in assets:
        name = a.get("name", "")
        m = ASSET_PATTERN.search(name)
        if m:
            version = m.group(1)
            return version, name, a.get("browser_download_url", "")
    raise RuntimeError("Could not find ta-lib-<version>-src.tar.gz asset in latest release")


def read_cached_latest_release_src_tarball(out_dir: Path) -> tuple[str, str, Path]:
    candidates: list[tuple[tuple[int, int, int], str, Path]] = []
    for p in out_dir.glob("ta-lib-*-src.tar.gz"):
        m = ASSET_PATTERN.search(p.name)
        if not m:
            continue
        version = m.group(1)
        candidates.append((version_key(version), version, p))
    if not candidates:
        raise RuntimeError("No cached ta-lib-<version>-src.tar.gz found")
    _, version, path = sorted(candidates)[-1]
    return version, path.name, path


def read_local_version() -> str:
    root_dir = Path(path_join(Path(__file__).resolve().parent, "..")).resolve()
    return get_version_string(str(root_dir))


def _current_branch() -> str:
    """Return the current git branch name, or '(unknown)' on failure."""
    result = subprocess.run(
        ["git", "rev-parse", "--abbrev-ref", "HEAD"],
        capture_output=True,
        text=True,
    )
    if result.returncode != 0:
        return "(unknown)"
    return result.stdout.strip()


def _check_no_existing_vcpkg_pr(version: str) -> None:
    """
    Raise RuntimeError if an open PR for this version already exists in
    microsoft/vcpkg.  Uses the public GitHub search API (no auth required).
    Prints a warning and continues if the API call fails.
    """
    query = "repo:microsoft/vcpkg is:pr is:open [ta-lib] in:title"
    url = "https://api.github.com/search/issues?" + urlencode({"q": query, "per_page": "10"})
    # Match the version as a whole token to avoid e.g. 0.6.1 matching 0.6.10.
    version_re = re.compile(r"(?<![.\d])" + re.escape(version) + r"(?![.\d])")
    try:
        data = fetch_json(url)
        for item in data.get("items", []):
            title = item.get("title", "")
            if version_re.search(title):
                pr_url = item.get("html_url", "")
                raise RuntimeError(
                    f"An open PR for ta-lib {version} already exists in microsoft/vcpkg:\n"
                    f"  {pr_url}\n"
                    "No new PR is needed. Run with --plan to review the current state."
                )
    except RuntimeError:
        raise
    except Exception as e:
        print(f"[warn] Could not check for existing vcpkg PRs: {e}")
        print("[warn] Proceeding — verify manually that no duplicate PR exists.")


def update_vcpkg_files(vcpkg_root: Path, version: str, sha512: str) -> None:
    """
    Idempotent: updates the vcpkg port files for talib to the given version + sha512.
    If expected files are missing, print guidance and return.
    """
    portfile = vcpkg_root / "ports" / VCPKG_PORT_NAME / "portfile.cmake"
    vcpkg_json = vcpkg_root / "ports" / VCPKG_PORT_NAME / "vcpkg.json"

    if not portfile.exists() or not vcpkg_json.exists():
        print(f"[warn] Could not find ports/{VCPKG_PORT_NAME} files in provided vcpkg checkout.")
        print("       Please update the port manually in microsoft/vcpkg.")
        return

    # Update version in vcpkg.json while preserving the current versioning scheme.
    # vcpkg manifests must contain exactly one of:
    # version, version-date, version-semver, version-string.
    data = json.loads(vcpkg_json.read_text())
    version_keys = ["version", "version-date", "version-semver", "version-string"]
    if "version-semver" in data:
        target_version_key = "version-semver"
    elif "version-string" in data:
        target_version_key = "version-string"
    elif "version-date" in data:
        target_version_key = "version-date"
    elif "version" in data:
        target_version_key = "version"
    else:
        target_version_key = "version"

    for key in version_keys:
        data.pop(key, None)
    data[target_version_key] = version
    vcpkg_json.write_text(json.dumps(data, indent=2) + "\n")

    # Replace SHA512 in portfile.cmake (first SHA512 occurrence)
    text = portfile.read_text()
    text_new = re.sub(r"(SHA512\s+)[0-9a-fA-F]{64,128}", rf"\1{sha512}", text, count=1)
    if text_new == text:
        print("[warn] Could not auto-replace SHA512 in portfile.cmake. Update manually.")
    else:
        portfile.write_text(text_new)

    print(f"[ok] Updated local vcpkg {VCPKG_PORT_NAME} port files.")


def ensure_vcpkg_checkout(vcpkg_root: Path) -> Path:
    vcpkg_root = vcpkg_root.resolve()
    if (vcpkg_root / ".git").exists():
        print(f"[ok] Using existing vcpkg checkout: {vcpkg_root}")
        try:
            run_command(["git", "fetch", "--all", "--prune"], cwd=str(vcpkg_root))
        except Exception as e:
            print(f"[warn] Could not fetch vcpkg remote: {e}")
        return vcpkg_root

    # Recover from older path bug where clone target was created nested under out_dir.
    nested_candidates = [
        p for p in vcpkg_root.parent.rglob("vcpkg")
        if p != vcpkg_root and (p / ".git").exists()
    ]
    if nested_candidates:
        nested = sorted(nested_candidates, key=lambda p: len(str(p)))[0]
        print(f"[warn] Found nested vcpkg checkout at: {nested}")
        print("[warn] Reusing it for this run.")
        return nested

    vcpkg_root.parent.mkdir(parents=True, exist_ok=True)
    try:
        run_command(
            ["git", "clone", "https://github.com/microsoft/vcpkg.git", str(vcpkg_root)],
            cwd=str(vcpkg_root.parent),
        )
        print(f"[ok] Cloned vcpkg into: {vcpkg_root}")
        return vcpkg_root
    except Exception as e:
        raise RuntimeError(
            f"Could not clone microsoft/vcpkg into {vcpkg_root}: {e}. "
            "Pass --vcpkg-root to an existing local checkout."
        )


def run_x_add_version(vcpkg_root: Path) -> None:
    vcpkg_exe = vcpkg_root / "vcpkg"
    if not vcpkg_exe.exists():
        bootstrap = vcpkg_root / "bootstrap-vcpkg.sh"
        if bootstrap.exists():
            try:
                run_command([str(bootstrap)], cwd=str(vcpkg_root))
            except Exception as e:
                print(f"[warn] bootstrap-vcpkg.sh failed: {e}")
                print("[warn] Skipping x-add-version. Run it manually when network/toolchain is available.")
                return
        if not vcpkg_exe.exists():
            print(f"[warn] Could not find {vcpkg_exe}; skipping x-add-version")
            return
    manifest_path = vcpkg_root / "ports" / VCPKG_PORT_NAME / "vcpkg.json"
    if manifest_path.exists():
        try:
            run_command([str(vcpkg_exe), "format-manifest", str(manifest_path)], cwd=str(vcpkg_root))
        except Exception as e:
            print(f"[warn] format-manifest failed: {e}")
            print(f"[warn] Run manually later: ./vcpkg format-manifest {manifest_path}")
            return
    try:
        run_command([str(vcpkg_exe), "x-add-version", VCPKG_PORT_NAME], cwd=str(vcpkg_root))
    except Exception as e:
        print(f"[warn] x-add-version failed: {e}")
        print(f"[warn] Run manually later: ./vcpkg x-add-version {VCPKG_PORT_NAME}")
        return
    print(f"[ok] Ran ./vcpkg x-add-version {VCPKG_PORT_NAME}")


def commit_and_open_pr(vcpkg_root: Path, version: str) -> None:
    run_command(["git", "checkout", "-B", f"ta-lib-{version}"], cwd=str(vcpkg_root))
    run_command(["git", "add", "-A"], cwd=str(vcpkg_root))

    status = run_command(["git", "status", "--porcelain"], cwd=str(vcpkg_root))
    if not status.strip():
        print("[warn] No changes to commit — port files already up-to-date for this version.")
        return

    run_command(["git", "commit", "-m", f"[ta-lib] update to {version}"], cwd=str(vcpkg_root))
    run_command(["git", "push", "-u", "origin", f"ta-lib-{version}"], cwd=str(vcpkg_root))

    gh_path = shutil.which("gh")
    if gh_path is None:
        print("[warn] GitHub CLI not found; skipping PR creation.")
        print("       Run manually: gh pr create --repo microsoft/vcpkg --fill")
        return

    run_command([gh_path, "pr", "create", "--repo", "microsoft/vcpkg", "--fill"], cwd=str(vcpkg_root))
    print("[ok] Opened PR in microsoft/vcpkg")


def main() -> int:
    p = argparse.ArgumentParser(
        description="Submit a TA-Lib update PR to microsoft/vcpkg after a release.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=(
            "Run with no arguments to update the local vcpkg checkout and open a PR.\n"
            "Run with --plan to only print the update plan (used by CI, no side-effects)."
        ),
    )
    p.add_argument("--plan", action="store_true", help="Print the update plan only; do not modify anything.")
    p.add_argument("--vcpkg-root", help="Path to an existing local microsoft/vcpkg checkout (auto-cloned if omitted).")
    p.add_argument("--out-dir", default="temp/post-release-vcpkg", help="Directory for downloading/caching the release tarball.")
    args = p.parse_args()

    out_dir = Path(args.out_dir).resolve()

    # --- Step 1: resolve the authoritative version from the published release ---
    try:
        release_version, tar_name, asset_url = read_latest_release_src_tarball()
    except Exception as e:
        raise RuntimeError(
            f"Could not fetch latest TA-Lib release from GitHub: {e}\n"
            "Make sure the release has been published (not a draft) and you have internet access."
        )

    # Cross-check with local VERSION — warn if they differ (main may be bumped ahead).
    try:
        local_version = read_local_version()
        if local_version != release_version:
            print(
                f"[info] Local VERSION ({local_version}) differs from latest published release ({release_version}).\n"
                f"[info] Using release version {release_version} for the vcpkg update."
            )
    except Exception:
        pass  # Not critical — use the release version regardless.

    version = release_version

    # --- Step 2: download (or use cached) tarball and compute SHA512 ---
    tar_path = out_dir / tar_name
    if not tar_path.exists():
        print(f"Downloading {asset_url}")
        download(asset_url, tar_path)
    else:
        print(f"Using cached tarball: {tar_path}")

    sha512 = sha512_file(tar_path)

    # --- Step 3: print the plan ---
    print("\n=== TA-Lib vcpkg update plan ===")
    print(f"Version : {version}")
    print(f"Asset   : {asset_url}")
    print(f"SHA512  : {sha512}")

    if args.plan:
        print("\n[plan mode] No changes made.")
        return 0

    # --- Step 4: safety guards (only when actually performing operations) ---
    verify_git_repo_original()
    branch = _current_branch()
    if branch != "main":
        raise RuntimeError(
            f"Must be on the 'main' branch (currently on '{branch}').\n"
            "The vcpkg port update should only be submitted after the official TA-Lib\n"
            "release has been published from main."
        )

    _check_no_existing_vcpkg_pr(version)

    # --- Step 5: confirmation prompt ---
    print(
        "\nThis will:\n"
        f"  1) Clone/update microsoft/vcpkg locally\n"
        f"  2) Update ports/{VCPKG_PORT_NAME}/{{portfile.cmake,vcpkg.json}} to {version}\n"
        f"  3) Run ./vcpkg x-add-version {VCPKG_PORT_NAME}\n"
        f"  4) Commit, push branch ta-lib-{version}, and open a PR to microsoft/vcpkg\n"
    )
    confirm = input("Proceed? (yes/NO): ")
    if confirm.strip().lower() != "yes":
        print("Operation cancelled.")
        return 0

    # --- Step 6: perform the update ---
    vcpkg_root = Path(args.vcpkg_root) if args.vcpkg_root else Path(path_join(out_dir, "vcpkg"))
    vcpkg_root = ensure_vcpkg_checkout(vcpkg_root)
    update_vcpkg_files(vcpkg_root, version, sha512)
    run_x_add_version(vcpkg_root)
    commit_and_open_pr(vcpkg_root, version)

    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except Exception as e:
        print(f"Error: {e}")
        raise SystemExit(1)

