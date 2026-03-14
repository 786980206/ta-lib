/*
 * TA_ACCBANDS - Acceleration Bands
 *
 * Input  = double, double, double
 * Output = double, double, double
 *
 * Optional Parameters
 * -------------------
 * optInTimePeriod:(From 2 to 100000)
 *
 */
TA_RetCode TA_ACCBANDS( int           START_IDX,
                        int           END_IDX,
                        const double *IN_ARRAY /* inHigh */,
                        const double *IN_ARRAY /* inLow */,
                        const double *IN_ARRAY /* inClose */,
                        int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                        int          *BEG_IDX,
                        int          *OUT_SIZE,
                        double       *OUT_ARRAY /* outRealUpperBand */,
                        double       *OUT_ARRAY /* outRealMiddleBand */,
                        double       *OUT_ARRAY /* outRealLowerBand */ );

TA_RetCode TA_ACCBANDS_Logic( int           START_IDX,
                              int           END_IDX,
                              const double *IN_ARRAY /* inHigh */,
                              const double *IN_ARRAY /* inLow */,
                              const double *IN_ARRAY /* inClose */,
                              int           OPT_INT /* optInTimePeriod */, /* From 2 to 100000 */
                              int          *BEG_IDX,
                              int          *OUT_SIZE,
                              double       *OUT_ARRAY /* outRealUpperBand */,
                              double       *OUT_ARRAY /* outRealMiddleBand */,
                              double       *OUT_ARRAY /* outRealLowerBand */ );

int TA_ACCBANDS_Lookback( int           optInTimePeriod  /* From 2 to 100000 */ );

