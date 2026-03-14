/*
 * TA_MAMA - MESA Adaptive Moving Average
 *
 * Input  = double
 * Output = double, double
 *
 * Optional Parameters
 * -------------------
 * optInFastLimit:(From 0 to 0)
 * optInSlowLimit:(From 0 to 0)
 *
 */
TA_RetCode TA_MAMA( int           START_IDX,
                    int           END_IDX,
                    const double *IN_ARRAY /* inReal */,
                    double           OPT_REAL /* optInFastLimit */, /* From 0 to 0 */
                    double           OPT_REAL /* optInSlowLimit */, /* From 0 to 0 */
                    int          *BEG_IDX,
                    int          *OUT_SIZE,
                    double       *OUT_ARRAY /* outMAMA */,
                    double       *OUT_ARRAY /* outFAMA */ );

TA_RetCode TA_MAMA_Logic( int           START_IDX,
                          int           END_IDX,
                          const double *IN_ARRAY /* inReal */,
                          double           OPT_REAL /* optInFastLimit */, /* From 0 to 0 */
                          double           OPT_REAL /* optInSlowLimit */, /* From 0 to 0 */
                          int          *BEG_IDX,
                          int          *OUT_SIZE,
                          double       *OUT_ARRAY /* outMAMA */,
                          double       *OUT_ARRAY /* outFAMA */ );

int TA_MAMA_Lookback( double           optInFastLimit  /* From 0 to 0 */, double           optInSlowLimit  /* From 0 to 0 */ );

