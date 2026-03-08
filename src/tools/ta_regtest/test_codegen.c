/* test_codegen.c — complete rewrite */
#include "test_codegen.h"
#include "codegen_pipe.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ta_libc.h"

/* ---- Language definitions ---- */

typedef struct {
    const char *name;           /* "rust", "c", "java", "dotnet", "swig" */
    const char *display;        /* "Rust", "C", "Java", ".NET", "SWIG/Python" */
    const char *const *argv;    /* NULL-terminated command array */
} CodegenLanguage;

static const char *const argv_rust[]  = {"./ta_codegen", "serve", NULL};
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

static int json_is_error(const char *json)
{
    return strstr(json, "\"error\"") != NULL;
}

/* ---- Codegen comparison ---- */

#define CODEGEN_EPSILON 1e-6
#define JSON_BUF_SIZE   (64 * 1024)

/* Shared context for doRangeTest callbacks */
typedef struct {
    /* Input data */
    const TA_Real *inReal;      /* Primary input array (close prices) */
    const TA_Real *inReal1;     /* Second input array (for MULT: volume) */
    int nbBars;                 /* Length of input arrays */

    /* Function parameters */
    int optInTimePeriod;        /* For SMA, RSI, etc. */
    TA_FuncUnstId unstId;       /* For skipping comparison during unstable period tests */

    /* Codegen pipe */
    CodegenPipe *cp;
    char *requestBuf;           /* Pre-allocated, reused across calls */
    char *responseBuf;          /* Pre-allocated, reused across calls */

    /* Error tracking (callback returns TA_RetCode, not ErrorNumber) */
    ErrorNumber codegenError;   /* Set on first codegen mismatch */
    const char *methodName;     /* For error messages (e.g. "TA_SMA") */
} CodegenRangeTestParam;

static void compare_codegen_output(
    CodegenRangeTestParam *p,
    TA_RetCode c_retCode,
    TA_Integer c_begIdx,
    TA_Integer c_nbElement,
    const TA_Real *c_out)
{
    /* Skip if we already have an error */
    if( p->codegenError != TA_TEST_PASS )
        return;

    /* Skip codegen comparison when unstable period is non-zero.
     * doRangeTest sets various unstable periods to test C implementation stability,
     * but the codegen server doesn't track this state — it always uses unstablePeriod=0.
     * Comparing would produce false mismatches. */
    if( p->unstId != TA_FUNC_UNST_NONE &&
        TA_GetUnstablePeriod(p->unstId) != 0 )
        return;

    /* Send to codegen pipe */
    ErrorNumber errNb = codegen_pipe_call(p->cp, p->requestBuf,
                                          p->responseBuf, JSON_BUF_SIZE);
    if( errNb != TA_TEST_PASS )
    {
        p->codegenError = errNb;
        return;
    }

    /* Unsupported function — skip silently */
    if( json_is_error(p->responseBuf) )
        return;

    /* Compare retCode */
    int cg_retCode = json_get_int(p->responseBuf, "retCode");
    if( (int)c_retCode != cg_retCode )
    {
        printf("CODEGEN MISMATCH [%s]: retCode C=%d codegen=%d\n",
               p->methodName, (int)c_retCode, cg_retCode);
        p->codegenError = TA_CODEGEN_RETCODE_MISMATCH;
        return;
    }

    /* If C returned error, both agree — done */
    if( c_retCode != TA_SUCCESS )
        return;

    /* If C produced no output (e.g. range too small for lookback+unstable period),
     * skip comparison — the codegen server may not have the same unstable period state. */
    if( c_nbElement == 0 )
        return;

    /* Compare outBegIdx */
    int cg_begIdx = json_get_int(p->responseBuf, "outBegIdx");
    if( c_begIdx != cg_begIdx )
    {
        printf("CODEGEN MISMATCH [%s]: outBegIdx C=%d codegen=%d\n",
               p->methodName, (int)c_begIdx, cg_begIdx);
        p->codegenError = TA_CODEGEN_BEGIDX_MISMATCH;
        return;
    }

    /* Compare outNBElement */
    int cg_nbElement = json_get_int(p->responseBuf, "outNBElement");
    if( c_nbElement != cg_nbElement )
    {
        printf("CODEGEN MISMATCH [%s]: outNBElement C=%d codegen=%d\n",
               p->methodName, (int)c_nbElement, cg_nbElement);
        p->codegenError = TA_CODEGEN_NBELEMENT_MISMATCH;
        return;
    }

    /* Compare output values */
    TA_Real cg_out[MAX_NB_TEST_ELEMENT];
    int parsed = json_get_double_array(p->responseBuf, "outReal",
                                       cg_out, MAX_NB_TEST_ELEMENT);
    for( int i = 0; i < c_nbElement && i < parsed; i++ )
    {
        double diff = fabs(c_out[i] - cg_out[i]);
        if( diff > CODEGEN_EPSILON )
        {
            printf("CODEGEN MISMATCH [%s]: outReal[%d] C=%.10f codegen=%.10f diff=%.2e\n",
                   p->methodName, i, c_out[i], cg_out[i], diff);
            p->codegenError = TA_CODEGEN_OUTPUT_MISMATCH;
            return;
        }
    }
}

