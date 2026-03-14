/*
 * TA_VAR - Variance
 *
 * Input  = double
 * Output = double
 *
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 1 to 100000)
 * optInNbDev:(From -2147483648 to 2147483647)
 *
 */
TA_RetCode TA_VAR( int           START_IDX,
                   int           END_IDX,
                   const double *IN_ARRAY /* inReal */,
                   int           OPT_INT /* optInTimePeriod */, /* From 1 to 100000 */
                   double           OPT_REAL /* optInNbDev */, /* From -2147483648 to 2147483647 */
                   int          *BEG_IDX,
                   int          *OUT_SIZE,
                   double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_VAR_Logic( int           START_IDX,
                         int           END_IDX,
                         const double *IN_ARRAY /* inReal */,
                         int           OPT_INT /* optInTimePeriod */, /* From 1 to 100000 */
                         double           OPT_REAL /* optInNbDev */, /* From -2147483648 to 2147483647 */
                         int          *BEG_IDX,
                         int          *OUT_SIZE,
                         double       *OUT_ARRAY /* outReal */ );

int TA_VAR_Lookback( int           optInTimePeriod  /* From 1 to 100000 */, double           optInNbDev  /* From -2147483648 to 2147483647 */ );

