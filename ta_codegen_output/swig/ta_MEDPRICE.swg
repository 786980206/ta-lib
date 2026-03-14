/*
 * TA_MEDPRICE - Median Price
 *
 * Input  = double, double
 * Output = double
 *
 */
TA_RetCode TA_MEDPRICE( int           START_IDX,
                        int           END_IDX,
                        const double *IN_ARRAY /* inHigh */,
                        const double *IN_ARRAY /* inLow */,
                        int          *BEG_IDX,
                        int          *OUT_SIZE,
                        double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_MEDPRICE_Logic( int           START_IDX,
                              int           END_IDX,
                              const double *IN_ARRAY /* inHigh */,
                              const double *IN_ARRAY /* inLow */,
                              int          *BEG_IDX,
                              int          *OUT_SIZE,
                              double       *OUT_ARRAY /* outReal */ );

int TA_MEDPRICE_Lookback( void );