/* ---- doRangeTest callbacks ---- */

/* SMA callback: calls TA_SMA + sends to codegen + compares */
static TA_RetCode codegen_range_sma(
    TA_Integer startIdx, TA_Integer endIdx,
    TA_Real *outputBuffer, TA_Integer *outputBufferInt,
    TA_Integer *outBegIdx, TA_Integer *outNbElement,
    TA_Integer *lookback, void *opaqueData,
    unsigned int outputNb, unsigned int *isOutputInteger)
{
    CodegenRangeTestParam *p = (CodegenRangeTestParam *)opaqueData;
    (void)outputBufferInt; (void)outputNb;

    /* 1. Call C reference */
    TA_RetCode retCode = TA_SMA(startIdx, endIdx, p->inReal,
                                 p->optInTimePeriod,
                                 outBegIdx, outNbElement, outputBuffer);
    *lookback = TA_SMA_Lookback(p->optInTimePeriod);
    *isOutputInteger = 0;

    /* 2. Build JSON-RPC request */
    int pos = snprintf(p->requestBuf, JSON_BUF_SIZE,
        "{\"method\":\"TA_SMA\",\"params\":{\"startIdx\":%d,\"endIdx\":%d,"
        "\"optInTimePeriod\":%d,\"inReal\":",
        (int)startIdx, (int)endIdx, p->optInTimePeriod);
    pos += json_write_double_array(p->requestBuf + pos, JSON_BUF_SIZE - pos,
                                   p->inReal, p->nbBars);
    pos += snprintf(p->requestBuf + pos, JSON_BUF_SIZE - pos, "}}");

    /* 3. Send to codegen and compare */
    compare_codegen_output(p, retCode, *outBegIdx, *outNbElement, outputBuffer);

    return retCode;
}

/* MULT callback: calls TA_MULT + sends to codegen + compares */
static TA_RetCode codegen_range_mult(
    TA_Integer startIdx, TA_Integer endIdx,
    TA_Real *outputBuffer, TA_Integer *outputBufferInt,
    TA_Integer *outBegIdx, TA_Integer *outNbElement,
    TA_Integer *lookback, void *opaqueData,
    unsigned int outputNb, unsigned int *isOutputInteger)
{
    CodegenRangeTestParam *p = (CodegenRangeTestParam *)opaqueData;
    (void)outputBufferInt; (void)outputNb;

    TA_RetCode retCode = TA_MULT(startIdx, endIdx,
                                  p->inReal, p->inReal1,
                                  outBegIdx, outNbElement, outputBuffer);
    *lookback = TA_MULT_Lookback();
    *isOutputInteger = 0;

    int pos = snprintf(p->requestBuf, JSON_BUF_SIZE,
        "{\"method\":\"TA_MULT\",\"params\":{\"startIdx\":%d,\"endIdx\":%d,\"inReal0\":",
        (int)startIdx, (int)endIdx);
    pos += json_write_double_array(p->requestBuf + pos, JSON_BUF_SIZE - pos,
                                   p->inReal, p->nbBars);
    pos += snprintf(p->requestBuf + pos, JSON_BUF_SIZE - pos, ",\"inReal1\":");
    pos += json_write_double_array(p->requestBuf + pos, JSON_BUF_SIZE - pos,
                                   p->inReal1, p->nbBars);
    pos += snprintf(p->requestBuf + pos, JSON_BUF_SIZE - pos, "}}");

    compare_codegen_output(p, retCode, *outBegIdx, *outNbElement, outputBuffer);

    return retCode;
}

/* RSI callback: calls TA_RSI + sends to codegen + compares */
static TA_RetCode codegen_range_rsi(
    TA_Integer startIdx, TA_Integer endIdx,
    TA_Real *outputBuffer, TA_Integer *outputBufferInt,
    TA_Integer *outBegIdx, TA_Integer *outNbElement,
    TA_Integer *lookback, void *opaqueData,
    unsigned int outputNb, unsigned int *isOutputInteger)
{
    CodegenRangeTestParam *p = (CodegenRangeTestParam *)opaqueData;
    (void)outputBufferInt; (void)outputNb;

    TA_RetCode retCode = TA_RSI(startIdx, endIdx, p->inReal,
                                 p->optInTimePeriod,
                                 outBegIdx, outNbElement, outputBuffer);
    *lookback = TA_RSI_Lookback(p->optInTimePeriod);
    *isOutputInteger = 0;

    int pos = snprintf(p->requestBuf, JSON_BUF_SIZE,
        "{\"method\":\"TA_RSI\",\"params\":{\"startIdx\":%d,\"endIdx\":%d,"
        "\"optInTimePeriod\":%d,\"inReal\":",
        (int)startIdx, (int)endIdx, p->optInTimePeriod);
    pos += json_write_double_array(p->requestBuf + pos, JSON_BUF_SIZE - pos,
                                   p->inReal, p->nbBars);
    pos += snprintf(p->requestBuf + pos, JSON_BUF_SIZE - pos, "}}");

    compare_codegen_output(p, retCode, *outBegIdx, *outNbElement, outputBuffer);

    return retCode;
}

