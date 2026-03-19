/* ta_lib_globals.c — Global variable definitions for TA-Lib C codegen output.
 * Separated from ta_lib_types.h to avoid ODR violations with separate compilation.
 */
#include "ta_lib_types.h"

/* Global unstable period storage — one definition, declared extern in header */
int ta_unstable_period[TA_FUNC_UNST_ALL];

void TA_SetUnstablePeriod(int id, int period) {
    if (id >= 0 && id < TA_FUNC_UNST_ALL) ta_unstable_period[id] = period;
}

/* Candle settings — one definition, declared extern in ta_lib_types.h */
TA_GlobalsType ta_globals_data = {
    .candleSettings = {
        { TA_BodyLong,        TA_RangeType_RealBody, 10, 1.0 },
        { TA_BodyVeryLong,    TA_RangeType_RealBody, 10, 3.0 },
        { TA_BodyShort,       TA_RangeType_RealBody, 10, 1.0 },
        { TA_BodyDoji,        TA_RangeType_HighLow,  10, 0.1 },
        { TA_ShadowLong,      TA_RangeType_RealBody,  0, 1.0 },
        { TA_ShadowVeryLong,  TA_RangeType_RealBody,  0, 2.0 },
        { TA_ShadowShort,     TA_RangeType_Shadows,  10, 1.0 },
        { TA_ShadowVeryShort, TA_RangeType_HighLow,  10, 0.1 },
        { TA_Near,            TA_RangeType_HighLow,   5, 0.2 },
        { TA_Far,             TA_RangeType_HighLow,   5, 0.6 },
        { TA_Equal,           TA_RangeType_HighLow,   5, 0.05 },
    }
};
TA_GlobalsType *TA_Globals = &ta_globals_data;
