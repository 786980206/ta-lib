/*
 * TA_CDL3BLACKCROWS - Three Black Crows
 *
 * Input  = double, double, double, double
 * Output = int
 *
 */
TA_RetCode TA_CDL3BLACKCROWS( int           START_IDX,
                              int           END_IDX,
                              const double *IN_ARRAY /* inOpen */,
                              const double *IN_ARRAY /* inHigh */,
                              const double *IN_ARRAY /* inLow */,
                              const double *IN_ARRAY /* inClose */,
                              int          *BEG_IDX,
                              int          *OUT_SIZE,
                              int          *OUT_ARRAY /* outInteger */ );

TA_RetCode TA_CDL3BLACKCROWS_Logic( int           START_IDX,
                                    int           END_IDX,
                                    const double *IN_ARRAY /* inOpen */,
                                    const double *IN_ARRAY /* inHigh */,
                                    const double *IN_ARRAY /* inLow */,
                                    const double *IN_ARRAY /* inClose */,
                                    int          *BEG_IDX,
                                    int          *OUT_SIZE,
                                    int          *OUT_ARRAY /* outInteger */ );

int TA_CDL3BLACKCROWS_Lookback( void );

