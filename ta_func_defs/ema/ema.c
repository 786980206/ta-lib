int ema_lookback(int           optInTimePeriod)
{
    return optInTimePeriod - 1 + TA_GetUnstablePeriod(TA_FUNC_UNST_EMA);
}

TA_RetCode ema(int startIdx, int endIdx, const double *inReal, int optInTimePeriod, double optInK_1, int *outBegIdx, int *outNBElement, double *outReal)
{
    double tempReal, prevMA;
    int i, today, outIdx, lookbackTotal;

    /* Ususally, optInK_1 = 2 / (optInTimePeriod + 1),
    * but sometime there is exception. This
    * is why both value are parameters.
    */

    /* Identify the minimum number of price bar needed
    * to calculate at least one output.
    */
    lookbackTotal = ema_lookback( optInTimePeriod );

    /* Move up the start index if there is not
    * enough initial data.
    */
    if( startIdx < lookbackTotal )
    startIdx = lookbackTotal;

    /* Make sure there is still something to evaluate. */
    if( startIdx > endIdx )
    {
    *outBegIdx = 0;
    *outNBElement = 0;
    return TA_SUCCESS;
    }
    *outBegIdx = startIdx;

    /* Do the EMA calculation using tight loops. */

    /* The first EMA is calculated differently. It
    * then become the seed for subsequent EMA.
    *
    * The algorithm for this seed vary widely.
    * Only 3 are implemented here:
    *
    * TA_MA_CLASSIC:
    *    Use a simple MA of the first 'period'.
    *    This is the approach most widely documented.
    *
    * TA_MA_METASTOCK:
    *    Use first price bar value as a seed
    *    from the begining of all the available
    *    data.
    *
    * TA_MA_TRADESTATION:
    *    Use 4th price bar as a seed, except when
    *    period is 1 who use 2th price bar or something
    *    like that... (not an obvious one...).
    */
    if( TA_GetCompatibility() == TA_COMPATIBILITY_DEFAULT )
    {
    today = startIdx-lookbackTotal;
    i = optInTimePeriod;
    tempReal = 0.0;
    while( i-- > 0 )
    tempReal += inReal[today++];

    prevMA = tempReal / optInTimePeriod;
    }
    else
    {
    prevMA = inReal[0];
    today = 1;

    /* !!! Tradestation not supported yet.
    case TA_MA_TRADESTATION:
    prevMA = inReal[startIdx-1];
    if( optInTimePeriod == 1 )
    *outBegIdx_0 = 1;
    else
    *outBegIdx_0 = 3;
    */
    }

    /* At this point, prevMA is the first EMA (the seed for
    * the rest).
    * 'today' keep track of where the processing is within the
    * input.
    */

    /* Skip the unstable period. Do the processing
    * but do not write it in the output.
    */
    while( today <= startIdx )
    prevMA = ((inReal[today++]-prevMA)*optInK_1) + prevMA;

    /* Write the first value. */
    outReal[0] = prevMA;
    outIdx = 1;

    /* Calculate the remaining range. */
    while( today <= endIdx )
    {
    prevMA = ((inReal[today++]-prevMA)*optInK_1) + prevMA;
    outReal[outIdx++] = prevMA;
    }

    *outNBElement = outIdx;

    return TA_SUCCESS;
}
