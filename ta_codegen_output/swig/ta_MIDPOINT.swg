/*
 * TA_MIDPOINT - MidPoint over period
 *
 * Input  = double
 * Output = double
 *
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 2 to 100000)
 *
 */
TA_RetCode TA_MIDPOINT( int           START_IDX,
                        int           END_IDX,
                        const double *IN_ARRAY /* inReal */,
                        int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                        int          *BEG_IDX,
                        int          *OUT_SIZE,
                        double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_MIDPOINT_Logic( int           START_IDX,
                              int           END_IDX,
                              const double *IN_ARRAY /* inReal */,
                              int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                              int          *BEG_IDX,
                              int          *OUT_SIZE,
                              double       *OUT_ARRAY /* outReal */ );

int TA_MIDPOINT_Lookback( int           optInTimePeriod  /* From 2 to 100000 */ );

