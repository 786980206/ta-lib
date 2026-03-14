/*
 * TA_MACDEXT - MACD with controllable MA type
 *
 * Input  = double
 * Output = double, double, double
 *
 * Optional Parameters
 * -------------------
 * optInFastPeriod:(From 2 to 100000)
 * optInFastMAType:
 * optInSlowPeriod:(From 2 to 100000)
 * optInSlowMAType:
 * optInSignalPeriod:(From 1 to 100000)
 * optInSignalMAType:
 *
 */
TA_RetCode TA_MACDEXT( int           START_IDX,
                       int           END_IDX,
                       const double *IN_ARRAY /* inReal */,
                       int           OPT_INT /* optInFastPeriod */, /* From 2 to 100000 */
                       int           OPT_INT /* optInFastMAType */,
                       int           OPT_INT /* optInSlowPeriod */, /* From 2 to 100000 */
                       int           OPT_INT /* optInSlowMAType */,
                       int           OPT_INT /* optInSignalPeriod */, /* From 1 to 100000 */
                       int           OPT_INT /* optInSignalMAType */,
                       int          *BEG_IDX,
                       int          *OUT_SIZE,
                       double       *OUT_ARRAY /* outMACD */,
                       double       *OUT_ARRAY /* outMACDSignal */,
                       double       *OUT_ARRAY /* outMACDHist */ );

TA_RetCode TA_MACDEXT_Logic( int           START_IDX,
                             int           END_IDX,
                             const double *IN_ARRAY /* inReal */,
                             int           OPT_INT /* optInFastPeriod */, /* From 2 to 100000 */
                             int           OPT_INT /* optInFastMAType */,
                             int           OPT_INT /* optInSlowPeriod */, /* From 2 to 100000 */
                             int           OPT_INT /* optInSlowMAType */,
                             int           OPT_INT /* optInSignalPeriod */, /* From 1 to 100000 */
                             int           OPT_INT /* optInSignalMAType */,
                             int          *BEG_IDX,
                             int          *OUT_SIZE,
                             double       *OUT_ARRAY /* outMACD */,
                             double       *OUT_ARRAY /* outMACDSignal */,
                             double       *OUT_ARRAY /* outMACDHist */ );

int TA_MACDEXT_Lookback( int           optInFastPeriod  /* From 2 to 100000 */, int           optInFastMAType, int           optInSlowPeriod  /* From 2 to 100000 */, int           optInSlowMAType, int           optInSignalPeriod  /* From 1 to 100000 */, int           optInSignalMAType );

