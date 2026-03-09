int cdldragonflydoji_lookback(void)
{
    return max( TA_CANDLEAVGPERIOD(BodyDoji), TA_CANDLEAVGPERIOD(ShadowVeryShort) );
}

TA_RetCode cdldragonflydoji(int startIdx, int endIdx, const double inOpen[], const double inHigh[], const double inLow[], const double inClose[], int *outBegIdx, int *outNBElement, int outInteger[])
{
    double BodyDojiPeriodTotal, ShadowVeryShortPeriodTotal;
    int i, outIdx, BodyDojiTrailingIdx, ShadowVeryShortTrailingIdx, lookbackTotal;


    /* Identify the minimum number of price bar needed
    * to calculate at least one output.
    */

    lookbackTotal = cdldragonflydoji_lookback();

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
    ShadowVeryShortPeriodTotal = 0;
    ShadowVeryShortTrailingIdx = startIdx - TA_CANDLEAVGPERIOD(ShadowVeryShort);

    i = BodyDojiTrailingIdx;
    while( i < startIdx ) {
    BodyDojiPeriodTotal += TA_CANDLERANGE( BodyDoji, i );
    i++;
    }
    i = ShadowVeryShortTrailingIdx;
    while( i < startIdx ) {
    ShadowVeryShortPeriodTotal += TA_CANDLERANGE( ShadowVeryShort, i );
    i++;
    }

    /* Proceed with the calculation for the requested range.
    *
    * Must have:
    * - doji body
    * - open and close at the high of the day = no or very short upper shadow
    * - lower shadow (to distinguish from other dojis, here lower shadow should not be very short)
    * The meaning of "doji" and "very short" is specified with TA_SetCandleSettings
    * outInteger is always positive (1 to 100) but this does not mean it is bullish: dragonfly doji must be considered
    * relatively to the trend
    */
    outIdx = 0;
    do
    {
    if( TA_REALBODY(i) <= TA_CANDLEAVERAGE( BodyDoji, BodyDojiPeriodTotal, i ) &&
    TA_UPPERSHADOW(i) < TA_CANDLEAVERAGE( ShadowVeryShort, ShadowVeryShortPeriodTotal, i ) &&
    TA_LOWERSHADOW(i) > TA_CANDLEAVERAGE( ShadowVeryShort, ShadowVeryShortPeriodTotal, i )
    )
    outInteger[outIdx++] = 100;
    else
    outInteger[outIdx++] = 0;

    /* add the current range and subtract the first range: this is done after the pattern recognition
    * when avgPeriod is not 0, that means "compare with the previous candles" (it excludes the current candle)
    */
    BodyDojiPeriodTotal += TA_CANDLERANGE( BodyDoji, i ) - TA_CANDLERANGE( BodyDoji, BodyDojiTrailingIdx );
    ShadowVeryShortPeriodTotal += TA_CANDLERANGE( ShadowVeryShort, i )
    - TA_CANDLERANGE( ShadowVeryShort, ShadowVeryShortTrailingIdx );
    i++;
    BodyDojiTrailingIdx++;
    ShadowVeryShortTrailingIdx++;
    } while( i <= endIdx );

    /* All done. Indicate the output limits and return. */
    *outNBElement = outIdx;
    *outBegIdx    = startIdx;

    return TA_SUCCESS;
}
