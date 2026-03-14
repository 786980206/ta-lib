/*
 * TA_HT_DCPHASE - Hilbert Transform - Dominant Cycle Phase
 *
 * Input  = double
 * Output = double
 *
 */
TA_RetCode TA_HT_DCPHASE( int           START_IDX,
                          int           END_IDX,
                          const double *IN_ARRAY /* inReal */,
                          int          *BEG_IDX,
                          int          *OUT_SIZE,
                          double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_HT_DCPHASE_Logic( int           START_IDX,
                                int           END_IDX,
                                const double *IN_ARRAY /* inReal */,
                                int          *BEG_IDX,
                                int          *OUT_SIZE,
                                double       *OUT_ARRAY /* outReal */ );

int TA_HT_DCPHASE_Lookback( void );

