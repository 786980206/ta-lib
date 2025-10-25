# HT_QUADRA - Hilbert Transform - Quadrature

## Overview
The Hilbert Transform - Quadrature (HT_QUADRA) is a cycle indicator that calculates the quadrature component of the Hilbert Transform. It's part of the MESA (MESA Adaptive Moving Average) suite of indicators developed by John Ehlers.

## Category
Cycle Indicators

## Calculation
The HT_QUADRA function calculates the quadrature component of the Hilbert Transform, which represents the imaginary part of the complex phasor.

### Formula
```
Q = 0.5 * (price[1] - price[3])
```

Where:
- `price[1]` is the price one period ago
- `price[3]` is the price three periods ago

## Parameters
- **Input**: Price data (typically close prices)
- **Output**: Quadrature component array

## What It Means
The HT_QUADRA represents the quadrature (imaginary) component of the cycle:
- **Positive Values**: Indicate upward cycle momentum
- **Negative Values**: Indicate downward cycle momentum
- **Zero Crossings**: Often signal cycle turning points
- **Amplitude**: Measures the strength of the cycle

## How to Use
1. **Cycle Turning Points**: Look for zero crossings of the quadrature component
2. **Momentum Analysis**: Use the sign and magnitude to assess cycle momentum
3. **Trend Changes**: Combine with in-phase component for trend analysis
4. **Cycle Strength**: Use amplitude to filter weak cycles

## Usage Example
```c
#include "ta_libc.h"

int main() {
    // Calculate HT_QUADRA
    TA_RetCode ret = TA_HT_QUADRA(
        0,                    // startIdx
        99,                   // endIdx
        close_prices,         // inReal
        &outBegIdx,          // outBegIdx
        &outNBElement,       // outNBElement
        quadrature           // outQuadrature
    );
    
    if (ret == TA_SUCCESS) {
        // Use quadrature array for analysis
        for (int i = 0; i < outNBElement; i++) {
            if (quadrature[i] > 0) {
                // Upward cycle momentum
            } else if (quadrature[i] < 0) {
                // Downward cycle momentum
            }
        }
    }
}
```

## Trading Strategies
1. **Zero Crossing Signals**: Enter positions when quadrature crosses zero
2. **Momentum Trading**: Follow the direction of quadrature momentum
3. **Cycle Filtering**: Only trade when quadrature amplitude is significant
4. **Trend Confirmation**: Use with other indicators for trend confirmation

## Advantages
- Provides clear cycle momentum signals
- Works well in trending markets
- Can be combined with other Hilbert Transform indicators
- Offers objective cycle measurement

## Limitations
- Requires sufficient data for accurate calculation
- May be noisy in very short timeframes
- Best used in combination with other indicators
- Requires understanding of cycle analysis

## Related Functions
- `HT_DCPERIOD` - Dominant Cycle Period
- `HT_DCPHASE` - Dominant Cycle Phase
- `HT_PHASOR` - Phasor Components
- `HT_SINE` - Sine Wave
- `HT_TRENDLINE` - Trendline
- `HT_TRENDMODE` - Trend Mode

## References
- Ehlers, J. F. (2001). "Rocket Science for Traders"
- Ehlers, J. F. (2004). "Cybernetic Analysis for Stocks and Futures"
- TA-Lib Documentation: https://ta-lib.github.io/ta-lib-python/
- DeepWiki TA-Lib: https://deepwiki.com/TA-Lib/ta-lib
