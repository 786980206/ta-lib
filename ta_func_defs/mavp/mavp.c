int mavp_lookback(int           optInMinPeriod,                                             int           optInMaxPeriod,                                             TA_MAType     optInMAType)
{
    return ma_lookback(optInMaxPeriod, optInMAType);
}

TA_RetCode mavp(int startIdx, int endIdx, const double inReal[], const double inPeriods[], int optInMinPeriod, int optInMaxPeriod, TA_MAType optInMAType, int *outBegIdx, int *outNBElement, double outReal[])
{
    int i, j, lookbackTotal, outputSize, tempInt, curPeriod;
    ARRAY_INT_REF(localPeriodArray);
    ARRAY_REF(localOutputArray);
    VALUE_HANDLE_INT(localBegIdx);
    VALUE_HANDLE_INT(localNbElement);
    ENUM_DECLARATION(RetCode) retCode;



    /* Identify the minimum number of price bar needed
    * to calculate at least one output.
    */
    lookbackTotal = ma_lookback(optInMaxPeriod,optInMAType);

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

    /* Calculate exact output size */
    if( lookbackTotal > startIdx )
    tempInt = lookbackTotal;
    else
    tempInt = startIdx;
    if( tempInt > endIdx )
    {
    /* No output */
    *outBegIdx = 0;
    *outNBElement = 0;
    return TA_SUCCESS;
    }
    outputSize = endIdx - tempInt + 1;

    /* Allocate intermediate local buffer. */
    ARRAY_ALLOC(localOutputArray,outputSize);
    ARRAY_INT_ALLOC(localPeriodArray,outputSize);

    /* Copy caller array of period into local buffer.
    * At the same time, truncate to min/max.
    */
    for( i=0; i < outputSize; i++ )
    {
    tempInt = (int)(inPeriods[startIdx+i]);
    if( tempInt < optInMinPeriod )
    tempInt = optInMinPeriod;
    else if( tempInt > optInMaxPeriod )
    tempInt = optInMaxPeriod;
    localPeriodArray[i] = tempInt;
    }

    /* Process each element of the input.
    * For each possible period value, the MA is calculated
    * only once.
    * The outReal is then fill up for all element with
    * the same period.
    * A local flag (value 0) is set in localPeriodArray
    * to avoid doing a second time the same calculation.
    */
    for( i=0; i < outputSize; i++ )
    {
    curPeriod = localPeriodArray[i];
    if( curPeriod != 0 )
    {
    /* TODO: This portion of the function can be slightly speed
    *       optimized by making the function without unstable period
    *       start their calculation at 'startIdx+i' instead of startIdx.
    */

    /* Calculation of the MA required. */
    retCode = ma( startIdx, endIdx, inReal,
    curPeriod, optInMAType,
    VALUE_HANDLE_OUT(localBegIdx),VALUE_HANDLE_OUT(localNbElement),localOutputArray );

    if( retCode != TA_SUCCESS )
    {
    ARRAY_FREE(localOutputArray);
    ARRAY_INT_FREE(localPeriodArray);
    *outBegIdx = 0;
    *outNBElement = 0;
    return retCode;
    }

    outReal[i] = localOutputArray[i];
    for( j=i+1; j < outputSize; j++ )
    {
    if( localPeriodArray[j] == curPeriod )
    {
    localPeriodArray[j] = 0; /* Flag to avoid recalculation */
    outReal[j] = localOutputArray[j];
    }
    }
    }
    }

    ARRAY_FREE(localOutputArray);
    ARRAY_INT_FREE(localPeriodArray);

    /* Done. Inform the caller of the success. */
    *outBegIdx = startIdx;
    *outNBElement = outputSize;
    return TA_SUCCESS;
}
