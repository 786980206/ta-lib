int mult_lookback(void)
{
    return 0;
}

TA_RetCode mult_logic(int startIdx, int endIdx,
                   const double inReal0[],
                   const double inReal1[],
                   int *outBegIdx, int *outNBElement,
                   double outReal[])
{
    size_t outIdx;
    size_t i;

    outIdx = 0;
    i = (size_t)startIdx;
    while( i <= (size_t)endIdx ) {
        outReal[outIdx] = inReal0[i] * inReal1[i];
        outIdx += 1;
        i += 1;
    }

    *outNBElement = outIdx;
    *outBegIdx = startIdx;

    return TA_SUCCESS;
}
