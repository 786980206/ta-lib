int apo_lookback(int           optInFastPeriod,                                            int           optInSlowPeriod,                                            TA_MAType     optInMAType)
{
    /* The slow MA is the key factor determining the lookback period. */
    return ma_lookback( max(optInSlowPeriod,optInFastPeriod), optInMAType );
}

TA_RetCode apo(int startIdx, int endIdx, const double inReal[], int optInFastPeriod, int optInSlowPeriod, TA_MAType optInMAType, int *outBegIdx, int *outNBElement, double outReal[])
{
    ARRAY_REF(tempBuffer);
    ENUM_DECLARATION(RetCode) retCode;



    /* Allocate an intermediate buffer. */
    ARRAY_ALLOC(tempBuffer, (endIdx-startIdx+1) );
    if( !tempBuffer )
    return TA_ALLOC_ERR;

    retCode = po( startIdx, endIdx,
    inReal,
    optInFastPeriod,
    optInSlowPeriod,
    optInMAType,
    outBegIdx,
    outNBElement,
    outReal,
    tempBuffer,
    0 /* No percentage. */ );

    ARRAY_FREE( tempBuffer );

    return retCode;
}
