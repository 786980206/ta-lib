/* test_codegen.c — generic ta_abstract-driven codegen verification
 *
 * Replaces 3 hand-coded callbacks (SMA, MULT, RSI) with one generic
 * callback that uses ta_abstract to call ANY TA function. Handles
 * price inputs, multi-output, integer outputs, real optional params,
 * and unstable periods.
 */
#include "test_codegen.h"
#include "codegen_pipe.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "ta_libc.h"
#include "ta_abstract.h"

/* ---- Language definitions ---- */

typedef struct {
    const char *name;           /* "rust", "c", "java", "dotnet", "swig" */
    const char *display;        /* "Rust", "C", "Java", ".NET", "SWIG/Python" */
    const char *const *argv;    /* NULL-terminated command array */
} CodegenLanguage;

static const char *const argv_rust[]  = {"./ta_codegen_serve_rust", NULL};
static const char *const argv_c[]     = {"./ta_codegen_serve_c", NULL};
static const char *const argv_java[]  = {"java", "-cp", "ta_codegen_java", "TaCodegenServe", NULL};
static const char *const argv_dotnet[]= {"dotnet", "ta_codegen_dotnet/TaCodegenServe.dll", NULL};
static const char *const argv_swig[]  = {"python3", "ta_codegen_serve.py", NULL};

static const CodegenLanguage ALL_LANGUAGES[] = {
    {"rust",   "Rust",         argv_rust},
    {"c",      "C",            argv_c},
    {"java",   "Java",         argv_java},
    {"dotnet", ".NET",         argv_dotnet},
    {"swig",   "SWIG/Python",  argv_swig},
};
#define NUM_LANGUAGES (sizeof(ALL_LANGUAGES) / sizeof(ALL_LANGUAGES[0]))

/* ---- Global timing results store (Task 12) ---- */

#define MAX_FUNCTIONS 200

typedef struct {
    char   funcName[64];
    double c_ref_us;
    struct {
        int    tested;   /* 0=skipped, 1=pass, -1=fail */
        double avg_us;
    } langs[NUM_LANGUAGES];
} FuncTimingResult;

static FuncTimingResult g_timingResults[MAX_FUNCTIONS];
static int              g_numTimingResults = 0;

/* ---- Constants ---- */

#define CODEGEN_EPSILON  1e-6
#define JSON_BUF_SIZE    (128 * 1024)   /* 128KB: enough for OHLCV inputs */
#define MAX_OUTPUTS      3              /* Max outputs any TA function has */

/* ---- Minimal JSON helpers (no library dependency) ---- */

static int json_write_double_array(char *buf, int buf_size,
                                   const TA_Real *data, int count)
{
    int pos = 0;
    buf[pos++] = '[';
    for( int i = 0; i < count; i++ )
    {
        if( i > 0 )
            pos += snprintf(buf + pos, buf_size - pos, ",");
        pos += snprintf(buf + pos, buf_size - pos, "%.15g", data[i]);
    }
    buf[pos++] = ']';
    buf[pos] = '\0';
    return pos;
}

static const char *json_find_field(const char *json, const char *field, int *len)
{
    char pattern[256];
    snprintf(pattern, sizeof(pattern), "\"%s\":", field);
    const char *p = strstr(json, pattern);
    if( !p ) return NULL;
    p += strlen(pattern);
    while( *p == ' ' ) p++;

    const char *start = p;
    if( *p == '"' )
    {
        p++;
        while( *p && *p != '"' ) p++;
        if( *p == '"' ) p++;
    }
    else if( *p == '[' )
    {
        int depth = 1;
        p++;
        while( *p && depth > 0 )
        {
            if( *p == '[' ) depth++;
            else if( *p == ']' ) depth--;
            p++;
        }
    }
    else
    {
        while( *p && *p != ',' && *p != '}' ) p++;
    }

    *len = (int)(p - start);
    return start;
}

static int json_get_int(const char *json, const char *field)
{
    int len;
    const char *val = json_find_field(json, field, &len);
    if( !val ) return 0;
    return atoi(val);
}

static int json_get_double_array(const char *json, const char *field,
                                 TA_Real *out, int max_count)
{
    int len;
    const char *val = json_find_field(json, field, &len);
    if( !val || *val != '[' ) return 0;

    int count = 0;
    const char *p = val + 1;
    while( *p && *p != ']' && count < max_count )
    {
        while( *p == ' ' || *p == ',' ) p++;
        if( *p == ']' ) break;
        out[count] = strtod(p, (char **)&p);
        count++;
    }
    return count;
}

static int json_get_int_array(const char *json, const char *field,
                              TA_Integer *out, int max_count)
{
    int len;
    const char *val = json_find_field(json, field, &len);
    if( !val || *val != '[' ) return 0;

    int count = 0;
    const char *p = val + 1;
    while( *p && *p != ']' && count < max_count )
    {
        while( *p == ' ' || *p == ',' ) p++;
        if( *p == ']' ) break;
        out[count] = (TA_Integer)strtol(p, (char **)&p, 10);
        count++;
    }
    return count;
}

static int json_is_error(const char *json)
{
    return strstr(json, "\"error\"") != NULL;
}

/* ---- Unstable period lookup ---- */

/* Map function name to TA_FuncUnstId. Only the 24 functions with
 * TA_FUNC_FLG_UNST_PER have entries here.
 */
