# CDLBREAKAWAY - Breakaway

## Overview
The Breakaway (CDLBREAKAWAY) is a five-candle reversal pattern that can be either bullish or bearish. It shows a gap followed by three small candles in the opposite direction, then a gap in the original direction.

## Category
Pattern Recognition

## Calculation
The CDLBREAKAWAY function identifies breakaway patterns:

### Breakaway Criteria
- First candle: Large candle in one direction
- Second candle: Gaps in same direction
- Third, fourth, fifth candles: Small candles in opposite direction
- Sixth candle: Gaps back in original direction
- Shows trend reversal

## Parameters
- **Input**: OHLC data (Open, High, Low, Close)
- **Output**: Pattern recognition array (100 for bullish, -100 for bearish, 0 for no pattern)

## What It Means
The Breakaway indicates:
- **Bullish Breakaway**: Strong upward reversal after consolidation
- **Bearish Breakaway**: Strong downward reversal after consolidation
- **Trend Reversal**: Shows clear trend change
- **High Reliability**: Strong reversal signal

## How to Use
1. **Reversal Signal**: Enter opposite to previous trend
2. **Trend Change**: Look for clear trend reversal
3. **Volume Confirmation**: Higher volume strengthens signal
4. **Position Sizing**: Increase size given reliability

## Usage Example
```c
#include "ta_libc.h"

int main() {
    // Calculate CDLBREAKAWAY
    TA_RetCode ret = TA_CDLBREAKAWAY(
        0,                    // startIdx
        99,                   // endIdx
        open_prices,          // open
        high_prices,         // high
        low_prices,          // low
        close_prices,        // close
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        pattern              // outInteger
    );
    
    if (ret == TA_SUCCESS) {
        for (int i = 0; i < outNBElement; i++) {
            if (pattern[i] == 100) {
                // Bullish breakaway
            } else if (pattern[i] == -100) {
                // Bearish breakaway
            }
        }
    }
}
```

## Trading Strategies
1. **Reversal Trading**: Enter opposite to previous trend
2. **Trend Change**: Look for clear trend reversal
3. **Gap Trading**: Trade the gap reversal
4. **Position Sizing**: Increase position size given reliability

## Advantages
- Highly reliable reversal pattern
- Clear trend change signal
- Works in all timeframes
- Strong historical track record

## Limitations
- Requires six candles to complete
- Relatively rare pattern
- May have false signals without confirmation
- Best at significant levels

## Related Functions
- `CDL3WHITESOLDIERS` - Three White Soldiers
- `CDL3BLACKCROWS` - Three Black Crows
- `CDLENGULFING` - Engulfing Pattern
- `CDLMARUBOZU` - Marubozu

## References
- Nison, S. (1991). "Japanese Candlestick Charting Techniques"
- TA-Lib Documentation: https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib: https://deepwiki.com/TA-Lib/ta-lib
