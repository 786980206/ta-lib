# Cross-Language Testing Harness Implementation Plan

> **For Claude:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Build a harness that runs TA-Lib indicators in both C and Rust, compares outputs for exact equality, and benchmarks timing.

**Architecture:** Two standalone binaries (C and Rust) each run the same indicators with shared hardcoded test data, output JSON to stdout. A Python script orchestrates both, compares, and reports.

**Tech Stack:** C (linked against ta-lib-static), Rust (depends on ta-lib crate), Python 3 (comparison script)

---

### Task 1: Create directory structure and test data header

**Files:**
- Create: `tests/cross-language/test_data.h`

**Step 1: Create the directory structure**

```bash
mkdir -p tests/cross-language/c tests/cross-language/rust/src
```

**Step 2: Write test_data.h**

Create `tests/cross-language/test_data.h` with ~100 realistic price data points (these are real-world-ish OHLC close prices) and a second array for MULT's second input:

```c
#ifndef TEST_DATA_H
#define TEST_DATA_H

/* Shared test data for cross-language harness.
 * Source of truth — Rust data generated from this file.
 * ~100 data points of realistic daily close prices.
 */
static const double TEST_PRICES[] = {
    44.34, 44.09, 43.61, 44.33, 44.83, 45.10, 45.42, 45.84,
    46.08, 45.89, 46.03, 45.61, 46.28, 46.28, 46.00, 46.03,
    46.41, 46.22, 45.64, 46.21, 46.25, 45.71, 46.45, 45.78,
    45.35, 44.03, 44.18, 44.22, 44.57, 43.42, 42.66, 43.13,
    43.82, 44.28, 44.00, 43.46, 44.12, 43.52, 42.94, 42.55,
    42.69, 43.15, 43.58, 44.12, 44.53, 44.79, 45.08, 44.67,
    44.18, 43.56, 43.15, 43.52, 44.02, 44.53, 44.85, 45.13,
    45.42, 45.66, 45.22, 44.85, 44.34, 44.02, 43.61, 43.28,
    42.94, 43.33, 43.82, 44.28, 44.67, 45.08, 44.53, 44.85,
    45.13, 45.42, 45.71, 46.00, 45.64, 45.22, 44.79, 44.34,
    43.82, 43.28, 42.69, 42.15, 41.55, 41.06, 40.52, 40.03,
    39.57, 39.15, 38.75, 39.22, 39.75, 40.28, 40.85, 41.42,
    42.03, 42.55, 43.15, 43.75
};
static const int TEST_PRICES_LEN = sizeof(TEST_PRICES) / sizeof(double);

/* Second array for two-input functions (e.g. MULT) */
static const double TEST_PRICES_2[] = {
    1.02, 0.98, 1.01, 0.99, 1.03, 1.00, 0.97, 1.04, 1.01, 0.96,
    1.02, 1.00, 0.98, 1.03, 1.01, 0.99, 1.02, 0.97, 1.04, 1.00,
    0.98, 1.01, 1.03, 0.99, 0.97, 1.02, 1.00, 1.01, 0.98, 1.03,
    1.01, 0.99, 1.02, 1.00, 0.97, 1.04, 1.01, 0.98, 1.03, 1.00,
    0.99, 1.02, 1.01, 0.97, 1.03, 1.00, 0.98, 1.01, 1.02, 0.99,
    1.00, 1.03, 0.98, 1.01, 0.97, 1.02, 1.00, 0.99, 1.03, 1.01,
    0.98, 1.00, 1.02, 0.97, 1.01, 1.03, 0.99, 1.00, 0.98, 1.02,
    1.01, 0.97, 1.03, 1.00, 0.99, 1.01, 1.02, 0.98, 1.00, 1.03,
    0.97, 1.01, 1.00, 0.99, 1.02, 1.03, 0.98, 1.01, 1.00, 0.97,
    1.02, 0.99, 1.01, 1.03, 1.00, 0.98, 1.02, 1.01, 0.99, 1.00
};
static const int TEST_PRICES_2_LEN = sizeof(TEST_PRICES_2) / sizeof(double);

#endif /* TEST_DATA_H */
```

