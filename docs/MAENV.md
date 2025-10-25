# MAENV - Moving Average Envelope

## Description

The Moving Average Envelope (MAENV) is a trend indicator that creates upper and lower bands around a moving average. It's similar to Bollinger Bands but uses fixed percentages instead of standard deviations. MAENV helps identify overbought/oversold conditions and potential trend reversals.

## Category
Overlap Studies

## Author
Traditional Technical Analysis

## Calculation

MAENV is calculated using a moving average with percentage bands:

### Step 1: Calculate Moving Average
```
MA = SMA(Price, period)
```

### Step 2: Calculate Upper Band
```
Upper Band = MA × (1 + percentage)
```

### Step 3: Calculate Lower Band
```
Lower Band = MA × (1 - percentage)
```

Where:
- SMA = Simple Moving Average
- percentage = envelope percentage (default: 2.5%)

## Parameters

- **optInTimePeriod** (default: 14): Period for moving average
  - Valid range: 2 to 100000
  - Common values: 14 (standard), 20, 30

- **optInNbDev** (default: 0.025): Envelope percentage
  - Valid range: 0.001 to 0.5
  - Common values: 0.025 (2.5%), 0.05 (5%), 0.1 (10%)

## Inputs
- Price data: `double[]` (typically closing prices)

## Outputs
- **outUpperBand**: Upper band values: `double[]`
- **outMiddleBand**: Middle band (MA) values: `double[]`
- **outLowerBand**: Lower band values: `double[]`

## Interpretation

### MAENV Values
- **Upper Band**: Resistance level
- **Middle Band**: Trend line
- **Lower Band**: Support level

### Trading Signals

1. **Overbought/Oversold**:
   - **Overbought**: Price above upper band
   - **Oversold**: Price below lower band
   - **Neutral**: Price between bands

2. **Trend Identification**:
   - **Uptrend**: Price above middle band
   - **Downtrend**: Price below middle band
   - **Sideways**: Price oscillating around middle band

3. **Breakouts**:
   - **Bullish**: Price breaks above upper band
   - **Bearish**: Price breaks below lower band
   - **Best in**: Trend continuation

4. **Mean Reversion**:
   - **Buy**: Price touches lower band
   - **Sell**: Price touches upper band
   - **Best in**: Range-bound markets

## Usage Example

```c
// C/C++ Example
double closePrices[100];
double upperBand[100], middleBand[100], lowerBand[100];
int outBegIdx, outNBElement;

// Calculate MAENV (14, 0.025)
TA_RetCode retCode = TA_MAENV(
    0,                    // start index
    99,                   // end index
    closePrices,          // input price data
    14,                   // time period
    0.025,                // envelope percentage
    &outBegIdx,           // output: beginning index
    &outNBElement,        // output: number of elements
    upperBand,            // output: upper band
    middleBand,           // output: middle band
    lowerBand             // output: lower band
);
```

## Implementation Details

The TA-Lib MAENV implementation:

1. **Moving Average**: Calculates SMA over specified period
2. **Upper Band**: Calculates upper band with percentage
3. **Lower Band**: Calculates lower band with percentage
4. **Lookback**: Requires n periods for first output

## Trading Strategies

### 1. Overbought/Oversold Strategy
- **Buy**: Price touches lower band
- **Sell**: Price touches upper band
- **Confirmation**: Wait for price reversal
- **Best in**: Range-bound markets

### 2. Breakout Strategy
- **Buy**: Price breaks above upper band
- **Sell**: Price breaks below lower band
- **Confirmation**: Volume increase
- **Best in**: Trending markets

### 3. Trend Following Strategy
- **Buy**: Price above middle band
- **Sell**: Price below middle band
- **Exit**: Price crosses middle band
- **Best in**: Trending markets

### 4. MAENV + Volume Strategy
- **Setup**: Use MAENV for levels
- **Entry**: Price direction with volume confirmation
- **Exit**: MAENV reversal or volume change
- **Best in**: Volume-confirmed trading

## MAENV vs. Bollinger Bands

| Aspect | MAENV | Bollinger Bands |
|--------|-------|-----------------|
| Calculation | Fixed percentage | Standard deviation |
| Responsiveness | Fixed | Adaptive |
| Volatility | No | Yes |
| Best For | Range-bound markets | Volatile markets |

## Advantages

1. **Simple**: Easy to understand and calculate
2. **Clear**: Obvious support/resistance levels
3. **Universal**: Works across all markets
4. **Versatile**: Many applications
5. **Reliable**: Fewer false signals

## Limitations

1. **Fixed**: Doesn't adapt to volatility
2. **Still Lags**: Based on historical data
3. **Whipsaws**: Possible in choppy markets
4. **Period Sensitivity**: Results vary with period
5. **Context Dependent**: Needs interpretation

## Period Selection

### Short Periods (10-14)
- **Characteristics**: More responsive
- **Use**: Short-term trading
- **Trade-off**: More signals, more noise
- **Best for**: Active trading

### Standard Periods (14-20)
- **Characteristics**: Balanced approach
- **Use**: General trend analysis
- **Trade-off**: Good balance
- **Best for**: Most applications

### Long Periods (20-30)
- **Characteristics**: Smoother, less responsive
- **Use**: Long-term analysis
- **Trade-off**: Fewer signals, more reliable
- **Best for**: Position trading

## Related Functions

- **BBANDS**: Bollinger Bands - adaptive version
- **SMA**: Simple Moving Average - building block
- **EMA**: Exponential Moving Average - alternative
- **WMA**: Weighted Moving Average - alternative

## References

- [TA-Lib Source Code: ta_MAENV.c](https://github.com/TA-Lib/ta-lib/blob/main/src/ta_func/ta_MAENV.c)
- [Investopedia: Moving Average Envelope](https://www.investopedia.com/terms/m/moving-average-envelope.asp)
- [StockCharts: Moving Average Envelope](https://school.stockcharts.com/doku.php?id=technical_indicators:moving_average_envelope)

## Additional Notes

The Moving Average Envelope is a simple but effective trend indicator that provides clear support and resistance levels.

### Key Insights

1. **Fixed Percentage**:
   - Uses fixed percentage for bands
   - Doesn't adapt to volatility
   - Good for range-bound markets
   - Simple to understand

2. **Support/Resistance**:
   - Upper band = resistance
   - Lower band = support
   - Middle band = trend line
   - Use for entry/exit levels

3. **Best Applications**:
   - Range-bound markets
   - Overbought/oversold identification
   - Trend confirmation
   - Support/resistance levels

4. **Signal Interpretation**:
   - Price above upper band = overbought
   - Price below lower band = oversold
   - Price between bands = neutral
   - Price crossing bands = breakout

5. **Combination Strategies**:
   - Use with volume analysis
   - Combine with trend indicators
   - Use for support/resistance
   - Multiple timeframe analysis

### Practical Tips

**For Range-bound Markets**:
- Use MAENV for overbought/oversold
- Buy at lower band
- Sell at upper band
- Use for mean reversion

**For Trending Markets**:
- Use MAENV for trend confirmation
- Price above middle band = uptrend
- Price below middle band = downtrend
- Use for trend following

**For Breakout Trading**:
- Watch for price breaking bands
- Confirm with volume
- Use for trend continuation
- Set stops beyond bands

**For Risk Management**:
- Use MAENV for stop placement
- Set stops beyond bands
- Use for position sizing
- Monitor band touches

MAENV is particularly valuable for traders who want a simple, clear trend indicator with obvious support and resistance levels. It's excellent for range-bound markets and provides clear overbought/oversold signals.
