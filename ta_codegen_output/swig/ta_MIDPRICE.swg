/*
 * TA_MIDPRICE - Midpoint Price over period
 *
 * Input  = double, double
 * Output = double
 *
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 2 to 100000)
 *
 */
TA_RetCode TA_MIDPRICE( int           START_IDX,
                        int           END_IDX,
                        const double *IN_ARRAY /* inHigh */,
                        const double *IN_ARRAY /* inLow */,
                        int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                        int          *BEG_IDX,
                        int          *OUT_SIZE,
                        double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_MIDPRICE_Logic( int           START_IDX,
                              int           END_IDX,
                              const double *IN_ARRAY /* inHigh */,
                              const double *IN_ARRAY /* inLow */,
                              int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                              int          *BEG_IDX,
                              int          *OUT_SIZE,
                              double       *OUT_ARRAY /* outReal */ );

int TA_MIDPRICE_Lookback( int           optInTimePeriod  /* From 2 to 100000 */ );

