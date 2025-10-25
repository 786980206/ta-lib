# VWMA - Volume Weighted Moving Average

## Description

The Volume Weighted Moving Average (VWMA) is a moving average that gives more weight to periods with higher volume. Unlike simple moving averages that treat all periods equally, VWMA emphasizes periods with higher trading activity, making it more responsive to significant price movements and providing better trend identification.

## Category
Overlap Studies

## Author
Traditional Technical Analysis

## Calculation

VWMA is calculated by weighting each price by its volume:

### Formula
```
VWMA = Σ(Price × Volume) / Σ(Volume)
```

Where:
- Σ = summation over the period
- Price = price for each period (typically close)
- Volume = volume for each period

### Example
For 3-period VWMA with:
- Period 1: Price = 100, Volume = 1000
- Period 2: Price = 102, Volume = 2000
- Period 3: Price = 101, Volume = 1500

```
VWMA = (100×1000 + 102×2000 + 101×1500) / (1000 + 2000 + 1500)
     = (100000 + 204000 + 151500) / 4500
     = 455500 / 4500 = 101.22
```

## Parameters

- **optInTimePeriod** (default: 30): Period for calculation
  - Valid range: 2 to 100000
  - Common values: 20, 30, 50

## Inputs
- **Close** prices: `double[]`
- **Volume** data: `double[]`

## Outputs
- VWMA values: `double[]`

## Interpretation

### VWMA Characteristics
- **Volume Weighted**: Higher volume periods have more influence
- **Trend Following**: Follows price trends with volume emphasis
- **Support/Resistance**: Acts as dynamic support/resistance
- **Volume Confirmation**: Volume confirms price movements

### Trading Applications

1. **Trend Identification**:
   - **Price above VWMA**: Uptrend with volume support
   - **Price below VWMA**: Downtrend with volume support
   - **VWMA slope**: Trend strength with volume confirmation

2. **Support/Resistance**:
   - **VWMA as support**: In uptrends
   - **VWMA as resistance**: In downtrends
   - **Volume confirmation**: Volume supports price levels

3. **Volume Analysis**:
   - **High volume periods**: More influence on VWMA
   - **Low volume periods**: Less influence on VWMA
   - **Volume trends**: VWMA reflects volume trends

## Usage Example

```c
// C/C++ Example
double close[100], volume[100];
double vwmaOutput[100];
int outBegIdx, outNBElement;

// Calculate 20-period VWMA
TA_RetCode retCode = TA_VWMA(
    0,                    // start index
    99,                   // end index
    close,                // close prices
    volume,               // volume data
    20,                   // time period
    &outBegIdx,           // output: beginning index
    &outNBElement,        // output: number of elements
    vwmaOutput            // output: VWMA values
);
```

## Implementation Details

The TA-Lib VWMA implementation:

1. **Volume Weighting**: Multiplies each price by its volume
2. **Summation**: Sums weighted prices and volumes
3. **Division**: Divides weighted sum by volume sum
4. **Lookback**: Requires n periods for first output

## Trading Strategies

### 1. VWMA Trend Strategy
- **Buy**: Price crosses above VWMA
- **Sell**: Price crosses below VWMA
- **Stop**: Below/above VWMA
- **Best in**: Volume-confirmed trends

### 2. VWMA + Volume Strategy
- **Setup**: Use VWMA for trend direction
- **Entry**: Price direction with volume confirmation
- **Exit**: VWMA reversal or volume change
- **Best in**: Volume-confirmed trading

### 3. VWMA + Price Action Strategy
- **Setup**: Use VWMA for support/resistance
- **Entry**: Price patterns at VWMA touches
- **Exit**: Opposite VWMA touch
- **Best in**: Range-bound markets

### 4. Multiple VWMA Strategy
- **Setup**: Two VWMAs (e.g., 20 and 50 period)
- **Buy**: Fast VWMA crosses above slow VWMA
- **Sell**: Fast VWMA crosses below slow VWMA
- **Best in**: Trend change detection

