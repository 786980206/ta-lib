/*
 * TA_LOG10 - Vector Log10
 *
 * Input  = double
 * Output = double
 *
 */
TA_RetCode TA_LOG10( int           START_IDX,
                     int           END_IDX,
                     const double *IN_ARRAY /* inReal */,
                     int          *BEG_IDX,
                     int          *OUT_SIZE,
                     double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_LOG10_Logic( int           START_IDX,
                           int           END_IDX,
                           const double *IN_ARRAY /* inReal */,
                           int          *BEG_IDX,
                           int          *OUT_SIZE,
                           double       *OUT_ARRAY /* outReal */ );

int TA_LOG10_Lookback( void );