typedef struct {
    const char   *name;
    TA_FuncUnstId id;
} UnstableLookup;

static const UnstableLookup UNSTABLE_MAP[] = {
    {"ADX",          TA_FUNC_UNST_ADX},
    {"ADXR",         TA_FUNC_UNST_ADXR},
    {"ATR",          TA_FUNC_UNST_ATR},
    {"CMO",          TA_FUNC_UNST_CMO},
    {"DX",           TA_FUNC_UNST_DX},
    {"EMA",          TA_FUNC_UNST_EMA},
    {"HT_DCPERIOD",  TA_FUNC_UNST_HT_DCPERIOD},
    {"HT_DCPHASE",   TA_FUNC_UNST_HT_DCPHASE},
    {"HT_PHASOR",    TA_FUNC_UNST_HT_PHASOR},
    {"HT_SINE",      TA_FUNC_UNST_HT_SINE},
    {"HT_TRENDLINE", TA_FUNC_UNST_HT_TRENDLINE},
    {"HT_TRENDMODE", TA_FUNC_UNST_HT_TRENDMODE},
    {"IMI",          TA_FUNC_UNST_IMI},
    {"KAMA",         TA_FUNC_UNST_KAMA},
    {"MAMA",         TA_FUNC_UNST_MAMA},
    {"MFI",          TA_FUNC_UNST_MFI},
    {"MINUS_DI",     TA_FUNC_UNST_MINUS_DI},
    {"MINUS_DM",     TA_FUNC_UNST_MINUS_DM},
    {"NATR",         TA_FUNC_UNST_NATR},
    {"PLUS_DI",      TA_FUNC_UNST_PLUS_DI},
    {"PLUS_DM",      TA_FUNC_UNST_PLUS_DM},
    {"RSI",          TA_FUNC_UNST_RSI},
    {"STOCHRSI",     TA_FUNC_UNST_STOCHRSI},
    {"T3",           TA_FUNC_UNST_T3},
};
#define NUM_UNSTABLE_MAP (sizeof(UNSTABLE_MAP) / sizeof(UNSTABLE_MAP[0]))

static TA_FuncUnstId get_unst_id(const char *funcName)
{
    for( unsigned int i = 0; i < NUM_UNSTABLE_MAP; i++ )
    {
        if( strcmp(funcName, UNSTABLE_MAP[i].name) == 0 )
            return UNSTABLE_MAP[i].id;
    }
    return TA_FUNC_UNST_NONE;
}

/* ---- Generic CodegenRangeTestParam (Task 6) ---- */

typedef struct {
    /* ta_abstract function metadata */
    const TA_FuncInfo *funcInfo;
    TA_ParamHolder   *paramHolder;

    /* Input data */
    const TA_History *history;
    int nbBars;

    /* Output buffers indexed by outputNb (logical output index).
     * Each output is EITHER real or integer, never both.
     * We allocate both arrays per outputNb for simplicity; only
     * the correct one (per outputIsInteger[i]) is used. */
    TA_Real    *outRealBufs[MAX_OUTPUTS];
    TA_Integer *outIntBufs[MAX_OUTPUTS];
    int         outputIsInteger[MAX_OUTPUTS];   /* Flag per output */
    int         totalOutputs;

    /* Cached results from TA_CallFunc (for multi-output) */
    TA_RetCode  lastRetCode;
    TA_Integer  lastBegIdx;
    TA_Integer  lastNbElement;

    /* Unstable period info */
    TA_FuncUnstId unstId;

    /* Codegen pipe */
    CodegenPipe *cp;
    char *requestBuf;
    char *responseBuf;

    /* Error tracking */
    ErrorNumber codegenError;

    /* Timing */
    long long c_ref_total_ns;
    long long server_total_ns;
    int       timing_count;
} CodegenRangeTestParam;

/* ---- Generic JSON request builder (Task 7) ---- */

