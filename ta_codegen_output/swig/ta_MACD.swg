/*
 * TA_MACD - Moving Average Convergence/Divergence
 *
 * Input  = double
 * Output = double, double, double
 *
 * Optional Parameters
 * -------------------
 * optInFastPeriod:(From 2 to 100000)
 * optInSlowPeriod:(From 2 to 100000)
 * optInSignalPeriod:(From 1 to 100000)
 *
 */
TA_RetCode TA_MACD( int           START_IDX,
                    int           END_IDX,
                    const double *IN_ARRAY /* inReal */,
                    int           OPT_INT /* optInFastPeriod */, /* From 2 to 100000 */
                    int           OPT_INT /* optInSlowPeriod */, /* From 2 to 100000 */
                    int           OPT_INT /* optInSignalPeriod */, /* From 1 to 100000 */
                    int          *BEG_IDX,
                    int          *OUT_SIZE,
                    double       *OUT_ARRAY /* outMACD */,
                    double       *OUT_ARRAY /* outMACDSignal */,
                    double       *OUT_ARRAY /* outMACDHist */ );

TA_RetCode TA_MACD_Logic( int           START_IDX,
                          int           END_IDX,
                          const double *IN_ARRAY /* inReal */,
                          int           OPT_INT /* optInFastPeriod */, /* From 2 to 100000 */
                          int           OPT_INT /* optInSlowPeriod */, /* From 2 to 100000 */
                          int           OPT_INT /* optInSignalPeriod */, /* From 1 to 100000 */
                          int          *BEG_IDX,
                          int          *OUT_SIZE,
                          double       *OUT_ARRAY /* outMACD */,
                          double       *OUT_ARRAY /* outMACDSignal */,
                          double       *OUT_ARRAY /* outMACDHist */ );

int TA_MACD_Lookback( int           optInFastPeriod  /* From 2 to 100000 */, int           optInSlowPeriod  /* From 2 to 100000 */, int           optInSignalPeriod  /* From 1 to 100000 */ );

