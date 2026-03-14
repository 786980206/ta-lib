/*
 * TA_SAREXT - Parabolic SAR - Extended
 *
 * Input  = double, double
 * Output = double
 *
 * Optional Parameters
 * -------------------
 * optInStartValue:(From -2147483648 to 2147483647)
 * optInOffsetOnReverse:(From 0 to 2147483647)
 * optInAccelerationInitLong:(From 0 to 2147483647)
 * optInAccelerationLong:(From 0 to 2147483647)
 * optInAccelerationMaxLong:(From 0 to 2147483647)
 * optInAccelerationInitShort:(From 0 to 2147483647)
 * optInAccelerationShort:(From 0 to 2147483647)
 * optInAccelerationMaxShort:(From 0 to 2147483647)
 *
 */
TA_RetCode TA_SAREXT( int           START_IDX,
                      int           END_IDX,
                      const double *IN_ARRAY /* inHigh */,
                      const double *IN_ARRAY /* inLow */,
                      double           OPT_REAL /* optInStartValue */, /* From -2147483648 to 2147483647 */
                      double           OPT_REAL /* optInOffsetOnReverse */, /* From 0 to 2147483647 */
                      double           OPT_REAL /* optInAccelerationInitLong */, /* From 0 to 2147483647 */
                      double           OPT_REAL /* optInAccelerationLong */, /* From 0 to 2147483647 */
                      double           OPT_REAL /* optInAccelerationMaxLong */, /* From 0 to 2147483647 */
                      double           OPT_REAL /* optInAccelerationInitShort */, /* From 0 to 2147483647 */
                      double           OPT_REAL /* optInAccelerationShort */, /* From 0 to 2147483647 */
                      double           OPT_REAL /* optInAccelerationMaxShort */, /* From 0 to 2147483647 */
                      int          *BEG_IDX,
                      int          *OUT_SIZE,
                      double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_SAREXT_Logic( int           START_IDX,
                            int           END_IDX,
                            const double *IN_ARRAY /* inHigh */,
                            const double *IN_ARRAY /* inLow */,
                            double           OPT_REAL /* optInStartValue */, /* From -2147483648 to 2147483647 */
                            double           OPT_REAL /* optInOffsetOnReverse */, /* From 0 to 2147483647 */
                            double           OPT_REAL /* optInAccelerationInitLong */, /* From 0 to 2147483647 */
                            double           OPT_REAL /* optInAccelerationLong */, /* From 0 to 2147483647 */
                            double           OPT_REAL /* optInAccelerationMaxLong */, /* From 0 to 2147483647 */
                            double           OPT_REAL /* optInAccelerationInitShort */, /* From 0 to 2147483647 */
                            double           OPT_REAL /* optInAccelerationShort */, /* From 0 to 2147483647 */
                            double           OPT_REAL /* optInAccelerationMaxShort */, /* From 0 to 2147483647 */
                            int          *BEG_IDX,
                            int          *OUT_SIZE,
                            double       *OUT_ARRAY /* outReal */ );

int TA_SAREXT_Lookback( double           optInStartValue  /* From -2147483648 to 2147483647 */, double           optInOffsetOnReverse  /* From 0 to 2147483647 */, double           optInAccelerationInitLong  /* From 0 to 2147483647 */, double           optInAccelerationLong  /* From 0 to 2147483647 */, double           optInAccelerationMaxLong  /* From 0 to 2147483647 */, double           optInAccelerationInitShort  /* From 0 to 2147483647 */, double           optInAccelerationShort  /* From 0 to 2147483647 */, double           optInAccelerationMaxShort  /* From 0 to 2147483647 */ );

