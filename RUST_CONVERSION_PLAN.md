# TA-Lib Rust Conversion Plan

Converting TA-Lib's C functions to Rust via the code generation pipeline.

See [RUST_CHANGELOG.md](RUST_CHANGELOG.md) for detailed commit history.

---

## Architecture

TA-Lib is a module that exports a `Core` struct. Functions are methods on `Core`:

```rust
pub struct Core {}

impl Core {
    pub fn mult(startIdx: usize, endIdx: usize, ...) -> RetCode { ... }
    pub fn sma(startIdx: usize, endIdx: usize, ...) -> RetCode { ... }
}
```

Multiple files extend `Core` via separate `impl Core` blocks (mult.rs, sma.rs, etc.).
Users instantiate core and call: `Core::mult(...)` (static) or `core.mult(...)` (instance).

## Design Decisions

These were established in early planning sessions (Dec 2024 - Feb 2025) with Mario:

**Error handling:** Uses `RetCode` enum (Success, BadParam, OutOfRangeStartIndex, OutOfRangeEndIndex, AllocErr, InternalError). Same pattern as Java. Source uses `ENUM_VALUE()` macro for cross-language handling.

**No unsafe:** We must preserve Rust's safety guarantees. No `unsafe` blocks allowed.

**No external dependencies:** Only the Rust standard library. Functions are simple array iterations.

**Threading model:** Core instances are single-threaded. For multi-threading, each thread owns a distinct Core instance (small memory footprint). No state is preserved between calls -- if a function allocates intermediate buffers, they're freed within the function scope.

**Pointers/memory:** Already solved by the Java/C# approach. C output arrays are accessed as `ptr[i]` with index arithmetic only, no pointer arithmetic. Rust slices (`&[f64]`, `&mut [f64]`) map directly.

**In-place buffers:** In C, input and output can be the same buffer. In Rust, you cannot pass the same slice as both `&[f64]` and `&mut [f64]`. Will address when tests reveal the issue.

**Increment operators:** Rust doesn't support `i++`. Handled by `FOR_EACH_OUTPUT` macro which generates `for i in start..=end` loops.

**Enums/flags:** Handled by `ENUM_VALUE()` macro. Binary flags like `TA_FUNC_FLG_OVERLAP` stay as-is.

**Testing strategy:**
- TDD unit tests in Rust (`rust/tests/`) for rapid development
- ta_regtest for C-to-Rust equivalency (future: compile a C+Rust variant that verifies output matches)

**Cargo.toml:** Hand-maintained for now; version synced by `sync.py`. May be generated later.

## How Code Generation Works

```
ta_SMA.c (source)  -->  gen_code processes  -->  ta_SMA.c (output with /* Generated */ prefix)
                                             -->  sma.rs (Rust file via mcpp with -D _RUST)
```

The approach is **macro-first**: when Rust needs different syntax, add a macro to `ta_defs.h` rather than writing `#if defined(_RUST)` conditionals in source files. The macro handles the language switch internally.

See CLAUDE.md for the full macro reference.

---

## Progress

### Completed

- [x] **Phase 1: Pipeline setup** (Dec 2024 - Feb 2025)
  - mcpp preprocessor with `_RUST` define
  - gen_rust.c with function signature generation (lookback, double, single precision)
  - Rust template and module structure
  - snake_case function name conversion

- [x] **Phase 2: Macro system** (Jun 2025)
  - Cross-language macros in ta_defs.h: FOR_EACH_OUTPUT, DECLARE_*_VAR, VALUE_HANDLE_*, ENUM_VALUE, CAST_TO_*
  - Curly braces on all generated if/else (Rust requires them, valid in all languages)
  - Cargo.toml, lib.rs, Core struct, RetCode enum

- [x] **Phase 3: MULT** (Jun 2025)
  - First function fully compiling and passing all tests
  - 6 tests: double precision, single precision, error conditions, lookback, partial range, usize validation
  - Established the pattern for converting simple functions

