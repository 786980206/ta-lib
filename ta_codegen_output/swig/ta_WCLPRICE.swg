/*
 * TA_WCLPRICE - Weighted Close Price
 *
 * Input  = double, double, double
 * Output = double
 *
 */
TA_RetCode TA_WCLPRICE( int           START_IDX,
                        int           END_IDX,
                        const double *IN_ARRAY /* inHigh */,
                        const double *IN_ARRAY /* inLow */,
                        const double *IN_ARRAY /* inClose */,
                        int          *BEG_IDX,
                        int          *OUT_SIZE,
                        double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_WCLPRICE_Logic( int           START_IDX,
                              int           END_IDX,
                              const double *IN_ARRAY /* inHigh */,
                              const double *IN_ARRAY /* inLow */,
                              const double *IN_ARRAY /* inClose */,
                              int          *BEG_IDX,
                              int          *OUT_SIZE,
                              double       *OUT_ARRAY /* outReal */ );

int TA_WCLPRICE_Lookback( void );

