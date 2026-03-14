/*
 * TA_MACDFIX - Moving Average Convergence/Divergence Fix 12/26
 *
 * Input  = double
 * Output = double, double, double
 *
 * Optional Parameters
 * -------------------
 * optInSignalPeriod:(From 1 to 100000)
 *
 */
TA_RetCode TA_MACDFIX( int           START_IDX,
                       int           END_IDX,
                       const double *IN_ARRAY /* inReal */,
                       int           OPT_INT /* optInSignalPeriod */, /* From 1 to 100000 */
                       int          *BEG_IDX,
                       int          *OUT_SIZE,
                       double       *OUT_ARRAY /* outMACD */,
                       double       *OUT_ARRAY /* outMACDSignal */,
                       double       *OUT_ARRAY /* outMACDHist */ );

TA_RetCode TA_MACDFIX_Logic( int           START_IDX,
                             int           END_IDX,
                             const double *IN_ARRAY /* inReal */,
                             int           OPT_INT /* optInSignalPeriod */, /* From 1 to 100000 */
                             int          *BEG_IDX,
                             int          *OUT_SIZE,
                             double       *OUT_ARRAY /* outMACD */,
                             double       *OUT_ARRAY /* outMACDSignal */,
                             double       *OUT_ARRAY /* outMACDHist */ );

int TA_MACDFIX_Lookback( int           optInSignalPeriod  /* From 1 to 100000 */ );

