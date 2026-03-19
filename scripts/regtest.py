#!/usr/bin/env python3
"""One-command regression testing and benchmarking.

Build control:
  --no-build                 Skip cmake (ta_regtest, ta_bench)
  --no-generate              Skip indicator AND server regeneration
  --no-generate-indicators   Skip indicator regeneration only
  --no-generate-servers      Skip server regeneration only

Test control:
  --no-regtest               Skip correctness verification
  --no-perftest              Skip performance benchmark
  --no-test                  Skip both regtest and perftest
  --test-only                Skip all build/generate, just run tests

Filters (applied to generate AND test):
  --language=c,rust          Filter languages
  --function=SMA,RSI         Filter indicators
  --codegen-only             Regtest: skip C reference tests

Perftest options:
  --points=5000              Data points (default 5000)
  --iters=20                 Iterations (default 20)

Examples:
  scripts/regtest.py                                             # full pipeline
  scripts/regtest.py --no-build --function=SMA                   # regen SMA + test
  scripts/regtest.py --no-build --no-generate-servers --function=SMA
                                                                 # regen SMA indicator + test
  scripts/regtest.py --no-regtest --language=c --function=STOCH  # build + perftest only
  scripts/regtest.py --test-only --no-regtest --function=STOCH   # just perftest, no build
"""

import os
import shutil
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from utilities.common import check_prerequisites, PREREQS_BUILD_SERVERS

OUR_FLAGS = {
    "--no-build", "--no-generate", "--no-generate-indicators", "--no-generate-servers",
    "--no-regtest", "--no-perftest", "--no-test", "--test-only",
}


def find_repo_root():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    result = subprocess.run(
        ["git", "rev-parse", "--show-toplevel"],
        check=True, capture_output=True, text=True, cwd=script_dir,
    )
    return result.stdout.strip()


def get_filter(args, prefix):
    for a in args:
        if a.startswith(prefix + "="):
            return a.split("=", 1)[1]
    return None


def main():
    check_prerequisites(PREREQS_BUILD_SERVERS)

    argv = sys.argv[1:]
    test_only      = "--test-only" in argv
    no_build       = "--no-build" in argv or test_only
    no_gen         = "--no-generate" in argv or test_only
    no_gen_ind     = "--no-generate-indicators" in argv or no_gen
    no_gen_srv     = "--no-generate-servers" in argv or no_gen
    no_test        = "--no-test" in argv
    no_regtest     = "--no-regtest" in argv or no_test
    no_perftest    = "--no-perftest" in argv or no_test

    # Alias --indicator to --function
    passthrough = [a.replace("--indicator=", "--function=", 1) if a.startswith("--indicator=") else a
                   for a in argv if a not in OUR_FLAGS]
    func_filter = get_filter(passthrough, "--function")
    lang_filter = get_filter(passthrough, "--language")

    root = find_repo_root()
    build_dir = os.path.join(root, "cmake-build")
    bin_dir = os.path.join(root, "bin")
    codegen_dir = os.path.join(root, "tools", "ta_codegen")
    jobs = str(os.cpu_count() or 4)

    # 1. cmake
    if not no_build:
        os.makedirs(build_dir, exist_ok=True)
        if not os.path.exists(os.path.join(build_dir, "CMakeCache.txt")):
            subprocess.run(["cmake", root, "-DCMAKE_BUILD_TYPE=Release"],
                           check=True, cwd=build_dir)
        print("=== Building ta_regtest + ta_bench ===")
        subprocess.run(["cmake", "--build", ".", "--target",
                        "ensure_ta_regtest_in_bin", "ta_bench", "-j", jobs],
                       check=True, cwd=build_dir)
        src = os.path.join(build_dir, "bin", "ta_bench")
        if os.path.exists(src):
            shutil.copy2(src, os.path.join(bin_dir, "ta_bench"))

    # 2. generate indicators
    if not no_gen_ind:
        print("\n=== Regenerating indicator files ===")
        cmd = ["cargo", "run", "--release", "--", "generate"]
        if lang_filter:
            cmd.append(f"--backend={lang_filter}")
        if func_filter:
            cmd.append(f"--function={func_filter}")
        subprocess.run(cmd, check=True, cwd=codegen_dir)

    # 3. generate servers
    if not no_gen_srv:
        print("\n=== Regenerating server files ===")
        cmd = ["cargo", "run", "--release", "--", "generate-servers"]
        if lang_filter:
            cmd.append(f"--backend={lang_filter}")
        subprocess.run(cmd, check=True, cwd=codegen_dir)

    # 4. compile servers (only if something was regenerated)
    did_generate = not no_gen_ind or not no_gen_srv
    if did_generate:
        print("\n=== Compiling servers ===")
        cmd = ["cargo", "run", "--release", "--", "build"]
        if lang_filter:
            cmd.append(f"--backend={lang_filter}")
        subprocess.run(cmd, check=True, cwd=codegen_dir)

    # 5. regtest
    rc = 0
    if not no_regtest:
        print("\n" + "=" * 60)
        print("REGTEST — correctness (252 points, all ranges)")
        print("=" * 60)
        regtest_args = list(passthrough)
        if not any(a.startswith("--codegen") for a in regtest_args):
            regtest_args = ["--codegen"] + regtest_args
        rc = subprocess.run(
            [os.path.join(bin_dir, "ta_regtest")] + regtest_args,
            cwd=bin_dir,
        ).returncode
        if rc != 0:
            print(f"\nRegtest FAILED (exit {rc})")
            sys.exit(rc)

    # 6. perftest
    if not no_perftest:
        print("\n" + "=" * 60)
        print("PERFTEST — performance (large dataset, averaged)")
        print("=" * 60, flush=True)
        bench_rc = subprocess.run(
            [os.path.join(bin_dir, "ta_bench")] + passthrough,
            cwd=bin_dir,
        ).returncode
        if bench_rc != 0 and rc == 0:
            rc = bench_rc

    sys.exit(rc)


if __name__ == "__main__":
    main()
