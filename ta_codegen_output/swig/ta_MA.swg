/*
 * TA_MA - Moving average
 *
 * Input  = double
 * Output = double
 *
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 1 to 100000)
 * optInMAType:
 *
 */
TA_RetCode TA_MA( int           START_IDX,
                  int           END_IDX,
                  const double *IN_ARRAY /* inReal */,
                  int           OPT_INT /* optInTimePeriod */, /* From 1 to 100000 */
                  int           OPT_INT /* optInMAType */,
                  int          *BEG_IDX,
                  int          *OUT_SIZE,
                  double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_MA_Logic( int           START_IDX,
                        int           END_IDX,
                        const double *IN_ARRAY /* inReal */,
                        int           OPT_INT /* optInTimePeriod */, /* From 1 to 100000 */
                        int           OPT_INT /* optInMAType */,
                        int          *BEG_IDX,
                        int          *OUT_SIZE,
                        double       *OUT_ARRAY /* outReal */ );

int TA_MA_Lookback( int           optInTimePeriod  /* From 1 to 100000 */, int           optInMAType );

