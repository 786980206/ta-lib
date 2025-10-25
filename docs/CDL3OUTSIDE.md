# CDL3OUTSIDE - Three Outside Pattern

## Overview
The Three Outside Pattern (CDL3OUTSIDE) is a candlestick pattern that consists of three candles where the second candle engulfs the first candle and the third candle engulfs the second candle. It's a strong reversal pattern that can signal trend changes.

## Category
Pattern Recognition

## Calculation
The CDL3OUTSIDE function identifies three outside patterns by analyzing three consecutive candles:

### Three Outside Criteria
- First candle has a small body
- Second candle completely engulfs the first candle
- Third candle completely engulfs the second candle
- All three candles have increasing body sizes
- Pattern can be bullish or bearish

## Parameters
- **Input**: OHLC data (Open, High, Low, Close)
- **Output**: Pattern recognition array (100 for bullish, -100 for bearish, 0 for no pattern)

## What It Means
The Three Outside Pattern indicates:
- **Bullish Three Outside**: Strong upward reversal
- **Bearish Three Outside**: Strong downward reversal
- **Engulfing Strength**: Shows increasing momentum
- **Confirmation**: Should be confirmed by other indicators

## How to Use
1. **Reversal Signals**: Look for three outside patterns at trend extremes
2. **Volume Confirmation**: Confirm with volume analysis
3. **Support/Resistance**: Use at key support/resistance levels
4. **Trend Context**: Consider the overall trend direction

## Usage Example
```c
#include "ta_libc.h"

int main() {
    // Calculate CDL3OUTSIDE
    TA_RetCode ret = TA_CDL3OUTSIDE(
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
                // Bullish three outside pattern
            } else if (pattern[i] == -100) {
                // Bearish three outside pattern
            }
        }
    }
}
```

## Trading Strategies
1. **Reversal Trading**: Enter positions opposite to the previous trend
2. **Breakout Confirmation**: Use to confirm breakout signals
3. **Trend Change**: Look for pattern at trend change points
4. **Risk Management**: Use stop losses based on pattern size

## Advantages
- Shows strong reversal signals
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
