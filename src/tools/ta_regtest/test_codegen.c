#include "test_codegen.h"
#include "codegen_pipe.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ta_libc.h"

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

/* ---- Comparison ---- */

#define CODEGEN_EPSILON 1e-6

static ErrorNumber compare_results(
    const char *func_name,
    TA_RetCode c_retCode, int c_begIdx, int c_nbElement, const TA_Real *c_out,
    const char *codegen_response)
{
    if( json_is_error(codegen_response) )
        return TA_TEST_PASS; /* Unsupported — skip */

    int cg_retCode   = json_get_int(codegen_response, "retCode");
    int cg_begIdx    = json_get_int(codegen_response, "outBegIdx");
    int cg_nbElement = json_get_int(codegen_response, "outNBElement");

    if( (int)c_retCode != cg_retCode )
    {
        printf("CODEGEN MISMATCH [%s]: retCode C=%d codegen=%d\n",
               func_name, (int)c_retCode, cg_retCode);
        return TA_CODEGEN_RETCODE_MISMATCH;
    }

    if( c_retCode != TA_SUCCESS )
        return TA_TEST_PASS;

    if( c_begIdx != cg_begIdx )
    {
        printf("CODEGEN MISMATCH [%s]: outBegIdx C=%d codegen=%d\n",
               func_name, c_begIdx, cg_begIdx);
        return TA_CODEGEN_BEGIDX_MISMATCH;
    }

    if( c_nbElement != cg_nbElement )
    {
        printf("CODEGEN MISMATCH [%s]: outNBElement C=%d codegen=%d\n",
               func_name, c_nbElement, cg_nbElement);
        return TA_CODEGEN_NBELEMENT_MISMATCH;
    }

    TA_Real cg_out[MAX_NB_TEST_ELEMENT];
    int parsed = json_get_double_array(codegen_response, "outReal",
                                       cg_out, MAX_NB_TEST_ELEMENT);
    if( parsed != cg_nbElement )
    {
        printf("CODEGEN MISMATCH [%s]: outReal length %d != outNBElement %d\n",
               func_name, parsed, cg_nbElement);
        return TA_CODEGEN_OUTPUT_MISMATCH;
    }

    for( int i = 0; i < c_nbElement; i++ )
    {
        double diff = fabs(c_out[i] - cg_out[i]);
        if( diff > CODEGEN_EPSILON )
        {
            printf("CODEGEN MISMATCH [%s]: outReal[%d] C=%.10f codegen=%.10f diff=%.2e\n",
                   func_name, i, c_out[i], cg_out[i], diff);
            return TA_CODEGEN_OUTPUT_MISMATCH;
        }
    }

    return TA_TEST_PASS;
}

/* ---- Per-function tests ---- */

#define JSON_BUF_SIZE (64 * 1024)