**Step 3: Commit**

```bash
git add tests/cross-language/test_data.h
git commit -m "feat: add shared test data header for cross-language harness"
```

---

### Task 2: Write the Python data generator script

**Files:**
- Create: `tests/cross-language/generate_rust_data.py`

**Step 1: Write generate_rust_data.py**

This script parses `test_data.h` and produces `rust/src/test_data.rs`:

```python
#!/usr/bin/env python3
"""Convert test_data.h to test_data.rs for cross-language harness."""

import re
import sys
from pathlib import Path

def parse_c_array(content: str, name: str) -> list[str]:
    """Extract array values from a C static const double array."""
    pattern = rf'static\s+const\s+double\s+{name}\[\]\s*=\s*\{{([^}}]+)\}}'
    match = re.search(pattern, content, re.DOTALL)
    if not match:
        print(f"ERROR: Could not find array '{name}' in test_data.h", file=sys.stderr)
        sys.exit(1)
    values_str = match.group(1)
    values = [v.strip() for v in values_str.split(',') if v.strip()]
    return values

def main():
    script_dir = Path(__file__).parent
    header_path = script_dir / "test_data.h"
    rust_path = script_dir / "rust" / "src" / "test_data.rs"

    content = header_path.read_text()

    prices = parse_c_array(content, "TEST_PRICES")
    prices_2 = parse_c_array(content, "TEST_PRICES_2")

    lines = [
        "// Auto-generated from test_data.h by generate_rust_data.py",
        "// Do not edit manually.",
        "",
        "#[allow(dead_code)]",
        f"pub const TEST_PRICES: [f64; {len(prices)}] = [",
    ]
    # Format 8 values per line
    for i in range(0, len(prices), 8):
        chunk = prices[i:i+8]
        line = "    " + ", ".join(f"{v}_f64" for v in chunk) + ","
        lines.append(line)
    lines.append("];")
    lines.append("")
    lines.append("#[allow(dead_code)]")
    lines.append(f"pub const TEST_PRICES_2: [f64; {len(prices_2)}] = [")
    for i in range(0, len(prices_2), 10):
        chunk = prices_2[i:i+10]
        line = "    " + ", ".join(f"{v}_f64" for v in chunk) + ","
        lines.append(line)
    lines.append("];")
    lines.append("")

    rust_path.write_text("\n".join(lines))
    print(f"Generated {rust_path} ({len(prices)} prices, {len(prices_2)} prices_2)")

if __name__ == "__main__":
    main()
```

**Step 2: Run it and verify output**

```bash
cd tests/cross-language && python3 generate_rust_data.py
cat rust/src/test_data.rs
```

Expected: a Rust file with `pub const TEST_PRICES: [f64; 100] = [...]` and `pub const TEST_PRICES_2: [f64; 100] = [...]`

**Step 3: Commit**

```bash
git add tests/cross-language/generate_rust_data.py tests/cross-language/rust/src/test_data.rs
git commit -m "feat: add Python script to generate Rust test data from C header"
```

---

### Task 3: Write the C harness binary

**Files:**
- Create: `tests/cross-language/c/main.c`
- Create: `tests/cross-language/c/CMakeLists.txt`

**Step 1: Write main.c**

The C binary runs each indicator with several parameter sets and outputs JSON. Uses `clock_gettime(CLOCK_MONOTONIC)` for timing on Linux, `mach_absolute_time()` on macOS.

