# Performance Iteration Log

## Session: 2026-03-19 22:10 - 23:xx EDT

### Final Results (Cycle 5 — volatile removed, fresh ref server)

**Complex CDL patterns 1.5-1.9x FASTER than reference:**
- CDLMORNINGDOJISTAR: 0.55x
- CDLHARAMI: 0.52x
- CDLEVENINGDOJISTAR: 0.56x
- CDLHARAMICROSS: 0.63x

**Simple CDL patterns at parity:**
- CDL2CROWS: 0.97x
- CDLENGULFING: 1.01x

**Core indicators at parity:**
- RSI: 1.00x
- SMA: 1.01x
- MINMAX: 1.24x (binary layout — assembly identical, not fixable in source)

**Remaining slow:**
- CDL3BLACKCROWS: 1.21x — investigate
- MINMAX: 1.24x — known, unfixable

### What Worked
1. Static globals + constant propagation = compact, fast CDL code
2. NO volatile — volatile forces memory reloads that kill complex patterns
3. Ternary chains for numeric switches (minor effect, mostly cosmetic)
4. Full parameter validation (NULL checks, INTEGER_DEFAULT, range)
5. CCI conditional reset instead of modulo
6. Fresh ta_ref_serve binary (auto-rebuilt by regtest.py)
7. Thermal canary in ta_bench

### What Didn't Work
1. Separate compilation — binary layout issues, CDL 10x slower
2. LTO with extern globals — didn't recover CDL performance
3. volatile candle reads — helped simple CDL, KILLED complex CDL
4. Ternary vs switch at source level — compiler produces identical assembly

### Key Lesson
The stale ta_ref_serve was the biggest red herring. ALWAYS rebuild when cmake runs.
The codegen produces FASTER code than the reference for complex CDL patterns
thanks to constant propagation eliminating runtime dispatch overhead.
