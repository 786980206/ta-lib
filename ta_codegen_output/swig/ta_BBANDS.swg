/*
 * TA_BBANDS - Bollinger Bands
 *
 * Input  = double
 * Output = double, double, double
 *
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 2 to 100000)
 * optInNbDevUp:(From -2147483648 to 2147483647)
 * optInNbDevDn:(From -2147483648 to 2147483647)
 * optInMAType:
 *
 */
TA_RetCode TA_BBANDS( int           START_IDX,
                      int           END_IDX,
                      const double *IN_ARRAY /* inReal */,
                      int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                      double           OPT_REAL /* optInNbDevUp */, /* From -2147483648 to 2147483647 */
                      double           OPT_REAL /* optInNbDevDn */, /* From -2147483648 to 2147483647 */
                      int           OPT_INT /* optInMAType */,
                      int          *BEG_IDX,
                      int          *OUT_SIZE,
                      double       *OUT_ARRAY /* outRealUpperBand */,
                      double       *OUT_ARRAY /* outRealMiddleBand */,
                      double       *OUT_ARRAY /* outRealLowerBand */ );

TA_RetCode TA_BBANDS_Logic( int           START_IDX,
                            int           END_IDX,
                            const double *IN_ARRAY /* inReal */,
                            int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                            double           OPT_REAL /* optInNbDevUp */, /* From -2147483648 to 2147483647 */
                            double           OPT_REAL /* optInNbDevDn */, /* From -2147483648 to 2147483647 */
                            int           OPT_INT /* optInMAType */,
                            int          *BEG_IDX,
                            int          *OUT_SIZE,
                            double       *OUT_ARRAY /* outRealUpperBand */,
                            double       *OUT_ARRAY /* outRealMiddleBand */,
                            double       *OUT_ARRAY /* outRealLowerBand */ );

int TA_BBANDS_Lookback( int           optInTimePeriod  /* From 2 to 100000 */, double           optInNbDevUp  /* From -2147483648 to 2147483647 */, double           optInNbDevDn  /* From -2147483648 to 2147483647 */, int           optInMAType );

