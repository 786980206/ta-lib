# Rust Performance Optimization Plan

> **For Claude:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Close the ~0.7x Rust-vs-C performance gap by replacing bounds-checked array access with iterator-based patterns via new macros in `ta_defs.h`.

**Architecture:** Add new loop macros that expand to idiomatic Rust iterators (zero-cost bounds elision) while expanding to equivalent C code. The key insight is that all "independent" loop indices are actually `base + k` where `k` is iteration count.

**Tech Stack:** C macros (`ta_defs.h`), gen_code pipeline, cross-language benchmark harness

---

## Background: Performance Investigation

### Benchmark Results (100k points, `python3 tests/cross-language/compare.py`)

| Function | C | Rust | Ratio |
|----------|------|--------|-------|
| SMA p=50 | ~40us | ~60us | ~0.7x |
| SMA p=200 | ~40us | ~55us | ~0.7x |
| RSI p=14 | ~55us | ~75us | ~0.7x |
| MULT | ~25us | ~35us | ~0.7x |

All correctness tests pass with exact output match. The gap is purely runtime.

### Root Cause Analysis

**1. Bounds checking on every array access (3+ per inner loop iteration)**

Rust inserts a bounds check on every `arr[i]` access. In hot loops with 100k iterations, this adds up. C has no bounds checks.

**2. `while` loops with manual increment prevent LLVM optimization**

The generated Rust code uses `while` loops with manual `i = i + 1` increments (transliterated from C). LLVM can optimize `for i in 0..n` ranges much better — it knows the bounds at loop entry and can elide checks.

**3. Separate `outIdx` counter prevents compiler from proving array bounds**

The output index (`outIdx`) is a separate variable incremented independently from the loop variable. LLVM cannot connect `outIdx` to the loop bounds, so it can't prove `outReal[outIdx]` is safe. This forces a bounds check on every write.

**4. Transliterated C code, not idiomatic Rust**

The generated code is a direct C-to-Rust transliteration. Idiomatic Rust would use iterators, `enumerate()`, and range-based loops.

### Assertion Prototype Results (reverted)

Added `assert!(outReal.len() >= expected_count)` before hot loops. Results:
- **RSI**: Marginal improvement (~0.7x → ~0.8x) — helps input array bounds only
- **SMA/MULT**: No improvement — LLVM still can't connect `outIdx` to loop bounds

**Conclusion:** Assertions alone don't close the gap. The `outIdx` problem requires restructuring the loops so all indices derive from a single loop variable.

---

## Proposed Solution: Three New Loop Macro Patterns

The key insight: in every loop across MULT, SMA, and RSI, all "independent" indices (`i`, `trailingIdx`, `outIdx`) are actually `base + k` where `k` is the iteration count. Converting to `for k in 0..N` with computed indices lets LLVM prove everything is in-bounds.

### Pattern 1 — Fix FOR_EACH_OUTPUT (MULT)

**Current Rust expansion** (in `ta_defs.h`):
```c
// Expands to:
outIdx = 0;
for i in (startIdx as usize)..=(endIdx as usize) {
    outReal[outIdx] = (inReal0[i] * inReal1[i]) as f64;
    outIdx += 1;
}
```

**Problem:** `outIdx` is a separate counter. LLVM can't connect it to the `for i` range.

**Fix — use `enumerate()`:**
```c
// New Rust expansion:
for (outIdx, i) in (startIdx..=endIdx).enumerate() {
    outReal[outIdx] = (inReal0[i] * inReal1[i]) as f64;
}
```

**C expansion stays the same.** This is a change only to the `#if defined(_RUST)` branch of the `FOR_EACH_OUTPUT` macro in `ta_defs.h`.

### Pattern 2 — New SLIDING_WINDOW_LOOP (SMA)

**Current generated Rust:**
```rust
while i <= endIdx {
    periodTotal += (inReal[i]) as f64;
    i = i + 1;
    tempReal = periodTotal;
    periodTotal -= (inReal[trailingIdx]) as f64;
    trailingIdx = trailingIdx + 1;
    outReal[outIdx] = tempReal / ((optInTimePeriod) as f64);
    outIdx = outIdx + 1;
}
```

