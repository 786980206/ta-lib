int mfi_lookback(int           optInTimePeriod)
{
    return optInTimePeriod + TA_GetUnstablePeriod(TA_FUNC_UNST_MFI);
}

TA_RetCode mfi(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], const double inVolume[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[])
{
    double posSumMF, negSumMF, prevValue;
    double tempValue1, tempValue2;
    int lookbackTotal, outIdx, i, today;

    MoneyFlow mflow[50]; int mflow_Idx = 0; /* Id, Type, Static Size */



    memset(mflow, 0, (optInTimePeriod) * sizeof(MoneyFlow)); mflow_Idx = 0;

    *outBegIdx = 0;
    *outNBElement = 0;

    /* Adjust startIdx to account for the lookback period. */
    lookbackTotal = optInTimePeriod + TA_GetUnstablePeriod(TA_FUNC_UNST_MFI);

    if( startIdx < lookbackTotal )
    startIdx = lookbackTotal;

    /* Make sure there is still something to evaluate. */
    if( startIdx > endIdx )
    {
    /* circular buffer cleanup (stack-allocated, no-op) */
    return TA_SUCCESS;
    }

    outIdx = 0; /* Index into the output. */

    /* Accumulate the positive and negative money flow
    * among the initial period.
    */
    today = startIdx-lookbackTotal;
    prevValue = (inHigh[today]+inLow[today]+inClose[today])/3.0;

    posSumMF = 0.0;
    negSumMF = 0.0;
    today++;
    for( i=optInTimePeriod; i > 0; i-- )
    {
    tempValue1 = (inHigh[today]+inLow[today]+inClose[today])/3.0;
    tempValue2 = tempValue1 - prevValue;
    prevValue  = tempValue1;
    tempValue1 *= inVolume[today++];
    if( tempValue2 < 0 )
    {
    mflow[mflow_Idx].negative = tempValue1;
    negSumMF += tempValue1;
    mflow[mflow_Idx].positive = 0.0;
    }
    else if( tempValue2 > 0 )
    {
    mflow[mflow_Idx].positive = tempValue1;
    posSumMF += tempValue1;
    mflow[mflow_Idx].negative = 0.0;
    }
    else
    {
    mflow[mflow_Idx].positive = 0.0;
    mflow[mflow_Idx].negative = 0.0;
    }

    CIRCBUF_NEXT(mflow);
    }

    /* The following two equations are equivalent:
    *    MFI = 100 - (100 / 1 + (posSumMF/negSumMF))
    *    MFI = 100 * (posSumMF/(posSumMF+negSumMF))
    * The second equation is used here for speed optimization.
    */
    if( today > startIdx )
    {
    tempValue1 = posSumMF+negSumMF;
    if( tempValue1 < 1.0 )
    outReal[outIdx++] = 0.0;
    else
    outReal[outIdx++] = 100.0*(posSumMF/tempValue1);
    }
    else
    {
    /* Skip the unstable period. Do the processing
    * but do not write it in the output.
    */
    while( today < startIdx )
    {
    posSumMF -= mflow[mflow_Idx].positive;
    negSumMF -= mflow[mflow_Idx].negative;

    tempValue1 = (inHigh[today]+inLow[today]+inClose[today])/3.0;
    tempValue2 = tempValue1 - prevValue;
    prevValue  = tempValue1;
    tempValue1 *= inVolume[today++];
    if( tempValue2 < 0 )
    {
    mflow[mflow_Idx].negative = tempValue1;
    negSumMF += tempValue1;
    mflow[mflow_Idx].positive = 0.0;
    }
    else if( tempValue2 > 0 )
    {
    mflow[mflow_Idx].positive = tempValue1;
    posSumMF += tempValue1;
    mflow[mflow_Idx].negative = 0.0;
    }
    else
    {
    mflow[mflow_Idx].positive = 0.0;
    mflow[mflow_Idx].negative = 0.0;
    }

    CIRCBUF_NEXT(mflow);
    }
    }

    /* Unstable period skipped... now continue
    * processing if needed.
    */
    while( today <= endIdx )
    {
    posSumMF -= mflow[mflow_Idx].positive;
    negSumMF -= mflow[mflow_Idx].negative;

    tempValue1 = (inHigh[today]+inLow[today]+inClose[today])/3.0;
    tempValue2 = tempValue1 - prevValue;
    prevValue  = tempValue1;
    tempValue1 *= inVolume[today++];
    if( tempValue2 < 0 )
    {
    mflow[mflow_Idx].negative = tempValue1;
    negSumMF += tempValue1;
    mflow[mflow_Idx].positive = 0.0;
    }
    else if( tempValue2 > 0 )
    {
    mflow[mflow_Idx].positive = tempValue1;
    posSumMF += tempValue1;
    mflow[mflow_Idx].negative = 0.0;
    }
    else
    {
    mflow[mflow_Idx].positive = 0.0;
    mflow[mflow_Idx].negative = 0.0;
    }

    tempValue1 = posSumMF+negSumMF;
    if( tempValue1 < 1.0 )
    outReal[outIdx++] = 0.0;
    else
    outReal[outIdx++] = 100.0*(posSumMF/tempValue1);

    CIRCBUF_NEXT(mflow);
    }

    /* circular buffer cleanup (stack-allocated, no-op) */

    *outBegIdx = startIdx;
    *outNBElement = outIdx;

    return TA_SUCCESS;
}
