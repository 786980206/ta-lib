# Design: Cross-Language ta_regtest via Link-Time FFI Swap

## Problem

ta_regtest is the trusted source of truth for TA-Lib correctness — it validates each function across ~32,000 range combinations with battle-tested tolerance logic. But it only tests C code. As we port functions to Rust, we need the same rigorous validation without reimplementing (and re-trusting) the test logic.

## Solution

Link ta_regtest against Rust implementations via FFI instead of (not in addition to) the C static library. ta_regtest's test logic stays untouched — it just calls into different object code.

## Architecture

```
                    ta_regtest.c (unchanged test logic)
                              │
              ┌───────────────┼───────────────┐
              ▼                               ▼
      Link: ta-lib-static             Link: libta_lib_ffi.a
      (C implementations)             (Rust via extern "C")
      target: ta_regtest              target: ta_regtest_rust
      (existing, unchanged)           (new build target)
```

## Components

### 1. FFI Staticlib — `rust/ffi/`

A separate Rust crate (`crate-type = ["staticlib"]`) that exports `#[no_mangle] pub extern "C"` wrappers matching the exact C signatures from `ta_func.h`.

- One wrapper per ported function (e.g., `TA_SMA`, `TA_SMA_Lookback`)
- Type mapping: C pointers ↔ Rust slices, `TA_RetCode` ↔ c_int, etc.
- **No fallback to C** for unported functions — they simply won't be linked
- If ta_regtest calls an unported function, it fails at link time (caught immediately) or at runtime with a missing symbol

Example wrapper:
```rust
#[no_mangle]
pub extern "C" fn TA_SMA(
    start_idx: c_int,
    end_idx: c_int,
    in_real: *const c_double,
    opt_in_time_period: c_int,
    out_beg_idx: *mut c_int,
    out_nb_element: *mut c_int,
    out_real: *mut c_double,
) -> c_int {
    // Convert C types → Rust types, call ta_lib::Core::sma(), convert back
}
```

### 2. gen_code Extension — FFI Wrapper Generation

Extend `gen_code` (specifically `gen_rust.c`) to also emit the `extern "C"` FFI wrappers alongside the pure Rust functions. gen_code already knows every function's signature, parameter types, and output structure — it has everything needed to generate the shims.

Output: `rust/ffi/src/generated.rs` (or per-function files)

### 3. CLI Filter on ta_regtest — `--function=NAME[,NAME,...]`

Small change to `ta_regtest.c` main():
- Parse `--function=SMA,RSI,BBANDS` from argv
- When set, skip `testTAFunction_*()` calls that don't match any name in the CSV list
- When not set, run everything (existing behavior preserved exactly)
- ~20-30 lines of change, all in main() argument parsing and the test dispatch section

### 4. CMake Build Target

New target in `CMakeLists.txt`:
- `ta_regtest_rust`: same sources as `ta_regtest`, links `libta_lib_ffi.a` + Rust stdlib instead of `ta-lib-static`
- Gated behind `ENABLE_RUST_REGTEST` cmake flag
- Existing `ta_regtest` target completely unchanged

## AI Tight-Loop Workflow

```bash
# Porting BBANDS to Rust:
# 1. gen_code generates bbands.rs + FFI wrapper
# 2. Implement/fix the Rust logic
# 3. Test:
cargo build --manifest-path rust/ffi/Cargo.toml
cmake --build cmake-build --target ta_regtest_rust
./bin/ta_regtest_rust --function=BBANDS

# Clear pass/fail. Fix and repeat from step 2.
```

## What Changes

| Component | Change |
|-----------|--------|
| `ta_regtest.c` | ~20-30 lines: argv parsing + conditional test dispatch |
| `gen_rust.c` / `gen_code.c` | Emit extern "C" FFI wrappers per function |
| `CMakeLists.txt` | New `ta_regtest_rust` target |
| `rust/ffi/` | New crate (staticlib) — mostly generated code |

## What Does NOT Change

- ta_regtest test logic, range testing, tolerance math, buffer overflow detection
- ta_regtest C build target and its behavior
- Existing Rust crate (`rust/`) and its unit tests
- Cross-language harness in `tests/cross-language/`
- Any C source files in `src/ta_func/`

## Risk Assessment

**ta_regtest code risk**: Minimal. Only main() gets a CLI filter. All test functions, range logic, tolerance — untouched.

**FFI correctness risk**: Self-validating. If calling conventions are wrong, ta_regtest fails loudly. The 3 already-passing functions (SMA, RSI, MULT) serve as the FFI canary — if they pass ta_regtest via FFI, the bridge is correct.

**Build system risk**: New target only, doesn't affect existing targets.

## Validation Plan

1. Hand-write FFI wrappers for SMA, RSI, MULT (the 3 functions already ported)
2. Build `ta_regtest_rust`, run with `--function=SMA,RSI,MULT`
3. Confirm all 3 pass — this proves the FFI bridge is correct
4. Then extend gen_code to generate the wrappers automatically
5. Verify generated wrappers produce same results as hand-written ones
6. Remove hand-written wrappers, use generated ones going forward
