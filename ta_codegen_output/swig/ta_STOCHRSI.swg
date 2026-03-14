/*
 * TA_STOCHRSI - Stochastic Relative Strength Index
 *
 * Input  = double
 * Output = double, double
 *
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 2 to 100000)
 * optInFastK_Period:(From 1 to 100000)
 * optInFastD_Period:(From 1 to 100000)
 * optInFastD_MAType:
 *
 */
TA_RetCode TA_STOCHRSI( int           START_IDX,
                        int           END_IDX,
                        const double *IN_ARRAY /* inReal */,
                        int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                        int           OPT_INT /* optInFastK_Period */, /* From 1 to 100000 */
                        int           OPT_INT /* optInFastD_Period */, /* From 1 to 100000 */
                        int           OPT_INT /* optInFastD_MAType */,
                        int          *BEG_IDX,
                        int          *OUT_SIZE,
                        double       *OUT_ARRAY /* outFastK */,
                        double       *OUT_ARRAY /* outFastD */ );

TA_RetCode TA_STOCHRSI_Logic( int           START_IDX,
                              int           END_IDX,
                              const double *IN_ARRAY /* inReal */,
                              int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                              int           OPT_INT /* optInFastK_Period */, /* From 1 to 100000 */
                              int           OPT_INT /* optInFastD_Period */, /* From 1 to 100000 */
                              int           OPT_INT /* optInFastD_MAType */,
                              int          *BEG_IDX,
                              int          *OUT_SIZE,
                              double       *OUT_ARRAY /* outFastK */,
                              double       *OUT_ARRAY /* outFastD */ );

int TA_STOCHRSI_Lookback( int           optInTimePeriod  /* From 2 to 100000 */, int           optInFastK_Period  /* From 1 to 100000 */, int           optInFastD_Period  /* From 1 to 100000 */, int           optInFastD_MAType );

