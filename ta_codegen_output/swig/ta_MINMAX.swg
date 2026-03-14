/*
 * TA_MINMAX - Lowest and highest values over a specified period
 *
 * Input  = double
 * Output = double, double
 *
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 2 to 100000)
 *
 */
TA_RetCode TA_MINMAX( int           START_IDX,
                      int           END_IDX,
                      const double *IN_ARRAY /* inReal */,
                      int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                      int          *BEG_IDX,
                      int          *OUT_SIZE,
                      double       *OUT_ARRAY /* outMin */,
                      double       *OUT_ARRAY /* outMax */ );

TA_RetCode TA_MINMAX_Logic( int           START_IDX,
                            int           END_IDX,
                            const double *IN_ARRAY /* inReal */,
                            int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                            int          *BEG_IDX,
                            int          *OUT_SIZE,
                            double       *OUT_ARRAY /* outMin */,
                            double       *OUT_ARRAY /* outMax */ );

int TA_MINMAX_Lookback( int           optInTimePeriod  /* From 2 to 100000 */ );

