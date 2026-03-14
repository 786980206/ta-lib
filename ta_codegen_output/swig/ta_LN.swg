/*
 * TA_LN - Vector Log Natural
 *
 * Input  = double
 * Output = double
 *
 */
TA_RetCode TA_LN( int           START_IDX,
                  int           END_IDX,
                  const double *IN_ARRAY /* inReal */,
                  int          *BEG_IDX,
                  int          *OUT_SIZE,
                  double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_LN_Logic( int           START_IDX,
                        int           END_IDX,
                        const double *IN_ARRAY /* inReal */,
                        int          *BEG_IDX,
                        int          *OUT_SIZE,
                        double       *OUT_ARRAY /* outReal */ );

int TA_LN_Lookback( void );

