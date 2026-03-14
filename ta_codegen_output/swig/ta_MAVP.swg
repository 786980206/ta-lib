/*
 * TA_MAVP - Moving average with variable period
 *
 * Input  = double, double
 * Output = double
 *
 * Optional Parameters
 * -------------------
 * optInMinPeriod:(From 2 to 100000)
 * optInMaxPeriod:(From 2 to 100000)
 * optInMAType:
 *
 */
TA_RetCode TA_MAVP( int           START_IDX,
                    int           END_IDX,
                    const double *IN_ARRAY /* inReal */,
                    const double *IN_ARRAY /* inPeriods */,
                    int           OPT_INT /* optInMinPeriod */, /* From 2 to 100000 */
                    int           OPT_INT /* optInMaxPeriod */, /* From 2 to 100000 */
                    int           OPT_INT /* optInMAType */,
                    int          *BEG_IDX,
                    int          *OUT_SIZE,
                    double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_MAVP_Logic( int           START_IDX,
                          int           END_IDX,
                          const double *IN_ARRAY /* inReal */,
                          const double *IN_ARRAY /* inPeriods */,
                          int           OPT_INT /* optInMinPeriod */, /* From 2 to 100000 */
                          int           OPT_INT /* optInMaxPeriod */, /* From 2 to 100000 */
                          int           OPT_INT /* optInMAType */,
                          int          *BEG_IDX,
                          int          *OUT_SIZE,
                          double       *OUT_ARRAY /* outReal */ );

int TA_MAVP_Lookback( int           optInMinPeriod  /* From 2 to 100000 */, int           optInMaxPeriod  /* From 2 to 100000 */, int           optInMAType );

