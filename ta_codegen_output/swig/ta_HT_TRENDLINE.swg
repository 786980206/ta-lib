/*
 * TA_HT_TRENDLINE - Hilbert Transform - Instantaneous Trendline
 *
 * Input  = double
 * Output = double
 *
 */
TA_RetCode TA_HT_TRENDLINE( int           START_IDX,
                            int           END_IDX,
                            const double *IN_ARRAY /* inReal */,
                            int          *BEG_IDX,
                            int          *OUT_SIZE,
                            double       *OUT_ARRAY /* outReal */ );

TA_RetCode TA_HT_TRENDLINE_Logic( int           START_IDX,
                                  int           END_IDX,
                                  const double *IN_ARRAY /* inReal */,
                                  int          *BEG_IDX,
                                  int          *OUT_SIZE,
                                  double       *OUT_ARRAY /* outReal */ );

int TA_HT_TRENDLINE_Lookback( void );