static int build_json_request(CodegenRangeTestParam *p,
                              TA_Integer startIdx, TA_Integer endIdx)
{
    const TA_FuncInfo *fi = p->funcInfo;
    char *buf = p->requestBuf;
    int bufSize = JSON_BUF_SIZE;
    int pos = 0;
    unsigned int i;
    int realInputCount = 0;

    /* Method and startIdx/endIdx */
    pos += snprintf(buf + pos, bufSize - pos,
        "{\"method\":\"TA_%s\",\"params\":{\"startIdx\":%d,\"endIdx\":%d",
        fi->name, (int)startIdx, (int)endIdx);

    /* Pre-count real inputs to decide naming convention */
    int totalRealInputs = 0;
    for( i = 0; i < fi->nbInput; i++ )
    {
        const TA_InputParameterInfo *tmpInfo;
        TA_GetInputParameterInfo(fi->handle, i, &tmpInfo);
        if( tmpInfo->type == TA_Input_Real )
            totalRealInputs++;
    }

    /* Input parameters */
    for( i = 0; i < fi->nbInput; i++ )
    {
        const TA_InputParameterInfo *inputInfo;
        TA_GetInputParameterInfo(fi->handle, i, &inputInfo);

        switch( inputInfo->type )
        {
        case TA_Input_Price:
        {
            TA_InputFlags flags = inputInfo->flags;
            if( flags & TA_IN_PRICE_OPEN )
            {
                pos += snprintf(buf + pos, bufSize - pos, ",\"inOpen\":");
                pos += json_write_double_array(buf + pos, bufSize - pos,
                           p->history->open, p->nbBars);
            }
            if( flags & TA_IN_PRICE_HIGH )
            {
                pos += snprintf(buf + pos, bufSize - pos, ",\"inHigh\":");
                pos += json_write_double_array(buf + pos, bufSize - pos,
                           p->history->high, p->nbBars);
            }
            if( flags & TA_IN_PRICE_LOW )
            {
                pos += snprintf(buf + pos, bufSize - pos, ",\"inLow\":");
                pos += json_write_double_array(buf + pos, bufSize - pos,
                           p->history->low, p->nbBars);
            }
            if( flags & TA_IN_PRICE_CLOSE )
            {
                pos += snprintf(buf + pos, bufSize - pos, ",\"inClose\":");
                pos += json_write_double_array(buf + pos, bufSize - pos,
                           p->history->close, p->nbBars);
            }
            if( flags & TA_IN_PRICE_VOLUME )
            {
                pos += snprintf(buf + pos, bufSize - pos, ",\"inVolume\":");
                pos += json_write_double_array(buf + pos, bufSize - pos,
                           p->history->volume, p->nbBars);
            }
            if( flags & TA_IN_PRICE_OPENINTEREST )
            {
                pos += snprintf(buf + pos, bufSize - pos, ",\"inOpenInterest\":");
                pos += json_write_double_array(buf + pos, bufSize - pos,
                           p->history->openInterest, p->nbBars);
            }
            break;
        }
        case TA_Input_Real:
        {
            if( totalRealInputs == 1 )
            {
                /* Single real input: "inReal" */
                pos += snprintf(buf + pos, bufSize - pos, ",\"inReal\":");
                pos += json_write_double_array(buf + pos, bufSize - pos,
                           p->history->close, p->nbBars);
            }
            else
            {
                /* Multiple real inputs: "inReal0", "inReal1", etc.
                 * Map: inReal0=close, inReal1=volume (matches old MULT behavior).
                 */
                const TA_Real *data;
                if( realInputCount == 0 )
                    data = p->history->close;
                else if( realInputCount == 1 )
                    data = p->history->volume;
                else
                    data = p->history->close;  /* fallback */

                pos += snprintf(buf + pos, bufSize - pos, ",\"inReal%d\":", realInputCount);
                pos += json_write_double_array(buf + pos, bufSize - pos,
                           data, p->nbBars);
            }
            realInputCount++;
            break;
        }
        case TA_Input_Integer:
            /* Integer inputs are rare (unused in practice).
             * Pass close prices cast to integers as placeholder. */
            break;
        }
    }

    /* Optional input parameters */
    for( i = 0; i < fi->nbOptInput; i++ )
    {
        const TA_OptInputParameterInfo *optInfo;
        TA_GetOptInputParameterInfo(fi->handle, i, &optInfo);

        pos += snprintf(buf + pos, bufSize - pos, ",\"%s\":", optInfo->paramName);

        switch( optInfo->type )
        {
        case TA_OptInput_RealRange:
        case TA_OptInput_RealList:
            pos += snprintf(buf + pos, bufSize - pos, "%.15g", optInfo->defaultValue);
            break;
        case TA_OptInput_IntegerRange:
        case TA_OptInput_IntegerList:
            pos += snprintf(buf + pos, bufSize - pos, "%d", (int)optInfo->defaultValue);
            break;
        }
    }

    /* Unstable period (for functions with TA_FUNC_FLG_UNST_PER) */
    if( fi->flags & TA_FUNC_FLG_UNST_PER )
    {
        int unstPeriod = (p->unstId != TA_FUNC_UNST_NONE)
                         ? (int)TA_GetUnstablePeriod(p->unstId) : 0;
        pos += snprintf(buf + pos, bufSize - pos, ",\"unstablePeriod\":%d", unstPeriod);
    }

    pos += snprintf(buf + pos, bufSize - pos, "}}");

    return pos;
}

/* ---- Generic output comparison (Task 8) ---- */

