int trix_lookback(int           optInTimePeriod)
{
    int emaLookback;
    
    emaLookback = ema_lookback( optInTimePeriod );
    return (emaLookback*3) + rocr_lookback( 1 );
}

TA_RetCode trix(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[])
{
    double k;
    ARRAY_REF(tempBuffer);
    VALUE_HANDLE_INT(nbElement);
    VALUE_HANDLE_INT(begIdx);
    int totalLookback;
    int emaLookback, rocLookback;
    ENUM_DECLARATION(RetCode) retCode;
    int nbElementToOutput;



    /* Adjust the startIdx to account for the lookback. */
    emaLookback   = ema_lookback( optInTimePeriod );
    rocLookback   = rocr_lookback( 1 );
    totalLookback = (emaLookback*3) + rocLookback;

    if( startIdx < totalLookback )
    startIdx = totalLookback;

    /* Make sure there is still something to evaluate. */
    if( startIdx > endIdx )
    {
    *outNBElement = 0;
    *outBegIdx = 0;
    return TA_SUCCESS;
    }

    *outBegIdx = startIdx;

    nbElementToOutput = (endIdx-startIdx)+1+totalLookback;

    /* Allocate a temporary buffer for performing
    * the calculation.
    */
    ARRAY_ALLOC(tempBuffer, nbElementToOutput );

    if( !tempBuffer )
    {
    *outNBElement = 0;
    *outBegIdx = 0;
    return TA_ALLOC_ERR;
    }

    /* Calculate the first EMA */
    k = TA_PER_TO_K(optInTimePeriod);
    retCode = ema( (startIdx-totalLookback), endIdx, inReal,
    optInTimePeriod, k,
    VALUE_HANDLE_OUT(begIdx), VALUE_HANDLE_OUT(nbElement),
    tempBuffer );

    /* Verify for failure or if not enough data after
    * calculating the EMA.
    */
    if( (retCode != TA_SUCCESS ) || (VALUE_HANDLE_GET(nbElement) == 0) )
    {
    *outNBElement = 0;
    *outBegIdx = 0;
    ARRAY_FREE( tempBuffer );
    return retCode;
    }

    nbElementToOutput--; /* Make this variable zero base from now on. */

    /* Calculate the second EMA */
    nbElementToOutput -= emaLookback;
    retCode = ema( 0, nbElementToOutput, tempBuffer,
    optInTimePeriod, k,
    VALUE_HANDLE_OUT(begIdx), VALUE_HANDLE_OUT(nbElement),
    tempBuffer );

    /* Verify for failure or if not enough data after
    * calculating the EMA.
    */
    if( (retCode != TA_SUCCESS ) || (VALUE_HANDLE_GET(nbElement) == 0) )
    {
    *outNBElement = 0;
    *outBegIdx = 0;
    ARRAY_FREE( tempBuffer );
    return retCode;
    }

    /* Calculate the third EMA */
    nbElementToOutput -= emaLookback;
    retCode = ema( 0, nbElementToOutput, tempBuffer,
    optInTimePeriod, k,
    VALUE_HANDLE_OUT(begIdx), VALUE_HANDLE_OUT(nbElement),
    tempBuffer );

    /* Verify for failure or if not enough data after
    * calculating the EMA.
    */
    if( (retCode != TA_SUCCESS ) || (VALUE_HANDLE_GET(nbElement) == 0) )
    {
    *outNBElement = 0;
    *outBegIdx = 0;
    ARRAY_FREE( tempBuffer );
    return retCode;
    }

    /* Calculate the 1-day Rate-Of-Change */
    nbElementToOutput -= emaLookback;
    retCode = roc( 0, nbElementToOutput,
    tempBuffer,
    1,  VALUE_HANDLE_OUT(begIdx), outNBElement,
    outReal );

    ARRAY_FREE( tempBuffer );
    /* Verify for failure or if not enough data after
    * calculating the rate-of-change.
    */
    if( (retCode != TA_SUCCESS ) || ((int)*outNBElement == 0) )
    {
    *outNBElement = 0;
    *outBegIdx = 0;
    return retCode;
    }

    return TA_SUCCESS;
}
