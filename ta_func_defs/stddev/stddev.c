int stddev_lookback(int           optInTimePeriod,                                               double        optInNbDev)
{
    /* Lookback is driven by the variance. */
    return var_lookback( optInTimePeriod, optInNbDev );
}

TA_RetCode stddev(int startIdx, int endIdx, const double inReal[], int optInTimePeriod, double optInNbDev, int *outBegIdx, int *outNBElement, double outReal[])
{
    int i;
    ENUM_DECLARATION(RetCode) retCode;
    double tempReal;



    /* Calculate the variance. */
    retCode = var( startIdx, endIdx,
    inReal, optInTimePeriod,
    outBegIdx, outNBElement, outReal );

    if( retCode != TA_SUCCESS )
    return retCode;

    /* Calculate the square root of each variance, this
    * is the standard deviation.
    *
    * Multiply also by the ratio specified.
    */
    if( optInNbDev != 1.0 )
    {
    for( i=0; i < (int)*outNBElement; i++ )
    {
    tempReal = outReal[i];
    if( !TA_IS_ZERO_OR_NEG(tempReal) )
    outReal[i] = std_sqrt(tempReal) * optInNbDev;
    else
    outReal[i] = (double)0.0;
    }
    }
    else
    {
    for( i=0; i < (int)*outNBElement; i++ )
    {
    tempReal = outReal[i];
    if( !TA_IS_ZERO_OR_NEG(tempReal) )
    outReal[i] = std_sqrt(tempReal);
    else
    outReal[i] = (double)0.0;
    }
    }

    return TA_SUCCESS;
}