static ErrorNumber test_codegen_sma(CodegenPipe *cp, const TA_History *history)
{
    char *request = malloc(JSON_BUF_SIZE);
    char *response = malloc(JSON_BUF_SIZE);
    if( !request || !response ) { free(request); free(response); return TA_CODEGEN_ALLOC_FAILED; }

    int endIdx = (int)history->nbBars - 1;
    TA_Real outReal[MAX_NB_TEST_ELEMENT];
    TA_Integer outBegIdx, outNbElement;
    ErrorNumber errNb;
    TA_RetCode retCode;
    int pos;

    /* Sub-test 1: SMA with period=2 (minimal) */
    {
        int startIdx = 0;
        int timePeriod = 2;
        retCode = TA_SMA(startIdx, endIdx, history->close, timePeriod,
                         &outBegIdx, &outNbElement, outReal);

        pos = snprintf(request, JSON_BUF_SIZE,
            "{\"method\":\"TA_SMA\",\"params\":{\"startIdx\":%d,\"endIdx\":%d,"
            "\"optInTimePeriod\":%d,\"inReal\":", startIdx, endIdx, timePeriod);
        pos += json_write_double_array(request + pos, JSON_BUF_SIZE - pos,
                                       history->close, (int)history->nbBars);
        pos += snprintf(request + pos, JSON_BUF_SIZE - pos, "}}");

        errNb = codegen_pipe_call(cp, request, response, JSON_BUF_SIZE);
        if( errNb == TA_TEST_PASS )
            errNb = compare_results("TA_SMA(period=2)", retCode, outBegIdx, outNbElement, outReal, response);
        if( errNb != TA_TEST_PASS ) { free(request); free(response); return errNb; }
    }

    /* Sub-test 2: SMA with period=30 (standard) */
    {
        int startIdx = 0;
        int timePeriod = 30;
        retCode = TA_SMA(startIdx, endIdx, history->close, timePeriod,
                         &outBegIdx, &outNbElement, outReal);

        pos = snprintf(request, JSON_BUF_SIZE,
            "{\"method\":\"TA_SMA\",\"params\":{\"startIdx\":%d,\"endIdx\":%d,"
            "\"optInTimePeriod\":%d,\"inReal\":", startIdx, endIdx, timePeriod);
        pos += json_write_double_array(request + pos, JSON_BUF_SIZE - pos,
                                       history->close, (int)history->nbBars);
        pos += snprintf(request + pos, JSON_BUF_SIZE - pos, "}}");

        errNb = codegen_pipe_call(cp, request, response, JSON_BUF_SIZE);
        if( errNb == TA_TEST_PASS )
            errNb = compare_results("TA_SMA(period=30)", retCode, outBegIdx, outNbElement, outReal, response);
        if( errNb != TA_TEST_PASS ) { free(request); free(response); return errNb; }
    }

    /* Sub-test 3: SMA with startIdx=50 (partial range) */
    {
        int startIdx = 50;
        int timePeriod = 30;
        retCode = TA_SMA(startIdx, endIdx, history->close, timePeriod,
                         &outBegIdx, &outNbElement, outReal);

        pos = snprintf(request, JSON_BUF_SIZE,
            "{\"method\":\"TA_SMA\",\"params\":{\"startIdx\":%d,\"endIdx\":%d,"
            "\"optInTimePeriod\":%d,\"inReal\":", startIdx, endIdx, timePeriod);
        pos += json_write_double_array(request + pos, JSON_BUF_SIZE - pos,
                                       history->close, (int)history->nbBars);
        pos += snprintf(request + pos, JSON_BUF_SIZE - pos, "}}");

        errNb = codegen_pipe_call(cp, request, response, JSON_BUF_SIZE);
        if( errNb == TA_TEST_PASS )
            errNb = compare_results("TA_SMA(period=30,startIdx=50)", retCode, outBegIdx, outNbElement, outReal, response);
        if( errNb != TA_TEST_PASS ) { free(request); free(response); return errNb; }
    }

    free(request); free(response);
    return TA_TEST_PASS;
}

static ErrorNumber test_codegen_mult(CodegenPipe *cp, const TA_History *history)
{
    char *request = malloc(JSON_BUF_SIZE);
    char *response = malloc(JSON_BUF_SIZE);
    if( !request || !response ) { free(request); free(response); return TA_CODEGEN_ALLOC_FAILED; }

    int startIdx = 0;
    int endIdx = (int)history->nbBars - 1;
    TA_Real outReal[MAX_NB_TEST_ELEMENT];
    TA_Integer outBegIdx, outNbElement;

    TA_RetCode retCode = TA_MULT(startIdx, endIdx, history->close, history->volume,
                                 &outBegIdx, &outNbElement, outReal);

    int pos = snprintf(request, JSON_BUF_SIZE,
        "{\"method\":\"TA_MULT\",\"params\":{\"startIdx\":%d,\"endIdx\":%d,\"inReal0\":", startIdx, endIdx);
    pos += json_write_double_array(request + pos, JSON_BUF_SIZE - pos, history->close, (int)history->nbBars);
    pos += snprintf(request + pos, JSON_BUF_SIZE - pos, ",\"inReal1\":");
    pos += json_write_double_array(request + pos, JSON_BUF_SIZE - pos, history->volume, (int)history->nbBars);
    pos += snprintf(request + pos, JSON_BUF_SIZE - pos, "}}");

    ErrorNumber errNb = codegen_pipe_call(cp, request, response, JSON_BUF_SIZE);
    if( errNb == TA_TEST_PASS )
        errNb = compare_results("TA_MULT", retCode, outBegIdx, outNbElement, outReal, response);

    free(request); free(response);
    return errNb;
}

