#!/usr/bin/env python3
"""One-command regression testing and benchmarking.

Usage:
  scripts/regtest.py                          # full: build + regtest + bench
  scripts/regtest.py --bench-only             # skip regtest, just bench
  scripts/regtest.py --regtest-only           # skip bench, just regtest
  scripts/regtest.py --no-build               # skip build step (use existing binaries)
  scripts/regtest.py --no-generate            # skip codegen regeneration
  scripts/regtest.py --codegen-only           # regtest: skip C ref tests
  scripts/regtest.py --language=c,rust        # filter languages (both regtest + bench)
  scripts/regtest.py --function=SMA,RSI       # filter functions (both regtest + bench)
  scripts/regtest.py --points=5000            # bench: data points (default 5000)
  scripts/regtest.py --iters=20               # bench: iterations (default 20)

All unknown arguments are passed through to ta_regtest/ta_bench.
"""

import os
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from utilities.common import check_prerequisites, PREREQS_BUILD_SERVERS


def find_repo_root():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    result = subprocess.run(
        ["git", "rev-parse", "--show-toplevel"],
        check=True, capture_output=True, text=True, cwd=script_dir,
    )
    return result.stdout.strip()


def build(root, build_dir, codegen_dir, do_cmake, do_generate):
    jobs = str(os.cpu_count() or 4)

    if do_cmake:
        # cmake configure if needed
        os.makedirs(build_dir, exist_ok=True)
        cache = os.path.join(build_dir, "CMakeCache.txt")
        if not os.path.exists(cache):
            subprocess.run(
                ["cmake", root, "-DCMAKE_BUILD_TYPE=Release"],
                check=True, cwd=build_dir,
            )

        # build ta_regtest + ta_bench
        print("=== Building ta_regtest + ta_bench ===")
        subprocess.run(
            ["cmake", "--build", ".", "--target", "ensure_ta_regtest_in_bin", "ta_bench",
             "-j", jobs],
            check=True, cwd=build_dir,
        )
        # copy ta_bench to bin/
        src = os.path.join(build_dir, "bin", "ta_bench")
        dst = os.path.join(root, "bin", "ta_bench")
        if os.path.exists(src):
            import shutil
            shutil.copy2(src, dst)

    if do_generate:
        print("\n=== Regenerating output files ===")
        subprocess.run(
            ["cargo", "run", "--release", "--", "generate"],
            check=True, cwd=codegen_dir,
        )
        print("\n=== Generating servers ===")
        subprocess.run(
            ["cargo", "run", "--release", "--", "generate-servers"],
            check=True, cwd=codegen_dir,
        )

    # Always rebuild servers (compiles generated code into binaries)
    print("\n=== Building codegen servers ===")
    subprocess.run(
        ["cargo", "run", "--release", "--", "build"],
        check=True, cwd=codegen_dir,
    )


def run_regtest(bin_dir, passthrough_args):
    # Default to --codegen if no codegen flag
    args = list(passthrough_args)
    if not any(a.startswith("--codegen") for a in args):
        args = ["--codegen"] + args

    print("\n" + "=" * 60)
    print("REGTEST — correctness verification (252 points, all ranges)")
    print("=" * 60)
    cmd = [os.path.join(bin_dir, "ta_regtest")] + args
    return subprocess.run(cmd, cwd=bin_dir).returncode


def run_bench(bin_dir, passthrough_args):
    print("\n" + "=" * 60)
    print("BENCH — performance comparison (large dataset, averaged)")
    print("=" * 60)
    cmd = [os.path.join(bin_dir, "ta_bench")] + passthrough_args
    return subprocess.run(cmd, cwd=bin_dir).returncode


def main():
    check_prerequisites(PREREQS_BUILD_SERVERS)

    # Parse our flags vs passthrough args
    our_flags = {"--bench-only", "--regtest-only", "--no-build", "--no-generate", "--run-only"}
    do_bench_only = "--bench-only" in sys.argv
    do_regtest_only = "--regtest-only" in sys.argv
    run_only = "--run-only" in sys.argv
    do_build = "--no-build" not in sys.argv and not run_only
    do_generate = "--no-generate" not in sys.argv and not run_only

    # Passthrough: everything that's not our flag
    passthrough = [a for a in sys.argv[1:] if a not in our_flags]

    root = find_repo_root()
    build_dir = os.path.join(root, "cmake-build")
    bin_dir = os.path.join(root, "bin")
    codegen_dir = os.path.join(root, "tools", "ta_codegen")

    if not run_only:
        build(root, build_dir, codegen_dir, do_build, do_generate)

    rc = 0

    if not do_bench_only:
        rc = run_regtest(bin_dir, passthrough)
        if rc != 0:
            print(f"\nRegtest failed (exit {rc})")
            sys.exit(rc)

    if not do_regtest_only:
        bench_rc = run_bench(bin_dir, passthrough)
        if bench_rc != 0 and rc == 0:
            rc = bench_rc

    sys.exit(rc)


if __name__ == "__main__":
    main()
