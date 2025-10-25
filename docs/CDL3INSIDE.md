# CDL3INSIDE - Three Inside Pattern

## Overview
The Three Inside Pattern (CDL3INSIDE) is a candlestick pattern that consists of three candles where the second candle is inside the first candle and the third candle is inside the second candle. It's a consolidation pattern that can signal trend continuation or reversal.

## Category
Pattern Recognition

## Calculation
The CDL3INSIDE function identifies three inside patterns by analyzing three consecutive candles:

### Three Inside Criteria
- First candle has a large body
- Second candle is completely inside the first candle
- Third candle is completely inside the second candle
- All three candles have decreasing body sizes
- Pattern can be bullish or bearish

## Parameters
- **Input**: OHLC data (Open, High, Low, Close)
- **Output**: Pattern recognition array (100 for bullish, -100 for bearish, 0 for no pattern)

## What It Means
The Three Inside Pattern indicates:
- **Bullish Three Inside**: Potential upward continuation or reversal
- **Bearish Three Inside**: Potential downward continuation or reversal
- **Consolidation**: Shows market consolidation
- **Confirmation**: Should be confirmed by other indicators

## How to Use
1. **Consolidation Signals**: Look for three inside patterns in consolidating markets
2. **Volume Confirmation**: Confirm with volume analysis
3. **Support/Resistance**: Use at key support/resistance levels
4. **Trend Context**: Consider the overall trend direction

## Usage Example
```c
#include "ta_libc.h"

int main() {
    // Calculate CDL3INSIDE
    TA_RetCode ret = TA_CDL3INSIDE(
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
                // Bullish three inside pattern
            } else if (pattern[i] == -100) {
                // Bearish three inside pattern
            }
        }
    }
}
```

## Trading Strategies
1. **Consolidation Trading**: Enter positions after consolidation
2. **Breakout Confirmation**: Use to confirm breakout signals
3. **Trend Continuation**: Look for pattern in trending markets
4. **Risk Management**: Use stop losses based on pattern size

## Advantages
- Shows market consolidation
- Easy to identify visually
- Works in all timeframes
- Can be combined with other indicators

## Limitations
- May give false signals in choppy markets
- Requires confirmation from other indicators
- Best used in consolidating markets
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
