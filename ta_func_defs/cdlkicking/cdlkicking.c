int cdlkicking_lookback(void)
{
    return max( TA_CANDLEAVGPERIOD(ShadowVeryShort), TA_CANDLEAVGPERIOD(BodyLong)
    ) + 1;
}

TA_RetCode cdlkicking(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[])
{
    ARRAY_LOCAL(ShadowVeryShortPeriodTotal,2);
    ARRAY_LOCAL(BodyLongPeriodTotal,2);
    int i, outIdx, totIdx, ShadowVeryShortTrailingIdx, BodyLongTrailingIdx, lookbackTotal;


    /* Identify the minimum number of price bar needed
    * to calculate at least one output.
    */

    lookbackTotal = cdlkicking_lookback();

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
    ShadowVeryShortPeriodTotal[1] = 0;
    ShadowVeryShortPeriodTotal[0] = 0;
    ShadowVeryShortTrailingIdx = startIdx - TA_CANDLEAVGPERIOD(ShadowVeryShort);
    BodyLongPeriodTotal[1] = 0;
    BodyLongPeriodTotal[0] = 0;
    BodyLongTrailingIdx = startIdx - TA_CANDLEAVGPERIOD(BodyLong);

    i = ShadowVeryShortTrailingIdx;
    while( i < startIdx ) {
    ShadowVeryShortPeriodTotal[1] += TA_CANDLERANGE( ShadowVeryShort, i-1 );
    ShadowVeryShortPeriodTotal[0] += TA_CANDLERANGE( ShadowVeryShort, i );
    i++;
    }
    i = BodyLongTrailingIdx;
    while( i < startIdx ) {
    BodyLongPeriodTotal[1] += TA_CANDLERANGE( BodyLong, i-1 );
    BodyLongPeriodTotal[0] += TA_CANDLERANGE( BodyLong, i );
    i++;
    }
    i = startIdx;

    /* Proceed with the calculation for the requested range.
    * Must have:
    * - first candle: marubozu
    * - second candle: opposite color marubozu
    * - gap between the two candles: upside gap if black then white, downside gap if white then black
    * The meaning of "long body" and "very short shadow" is specified with TA_SetCandleSettings
    * outInteger is positive (1 to 100) when bullish or negative (-1 to -100) when bearish
    */
    outIdx = 0;
    do
    {
    if( TA_CANDLECOLOR(i-1) == -TA_CANDLECOLOR(i) &&                                        // opposite candles
    // 1st marubozu
    TA_REALBODY(i-1) > TA_CANDLEAVERAGE( BodyLong, BodyLongPeriodTotal[1], i-1 ) &&
    TA_UPPERSHADOW(i-1) < TA_CANDLEAVERAGE( ShadowVeryShort, ShadowVeryShortPeriodTotal[1], i-1 ) &&
    TA_LOWERSHADOW(i-1) < TA_CANDLEAVERAGE( ShadowVeryShort, ShadowVeryShortPeriodTotal[1], i-1 ) &&
    // 2nd marubozu
    TA_REALBODY(i) > TA_CANDLEAVERAGE( BodyLong, BodyLongPeriodTotal[0], i ) &&
    TA_UPPERSHADOW(i) < TA_CANDLEAVERAGE( ShadowVeryShort, ShadowVeryShortPeriodTotal[0], i ) &&
    TA_LOWERSHADOW(i) < TA_CANDLEAVERAGE( ShadowVeryShort, ShadowVeryShortPeriodTotal[0], i ) &&
    // gap
    (
    ( TA_CANDLECOLOR(i-1) == -1 && TA_CANDLEGAPUP(i,i-1) )
    ||
    ( TA_CANDLECOLOR(i-1) == 1 && TA_CANDLEGAPDOWN(i,i-1) )
    )
    )
    outInteger[outIdx++] = TA_CANDLECOLOR(i) * 100;
    else
    outInteger[outIdx++] = 0;

    /* add the current range and subtract the first range: this is done after the pattern recognition
    * when avgPeriod is not 0, that means "compare with the previous candles" (it excludes the current candle)
    */
    for (totIdx = 1; totIdx >= 0; --totIdx) {
    BodyLongPeriodTotal[totIdx] += TA_CANDLERANGE( BodyLong, i-totIdx )
    - TA_CANDLERANGE( BodyLong, BodyLongTrailingIdx-totIdx );
    ShadowVeryShortPeriodTotal[totIdx] += TA_CANDLERANGE( ShadowVeryShort, i-totIdx )
    - TA_CANDLERANGE( ShadowVeryShort, ShadowVeryShortTrailingIdx-totIdx );
    }
    i++;
    ShadowVeryShortTrailingIdx++;
    BodyLongTrailingIdx++;
    } while( i <= endIdx );

    /* All done. Indicate the output limits and return. */
    *outNBElement = outIdx;
    *outBegIdx    = startIdx;

    return TA_SUCCESS;
}
