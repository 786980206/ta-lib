---
title: KAMA
description: "Kaufman Adaptive Moving Average: an EMA whose smoothing factor adapts each bar to an efficiency ratio (directional move vs. total volatility). Reacts fast in trends and smooths in ranging markets. Flat KAMA = non-trending/ranging market. KAMA tracking price closely = efficient trend."
---

# KAMA

## Summary

Kaufman Adaptive Moving Average: an EMA whose smoothing factor adapts each bar to an efficiency ratio (directional move vs. total volatility). Reacts fast in trends and smooths in ranging markets. Flat KAMA = non-trending/ranging market. KAMA tracking price closely = efficient trend.

## Formula

ER = |price[t] - price[t-period]| / sum(|price[i]-price[i-1]|, last period bars)
SC = (ER*(2/3 - 2/31) + 2/31)^2
KAMA[t] = KAMA[t-1] + SC*(price[t] - KAMA[t-1])

## Inputs

- `inReal` — Source price series

## Outputs

- `outReal` — Adaptive moving average line

## Parameters

- `optInTimePeriod` — Lookback window for the efficiency ratio

## Implementation

TA-Lib Definition: [`kama.c`](https://github.com/TA-Lib/ta-lib/blob/main/ta_codegen/input/kama/kama.c) · [`kama.yaml`](https://github.com/TA-Lib/ta-lib/blob/main/ta_codegen/input/kama/kama.yaml)

| Native | File |
|--------|------|
| C | [`ta_KAMA.c`](https://github.com/TA-Lib/ta-lib/blob/main/src/ta_func/ta_KAMA.c) |
| Rust | [`kama.rs`](https://github.com/TA-Lib/ta-lib/blob/main/ta_codegen/output/rust/src/ta_func/kama.rs) |
| Java | [`Core.java`](https://github.com/TA-Lib/ta-lib/blob/main/java/src/com/tictactec/ta/lib/Core.java) |

TA-Lib is also available for Python, R and more using a [wrapper](https://ta-lib.org/wrappers/).

## Aliases

Kaufman Adaptive Moving Average, Kaufman's Adaptive Moving Average

## See Also

[MAMA](mama.md) · [EMA](ema.md) · [MA](ma.md)
