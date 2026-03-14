/*
 * TA_DX - Directional Movement Index
 *
 * Input  = double, double, double
 * Output = double
 *
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 2 to 100000)
 *
 */
TA_RetCode TA_DX( int           START_IDX,
                  int           END_IDX,
                  const double *IN_ARRAY /* inHigh */,
                  const double *IN_ARRAY /* inLow */,
                  const double *IN_ARRAY /* inClose */,
                  int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                  int          *BEG_IDX,
                  int          *OUT_SIZE,
                  double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_DX_Logic( int           START_IDX,
                        int           END_IDX,
                        const double *IN_ARRAY /* inHigh */,
                        const double *IN_ARRAY /* inLow */,
                        const double *IN_ARRAY /* inClose */,
                        int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                        int          *BEG_IDX,
                        int          *OUT_SIZE,
                        double       *OUT_ARRAY /* outReal */ );

int TA_DX_Lookback( int           optInTimePeriod  /* From 2 to 100000 */ );

