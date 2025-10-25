# CDLADVANCEBLOCK - Advance Block Pattern

## Overview
The Advance Block Pattern (CDLADVANCEBLOCK) is a candlestick pattern that consists of three candles where the first two are bullish and the third is bearish. It's a bearish reversal pattern that can signal trend changes.

## Category
Pattern Recognition

## Calculation
The CDLADVANCEBLOCK function identifies advance block patterns by analyzing three consecutive candles:

### Advance Block Criteria
- First candle is bullish (close > open)
- Second candle is bullish (close > open)
- Third candle is bearish (close < open)
- Second candle has a higher close than first candle
- Third candle has a lower close than second candle
- Each candle has a smaller body than the previous

## Parameters
- **Input**: OHLC data (Open, High, Low, Close)
- **Output**: Pattern recognition array (100 for advance block, 0 for no pattern)

## What It Means
The Advance Block Pattern indicates:
- **Bearish Reversal**: Potential downward reversal after an uptrend
- **Weakening Momentum**: Shows decreasing bullish momentum
- **Resistance Test**: Often appears at key resistance levels
- **Confirmation**: Should be confirmed by other indicators

## How to Use
1. **Reversal Signals**: Look for advance block patterns at trend extremes
2. **Volume Confirmation**: Confirm with volume analysis
3. **Support/Resistance**: Use at key support/resistance levels
4. **Trend Context**: Consider the overall trend direction

## Usage Example
```c
#include "ta_libc.h"

int main() {
    // Calculate CDLADVANCEBLOCK
    TA_RetCode ret = TA_CDLADVANCEBLOCK(
        0,                    // startIdx
        99,                   // endIdx
        open_prices,          // open
        high_prices,         // high
        low_prices,          // low
        close_prices,        // close
        &outBegIdx,          // outBegIdx
        &outNBElement,      // outNBElement
        pattern              // outInteger
    );
    
    if (ret == TA_SUCCESS) {
        // Use pattern array for analysis
        for (int i = 0; i < outNBElement; i++) {
            if (pattern[i] == 100) {
                // Advance block pattern
            }
        }
    }
}
```

## Trading Strategies
1. **Reversal Trading**: Enter short positions after advance block
2. **Breakout Confirmation**: Use to confirm breakout signals
3. **Trend Change**: Look for pattern at trend change points
4. **Risk Management**: Use stop losses based on pattern size

## Advantages
- Shows potential bearish reversal
- Easy to identify visually
- Works in all timeframes
- Can be combined with other indicators

## Limitations
- May give false signals in choppy markets
- Requires confirmation from other indicators
- Best used at key support/resistance levels
- May lag in fast-moving markets

## Related Functions
- `CDLHAMMER` - Hammer Pattern
- `CDLDOJI` - Doji Pattern
- `CDLENGULFING` - Engulfing Pattern
- `CDLHARAMI` - Harami Pattern
- `CDLSPINNINGTOP` - Spinning Top Pattern

## References
- Nison, S. (1991). "Japanese Candlestick Charting Techniques"
- TA-Lib Documentation: https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib: https://deepwiki.com/TA-Lib/ta-lib
