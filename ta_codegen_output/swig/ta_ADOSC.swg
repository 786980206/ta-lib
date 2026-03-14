/*
 * TA_ADOSC - Chaikin A/D Oscillator
 *
 * Input  = double, double, double, double
 * Output = double
 *
 * Optional Parameters
 * -------------------
 * optInFastPeriod:(From 2 to 100000)
 * optInSlowPeriod:(From 2 to 100000)
 *
 */
TA_RetCode TA_ADOSC( int           START_IDX,
                     int           END_IDX,
                     const double *IN_ARRAY /* inHigh */,
                     const double *IN_ARRAY /* inLow */,
                     const double *IN_ARRAY /* inClose */,
                     const double *IN_ARRAY /* inVolume */,
                     int           OPT_INT /* optInFastPeriod */, /* From 2 to 100000 */
                     int           OPT_INT /* optInSlowPeriod */, /* From 2 to 100000 */
                     int          *BEG_IDX,
                     int          *OUT_SIZE,
                     double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_ADOSC_Logic( int           START_IDX,
                           int           END_IDX,
                           const double *IN_ARRAY /* inHigh */,
                           const double *IN_ARRAY /* inLow */,
                           const double *IN_ARRAY /* inClose */,
                           const double *IN_ARRAY /* inVolume */,
                           int           OPT_INT /* optInFastPeriod */, /* From 2 to 100000 */
                           int           OPT_INT /* optInSlowPeriod */, /* From 2 to 100000 */
                           int          *BEG_IDX,
                           int          *OUT_SIZE,
                           double       *OUT_ARRAY /* outReal */ );

int TA_ADOSC_Lookback( int           optInFastPeriod  /* From 2 to 100000 */, int           optInSlowPeriod  /* From 2 to 100000 */ );