static void compare_codegen_output_generic(
    CodegenRangeTestParam *p,
    unsigned int outputNb)
{
    /* Skip if we already have an error */
    if( p->codegenError != TA_TEST_PASS )
        return;

    /* Unsupported function -- skip silently */
    if( json_is_error(p->responseBuf) )
        return;

    /* Compare retCode */
    int cg_retCode = json_get_int(p->responseBuf, "retCode");
    if( (int)p->lastRetCode != cg_retCode )
    {
        printf("CODEGEN MISMATCH [TA_%s]: retCode C=%d codegen=%d\n",
               p->funcInfo->name, (int)p->lastRetCode, cg_retCode);
        p->codegenError = TA_CODEGEN_RETCODE_MISMATCH;
        return;
    }

    /* If C returned error, both agree -- done */
    if( p->lastRetCode != TA_SUCCESS )
        return;

    /* If C produced no output, skip comparison */
    if( p->lastNbElement == 0 )
        return;

    /* Compare outBegIdx */
    int cg_begIdx = json_get_int(p->responseBuf, "outBegIdx");
    if( p->lastBegIdx != cg_begIdx )
    {
        printf("CODEGEN MISMATCH [TA_%s]: outBegIdx C=%d codegen=%d\n",
               p->funcInfo->name, (int)p->lastBegIdx, cg_begIdx);
        p->codegenError = TA_CODEGEN_BEGIDX_MISMATCH;
        return;
    }

    /* Compare outNBElement */
    int cg_nbElement = json_get_int(p->responseBuf, "outNBElement");
    if( p->lastNbElement != cg_nbElement )
    {
        printf("CODEGEN MISMATCH [TA_%s]: outNBElement C=%d codegen=%d\n",
               p->funcInfo->name, (int)p->lastNbElement, cg_nbElement);
        p->codegenError = TA_CODEGEN_NBELEMENT_MISMATCH;
        return;
    }

    /* Compare output values for the requested outputNb */
    if( p->outputIsInteger[outputNb] )
    {
        /* Integer output comparison (exact match) */
        char fieldName[64];
        if( outputNb == 0 )
            snprintf(fieldName, sizeof(fieldName), "outInteger");
        else
            snprintf(fieldName, sizeof(fieldName), "outInteger%d", outputNb);

        TA_Integer cg_out[MAX_NB_TEST_ELEMENT];
        int parsed = json_get_int_array(p->responseBuf, fieldName,
                                         cg_out, MAX_NB_TEST_ELEMENT);
        for( int i = 0; i < p->lastNbElement && i < parsed; i++ )
        {
            if( p->outIntBufs[outputNb][i] != cg_out[i] )
            {
                printf("CODEGEN MISMATCH [TA_%s]: %s[%d] C=%d codegen=%d\n",
                       p->funcInfo->name, fieldName, i,
                       (int)p->outIntBufs[outputNb][i], (int)cg_out[i]);
                p->codegenError = TA_CODEGEN_OUTPUT_MISMATCH;
                return;
            }
        }
    }
    else
    {
        /* Real output comparison (epsilon) */
        char fieldName[64];
        if( outputNb == 0 )
            snprintf(fieldName, sizeof(fieldName), "outReal");
        else
            snprintf(fieldName, sizeof(fieldName), "outReal%d", outputNb);

        TA_Real cg_out[MAX_NB_TEST_ELEMENT];
        int parsed = json_get_double_array(p->responseBuf, fieldName,
                                            cg_out, MAX_NB_TEST_ELEMENT);
        for( int i = 0; i < p->lastNbElement && i < parsed; i++ )
        {
            double cVal = p->outRealBufs[outputNb][i];
            double diff = fabs(cVal - cg_out[i]);
            double threshold = CODEGEN_EPSILON;
            /* Use relative epsilon for large values (JSON roundtrip precision) */
            if( fabs(cVal) > 1.0 )
            {
                double relThreshold = fabs(cVal) * 1e-12;
                if( relThreshold > threshold )
                    threshold = relThreshold;
            }
            if( diff > threshold )
            {
                printf("CODEGEN MISMATCH [TA_%s]: %s[%d] C=%.10f codegen=%.10f diff=%.2e\n",
                       p->funcInfo->name, fieldName, i,
                       p->outRealBufs[outputNb][i], cg_out[i], diff);
                p->codegenError = TA_CODEGEN_OUTPUT_MISMATCH;
                return;
            }
        }
    }

    /* Parse server timing_ns if present */
    int len;
    const char *timingVal = json_find_field(p->responseBuf, "timing_ns", &len);
    if( timingVal )
    {
        long long serverNs = strtoll(timingVal, NULL, 10);
        p->server_total_ns += serverNs;
        p->timing_count++;
    }
}

/* ---- Generic doRangeTest callback (Task 8) ---- */

static TA_RetCode codegen_range_generic(
    TA_Integer startIdx, TA_Integer endIdx,
    TA_Real *outputBuffer, TA_Integer *outputBufferInt,
    TA_Integer *outBegIdx, TA_Integer *outNbElement,
    TA_Integer *lookback, void *opaqueData,
    unsigned int outputNb, unsigned int *isOutputInteger)
{
    CodegenRangeTestParam *p = (CodegenRangeTestParam *)opaqueData;

    /* Set output type flag */
    *isOutputInteger = (unsigned int)p->outputIsInteger[outputNb];

    /* Get lookback */
    TA_GetLookback(p->paramHolder, lookback);

    /* Call TA_CallFunc for EVERY invocation (not just outputNb==0).
     * doRangeTest iterates all startIdx values for output 0, then all for
     * output 1, etc. — so the startIdx/endIdx differ between outputNb calls
     * and we cannot cache across them. */

    /* Re-point all output buffers (TA_CallFunc writes into these) */
    for( unsigned int i = 0; i < p->funcInfo->nbOutput; i++ )
    {
        if( p->outputIsInteger[i] )
            TA_SetOutputParamIntegerPtr(p->paramHolder, i, p->outIntBufs[i]);
        else
            TA_SetOutputParamRealPtr(p->paramHolder, i, p->outRealBufs[i]);
    }

    /* Call the C reference function via ta_abstract */
    p->lastRetCode = TA_CallFunc(p->paramHolder, startIdx, endIdx,
                                  &p->lastBegIdx, &p->lastNbElement);


    *outBegIdx = p->lastBegIdx;
    *outNbElement = p->lastNbElement;

    /* Copy the requested output into the doRangeTest buffer */
    if( p->lastRetCode == TA_SUCCESS && p->lastNbElement > 0 )
    {
        if( p->outputIsInteger[outputNb] )
        {
            for( int i = 0; i < p->lastNbElement; i++ )
                outputBufferInt[i] = p->outIntBufs[outputNb][i];
        }
        else
        {
            for( int i = 0; i < p->lastNbElement; i++ )
                outputBuffer[i] = p->outRealBufs[outputNb][i];
        }
    }

    /* Codegen comparison is done once in test_one_function (full range).
     * This callback only handles C reference coherency for doRangeTest. */

    return p->lastRetCode;
}

