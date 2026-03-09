int adxr_lookback(int           optInTimePeriod)
{
    if( optInTimePeriod > 1 )
    return optInTimePeriod + adx_lookback( optInTimePeriod) - 1;
    else
    return 3;
}

TA_RetCode adxr(int startIdx, int endIdx, const double inHigh[], const double inLow[], const double inClose[], int optInTimePeriod, int *outBegIdx, int *outNBElement, double outReal[])
{
    ARRAY_REF( adx );
    int adxrLookback, i, j, outIdx, nbElement;
    ENUM_DECLARATION(RetCode) retCode;



    /* Original implementation from Wilder's book was doing some integer
    * rounding in its calculations.
    *
    * This was understandable in the context that at the time the book
    * was written, most user were doing the calculation by hand.
    *
    * For a computer, rounding is unnecessary (and even problematic when inputs
    * are close to 1).
    *
    * TA-Lib does not do the rounding. Still, if you want to reproduce Wilder's examples,
    * you can comment out the following #undef/#define and rebuild the library.
    */
    #undef  round_pos
    #define round_pos(x) (x)

    /* Move up the start index if there is not
    * enough initial data.
    * Always one price bar gets consumed.
    */
    adxrLookback = adxr_lookback( optInTimePeriod );

    if( startIdx < adxrLookback )
    startIdx = adxrLookback;

    /* Make sure there is still something to evaluate. */
    if( startIdx > endIdx )
    {
    *outBegIdx = 0;
    *outNBElement = 0;
    return TA_SUCCESS;
    }

    ARRAY_ALLOC( adx, endIdx-startIdx+optInTimePeriod );
    if( !adx )
    return TA_ALLOC_ERR;

    retCode = adx( startIdx-(optInTimePeriod-1), endIdx,
    inHigh, inLow, inClose,
    optInTimePeriod, outBegIdx, outNBElement, adx );

    if( retCode != TA_SUCCESS )
    {
    ARRAY_FREE( adx );
    return retCode;
    }

    i = optInTimePeriod-1;
    j = 0;
    outIdx = 0;
    nbElement = endIdx-startIdx+2;
    while( --nbElement != 0 )
    outReal[outIdx++] = round_pos( (adx[i++]+adx[j++])/2.0 );

    ARRAY_FREE( adx );

    *outBegIdx    = startIdx;
    *outNBElement = outIdx;

    return TA_SUCCESS;
}
