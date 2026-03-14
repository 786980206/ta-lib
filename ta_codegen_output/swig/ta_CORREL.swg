/*
 * TA_CORREL - Pearson's Correlation Coefficient (r)
 *
 * Input  = double, double
 * Output = double
 *
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 1 to 100000)
 *
 */
TA_RetCode TA_CORREL( int           START_IDX,
                      int           END_IDX,
                      const double *IN_ARRAY /* inReal0 */,
                      const double *IN_ARRAY /* inReal1 */,
                      int           OPT_INT /* optInTimePeriod */, /* From 1 to 100000 */
                      int          *BEG_IDX,
                      int          *OUT_SIZE,
                      double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_CORREL_Logic( int           START_IDX,
                            int           END_IDX,
                            const double *IN_ARRAY /* inReal0 */,
                            const double *IN_ARRAY /* inReal1 */,
                            int           OPT_INT /* optInTimePeriod */, /* From 1 to 100000 */
                            int          *BEG_IDX,
                            int          *OUT_SIZE,
                            double       *OUT_ARRAY /* outReal */ );

int TA_CORREL_Lookback( int           optInTimePeriod  /* From 1 to 100000 */ );

