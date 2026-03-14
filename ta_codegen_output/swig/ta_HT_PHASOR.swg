/*
 * TA_HT_PHASOR - Hilbert Transform - Phasor Components
 *
 * Input  = double
 * Output = double, double
 *
 */
TA_RetCode TA_HT_PHASOR( int           START_IDX,
                         int           END_IDX,
                         const double *IN_ARRAY /* inReal */,
                         int          *BEG_IDX,
                         int          *OUT_SIZE,
                         double       *OUT_ARRAY /* outInPhase */,
                         double       *OUT_ARRAY /* outQuadrature */ );

TA_RetCode TA_HT_PHASOR_Logic( int           START_IDX,
                               int           END_IDX,
                               const double *IN_ARRAY /* inReal */,
                               int          *BEG_IDX,
                               int          *OUT_SIZE,
                               double       *OUT_ARRAY /* outInPhase */,
                               double       *OUT_ARRAY /* outQuadrature */ );

int TA_HT_PHASOR_Lookback( void );

