/*
 * TA_ACOS - Vector Trigonometric ACos
 *
 * Input  = double
 * Output = double
 *
 */
TA_RetCode TA_ACOS( int           START_IDX,
                    int           END_IDX,
                    const double *IN_ARRAY /* inReal */,
                    int          *BEG_IDX,
                    int          *OUT_SIZE,
                    double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_ACOS_Logic( int           START_IDX,
                          int           END_IDX,
                          const double *IN_ARRAY /* inReal */,
                          int          *BEG_IDX,
                          int          *OUT_SIZE,
                          double       *OUT_ARRAY /* outReal */ );

int TA_ACOS_Lookback( void );