```c
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifdef __APPLE__
#include <mach/mach_time.h>
#endif

#include "ta_libc.h"
#include "test_data.h"

/* Timing helpers */
static uint64_t now_ns(void) {
#ifdef __APPLE__
    static mach_timebase_info_data_t info = {0, 0};
    if (info.denom == 0) mach_timebase_info(&info);
    return mach_absolute_time() * info.numer / info.denom;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;
#endif
}

/* Print a double array as JSON */
static void print_double_array(const double *arr, int len) {
    printf("[");
    for (int i = 0; i < len; i++) {
        if (i > 0) printf(", ");
        printf("%.15g", arr[i]);
    }
    printf("]");
}

/* Run SMA with given period */
static void run_sma(int period, int startIdx, int endIdx, int *first) {
    double outReal[TEST_PRICES_LEN];
    int outBegIdx = 0, outNBElement = 0;
    memset(outReal, 0, sizeof(outReal));

    uint64_t t0 = now_ns();
    TA_RetCode rc = TA_SMA(startIdx, endIdx, TEST_PRICES,
                           period, &outBegIdx, &outNBElement, outReal);
    uint64_t elapsed = now_ns() - t0;

    if (!*first) printf(",\n");
    *first = 0;

    printf("  {\"function\": \"SMA\", \"params\": {\"period\": %d, \"startIdx\": %d, \"endIdx\": %d}, ",
           period, startIdx, endIdx);
    printf("\"retCode\": %d, \"outBegIdx\": %d, \"outNBElement\": %d, \"output\": ",
           (int)rc, outBegIdx, outNBElement);
    print_double_array(outReal, outNBElement);
    printf(", \"elapsed_ns\": %llu}", (unsigned long long)elapsed);
}

/* Run RSI with given period */
static void run_rsi(int period, int startIdx, int endIdx, int *first) {
    double outReal[TEST_PRICES_LEN];
    int outBegIdx = 0, outNBElement = 0;
    memset(outReal, 0, sizeof(outReal));

    uint64_t t0 = now_ns();
    TA_RetCode rc = TA_RSI(startIdx, endIdx, TEST_PRICES,
                           period, &outBegIdx, &outNBElement, outReal);
    uint64_t elapsed = now_ns() - t0;

    if (!*first) printf(",\n");
    *first = 0;

    printf("  {\"function\": \"RSI\", \"params\": {\"period\": %d, \"startIdx\": %d, \"endIdx\": %d}, ",
           period, startIdx, endIdx);
    printf("\"retCode\": %d, \"outBegIdx\": %d, \"outNBElement\": %d, \"output\": ",
           (int)rc, outBegIdx, outNBElement);
    print_double_array(outReal, outNBElement);
    printf(", \"elapsed_ns\": %llu}", (unsigned long long)elapsed);
}

/* Run MULT full range */
static void run_mult(int startIdx, int endIdx, int *first) {
    double outReal[TEST_PRICES_LEN];
    int outBegIdx = 0, outNBElement = 0;
    memset(outReal, 0, sizeof(outReal));

    uint64_t t0 = now_ns();
    TA_RetCode rc = TA_MULT(startIdx, endIdx, TEST_PRICES, TEST_PRICES_2,
                            &outBegIdx, &outNBElement, outReal);
    uint64_t elapsed = now_ns() - t0;

    if (!*first) printf(",\n");
    *first = 0;

    printf("  {\"function\": \"MULT\", \"params\": {\"startIdx\": %d, \"endIdx\": %d}, ",
           startIdx, endIdx);
    printf("\"retCode\": %d, \"outBegIdx\": %d, \"outNBElement\": %d, \"output\": ",
           (int)rc, outBegIdx, outNBElement);
    print_double_array(outReal, outNBElement);
    printf(", \"elapsed_ns\": %llu}", (unsigned long long)elapsed);
}

int main(void) {
    TA_RetCode rc = TA_Initialize();
    if (rc != TA_SUCCESS) {
        fprintf(stderr, "TA_Initialize failed: %d\n", (int)rc);
        return 1;
    }

    int first = 1;
    int endIdx = TEST_PRICES_LEN - 1;

    printf("[\n");

    /* SMA tests */
    run_sma(5,  0, endIdx, &first);
    run_sma(10, 0, endIdx, &first);
    run_sma(30, 0, endIdx, &first);

    /* RSI tests */
    run_rsi(14, 0, endIdx, &first);
    run_rsi(7,  0, endIdx, &first);

    /* MULT tests */
    run_mult(0, endIdx, &first);
    run_mult(10, 50, &first);

    printf("\n]\n");

    TA_Shutdown();
    return 0;
}
```

