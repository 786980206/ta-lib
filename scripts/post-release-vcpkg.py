#!/usr/bin/env python3
"""
Manual helper to prepare/update a TA-Lib vcpkg port PR.

Why this exists:
- Homebrew already has manual post-release support via post-release-brew.py.
- vcpkg maintainers welcomed a manual PR workflow for TA-Lib updates.

What this script does:
1) Reads latest TA-Lib release from GitHub.
2) Downloads the source tarball and computes SHA512 (required by vcpkg).
3) Prints ready-to-copy update instructions for microsoft/vcpkg.
4) Optionally updates a local vcpkg checkout (versions + baseline) when provided.

Notes:
- This script is intentionally conservative and defaults to "plan/output" mode.
- It does not push branches by default.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import re
import sys
from pathlib import Path
from urllib.request import urlopen


API_RELEASE_LATEST = "https://api.github.com/repos/TA-Lib/ta-lib/releases/latest"
ASSET_PATTERN = re.compile(r"ta-lib-(\d+\.\d+\.\d+)-src\.tar\.gz$")


def sha512_file(path: Path) -> str:
    h = hashlib.sha512()
    with path.open("rb") as f:
        for chunk in iter(lambda: f.read(1024 * 1024), b""):
            h.update(chunk)
    return h.hexdigest()


def fetch_json(url: str) -> dict:
    with urlopen(url) as r:
        return json.loads(r.read().decode("utf-8"))


def download(url: str, out: Path) -> None:
    out.parent.mkdir(parents=True, exist_ok=True)
    with urlopen(url) as r, out.open("wb") as f:
        while True:
            chunk = r.read(1024 * 1024)
            if not chunk:
                break
            f.write(chunk)


def read_latest_release() -> tuple[str, str]:
    data = fetch_json(API_RELEASE_LATEST)
    tag = data.get("tag_name", "")
    assets = data.get("assets", [])
    for a in assets:
        name = a.get("name", "")
        if ASSET_PATTERN.search(name):
            m = ASSET_PATTERN.search(name)
            assert m is not None
            version = m.group(1)
            return version, a.get("browser_download_url", "")
    raise RuntimeError("Could not find ta-lib-<version>-src.tar.gz asset in latest release")


def update_vcpkg_files(vcpkg_root: Path, version: str, sha512: str) -> None:
    """
    Best-effort local file updates for a standard vcpkg checkout.
    If expected files are missing, print guidance and return.
    """
    portfile = vcpkg_root / "ports" / "ta-lib" / "portfile.cmake"
    vcpkg_json = vcpkg_root / "ports" / "ta-lib" / "vcpkg.json"

    if not portfile.exists() or not vcpkg_json.exists():
        print("[warn] Could not find ports/ta-lib files in provided vcpkg checkout.")
        print("       Please update the port manually in microsoft/vcpkg.")
        return

    # Update version in vcpkg.json (best effort)
    data = json.loads(vcpkg_json.read_text())
    if "version" in data:
        data["version"] = version
    elif "version-string" in data:
        data["version-string"] = version
    else:
        data["version"] = version
    vcpkg_json.write_text(json.dumps(data, indent=2) + "\n")

    # Replace SHA512 in portfile.cmake (first SHA512 occurrence)
    text = portfile.read_text()
    text_new = re.sub(r"(SHA512\s+)[0-9a-fA-F]{64,128}", rf"\1{sha512}", text, count=1)
    if text_new == text:
        print("[warn] Could not auto-replace SHA512 in portfile.cmake. Update manually.")
    else:
        portfile.write_text(text_new)

    print("[ok] Updated local vcpkg ta-lib port files.")


def main() -> int:
    p = argparse.ArgumentParser(description="Prepare TA-Lib vcpkg update info")
    p.add_argument("--vcpkg-root", help="Optional path to local microsoft/vcpkg checkout")
    p.add_argument("--out-dir", default="temp/post-release-vcpkg", help="Download/cache directory")
    args = p.parse_args()

    version, asset_url = read_latest_release()
    if not asset_url:
        raise RuntimeError("Latest release asset URL missing")

    out_dir = Path(args.out_dir)
    tar_name = f"ta-lib-{version}-src.tar.gz"
    tar_path = out_dir / tar_name

    if not tar_path.exists():
        print(f"Downloading {asset_url}")
        download(asset_url, tar_path)
    else:
        print(f"Using cached tarball: {tar_path}")

    sha512 = sha512_file(tar_path)

    print("\n=== TA-Lib vcpkg update plan ===")
    print(f"Version : {version}")
    print(f"Asset   : {asset_url}")
    print(f"SHA512  : {sha512}")
    print("\nSuggested next steps:")
    print("1) Clone/fetch microsoft/vcpkg")
    print("2) Update ports/ta-lib/{portfile.cmake,vcpkg.json}")
    print("3) Run: ./vcpkg x-add-version ta-lib")
    print("4) Commit + open PR to microsoft/vcpkg")

    if args.vcpkg_root:
        update_vcpkg_files(Path(args.vcpkg_root), version, sha512)

    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except Exception as e:
        print(f"Error: {e}")
        raise SystemExit(1)
