/*
 * TA_SAR - Parabolic SAR
 *
 * Input  = double, double
 * Output = double
 *
 * Optional Parameters
 * -------------------
 * optInAcceleration:(From 0 to 2147483647)
 * optInMaximum:(From 0 to 2147483647)
 *
 */
TA_RetCode TA_SAR( int           START_IDX,
                   int           END_IDX,
                   const double *IN_ARRAY /* inHigh */,
                   const double *IN_ARRAY /* inLow */,
                   double           OPT_REAL /* optInAcceleration */, /* From 0 to 2147483647 */
                   double           OPT_REAL /* optInMaximum */, /* From 0 to 2147483647 */
                   int          *BEG_IDX,
                   int          *OUT_SIZE,
                   double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_SAR_Logic( int           START_IDX,
                         int           END_IDX,
                         const double *IN_ARRAY /* inHigh */,
                         const double *IN_ARRAY /* inLow */,
                         double           OPT_REAL /* optInAcceleration */, /* From 0 to 2147483647 */
                         double           OPT_REAL /* optInMaximum */, /* From 0 to 2147483647 */
                         int          *BEG_IDX,
                         int          *OUT_SIZE,
                         double       *OUT_ARRAY /* outReal */ );

int TA_SAR_Lookback( double           optInAcceleration  /* From 0 to 2147483647 */, double           optInMaximum  /* From 0 to 2147483647 */ );

