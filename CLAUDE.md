# CLAUDE.md - TA-Lib Rust Integration Guide

## CRITICAL: Generated Code Philosophy

**DO NOT hand-write language-specific code in source files.** The entire system is designed around code generation:

1. **Function signatures are GENERATED** by `ta_codegen` (the Rust codegen tool) for indicator functions. The `gen_rust.c` functions (`printRustDoublePrecisionFunctionSignature`, `printRustSinglePrecisionFunctionSignature`, `printRustLookbackFunctionSignature`) are now only used for FFI wrapper generation.
2. **GENCODE sections are GENERATED** - never manually edit lines prefixed with `/* Generated */`
3. **Macros enable cross-language code** - use macros from `ta_defs.h` rather than writing language-specific syntax
4. **If you need new Rust functionality**, the correct approach is:
   - Add a new macro to `ta_defs.h` with proper `#if defined( _RUST )` / `#else` handling
   - OR add a new print function to `gen_rust.c` and call it from `gen_code.c`
   - NEVER write raw Rust syntax in `.c` source files

### PREFER MACROS OVER CONDITIONALS

When modifying source `.c` files (in the logic sections between GENCODE 3-5), **use macros directly** rather than adding `#if defined(_RUST)` conditionals:

**WRONG** - Adding conditionals in source:
```c
#if defined( _RUST )
   DECLARE_DOUBLE_VAR(periodTotal)
#else
   double periodTotal;
#endif
```

**RIGHT** - Using macros directly (let macro handle the switch):
```c
   DECLARE_DOUBLE_VAR(periodTotal)
```

The macro in `ta_defs.h` already handles language switching:
- Rust: `DECLARE_DOUBLE_VAR(x)` → `let mut x: T;` (generic over `TaFloat`)
- C/Java: `DECLARE_DOUBLE_VAR(x)` → `double x;`

This keeps the source clean and maintainable. If a macro doesn't exist for what you need, **add the macro to ta_defs.h** rather than adding conditionals to source files.

### Cross-Language Development Workflow

When converting an indicator to Rust, the process is:

1. **Compare** the generated Rust output (`rust/src/ta_func/xxx.rs`) against the Java reference in `Core.java` — the Java is the known-working target
2. **Find syntax mismatches** — anything that doesn't compile or behaves differently
3. **Trace the origin** — is the bad syntax in:
   - The hand-written logic (between GENCODE 3-5 in `ta_XXX.c`)?
   - The generated scaffolding (`printFunc`, `printOptInputValidation`, etc. in `gen_code.c`)?
4. **Fix at the right level**, in this priority order:
   - **Light C refactoring** (preferred) — remove unnecessary syntax that's invalid in Rust but a no-op in C/Java (e.g., adding curly braces to bare if/else). BUT: verify the syntax is truly unnecessary across ALL parameter types and languages first.
   - **New macro in `ta_defs.h`** — when syntax genuinely differs or has semantic meaning in some code paths. Every macro MUST have a healthy default for C/Java/.NET (the `#else` branch).
   - **Generator changes in `gen_code.c`/`gen_rust.c`** — when the scaffolding itself needs different output per language
   - **ALWAYS verify C/Java/.NET output is unchanged** after any fix (`git diff` the generated files)
5. **Rebuild and verify**: build gen_code → run gen_code from `bin/` → `cargo check` → `cargo test`

**Precedent**: Commits `a6702544`/`c2aacd15` added curly braces to all generated if/else in `gen_code.c` because Rust requires them — a light refactoring that's valid in all languages, cleaner than a macro.

### Code Generation Flow
```
ta_SMA.c (source)     →  gen_code processes  →  ta_SMA.c (output with Generated prefix)
                                              →  sma.rs (Rust file via mcpp)
```

The generator:
1. Reads source `.c` files
2. Creates templates by emptying GENCODE sections
3. RE-GENERATES those sections using `printFunc`, `printRustXxxSignature`, etc.
4. Extracts "logic" between sections 3-5 and re-inserts with `/* Generated */` prefix
5. Runs mcpp to produce Rust output

## Quick Reference Commands

