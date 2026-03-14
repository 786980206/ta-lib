/*
 * TA_HT_TRENDMODE - Hilbert Transform - Trend vs Cycle Mode
 *
 * Input  = double
 * Output = int
 *
 */
TA_RetCode TA_HT_TRENDMODE( int           START_IDX,
                            int           END_IDX,
                            const double *IN_ARRAY /* inReal */,
                            int          *BEG_IDX,
                            int          *OUT_SIZE,
                            int          *OUT_ARRAY /* outInteger */ );

TA_RetCode TA_HT_TRENDMODE_Logic( int           START_IDX,
                                  int           END_IDX,
                                  const double *IN_ARRAY /* inReal */,
                                  int          *BEG_IDX,
                                  int          *OUT_SIZE,
                                  int          *OUT_ARRAY /* outInteger */ );

int TA_HT_TRENDMODE_Lookback( void );

