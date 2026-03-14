/*
 * TA_CDLINNECK - In-Neck Pattern
 *
 * Input  = double, double, double, double
 * Output = int
 *
 */
TA_RetCode TA_CDLINNECK( int           START_IDX,
                         int           END_IDX,
                         const double *IN_ARRAY /* inOpen */,
                         const double *IN_ARRAY /* inHigh */,
                         const double *IN_ARRAY /* inLow */,
                         const double *IN_ARRAY /* inClose */,
                         int          *BEG_IDX,
                         int          *OUT_SIZE,
                         int          *OUT_ARRAY /* outInteger */ );

TA_RetCode TA_CDLINNECK_Logic( int           START_IDX,
                               int           END_IDX,
                               const double *IN_ARRAY /* inOpen */,
                               const double *IN_ARRAY /* inHigh */,
                               const double *IN_ARRAY /* inLow */,
                               const double *IN_ARRAY /* inClose */,
                               int          *BEG_IDX,
                               int          *OUT_SIZE,
                               int          *OUT_ARRAY /* outInteger */ );

int TA_CDLINNECK_Lookback( void );

