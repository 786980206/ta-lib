#!/usr/bin/env python3

# Developer build helper for TA-Lib.
#
# Wraps CMake so you can build and test from any directory within the repo.
#
# Usage:
#   python3 scripts/build.py                Build library + all tools
#   python3 scripts/build.py ta_regtest     Build the regression test runner
#   python3 scripts/build.py gen_code       Build the legacy C code generator
#   python3 scripts/build.py ta_codegen     Build the Rust codegen tool
#   python3 scripts/build.py generate       Generate per-function source for all backends
#   python3 scripts/build.py servers        Generate + compile JSON-RPC language servers
#   python3 scripts/build.py test           C reference regression tests
#   python3 scripts/build.py regtest        Full cross-language regression tests
#   python3 scripts/build.py regtest-only   Codegen verification only (skip C tests)
#   python3 scripts/build.py clean          Remove build directory
#   python3 scripts/build.py help           Show all targets

import argparse
import os
import shutil
import subprocess
import sys

BUILD_DIR_NAME = "cmake-build"
DEFAULT_BUILD_TYPE = "Release"
DEFAULT_JOBS = 4

def find_repo_root() -> str:
    """Find the git repository root, regardless of where the script is called from."""
    # Use the script's own location to find the repo, so it works even
    # when cwd is outside the repository.
    script_dir = os.path.dirname(os.path.abspath(__file__))
    try:
        result = subprocess.run(
            ['git', 'rev-parse', '--show-toplevel'],
            check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
            cwd=script_dir
        )
        root = result.stdout.strip().decode('utf-8')
    except (subprocess.CalledProcessError, FileNotFoundError):
        print("Error: Must be run from within a TA-Lib Git repository.")
        sys.exit(1)

    # Sanity check
    if not os.path.isdir(os.path.join(root, 'src', 'ta_func')):
        print("Error: Not a complete TA-Lib repository (src/ta_func missing).")
        sys.exit(1)

    return root

def ensure_configured(root_dir: str, build_dir: str, build_type: str, cmake_args: str):
    """Ensure cmake-build exists and is configured. Reconfigure if CMakeLists.txt is newer."""
    cmake_cache = os.path.join(build_dir, "CMakeCache.txt")
    cmakelists = os.path.join(root_dir, "CMakeLists.txt")
    needs_configure = False

    if not os.path.exists(cmake_cache):
        needs_configure = True
    elif os.path.getmtime(cmakelists) > os.path.getmtime(cmake_cache):
        needs_configure = True

    if needs_configure:
        os.makedirs(build_dir, exist_ok=True)
        cmd = ['cmake', '..', f'-DCMAKE_BUILD_TYPE={build_type}']
        if cmake_args:
            cmd.extend(cmake_args.split())
        subprocess.run(cmd, check=True, cwd=build_dir)

def cmake_build(build_dir: str, target: str, jobs: int):
    """Run cmake --build for a specific target."""
    cmd = ['cmake', '--build', '.', '--target', target, '-j', str(jobs)]
    subprocess.run(cmd, check=True, cwd=build_dir)

def cmake_build_all(build_dir: str, jobs: int):
    """Run cmake --build with no specific target (build all)."""
    cmd = ['cmake', '--build', '.', '-j', str(jobs)]
    subprocess.run(cmd, check=True, cwd=build_dir)

def show_help():
    print("""TA-Lib Build Targets

  Building:
    (default)           Build library + all tools
    ta_regtest          Build the regression test runner
    gen_code            Build the legacy C code generator
    ta_codegen          Build the Rust codegen tool
    generate            Generate per-function source for all backends
    servers             Generate all source + compile JSON-RPC language servers

  Testing:
    test                C reference regression tests
    regtest             Full pipeline: servers + C tests + codegen verification
    regtest-only        Codegen verification only (skip C tests)

  Other:
    install             Install to system
    package             Create distribution package
    clean               Remove cmake-build/
    help                Show this message

  Options:
    --build-type=Debug  Set cmake build type (default: Release)
    --jobs=8            Parallel jobs (default: 4)
    --cmake-args="..."  Extra arguments passed to cmake configure
""")

# Targets that map to a single cmake target
SIMPLE_TARGETS = {
    'ta_regtest':  ['ta_regtest', 'ensure_ta_regtest_in_bin'],
    'gen_code':    ['gen_code', 'ensure_gen_code_in_bin'],
    'ta_codegen':  ['ta_codegen_bin'],
    'generate':    ['ta_codegen_generate'],
    'servers':     ['ta_codegen_servers'],
    'test':        ['test'],
    'regtest':     ['regtest'],
    'regtest-only':['regtest-only'],
    'install':     ['install'],
    'package':     ['package'],
}

def main():
    # Refuse to run as root/sudo.
    if os.getuid() == 0:
        print("Error: Do not run this script as root or with sudo.")
        sys.exit(1)

    parser = argparse.ArgumentParser(
        description="TA-Lib developer build helper",
        add_help=False,
    )
    parser.add_argument('target', nargs='?', default='all')
    parser.add_argument('--build-type', default=DEFAULT_BUILD_TYPE)
    parser.add_argument('--jobs', '-j', type=int, default=DEFAULT_JOBS)
    parser.add_argument('--cmake-args', default='')
    parser.add_argument('--help', '-h', action='store_true')
    args = parser.parse_args()

    if args.help or args.target == 'help':
        show_help()
        return

    root_dir = find_repo_root()
    build_dir = os.path.join(root_dir, BUILD_DIR_NAME)

    if args.target == 'clean':
        if os.path.exists(build_dir):
            shutil.rmtree(build_dir)
            print(f"Removed {build_dir}")
        else:
            print("Nothing to clean.")
        return

    ensure_configured(root_dir, build_dir, args.build_type, args.cmake_args)

    if args.target == 'all':
        cmake_build_all(build_dir, args.jobs)
    elif args.target in SIMPLE_TARGETS:
        for t in SIMPLE_TARGETS[args.target]:
            cmake_build(build_dir, t, args.jobs)
    else:
        print(f"Error: Unknown target '{args.target}'. Run with 'help' to see available targets.")
        sys.exit(1)

if __name__ == '__main__':
    main()
