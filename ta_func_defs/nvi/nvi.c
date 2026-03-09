int nvi_lookback(void)
{
    return 0;
}

TA_RetCode nvi(int startIdx, int endIdx, const double inClose[], const int inVolume[], int *outBegIdx, int *outNBElement, double outReal[])
{
    /* Default return values */
    *outBegIdx    = 0;
    *outNBElement = 0;

    return TA_SUCCESS;
}
