/* ta_lib_types.h — Hand-written TA-Lib type definitions for C.
 * These are stable and rarely change. Do not auto-generate.
 */
#ifndef TA_LIB_TYPES_H
#define TA_LIB_TYPES_H

#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Core types */
typedef int TA_RetCode;
typedef double TA_Real;
typedef int TA_Integer;

#define TA_SUCCESS 0
#define TA_BAD_PARAM 2
#define TA_ALLOC_ERR 3
#define TA_OUT_OF_RANGE_START_INDEX 12
#define TA_OUT_OF_RANGE_END_INDEX 13
#define TA_LIB_API

/* Unstable period function IDs */
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

/* Global unstable period storage — defined in ta_lib_globals.c */
extern int ta_unstable_period[TA_FUNC_UNST_ALL];
#define TA_GLOBALS_UNSTABLE_PERIOD(id, name) ta_unstable_period[id]

extern void TA_SetUnstablePeriod(int id, int period);

/* Compatibility mode */
#define TA_GLOBALS_COMPATIBILITY 0
#define TA_COMPATIBILITY_DEFAULT 0
#define TA_COMPATIBILITY_METASTOCK 1
#define ENUM_VALUE(type, c_val, rust_val) (c_val)

/* Candle settings infrastructure */
typedef int TA_RangeType;
#define TA_RangeType_RealBody 0
#define TA_RangeType_HighLow  1
#define TA_RangeType_Shadows  2

typedef int TA_CandleSettingType;
#define TA_BodyLong         0
#define TA_BodyVeryLong     1
#define TA_BodyShort        2
#define TA_BodyDoji         3
#define TA_ShadowLong       4
#define TA_ShadowVeryLong   5
#define TA_ShadowShort      6
#define TA_ShadowVeryShort  7
#define TA_Near             8
#define TA_Far              9
#define TA_Equal           10
#define TA_AllCandleSettings 11

typedef struct {
    TA_CandleSettingType settingType;
    TA_RangeType rangeType;
    int avgPeriod;
    double factor;
} TA_CandleSetting;

typedef struct {
    TA_CandleSetting candleSettings[TA_AllCandleSettings];
} TA_GlobalsType;

static TA_GlobalsType ta_globals_data = {
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
static TA_GlobalsType *TA_Globals = &ta_globals_data;

/* Utility macros */
#define TA_EPSILON (0.00000000000001)
#define TA_IS_ZERO(v)        (((-TA_EPSILON)<v)&&(v<TA_EPSILON))
#define TA_IS_ZERO_OR_NEG(v) (v<TA_EPSILON)

#define ARRAY_MEMMOVE(dst, dstIdx, src, srcIdx, count) \
    memmove(&(dst)[dstIdx], &(src)[srcIdx], (count) * sizeof(double))
#define ARRAY_MEMMOVEMIX(dst, dstIdx, src, srcIdx, count) \
    do { for(int _i=0; _i<(count); _i++) (dst)[(dstIdx)+_i] = (double)(src)[(srcIdx)+_i]; } while(0)

/* Moving average types */
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

#endif /* TA_LIB_TYPES_H */
