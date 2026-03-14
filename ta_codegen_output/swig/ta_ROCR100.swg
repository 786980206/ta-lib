/*
 * TA_ROCR100 - Rate of change ratio 100 scale: (price/prevPrice)*100
 *
 * Input  = double
 * Output = double
 *
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 1 to 100000)
 *
 */
TA_RetCode TA_ROCR100( int           START_IDX,
                       int           END_IDX,
                       const double *IN_ARRAY /* inReal */,
                       int           OPT_INT /* optInTimePeriod */, /* From 1 to 100000 */
                       int          *BEG_IDX,
                       int          *OUT_SIZE,
                       double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_ROCR100_Logic( int           START_IDX,
                             int           END_IDX,
                             const double *IN_ARRAY /* inReal */,
                             int           OPT_INT /* optInTimePeriod */, /* From 1 to 100000 */
                             int          *BEG_IDX,
                             int          *OUT_SIZE,
                             double       *OUT_ARRAY /* outReal */ );

int TA_ROCR100_Lookback( int           optInTimePeriod  /* From 1 to 100000 */ );

