#!/usr/bin/env python3
"""One-command regression testing: build everything, then run ta_regtest.

Usage:
  scripts/regtest.py                     # C tests + all codegen languages
  scripts/regtest.py --codegen-only      # skip C tests, codegen only
  scripts/regtest.py --language=c,rust   # filter languages
  scripts/regtest.py --function=SMA,RSI  # filter functions

All arguments are passed through to ta_regtest.
"""

import os
import subprocess
import sys

def find_repo_root():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    result = subprocess.run(
        ["git", "rev-parse", "--show-toplevel"],
        check=True, capture_output=True, text=True, cwd=script_dir,
    )
    return result.stdout.strip()

def main():
    root = find_repo_root()
    build_dir = os.path.join(root, "cmake-build")
    bin_dir = os.path.join(root, "bin")
    codegen_dir = os.path.join(root, "tools", "ta_codegen")

    # 1. Build ta_regtest (cmake)
    print("=== Building ta_regtest ===")
    os.makedirs(build_dir, exist_ok=True)
    cache = os.path.join(build_dir, "CMakeCache.txt")
    if not os.path.exists(cache):
        subprocess.run(
            ["cmake", root, "-DCMAKE_BUILD_TYPE=Release"],
            check=True, cwd=build_dir,
        )
    subprocess.run(
        ["cmake", "--build", ".", "--target", "ensure_ta_regtest_in_bin",
         "-j", str(os.cpu_count() or 4)],
        check=True, cwd=build_dir,
    )

    # 2. Build codegen servers (cargo + gcc)
    print("\n=== Building codegen servers ===")
    subprocess.run(
        ["cargo", "run", "--release", "--", "build"],
        check=True, cwd=codegen_dir,
    )

    # 3. Run ta_regtest with passthrough args
    # Default to --codegen if no codegen flag is present
    user_args = sys.argv[1:]
    has_codegen_flag = any(
        a.startswith("--codegen") for a in user_args
    )
    if not has_codegen_flag:
        user_args = ["--codegen"] + user_args

    print("\n=== Running ta_regtest ===")
    cmd = [os.path.join(bin_dir, "ta_regtest")] + user_args
    result = subprocess.run(cmd, cwd=bin_dir)
    sys.exit(result.returncode)

if __name__ == "__main__":
    main()
