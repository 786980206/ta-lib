# CLAUDE.md - TA-Lib Rust Integration Guide

## Quick Reference Commands

```bash
# Build gen_code (from project root)
cd cmake-build && cmake .. -DCMAKE_BUILD_TYPE=Release && make gen_code -j4

# Run gen_code (must run from bin directory)
cd /path/to/ta-lib/bin && ../cmake-build/bin/gen_code

# Verify Rust compilation
cd rust && cargo check

# Run Rust tests
cd rust && cargo test

# Format and lint Rust code (done automatically by gen_code)
cd rust && cargo fix --lib -p ta-lib --allow-dirty && cargo fmt
```

## High-Level Architecture

### Design Philosophy
- **TA-Lib** is a module that exports a `Core` struct
- Functions are implemented as methods on `Core`: `impl Core { pub fn mult(...) }`
- Multiple files can extend `Core` via separate `impl Core` blocks
- User instantiates core, then calls: `Core::mult(...)` (static) or `core.mult(...)` (instance)

### Code Generation Pipeline
1. **Source of Truth**: C files in `src/ta_func/ta_*.c` contain cross-language code
2. **Generator**: `gen_code` binary (built from `gen_code.c` + `gen_rust.c`)
3. **Preprocessor**: `mcpp` processes C files with `_RUST` defined
4. **Output**: Rust files in `rust/src/ta_func/*.rs`

### Key Files
- `src/tools/gen_code/gen_code.c` - Main generator (168KB, "heart of madness")
- `src/tools/gen_code/gen_rust.c` - Rust-specific signature generation
- `include/ta_defs.h` - Cross-language macros (Rust definitions lines 159-184, 225-273)
- `src/ta_abstract/templates/ta_x.rs.template` - Rust file template
- `rust/src/ta_func/mod.rs` - Generated module file

## Macro System

### Variable Declaration Macros (ta_defs.h)
```c
// Rust:
DECLARE_INDEX_VAR(name)   → let mut name: usize;
DECLARE_LOOP_VAR(name)    → /* no-op: FOR_EACH_OUTPUT creates binding */
DECLARE_INT_VAR(name)     → let mut name: i32;
DECLARE_DOUBLE_VAR(name)  → let mut name: f64;
```

### Loop Macros
```c
// FOR_EACH_OUTPUT: C → Rust conversion
FOR_EACH_OUTPUT(startIdx, endIdx, i, outIdx)
   outReal[outIdx] = OUTPUT_F64(inReal0[i] * inReal1[i]);
FOR_EACH_OUTPUT_END(outIdx)

// Rust expands to:
outIdx = 0;
for i in (startIdx as usize)..=(endIdx as usize) {
    outReal[outIdx] = (inReal0[i] * inReal1[i]) as f64;
    outIdx += 1;
}
```

### Value Handle Macros (for output params)
```c
VALUE_HANDLE_DEREF(name)         → (*name)           // dereference
VALUE_HANDLE_DEREF_INDEX(n, v)   → (*n) = (v)        // assign to deref
VALUE_HANDLE_DEREF_TO_ZERO(name) → (*name) = 0       // initialize to zero
```

### Type Conversion
```c
OUTPUT_F64(val)   → (val) as f64   // Cast to f64 (important for f32 inputs)
CAST_TO_USIZE(v)  → (v) as usize
CAST_TO_I32(v)    → (v) as i32
```

### Function/Enum Macros
```c
ENUM_VALUE(RetCode, TA_SUCCESS, Success) → RetCode::Success
FUNCTION_CALL(SMA)                       → TA_PREFIX(SMA) → depends on context
LOOKBACK_CALL(RSI)                       → TA_RSI_Lookback
```

## Critical Fixes Implemented

### 1. Loop Variable Declaration
**Problem**: `DECLARE_INDEX_VAR(i)` creates unused `let mut i: usize;` since `FOR_EACH_OUTPUT` creates its own binding
**Solution**: `DECLARE_LOOP_VAR(i)` - no-op for Rust, normal declaration for C

### 2. Index Validation
**Problem**: `startIdx < 0` meaningless for `usize` types
**Solution**: Modified `gen_code.c:3464-3476` - Rust skips negative checks, only validates `endIdx < startIdx`

### 3. Type Conversion
**Problem**: f32 inputs → f64 outputs need explicit cast in Rust
**Solution**: `OUTPUT_F64(val)` macro casts to f64 in Rust, no-op in C

## Next Functions to Implement