**Step 2: Write CMakeLists.txt for the C harness**

```cmake
cmake_minimum_required(VERSION 3.18)
project(ta_cross_language_c C)

# Find the parent TA-Lib build
set(TALIB_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../..")
set(TALIB_BUILD "${TALIB_ROOT}/cmake-build")

add_executable(cross_lang_c main.c)

target_include_directories(cross_lang_c PRIVATE
    "${TALIB_ROOT}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/.."
)

# Link against the static library built by the parent project
find_library(TALIB_STATIC
    NAMES ta-lib
    PATHS "${TALIB_BUILD}/lib" "${TALIB_BUILD}"
    NO_DEFAULT_PATH
)

if(NOT TALIB_STATIC)
    message(FATAL_ERROR "Could not find ta-lib static library in ${TALIB_BUILD}. Build the main project first.")
endif()

target_link_libraries(cross_lang_c PRIVATE ${TALIB_STATIC})

if(NOT WIN32)
    target_link_libraries(cross_lang_c PRIVATE m)
endif()
```

**Step 3: Build and run to verify JSON output**

```bash
cd tests/cross-language/c
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4
./cross_lang_c
```

Expected: valid JSON array with 7 test result objects.

**Step 4: Commit**

```bash
git add tests/cross-language/c/
git commit -m "feat: add C harness binary for cross-language testing"
```

---

### Task 4: Write the Rust harness binary

**Files:**
- Create: `tests/cross-language/rust/Cargo.toml`
- Create: `tests/cross-language/rust/src/main.rs`

**Step 1: Write Cargo.toml**

```toml
[package]
name = "cross-lang-rust"
version = "0.1.0"
edition = "2021"

[dependencies]
ta-lib = { path = "../../../rust" }
```

**Step 2: Write main.rs**

