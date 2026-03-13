int ppo_lookback(int           optInFastPeriod,                                            int           optInSlowPeriod,                                            TA_MAType     optInMAType)
{
    /* Lookback is driven by the slowest MA. */
    return ma_lookback( max(optInSlowPeriod,optInFastPeriod), optInMAType );
}

TA_RetCode ppo(int startIdx, int endIdx, const double inReal[], int optInFastPeriod, int optInSlowPeriod, TA_MAType optInMAType, int *outBegIdx, int *outNBElement, double outReal[])
{
    double *tempBuffer;
    TA_RetCode retCode;



    /* Allocate an intermediate buffer. */
    double *tempBuffer = malloc((endIdx-startIdx+1) * sizeof(double));
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

    free(tempBuffer);

    return retCode;
}
