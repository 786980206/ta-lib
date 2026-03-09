int cdlsticksandwich_lookback(void)
{
    return TA_CANDLEAVGPERIOD(Equal) + 2;
}

TA_RetCode cdlsticksandwich(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[])
{
    double EqualPeriodTotal;
    int i, outIdx, EqualTrailingIdx, lookbackTotal;


    /* Identify the minimum number of price bar needed
    * to calculate at least one output.
    */

    lookbackTotal = cdlsticksandwich_lookback();

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

    i = EqualTrailingIdx;
    while( i < startIdx ) {
    EqualPeriodTotal += TA_CANDLERANGE( Equal, i-2 );
    i++;
    }
    i = startIdx;

    /* Proceed with the calculation for the requested range.
    * Must have:
    * - first candle: black candle
    * - second candle: white candle that trades only above the prior close (low > prior close)
    * - third candle: black candle with the close equal to the first candle's close
    * The meaning of "equal" is specified with TA_SetCandleSettings
    * outInteger is always positive (1 to 100): stick sandwich is always bullish;
    * the user should consider that stick sandwich is significant when coming in a downtrend,
    * while this function does not consider it
    */
    outIdx = 0;
    do
    {
    if( TA_CANDLECOLOR(i-2) == -1 &&                                                        // first black
    TA_CANDLECOLOR(i-1) == 1 &&                                                         // second white
    TA_CANDLECOLOR(i) == -1 &&                                                          // third black
    inLow[i-1] > inClose[i-2] &&                                                        // 2nd low > prior close
    inClose[i] <= inClose[i-2] + TA_CANDLEAVERAGE( Equal, EqualPeriodTotal, i-2 ) && // 1st and 3rd same close
    inClose[i] >= inClose[i-2] - TA_CANDLEAVERAGE( Equal, EqualPeriodTotal, i-2 )
    )
    outInteger[outIdx++] = 100;
    else
    outInteger[outIdx++] = 0;
    /* add the current range and subtract the first range: this is done after the pattern recognition
    * when avgPeriod is not 0, that means "compare with the previous candles" (it excludes the current candle)
    */
    EqualPeriodTotal += TA_CANDLERANGE( Equal, i-2 ) - TA_CANDLERANGE( Equal, EqualTrailingIdx-2 );
    i++;
    EqualTrailingIdx++;
    } while( i <= endIdx );

    /* All done. Indicate the output limits and return. */
    *outNBElement = outIdx;
    *outBegIdx    = startIdx;

    return TA_SUCCESS;
}
