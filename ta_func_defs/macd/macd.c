int macd_lookback(int           optInFastPeriod,                                             int           optInSlowPeriod,                                             int           optInSignalPeriod)
{
    int tempInteger;
    
    
    
    /* The lookback is driven by the signal line output.
    *
    * (must also account for the initial data consume
    *  by the slow period).
    */
    
    /* Make sure slow is really slower than
    * the fast period! if not, swap...
    */
    if( optInSlowPeriod < optInFastPeriod )
    {
    /* swap */
    tempInteger       = optInSlowPeriod;
    optInSlowPeriod = optInFastPeriod;
    optInFastPeriod = tempInteger;
    }
    
    return   ema_lookback( optInSlowPeriod   )
    + ema_lookback( optInSignalPeriod );
}

TA_RetCode macd(int startIdx, int endIdx, const double inReal[], int optInFastPeriod, int optInSlowPeriod, int optInSignalPeriod_2, int *outBegIdx, int *outNBElement, double outMACD[], double outMACDSignal[], double outMACDHist[])
{
    ARRAY_REF(slowEMABuffer);
    ARRAY_REF(fastEMABuffer);
    double k1, k2;
    ENUM_DECLARATION(RetCode) retCode;
    int tempInteger;
    VALUE_HANDLE_INT(outBegIdx1);
    VALUE_HANDLE_INT(outNbElement1);
    VALUE_HANDLE_INT(outBegIdx2);
    VALUE_HANDLE_INT(outNbElement2);
    int lookbackTotal, lookbackSignal;
    int i;

    /* !!! A lot of speed optimization could be done
    * !!! with this function.
    * !!!
    * !!! A better approach would be to use ema
    * !!! just to get the seeding values for the
    * !!! fast and slow EMA. Then process the difference
    * !!! in an allocated buffer until enough data is
    * !!! available for the first signal value.
    * !!! From that point all the processing can
    * !!! be done in a tight loop.
    * !!!
    * !!! That approach will have the following
    * !!! advantage:
    * !!!   1) One mem allocation needed instead of two.
    * !!!   2) The mem allocation size will be only the
    * !!!      signal lookback period instead of the
    * !!!      whole range of data.
    * !!!   3) Processing will be done in a tight loop.
    * !!!      allowing to avoid a lot of memory store-load
    * !!!      operation.
    * !!!   4) The memcpy at the end will be eliminated!
    * !!!
    * !!! If only I had time....
    */

    /* Make sure slow is really slower than
    * the fast period! if not, swap...
    */
    if( optInSlowPeriod < optInFastPeriod )
    {
    /* swap */
    tempInteger       = optInSlowPeriod;
    optInSlowPeriod = optInFastPeriod;
    optInFastPeriod = tempInteger;
    }

    /* Catch special case for fix 26/12 MACD. */
    if( optInSlowPeriod != 0 )
    k1 = TA_PER_TO_K(optInSlowPeriod);
    else
    {
    optInSlowPeriod = 26;
    k1 = (double)0.075; /* Fix 26 */
    }

    if( optInFastPeriod != 0 )
    k2 = TA_PER_TO_K(optInFastPeriod);
    else
    {
    optInFastPeriod = 12;
    k2 = (double)0.15; /* Fix 12 */
    }

    lookbackSignal = ema_lookback( optInSignalPeriod_2 );

    /* Move up the start index if there is not
    * enough initial data.
    */
    lookbackTotal =  lookbackSignal;
    lookbackTotal += ema_lookback( optInSlowPeriod );

    if( startIdx < lookbackTotal )
    startIdx = lookbackTotal;

    /* Make sure there is still something to evaluate. */
    if( startIdx > endIdx )
    {
    *outBegIdx = 0;
    *outNBElement = 0;
    return TA_SUCCESS;
    }

    /* Allocate intermediate buffer for fast/slow EMA. */
    tempInteger = (endIdx-startIdx)+1+lookbackSignal;
    ARRAY_ALLOC( fastEMABuffer, tempInteger );
    if( !fastEMABuffer )
    {
    *outBegIdx = 0;
    *outNBElement = 0;
    return TA_ALLOC_ERR;
    }

    ARRAY_ALLOC( slowEMABuffer, tempInteger );
    if( !slowEMABuffer )
    {
    *outBegIdx = 0;
    *outNBElement = 0;
    ARRAY_FREE( fastEMABuffer );
    return TA_ALLOC_ERR;
    }

    /* Calculate the slow EMA.
    *
    * Move back the startIdx to get enough data
    * for the signal period. That way, once the
    * signal calculation is done, all the output
    * will start at the requested 'startIdx'.
    */
    tempInteger = startIdx-lookbackSignal;
    retCode = ema( tempInteger, endIdx,
    inReal, optInSlowPeriod, k1,
    VALUE_HANDLE_OUT(outBegIdx1), VALUE_HANDLE_OUT(outNbElement1), slowEMABuffer );

    if( retCode != TA_SUCCESS )
    {
    *outBegIdx = 0;
    *outNBElement = 0;
    ARRAY_FREE( fastEMABuffer );
    ARRAY_FREE( slowEMABuffer );
    return retCode;
    }

    /* Calculate the fast EMA. */
    retCode = ema( tempInteger, endIdx,
    inReal, optInFastPeriod, k2,
    VALUE_HANDLE_OUT(outBegIdx2), VALUE_HANDLE_OUT(outNbElement2), fastEMABuffer );

    if( retCode != TA_SUCCESS )
    {
    *outBegIdx = 0;
    *outNBElement = 0;
    ARRAY_FREE( fastEMABuffer );
    ARRAY_FREE( slowEMABuffer );
    return retCode;
    }

    /* Parano tests. Will be removed eventually. */
    if( (VALUE_HANDLE_GET(outBegIdx1) != tempInteger) ||
    (VALUE_HANDLE_GET(outBegIdx2) != tempInteger) ||
    (VALUE_HANDLE_GET(outNbElement1) != VALUE_HANDLE_GET(outNbElement2)) ||
    (VALUE_HANDLE_GET(outNbElement1) != (endIdx-startIdx)+1+lookbackSignal) )
    {
    *outBegIdx = 0;
    *outNBElement = 0;
    ARRAY_FREE( fastEMABuffer );
    ARRAY_FREE( slowEMABuffer );
    return TA_INTERNAL_ERROR(119);
    }

    /* Calculate (fast EMA) - (slow EMA). */
    for( i=0; i < VALUE_HANDLE_GET(outNbElement1); i++ )
    fastEMABuffer[i] = fastEMABuffer[i] - slowEMABuffer[i];


    /* Copy the result into the output for the caller. */
    TA_ARRAY_COPY( outMACD, 0, fastEMABuffer, lookbackSignal, (endIdx-startIdx)+1 );

    /* Calculate the signal/trigger line. */
    retCode = ema( 0, VALUE_HANDLE_GET(outNbElement1)-1,
    fastEMABuffer, optInSignalPeriod_2, TA_PER_TO_K(optInSignalPeriod_2),
    VALUE_HANDLE_OUT(outBegIdx2), VALUE_HANDLE_OUT(outNbElement2), outMACDSignal );


    ARRAY_FREE( fastEMABuffer );
    ARRAY_FREE( slowEMABuffer );

    if( retCode != TA_SUCCESS )
    {
    *outBegIdx = 0;
    *outNBElement = 0;
    return retCode;
    }

    /* Calculate the histogram. */
    for( i=0; i < VALUE_HANDLE_GET(outNbElement2); i++ )
    outMACDHist[i] = outMACD[i]-outMACDSignal[i];


    /* All done! Indicate the output limits and return success. */
    *outBegIdx     = startIdx;
    *outNBElement  = VALUE_HANDLE_GET(outNbElement2);

    return TA_SUCCESS;
}