```rust
mod test_data;

use std::time::Instant;
use ta_lib::{Core, RetCode};

/// Format a f64 with full precision matching C's "%.15g"
fn fmt_f64(v: f64) -> String {
    // Use {:.*} with enough precision, then trim trailing zeros like %g
    let s = format!("{:.15e}", v);
    // Parse and reformat with %g-like behavior
    let v2: f64 = s.parse().unwrap();
    format!("{:.15}", v2)
        .trim_end_matches('0')
        .trim_end_matches('.')
        .to_string()
}

fn print_array(arr: &[f64]) {
    print!("[");
    for (i, v) in arr.iter().enumerate() {
        if i > 0 { print!(", "); }
        print!("{}", fmt_f64(*v));
    }
    print!("]");
}

fn print_comma(first: &mut bool) {
    if !*first { print!(",\n"); }
    *first = false;
}

fn run_sma(core: &Core, period: i32, start_idx: usize, end_idx: usize, first: &mut bool) {
    let mut out_real = vec![0.0_f64; test_data::TEST_PRICES.len()];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    let t0 = Instant::now();
    let rc = core.sma(
        start_idx, end_idx, &test_data::TEST_PRICES,
        period, &mut out_beg_idx, &mut out_nb_element, &mut out_real,
    );
    let elapsed = t0.elapsed().as_nanos();

    print_comma(first);
    print!("  {{\"function\": \"SMA\", \"params\": {{\"period\": {}, \"startIdx\": {}, \"endIdx\": {}}}, ", period, start_idx, end_idx);
    print!("\"retCode\": {}, \"outBegIdx\": {}, \"outNBElement\": {}, \"output\": ",
        rc as i32, out_beg_idx, out_nb_element);
    print_array(&out_real[..out_nb_element]);
    print!(", \"elapsed_ns\": {}}}", elapsed);
}

fn run_rsi(core: &Core, period: i32, start_idx: usize, end_idx: usize, first: &mut bool) {
    let mut out_real = vec![0.0_f64; test_data::TEST_PRICES.len()];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    let t0 = Instant::now();
    let rc = core.rsi(
        start_idx, end_idx, &test_data::TEST_PRICES,
        period, &mut out_beg_idx, &mut out_nb_element, &mut out_real,
    );
    let elapsed = t0.elapsed().as_nanos();

    print_comma(first);
    print!("  {{\"function\": \"RSI\", \"params\": {{\"period\": {}, \"startIdx\": {}, \"endIdx\": {}}}, ", period, start_idx, end_idx);
    print!("\"retCode\": {}, \"outBegIdx\": {}, \"outNBElement\": {}, \"output\": ",
        rc as i32, out_beg_idx, out_nb_element);
    print_array(&out_real[..out_nb_element]);
    print!(", \"elapsed_ns\": {}}}", elapsed);
}

fn run_mult(core: &Core, start_idx: usize, end_idx: usize, first: &mut bool) {
    let mut out_real = vec![0.0_f64; test_data::TEST_PRICES.len()];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    let t0 = Instant::now();
    let rc = core.mult(
        start_idx, end_idx,
        &test_data::TEST_PRICES, &test_data::TEST_PRICES_2,
        &mut out_beg_idx, &mut out_nb_element, &mut out_real,
    );
    let elapsed = t0.elapsed().as_nanos();

    print_comma(first);
    print!("  {{\"function\": \"MULT\", \"params\": {{\"startIdx\": {}, \"endIdx\": {}}}, ", start_idx, end_idx);
    print!("\"retCode\": {}, \"outBegIdx\": {}, \"outNBElement\": {}, \"output\": ",
        rc as i32, out_beg_idx, out_nb_element);
    print_array(&out_real[..out_nb_element]);
    print!(", \"elapsed_ns\": {}}}", elapsed);
}

fn main() {
    let core = Core::new();
    let mut first = true;
    let end_idx = test_data::TEST_PRICES.len() - 1;

    println!("[");

    // SMA tests
    run_sma(&core, 5,  0, end_idx, &mut first);
    run_sma(&core, 10, 0, end_idx, &mut first);
    run_sma(&core, 30, 0, end_idx, &mut first);

    // RSI tests
    run_rsi(&core, 14, 0, end_idx, &mut first);
    run_rsi(&core, 7,  0, end_idx, &mut first);

    // MULT tests
    run_mult(&core, 0, end_idx, &mut first);
    run_mult(&core, 10, 50, &mut first);

    println!("\n]");
}
```

**Step 3: Build and run to verify JSON output**

```bash
cd tests/cross-language/rust
cargo build --release
cargo run --release
```

Expected: valid JSON array with 7 test result objects, same structure as C output.

**Step 4: Commit**

```bash
git add tests/cross-language/rust/
git commit -m "feat: add Rust harness binary for cross-language testing"
```

---

### Task 5: Write the Python comparison script

**Files:**
- Create: `tests/cross-language/compare.py`

**Step 1: Write compare.py**

```python
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
        params = ", ".join(f"{k}={v}" for k, v in c["params"].items()
                          if k not in ("startIdx", "endIdx"))
        if not params:
            si, ei = c["params"].get("startIdx", 0), c["params"].get("endIdx", 0)
            params = f"[{si}..{ei}]"

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

    # Print results table
    print("\nCross-Language Test Results")
    print("=" * 78)
    print(f"{'Function':<10} {'Params':<20} {'Match':<7} {'C (us)':>10} {'Rust (us)':>10} {'Speedup':>8}")
    print("-" * 78)

    for row in rows:
        status = "PASS" if row["passed"] else "FAIL"
        print(f"{row['function']:<10} {row['params']:<20} {status:<7} "
              f"{row['c_us']:>10.1f} {row['r_us']:>10.1f} {row['speedup']:>7.1f}x")
        if row["errors"]:
            for err in row["errors"]:
                print(f"  >> {err}")

    passed_count = sum(1 for r in rows if r["passed"])
    failed_count = len(rows) - passed_count
    print("-" * 78)
    print(f"{passed_count}/{len(rows)} passed, {failed_count} failed")

    return all_pass

def main():
    # Ensure ta-lib C library is built
    talib_lib = PROJECT_ROOT / "cmake-build" / "lib"
    if not talib_lib.exists():
        print("ERROR: cmake-build/lib not found. Build the main ta-lib project first:")
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
```

