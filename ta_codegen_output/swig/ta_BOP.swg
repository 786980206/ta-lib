/*
 * TA_BOP - Balance Of Power
 *
 * Input  = double, double, double, double
 * Output = double
 *
 */
TA_RetCode TA_BOP( int           START_IDX,
                   int           END_IDX,
                   const double *IN_ARRAY /* inOpen */,
                   const double *IN_ARRAY /* inHigh */,
                   const double *IN_ARRAY /* inLow */,
                   const double *IN_ARRAY /* inClose */,
                   int          *BEG_IDX,
                   int          *OUT_SIZE,
                   double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_BOP_Logic( int           START_IDX,
                         int           END_IDX,
                         const double *IN_ARRAY /* inOpen */,
                         const double *IN_ARRAY /* inHigh */,
                         const double *IN_ARRAY /* inLow */,
                         const double *IN_ARRAY /* inClose */,
                         int          *BEG_IDX,
                         int          *OUT_SIZE,
                         double       *OUT_ARRAY /* outReal */ );

int TA_BOP_Lookback( void );

