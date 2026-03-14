/*
 * TA_MININDEX - Index of lowest value over a specified period
 *
 * Input  = double
 * Output = int
 *
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 2 to 100000)
 *
 */
TA_RetCode TA_MININDEX( int           START_IDX,
                        int           END_IDX,
                        const double *IN_ARRAY /* inReal */,
                        int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                        int          *BEG_IDX,
                        int          *OUT_SIZE,
                        int          *OUT_ARRAY /* outInteger */ );

TA_RetCode TA_MININDEX_Logic( int           START_IDX,
                              int           END_IDX,
                              const double *IN_ARRAY /* inReal */,
                              int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                              int          *BEG_IDX,
                              int          *OUT_SIZE,
                              int          *OUT_ARRAY /* outInteger */ );

int TA_MININDEX_Lookback( int           optInTimePeriod  /* From 2 to 100000 */ );