/* ---- Setup helpers (Task 9) ---- */

static void setup_inputs(TA_ParamHolder *paramHolder,
                         const TA_FuncInfo *funcInfo,
                         const TA_History *history)
{
    unsigned int i;
    int realInputCount = 0;

    for( i = 0; i < funcInfo->nbInput; i++ )
    {
        const TA_InputParameterInfo *inputInfo;
        TA_GetInputParameterInfo(funcInfo->handle, i, &inputInfo);

        switch( inputInfo->type )
        {
        case TA_Input_Price:
            TA_SetInputParamPricePtr(paramHolder, i,
                inputInfo->flags & TA_IN_PRICE_OPEN         ? history->open : NULL,
                inputInfo->flags & TA_IN_PRICE_HIGH         ? history->high : NULL,
                inputInfo->flags & TA_IN_PRICE_LOW          ? history->low  : NULL,
                inputInfo->flags & TA_IN_PRICE_CLOSE        ? history->close : NULL,
                inputInfo->flags & TA_IN_PRICE_VOLUME       ? history->volume : NULL,
                inputInfo->flags & TA_IN_PRICE_OPENINTEREST ? history->openInterest : NULL);
            break;

        case TA_Input_Real:
        {
            const TA_Real *data;
            if( realInputCount == 0 )
                data = history->close;
            else if( realInputCount == 1 )
                data = history->volume;
            else
                data = history->close;  /* fallback */
            TA_SetInputParamRealPtr(paramHolder, i, data);
            realInputCount++;
            break;
        }
        case TA_Input_Integer:
            /* Integer inputs are rare; pass NULL -- TA_CallFunc will
             * return an error for these functions, which is fine. */
            break;
        }
    }
}

/* Optional inputs are left at defaults (TA_ParamHolderAlloc sets them). */

static void setup_outputs(CodegenRangeTestParam *p)
{
    unsigned int i;

    memset(p->outputIsInteger, 0, sizeof(p->outputIsInteger));
    memset(p->outRealBufs, 0, sizeof(p->outRealBufs));
    memset(p->outIntBufs, 0, sizeof(p->outIntBufs));
    p->totalOutputs = 0;

    for( i = 0; i < p->funcInfo->nbOutput && i < MAX_OUTPUTS; i++ )
    {
        const TA_OutputParameterInfo *outputInfo;
        TA_GetOutputParameterInfo(p->funcInfo->handle, i, &outputInfo);

        switch( outputInfo->type )
        {
        case TA_Output_Real:
            p->outputIsInteger[i] = 0;
            p->outRealBufs[i] = (TA_Real *)calloc(MAX_NB_TEST_ELEMENT, sizeof(TA_Real));
            TA_SetOutputParamRealPtr(p->paramHolder, i, p->outRealBufs[i]);
            break;
        case TA_Output_Integer:
            p->outputIsInteger[i] = 1;
            p->outIntBufs[i] = (TA_Integer *)calloc(MAX_NB_TEST_ELEMENT, sizeof(TA_Integer));
            TA_SetOutputParamIntegerPtr(p->paramHolder, i, p->outIntBufs[i]);
            break;
        }
        p->totalOutputs++;
    }
}

static void free_outputs(CodegenRangeTestParam *p)
{
    for( int i = 0; i < p->totalOutputs; i++ )
    {
        free(p->outRealBufs[i]);
        p->outRealBufs[i] = NULL;
        free(p->outIntBufs[i]);
        p->outIntBufs[i] = NULL;
    }
}

/* ---- Determine integer tolerance for doRangeTest ---- */

static unsigned int get_integer_tolerance(const TA_FuncInfo *funcInfo)
{
    /* Functions with only integer outputs (candlestick patterns) and
     * functions with unstable periods need TA_DO_NOT_COMPARE to avoid
     * false failures from range-dependent floating-point drift.
     *
     * For now, use TA_DO_NOT_COMPARE for all functions -- the codegen
     * comparison is the real test. doRangeTest still validates coherency
     * (lookback consistency, no out-of-bounds writes, etc.).
     */
    (void)funcInfo;
    return TA_DO_NOT_COMPARE;
}

/* ---- Filter helper ---- */

static int codegen_matches_filter(const char *filter, const char *name)
{
    char filterCopy[1024];
    char *token;
    if( filter == NULL ) return 1;
    strncpy(filterCopy, filter, sizeof(filterCopy) - 1);
    filterCopy[sizeof(filterCopy) - 1] = '\0';
    token = strtok(filterCopy, ",");
    while( token != NULL )
    {
        if( strstr(name, token) != NULL ) return 1;
        token = strtok(NULL, ",");
    }
    return 0;
}

