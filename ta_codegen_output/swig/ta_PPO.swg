/*
 * TA_PPO - Percentage Price Oscillator
 *
 * Input  = double
 * Output = double
 *
 * Optional Parameters
 * -------------------
 * optInFastPeriod:(From 2 to 100000)
 * optInSlowPeriod:(From 2 to 100000)
 * optInMAType:
 *
 */
TA_RetCode TA_PPO( int           START_IDX,
                   int           END_IDX,
                   const double *IN_ARRAY /* inReal */,
                   int           OPT_INT /* optInFastPeriod */, /* From 2 to 100000 */
                   int           OPT_INT /* optInSlowPeriod */, /* From 2 to 100000 */
                   int           OPT_INT /* optInMAType */,
                   int          *BEG_IDX,
                   int          *OUT_SIZE,
                   double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_PPO_Logic( int           START_IDX,
                         int           END_IDX,
                         const double *IN_ARRAY /* inReal */,
                         int           OPT_INT /* optInFastPeriod */, /* From 2 to 100000 */
                         int           OPT_INT /* optInSlowPeriod */, /* From 2 to 100000 */
                         int           OPT_INT /* optInMAType */,
                         int          *BEG_IDX,
                         int          *OUT_SIZE,
                         double       *OUT_ARRAY /* outReal */ );

int TA_PPO_Lookback( int           optInFastPeriod  /* From 2 to 100000 */, int           optInSlowPeriod  /* From 2 to 100000 */, int           optInMAType );

