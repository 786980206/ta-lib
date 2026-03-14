/*
 * TA_MAXINDEX - Index of highest value over a specified period
 *
 * Input  = double
 * Output = int
 *
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 2 to 100000)
 *
 */
TA_RetCode TA_MAXINDEX( int           START_IDX,
                        int           END_IDX,
                        const double *IN_ARRAY /* inReal */,
                        int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                        int          *BEG_IDX,
                        int          *OUT_SIZE,
                        int          *OUT_ARRAY /* outInteger */ );

TA_RetCode TA_MAXINDEX_Logic( int           START_IDX,
                              int           END_IDX,
                              const double *IN_ARRAY /* inReal */,
                              int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                              int          *BEG_IDX,
                              int          *OUT_SIZE,
                              int          *OUT_ARRAY /* outInteger */ );

int TA_MAXINDEX_Lookback( int           optInTimePeriod  /* From 2 to 100000 */ );