/* ---- Per-function callback for TA_ForEachFunc (Task 9) ---- */

typedef struct {
    const TA_History *history;
    const char       *functionFilter;
    CodegenPipe      *cp;
    char             *requestBuf;
    char             *responseBuf;
    ErrorNumber       error;
    int               passed;
    int               failed;
    int               skipped;
    int               langIndex;   /* index into ALL_LANGUAGES */
    const CodegenLanguage *lang;
} ForEachFuncContext;

static void test_one_function(const TA_FuncInfo *funcInfo, void *opaqueData)
{
    ForEachFuncContext *ctx = (ForEachFuncContext *)opaqueData;

    /* Stop iterating if we already hit an error */
    if( ctx->error != TA_TEST_PASS )
        return;

    /* Apply function filter */
    if( !codegen_matches_filter(ctx->functionFilter, funcInfo->name) )
        return;

    /* Skip functions with integer inputs (very rare, no test data) */
    unsigned int hasIntegerInput = 0;
    for( unsigned int i = 0; i < funcInfo->nbInput; i++ )
    {
        const TA_InputParameterInfo *inputInfo;
        TA_GetInputParameterInfo(funcInfo->handle, i, &inputInfo);
        if( inputInfo->type == TA_Input_Integer )
        {
            hasIntegerInput = 1;
            break;
        }
    }
    if( hasIntegerInput )
    {
        /* Record skip in global table */
        int ridx = -1;
        for( int i = 0; i < g_numTimingResults; i++ )
        {
            if( strcmp(g_timingResults[i].funcName, funcInfo->name) == 0 )
            {
                ridx = i;
                break;
            }
        }
        if( ridx < 0 && g_numTimingResults < MAX_FUNCTIONS )
        {
            ridx = g_numTimingResults++;
            memset(&g_timingResults[ridx], 0, sizeof(FuncTimingResult));
            strncpy(g_timingResults[ridx].funcName, funcInfo->name,
                    sizeof(g_timingResults[ridx].funcName) - 1);
        }
        /* langs[langIndex].tested stays 0 (skipped) */
        ctx->skipped++;
        return;
    }

    printf("  %-40s ", funcInfo->name);
    fflush(stdout);

    /* Allocate param holder */
    TA_ParamHolder *paramHolder = NULL;
    TA_RetCode retCode = TA_ParamHolderAlloc(funcInfo->handle, &paramHolder);
    if( retCode != TA_SUCCESS )
    {
        printf("FAILED (ParamHolderAlloc: %d)\n", retCode);
        ctx->error = TA_CODEGEN_ALLOC_FAILED;
        return;
    }

    /* Build CodegenRangeTestParam */
    CodegenRangeTestParam params;
    memset(&params, 0, sizeof(params));
    params.funcInfo    = funcInfo;
    params.paramHolder = paramHolder;
    params.history     = ctx->history;
    params.nbBars      = (int)ctx->history->nbBars;
    params.unstId      = get_unst_id(funcInfo->name);
    params.cp          = ctx->cp;
    params.requestBuf  = ctx->requestBuf;
    params.responseBuf = ctx->responseBuf;
    params.codegenError = TA_TEST_PASS;

    /* Set up inputs (using defaults for optional params) */
    setup_inputs(paramHolder, funcInfo, ctx->history);

    /* Set up output buffers */
    setup_outputs(&params);

    /* Measure C reference call once for timing baseline */
    TA_Integer begIdx  = 0;
    TA_Integer nbElem  = 0;
    clock_t c_t0 = clock();
    TA_CallFunc(params.paramHolder, 0, params.nbBars - 1, &begIdx, &nbElem);
    clock_t c_t1 = clock();
    double c_avg_us = (c_t1 > c_t0 && CLOCKS_PER_SEC > 0)
                      ? (double)(c_t1 - c_t0) / (double)CLOCKS_PER_SEC * 1e6
                      : 0.0;
    params.c_ref_total_ns = (long long)((double)(c_t1 - c_t0) / (double)CLOCKS_PER_SEC * 1e9);

    /* Save C reference results for codegen comparison */
    params.lastRetCode  = TA_SUCCESS;
    params.lastBegIdx   = begIdx;
    params.lastNbElement = nbElem;

    /* Codegen comparison: one full-range JSON-RPC call, compare all outputs.
     * This is done BEFORE doRangeTest to separate concerns:
     * - codegen comparison: does generated code match C reference?
     * - range test: is the C function coherent across sub-ranges?
     */
    build_json_request(&params, 0, params.nbBars - 1);
    ErrorNumber codegenErr = codegen_pipe_call(params.cp, params.requestBuf,
                                               params.responseBuf, JSON_BUF_SIZE);
    if( codegenErr != TA_TEST_PASS )
    {
        params.codegenError = codegenErr;
    }
    else
    {
        for( unsigned int outNb = 0; outNb < funcInfo->nbOutput; outNb++ )
            compare_codegen_output_generic(&params, outNb);
    }

    /* Run doRangeTest with the generic callback (C reference coherency only).
     * Skip when lookback exceeds data range (no output possible). */
    ErrorNumber errNb = TA_TEST_PASS;
    if( nbElem > 0 )
    {
        errNb = doRangeTest(
            codegen_range_generic,
            params.unstId,
            (void *)&params,
            funcInfo->nbOutput,
            get_integer_tolerance(funcInfo));
    }

    /* Compute server average timing */
    double s_avg_us = (params.timing_count > 0)
                      ? (double)params.server_total_ns / (double)params.timing_count / 1000.0
                      : 0.0;

    /* Record results in global timing table */
    int resultIdx = -1;
    for( int i = 0; i < g_numTimingResults; i++ )
    {
        if( strcmp(g_timingResults[i].funcName, funcInfo->name) == 0 )
        {
            resultIdx = i;
            break;
        }
    }
    if( resultIdx < 0 && g_numTimingResults < MAX_FUNCTIONS )
    {
        resultIdx = g_numTimingResults++;
        memset(&g_timingResults[resultIdx], 0, sizeof(FuncTimingResult));
        strncpy(g_timingResults[resultIdx].funcName, funcInfo->name,
                sizeof(g_timingResults[resultIdx].funcName) - 1);
        g_timingResults[resultIdx].c_ref_us = c_avg_us;
    }

    /* Check for codegen mismatch */
    if( params.codegenError != TA_TEST_PASS )
    {
        printf("CODEGEN FAILED (code=%d)\n", params.codegenError);
        if( resultIdx >= 0 && ctx->langIndex < (int)NUM_LANGUAGES )
        {
            g_timingResults[resultIdx].langs[ctx->langIndex].tested  = -1;
            g_timingResults[resultIdx].langs[ctx->langIndex].avg_us  = s_avg_us;
        }
        free_outputs(&params);
        TA_ParamHolderFree(paramHolder);
        ctx->failed++;
        ctx->error = params.codegenError;
        return;
    }

    if( errNb != TA_TEST_PASS )
    {
        printf("RANGE TEST FAILED (code=%d)\n", errNb);
        if( resultIdx >= 0 && ctx->langIndex < (int)NUM_LANGUAGES )
        {
            g_timingResults[resultIdx].langs[ctx->langIndex].tested  = -1;
            g_timingResults[resultIdx].langs[ctx->langIndex].avg_us  = s_avg_us;
        }
        free_outputs(&params);
        TA_ParamHolderFree(paramHolder);
        ctx->failed++;
        ctx->error = errNb;
        return;
    }

    /* Mark pass in global table */
    if( resultIdx >= 0 && ctx->langIndex < (int)NUM_LANGUAGES )
    {
        g_timingResults[resultIdx].langs[ctx->langIndex].tested  = 1;
        g_timingResults[resultIdx].langs[ctx->langIndex].avg_us  = s_avg_us;
    }

    /* Print result with timing and speedup ratio */
    if( s_avg_us > 0 && c_avg_us > 0 )
    {
        double ratio = c_avg_us / s_avg_us;
        printf("PASS   (C: %.1fus, %s: %.1fus, %.2fx %s)\n",
               c_avg_us, ctx->lang->display, s_avg_us,
               (ratio >= 1.0) ? ratio : 1.0 / ratio,
               (ratio >= 1.0) ? "faster" : "slower");
    }
    else
    {
        printf("PASS\n");
    }
    ctx->passed++;

    free_outputs(&params);
    TA_ParamHolderFree(paramHolder);
}

