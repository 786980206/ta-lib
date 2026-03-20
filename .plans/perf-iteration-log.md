# Performance Iteration Log

## Session Start: 2026-03-19 22:10 EDT

### ROOT CAUSE FOUND: Stale ta_ref_serve binary

The CDL "10x slowdown" was a measurement artifact. The ta_ref_serve binary at bin/ta_ref_serve was built at 15:42 against a version of libta-lib.a that had different CDL code. After rebuilding fresh:

**CDL patterns at parity or FASTER:**
- CDL2CROWS: 0.94x (codegen faster)
- CDLENGULFING: 1.02x (parity)
- CDL3WHITESOLDIERS: 1.16x (slight slow — investigate further)
- CDLSHORTLINE: 1.23x (slight slow — investigate further)

**Core indicators at parity:**
- RSI: 1.00x
- SMA: 1.01x
- EMA: 0.97x (codegen faster)
- MINMAX: 1.01x (FIXED from 1.25x!)

### Changes That Helped
1. Volatile cast on candle settings reads — prevents constant propagation
2. Ternary chains for numeric switch cases — matches reference macro pattern
3. Full parameter validation (NULL checks, default/range) — matches reference
4. CCI circular buffer conditional reset — replaces modulo
5. Thermal canary in ta_bench — eliminates thermal noise
6. **Rebuilding ta_ref_serve** — most critical! Stale binary was measuring different code.

### Lesson Learned
ALWAYS rebuild ta_ref_serve when cmake rebuilds libta-lib.a. The ref server is statically linked — it doesn't pick up library changes automatically.

### Remaining
- CDL3WHITESOLDIERS 1.16x and CDLSHORTLINE 1.23x — investigate if consistent
- Run full regtest.py pipeline
- Automate ta_ref_serve rebuild in regtest.py
