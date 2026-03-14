/*
 * TA_OBV - On Balance Volume
 *
 * Input  = double, double
 * Output = double
 *
 */
TA_RetCode TA_OBV( int           START_IDX,
                   int           END_IDX,
                   const double *IN_ARRAY /* inReal */,
                   const double *IN_ARRAY /* inVolume */,
                   int          *BEG_IDX,
                   int          *OUT_SIZE,
                   double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_OBV_Logic( int           START_IDX,
                         int           END_IDX,
                         const double *IN_ARRAY /* inReal */,
                         const double *IN_ARRAY /* inVolume */,
                         int          *BEG_IDX,
                         int          *OUT_SIZE,
                         double       *OUT_ARRAY /* outReal */ );

int TA_OBV_Lookback( void );