```bash
# Build gen_code (from project root)
cd cmake-build && cmake .. -DCMAKE_BUILD_TYPE=Release && make gen_code -j4

# Run gen_code (must run from bin directory)
cd bin && ../cmake-build/bin/gen_code

# Verify Rust compilation
cd rust && cargo check

# Run Rust tests
cd rust && cargo test

# Format and lint Rust code (done automatically by gen_code)
cd rust && cargo fix --lib -p ta-lib --allow-dirty && cargo fmt

# Build ta_regtest (universal test runner)
cd cmake-build && cmake .. -DCMAKE_BUILD_TYPE=Release && make ta_regtest -j4

# Run C reference tests (standard)
cd ../bin && ./ta_regtest

# Run codegen verification against all languages (all 158 indicators)
./ta_regtest --codegen

# Run codegen verification, skip C reference tests
./ta_regtest --codegen-only

# Filter by language and function
./ta_regtest --codegen --language=c,rust --function=RSI,SMA

# Run ta_regtest with multiple function filters
./ta_regtest --function=MATH,RSI,"Moving Averages"
```

## Cross-Language Regression Testing

### Target Architecture: Server-Based Testing

`ta_regtest` is the **universal test runner** for all languages. Instead of linking directly against each language's compiled code, ta_regtest drives **JSON-RPC servers** generated by `ta_codegen`:

```
ta_regtest (C)
    ↓ JSON-RPC over stdin/stdout
    ├── ta_codegen_serve_c      (C server)
    ├── TaCodegenServe.class    (Java server)
    ├── TaCodegenServe          (.NET server)
    ├── ta_codegen_serve.py     (Python/SWIG server)
    └── (future: Rust server)
```

Each server:
- Exposes compiled, generated indicator code for its language
- Reports available functions via `list_functions`
- Returns timing data (`timing_ns`) with each call
- Supports `set_unstable_period` and `set_compatibility` for global state

All of ta_regtest's existing test logic, test data, range testing, and expected values run unchanged — the only difference is the transport layer.

### Current State

The system is fully implemented. `codegen_pipe.c/h` handles subprocess management and JSON-RPC communication. `test_codegen.c` has a generic callback driven by `TA_ForEachFunc` enumeration — it covers all 158 indicators automatically using ta_abstract function metadata. The callback handles:
- Price inputs (STOCH, BBANDS, ADX) via `TA_InputParameterInfo.flags` → OHLCV arrays
- Multi-output functions (BBANDS=3, MACD=3, STOCH=2) via per-`outputNb` `doRangeTest` calls
- Integer outputs (CDL* candlestick patterns, MINMAXINDEX) with exact match comparison
- Real optional params (BBANDS `optInNbDevUp`, SAR `optInAcceleration`) via `json_find_double`
- All 24 unstable-period functions with `unstablePeriod` propagation to servers
- Timing summary, cross-language comparison table, and JSONL report output

See `src/tools/ta_regtest/CLAUDE.md` and `tools/ta_codegen/CLAUDE.md` for detailed specs.

### Server Generation

```bash
cd tools/ta_codegen
cargo run -- generate-servers              # Generate server source for all languages
cargo run -- generate-servers --backend=c  # Generate for specific language
cargo run -- build                         # Compile servers into bin/
```

Output: `ta_codegen_output/{c,java,dotnet,swig}/`

### `--function=CSV` Filter

The `--function` flag accepts a comma-separated list of names. Each name is substring-matched against test group descriptions:

| Filter Value | Test Group(s) Matched |
|-------------|----------------------|
| `MATH` | MATH,VECTOR,DCPERIOD/PHASE,TRENDLINE/MODE (includes MULT) |
| `Moving Averages` | All Moving Averages (includes SMA) |
| `RSI` | RSI,CMO + STOCH,STOCHF,STOCHRSI (substring match) |
| `BBANDS` | BBANDS |
| `ADX` | ADX,ADXR,DI,DM,DX |

Without `--function`, all test groups run (existing behavior).

### Key Files

| File | Purpose |
|------|---------|
| `tools/ta_codegen/src/server_gen.rs` | Generates JSON-RPC servers for all languages |
| `tools/ta_codegen/src/main.rs` | `generate-servers` and `build` commands |
| `ta_codegen_output/` | Generated server source per language |
| `src/tools/ta_regtest/` | Universal test runner (C) |

## High-Level Architecture

