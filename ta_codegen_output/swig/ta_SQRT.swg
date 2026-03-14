/*
 * TA_SQRT - Vector Square Root
 *
 * Input  = double
 * Output = double
 *
 */
TA_RetCode TA_SQRT( int           START_IDX,
                    int           END_IDX,
                    const double *IN_ARRAY /* inReal */,
                    int          *BEG_IDX,
                    int          *OUT_SIZE,
                    double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_SQRT_Logic( int           START_IDX,
                          int           END_IDX,
                          const double *IN_ARRAY /* inReal */,
                          int          *BEG_IDX,
                          int          *OUT_SIZE,
                          double       *OUT_ARRAY /* outReal */ );

int TA_SQRT_Lookback( void );

