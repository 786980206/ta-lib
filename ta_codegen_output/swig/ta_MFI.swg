/*
 * TA_MFI - Money Flow Index
 *
 * Input  = double, double, double, double
 * Output = double
 *
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 2 to 100000)
 *
 */
TA_RetCode TA_MFI( int           START_IDX,
                   int           END_IDX,
                   const double *IN_ARRAY /* inHigh */,
                   const double *IN_ARRAY /* inLow */,
                   const double *IN_ARRAY /* inClose */,
                   const double *IN_ARRAY /* inVolume */,
                   int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                   int          *BEG_IDX,
                   int          *OUT_SIZE,
                   double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_MFI_Logic( int           START_IDX,
                         int           END_IDX,
                         const double *IN_ARRAY /* inHigh */,
                         const double *IN_ARRAY /* inLow */,
                         const double *IN_ARRAY /* inClose */,
                         const double *IN_ARRAY /* inVolume */,
                         int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                         int          *BEG_IDX,
                         int          *OUT_SIZE,
                         double       *OUT_ARRAY /* outReal */ );

int TA_MFI_Lookback( int           optInTimePeriod  /* From 2 to 100000 */ );

