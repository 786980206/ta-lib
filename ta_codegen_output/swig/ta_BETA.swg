/*
 * TA_BETA - Beta
 *
 * Input  = double, double
 * Output = double
 *
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 1 to 100000)
 *
 */
TA_RetCode TA_BETA( int           START_IDX,
                    int           END_IDX,
                    const double *IN_ARRAY /* inReal0 */,
                    const double *IN_ARRAY /* inReal1 */,
                    int           OPT_INT /* optInTimePeriod */, /* From 1 to 100000 */
                    int          *BEG_IDX,
                    int          *OUT_SIZE,
                    double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_BETA_Logic( int           START_IDX,
                          int           END_IDX,
                          const double *IN_ARRAY /* inReal0 */,
                          const double *IN_ARRAY /* inReal1 */,
                          int           OPT_INT /* optInTimePeriod */, /* From 1 to 100000 */
                          int          *BEG_IDX,
                          int          *OUT_SIZE,
                          double       *OUT_ARRAY /* outReal */ );

int TA_BETA_Lookback( int           optInTimePeriod  /* From 1 to 100000 */ );