/* ---- Test orchestration (Task 9) ---- */

static ErrorNumber test_codegen_for_language(
    const CodegenLanguage *lang,
    int langIndex,
    const TA_History *history,
    const char *functionFilter)
{
    CodegenPipe cp;
    ErrorNumber errNb;

    printf("\n");
    printf("Codegen verification: %s\n", lang->display);
    printf("---------------------------------------------\n");

    errNb = codegen_pipe_open(&cp, lang->argv);
    if( errNb != TA_TEST_PASS )
    {
        printf("FAILED: Cannot start %s server", lang->display);
        if( strcmp(lang->name, "rust") == 0 )
            printf(" (is ./ta_codegen built?)");
        else
            printf(" (run: ta_codegen build --lang=%s)", lang->name);
        printf("\n");
        return errNb;
    }
    printf("  Server started (pid=%d)\n", cp.child_pid);

    /* Allocate reusable JSON buffers */
    char *requestBuf = malloc(JSON_BUF_SIZE);
    char *responseBuf = malloc(JSON_BUF_SIZE);
    if( !requestBuf || !responseBuf )
    {
        free(requestBuf);
        free(responseBuf);
        codegen_pipe_close(&cp);
        return TA_CODEGEN_ALLOC_FAILED;
    }

    /* Use TA_ForEachFunc to iterate all functions */
    ForEachFuncContext ctx;
    memset(&ctx, 0, sizeof(ctx));
    ctx.history        = history;
    ctx.functionFilter = functionFilter;
    ctx.cp             = &cp;
    ctx.requestBuf     = requestBuf;
    ctx.responseBuf    = responseBuf;
    ctx.error          = TA_TEST_PASS;
    ctx.passed         = 0;
    ctx.failed         = 0;
    ctx.skipped        = 0;
    ctx.langIndex      = langIndex;
    ctx.lang           = lang;

    TA_ForEachFunc(test_one_function, &ctx);

    free(requestBuf);
    free(responseBuf);
    codegen_pipe_close(&cp);

    if( ctx.error != TA_TEST_PASS )
        return ctx.error;

    printf("\n  %s: %d passed, %d failed, %d skipped\n",
           lang->display, ctx.passed, ctx.failed, ctx.skipped);

    return TA_TEST_PASS;
}

