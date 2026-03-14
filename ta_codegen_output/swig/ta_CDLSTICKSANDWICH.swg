/*
 * TA_CDLSTICKSANDWICH - Stick Sandwich
 *
 * Input  = double, double, double, double
 * Output = int
 *
 */
TA_RetCode TA_CDLSTICKSANDWICH( int           START_IDX,
                                int           END_IDX,
                                const double *IN_ARRAY /* inOpen */,
                                const double *IN_ARRAY /* inHigh */,
                                const double *IN_ARRAY /* inLow */,
                                const double *IN_ARRAY /* inClose */,
                                int          *BEG_IDX,
                                int          *OUT_SIZE,
                                int          *OUT_ARRAY /* outInteger */ );

TA_RetCode TA_CDLSTICKSANDWICH_Logic( int           START_IDX,
                                      int           END_IDX,
                                      const double *IN_ARRAY /* inOpen */,
                                      const double *IN_ARRAY /* inHigh */,
                                      const double *IN_ARRAY /* inLow */,
                                      const double *IN_ARRAY /* inClose */,
                                      int          *BEG_IDX,
                                      int          *OUT_SIZE,
                                      int          *OUT_ARRAY /* outInteger */ );

int TA_CDLSTICKSANDWICH_Lookback( void );