### Design Philosophy
- **TA-Lib** is a module that exports a `Core` struct
- Functions are implemented as methods on `Core`: `impl Core { pub fn mult(...) }`
- Multiple files can extend `Core` via separate `impl Core` blocks
- User instantiates core, then calls: `Core::mult(...)` (static) or `core.mult(...)` (instance)

## Rust Generic Type System

### TaFloat Trait
All indicator functions are generic over `T: TaFloat`, a sealed trait implemented for `f32` and `f64`. The type is inferred from the input/output slice types:

```rust
// f64 usage (default)
let input: &[f64] = &[1.0, 2.0, 3.0];
let mut output = [0.0f64; 3];
core.sma(0, 2, input, 3, &mut beg, &mut nb, &mut output);

// f32 usage (same function name)
let input: &[f32] = &[1.0, 2.0, 3.0];
let mut output = [0.0f32; 3];
core.sma(0, 2, input, 3, &mut beg, &mut nb, &mut output);
```

### Function Variants
Each indicator generates 4 variants:

| Variant | Safety | Indexing | Use Case |
|---------|--------|----------|----------|
| `sma<T>` | Safe | Bounds-checked | Public API |
| `sma_unguarded<T>` | Safe | Bounds-checked | Cross-indicator calls |
| `sma_unchecked<T>` | Unsafe | get_unchecked | Performance-critical |
| `sma_unguarded_unchecked<T>` | Unsafe | get_unchecked | Internal hot paths |

- **Guarded** validates parameters and delegates to `_unguarded`
- **Unchecked** uses `get_unchecked` for array access (unsafe)
- Cross-indicator calls use `_unguarded` to avoid double-validation

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
   outReal[outIdx] = CAST_TO_F64(inReal0[i] * inReal1[i]);
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
CAST_TO_F64(v)    → (v) as f64     // Cast to f64 (important for f32 inputs)
CAST_TO_INDEX(v)  → (v) as usize   // Cast to index type (usize in Rust, int in C/Java)
CAST_TO_I32(v)    → (v) as i32
```

### Control Flow Macros
```c
IF_CONDITION(expr)      → if expr {
IF_CONDITION_END        → }
FOR_COUNTDOWN(i, n)     → for i in (0..n).rev() {
FOR_COUNTDOWN_END       → }
```

### Array/Function Macros
```c
ARRAY_ACCESS(arr, i)                     → arr[i]
ENUM_VALUE(RetCode, TA_SUCCESS, Success) → RetCode::Success
FUNCTION_CALL(SMA)                       → TA_PREFIX(SMA) → depends on context
FUNCTION_CALL_DOUBLE(SMA)                → explicit f64 variant (used in cross-indicator calls)
LOOKBACK_CALL(RSI)                       → TA_RSI_Lookback → self.rsi_lookback
```

**Note**: `LOOKBACK_CALL` uses two-level expansion for Rust. `LOOKBACK_CALL(RSI)` → `TA_RSI_Lookback` → `self.rsi_lookback`. Add one `#define TA_XXX_Lookback self.xxx_lookback` per function in `ta_defs.h`.

**Note**: `TA_FUNC_NO_RANGE_CHECK` was removed — it disabled ALL validation including basic range checks, causing test regressions. Use targeted macros (`CAST_TO_I32`, exclusion guards) instead.

## Known Gotchas

- **Loop variables**: Use `DECLARE_LOOP_VAR(i)` (no-op for Rust) instead of `DECLARE_INDEX_VAR(i)` when the variable is rebound by `FOR_EACH_OUTPUT`
- **Index validation**: Rust skips `startIdx < 0` checks (meaningless for `usize`); see `gen_code.c:3464-3476`
- **Type conversion**: With generics, f32 inputs produce f32 outputs and f64 inputs produce f64 outputs. `CAST_TO_F64` is used internally where needed but the public API is generic over `T: TaFloat`.

## Next Functions to Implement

### MA (Moving Average - dispatcher)
**Uses `FUNCTION_CALL` extensively** to dispatch to SMA, EMA, WMA, etc. Needs Rust equivalent for method dispatch.

### EMA (Exponential Moving Average)
Uses unstable period like RSI. Should be straightforward given RSI infrastructure.

## Macros Completed for RSI

