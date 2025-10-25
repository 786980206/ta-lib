# PERF - Performance

## Description

The Performance (PERF) function calculates the percentage change in price over a specified period. It's a simple but useful indicator that measures the performance of a security over time, providing insight into the rate of return and price appreciation or depreciation. PERF is commonly used for performance analysis and trend assessment.

## Category
Math Operators

## Calculation

PERF is calculated as the percentage change in price over a period:

### Formula
```
PERF = ((Current Price - Previous Price) / Previous Price) × 100
```

Where:
- Current Price = price at end of period
- Previous Price = price at start of period
- Result is expressed as percentage

### Example
If price was 100 at start and 110 at end:
```
PERF = ((110 - 100) / 100) × 100 = 10%
```

## Parameters

- **optInTimePeriod** (default: 30): Period for calculation
  - Valid range: 2 to 100000
  - Common values: 10, 20, 50

## Inputs
- Price data: `double[]` (typically closing prices)

## Outputs
- Performance values: `double[]` (percentage)

## Interpretation

### PERF Values
- **Positive**: Price appreciation (gains)
- **Negative**: Price depreciation (losses)
- **Zero**: No change in price
- **High Positive**: Strong gains
- **High Negative**: Strong losses

### Trading Applications

1. **Performance Analysis**:
   - **Positive PERF**: Profitable periods
   - **Negative PERF**: Loss periods
   - **PERF Trends**: Performance trend analysis
   - **Best in**: Performance assessment

2. **Trend Analysis**:
   - **Rising PERF**: Improving performance
   - **Falling PERF**: Declining performance
   - **PERF Patterns**: Performance pattern analysis
   - **Best in**: Trend analysis

3. **Market Analysis**:
   - **High PERF**: Strong markets
   - **Low PERF**: Weak markets
   - **PERF Patterns**: Market regime identification
   - **Best in**: Market analysis

## Usage Example

```c
// C/C++ Example
double closePrices[100];
double perfOutput[100];
int outBegIdx, outNBElement;

// Calculate 20-period PERF
TA_RetCode retCode = TA_PERF(
    0,                    // start index
    99,                   // end index
    closePrices,          // input price data
    20,                   // time period
    &outBegIdx,           // output: beginning index
    &outNBElement,        // output: number of elements
    perfOutput            // output: PERF values
);
```

## Implementation Details

The TA-Lib PERF implementation:

1. **Price Difference**: Calculates difference between current and previous price
2. **Percentage Calculation**: Converts to percentage
3. **Lookback**: Requires n periods for first output

## Trading Strategies

### 1. Performance-Based Strategy
- **Setup**: Track PERF over time
- **Entry**: When PERF reaches extremes
- **Exit**: When PERF returns to mean
- **Best in**: Performance trading

### 2. Trend Following Strategy
- **Setup**: Use PERF for trend direction
- **Entry**: Positive PERF for uptrends
- **Exit**: Negative PERF for downtrends
- **Best in**: Trend following

### 3. Market Regime Strategy
- **Setup**: Identify PERF regimes
- **Entry**: Different strategies for different regimes
- **Exit**: Switch strategies on regime change
- **Best in**: Adaptive trading

### 4. PERF Mean Reversion Strategy
- **Setup**: Track PERF mean reversion
- **Entry**: When PERF deviates from mean
- **Exit**: When PERF returns to mean
- **Best in**: Performance trading

## PERF Analysis

### 1. Positive PERF Periods
- **Characteristics**: Price appreciation
- **Trading**: Trend following
- **Risk**: Moderate risk
- **Best in**: Uptrends

### 2. Negative PERF Periods
- **Characteristics**: Price depreciation
- **Trading**: Trend following
- **Risk**: Moderate risk
- **Best in**: Downtrends

### 3. High PERF Periods
- **Characteristics**: Strong gains
- **Trading**: Momentum strategies
- **Risk**: High risk
- **Best in**: Momentum trading

### 4. Low PERF Periods
- **Characteristics**: Weak performance
- **Trading**: Defensive strategies
- **Risk**: Low risk
- **Best in**: Defensive trading

## Advantages

1. **Simple**: Easy to understand and calculate
2. **Clear**: Percentage change is intuitive
3. **Universal**: Works across all markets
4. **Fast**: Very efficient calculation
5. **Versatile**: Many applications

## Limitations

1. **No Bounds**: Unbounded percentage values
2. **Still Lags**: Based on historical data
3. **Whipsaws**: Possible in choppy markets
4. **Period Sensitivity**: Results vary with period
5. **No Direction**: Doesn't indicate future direction

## Period Selection

### Short Periods (5-10)
- **Characteristics**: More responsive
- **Use**: Short-term trading
- **Trade-off**: More signals, more noise
- **Best for**: Active trading

### Standard Periods (10-20)
- **Characteristics**: Balanced approach
- **Use**: General analysis
- **Trade-off**: Good balance
- **Best for**: Most applications

### Long Periods (20-50)
- **Characteristics**: Smoother, less responsive
- **Use**: Long-term analysis
- **Trade-off**: Fewer signals, more reliable
- **Best for**: Position trading

## Related Functions

- **ROC**: Rate of Change - similar concept
- **MOM**: Momentum - absolute change version
- **PPO**: Percentage Price Oscillator - similar concept
- **APO**: Absolute Price Oscillator - absolute version

## References

- [TA-Lib Source Code: ta_PERF.c](https://github.com/TA-Lib/ta-lib/blob/main/src/ta_func/ta_PERF.c)
- [Investopedia: Performance](https://www.investopedia.com/terms/p/performance.asp)
- [StockCharts: Performance](https://school.stockcharts.com/doku.php?id=technical_indicators:performance)

## Additional Notes

PERF is a fundamental performance measure that quantifies the rate of return over a specified period. It's essential for understanding price appreciation and depreciation in financial markets.

### Key Insights

1. **Performance Measurement**:
   - Measures rate of return
   - Positive = gains
   - Negative = losses
   - Zero = no change

2. **Trend Analysis**:
   - Rising PERF = improving performance
   - Falling PERF = declining performance
   - PERF patterns = trend patterns
   - Use for trend identification

3. **Best Applications**:
   - Performance assessment
   - Trend analysis
   - Market analysis
   - Return measurement

4. **Trading Applications**:
   - Performance-based strategies
   - Trend following
   - Market regime identification
   - Return analysis

5. **Combination Strategies**:
   - Use with trend indicators
   - Combine with volume analysis
   - Use for performance analysis
   - Multiple timeframe analysis

### Practical Tips

**For Performance Analysis**:
- Track PERF over time
- Identify performance trends
- Use for performance assessment
- Monitor return rates

**For Trend Analysis**:
- Use PERF for trend direction
- Enter on positive PERF
- Exit on negative PERF
- Use for trend identification

**For Market Analysis**:
- Identify market regimes
- Use PERF for market classification
- Monitor PERF patterns
- Use for market timing

**For Risk Management**:
- Use PERF for position sizing
- Reduce size during negative PERF
- Increase size during positive PERF
- Monitor performance trends

PERF is particularly valuable for performance analysis, trend assessment, and understanding the rate of return in financial markets. It's an essential tool for performance measurement and trend analysis.

