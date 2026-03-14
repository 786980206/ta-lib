/*
 * TA_ULTOSC - Ultimate Oscillator
 *
 * Input  = double, double, double
 * Output = double
 *
 * Optional Parameters
 * -------------------
 * optInTimePeriod1:(From 1 to 100000)
 * optInTimePeriod2:(From 1 to 100000)
 * optInTimePeriod3:(From 1 to 100000)
 *
 */
TA_RetCode TA_ULTOSC( int           START_IDX,
                      int           END_IDX,
                      const double *IN_ARRAY /* inHigh */,
                      const double *IN_ARRAY /* inLow */,
                      const double *IN_ARRAY /* inClose */,
                      int           OPT_INT /* optInTimePeriod1 */, /* From 1 to 100000 */
                      int           OPT_INT /* optInTimePeriod2 */, /* From 1 to 100000 */
                      int           OPT_INT /* optInTimePeriod3 */, /* From 1 to 100000 */
                      int          *BEG_IDX,
                      int          *OUT_SIZE,
                      double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_ULTOSC_Logic( int           START_IDX,
                            int           END_IDX,
                            const double *IN_ARRAY /* inHigh */,
                            const double *IN_ARRAY /* inLow */,
                            const double *IN_ARRAY /* inClose */,
                            int           OPT_INT /* optInTimePeriod1 */, /* From 1 to 100000 */
                            int           OPT_INT /* optInTimePeriod2 */, /* From 1 to 100000 */
                            int           OPT_INT /* optInTimePeriod3 */, /* From 1 to 100000 */
                            int          *BEG_IDX,
                            int          *OUT_SIZE,
                            double       *OUT_ARRAY /* outReal */ );

int TA_ULTOSC_Lookback( int           optInTimePeriod1  /* From 1 to 100000 */, int           optInTimePeriod2  /* From 1 to 100000 */, int           optInTimePeriod3  /* From 1 to 100000 */ );

