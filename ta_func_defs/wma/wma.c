int TA_WMA_Lookback(int optInTimePeriod)
{
    return optInTimePeriod - 1;
}

TA_RetCode TA_INT_WMA(int startIdx, int endIdx,
                      const double inReal[],
                      int optInTimePeriod,
                      int *outBegIdx, int *outNBElement,
                      double outReal[])
{
    int divider;
    double periodSum = 0.0;
    double periodSub = 0.0;
    double tempReal;
    double trailingValue;
    size_t inIdx;
    size_t outIdx;
    size_t trailingIdx;
    size_t lookbackTotal;
    int i;

    lookbackTotal = (size_t)(optInTimePeriod - 1);

    if( startIdx < lookbackTotal ) {
        startIdx = lookbackTotal;
    }
    if( startIdx > endIdx ) {
        *outBegIdx = 0;
        *outNBElement = 0;
        return TA_SUCCESS;
    }

    if( optInTimePeriod == 1 ) {
        size_t nbElement = endIdx - startIdx + 1;
        *outNBElement = nbElement;
        *outBegIdx = startIdx;
        TA_ARRAY_COPY(outReal, 0, inReal, startIdx, nbElement);
        return TA_SUCCESS;
    }

    divider = (optInTimePeriod * (optInTimePeriod + 1)) / 2;
    outIdx = 0;
    trailingIdx = startIdx - lookbackTotal;

    inIdx = trailingIdx;
    i = 1;
    while( inIdx < startIdx ) {
        tempReal = (double)inReal[inIdx];
        periodSub += tempReal;
        periodSum += tempReal * (double)i;
        i += 1;
        inIdx += 1;
    }

    trailingValue = 0.0;
    while( inIdx <= endIdx ) {
        tempReal = (double)inReal[inIdx];
        inIdx += 1;
        periodSub += tempReal;
        periodSub -= trailingValue;
        periodSum += tempReal * (double)optInTimePeriod;
        trailingValue = (double)inReal[trailingIdx];
        trailingIdx += 1;
        outReal[outIdx] = periodSum / (double)divider;
        outIdx += 1;
        periodSum -= periodSub;
    }

    *outNBElement = outIdx;
    *outBegIdx = startIdx;

    return TA_SUCCESS;
}
