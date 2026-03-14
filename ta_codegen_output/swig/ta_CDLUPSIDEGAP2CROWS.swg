/*
 * TA_CDLUPSIDEGAP2CROWS - Upside Gap Two Crows
 *
 * Input  = double, double, double, double
 * Output = int
 *
 */
TA_RetCode TA_CDLUPSIDEGAP2CROWS( int           START_IDX,
                                  int           END_IDX,
                                  const double *IN_ARRAY /* inOpen */,
                                  const double *IN_ARRAY /* inHigh */,
                                  const double *IN_ARRAY /* inLow */,
                                  const double *IN_ARRAY /* inClose */,
                                  int          *BEG_IDX,
                                  int          *OUT_SIZE,
                                  int          *OUT_ARRAY /* outInteger */ );

TA_RetCode TA_CDLUPSIDEGAP2CROWS_Logic( int           START_IDX,
                                        int           END_IDX,
                                        const double *IN_ARRAY /* inOpen */,
                                        const double *IN_ARRAY /* inHigh */,
                                        const double *IN_ARRAY /* inLow */,
                                        const double *IN_ARRAY /* inClose */,
                                        int          *BEG_IDX,
                                        int          *OUT_SIZE,
                                        int          *OUT_ARRAY /* outInteger */ );

int TA_CDLUPSIDEGAP2CROWS_Lookback( void );

