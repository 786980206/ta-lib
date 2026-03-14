/*
 * TA_STOCH - Stochastic
 *
 * Input  = double, double, double
 * Output = double, double
 *
 * Optional Parameters
 * -------------------
 * optInFastK_Period:(From 1 to 100000)
 * optInSlowK_Period:(From 1 to 100000)
 * optInSlowK_MAType:
 * optInSlowD_Period:(From 1 to 100000)
 * optInSlowD_MAType:
 *
 */
TA_RetCode TA_STOCH( int           START_IDX,
                     int           END_IDX,
                     const double *IN_ARRAY /* inHigh */,
                     const double *IN_ARRAY /* inLow */,
                     const double *IN_ARRAY /* inClose */,
                     int           OPT_INT /* optInFastK_Period */, /* From 1 to 100000 */
                     int           OPT_INT /* optInSlowK_Period */, /* From 1 to 100000 */
                     int           OPT_INT /* optInSlowK_MAType */,
                     int           OPT_INT /* optInSlowD_Period */, /* From 1 to 100000 */
                     int           OPT_INT /* optInSlowD_MAType */,
                     int          *BEG_IDX,
                     int          *OUT_SIZE,
                     double       *OUT_ARRAY /* outSlowK */,
                     double       *OUT_ARRAY /* outSlowD */ );

TA_RetCode TA_STOCH_Logic( int           START_IDX,
                           int           END_IDX,
                           const double *IN_ARRAY /* inHigh */,
                           const double *IN_ARRAY /* inLow */,
                           const double *IN_ARRAY /* inClose */,
                           int           OPT_INT /* optInFastK_Period */, /* From 1 to 100000 */
                           int           OPT_INT /* optInSlowK_Period */, /* From 1 to 100000 */
                           int           OPT_INT /* optInSlowK_MAType */,
                           int           OPT_INT /* optInSlowD_Period */, /* From 1 to 100000 */
                           int           OPT_INT /* optInSlowD_MAType */,
                           int          *BEG_IDX,
                           int          *OUT_SIZE,
                           double       *OUT_ARRAY /* outSlowK */,
                           double       *OUT_ARRAY /* outSlowD */ );

int TA_STOCH_Lookback( int           optInFastK_Period  /* From 1 to 100000 */, int           optInSlowK_Period  /* From 1 to 100000 */, int           optInSlowK_MAType, int           optInSlowD_Period  /* From 1 to 100000 */, int           optInSlowD_MAType );

