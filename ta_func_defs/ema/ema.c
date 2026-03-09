int ema_lookback(int optInTimePeriod)
{
    return optInTimePeriod - 1 + TA_GetUnstablePeriod(EMA);
}

TA_RetCode ema(int startIdx, int endIdx,
                      const double inReal[],
                      int optInTimePeriod,
                      int *outBegIdx, int *outNBElement,
                      double outReal[])
{
    double tempReal;
    double prevMA;
    int i;
    size_t today;
    size_t outIdx;
    size_t lookbackTotal;
    double optInK_1;

    lookbackTotal = (size_t)ema_lookback(optInTimePeriod);

    if( startIdx < lookbackTotal ) {
        startIdx = lookbackTotal;
    }

    if( startIdx > endIdx ) {
        *outBegIdx = 0;
        *outNBElement = 0;
        return TA_SUCCESS;
    }

    optInK_1 = TA_PER_TO_K(optInTimePeriod);
    *outBegIdx = startIdx;

    if( TA_GetCompatibility() == TA_COMPATIBILITY_DEFAULT ) {
        today = startIdx - lookbackTotal;
        i = optInTimePeriod;
        tempReal = 0.0;
        for( i = optInTimePeriod; i > 0; i-- ) {
            tempReal += (double)inReal[today];
            today = today + 1;
        }
        prevMA = tempReal / (double)optInTimePeriod;
    } else {
        prevMA = (double)inReal[0];
        today = 1;
    }

    while( today <= startIdx ) {
        prevMA = (((double)inReal[today] - prevMA) * optInK_1) + prevMA;
        today = today + 1;
    }

    outReal[0] = prevMA;
    outIdx = 1;

    while( today <= endIdx ) {
        prevMA = (((double)inReal[today] - prevMA) * optInK_1) + prevMA;
        today = today + 1;
        outReal[outIdx] = prevMA;
        outIdx = outIdx + 1;
    }

    *outNBElement = outIdx;

    return TA_SUCCESS;
}
