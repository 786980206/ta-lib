int cdleveningstar_lookback(double        optInPenetration)
{
    (void)optInPenetration;
    
    return max( TA_CANDLEAVGPERIOD(BodyShort), TA_CANDLEAVGPERIOD(BodyLong) ) + 2;
}

TA_RetCode cdleveningstar(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], double optInPenetration, int *outBegIdx, int *outNBElement, int outInteger[])
{
    double BodyShortPeriodTotal, BodyLongPeriodTotal, BodyShortPeriodTotal2;
    int i, outIdx, BodyShortTrailingIdx, BodyLongTrailingIdx, lookbackTotal;


    /* Identify the minimum number of price bar needed
    * to calculate at least one output.
    */

    lookbackTotal = cdleveningstar_lookback(optInPenetration);

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
    BodyLongPeriodTotal = 0;
    BodyShortPeriodTotal = 0;
    BodyShortPeriodTotal2 = 0;
    BodyLongTrailingIdx = startIdx -2 - TA_CANDLEAVGPERIOD(BodyLong);
    BodyShortTrailingIdx = startIdx -1 - TA_CANDLEAVGPERIOD(BodyShort);

    i = BodyLongTrailingIdx;
    while( i < startIdx-2 ) {
    BodyLongPeriodTotal += TA_CANDLERANGE( BodyLong, i );
    i++;
    }
    i = BodyShortTrailingIdx;
    while( i < startIdx-1 ) {
    BodyShortPeriodTotal += TA_CANDLERANGE( BodyShort, i );
    BodyShortPeriodTotal2 += TA_CANDLERANGE( BodyShort, i+1 );
    i++;
    }
    i = startIdx;

    /* Proceed with the calculation for the requested range.
    * Must have:
    * - first candle: long white real body
    * - second candle: star (short real body gapping up)
    * - third candle: black real body that moves well within the first candle's real body
    * The meaning of "short" and "long" is specified with TA_SetCandleSettings
    * The meaning of "moves well within" is specified with optInPenetration and "moves" should mean the real body should
    * not be short ("short" is specified with TA_SetCandleSettings) - Greg Morris wants it to be long, someone else want
    * it to be relatively long
    * outInteger is negative (-1 to -100): evening star is always bearish;
    * the user should consider that an evening star is significant when it appears in an uptrend,
    * while this function does not consider the trend
    */
    outIdx = 0;
    do
    {
    if( TA_REALBODY(i-2) > TA_CANDLEAVERAGE( BodyLong, BodyLongPeriodTotal, i-2 ) &&         // 1st: long
    TA_CANDLECOLOR(i-2) == 1 &&                                                             //           white
    TA_REALBODY(i-1) <= TA_CANDLEAVERAGE( BodyShort, BodyShortPeriodTotal, i-1 ) &&      // 2nd: short
    TA_REALBODYGAPUP(i-1,i-2) &&                                                            //            gapping up
    TA_REALBODY(i) > TA_CANDLEAVERAGE( BodyShort, BodyShortPeriodTotal2, i ) &&          // 3rd: longer than short
    TA_CANDLECOLOR(i) == -1 &&                                                              //          black real body
    inClose[i] < inClose[i-2] - TA_REALBODY(i-2) * optInPenetration                         //               closing well within 1st rb
    )
    outInteger[outIdx++] = -100;
    else
    outInteger[outIdx++] = 0;

    /* add the current range and subtract the first range: this is done after the pattern recognition
    * when avgPeriod is not 0, that means "compare with the previous candles" (it excludes the current candle)
    */
    BodyLongPeriodTotal += TA_CANDLERANGE( BodyLong, i-2 ) - TA_CANDLERANGE( BodyLong, BodyLongTrailingIdx );
    BodyShortPeriodTotal += TA_CANDLERANGE( BodyShort, i-1 ) - TA_CANDLERANGE( BodyShort, BodyShortTrailingIdx );
    BodyShortPeriodTotal2 += TA_CANDLERANGE( BodyShort, i ) - TA_CANDLERANGE( BodyShort, BodyShortTrailingIdx+1 );
    i++;
    BodyLongTrailingIdx++;
    BodyShortTrailingIdx++;
    } while( i <= endIdx );

    /* All done. Indicate the output limits and return. */
    *outNBElement = outIdx;
    *outBegIdx    = startIdx;

    return TA_SUCCESS;
}
