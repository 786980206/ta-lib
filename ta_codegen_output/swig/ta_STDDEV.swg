/*
 * TA_STDDEV - Standard Deviation
 *
 * Input  = double
 * Output = double
 *
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 2 to 100000)
 * optInNbDev:(From -2147483648 to 2147483647)
 *
 */
TA_RetCode TA_STDDEV( int           START_IDX,
                      int           END_IDX,
                      const double *IN_ARRAY /* inReal */,
                      int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                      double           OPT_REAL /* optInNbDev */, /* From -2147483648 to 2147483647 */
                      int          *BEG_IDX,
                      int          *OUT_SIZE,
                      double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_STDDEV_Logic( int           START_IDX,
                            int           END_IDX,
                            const double *IN_ARRAY /* inReal */,
                            int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                            double           OPT_REAL /* optInNbDev */, /* From -2147483648 to 2147483647 */
                            int          *BEG_IDX,
                            int          *OUT_SIZE,
                            double       *OUT_ARRAY /* outReal */ );

int TA_STDDEV_Lookback( int           optInTimePeriod  /* From 2 to 100000 */, double           optInNbDev  /* From -2147483648 to 2147483647 */ );

