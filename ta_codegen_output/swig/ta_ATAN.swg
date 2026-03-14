/*
 * TA_ATAN - Vector Trigonometric ATan
 *
 * Input  = double
 * Output = double
 *
 */
TA_RetCode TA_ATAN( int           START_IDX,
                    int           END_IDX,
                    const double *IN_ARRAY /* inReal */,
                    int          *BEG_IDX,
                    int          *OUT_SIZE,
                    double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_ATAN_Logic( int           START_IDX,
                          int           END_IDX,
                          const double *IN_ARRAY /* inReal */,
                          int          *BEG_IDX,
                          int          *OUT_SIZE,
                          double       *OUT_ARRAY /* outReal */ );

int TA_ATAN_Lookback( void );

