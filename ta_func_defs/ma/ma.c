int TA_MA_Lookback(int optInTimePeriod, int optInMAType)
{
    int retValue;
    if( optInTimePeriod <= 1 ) {
        return 0;
    }
    switch( optInMAType ) {
        case MAType_SMA:
            retValue = TA_SMA_Lookback(optInTimePeriod);
            break;
        case MAType_EMA:
            retValue = TA_EMA_Lookback(optInTimePeriod);
            break;
        default:
            retValue = 0;
            break;
    }
    return retValue;
}

TA_RetCode TA_MA(int startIdx, int endIdx,
                 const double inReal[],
                 int optInTimePeriod,
                 int optInMAType,
                 int *outBegIdx, int *outNBElement,
                 double outReal[])
{
    size_t nbElement;
    size_t outIdx;
    size_t todayIdx;
    TA_RetCode retCode;

    if( optInTimePeriod == 1 ) {
        nbElement = endIdx - startIdx + 1;
        *outNBElement = nbElement;
        todayIdx = startIdx;
        outIdx = 0;
        while( outIdx < nbElement ) {
            outReal[outIdx] = (double)inReal[todayIdx];
            outIdx = outIdx + 1;
            todayIdx = todayIdx + 1;
        }
        *outBegIdx = startIdx;
        return TA_SUCCESS;
    }

    switch( optInMAType ) {
        case MAType_SMA:
            retCode = TA_SMA(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
            break;
        case MAType_EMA:
            retCode = TA_EMA(startIdx, endIdx, inReal, optInTimePeriod, outBegIdx, outNBElement, outReal);
            break;
        default:
            retCode = TA_BAD_PARAM;
            break;
    }

    return retCode;
}
