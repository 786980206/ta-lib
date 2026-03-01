# RSI Conversion Implementation Plan

> **For Claude:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Convert RSI (Relative Strength Index) to Rust via the gen_code pipeline, introducing Core instance state, unstable periods, and compatibility modes.

**Architecture:** Two-phase approach. Phase A adds infrastructure (stateful Core, new enums, macro fixes) without adding RSI. Phase B converts the RSI logic and adds tests. All existing tests must pass after each phase.

**Tech Stack:** C (gen_code, ta_defs.h, ta_memory.h), Rust (generated output), mcpp preprocessor

**Key reference files:**
- Design doc: `docs/plans/2026-03-01-rsi-conversion-design.md`
- C source: `src/ta_func/ta_RSI.c` (logic between GENCODE 3-5)
- Java reference: `java/src/com/tictactec/ta/lib/Core.java` (search "rsiLookback" and "rsi(")
- SMA patterns: `src/ta_func/ta_SMA.c` (established DECLARE/CAST macro usage)

---

## Phase A: Infrastructure

### Task 1: Add Compatibility and FuncUnstId enums to template

**Files:**
- Modify: `src/ta_abstract/templates/ta_func_mod.rs.template`

**Step 1: Add the enums to the template**

Add `Compatibility` and `FuncUnstId` enums after `RetCode` and before the `Core` struct definition. Match the variants from `include/ta_defs.h:342-389`.

```rust
/// Compatibility mode for technical analysis calculations.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Compatibility {
    Default,
    Metastock,
}

/// Identifies functions that have an unstable period.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum FuncUnstId {
    Adx,
    Adxr,
    Atr,
    Cmo,
    Dx,
    Ema,
    HtDcPeriod,
    HtDcPhase,
    HtPhasor,
    HtSine,
    HtTrendline,
    HtTrendMode,
    Imi,
    Kama,
    Mama,
    Mfi,
    MinusDI,
    MinusDM,
    Natr,
    PlusDI,
    PlusDM,
    Rsi,
    StochRsi,
    T3,
    FuncUnstAll,
}
```

Note: Drop `FuncUnstNone = -1` — Rust uses `Option<FuncUnstId>` instead. `FuncUnstAll` is the last variant and its discriminant (24) is used for array sizing.

**Step 2: Rebuild gen_code, run gen_code, verify Rust compiles**

```bash
cd cmake-build && cmake .. -DCMAKE_BUILD_TYPE=Release && make gen_code -j4
cd ../bin && ../cmake-build/bin/gen_code
cd ../rust && cargo check
```

**Step 3: Run tests to verify no regressions**

```bash
cd ../rust && cargo test
```

Expected: all 16 tests pass.

**Step 4: Commit**

```bash
git add src/ta_abstract/templates/ta_func_mod.rs.template rust/src/ta_func/mod.rs
git commit -m "Add Compatibility and FuncUnstId enums to Rust template"
```

---

### Task 2: Make Core stateful with fields and constructor

**Files:**
- Modify: `src/ta_abstract/templates/ta_func_mod.rs.template`

**Step 1: Update Core struct with fields, constructor, and accessor methods**

Replace the existing `pub struct Core {}` and its doc comment with:

```rust
/// Core struct providing access to all TA-Lib technical analysis functions.
///
/// Create an instance with [`Core::new()`] and call functions as methods.
/// Unstable period and compatibility mode can be configured per-instance.
///
/// # Example
///
/// ```
/// use ta_lib::ta_func::{Core, RetCode};
///
/// let core = Core::new();
/// let lookback = core.sma_lookback(30);
/// assert_eq!(lookback, 29);
/// ```
pub struct Core {
    /// Unstable period for each function identified by [`FuncUnstId`].
    pub unstable_period: [i32; FuncUnstId::FuncUnstAll as usize],
    /// Compatibility mode (default: [`Compatibility::Default`]).
    pub compatibility: Compatibility,
}

impl Core {
    /// Create a new Core instance with default settings.
    ///
    /// All unstable periods are initialized to 0 and compatibility
    /// mode is set to [`Compatibility::Default`].
    pub fn new() -> Self {
        Self {
            unstable_period: [0; FuncUnstId::FuncUnstAll as usize],
            compatibility: Compatibility::Default,
        }
    }

    /// Set the unstable period for a specific function.
    pub fn set_unstable_period(&mut self, id: FuncUnstId, period: i32) {
        self.unstable_period[id as usize] = period;
    }