Three separate indices: `i` (starts at `startIdx`), `trailingIdx` (starts at `startIdx - lookbackTotal`), `outIdx` (starts at 0).

**All are `base + k`:**
- `i = startIdx + k`
- `trailingIdx = (startIdx - lookbackTotal) + k`
- `outIdx = k`

**New macro (C version — identical behavior):**
```c
SLIDING_WINDOW_LOOP(i, trailingIdx, outIdx, startIdx, endIdx, lookbackTotal)
    // body unchanged
SLIDING_WINDOW_LOOP_END
```

**C expansion:**
```c
// Same while loop as today
```

**Rust expansion:**
```rust
{
    let _n = endIdx - startIdx + 1;
    let _trail_base = startIdx - lookbackTotal;
    for _k in 0.._n {
        let i = startIdx + _k;
        let trailingIdx = _trail_base + _k;
        let outIdx = _k;
        // body
    }
}
```

LLVM sees `_k < _n`, knows `i`, `trailingIdx`, `outIdx` are all bounded, elides all bounds checks.

### Pattern 3 — New ACCUMULATE_LOOP (RSI)

**Current generated Rust (RSI phase 2, simplified):**
```rust
while today <= endIdx {
    // ... use inReal[today], inReal[today-1]
    outReal[outIdx] = ...;
    today = today + 1;
    outIdx = outIdx + 1;
}
```

Two indices: `today` (starts at some computed value), `outIdx` (starts at some value).

**Both are `base + k`:**
- `today = today_start + k`
- `outIdx = outIdx_start + k`

**New macro:**
```c
ACCUMULATE_LOOP(today, outIdx, todayStart, outIdxStart, endIdx)
    // body unchanged
ACCUMULATE_LOOP_END
```

**C expansion:** Same while loop as today.

**Rust expansion:**
```rust
{
    let _n = endIdx - todayStart + 1;
    for _k in 0.._n {
        let today = todayStart + _k;
        let outIdx = outIdxStart + _k;
        // body
    }
}
```

---

## Implementation Steps (when ready to pick up)

### Step 1: Prototype Pattern 1 (FOR_EACH_OUTPUT fix)

1. Modify `FOR_EACH_OUTPUT` macro in `ta_defs.h` — Rust branch only
2. Rebuild gen_code, regenerate MULT
3. `cargo check && cargo test` — verify correctness
4. Run `python3 tests/cross-language/compare.py` — measure speedup
5. Verify C/Java/.NET output unchanged via `git diff`

### Step 2: Prototype Pattern 2 (SLIDING_WINDOW_LOOP)

1. Add new `SLIDING_WINDOW_LOOP` / `SLIDING_WINDOW_LOOP_END` macros to `ta_defs.h`
2. Modify `ta_SMA.c` to use the new macro (replace while loop in int_sma)
3. Rebuild gen_code, regenerate SMA
4. `cargo check && cargo test` — verify correctness
5. Run cross-language harness — measure speedup
6. Verify C/Java/.NET output unchanged

### Step 3: Prototype Pattern 3 (ACCUMULATE_LOOP)

1. Add new `ACCUMULATE_LOOP` / `ACCUMULATE_LOOP_END` macros to `ta_defs.h`
2. Modify `ta_RSI.c` to use the new macro (replace while loops in int_rsi)
3. Rebuild gen_code, regenerate RSI
4. `cargo check && cargo test` — verify correctness
5. Run cross-language harness — measure speedup
6. Verify C/Java/.NET output unchanged

### Step 4: Measure and document

1. Run full benchmark suite, record before/after numbers
2. Update this doc with final results
3. Decide if patterns generalize to other indicators (EMA, WMA, etc.)

---

## Risk Assessment

- **Low risk**: Pattern 1 (FOR_EACH_OUTPUT) — only changes Rust macro branch, C unchanged
- **Medium risk**: Patterns 2-3 — require modifying source `.c` files. Must verify all languages still produce correct output. Use `git diff` on generated C/Java/.NET files.
- **No correctness risk**: All patterns produce mathematically identical results. The cross-language harness validates this.

## How to Run the Benchmark

```bash
python3 tests/cross-language/compare.py
```

This builds both C and Rust harnesses, runs them, compares outputs for exact match, and reports timing.
