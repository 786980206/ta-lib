int atr_lookback(int           optInTimePeriod)
{
    /* The ATR lookback is the sum of:
    *    1 + (optInTimePeriod - 1)
    *
    * Where 1 is for the True Range, and
    * (optInTimePeriod-1) is for the simple
    * moving average.
    */
    return optInTimePeriod + TA_GetUnstablePeriod(ATR);
}

TA_RetCode atr(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[])
{
    ENUM_DECLARATION(RetCode) retCode;
    int outIdx, today, lookbackTotal;
    int nbATR;
    VALUE_HANDLE_INT(outBegIdx1);
    VALUE_HANDLE_INT(outNbElement1);

    double prevATR;
    ARRAY_REF( tempBuffer );
    ARRAY_LOCAL(prevATRTemp,1);


    /* Average True Range is the greatest of the following:
    *
    *  val1 = distance from today's high to today's low.
    *  val2 = distance from yesterday's close to today's high.
    *  val3 = distance from yesterday's close to today's low.
    *
    * These value are averaged for the specified period using
    * Wilder method. This method have an unstable period comparable
    * to and Exponential Moving Average (EMA).
    */
    *outBegIdx = 0;
    *outNBElement = 0;

    /* Adjust startIdx to account for the lookback period. */
    lookbackTotal = atr_lookback( optInTimePeriod );

    if( startIdx < lookbackTotal )
    startIdx = lookbackTotal;

    /* Make sure there is still something to evaluate. */
    if( startIdx > endIdx )
    return TA_SUCCESS;

    /* Trap the case where no smoothing is needed. */
    if( optInTimePeriod <= 1 )
    {
    /* No smoothing needed. Just do a TRANGE. */
    return trange( startIdx, endIdx,
    inHigh, inLow, inClose,
    outBegIdx, outNBElement, outReal );
    }

    /* Allocate an intermediate buffer for TRANGE. */
    ARRAY_ALLOC(tempBuffer, lookbackTotal+(endIdx-startIdx)+1 );

    /* Do TRANGE in the intermediate buffer. */
    retCode = trange( (startIdx-lookbackTotal+1), endIdx,
    inHigh, inLow, inClose,
    VALUE_HANDLE_OUT(outBegIdx1), VALUE_HANDLE_OUT(outNbElement1),
    tempBuffer );

    if( retCode != TA_SUCCESS )
    {
    ARRAY_FREE( tempBuffer );
    return retCode;
    }

    /* First value of the ATR is a simple Average of
    * the TRANGE output for the specified period.
    */
    retCode = sma( optInTimePeriod-1,
    optInTimePeriod-1,
    tempBuffer, optInTimePeriod,
    VALUE_HANDLE_OUT(outBegIdx1), VALUE_HANDLE_OUT(outNbElement1),
    prevATRTemp );

    if( retCode != TA_SUCCESS )
    {
    ARRAY_FREE( tempBuffer );
    return retCode;
    }
    prevATR = prevATRTemp[0];

    /* Subsequent value are smoothed using the
    * previous ATR value (Wilder's approach).
    *  1) Multiply the previous ATR by 'period-1'.
    *  2) Add today TR value.
    *  3) Divide by 'period'.
    */
    today = optInTimePeriod;
    outIdx = TA_GetUnstablePeriod(ATR);
    /* Skip the unstable period. */
    while( outIdx != 0 )
    {
    prevATR *= optInTimePeriod - 1;
    prevATR += tempBuffer[today++];
    prevATR /= optInTimePeriod;
    outIdx--;
    }

    /* Now start to write the final ATR in the caller
    * provided outReal.
    */
    outIdx = 1;
    outReal[0] = prevATR;

    /* Now do the number of requested ATR. */
    nbATR = (endIdx - startIdx)+1;

    while( --nbATR != 0 )
    {
    prevATR *= optInTimePeriod - 1;
    prevATR += tempBuffer[today++];
    prevATR /= optInTimePeriod;
    outReal[outIdx++] = prevATR;
    }

    *outBegIdx    = startIdx;
    *outNBElement = outIdx;

    ARRAY_FREE( tempBuffer );

    return retCode;
}
