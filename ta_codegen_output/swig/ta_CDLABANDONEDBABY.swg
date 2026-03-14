/*
 * TA_CDLABANDONEDBABY - Abandoned Baby
 *
 * Input  = double, double, double, double
 * Output = int
 *
 * Optional Parameters
 * -------------------
 * optInPenetration:(From 0 to 2147483647)
 *
 */
TA_RetCode TA_CDLABANDONEDBABY( int           START_IDX,
                                int           END_IDX,
                                const double *IN_ARRAY /* inOpen */,
                                const double *IN_ARRAY /* inHigh */,
                                const double *IN_ARRAY /* inLow */,
                                const double *IN_ARRAY /* inClose */,
                                double           OPT_REAL /* optInPenetration */, /* From 0 to 2147483647 */
                                int          *BEG_IDX,
                                int          *OUT_SIZE,
                                int          *OUT_ARRAY /* outInteger */ );

TA_RetCode TA_CDLABANDONEDBABY_Logic( int           START_IDX,
                                      int           END_IDX,
                                      const double *IN_ARRAY /* inOpen */,
                                      const double *IN_ARRAY /* inHigh */,
                                      const double *IN_ARRAY /* inLow */,
                                      const double *IN_ARRAY /* inClose */,
                                      double           OPT_REAL /* optInPenetration */, /* From 0 to 2147483647 */
                                      int          *BEG_IDX,
                                      int          *OUT_SIZE,
                                      int          *OUT_ARRAY /* outInteger */ );

int TA_CDLABANDONEDBABY_Lookback( double           optInPenetration  /* From 0 to 2147483647 */ );

