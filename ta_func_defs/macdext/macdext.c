int macdext_lookback(int           optInFastPeriod,                                                TA_MAType     optInFastMAType,                                               int           optInSlowPeriod,                                                TA_MAType     optInSlowMAType,                                               int           optInSignalPeriod,                                                TA_MAType     optInSignalMAType)
{
    int tempInteger, lookbackLargest;
    
    
    
    /* Find the MA with the largest lookback */
    lookbackLargest = ma_lookback( optInFastPeriod, optInFastMAType );
    tempInteger     = ma_lookback( optInSlowPeriod, optInSlowMAType );
    if( tempInteger > lookbackLargest )
    lookbackLargest = tempInteger;
    
    /* Add to the largest MA lookback the signal line lookback */
    return lookbackLargest + ma_lookback( optInSignalPeriod, optInSignalMAType );
}

TA_RetCode macdext(int startIdx, int endIdx, const double inReal[], int optInFastPeriod, TA_MAType optInFastMAType, int optInSlowPeriod, TA_MAType optInSlowMAType, int optInSignalPeriod, TA_MAType optInSignalMAType, int *outBegIdx, int *outNBElement, double outMACD[], double outMACDSignal[], double outMACDHist[])
{
    ARRAY_REF( slowMABuffer );
    ARRAY_REF( fastMABuffer );
    ENUM_DECLARATION(RetCode) retCode;
    int tempInteger;
    VALUE_HANDLE_INT(outBegIdx1);
    VALUE_HANDLE_INT(outNbElement1);
    VALUE_HANDLE_INT(outBegIdx2);
    VALUE_HANDLE_INT(outNbElement2);
    int lookbackTotal, lookbackSignal, lookbackLargest;
    int i;
    ENUM_DECLARATION(MAType) tempMAType;



    /* Make sure slow is really slower than
    * the fast period! if not, swap...
    */
    if( optInSlowPeriod < optInFastPeriod )
    {
    /* swap period */
    tempInteger     = optInSlowPeriod;
    optInSlowPeriod = optInFastPeriod;
    optInFastPeriod = tempInteger;
    /* swap type */
    tempMAType      = optInSlowMAType;
    optInSlowMAType = optInFastMAType;
    optInFastMAType = tempMAType;
    }

    /* Find the MA with the largest lookback */
    lookbackLargest = ma_lookback( optInFastPeriod, optInFastMAType );
    tempInteger     = ma_lookback( optInSlowPeriod, optInSlowMAType );
    if( tempInteger > lookbackLargest )
    lookbackLargest = tempInteger;

    /* Add the lookback needed for the signal line */
    lookbackSignal = ma_lookback( optInSignalPeriod, optInSignalMAType );
    lookbackTotal  = lookbackSignal+lookbackLargest;

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

    /* Allocate intermediate buffer for fast/slow MA. */
    tempInteger = (endIdx-startIdx)+1+lookbackSignal;
    ARRAY_ALLOC( fastMABuffer, tempInteger );
    if( !fastMABuffer )
    {
    *outBegIdx = 0;
    *outNBElement = 0;
    return TA_ALLOC_ERR;
    }

    ARRAY_ALLOC( slowMABuffer, tempInteger );
    if( !slowMABuffer )
    {
    *outBegIdx = 0;
    *outNBElement = 0;
    ARRAY_FREE( fastMABuffer );
    return TA_ALLOC_ERR;
    }

    /* Calculate the slow MA.
    *
    * Move back the startIdx to get enough data
    * for the signal period. That way, once the
    * signal calculation is done, all the output
    * will start at the requested 'startIdx'.
    */
    tempInteger = startIdx-lookbackSignal;
    retCode = ma( tempInteger, endIdx,
    inReal, optInSlowPeriod, optInSlowMAType,
    VALUE_HANDLE_OUT(outBegIdx1), VALUE_HANDLE_OUT(outNbElement1),
    slowMABuffer );

    if( retCode != TA_SUCCESS )
    {
    *outBegIdx = 0;
    *outNBElement = 0;
    ARRAY_FREE( fastMABuffer );
    ARRAY_FREE( slowMABuffer );
    return retCode;
    }

    /* Calculate the fast MA. */
    retCode = ma( tempInteger, endIdx,
    inReal, optInFastPeriod, optInFastMAType,
    VALUE_HANDLE_OUT(outBegIdx2), VALUE_HANDLE_OUT(outNbElement2),
    fastMABuffer );

    if( retCode != TA_SUCCESS )
    {
    *outBegIdx = 0;
    *outNBElement = 0;
    ARRAY_FREE( fastMABuffer );
    ARRAY_FREE( slowMABuffer );
    return retCode;
    }

    /* Parano tests. Will be removed eventually. */
    if( (VALUE_HANDLE_GET(outBegIdx1) != tempInteger) ||
    (VALUE_HANDLE_GET(outBegIdx2) != tempInteger) ||
    (VALUE_HANDLE_GET(outNbElement1) != VALUE_HANDLE_GET(outNbElement2)) ||
    (VALUE_HANDLE_GET(outNbElement1) != (endIdx-startIdx)+1+lookbackSignal) )
    {
    *outBegIdx = 0;
    *outNBElement = 0;
    ARRAY_FREE( fastMABuffer );
    ARRAY_FREE( slowMABuffer );
    return TA_INTERNAL_ERROR(119);
    }

    /* Calculate (fast MA) - (slow MA). */
    for( i=0; i < VALUE_HANDLE_GET(outNbElement1); i++ )
    fastMABuffer[i] = fastMABuffer[i] - slowMABuffer[i];

    /* Copy the result into the output for the caller. */
    TA_ARRAY_COPY( outMACD, 0, fastMABuffer, lookbackSignal, (endIdx-startIdx)+1 );

    /* Calculate the signal/trigger line. */
    retCode = ma( 0, VALUE_HANDLE_GET(outNbElement1)-1,
    fastMABuffer, optInSignalPeriod, optInSignalMAType,
    VALUE_HANDLE_OUT(outBegIdx2), VALUE_HANDLE_OUT(outNbElement2), outMACDSignal );

    ARRAY_FREE( fastMABuffer );
    ARRAY_FREE( slowMABuffer );

    if( retCode != TA_SUCCESS )
    {
    *outBegIdx = 0;
    *outNBElement = 0;
    return retCode;
    }

    /* Calculate the histogram. */
    for( i=0; i < VALUE_HANDLE_GET(outNbElement2); i++ )
    outMACDHist[i] = outMACD[i]-outMACDSignal[i];

    /* All done! Indicate the output limits and return success. */
    *outBegIdx     = startIdx;
    *outNBElement  = VALUE_HANDLE_GET(outNbElement2);

    return TA_SUCCESS;
}
