/*
 * TA_T3 - Triple Exponential Moving Average (T3)
 *
 * Input  = double
 * Output = double
 *
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 2 to 100000)
 * optInVFactor:(From 0 to 1)
 *
 */
TA_RetCode TA_T3( int           START_IDX,
                  int           END_IDX,
                  const double *IN_ARRAY /* inReal */,
                  int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                  double           OPT_REAL /* optInVFactor */, /* From 0 to 1 */
                  int          *BEG_IDX,
                  int          *OUT_SIZE,
                  double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_T3_Logic( int           START_IDX,
                        int           END_IDX,
                        const double *IN_ARRAY /* inReal */,
                        int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                        double           OPT_REAL /* optInVFactor */, /* From 0 to 1 */
                        int          *BEG_IDX,
                        int          *OUT_SIZE,
                        double       *OUT_ARRAY /* outReal */ );

int TA_T3_Lookback( int           optInTimePeriod  /* From 2 to 100000 */, double           optInVFactor  /* From 0 to 1 */ );