### RSI (Relative Strength Index)
**New Challenges**:
- `TA_IS_ZERO` macro - floating point epsilon comparison (avoid divide by zero)
- `TA_GLOBALS_UNSTABLE_PERIOD` - unstable period handling for technical indicators
- `TA_GLOBALS_COMPATIBILITY` - Metastock compatibility mode
- `LOOKBACK_CALL(RSI)` - calling lookback function within implementation
- Optional parameter: `optInTimePeriod` with default value handling

**Floating Point Note**: "What every computer scientist should know about floating point" - epsilon comparison is critical for financial calculations.

### SMA (Simple Moving Average)
**New Challenges**:
- `FUNCTION_CALL(INT_SMA)` - internal function calls between TA functions
- Pattern: `ta_SMA` calls `ta_INT_SMA` for the actual implementation
- This pattern is used in `ta_MA.c` which dispatches to SMA, EMA, WMA, etc.

### MA (Moving Average - dispatcher)
**Uses `FUNCTION_CALL` extensively**:
```c
retCode = FUNCTION_CALL(SMA)(startIdx, endIdx, inReal, optInTimePeriod, ...);
retCode = FUNCTION_CALL(EMA)(startIdx, endIdx, inReal, optInTimePeriod, ...);
// etc.
```
Needs Rust equivalent for method dispatch.

## Macros Still Needed for RSI/SMA

```c
// These need Rust implementations:
TA_IS_ZERO(x)                           // → x.abs() < f64::EPSILON ?
TA_GLOBALS_UNSTABLE_PERIOD(id, name)    // → Core state or const
TA_GLOBALS_COMPATIBILITY                // → Core config/const
LOOKBACK_CALL(x)                        // → Core::x_lookback()
FUNCTION_CALL(x)                        // → Core::x() or self.x()
ARRAY_MEMMOVE(dst, di, src, si, n)      // → dst[di..di+n].copy_from_slice(&src[si..si+n])
ARRAY_MEMMOVEMIX(dst, di, src, si, n)   // → same with type conversion
```

## Current Status

- **MULT** - Compiles clean with `cargo check` and all tests pass
- **RUST_SINGLE_FUNC** - Currently set to "MULT" in gen_code.c line 111
- **Price Inputs** - Complex candlestick inputs (OHLCV combinations) not fully supported yet

## Build Configuration

### gen_code.c Configuration (lines 105-111)
```c
#define ENABLE_JAVA
#define ENABLE_C
#define ENABLE_DOTNET
#define ENABLE_RUST

// Comment to generate all functions:
#define RUST_SINGLE_FUNC "MULT"
```

### Dependencies
- CMake 3.18+
- C compiler (clang/gcc)
- Rust toolchain (`rustup`)
- `mcpp` preprocessor (`brew install mcpp` or `apt install mcpp`)

## Type Mappings

| C Type | Rust Type | Notes |
|--------|-----------|-------|
| `int startIdx` | `usize` | Index into arrays |
| `int *outBegIdx` | `&mut usize` | Output param |
| `const double inReal[]` | `&[f64]` | Input slice |
| `double outReal[]` | `&mut [f64]` | Output slice |
| `const float inReal[]` | `&[f32]` | Single precision input |
| `int optInTimePeriod` | `i32` | Optional params stay i32 |

## Rust Ownership Considerations

**Future Challenge**: In C, input and output can be the same buffer. In Rust:
- Cannot pass same slice as both `&[f64]` and `&mut [f64]`
- Will need to handle in-place operations differently
- Cross that bridge when tests reveal the issue

## Java Reference

The Rust implementation is largely based on the Java implementation patterns. Key similarities:
- Both use method dispatch within class/impl
- Both have MInteger-style output parameter handling
- Both share the same GENCODE sections in source files

## Project Structure

```
ta-lib/
├── bin/                    # Built executables (gen_code, ta_regtest)
├── cmake-build/           # CMake build directory
├── include/
│   └── ta_defs.h          # Cross-language macros
├── rust/
│   ├── Cargo.toml
│   ├── src/
│   │   ├── lib.rs
│   │   └── ta_func/
│   │       ├── mod.rs     # Generated module declarations
│   │       └── mult.rs    # Generated MULT function
│   └── tests/
│       └── mult_test.rs
└── src/
    ├── ta_func/
    │   ├── ta_MULT.c      # Source with GENCODE sections
    │   ├── ta_RSI.c
    │   └── ta_SMA.c
    └── tools/gen_code/
        ├── gen_code.c     # Main generator
        └── gen_rust.c     # Rust signature generation
```
