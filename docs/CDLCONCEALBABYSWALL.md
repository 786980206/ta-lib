# CDLCONCEALBABYSWALL - Concealing Baby Swallow

## Overview
The Concealing Baby Swallow (CDLCONCEALBABYSWALL) is a four-candle bearish reversal pattern that appears at the top of an uptrend. It consists of four bearish candles with specific characteristics.

## Category
Pattern Recognition

## Calculation
The CDLCONCEALBABYSWALL function identifies concealing baby swallow patterns:

### Concealing Baby Swallow Criteria
- First candle: Large bearish candle
- Second candle: Bearish candle that gaps down
- Third candle: Bearish candle with long lower shadow
- Fourth candle: Bearish candle that engulfs the third candle
- Pattern appears after uptrend

## Parameters
- **Input**: OHLC data (Open, High, Low, Close)
- **Output**: Pattern recognition array (-100 for pattern, 0 for no pattern)

## What It Means
The Concealing Baby Swallow indicates:
- **Bearish Reversal**: Strong downward reversal after uptrend
- **Top Formation**: Often marks market tops
- **Momentum Shift**: Clear shift from bullish to bearish momentum
- **High Reliability**: Strong reversal signal

## How to Use
1. **Reversal Signal**: Enter short positions after pattern completion
2. **Resistance Levels**: Most powerful at key resistance levels
3. **Volume Confirmation**: Higher volume strengthens signal
4. **Stop Loss**: Place above pattern high

## Usage Example
\`\`\`c
#include "ta_libc.h"

int main() {
    // Calculate CDLCONCEALBABYSWALL
    TA_RetCode ret = TA_CDLCONCEALBABYSWALL(
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
            if (pattern[i] == -100) {
                // Concealing baby swallow pattern
            }
        }
    }
}
\`\`\`

## Trading Strategies
1. **Reversal Trading**: Enter short at pattern completion
2. **Trend Change**: Exit long positions
3. **Resistance Trading**: Combine with resistance analysis
4. **Position Sizing**: Increase position size given pattern reliability

## Advantages
- Highly reliable reversal pattern
- Clear visual identification
- Works in all timeframes
- Strong historical track record

## Limitations
- Relatively rare pattern
- Requires four candles to complete
- May have false signals without confirmation
- Best at significant resistance levels

## Related Functions
- `CDLEVENINGSTAR` - Evening Star
- `CDL3BLACKCROWS` - Three Black Crows
- `CDLDARKCLOUDCOVER` - Dark Cloud Cover
- `CDLENGULFING` - Engulfing Pattern

## References
- Nison, S. (1991). "Japanese Candlestick Charting Techniques"
- TA-Lib Documentation: https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib: https://deepwiki.com/TA-Lib/ta-lib
