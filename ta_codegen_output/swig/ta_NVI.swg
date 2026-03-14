/*
 * TA_NVI - Negative Volume Index
 *
 * Input  = double, double
 * Output = double
 *
 */
TA_RetCode TA_NVI( int           START_IDX,
                   int           END_IDX,
                   const double *IN_ARRAY /* inClose */,
                   const double *IN_ARRAY /* inVolume */,
                   int          *BEG_IDX,
                   int          *OUT_SIZE,
                   double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_NVI_Logic( int           START_IDX,
                         int           END_IDX,
                         const double *IN_ARRAY /* inClose */,
                         const double *IN_ARRAY /* inVolume */,
                         int          *BEG_IDX,
                         int          *OUT_SIZE,
                         double       *OUT_ARRAY /* outReal */ );

int TA_NVI_Lookback( void );

