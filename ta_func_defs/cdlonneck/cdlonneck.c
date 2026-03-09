int cdlonneck_lookback(void)
{
    return max( TA_CANDLEAVGPERIOD(Equal), TA_CANDLEAVGPERIOD(BodyLong)
    ) + 1;
}

TA_RetCode cdlonneck(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[])
{
    double EqualPeriodTotal, BodyLongPeriodTotal;
    int i, outIdx, EqualTrailingIdx, BodyLongTrailingIdx, lookbackTotal;


    /* Identify the minimum number of price bar needed
    * to calculate at least one output.
    */

    lookbackTotal = cdlonneck_lookback();

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
    EqualPeriodTotal = 0;
    EqualTrailingIdx = startIdx - TA_CANDLEAVGPERIOD(Equal);
    BodyLongPeriodTotal = 0;
    BodyLongTrailingIdx = startIdx - TA_CANDLEAVGPERIOD(BodyLong);

    i = EqualTrailingIdx;
    while( i < startIdx ) {
    EqualPeriodTotal += TA_CANDLERANGE( Equal, i-1 );
    i++;
    }
    i = BodyLongTrailingIdx;
    while( i < startIdx ) {
    BodyLongPeriodTotal += TA_CANDLERANGE( BodyLong, i-1 );
    i++;
    }
    i = startIdx;

    /* Proceed with the calculation for the requested range.
    * Must have:
    * - first candle: long black candle
    * - second candle: white candle with open below previous day low and close equal to previous day low
    * The meaning of "equal" is specified with TA_SetCandleSettings
    * outInteger is negative (-1 to -100): on-neck is always bearish
    * the user should consider that on-neck is significant when it appears in a downtrend, while this function
    * does not consider it
    */
    outIdx = 0;
    do
    {
    if( TA_CANDLECOLOR(i-1) == -1 &&                                                        // 1st: black
    TA_REALBODY(i-1) > TA_CANDLEAVERAGE( BodyLong, BodyLongPeriodTotal, i-1 ) &&     //      long
    TA_CANDLECOLOR(i) == 1 &&                                                           // 2nd: white
    inOpen[i] < inLow[i-1] &&                                                           //   open below prior low
    inClose[i] <= inLow[i-1] + TA_CANDLEAVERAGE( Equal, EqualPeriodTotal, i-1 ) &&   //   close equal to prior low
    inClose[i] >= inLow[i-1] - TA_CANDLEAVERAGE( Equal, EqualPeriodTotal, i-1 )
    )
    outInteger[outIdx++] = -100;
    else
    outInteger[outIdx++] = 0;
    /* add the current range and subtract the first range: this is done after the pattern recognition
    * when avgPeriod is not 0, that means "compare with the previous candles" (it excludes the current candle)
    */
    EqualPeriodTotal += TA_CANDLERANGE( Equal, i-1 ) - TA_CANDLERANGE( Equal, EqualTrailingIdx-1 );
    BodyLongPeriodTotal += TA_CANDLERANGE( BodyLong, i-1 )
    - TA_CANDLERANGE( BodyLong, BodyLongTrailingIdx-1 );
    i++;
    EqualTrailingIdx++;
    BodyLongTrailingIdx++;
    } while( i <= endIdx );

    /* All done. Indicate the output limits and return. */
    *outNBElement = outIdx;
    *outBegIdx    = startIdx;

    return TA_SUCCESS;
}
