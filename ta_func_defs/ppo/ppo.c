int ppo_lookback(int           optInFastPeriod,                                            int           optInSlowPeriod,                                            TA_MAType     optInMAType)
{
    /* Lookback is driven by the slowest MA. */
    return ma_lookback( max(optInSlowPeriod,optInFastPeriod), optInMAType );
}

TA_RetCode ppo(int startIdx, int endIdx, const double inReal[], int optInFastPeriod, int optInSlowPeriod, TA_MAType optInMAType, int *outBegIdx, int *outNBElement, double outReal[])
{
    ARRAY_REF(tempBuffer);
    ENUM_DECLARATION(RetCode) retCode;



    /* Allocate an intermediate buffer. */
    ARRAY_ALLOC( tempBuffer, endIdx-startIdx+1 );
    if( !tempBuffer )
    return TA_ALLOC_ERR;

    retCode = po( startIdx, endIdx, inReal,
    optInFastPeriod,
    optInSlowPeriod,
    optInMAType,
    outBegIdx,
    outNBElement,
    outReal,
    tempBuffer,
    1 /* Do percentage processing. */ );

    ARRAY_FREE( tempBuffer );

    return retCode;
}
