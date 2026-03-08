int sma_lookback(int optInTimePeriod)
{
    return optInTimePeriod - 1;
}

TA_RetCode sma_logic(int startIdx, int endIdx,
                       const double inReal[],
                       int optInTimePeriod,
                       int *outBegIdx, int *outNBElement,
                       double outReal[])
{
    double periodTotal = 0.0;
    double tempReal;
    size_t i, outIdx, trailingIdx, lookbackTotal;

    lookbackTotal = (size_t)(optInTimePeriod - 1);

    if( startIdx < lookbackTotal )
        startIdx = lookbackTotal;

    if( startIdx > endIdx ) {
        *outBegIdx = 0;
        *outNBElement = 0;
        return TA_SUCCESS;
    }

    periodTotal = 0.0;
    trailingIdx = startIdx - lookbackTotal;
    i = trailingIdx;

    if( optInTimePeriod > 1 ) {
        while( i < startIdx ) {
            periodTotal += (double)inReal[i];
            i++;
        }
    }

    outIdx = 0;
    while( i <= endIdx ) {
        periodTotal += (double)inReal[i];
        i++;
        tempReal = periodTotal;
        periodTotal -= (double)inReal[trailingIdx];
        trailingIdx++;
        outReal[outIdx] = tempReal / (double)optInTimePeriod;
        outIdx++;
    }

    *outNBElement = outIdx;
    *outBegIdx = startIdx;

    return TA_SUCCESS;
}