    /// Get the unstable period for a specific function.
    pub fn get_unstable_period(&self, id: FuncUnstId) -> i32 {
        self.unstable_period[id as usize]
    }

    /// Set the compatibility mode.
    pub fn set_compatibility(&mut self, compat: Compatibility) {
        self.compatibility = compat;
    }

    /// Get the current compatibility mode.
    pub fn get_compatibility(&self) -> Compatibility {
        self.compatibility
    }
}
```

**Step 2: Rebuild gen_code, run gen_code, cargo check**

Note: This will cause compilation errors because existing functions are still static but Core now has fields. That's expected — Task 3 fixes the signatures.

**Step 3: Commit (even if cargo check fails — this is an intermediate step)**

```bash
git add src/ta_abstract/templates/ta_func_mod.rs.template rust/src/ta_func/mod.rs
git commit -m "Make Core stateful with unstable_period and compatibility fields"
```

---

### Task 3: Add &self to all Rust function signatures

**Files:**
- Modify: `src/tools/gen_code/gen_rust.c:340-392` (lookback signature)
- Modify: `src/tools/gen_code/gen_rust.c:394-525` (double precision signature)
- Modify: `src/tools/gen_code/gen_rust.c:527-end` (single precision signature)

**Step 1: Add &self parameter to lookback signature**

In `printRustLookbackFunctionSignature` (gen_rust.c:350), change:
```c
sprintf(gTempBuf, "%spub fn %s_lookback(\n",
```
to:
```c
sprintf(gTempBuf, "%spub fn %s_lookback(&self,\n",
```

**Step 2: Add &self parameter to double precision signature**

In `printRustDoublePrecisionFunctionSignature` (gen_rust.c:406), change:
```c
sprintf(gTempBuf, "%spub fn %s(",
```
to:
```c
sprintf(gTempBuf, "%spub fn %s(&self, ",
```

**Step 3: Add &self parameter to single precision signature**

In `printRustSinglePrecisionFunctionSignature` (gen_rust.c:539), change:
```c
sprintf(gTempBuf, "%spub fn %s_s(",
```
to:
```c
sprintf(gTempBuf, "%spub fn %s_s(&self, ",
```

**Step 4: Handle the internal SMA function**

Check `src/ta_func/ta_SMA.c` — the internal `int_sma` / `int_sma_s` functions are hand-written Rust signatures in `#elif defined(_RUST)` blocks. These need `&self` added too. Look for:
```c
fn int_sma(
fn int_sma_s(
```
and add `&self,` as the first parameter.

Also update the call site in the SMA outer function — `FUNCTION_CALL(INT_SMA)(...)` expands to `Self::int_sma(...)` via `TA_INT_SMA`. Since these are now `&self` methods, `Self::int_sma` needs to become `self.int_sma`. Update the defines in the Rust block of ta_defs.h:
```c
// Change from:
#define TA_INT_SMA Self::int_sma
#define TA_S_INT_SMA Self::int_sma_s
// To:
#define TA_INT_SMA self.int_sma
#define TA_S_INT_SMA self.int_sma_s
```

**Step 5: Rebuild gen_code, run gen_code, cargo check**

```bash
cd cmake-build && make gen_code -j4
cd ../bin && ../cmake-build/bin/gen_code
cd ../rust && cargo check
```

Expected: compiles (existing functions now take `&self`).

**Step 6: Verify C/Java/.NET output is unchanged**

```bash
git diff -- src/ta_func/ta_SMA.c src/ta_func/ta_MULT.c java/src/com/tictactec/ta/lib/Core.java
```

Only the `/* Generated */` Rust sections should differ.

**Step 7: Commit**

```bash
git add src/tools/gen_code/gen_rust.c include/ta_defs.h src/ta_func/ta_SMA.c rust/
git commit -m "Add &self to all Rust function signatures — methods instead of static functions"
```

---

### Task 4: Update existing MULT/SMA tests and doctests for &self API

**Files:**
- Modify: `rust/tests/mult_test.rs`
- Modify: `rust/tests/sma_test.rs`

**Step 1: Update all tests**

Change every `Core::function_name(...)` call to `core.function_name(...)`. At the top of each test, add `let core = Core::new();`. Import `Core` (already imported).

Pattern to find and replace in each test:
```rust
// Before:
let result = Core::mult(...);
// After:
let core = Core::new();
let result = core.mult(...);
```

For lookback calls:
```rust
// Before:
let lookback = Core::sma_lookback(30);
// After:
let core = Core::new();
let lookback = core.sma_lookback(30);
```

**Step 2: Run tests**

```bash
cd rust && cargo test
```

Expected: all 16 tests pass.

**Step 3: Commit**

```bash
git add rust/tests/mult_test.rs rust/tests/sma_test.rs
git commit -m "Update MULT/SMA tests for &self method API"
```

---

### Task 5: Fix TA_GLOBALS macros — separate Rust from Java

**Files:**
- Modify: `src/ta_common/ta_memory.h:105-114`

**Step 1: Add separate Rust branch for TA_GLOBALS**

Change:
```c
#elif defined( _JAVA ) || defined( _RUST)
   #define TA_GLOBALS_UNSTABLE_PERIOD(x,y) (this.unstablePeriod[FuncUnstId.y.ordinal()])
   #define TA_GLOBALS_COMPATIBILITY        (this.compatibility)
```

To:
```c
#elif defined( _RUST )
   #define TA_GLOBALS_UNSTABLE_PERIOD(x,y) (self.unstable_period[FuncUnstId::y as usize])
   #define TA_GLOBALS_COMPATIBILITY        (self.compatibility)
#elif defined( _JAVA )
   #define TA_GLOBALS_UNSTABLE_PERIOD(x,y) (this.unstablePeriod[FuncUnstId.y.ordinal()])
   #define TA_GLOBALS_COMPATIBILITY        (this.compatibility)
```

Note: Rust must come BEFORE Java in the `#if` chain.

**Step 2: Verify Java output is unchanged**

```bash
cd cmake-build && make gen_code -j4
cd ../bin && ../cmake-build/bin/gen_code
git diff -- java/src/com/tictactec/ta/lib/Core.java
```

Expected: no Java changes.

**Step 3: Commit**

```bash
git add src/ta_common/ta_memory.h
git commit -m "Separate Rust from Java in TA_GLOBALS macros — use self instead of this"
```

---

### Task 6: Add LOOKBACK_CALL for Rust

**Files:**
- Modify: `include/ta_defs.h:292-296`

**Step 1: Define LOOKBACK_CALL for Rust**

The current block is:
```c
#if !defined(_RUST)
#define FUNCTION_CALL(x)        TA_PREFIX(x)
#define FUNCTION_CALL_DOUBLE(x) TA_##x
#define LOOKBACK_CALL(x)        TA_##x##_Lookback
#endif
```

Change to:
```c
#if !defined(_RUST)
#define FUNCTION_CALL(x)        TA_PREFIX(x)
#define FUNCTION_CALL_DOUBLE(x) TA_##x
#define LOOKBACK_CALL(x)        TA_##x##_Lookback
#else
#define LOOKBACK_CALL(x)        TA_##x##_Lookback
#endif
```

This makes LOOKBACK_CALL(RSI) expand to `TA_RSI_Lookback` in Rust. We then need per-function defines to map to the Rust method name. For RSI, add in the Rust macro block (around line 260):

```c
#define TA_RSI_Lookback self.rsi_lookback
```

This two-level expansion gives: `LOOKBACK_CALL(RSI)(optInTimePeriod)` → `TA_RSI_Lookback(optInTimePeriod)` → `self.rsi_lookback(optInTimePeriod)`.

Note: As more functions are converted, add one `#define TA_XXX_Lookback self.xxx_lookback` line per function. Consider automating this in gen_code later if it becomes tedious.

**Step 2: Commit**

```bash
git add include/ta_defs.h
git commit -m "Add LOOKBACK_CALL macro for Rust — two-level expansion via TA_RSI_Lookback"
```

---

### Task 7: Add ARRAY_MEMMOVE / ARRAY_MEMMOVEMIX Rust definitions

**Files:**
- Modify: `src/ta_common/ta_memory.h:48-55` (the `_JAVA || _RUST` block)
- Modify: `src/ta_common/ta_memory.h:87-95` (ARRAY_MEMMOVEMIX macros)

**Step 1: Separate Rust from Java in ARRAY_VTYPE macros**

The current block at line 48:
```c
#elif defined( _JAVA ) || defined( _RUST )
   #define ARRAY_VTYPE_REF(type,name)             type []name
   ...
   #define ARRAY_VTYPE_MEMMOVE(type,dest,destIdx,src,srcIdx,size) System.arraycopy(src,srcIdx,dest,destIdx,size)
   ...
```

Add a separate `_RUST` block before `_JAVA`:
```c
#elif defined( _RUST )
   #define ARRAY_VTYPE_REF(type,name)             /* not used in Rust */
   #define ARRAY_VTYPE_LOCAL(type,name,size)       /* not used in Rust */
   #define ARRAY_VTYPE_ALLOC(type,name,size)       /* not used in Rust */
   #define ARRAY_VTYPE_COPY(type,dest,src,size)    dest[0..(size)].copy_from_slice(&src[0..(size)])
   #define ARRAY_VTYPE_MEMMOVE(type,dest,destIdx,src,srcIdx,size) { let _n = (size) as usize; let _di = (destIdx) as usize; let _si = (srcIdx) as usize; dest[_di.._di+_n].copy_from_slice(&src[_si.._si+_n]); }
   #define ARRAY_VTYPE_FREE(type,name)
   #define ARRAY_VTYPE_FREE_COND(type,cond,name)
#elif defined( _JAVA )
```

**Step 2: Add Rust ARRAY_MEMMOVEMIX definitions**

The current ARRAY_MEMMOVEMIX (line 87-95) uses C-style for loops. Add Rust-specific versions. Since `ARRAY_MEMMOVEMIX` is NOT language-branched (it's a single `#define`), we need to wrap it:

```c
#if defined(_RUST)
#define ARRAY_MEMMOVEMIX_VAR /* no-op for Rust */
#define ARRAY_MEMMOVEMIX(dest,destIdx,src,srcIdx,size) { let _n = (size) as usize; let _di = (destIdx) as usize; let _si = (srcIdx) as usize; for _k in 0.._n { dest[_di+_k] = src[_si+_k] as f64; } }
#else
#define ARRAY_MEMMOVEMIX_VAR int mmmixi, mmmixdestIdx, mmmixsrcIdx
#define ARRAY_MEMMOVEMIX(dest,destIdx,src,srcIdx,size) { \
            for( mmmixi=0, mmmixdestIdx=destIdx, mmmixsrcIdx=srcIdx; \
                mmmixi < size; \
                mmmixi++, mmmixdestIdx++, mmmixsrcIdx++ ) \
              { \
                  dest[mmmixdestIdx] = src[mmmixsrcIdx]; \
              } \
            }
#endif
```

**Step 3: Verify C/Java output is unchanged**

```bash
cd cmake-build && make gen_code -j4
cd ../bin && ../cmake-build/bin/gen_code
git diff -- src/ta_func/ java/
```

**Step 4: Commit**

```bash
git add src/ta_common/ta_memory.h
git commit -m "Add Rust ARRAY_MEMMOVE and ARRAY_MEMMOVEMIX definitions"
```

---

### Task 8: Phase A verification — rebuild everything and confirm zero regressions

**Step 1: Full rebuild and test**

```bash
cd cmake-build && cmake .. -DCMAKE_BUILD_TYPE=Release && make gen_code -j4
cd ../bin && ../cmake-build/bin/gen_code
cd ../rust && cargo check && cargo test
```

Expected: all 16 tests pass, zero warnings.

**Step 2: Verify no C/Java/.NET regressions**

```bash
git diff -- src/ta_func/ java/ dotnet/
```

Understand every diff. Cosmetic changes from macro expansion are OK.

---

## Phase B: RSI Conversion

### Task 9: Convert ta_RSI.c logic section variables to DECLARE macros

**Files:**
- Modify: `src/ta_func/ta_RSI.c` (logic between GENCODE 3-5, approximately lines 224-487)

**Step 1: Replace raw C variable declarations**

Change the local variable declarations at the top of the function body:
```c
/* From: */
   int outIdx;
   int today, lookbackTotal, unstablePeriod, i;
   double prevGain, prevLoss, prevValue, savePrevValue;
   double tempValue1, tempValue2;
```

To (using established DECLARE macros):
```c
/* To: */
   DECLARE_INDEX_VAR(outIdx)
   DECLARE_INDEX_VAR(today)
   DECLARE_INDEX_VAR(lookbackTotal)
   DECLARE_INT_VAR(unstablePeriod)
   DECLARE_INT_VAR(i)
   DECLARE_DOUBLE_VAR(prevGain)
   DECLARE_DOUBLE_VAR(prevLoss)
   DECLARE_DOUBLE_VAR(prevValue)
   DECLARE_DOUBLE_VAR(savePrevValue)
   DECLARE_DOUBLE_VAR(tempValue1)
   DECLARE_DOUBLE_VAR(tempValue2)
```

Notes on type choices (following SMA's pattern):
- `outIdx`, `today`, `lookbackTotal` are `DECLARE_INDEX_VAR` (usize) because they index into arrays or compare with `startIdx`/`endIdx` (usize)
- `unstablePeriod` is `DECLARE_INT_VAR` (i32) because it comes from `TA_GLOBALS_UNSTABLE_PERIOD`
- `i` is `DECLARE_INT_VAR` (i32) because it counts down from `optInTimePeriod` (i32)

**Step 2: Add type casts at int/usize boundaries**

Key conversions needed throughout the logic:
- `lookbackTotal = LOOKBACK_CALL(RSI)(optInTimePeriod);` → `lookbackTotal = CAST_TO_INDEX(LOOKBACK_CALL(RSI)(optInTimePeriod));`
- `today = startIdx-lookbackTotal;` — both usize, works as-is after the change above
- `today -= optInTimePeriod;` → `today = today - CAST_TO_INDEX(optInTimePeriod);`
- `i = (endIdx-startIdx)+1;` → `i = CAST_TO_I32((endIdx-startIdx)+1);` (for the period==1 case)
- `VALUE_HANDLE_DEREF(outNBElement) = i;` → `VALUE_HANDLE_DEREF(outNBElement) = CAST_TO_INDEX(i);`
- Divisions by `optInTimePeriod`: `prevLoss/optInTimePeriod` → `prevLoss/CAST_TO_F64(optInTimePeriod)`
- Multiplications: `prevLoss *= (optInTimePeriod-1)` → `prevLoss *= CAST_TO_F64(optInTimePeriod-1)`
- `100*(tempValue2/tempValue1)` — both f64, works as-is
- ARRAY_MEMMOVE size param: `ARRAY_MEMMOVE(outReal, 0, inReal, startIdx, i)` — `i` is i32, the Rust macro casts to usize internally. But `startIdx` is already usize. Verify this compiles.

**Step 3: Convert post-increment syntax**

Replace all `today++` and `outIdx++` with `today = today + 1` and `outIdx = outIdx + 1`.

Watch out for `inReal[today++]` — this reads then increments. In Rust:
```c
/* From: */ tempValue1 = inReal[today++];
/* To:   */ tempValue1 = inReal[today]; today = today + 1;
```

Same for `outReal[outIdx++] = value;`:
```c
/* From: */ outReal[outIdx++] = 100.0*(prevGain/tempValue1);
/* To:   */ outReal[outIdx] = 100.0*(prevGain/tempValue1); outIdx = outIdx + 1;
```

**Step 4: Convert countdown loops**

```c
/* From: */ for( i=optInTimePeriod; i > 0; i-- )
/* To:   */ FOR_COUNTDOWN(optInTimePeriod, i)
...
/* From: */ (closing brace)
/* To:   */ FOR_COUNTDOWN_END
```

There are multiple countdown loops in RSI — convert all of them.

**Step 5: Don't touch GENCODE sections 1-4 or the generated section 5** — only modify the hand-written logic between GENCODE 3 and GENCODE 5.

**Step 6: Verify C output is unchanged** (the macros should expand identically for C)

```bash
cd cmake-build && make gen_code -j4
cd ../bin && ../cmake-build/bin/gen_code
git diff -- src/ta_func/ta_RSI.c
```

The only diffs should be in the `/* Generated */` section 5 (which mirrors the logic).

**Step 7: Commit**

```bash
git add src/ta_func/ta_RSI.c
git commit -m "Convert ta_RSI.c logic section to cross-language macros"
```

---

### Task 10: Add RSI to RUST_SUPPORTED_FUNCS and generate

**Files:**
- Modify: `src/tools/gen_code/gen_code.c:112`

**Step 1: Add RSI to the supported functions list**

```c
// From:
#define RUST_SUPPORTED_FUNCS "SMA,MULT"
// To:
#define RUST_SUPPORTED_FUNCS "SMA,MULT,RSI"
```

**Step 2: Rebuild and generate**

```bash
cd cmake-build && make gen_code -j4
cd ../bin && ../cmake-build/bin/gen_code
cd ../rust && cargo check
```

**Step 3: Fix any compilation errors**

The generated `rust/src/ta_func/rsi.rs` will likely have issues. Common problems:
- Type mismatches at int/usize boundaries → add CAST macros in ta_RSI.c
- Missing macro definitions → check ta_defs.h
- `TA_IS_ZERO` expanding with C negation `!` → verify Rust accepts `!` for bool negation (it should — `!` is logical NOT for booleans in Rust)

Iterate: fix source → rebuild gen_code → run gen_code → cargo check until it compiles.

**Step 4: Run existing tests**

```bash
cd ../rust && cargo test
```

Expected: all 16 existing tests pass (RSI has no tests yet, but shouldn't break anything).

**Step 5: Commit**

```bash
git add src/tools/gen_code/gen_code.c rust/src/ta_func/ include/ta_defs.h src/ta_func/ta_RSI.c
git commit -m "Add RSI to RUST_SUPPORTED_FUNCS — compiles in Rust"
```

---

### Task 11: Write RSI tests (TDD)

**Files:**
- Create: `rust/tests/rsi_test.rs`

**Step 1: Write tests covering these scenarios**

Use Java output as reference for expected values. Key test cases:

1. **Basic RSI calculation** — known input prices, verify output matches Java
2. **Single precision (f32 input)** — same test with `rsi_s`
3. **Lookback** — `core.rsi_lookback(14)` should return 14 (with default unstable period 0 and default compatibility)
4. **Lookback with unstable period** — set unstable period, verify lookback increases
5. **Lookback with Metastock compat** — set compatibility to Metastock, verify lookback decreases by 1
6. **Period 1 special case** — RSI with period=1 copies input to output
7. **Bad params** — period 0, period 1 (minimum is 2), period > 100000
8. **Default period** — pass `i32::MIN` as period, should use default 14
9. **Out of range end index** — endIdx < startIdx
10. **Partial range** — startIdx > 0
11. **Unstable period behavior** — set unstable period, verify initial outputs are skipped

**Step 2: Run to verify they fail**

```bash
cd rust && cargo test rsi
```

Expected: tests that call RSI should pass if Task 10 compiled successfully. If not, iterate on Task 10.

**Step 3: Commit tests**

```bash
git add rust/tests/rsi_test.rs
git commit -m "Add RSI test suite — basic, single precision, lookback, error conditions, unstable period"
```

---

### Task 12: Write rich RSI doctest example

**Files:**
- Create: `src/ta_abstract/rust_examples/rsi.txt`

**Step 1: Write a clear example showing RSI usage**

Follow the pattern from `src/ta_abstract/rust_examples/sma.txt`. The example should:
- Create a Core instance
- Call `core.rsi()` with realistic price data
- Assert on `out_beg_idx`, `out_nb_element`, and output values
- Show the unstable period concept if practical

Note: `//` comments will be stripped by mcpp. Use assertions to document expected behavior.

**Step 2: Rebuild to regenerate docs**

```bash
cd cmake-build && make gen_code -j4
cd ../bin && ../cmake-build/bin/gen_code
cd ../rust && cargo test --doc
```

**Step 3: Commit**

```bash
git add src/ta_abstract/rust_examples/rsi.txt rust/src/ta_func/rsi.rs
git commit -m "Add rich hand-written doctest example for RSI"
```

---

### Task 13: Update tracking and changelog

**Files:**
- Modify: `CLAUDE.md` (Current Status, Macros Still Needed sections)
- Modify: `RUST_CHANGELOG.md`
- Modify: `src/tools/gen_code/gen_code.c:112` (if not already updated)

**Step 1: Update CLAUDE.md**

- Add RSI to Current Status: `**RSI** - Complete, N tests pass + 1 doctest`
- Update `RUST_SUPPORTED_FUNCS` line to `"SMA,MULT,RSI"`
- Remove RSI-related items from "Macros Still Needed" (LOOKBACK_CALL, TA_IS_ZERO done)
- Update "Next Functions to Implement" — remove RSI, add next target

**Step 2: Update RUST_CHANGELOG.md**

Add entries under the existing 2026-03-01 heading (or create new date entry). Follow the established format with per-bullet commit links and release diff line.

**Step 3: Commit**

```bash
git add CLAUDE.md RUST_CHANGELOG.md
git commit -m "Update tracking for RSI conversion — changelog, CLAUDE.md status"
```

---

## Verification Checklist

After all tasks:
- [ ] All existing MULT tests pass (6 tests)
- [ ] All existing SMA tests pass (7 tests)
- [ ] All doctests pass (3+ existing + RSI doctest)
- [ ] All RSI tests pass
- [ ] `cargo check` — zero warnings
- [ ] C output unchanged (or only cosmetic macro expansion diffs)
- [ ] Java output unchanged
- [ ] .NET output unchanged
