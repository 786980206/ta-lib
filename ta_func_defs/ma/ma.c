int ma_lookback(int           optInTimePeriod,                                           TA_MAType     optInMAType)
{
    int retValue;
    
    
    
    if( optInTimePeriod <= 1 )
    return 0;
    
    switch( optInMAType )
    {
    case ENUM_CASE(MAType, TA_MAType_SMA, Sma ):
    retValue = sma_lookback( optInTimePeriod );
    break;
    
    case ENUM_CASE(MAType, TA_MAType_EMA, Ema):
    retValue = ema_lookback( optInTimePeriod );
    break;
    
    case ENUM_CASE(MAType, TA_MAType_WMA, Wma):
    retValue = wma_lookback( optInTimePeriod );
    break;
    
    case ENUM_CASE(MAType, TA_MAType_DEMA, Dema):
    retValue = dema_lookback( optInTimePeriod );
    break;
    
    case ENUM_CASE(MAType, TA_MAType_TEMA, Tema ):
    retValue = tema_lookback( optInTimePeriod );
    break;
    
    case ENUM_CASE(MAType, TA_MAType_TRIMA, Trima ):
    retValue = trima_lookback( optInTimePeriod );
    break;
    
    case ENUM_CASE(MAType, TA_MAType_KAMA, Kama ):
    retValue = kama_lookback( optInTimePeriod );
    break;
    
    case ENUM_CASE(MAType, TA_MAType_MAMA, Mama ):
    retValue = mama_lookback( 0.5, 0.05 );
    break;
    
    case ENUM_CASE(MAType, TA_MAType_T3, T3):
    retValue = t3_lookback( optInTimePeriod, 0.7 );
    break;
    
    default:
    retValue = 0;
    }
    
    return retValue;
}

TA_RetCode ma(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, TA_MAType optInMAType, int *outBegIdx, int *outNBElement, double outReal[])
{
    double *dummyBuffer;
    TA_RetCode retCode;

    int nbElement;
    int outIdx, todayIdx;


    if( optInTimePeriod == 1 )
    {
    nbElement = endIdx-startIdx+1;
    *outNBElement = nbElement;
    for( todayIdx=startIdx, outIdx=0; outIdx < nbElement; outIdx++, todayIdx++ )
    outReal[outIdx] = inReal[todayIdx];
    *outBegIdx    = startIdx;
    return TA_SUCCESS;
    }
    /* Simply forward the job to the corresponding TA function. */
    switch( optInMAType )
    {
    case ENUM_CASE(MAType, TA_MAType_SMA, Sma):
    retCode = sma( startIdx, endIdx, inReal, optInTimePeriod,
    outBegIdx, outNBElement, outReal );
    break;

    case ENUM_CASE(MAType, TA_MAType_EMA, Ema):
    retCode = ema( startIdx, endIdx, inReal, optInTimePeriod,
    outBegIdx, outNBElement, outReal );
    break;

    case ENUM_CASE(MAType, TA_MAType_WMA, Wma):
    retCode = wma( startIdx, endIdx, inReal, optInTimePeriod,
    outBegIdx, outNBElement, outReal );
    break;

    case ENUM_CASE(MAType, TA_MAType_DEMA, Dema):
    retCode = dema( startIdx, endIdx, inReal, optInTimePeriod,
    outBegIdx, outNBElement, outReal );
    break;

    case ENUM_CASE(MAType, TA_MAType_TEMA, Tema):
    retCode = tema( startIdx, endIdx, inReal, optInTimePeriod,
    outBegIdx, outNBElement, outReal );
    break;

    case ENUM_CASE(MAType, TA_MAType_TRIMA, Trima):
    retCode = trima( startIdx, endIdx, inReal, optInTimePeriod,
    outBegIdx, outNBElement, outReal );
    break;

    case ENUM_CASE(MAType, TA_MAType_KAMA, Kama):
    retCode = kama( startIdx, endIdx, inReal, optInTimePeriod,
    outBegIdx, outNBElement, outReal );
    break;

    case ENUM_CASE(MAType, TA_MAType_MAMA, Mama):
    /* The optInTimePeriod is ignored and the FAMA output of the MAMA
    * is ignored.
    */
    ARRAY_ALLOC(dummyBuffer, (endIdx-startIdx+1) );

    if( !dummyBuffer )
    return TA_ALLOC_ERR;

    retCode = mama( startIdx, endIdx, inReal, 0.5, 0.05,
    outBegIdx, outNBElement,
    outReal, dummyBuffer );

    free(dummyBuffer);
    break;

    case ENUM_CASE(MAType, TA_MAType_T3, T3 ):
    retCode = t3( startIdx, endIdx, inReal,
    optInTimePeriod, 0.7,
    outBegIdx, outNBElement, outReal );
    break;

    default:
    retCode = TA_BAD_PARAM;
    break;
    }

    return retCode;
}
