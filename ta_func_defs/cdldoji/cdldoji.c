int cdldoji_lookback(void)
{
    return TA_CANDLEAVGPERIOD(BodyDoji);
}

TA_RetCode cdldoji(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[])
{
    double BodyDojiPeriodTotal;
    int i, outIdx, BodyDojiTrailingIdx, lookbackTotal;


    /* Identify the minimum number of price bar needed
    * to calculate at least one output.
    */

    lookbackTotal = cdldoji_lookback();

    /* Move up the start index if there is not
    * enough initial data.
    */
    if( startIdx < lookbackTotal )
    startIdx = lookbackTotal;

    /* Make sure there is still something to evaluate. */
    if( startIdx > endIdx )
    {
    *outBegIdx = 0;
    *outNBElement = 0;
    return TA_SUCCESS;
    }

    /* Do the calculation using tight loops. */
    /* Add-up the initial period, except for the last value. */
    BodyDojiPeriodTotal = 0;
    BodyDojiTrailingIdx = startIdx - TA_CANDLEAVGPERIOD(BodyDoji);

    i = BodyDojiTrailingIdx;
    while( i < startIdx ) {
    BodyDojiPeriodTotal += TA_CANDLERANGE( BodyDoji, i );
    i++;
    }

    /* Proceed with the calculation for the requested range.
    *
    * Must have:
    * - open quite equal to close
    * How much can be the maximum distance between open and close is specified with TA_SetCandleSettings
    * outInteger is always positive (1 to 100) but this does not mean it is bullish: doji shows uncertainty and it is
    * neither bullish nor bearish when considered alone
    */
    outIdx = 0;
    do
    {
    if( TA_REALBODY(i) <= TA_CANDLEAVERAGE( BodyDoji, BodyDojiPeriodTotal, i ) )
    outInteger[outIdx++] = 100;
    else
    outInteger[outIdx++] = 0;
    /* add the current range and subtract the first range: this is done after the pattern recognition
    * when avgPeriod is not 0, that means "compare with the previous candles" (it excludes the current candle)
    */
    BodyDojiPeriodTotal += TA_CANDLERANGE( BodyDoji, i ) - TA_CANDLERANGE( BodyDoji, BodyDojiTrailingIdx );
    i++;
    BodyDojiTrailingIdx++;
    } while( i <= endIdx );

    /* All done. Indicate the output limits and return. */
    *outNBElement = outIdx;
    *outBegIdx    = startIdx;

    return TA_SUCCESS;
}
