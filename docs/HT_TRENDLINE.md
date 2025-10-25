# HT_TRENDLINE - Hilbert Transform - Trendline

## Overview
The Hilbert Transform - Trendline (HT_TRENDLINE) is a cycle indicator that calculates a trendline based on the Hilbert Transform. It's part of the MESA (MESA Adaptive Moving Average) suite of indicators developed by John Ehlers.

## Category
Cycle Indicators

## Calculation
The HT_TRENDLINE function calculates a trendline that adapts to the dominant cycle period. It uses the Hilbert Transform to identify the dominant cycle and then calculates a trendline based on that cycle.

### Formula
```
Trendline = (In-Phase + Quadrature) / 2
```

Where:
- `In-Phase` is the in-phase component from HT_PHASOR
- `Quadrature` is the quadrature component from HT_PHASOR

## Parameters
- **Input**: Price data (typically close prices)
- **Output**: Trendline array

## What It Means
The HT_TRENDLINE represents an adaptive trendline that:
- **Adapts to Cycle**: Changes with the dominant cycle period
- **Smooths Price**: Provides a smoothed representation of price movement
- **Trend Direction**: Indicates the overall trend direction
- **Support/Resistance**: Can act as dynamic support or resistance

## How to Use
1. **Trend Identification**: Use the trendline to identify overall trend direction
2. **Support/Resistance**: Use as dynamic support or resistance levels
3. **Entry/Exit Signals**: Enter positions when price crosses the trendline
4. **Trend Changes**: Look for trendline slope changes

## Usage Example
```c
#include "ta_libc.h"

int main() {
    // Calculate HT_TRENDLINE
    TA_RetCode ret = TA_HT_TRENDLINE(
        0,                    // startIdx
        99,                   // endIdx
        close_prices,         // inReal
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        trendline            // outTrendline
    );
    
    if (ret == TA_SUCCESS) {
        // Use trendline array for analysis
        for (int i = 0; i < outNBElement; i++) {
            if (close_prices[i] > trendline[i]) {
                // Price above trendline - bullish
            } else if (close_prices[i] < trendline[i]) {
                // Price below trendline - bearish
            }
        }
    }
}
```

## Trading Strategies
1. **Trend Following**: Enter positions in the direction of the trendline
2. **Mean Reversion**: Trade against the trendline when price deviates significantly
3. **Breakout Trading**: Enter positions when price breaks through the trendline
4. **Trend Confirmation**: Use with other indicators for trend confirmation

## Advantages
- Adapts to changing market cycles
- Provides clear trend signals
- Works well in trending markets
- Can be combined with other Hilbert Transform indicators

## Limitations
- Requires sufficient data for accurate calculation
- May lag in fast-moving markets
- Best used in combination with other indicators
- Requires understanding of cycle analysis

## Related Functions
- `HT_DCPERIOD` - Dominant Cycle Period
- `HT_DCPHASE` - Dominant Cycle Phase
- `HT_PHASOR` - Phasor Components
- `HT_QUADRA` - Quadrature
- `HT_SINE` - Sine Wave
- `HT_TRENDMODE` - Trend Mode

## References
- Ehlers, J. F. (2001). "Rocket Science for Traders"
- Ehlers, J. F. (2004). "Cybernetic Analysis for Stocks and Futures"
- TA-Lib Documentation: https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib: https://deepwiki.com/TA-Lib/ta-lib