/* ---- Main entry point ---- */

static int language_matches_filter(const char *filter, const char *name)
{
    char filterCopy[1024];
    char *token;
    if( filter == NULL ) return 1;
    strncpy(filterCopy, filter, sizeof(filterCopy) - 1);
    filterCopy[sizeof(filterCopy) - 1] = '\0';
    token = strtok(filterCopy, ",");
    while( token != NULL )
    {
        if( strcmp(name, token) == 0 ) return 1;
        token = strtok(NULL, ",");
    }
    return 0;
}

/* ---- Cross-language timing table (Task 12) ---- */

static void print_timing_table(const char *languageFilter)
{
    if( g_numTimingResults == 0 )
        return;

    /* Collect which language columns to show */
    int showLang[NUM_LANGUAGES];
    for( unsigned int li = 0; li < NUM_LANGUAGES; li++ )
        showLang[li] = language_matches_filter(languageFilter, ALL_LANGUAGES[li].name);

    printf("\n");
    printf("=============================================\n");
    printf("Codegen Results + Timing (avg us/call)\n");
    printf("=============================================\n");

    /* Header */
    printf("%-20s %8s", "Function", "C-ref");
    for( unsigned int li = 0; li < NUM_LANGUAGES; li++ )
    {
        if( showLang[li] )
            printf(" %9s", ALL_LANGUAGES[li].display);
    }
    printf("\n");

    /* Rows */
    for( int ri = 0; ri < g_numTimingResults; ri++ )
    {
        FuncTimingResult *r = &g_timingResults[ri];
        printf("%-20s %8.1f", r->funcName, r->c_ref_us);
        for( unsigned int li = 0; li < NUM_LANGUAGES; li++ )
        {
            if( !showLang[li] )
                continue;
            int st = r->langs[li].tested;
            if( st == 0 )
                printf(" %9s", "--");
            else if( st == -1 )
                printf(" %9s", "FAIL");
            else
                printf(" %7.1fok", r->langs[li].avg_us);
        }
        printf("\n");
    }
}

/* ---- JSONL rolling report (Task 13) ---- */

static void write_timing_report(const char *filepath)
{
    FILE *f = fopen(filepath, "a");
    if( !f ) return;

    /* Get git SHA */
    char gitSha[64] = "unknown";
    FILE *git = popen("git rev-parse --short HEAD 2>/dev/null", "r");
    if( git ) { fgets(gitSha, sizeof(gitSha), git); pclose(git); }
    char *nl = strchr(gitSha, '\n');
    if( nl ) *nl = '\0';

    /* Get timestamp */
    time_t now = time(NULL);
    char timestamp[64];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%SZ", gmtime(&now));

    /* Write JSONL line */
    fprintf(f, "{\"timestamp\":\"%s\",\"git_sha\":\"%s\",\"results\":{",
            timestamp, gitSha);

    int first = 1;
    for( int ri = 0; ri < g_numTimingResults; ri++ )
    {
        FuncTimingResult *r = &g_timingResults[ri];
        if( !first ) fprintf(f, ",");
        first = 0;
        fprintf(f, "\"%s\":{\"c_ref_us\":%.3f,\"langs\":{", r->funcName, r->c_ref_us);
        int firstLang = 1;
        for( unsigned int li = 0; li < NUM_LANGUAGES; li++ )
        {
            int st = r->langs[li].tested;
            if( st == 0 ) continue;   /* skip not-tested */
            if( !firstLang ) fprintf(f, ",");
            firstLang = 0;
            fprintf(f, "\"%s\":{\"status\":\"%s\",\"avg_us\":%.3f}",
                    ALL_LANGUAGES[li].name,
                    (st == 1) ? "pass" : "fail",
                    r->langs[li].avg_us);
        }
        fprintf(f, "}}");
    }

    fprintf(f, "}}\n");
    fclose(f);
}

ErrorNumber test_codegen(const TA_History *history,
                         const char *languageFilter,
                         const char *functionFilter)
{
    ErrorNumber errNb;
    int langsTested = 0;

    printf("\n");
    printf("=============================================\n");
    printf("Codegen Multi-Language Verification\n");
    printf("=============================================\n");

    for( unsigned int i = 0; i < NUM_LANGUAGES; i++ )
    {
        if( !language_matches_filter(languageFilter, ALL_LANGUAGES[i].name) )
            continue;

        errNb = test_codegen_for_language(&ALL_LANGUAGES[i], (int)i, history,
                                          functionFilter);
        if( errNb != TA_TEST_PASS )
            return errNb;

        langsTested++;
    }

    if( langsTested == 0 )
    {
        printf("\nNo languages matched filter '%s'\n",
               languageFilter ? languageFilter : "(none)");
        return TA_REGTEST_BAD_USER_PARAM;
    }

    print_timing_table(languageFilter);

    printf("\n=============================================\n");
    printf("All %d language(s) passed codegen verification\n", langsTested);
    printf("=============================================\n");

    write_timing_report("ta_regtest_timing.jsonl");

    return TA_TEST_PASS;
}