All macros needed for RSI are now implemented:
- `TA_IS_ZERO(x)` — already worked as-is (C epsilon comparison compiles in Rust)
- `TA_GLOBALS_UNSTABLE_PERIOD(x,y)` — `self.unstable_period[FuncUnstId::y as usize]` (ta_memory.h)
- `TA_GLOBALS_COMPATIBILITY` — `self.compatibility` (ta_memory.h)
- `LOOKBACK_CALL(x)` — two-level expansion via `TA_RSI_Lookback` → `self.rsi_lookback` (ta_defs.h)
- `ARRAY_MEMMOVE` / `ARRAY_MEMMOVEMIX` — `copy_from_slice` / element-wise `as f64` (ta_memory.h)

## Current Status

- **MULT** - Complete, all 6 tests pass + 1 doctest
- **SMA** - Complete, all 7 tests pass + 1 doctest (rich hand-written example)
- **RSI** - Complete, all 13 tests pass + 1 doctest. First "unstable" indicator — uses Core state, unstable periods, compatibility modes.
- **Doc generation** - `printRustFuncDoc` in gen_rust.c generates `///` doc comments from ta_abstract metadata. Zero `missing_docs` warnings. Uses `@RUSTDOC@` markers to survive mcpp. Rich examples override via `src/ta_abstract/rust_examples/<name>.txt`.
- **RUST_SUPPORTED_FUNCS** - Currently `"SMA,MULT,RSI"` in gen_code.c line 111
- **Generic type system** — `TaFloat` sealed trait replaces `_s` suffix convention. f32 inputs produce f32 outputs.
- **Price Inputs** - Complex candlestick inputs (OHLCV combinations) not fully supported yet

## Build Configuration

### gen_code.c Configuration (lines 105-111)
```c
#define ENABLE_JAVA
#define ENABLE_C
#define ENABLE_DOTNET
#define ENABLE_RUST

// CSV list of supported Rust functions (comment out to generate all):
#define RUST_SUPPORTED_FUNCS "SMA,MULT,RSI"
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
| `const double inReal[]` | `&[T]` where `T: TaFloat` | Generic over f32/f64 |
| `double outReal[]` | `&mut [T]` | Generic output slice |
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

## Changelog Format (RUST_CHANGELOG.md)

One entry per day. If multiple commits happen on the same day, consolidate into a single entry. Each bullet links to the specific commit that introduced it:

```markdown
## 2026-03-01 -- Short title summarizing the day's work

`git diff abc1234^..fed9876` | [view on GitHub](https://github.com/TA-Lib/ta-lib/compare/def5678...fed9876)

* [abc1234](https://github.com/TA-Lib/ta-lib/commit/abc1234) Description of change from this commit
* [abc1234](https://github.com/TA-Lib/ta-lib/commit/abc1234) Another change from the same commit
* [fed9876](https://github.com/TA-Lib/ta-lib/commit/fed9876) Change from a different commit
* All 13 Rust tests passing (6 MULT + 7 SMA)
```

**Range inclusivity — critical:**
- **Local diff**: `git diff first^..last` — the `^` after `first` makes it inclusive (without `^`, `first`'s changes are excluded)
- **GitHub URL**: `compare/<PARENT-of-first>...last` — GitHub `compare/A...B` excludes A, so use `git rev-parse first^` to get the parent hash and use that in the URL
- **Verify**: run `git log first^..last --oneline | wc -l` and confirm the count matches the number of bulleted commits (excluding the summary bullet)

Rules:
- **One entry per day** — amend the existing entry if pushing more commits on the same day
- **Every commit = at least one bullet** — no exceptions, even for tracking updates, formatting fixes, or regeneration commits. If it's in the range, it gets a bullet.
- **Per-bullet commit links** — every bullet gets `[short-hash](commit-url)`, even if multiple bullets share the same commit
- **Summary bullet at the end** — total test count to show nothing regressed
- **Amend the changelog commit** when updating the same day's entry

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
│   │       ├── mult.rs    # Generated MULT function
│   │       └── sma.rs     # Generated SMA function
│   └── tests/
│       ├── mult_test.rs
│       └── sma_test.rs
└── src/
    ├── ta_func/
    │   ├── ta_MULT.c      # Source with GENCODE sections
    │   ├── ta_RSI.c
    │   └── ta_SMA.c
    └── tools/gen_code/
        ├── gen_code.c     # Main generator
        └── gen_rust.c     # Rust signature generation
```
