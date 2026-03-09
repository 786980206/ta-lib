int cdl3blackcrows_lookback(void)
{
    return TA_CANDLEAVGPERIOD(ShadowVeryShort) + 3;
}

TA_RetCode cdl3blackcrows(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[])
{
    ARRAY_LOCAL(ShadowVeryShortPeriodTotal,3);
    int i, outIdx, totIdx, ShadowVeryShortTrailingIdx, lookbackTotal;


    /* Identify the minimum number of price bar needed
    * to calculate at least one output.
    */

    lookbackTotal = cdl3blackcrows_lookback();

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
    ShadowVeryShortPeriodTotal[2] = 0;
    ShadowVeryShortPeriodTotal[1] = 0;
    ShadowVeryShortPeriodTotal[0] = 0;
    ShadowVeryShortTrailingIdx = startIdx - TA_CANDLEAVGPERIOD(ShadowVeryShort);

    i = ShadowVeryShortTrailingIdx;
    while( i < startIdx ) {
    ShadowVeryShortPeriodTotal[2] += TA_CANDLERANGE( ShadowVeryShort, i-2 );
    ShadowVeryShortPeriodTotal[1] += TA_CANDLERANGE( ShadowVeryShort, i-1 );
    ShadowVeryShortPeriodTotal[0] += TA_CANDLERANGE( ShadowVeryShort, i );
    i++;
    }
    i = startIdx;

    /* Proceed with the calculation for the requested range.
    * Must have:
    * - three consecutive and declining black candlesticks
    * - each candle must have no or very short lower shadow
    * - each candle after the first must open within the prior candle's real body
    * - the first candle's close should be under the prior white candle's high
    * The meaning of "very short" is specified with TA_SetCandleSettings
    * outInteger is negative (-1 to -100): three black crows is always bearish;
    * the user should consider that 3 black crows is significant when it appears after a mature advance or at high levels,
    * while this function does not consider it
    */
    outIdx = 0;
    do
    {
    if( TA_CANDLECOLOR(i-3) == 1 &&                                         // white
    TA_CANDLECOLOR(i-2) == -1 &&                                        // 1st black
    TA_LOWERSHADOW(i-2) < TA_CANDLEAVERAGE( ShadowVeryShort, ShadowVeryShortPeriodTotal[2], i-2 ) &&
    // very short lower shadow
    TA_CANDLECOLOR(i-1) == -1 &&                                        // 2nd black
    TA_LOWERSHADOW(i-1) < TA_CANDLEAVERAGE( ShadowVeryShort, ShadowVeryShortPeriodTotal[1], i-1 ) &&
    // very short lower shadow
    TA_CANDLECOLOR(i) == -1 &&                                          // 3rd black
    TA_LOWERSHADOW(i) < TA_CANDLEAVERAGE( ShadowVeryShort, ShadowVeryShortPeriodTotal[0], i ) &&
    // very short lower shadow
    inOpen[i-1] < inOpen[i-2] && inOpen[i-1] > inClose[i-2] &&          // 2nd black opens within 1st black's rb
    inOpen[i] < inOpen[i-1] && inOpen[i] > inClose[i-1] &&              // 3rd black opens within 2nd black's rb
    inHigh[i-3] > inClose[i-2] &&                                       // 1st black closes under prior candle's high
    inClose[i-2] > inClose[i-1] &&                                      // three declining
    inClose[i-1] > inClose[i]                                           // three declining
    )
    outInteger[outIdx++] = -100;
    else
    outInteger[outIdx++] = 0;
    /* add the current range and subtract the first range: this is done after the pattern recognition
    * when avgPeriod is not 0, that means "compare with the previous candles" (it excludes the current candle)
    */
    for (totIdx = 2; totIdx >= 0; --totIdx)
    ShadowVeryShortPeriodTotal[totIdx] += TA_CANDLERANGE( ShadowVeryShort, i-totIdx )
    - TA_CANDLERANGE( ShadowVeryShort, ShadowVeryShortTrailingIdx-totIdx );
    i++;
    ShadowVeryShortTrailingIdx++;
    } while( i <= endIdx );

    /* All done. Indicate the output limits and return. */
    *outNBElement = outIdx;
    *outBegIdx    = startIdx;

    return TA_SUCCESS;
}