## VWMA vs. SMA

| Aspect | VWMA | SMA |
|--------|------|-----|
| Weighting | Volume weighted | Equal weighted |
| Responsiveness | More responsive to volume | Less responsive |
| Volume | Incorporates volume | No volume |
| Signals | Volume confirmed | Price only |
| Best For | Volume analysis | General analysis |

## Advantages

1. **Volume Weighted**: Incorporates volume information
2. **More Accurate**: Better trend identification
3. **Volume Confirmation**: Volume confirms signals
4. **Universal**: Works across all markets
5. **Responsive**: Responds to significant volume

## Limitations

1. **Volume Dependent**: Requires volume data
2. **Still Lags**: Based on historical data
3. **Whipsaws**: Possible in choppy markets
4. **Period Sensitivity**: Results vary with period
5. **Complex**: More complex than SMA

## Period Selection

### Short Periods (10-20)
- **Characteristics**: More responsive
- **Use**: Short-term trading
- **Trade-off**: More signals, more noise
- **Best for**: Active trading

### Standard Periods (20-30)
- **Characteristics**: Balanced approach
- **Use**: General analysis
- **Trade-off**: Good balance
- **Best for**: Most applications

### Long Periods (30-50)
- **Characteristics**: Smoother, less responsive
- **Use**: Long-term analysis
- **Trade-off**: Fewer signals, more reliable
- **Best for**: Position trading

## Related Functions

- **SMA**: Simple Moving Average - equal weighted
- **EMA**: Exponential Moving Average - time weighted
- **WMA**: Weighted Moving Average - time weighted
- **OBV**: On Balance Volume - volume-based

## References

- [TA-Lib Source Code: ta_VWMA.c](https://github.com/TA-Lib/ta-lib/blob/main/src/ta_func/ta_VWMA.c)
- [Investopedia: Volume Weighted Moving Average](https://www.investopedia.com/terms/v/vwma.asp)
- [StockCharts: VWMA](https://school.stockcharts.com/doku.php?id=technical_indicators:volume_weighted_moving_average)

## Additional Notes

VWMA is a volume-weighted version of the simple moving average that gives more weight to periods with higher trading activity. It's particularly useful for identifying trends with volume confirmation.

### Key Insights

1. **Volume Weighting**:
   - Higher volume periods have more influence
   - Lower volume periods have less influence
   - VWMA reflects volume trends
   - Volume confirms price movements

2. **Trend Identification**:
   - Price above VWMA = uptrend with volume
   - Price below VWMA = downtrend with volume
   - VWMA slope = trend strength
   - Volume confirmation = stronger signals

3. **Best Applications**:
   - Volume-confirmed trend following
   - Support/resistance analysis
   - Volume-based trading
   - Trend strength assessment

4. **Signal Interpretation**:
   - Price crossovers = trend changes
   - VWMA slope = trend strength
   - Volume confirmation = signal strength
   - Support/resistance = dynamic levels

5. **Combination Strategies**:
   - Use with price indicators
   - Combine with volume analysis
   - Use for trend confirmation
   - Multiple timeframe analysis

### Practical Tips

**For Trend Following**:
- Use VWMA for trend direction
- Enter on volume confirmation
- Exit on trend change
- Use volume for validation

**For Support/Resistance**:
- Use VWMA as dynamic levels
- Enter on bounces from VWMA
- Exit on opposite VWMA touch
- Use volume for confirmation

**For Volume Analysis**:
- Track volume trends
- Use VWMA for volume confirmation
- Enter on volume increases
- Exit on volume decreases

**For Risk Management**:
- Use VWMA for stop placement
- Set stops beyond VWMA
- Use volume for position sizing
- Monitor VWMA trends

VWMA is particularly valuable for traders who want to incorporate volume analysis into their trend following strategies. It's excellent for volume-confirmed trading and provides better trend identification than simple moving averages.

