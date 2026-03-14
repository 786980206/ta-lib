/*
 * TA_AROON - Aroon
 *
 * Input  = double, double
 * Output = double, double
 *
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 2 to 100000)
 *
 */
TA_RetCode TA_AROON( int           START_IDX,
                     int           END_IDX,
                     const double *IN_ARRAY /* inHigh */,
                     const double *IN_ARRAY /* inLow */,
                     int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                     int          *BEG_IDX,
                     int          *OUT_SIZE,
                     double       *OUT_ARRAY /* outAroonDown */,
                     double       *OUT_ARRAY /* outAroonUp */ );

TA_RetCode TA_AROON_Logic( int           START_IDX,
                           int           END_IDX,
                           const double *IN_ARRAY /* inHigh */,
                           const double *IN_ARRAY /* inLow */,
                           int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                           int          *BEG_IDX,
                           int          *OUT_SIZE,
                           double       *OUT_ARRAY /* outAroonDown */,
                           double       *OUT_ARRAY /* outAroonUp */ );

int TA_AROON_Lookback( int           optInTimePeriod  /* From 2 to 100000 */ );

