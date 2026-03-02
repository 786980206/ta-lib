# Cross-Language Testing Harness Design

## Goal

Two standalone executables (C and Rust) run the same indicators with identical hardcoded inputs, output JSON to stdout. A Python script runs both, compares outputs for exact equality, and reports timing.

## Structure

```
tests/cross-language/
├── test_data.h              # Single source of truth: hardcoded price arrays
├── c/
│   ├── CMakeLists.txt       # Builds the C harness binary
│   └── main.c               # Runs indicators, prints JSON
├── rust/
│   ├── Cargo.toml           # Depends on ta-lib (path = "../../rust")
│   └── src/main.rs          # Runs indicators, prints JSON
├── compare.py               # Orchestrates, compares, reports
└── generate_rust_data.py    # Converts test_data.h → test_data.rs
```

## Decisions

- **Test data**: Hardcoded arrays in a C header (`test_data.h`), converted to Rust via a Python script
- **Comparison script**: Python
- **Float tolerance**: Exact match (no epsilon)
- **Output format**: JSON to stdout
- **Location**: `tests/cross-language/`

## Data Flow

```
test_data.h ──────────────────► C binary ────► JSON stdout ──┐
     │                                                        │
     ├─► generate_rust_data.py ► test_data.rs ► Rust binary ─► JSON stdout ──┤
                                                              │
                                                        compare.py
                                                              │
                                                        ┌─────┴─────┐
                                                     Results     Timing
                                                   (pass/fail)  (table)
```

## test_data.h

Single source of truth. ~100 data points of realistic price data. A second array for two-input functions (MULT).

```c
#ifndef TEST_DATA_H
#define TEST_DATA_H

static const double TEST_PRICES[] = { 44.34, 44.09, ... };
static const int TEST_PRICES_LEN = sizeof(TEST_PRICES) / sizeof(double);

static const double TEST_PRICES_2[] = { ... };
static const int TEST_PRICES_2_LEN = sizeof(TEST_PRICES_2) / sizeof(double);
#endif
```

## JSON Output Format

Each program outputs a JSON array:

```json
[
  {
    "function": "SMA",
    "params": {"period": 10},
    "outBegIdx": 9,
    "outNBElement": 91,
    "output": [44.34, 44.28, ...],
    "elapsed_ns": 1234
  }
]
```

## Test Cases Per Indicator

- **MULT**: full range, partial range
- **SMA**: period 5, 10, 30, default period
- **RSI**: period 14 (default), period 7, with unstable period set

## C Binary

Links against `ta_lib` static library. Uses `clock_gettime` for timing. Manual JSON formatting (no dependencies).

## Rust Binary

Depends on `ta-lib = { path = "../../rust" }`. Uses `std::time::Instant` for timing. Manual JSON formatting (no serde).

## compare.py

1. Build C binary (cmake)
2. Build Rust binary (cargo build --release)
3. Run both, capture JSON
4. Compare per test case: outBegIdx, outNBElement, output array (exact f64 match)
5. Print results table with pass/fail and timing

## Output Example

```
Cross-Language Test Results
==========================
Function  Params          Match  C (us)  Rust (us)  Speedup
--------  --------------  -----  ------  ---------  -------
SMA       period=5        PASS   12      8          1.5x
SMA       period=10       PASS   15      9          1.7x
SMA       period=30       PASS   18      11         1.6x
RSI       period=14       PASS   45      28         1.6x
RSI       period=7        PASS   38      22         1.7x
MULT      full_range      PASS   5       3          1.7x

6/6 passed, 0 failed
```
