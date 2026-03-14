/*
 * TA_LINEARREG_ANGLE - Linear Regression Angle
 *
 * Input  = double
 * Output = double
 *
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 2 to 100000)
 *
 */
TA_RetCode TA_LINEARREG_ANGLE( int           START_IDX,
                               int           END_IDX,
                               const double *IN_ARRAY /* inReal */,
                               int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                               int          *BEG_IDX,
                               int          *OUT_SIZE,
                               double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_LINEARREG_ANGLE_Logic( int           START_IDX,
                                     int           END_IDX,
                                     const double *IN_ARRAY /* inReal */,
                                     int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                                     int          *BEG_IDX,
                                     int          *OUT_SIZE,
                                     double       *OUT_ARRAY /* outReal */ );

int TA_LINEARREG_ANGLE_Lookback( int           optInTimePeriod  /* From 2 to 100000 */ );

