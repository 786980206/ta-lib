/* ta_lib_globals.c — Global variable definitions for TA-Lib C codegen output.
 * Separated from ta_lib_types.h to avoid ODR violations with separate compilation.
 */
#include "ta_lib_types.h"

/* Global unstable period storage — one definition, declared extern in header */
int ta_unstable_period[TA_FUNC_UNST_ALL];

void TA_SetUnstablePeriod(int id, int period) {
    if (id >= 0 && id < TA_FUNC_UNST_ALL) ta_unstable_period[id] = period;
}
