/*
 * TA_AVGPRICE - Average Price
 *
 * Input  = double, double, double, double
 * Output = double
 *
 */
TA_RetCode TA_AVGPRICE( int           START_IDX,
                        int           END_IDX,
                        const double *IN_ARRAY /* inOpen */,
                        const double *IN_ARRAY /* inHigh */,
                        const double *IN_ARRAY /* inLow */,
                        const double *IN_ARRAY /* inClose */,
                        int          *BEG_IDX,
                        int          *OUT_SIZE,
                        double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_AVGPRICE_Logic( int           START_IDX,
                              int           END_IDX,
                              const double *IN_ARRAY /* inOpen */,
                              const double *IN_ARRAY /* inHigh */,
                              const double *IN_ARRAY /* inLow */,
                              const double *IN_ARRAY /* inClose */,
                              int          *BEG_IDX,
                              int          *OUT_SIZE,
                              double       *OUT_ARRAY /* outReal */ );

int TA_AVGPRICE_Lookback( void );