- [x] **Phase 4: SMA** (Jan - Mar 2026)
  - Optional parameter handling (`optInTimePeriod` with default value)
  - Lookback validation with `CAST_TO_I32` macro (replaced broken `TA_FUNC_NO_RANGE_CHECK`)
  - Internal function dispatch via `FUNCTION_CALL` macro (`TA_INT_SMA` -> `Self::int_sma`)
  - `CAST_TO_INDEX` for cross-language index types
  - 5 tests: basic, single precision, lookback, period 1, partial range
  - Note: SMA uses a `FUNCTION_CALL` macro pattern in MA.c where MA dispatches to SMA via `TA_INT_SMA`. This pattern is preserved in Rust via explicit `#define TA_INT_SMA Self::int_sma` mappings in ta_defs.h.

### Next Up

- [ ] **Phase 5: RSI** (Relative Strength Index)

  RSI introduces several new challenges beyond SMA:

  - **`TA_IS_ZERO` macro** -- floating point epsilon comparison to avoid divide-by-zero. Critical for financial calculations. See: "What Every Computer Scientist Should Know About Floating-Point Arithmetic."
  - **Unstable period** (`TA_GLOBALS_UNSTABLE_PERIOD`) -- RSI and other indicators need a warmup period where output is suppressed. This is state on the Core struct, not a simple constant.
  - **Compatibility mode** (`TA_GLOBALS_COMPATIBILITY`) -- Metastock compatibility affects calculation.
  - **`LOOKBACK_CALL(RSI)`** -- needs a Rust definition mapping to `Self::rsi_lookback()`. Currently only defined for C/Java.
  - **Optional parameter** (`optInTimePeriod`) -- already solved by SMA, but RSI validates differently.

- [ ] **Phase 6: Moving Averages (EMA, WMA, etc.)**

  The MA function (`ta_MA.c`) is a dispatcher that calls SMA, EMA, WMA, DEMA, TEMA, TRIMA, KAMA, MAMA, T3 based on `TA_MAType`. This uses `FUNCTION_CALL` extensively. Each sub-function will need:
  - Its own Rust implementation
  - `TA_INT_*` / `TA_S_INT_*` mappings in ta_defs.h
  - The dispatch logic in MA itself

- [ ] **Phase 7: Complex price inputs (OHLCV)**

  Functions like ATR, STOCH, WILLR take candlestick inputs (open, high, low, close, volume in various combinations). The generator needs to handle these multi-input signatures for Rust.

- [ ] **Phase 8: Remaining functions**

  Once the macro system covers all patterns (epsilon comparison, unstable periods, function dispatch, OHLCV inputs), the remaining ~150 functions should be largely mechanical to convert.

### Open Questions

- **`ARRAY_MEMMOVE` / `ARRAY_MEMMOVEMIX`** -- needed for functions that shift data in buffers. Rust equivalent: `dst[di..di+n].copy_from_slice(&src[si..si+n])` with possible type conversion for the MIX variant.
- **ta_regtest integration** -- how to build a C+Rust variant that validates output equivalency. GitHub Actions integration TBD.
- **Do-while loops** -- some C functions use do-while. Rust has no do-while; will need a macro or `loop { ...; if !cond { break; } }` pattern when encountered.
- **Switch statements** -- C switch/case will need Rust match expressions. May need a macro when encountered.

## Macros Still Needed

```
TA_IS_ZERO(x)                           // floating point epsilon compare
TA_GLOBALS_UNSTABLE_PERIOD(id, name)    // unstable period from Core state
TA_GLOBALS_COMPATIBILITY                // Metastock compatibility mode
LOOKBACK_CALL(x)                        // -> Self::x_lookback()
ARRAY_MEMMOVE(dst, di, src, si, n)      // buffer shift
ARRAY_MEMMOVEMIX(dst, di, src, si, n)   // buffer shift with type conversion
```

See CLAUDE.md for the full list with Rust/C expansions.