**Step 2: Run the full comparison**

```bash
python3 tests/cross-language/compare.py
```

Expected: table showing all 7 tests, PASS/FAIL status, and timing.

**Step 3: Commit**

```bash
git add tests/cross-language/compare.py
git commit -m "feat: add Python comparison script for cross-language harness"
```

---

### Task 6: Fix float formatting to ensure exact match

**Files:**
- Modify: `tests/cross-language/rust/src/main.rs` (the `fmt_f64` function)
- Possibly modify: `tests/cross-language/c/main.c` (printf format)

**Step 1: Run compare.py and check for mismatches**

```bash
python3 tests/cross-language/compare.py
```

If there are formatting differences (e.g., C prints `44.34` but Rust prints `44.33999999999999`), fix by aligning the formatting approach.

The simplest fix: both use `%.15g` style formatting. In Rust, this is tricky because `{:.15}` is not the same as `%.15g`. The most reliable approach is to serialize as raw bytes (full precision) and compare numerically in Python rather than as strings.

**Step 2: If needed, switch to numeric comparison in compare.py**

The JSON parser already converts strings to Python floats, so comparison via `==` on the parsed float values should work. The risk is JSON serialization losing precision. Both C and Rust should print with enough decimal places. Use `%.17g` in C and a matching format in Rust to ensure full f64 round-trip fidelity.

**Step 3: Iterate until all 7 tests pass**

**Step 4: Commit**

```bash
git add tests/cross-language/
git commit -m "fix: align float formatting between C and Rust harnesses"
```

---

### Task 7: Add .gitignore and final polish

**Files:**
- Create: `tests/cross-language/.gitignore`

**Step 1: Write .gitignore**

```
c/build/
rust/target/
```

**Step 2: Verify everything works end-to-end**

```bash
python3 tests/cross-language/compare.py
```

Expected: all 7 tests PASS.

**Step 3: Final commit**

```bash
git add tests/cross-language/.gitignore
git commit -m "chore: add gitignore for cross-language harness build artifacts"
```

---

### Task 8: Add RetCode numeric mapping for Rust

**Context:** C's `TA_RetCode` enum has explicit integer values (`TA_SUCCESS = 0`, `TA_BAD_PARAM = 2`, etc.) but Rust's `RetCode` enum doesn't derive numeric values. The `rc as i32` cast in `main.rs` needs the Rust enum to have matching integer discriminants, or we need a match statement.

**Files:**
- Modify: `tests/cross-language/rust/src/main.rs`

**Step 1: Check if `RetCode as i32` produces correct values**

Look at `rust/src/ta_func/mod.rs` — if `RetCode` variants don't have explicit discriminants, `Success` = 0, `BadParam` = 1 (not 2 like C). Fix with a helper function:

```rust
fn retcode_to_int(rc: RetCode) -> i32 {
    match rc {
        RetCode::Success => 0,
        RetCode::BadParam => 2,
        RetCode::OutOfRangeStartIndex => 13,
        RetCode::OutOfRangeEndIndex => 14,
        RetCode::AllocErr => 3,
        RetCode::InternalError => 5000,
    }
}
```

Or: since we only expect `Success` (0) for valid test cases, verify the C values match and document the mapping.

**Step 2: Verify retCode values match between C and Rust output**

**Step 3: Commit if changes needed**

```bash
git add tests/cross-language/rust/src/main.rs
git commit -m "fix: align RetCode integer values between C and Rust harnesses"
```
