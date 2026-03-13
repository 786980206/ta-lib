/* Auto-generated ta_func.h stub for standalone server compilation. */
#ifndef TA_FUNC_H
#define TA_FUNC_H

typedef int TA_RetCode;
typedef double TA_Real;
typedef int TA_Integer;
#define TA_SUCCESS 0
#define TA_BAD_PARAM 2
#define TA_OUT_OF_RANGE_START_INDEX 12
#define TA_OUT_OF_RANGE_END_INDEX 13
#define TA_ALLOC_ERR 3
#define TA_LIB_API

#define TA_FUNC_UNST_ADX 0
#define TA_FUNC_UNST_ADXR 1
#define TA_FUNC_UNST_ATR 2
#define TA_FUNC_UNST_CMO 3
#define TA_FUNC_UNST_DX 4
#define TA_FUNC_UNST_EMA 5
#define TA_FUNC_UNST_HT_DCPERIOD 6
#define TA_FUNC_UNST_HT_DCPHASE 7
#define TA_FUNC_UNST_HT_PHASOR 8
#define TA_FUNC_UNST_HT_SINE 9
#define TA_FUNC_UNST_HT_TRENDLINE 10
#define TA_FUNC_UNST_HT_TRENDMODE 11
#define TA_FUNC_UNST_IMI 12
#define TA_FUNC_UNST_KAMA 13
#define TA_FUNC_UNST_MAMA 14
#define TA_FUNC_UNST_MFI 15
#define TA_FUNC_UNST_MINUS_DI 16
#define TA_FUNC_UNST_MINUS_DM 17
#define TA_FUNC_UNST_NATR 18
#define TA_FUNC_UNST_PLUS_DI 19
#define TA_FUNC_UNST_PLUS_DM 20
#define TA_FUNC_UNST_RSI 21
#define TA_FUNC_UNST_STOCHRSI 22
#define TA_FUNC_UNST_T3 23
#define TA_FUNC_UNST_ALL 24
#define TA_FUNC_UNST_NONE 99
int ta_unstable_period[TA_FUNC_UNST_ALL];
#define TA_GLOBALS_UNSTABLE_PERIOD(id, name) ta_unstable_period[id]
void TA_SetUnstablePeriod(int id, int period) {
    if (id >= 0 && id < TA_FUNC_UNST_ALL) ta_unstable_period[id] = period;
}

#define TA_GLOBALS_COMPATIBILITY 0
#define TA_COMPATIBILITY_DEFAULT 0
#define TA_COMPATIBILITY_METASTOCK 1
#define ENUM_VALUE(type, c_val, rust_val) (c_val)

#define TA_IS_ZERO(v) ((-(0.00000001)) < (v) && (v) < (0.00000001))
#define TA_IS_ZERO_OR_NEG(v) ((v) < (0.00000001))

#include <string.h>
#define ARRAY_MEMMOVE(dst, dstIdx, src, srcIdx, count) \
    memmove(&(dst)[dstIdx], &(src)[srcIdx], (count) * sizeof(double))
#define ARRAY_MEMMOVEMIX(dst, dstIdx, src, srcIdx, count) \
    do { for(int _i=0; _i<(count); _i++) (dst)[(dstIdx)+_i] = (double)(src)[(srcIdx)+_i]; } while(0)

typedef int TA_MAType;
#define TA_MAType_SMA   0
#define TA_MAType_EMA   1
#define TA_MAType_WMA   2
#define TA_MAType_DEMA  3
#define TA_MAType_TEMA  4
#define TA_MAType_TRIMA 5
#define TA_MAType_KAMA  6
#define TA_MAType_MAMA  7
#define TA_MAType_T3    8
#define ENUM_CASE(type, c_val, pascal_val) (c_val)

#endif /* TA_FUNC_H */
