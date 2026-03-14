/*
 * TA_PVI - Positive Volume Index
 *
 * Input  = double, double
 * Output = double
 *
 */
TA_RetCode TA_PVI( int           START_IDX,
                   int           END_IDX,
                   const double *IN_ARRAY /* inClose */,
                   const double *IN_ARRAY /* inVolume */,
                   int          *BEG_IDX,
                   int          *OUT_SIZE,
                   double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_PVI_Logic( int           START_IDX,
                         int           END_IDX,
                         const double *IN_ARRAY /* inClose */,
                         const double *IN_ARRAY /* inVolume */,
                         int          *BEG_IDX,
                         int          *OUT_SIZE,
                         double       *OUT_ARRAY /* outReal */ );

int TA_PVI_Lookback( void );

