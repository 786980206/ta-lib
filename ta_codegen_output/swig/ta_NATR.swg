/*
 * TA_NATR - Normalized Average True Range
 *
 * Input  = double, double, double
 * Output = double
 *
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 1 to 100000)
 *
 */
TA_RetCode TA_NATR( int           START_IDX,
                    int           END_IDX,
                    const double *IN_ARRAY /* inHigh */,
                    const double *IN_ARRAY /* inLow */,
                    const double *IN_ARRAY /* inClose */,
                    int           OPT_INT /* optInTimePeriod */, /* From 1 to 100000 */
                    int          *BEG_IDX,
                    int          *OUT_SIZE,
                    double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_NATR_Logic( int           START_IDX,
                          int           END_IDX,
                          const double *IN_ARRAY /* inHigh */,
                          const double *IN_ARRAY /* inLow */,
                          const double *IN_ARRAY /* inClose */,
                          int           OPT_INT /* optInTimePeriod */, /* From 1 to 100000 */
                          int          *BEG_IDX,
                          int          *OUT_SIZE,
                          double       *OUT_ARRAY /* outReal */ );

int TA_NATR_Lookback( int           optInTimePeriod  /* From 1 to 100000 */ );

