#!/usr/bin/env python3
"""Cross-language comparison harness for TA-Lib C vs Rust.

Builds both binaries, runs them, compares outputs for exact equality,
and reports timing differences.

Usage: python3 tests/cross-language/compare.py
"""

import json
import subprocess
import sys
import os
from pathlib import Path

SCRIPT_DIR = Path(__file__).parent
PROJECT_ROOT = SCRIPT_DIR.parent.parent


def build_c():
    """Build the C harness binary."""
    build_dir = SCRIPT_DIR / "c" / "build"
    build_dir.mkdir(exist_ok=True)

    print("Building C harness...")
    subprocess.run(
        ["cmake", "..", "-DCMAKE_BUILD_TYPE=Release"],
        cwd=build_dir, check=True,
        stdout=subprocess.DEVNULL, stderr=subprocess.PIPE,
    )
    subprocess.run(
        ["make", "-j4"],
        cwd=build_dir, check=True,
        stdout=subprocess.DEVNULL, stderr=subprocess.PIPE,
    )
    print("  C harness built.")
    return build_dir / "cross_lang_c"


def build_rust():
    """Build the Rust harness binary."""
    rust_dir = SCRIPT_DIR / "rust"

    print("Building Rust harness...")
    subprocess.run(
        ["cargo", "build", "--release"],
        cwd=rust_dir, check=True,
        stdout=subprocess.DEVNULL, stderr=subprocess.PIPE,
    )
    print("  Rust harness built.")
    return rust_dir / "target" / "release" / "cross-lang-rust"


def run_binary(path: Path, label: str) -> list[dict]:
    """Run a harness binary and parse its JSON output."""
    print(f"Running {label} harness...")
    result = subprocess.run(
        [str(path)],
        capture_output=True, text=True, check=True,
    )
    data = json.loads(result.stdout)
    print(f"  {label} returned {len(data)} test results.")
    return data


def compare_results(c_results: list[dict], rust_results: list[dict]) -> bool:
    """Compare C and Rust results for exact equality. Returns True if all pass."""
    if len(c_results) != len(rust_results):
        print(f"\nERROR: C returned {len(c_results)} results, Rust returned {len(rust_results)}")
        return False

    all_pass = True
    rows = []

    for i, (c, r) in enumerate(zip(c_results, rust_results)):
        func = c["function"]
        params = ", ".join(
            f"{k}={v}" for k, v in c["params"].items()
            if k not in ("startIdx", "endIdx", "n")
        )
        n = c["params"].get("n", 0)
        if not params:
            si = c["params"].get("startIdx", 0)
            ei = c["params"].get("endIdx", 0)
            params = f"[{si}..{ei}]"
        if n > 1000:
            params += f" n={n // 1000}k"

        passed = True
        errors = []

        # Compare retCode
        if c["retCode"] != r["retCode"]:
            passed = False
            errors.append(f"retCode: C={c['retCode']} Rust={r['retCode']}")

        # Compare outBegIdx
        if c["outBegIdx"] != r["outBegIdx"]:
            passed = False
            errors.append(f"outBegIdx: C={c['outBegIdx']} Rust={r['outBegIdx']}")

        # Compare outNBElement
        if c["outNBElement"] != r["outNBElement"]:
            passed = False
            errors.append(f"outNBElement: C={c['outNBElement']} Rust={r['outNBElement']}")

        # Compare output arrays element-wise (exact match)
        c_out = c["output"]
        r_out = r["output"]
        if len(c_out) != len(r_out):
            passed = False
            errors.append(f"output length: C={len(c_out)} Rust={len(r_out)}")
        else:
            for j, (cv, rv) in enumerate(zip(c_out, r_out)):
                if cv != rv:
                    passed = False
                    errors.append(f"output[{j}]: C={cv!r} Rust={rv!r}")
                    if len(errors) > 5:
                        errors.append("... (more differences)")
                        break

        if not passed:
            all_pass = False

        c_us = c["elapsed_ns"] / 1000.0
        r_us = r["elapsed_ns"] / 1000.0
        speedup = c_us / r_us if r_us > 0 else float("inf")

        rows.append({
            "function": func,
            "params": params,
            "passed": passed,
            "c_us": c_us,
            "r_us": r_us,
            "speedup": speedup,
            "errors": errors,
        })

    def fmt_time(us: float) -> str:
        """Format time with auto-scaling units."""
        if us >= 1000:
            return f"{us / 1000:.1f}ms"
        if us < 1.0:
            return f"{us * 1000:.0f}ns"
        return f"{us:.1f}us"

    # Print results table
    print("\nCross-Language Test Results")
    print("=" * 85)
    print(
        f"{'Function':<10} {'Params':<28} {'Match':<7} "
        f"{'C':>10} {'Rust':>10} {'Speedup':>8}"
    )
    print("-" * 85)

    for row in rows:
        status = "PASS" if row["passed"] else "FAIL"
        print(
            f"{row['function']:<10} {row['params']:<28} {status:<7} "
            f"{fmt_time(row['c_us']):>10} {fmt_time(row['r_us']):>10} {row['speedup']:>7.1f}x"
        )
        if row["errors"]:
            for err in row["errors"]:
                print(f"  >> {err}")

    passed_count = sum(1 for r in rows if r["passed"])
    failed_count = len(rows) - passed_count
    print("-" * 85)
    print(f"{passed_count}/{len(rows)} passed, {failed_count} failed")

    return all_pass


def main():
    # Ensure ta-lib C library is built (check both lib/ subdir and cmake-build root)
    talib_build = PROJECT_ROOT / "cmake-build"
    talib_lib_dir = talib_build / "lib"
    talib_lib_root = talib_build / "libta-lib.a"

    if not talib_lib_dir.exists() and not talib_lib_root.exists():
        print("ERROR: ta-lib static library not found. Build the main ta-lib project first:")
        print("  cd cmake-build && cmake .. -DCMAKE_BUILD_TYPE=Release && make -j4")
        sys.exit(1)

    # Generate Rust test data from C header
    print("Generating Rust test data from C header...")
    subprocess.run(
        [sys.executable, str(SCRIPT_DIR / "generate_rust_data.py")],
        check=True,
    )

    c_bin = build_c()
    rust_bin = build_rust()

    c_results = run_binary(c_bin, "C")
    rust_results = run_binary(rust_bin, "Rust")

    all_pass = compare_results(c_results, rust_results)

    sys.exit(0 if all_pass else 1)


if __name__ == "__main__":
    main()