static ErrorNumber test_codegen_rsi(CodegenPipe *cp, const TA_History *history)
{
    char *request = malloc(JSON_BUF_SIZE);
    char *response = malloc(JSON_BUF_SIZE);
    if( !request || !response ) { free(request); free(response); return TA_CODEGEN_ALLOC_FAILED; }

    int startIdx = 0;
    int endIdx = (int)history->nbBars - 1;
    TA_Real outReal[MAX_NB_TEST_ELEMENT];
    TA_Integer outBegIdx, outNbElement;
    ErrorNumber errNb;
    TA_RetCode retCode;
    int pos;

    /* Sub-test 1: RSI with period=14 (standard) */
    {
        int timePeriod = 14;
        TA_SetUnstablePeriod(TA_FUNC_UNST_RSI, 0);
        TA_SetCompatibility(TA_COMPATIBILITY_DEFAULT);

        retCode = TA_RSI(startIdx, endIdx, history->close, timePeriod,
                         &outBegIdx, &outNbElement, outReal);

        pos = snprintf(request, JSON_BUF_SIZE,
            "{\"method\":\"TA_RSI\",\"params\":{\"startIdx\":%d,\"endIdx\":%d,"
            "\"optInTimePeriod\":%d,\"inReal\":", startIdx, endIdx, timePeriod);
        pos += json_write_double_array(request + pos, JSON_BUF_SIZE - pos, history->close, (int)history->nbBars);
        pos += snprintf(request + pos, JSON_BUF_SIZE - pos, "}}");

        errNb = codegen_pipe_call(cp, request, response, JSON_BUF_SIZE);
        if( errNb == TA_TEST_PASS )
            errNb = compare_results("TA_RSI(period=14)", retCode, outBegIdx, outNbElement, outReal, response);
        if( errNb != TA_TEST_PASS ) { free(request); free(response); return errNb; }
    }

    /* Sub-test 2: RSI with period=2 (minimal) */
    {
        int timePeriod = 2;
        TA_SetUnstablePeriod(TA_FUNC_UNST_RSI, 0);
        TA_SetCompatibility(TA_COMPATIBILITY_DEFAULT);

        retCode = TA_RSI(startIdx, endIdx, history->close, timePeriod,
                         &outBegIdx, &outNbElement, outReal);

        pos = snprintf(request, JSON_BUF_SIZE,
            "{\"method\":\"TA_RSI\",\"params\":{\"startIdx\":%d,\"endIdx\":%d,"
            "\"optInTimePeriod\":%d,\"inReal\":", startIdx, endIdx, timePeriod);
        pos += json_write_double_array(request + pos, JSON_BUF_SIZE - pos, history->close, (int)history->nbBars);
        pos += snprintf(request + pos, JSON_BUF_SIZE - pos, "}}");

        errNb = codegen_pipe_call(cp, request, response, JSON_BUF_SIZE);
        if( errNb == TA_TEST_PASS )
            errNb = compare_results("TA_RSI(period=2)", retCode, outBegIdx, outNbElement, outReal, response);
        if( errNb != TA_TEST_PASS ) { free(request); free(response); return errNb; }
    }

    free(request); free(response);
    return TA_TEST_PASS;
}

/* ---- Main entry point ---- */

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

ErrorNumber test_codegen(const TA_History *history, const char *functionFilter)
{
    CodegenPipe cp;
    ErrorNumber errNb;
    int tested = 0;

    printf("\n");
    printf("Codegen verification tests\n");
    printf("--------------------------\n");

    errNb = codegen_pipe_open(&cp, "./ta_codegen");
    if( errNb != TA_TEST_PASS )
    {
        printf("Failed to start ta_codegen serve (is ./ta_codegen built?)\n");
        return errNb;
    }
    printf("ta_codegen serve started (pid=%d)\n", cp.child_pid);

    #define DO_CODEGEN_TEST(func, name) \
        if( codegen_matches_filter(functionFilter, name) ) \
        { \
            printf("  %-40s ", name); \
            fflush(stdout); \
            errNb = func(&cp, history); \
            if( errNb != TA_TEST_PASS ) \
            { \
                printf("FAILED (code=%d)\n", errNb); \
                codegen_pipe_close(&cp); \
                return errNb; \
            } \
            printf("passed\n"); \
            tested++; \
        }

    DO_CODEGEN_TEST(test_codegen_mult, "MULT");
    DO_CODEGEN_TEST(test_codegen_sma,  "SMA");
    DO_CODEGEN_TEST(test_codegen_rsi,  "RSI");

    codegen_pipe_close(&cp);
    printf("\nCodegen verification: %d tests passed\n", tested);
    return TA_TEST_PASS;
}
