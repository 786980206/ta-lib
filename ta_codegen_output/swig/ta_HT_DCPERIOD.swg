/*
 * TA_HT_DCPERIOD - Hilbert Transform - Dominant Cycle Period
 *
 * Input  = double
 * Output = double
 *
 */
TA_RetCode TA_HT_DCPERIOD( int           START_IDX,
                           int           END_IDX,
                           const double *IN_ARRAY /* inReal */,
                           int          *BEG_IDX,
                           int          *OUT_SIZE,
                           double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_HT_DCPERIOD_Logic( int           START_IDX,
                                 int           END_IDX,
                                 const double *IN_ARRAY /* inReal */,
                                 int          *BEG_IDX,
                                 int          *OUT_SIZE,
                                 double       *OUT_ARRAY /* outReal */ );

int TA_HT_DCPERIOD_Lookback( void );

