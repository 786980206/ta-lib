/*
 * TA_MINMAXINDEX - Indexes of lowest and highest values over a specified period
 *
 * Input  = double
 * Output = int, int
 *
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 2 to 100000)
 *
 */
TA_RetCode TA_MINMAXINDEX( int           START_IDX,
                           int           END_IDX,
                           const double *IN_ARRAY /* inReal */,
                           int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                           int          *BEG_IDX,
                           int          *OUT_SIZE,
                           int          *OUT_ARRAY /* outMinIdx */,
                           int          *OUT_ARRAY /* outMaxIdx */ );

TA_RetCode TA_MINMAXINDEX_Logic( int           START_IDX,
                                 int           END_IDX,
                                 const double *IN_ARRAY /* inReal */,
                                 int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                                 int          *BEG_IDX,
                                 int          *OUT_SIZE,
                                 int          *OUT_ARRAY /* outMinIdx */,
                                 int          *OUT_ARRAY /* outMaxIdx */ );

int TA_MINMAXINDEX_Lookback( int           optInTimePeriod  /* From 2 to 100000 */ );

