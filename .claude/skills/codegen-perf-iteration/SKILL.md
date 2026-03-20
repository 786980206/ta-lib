---
name: codegen-perf-iteration
description: Autonomous codegen quality and performance loop. Use when optimizing ta_codegen C output, investigating performance regressions, or iterating toward parity with the C reference library. Triggers on "perf iteration", "performance loop", "benchmark loop", "codegen performance", or "optimize codegen".
---

# Codegen Performance Iteration

Autonomously evolve ta-lib's codegen output toward performance parity with the C reference library through a generate, build, test, benchmark, analyze, fix loop.

## The Core Loop

```
GENERATE → BUILD → TEST → BENCHMARK → ANALYZE → PLAN → FIX → TEST → BENCHMARK → COMMIT/REVERT → repeat
```

### GENERATE
```bash
cd tools/ta_codegen
cargo run --release -- generate --backend=c
cargo run --release -- generate-servers --backend=c
```
If the codegen panics, fix the parser/backend issue first. Don't iterate on broken generation.

### BUILD
```bash
cargo run --release -- build --backend=c
```
If compilation fails, examine the error. Common issues:
- Unhandled operators in generated C (`^`, `|`)
- `f64::MAX` printed as massive integer literal (use scientific notation or skip unbounded ranges)
- Type mismatches from validation code
Fix in `backends/c.rs` and regenerate.

### TEST (correctness gate)
```bash
cd bin && ./ta_regtest --codegen --language=c
```
**Must be 161/161 pass.** If ANY function fails, stop and fix before benchmarking. Common failures:
- Validation code rejecting valid params (check range bounds, default values)
- Codegen producing wrong logic (check extracted .c source vs reference)

### BENCHMARK
Run individual problem indicators first (ground truth), then the full suite:
```bash
# Isolated (trustworthy — no icache noise)
cd bin && ./ta_bench --language=cref,c --function=NAME --points=100000 --iters=500

# Full suite (noisy — use for overview, not verdicts)
cd bin && ./ta_bench --language=cref,c --points=100000 --iters=200
```
The thermal canary (SMA) runs between each indicator to normalize CPU state. Parse output:
```python
import re
text = re.sub(r'\033\[[0-9;]*m', '', raw_output)
for line in text.split('\n'):
    m = re.match(r'(\w+)\s+(\d+)\s+(\d+)', line.strip())
    if m:
        name, ref, cg = m.group(1), int(m.group(2)), int(m.group(3))
        ratio = cg / ref if ref > 0 else 0
```

### ANALYZE
Categorize results:
- **Broken** (>2.0x slower): Something fundamentally wrong
- **Slow** (1.10x-2.0x): Investigate assembly, compare with reference
- **Parity** (0.90x-1.10x): Acceptable
- **Faster** (<0.90x): Verify correctness — could indicate skipped work

For each slow indicator:
1. **Confirm in isolation** with 500 iters — the full-run has ~10-20% noise from icache pressure
2. **Compare assembly**: `cc -O3 -DNDEBUG -S` both codegen and reference source
3. **Diff the source**: normalize whitespace, strip comments, compare function bodies

### PLAN
Pick the **single highest-impact** fix. Priority:
1. Broken indicators (>2.0x) first
2. Groups sharing a root cause (e.g., all CDL patterns)
3. Individual slow indicators

Root cause categories:
- **Candle settings**: switch statements vs ternary chains — the reference's `TA_CandleRange()` macro uses nested ternary expressions that the compiler loop-unswitches into many specialized tight loops. The codegen emits switch statements that don't get unswitched as aggressively.
- **Circular buffer**: modulo `%` vs conditional reset `if(idx>=max) idx=0`
- **Validation**: missing NULL checks or param range checks that change the compiler's register allocation decisions
- **Expression style**: extra parens, split assignments — usually irrelevant but check assembly
- **Binary layout**: linker ordering, icache effects — NOT fixable in source. Verify by testing in isolation.

### FIX
Make ONE change. Fix locations in priority order:
1. `ta_func_defs/<name>/<name>.c` — extracted indicator source
2. `tools/ta_codegen/src/backends/c.rs` — C backend rendering
3. `ta_func_defs/lib/c/ta_lib_types.h` — type system, globals, macros
4. `tools/ta_codegen/src/parser/` — parser changes

After fixing, go back to GENERATE and repeat the full loop.

