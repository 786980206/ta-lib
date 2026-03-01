# RSI Conversion Design

## Overview

Convert RSI (Relative Strength Index) from C/Java to Rust via the gen_code pipeline. RSI is the first "unstable" indicator — it introduces Core instance state, unstable periods, compatibility modes, and several new macros.

## Key Decisions

- **Core becomes stateful** — matching Java exactly. All functions (including MULT/SMA) become `&self` methods. Breaking change to existing API.
- **FuncUnstId enum** — generated via ta_defs.h macros, drop `FuncUnstNone = -1` sentinel (use `Option<FuncUnstId>` if needed). 25 variants including `FuncUnstAll` for array sizing.
- **Compatibility enum** — 2 variants (Default, Metastock), also in template.

## Core Struct

```rust
pub struct Core {
    pub unstable_period: [i32; FuncUnstId::FuncUnstAll as usize],
    pub compatibility: Compatibility,
}

impl Core {
    pub fn new() -> Self { /* zeros + Default */ }
    pub fn set_unstable_period(&mut self, id: FuncUnstId, period: i32) { ... }
    pub fn get_unstable_period(&self, id: FuncUnstId) -> i32 { ... }
    pub fn set_compatibility(&mut self, compat: Compatibility) { ... }
    pub fn get_compatibility(&self) -> Compatibility { ... }
}
```

## Macro Changes

### 1. TA_GLOBALS (ta_memory.h) — separate Rust from Java

Current: `#elif defined(_JAVA) || defined(_RUST)` with Java syntax (`this.unstablePeriod[FuncUnstId.y.ordinal()]`).

Fix: Add separate `#elif defined(_RUST)` branch:
```c
#define TA_GLOBALS_UNSTABLE_PERIOD(x,y) (self.unstable_period[FuncUnstId::y as usize])
#define TA_GLOBALS_COMPATIBILITY        (self.compatibility)
```

### 2. LOOKBACK_CALL — generator-level fix

Can't use a macro (C preprocessor can't lowercase `RSI` → `rsi`). gen_code already knows the snake_case name, so it should emit the lookback call directly in the generated output, replacing `LOOKBACK_CALL(RSI)(args)` with `self.rsi_lookback(args)` for Rust.

### 3. ARRAY_MEMMOVE / ARRAY_MEMMOVEMIX (ta_memory.h)

Add Rust branch:
```c
#elif defined(_RUST)
  #define ARRAY_MEMMOVE(dest,destIdx,src,srcIdx,size) \
    dest[destIdx..destIdx+(size)].copy_from_slice(&src[srcIdx..srcIdx+(size)])
  #define ARRAY_MEMMOVEMIX(dest,destIdx,src,srcIdx,size) \
    for _mmi in 0..(size) { dest[destIdx+_mmi] = src[srcIdx+_mmi] as f64; }
  #define ARRAY_MEMMOVEMIX_VAR /* no-op */
```

### 4. TA_IS_ZERO — no change needed

Existing definition `(((-TA_EPSILON)<v)&&(v<TA_EPSILON))` compiles as-is in Rust.

### 5. Function signatures (gen_rust.c)

Add `&self,` as first parameter in:
- `printRustDoublePrecisionFunctionSignature`
- `printRustSinglePrecisionFunctionSignature`
- `printRustLookbackFunctionSignature`

## ta_RSI.c Logic Section Changes

Replace raw C declarations with macros:
- `int outIdx` → `DECLARE_INDEX_VAR(outIdx)`
- `int today` → `DECLARE_INDEX_VAR(today)`
- `int lookbackTotal` → `DECLARE_INT_VAR(lookbackTotal)`
- `int unstablePeriod` → `DECLARE_INT_VAR(unstablePeriod)`
- `int i` → `DECLARE_INT_VAR(i)`
- `double prevGain` etc → `DECLARE_DOUBLE_VAR(prevGain)` etc

Replace C syntax:
- `today++` → `today = today + 1`
- `outIdx++` → `outIdx = outIdx + 1`
- `for(i=optInTimePeriod; i > 0; i--)` → `FOR_COUNTDOWN(optInTimePeriod, i)` ... `FOR_COUNTDOWN_END`
- Type conversions at int/usize boundaries with `CAST_TO_INDEX()` / `CAST_TO_I32()`

## Two-Phase Work Breakdown

### Phase A — Infrastructure (no new indicator)

1. Add `Compatibility` + `FuncUnstId` enums to mod.rs template
2. Make Core stateful (fields, constructor, accessors)
3. Add `&self` to all three signature generators in gen_rust.c
4. Separate Rust from Java in `TA_GLOBALS_*` macros (ta_memory.h)
5. Add Rust `ARRAY_MEMMOVE` / `ARRAY_MEMMOVEMIX` / `ARRAY_MEMMOVEMIX_VAR` definitions
6. Handle `LOOKBACK_CALL` in gen_code for Rust
7. Update existing MULT/SMA tests + doctests for `&self` API
8. Rebuild, verify zero regressions on all 16 existing tests

### Phase B — RSI conversion

1. Convert ta_RSI.c logic section (DECLARE macros, post-increments, FOR_COUNTDOWN)
2. Add RSI to `RUST_SUPPORTED_FUNCS`
3. Write RSI tests (TDD — basic, single precision, lookback, error conditions, unstable period, Metastock compat)
4. Rebuild gen_code + run gen_code
5. Fix compilation issues
6. Update tracking (CLAUDE.md, RUST_CHANGELOG.md)

## Verification

- All existing 16 tests must pass after Phase A (zero regressions)
- RSI tests must cover: basic calculation, single precision, lookback, bad params, default period, unstable period behavior, Metastock compatibility mode
- `cargo check` with zero warnings
- C/Java/.NET output unchanged (verify with `git diff`)
