/*
 * TA_ATR - Average True Range
 *
 * Input  = double, double, double
 * Output = double
 *
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 1 to 100000)
 *
 */
TA_RetCode TA_ATR( int           START_IDX,
                   int           END_IDX,
                   const double *IN_ARRAY /* inHigh */,
                   const double *IN_ARRAY /* inLow */,
                   const double *IN_ARRAY /* inClose */,
                   int           OPT_INT /* optInTimePeriod */, /* From 1 to 100000 */
                   int          *BEG_IDX,
                   int          *OUT_SIZE,
                   double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_ATR_Logic( int           START_IDX,
                         int           END_IDX,
                         const double *IN_ARRAY /* inHigh */,
                         const double *IN_ARRAY /* inLow */,
                         const double *IN_ARRAY /* inClose */,
                         int           OPT_INT /* optInTimePeriod */, /* From 1 to 100000 */
                         int          *BEG_IDX,
                         int          *OUT_SIZE,
                         double       *OUT_ARRAY /* outReal */ );

int TA_ATR_Lookback( int           optInTimePeriod  /* From 1 to 100000 */ );

