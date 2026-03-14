/*
 * TA_AD - Chaikin A/D Line
 *
 * Input  = double, double, double, double
 * Output = double
 *
 */
TA_RetCode TA_AD( int           START_IDX,
                  int           END_IDX,
                  const double *IN_ARRAY /* inHigh */,
                  const double *IN_ARRAY /* inLow */,
                  const double *IN_ARRAY /* inClose */,
                  const double *IN_ARRAY /* inVolume */,
                  int          *BEG_IDX,
                  int          *OUT_SIZE,
                  double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_AD_Logic( int           START_IDX,
                        int           END_IDX,
                        const double *IN_ARRAY /* inHigh */,
                        const double *IN_ARRAY /* inLow */,
                        const double *IN_ARRAY /* inClose */,
                        const double *IN_ARRAY /* inVolume */,
                        int          *BEG_IDX,
                        int          *OUT_SIZE,
                        double       *OUT_ARRAY /* outReal */ );

int TA_AD_Lookback( void );

