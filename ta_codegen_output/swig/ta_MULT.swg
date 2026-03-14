/*
 * TA_MULT - Vector Arithmetic Mult
 *
 * Input  = double, double
 * Output = double
 *
 */
TA_RetCode TA_MULT( int           START_IDX,
                    int           END_IDX,
                    const double *IN_ARRAY /* inReal0 */,
                    const double *IN_ARRAY /* inReal1 */,
                    int          *BEG_IDX,
                    int          *OUT_SIZE,
                    double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_MULT_Logic( int           START_IDX,
                          int           END_IDX,
                          const double *IN_ARRAY /* inReal0 */,
                          const double *IN_ARRAY /* inReal1 */,
                          int          *BEG_IDX,
                          int          *OUT_SIZE,
                          double       *OUT_ARRAY /* outReal */ );

int TA_MULT_Lookback( void );

