#!/usr/bin/env python3

# Test release candidate assets in 'dist'
#
# This script can be called directly by a dev and also from various
# GitHub Actions, branches and platforms (e.g. ubuntu-latest, windows-2022)
#
# The script must be executed from within a TA-Lib Git repos.
#
# Failing this test will **block** the official release.
#
# Returns a non-zero exit code if any problem is found.

import argparse
import os
import sys
import platform
import tempfile

from utilities.common import verify_git_repo, get_version_string, create_temp_dir
from install_tests.python import test_python_windows, test_python_linux

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Test release candidate assets in 'dist'")
    parser.add_argument('-p', '--pwd', type=str, default="", help="Password for sudo commands")
    args = parser.parse_args()

    sudo_pwd = args.pwd

    root_dir = verify_git_repo()
    version = get_version_string(root_dir)
    temp_dir = create_temp_dir(root_dir)

    # Identify the dist package to test by this host.
    host_platform = sys.platform
    if host_platform == "linux":
        package_file_path = os.path.join(root_dir, "dist", f"ta-lib-{version}-src.tar.gz")
    elif host_platform == "win32":
        arch = platform.architecture()[0]
        if arch == '64bit':
            package_file_path = os.path.join(root_dir, "dist", f"ta-lib-{version}-win64.zip")
        else:
            print( f"Architecture [{arch}] not yet supported. Only 64 bits supported on windows.")
    else:
        print(f"Unsupported platform [{host_platform}]")
        sys.exit(1)

    if not os.path.isfile(package_file_path):
        print(f"Package file not found: {package_file_path}. Do './scripts/package.py")
        sys.exit(1)

    # Simulate user doing a ta-lib-python installation.
    if host_platform == "linux":
        test_python_linux(package_file_path, temp_dir, version, sudo_pwd)
    elif host_platform == "win32":
        test_python_windows(package_file_path, temp_dir, version, sudo_pwd)
    else:
        print(f"Unsupported platform [{host_platform}]")
        sys.exit(1)