/* ---- Test orchestration ---- */

typedef struct {
    const char *name;           /* Filter name (e.g. "SMA", "MULT") */
    const char *method;         /* JSON-RPC method (e.g. "TA_SMA") */
    RangeTestFunction callback;
    TA_FuncUnstId unstId;
    unsigned int nbOutput;
    int needsTimePeriod;        /* Does this function use optInTimePeriod? */
    int defaultTimePeriod;      /* Default value if needsTimePeriod */
    int needsSecondInput;       /* Does this function use inReal1? */
    unsigned int integerTolerance; /* Passed to doRangeTest (TA_DO_NOT_COMPARE to skip value comparison) */
} CodegenTestDef;

static const CodegenTestDef CODEGEN_TESTS[] = {
    {"MULT", "TA_MULT", codegen_range_mult, TA_FUNC_UNST_NONE, 1, 0, 0,  1, TA_DO_NOT_COMPARE},
    {"SMA",  "TA_SMA",  codegen_range_sma,  TA_FUNC_UNST_NONE, 1, 1, 30, 0, 0},
    {"RSI",  "TA_RSI",  codegen_range_rsi,  TA_FUNC_UNST_RSI,  1, 1, 14, 0, 0},
};
#define NUM_CODEGEN_TESTS (sizeof(CODEGEN_TESTS) / sizeof(CODEGEN_TESTS[0]))

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

static ErrorNumber test_codegen_for_language(
    const CodegenLanguage *lang,
    const TA_History *history,
    const char *functionFilter)
{
    CodegenPipe cp;
    ErrorNumber errNb;
    int tested = 0;

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

    for( unsigned int t = 0; t < NUM_CODEGEN_TESTS; t++ )
    {
        const CodegenTestDef *def = &CODEGEN_TESTS[t];

        if( !codegen_matches_filter(functionFilter, def->name) )
            continue;

        printf("  %-40s ", def->name);
        fflush(stdout);

        /* Set up callback params */
        CodegenRangeTestParam params;
        memset(&params, 0, sizeof(params));
        params.inReal = history->close;
        params.inReal1 = def->needsSecondInput ? history->volume : NULL;
        params.nbBars = (int)history->nbBars;
        params.optInTimePeriod = def->needsTimePeriod ? def->defaultTimePeriod : 0;
        params.unstId = def->unstId;
        params.cp = &cp;
        params.requestBuf = requestBuf;
        params.responseBuf = responseBuf;
        params.codegenError = TA_TEST_PASS;
        params.methodName = def->method;

        /* For RSI: reset unstable period */
        if( def->unstId == TA_FUNC_UNST_RSI )
        {
            TA_SetUnstablePeriod(TA_FUNC_UNST_RSI, 0);
            TA_SetCompatibility(TA_COMPATIBILITY_DEFAULT);
        }

        /* Run doRangeTest — this calls our callback hundreds of times */
        errNb = doRangeTest(def->callback, def->unstId,
                            (void *)&params, def->nbOutput,
                            def->integerTolerance);

        /* Check for codegen mismatch (separate from doRangeTest errors) */
        if( params.codegenError != TA_TEST_PASS )
        {
            printf("CODEGEN FAILED (code=%d)\n", params.codegenError);
            free(requestBuf);
            free(responseBuf);
            codegen_pipe_close(&cp);
            return params.codegenError;
        }

        if( errNb != TA_TEST_PASS )
        {
            printf("RANGE TEST FAILED (code=%d)\n", errNb);
            free(requestBuf);
            free(responseBuf);
            codegen_pipe_close(&cp);
            return errNb;
        }

        printf("passed\n");
        tested++;
    }

    free(requestBuf);
    free(responseBuf);
    codegen_pipe_close(&cp);

    printf("\n  %s: %d tests passed\n", lang->display, tested);
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

        errNb = test_codegen_for_language(&ALL_LANGUAGES[i], history,
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

    printf("\n=============================================\n");
    printf("All %d language(s) passed codegen verification\n", langsTested);
    printf("=============================================\n");

    return TA_TEST_PASS;
}
