/*
 * TA_FLOOR - Vector Floor
 *
 * Input  = double
 * Output = double
 *
 */
TA_RetCode TA_FLOOR( int           START_IDX,
                     int           END_IDX,
                     const double *IN_ARRAY /* inReal */,
                     int          *BEG_IDX,
                     int          *OUT_SIZE,
                     double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_FLOOR_Logic( int           START_IDX,
                           int           END_IDX,
                           const double *IN_ARRAY /* inReal */,
                           int          *BEG_IDX,
                           int          *OUT_SIZE,
                           double       *OUT_ARRAY /* outReal */ );

int TA_FLOOR_Lookback( void );

