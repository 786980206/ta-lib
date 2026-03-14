/*
 * TA_STOCHF - Stochastic Fast
 *
 * Input  = double, double, double
 * Output = double, double
 *
 * Optional Parameters
 * -------------------
 * optInFastK_Period:(From 1 to 100000)
 * optInFastD_Period:(From 1 to 100000)
 * optInFastD_MAType:
 *
 */
TA_RetCode TA_STOCHF( int           START_IDX,
                      int           END_IDX,
                      const double *IN_ARRAY /* inHigh */,
                      const double *IN_ARRAY /* inLow */,
                      const double *IN_ARRAY /* inClose */,
                      int           OPT_INT /* optInFastK_Period */, /* From 1 to 100000 */
                      int           OPT_INT /* optInFastD_Period */, /* From 1 to 100000 */
                      int           OPT_INT /* optInFastD_MAType */,
                      int          *BEG_IDX,
                      int          *OUT_SIZE,
                      double       *OUT_ARRAY /* outFastK */,
                      double       *OUT_ARRAY /* outFastD */ );

TA_RetCode TA_STOCHF_Logic( int           START_IDX,
                            int           END_IDX,
                            const double *IN_ARRAY /* inHigh */,
                            const double *IN_ARRAY /* inLow */,
                            const double *IN_ARRAY /* inClose */,
                            int           OPT_INT /* optInFastK_Period */, /* From 1 to 100000 */
                            int           OPT_INT /* optInFastD_Period */, /* From 1 to 100000 */
                            int           OPT_INT /* optInFastD_MAType */,
                            int          *BEG_IDX,
                            int          *OUT_SIZE,
                            double       *OUT_ARRAY /* outFastK */,
                            double       *OUT_ARRAY /* outFastD */ );

int TA_STOCHF_Lookback( int           optInFastK_Period  /* From 1 to 100000 */, int           optInFastD_Period  /* From 1 to 100000 */, int           optInFastD_MAType );

