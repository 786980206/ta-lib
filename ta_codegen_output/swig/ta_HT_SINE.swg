/*
 * TA_HT_SINE - Hilbert Transform - SineWave
 *
 * Input  = double
 * Output = double, double
 *
 */
TA_RetCode TA_HT_SINE( int           START_IDX,
                       int           END_IDX,
                       const double *IN_ARRAY /* inReal */,
                       int          *BEG_IDX,
                       int          *OUT_SIZE,
                       double       *OUT_ARRAY /* outSine */,
                       double       *OUT_ARRAY /* outLeadSine */ );

TA_RetCode TA_HT_SINE_Logic( int           START_IDX,
                             int           END_IDX,
                             const double *IN_ARRAY /* inReal */,
                             int          *BEG_IDX,
                             int          *OUT_SIZE,
                             double       *OUT_ARRAY /* outSine */,
                             double       *OUT_ARRAY /* outLeadSine */ );

int TA_HT_SINE_Lookback( void );