### COMMIT or REVERT
- Tests pass AND target indicator improved → commit with descriptive message
- Tests fail OR indicator worse → `git checkout` changed files, try different approach
- 5 consecutive cycles with no improvement → stop and report

## Quality Gates

| Gate | Criterion | How to Check |
|------|-----------|-------------|
| Correctness | 161/161 pass | `ta_regtest --codegen --language=c` |
| Core parity | RSI, SMA, EMA, MACD, STOCH within 1.05x | Isolated benchmark, 500 iters |
| CDL performance | CDL patterns at parity or faster | Isolated benchmark — currently SLOW due to switch-vs-ternary issue |
| CCI parity | Conditional reset, not modulo | Assembly: look for `subs` pattern |
| Validation | NULL checks + default/range for opt params | Grep generated output |
| No regressions | No indicator >1.10x in isolation | Compare against saved baseline |

## Autonomy Rules

1. **Never wait for human input.** Log questions to `.plans/perf-iteration-questions.md`, pick faster-to-test approach, keep going.
2. **One change per cycle.** Don't fix three things at once.
3. **Trust the assembly.** If benchmark says slow but assembly is identical, it's binary layout. Move on.
4. **Trust isolation over full-run.** Full 161-indicator run has ~10-20% noise. Isolated benchmarks are ground truth.
5. **Revert failures quickly.** Don't spend 3 cycles saving a bad idea.
6. **Log everything.** Each iteration → `.plans/perf-iteration-log.md`: what changed, why, before/after, outcome.

## Rebuilding ta_ref_serve

When cmake rebuilds libta-lib.a, the reference server needs rebuilding too:
```bash
sed '/#include "ta_[A-Z].*\.c"/d' ta_codegen_output/c/ta_codegen_serve.c > /tmp/ta_ref_serve.c
sed -i '' '/#include "ta_lib_globals.c"/a\
extern int TA_Initialize(void);\
extern int TA_RestoreCandleDefaultSettings(int settingType);
' /tmp/ta_ref_serve.c
sed -i '' 's|int main(void) {|int main(void) { TA_Initialize(); TA_RestoreCandleDefaultSettings(11);|' /tmp/ta_ref_serve.c
cc -O3 -DNDEBUG -Wno-everything -I ta_codegen_output/c -o bin/ta_ref_serve /tmp/ta_ref_serve.c cmake-build/libta-lib.a -lm
```

## Known Issues (Current Session — 2026-03-19)

### CDL Switch vs Ternary (TOP PRIORITY)
The codegen emits `switch(rangeType)` for candle range calculations. The reference uses ternary-chain macros (`TA_CandleRange`, `TA_CandleAverage`) that the compiler loop-unswitches into many specialized tight loops (441 lines for CDL2CROWS). The codegen's switch-based code compiles to a compact single-path version (157 lines) that runs 5-10x slower because the compiler doesn't unswitch it.

**Fix approach**: Change `backends/c.rs` candle settings emission to use ternary expressions matching the reference macro pattern. Specifically, `emit_c_unpacking` and the switch-statement rendering for `CandleRange`/`CandleAverage` nodes in the IR.

### MINMAX Binary Layout
Assembly is instruction-identical to reference but ~1.2x slower in the server binary. Confirmed as a linker ordering effect — not fixable in source. The parameter validation (NULL checks + INTEGER_DEFAULT) got the assembly to match, which is the best we can do.

### Benchmark Noise
Full 161-indicator runs have 10-20% variation from icache pressure when switching between functions rapidly. The thermal canary helps with CPU throttling but doesn't address icache. Always verify with isolated benchmarks before acting on full-run numbers.

## Key Files

| File | Role |
|------|------|
| `tools/ta_codegen/src/backends/c.rs` | C code generation — validation, candle settings, expressions |
| `tools/ta_codegen/src/server_gen.rs` | Server generation — dispatch, load_data, timing |
| `tools/ta_codegen/src/main.rs` | Build step — separate compilation, flags |
| `ta_func_defs/<name>/<name>.c` | Extracted indicator source — the logic itself |
| `ta_func_defs/lib/c/ta_lib_types.h` | Type system, static globals, candle settings |
| `src/tools/ta_bench/ta_bench.c` | Benchmark harness with thermal canary |
| `scripts/regtest.py` | Full pipeline: generate + build + test + benchmark |
