# Multi-Language Codegen Regression Testing Implementation Plan

> **For Claude:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Verify ta_codegen's generated code in all 5 target languages against the C reference using ta_regtest's existing `doRangeTest` infrastructure.

**Architecture:** ta_regtest spawns a JSON-RPC server for each language (one at a time), runs `doRangeTest` callbacks that call both the C reference AND the codegen server, comparing outputs element-by-element. ta_codegen auto-generates the JSON-RPC server wrapper for each language alongside the normal code generation. Errors loudly if a server is missing.

**Tech Stack:** C (POSIX pipe/fork/exec for ta_regtest), Rust (ta_codegen + Rust server), Java (javac/java), C# (dotnet), Python (SWIG bindings), CMake

---

## Background

### Key files to understand before starting

| File | What it does |
|------|-------------|
| `src/tools/ta_regtest/codegen_pipe.h` | Subprocess handle: `CodegenPipe` struct, `codegen_pipe_open()`, `codegen_pipe_call()`, `codegen_pipe_close()` |
| `src/tools/ta_regtest/codegen_pipe.c` | fork/exec/pipe implementation. Currently hardcodes `execl(binary_path, "ta_codegen", "serve", NULL)` |
| `src/tools/ta_regtest/test_codegen.h` | Declares `test_codegen(history, functionFilter)` |
| `src/tools/ta_regtest/test_codegen.c` | Current hand-written test cases (MULT, SMA, RSI). Will be **replaced** |
| `src/tools/ta_regtest/ta_regtest.c:135-137` | `--codegen` flag parsing |
| `src/tools/ta_regtest/ta_regtest.c:240-265` | `test_codegen_with_simulator()` — sets up TA_History, calls `test_codegen()` |
| `src/tools/ta_regtest/ta_test_priv.h:155-200` | `RangeTestFunction` typedef, `doRangeTest()` signature |
| `src/tools/ta_regtest/ta_test_func/test_ma.c` | Example: `TA_RangeTestParam` struct, `rangeTestFunction` callback, `doRangeTest()` calls |
| `tools/ta_codegen/src/server.rs` | Rust JSON-RPC server. Dispatches TA_MULT, TA_SMA, TA_RSI |
| `tools/ta_codegen/src/main.rs` | CLI: `ta_codegen generate [--func=X] [--backend=X]` and `ta_codegen serve` |
| `tools/ta_codegen/src/ir.rs` | `FuncDef` struct — function metadata (name, inputs, optional_inputs, outputs) |
| `tools/ta_codegen/src/backends/` | 5 backend generators: `c.rs`, `rust_lang.rs`, `java.rs`, `dotnet.rs`, `swig.rs` |
| `ta_codegen_output/` | Generated code: `c/`, `rust/`, `java/`, `dotnet/`, `swig/` subdirs |

### Current backend capabilities

| Backend | Generates full implementation? | Server feasibility |
|---------|-------------------------------|-------------------|
| C | Yes (ta_SMA.c etc.) | Compile to binary |
| Rust | Yes (sma.rs etc.) | Already exists in ta_codegen serve |
| Java | Yes (Core_SMA.java etc.) | Compile + run with java |
| .NET | Declarations only (Core_SMA.h) | Need to extend backend to generate C# first |
| SWIG | Declarations only (ta_SMA.swg) | Python script that imports SWIG bindings wrapping C |

### Language server commands (what ta_regtest will spawn)

| Language | Command | Binary/script location |
|----------|---------|----------------------|
| rust | `./ta_codegen serve` | `bin/ta_codegen` (already exists) |
| c | `./ta_codegen_serve_c` | `bin/ta_codegen_serve_c` |
| java | `java -cp ta_codegen_java TaCodegenServe` | `bin/ta_codegen_java/` |
| dotnet | `dotnet ta_codegen_serve.dll` | `bin/ta_codegen_dotnet/` |
| swig | `python3 ta_codegen_serve.py` | `bin/ta_codegen_serve.py` |

### JSON-RPC protocol (unchanged, all languages speak this)

Request: `{"method": "TA_SMA", "params": {"startIdx": 0, "endIdx": 251, "inReal": [...], "optInTimePeriod": 30}}\n`

Response: `{"retCode": 0, "outBegIdx": 29, "outNBElement": 223, "outReal": [...]}\n`

Error: `{"error": "Unknown method: TA_XXX"}\n`

### Constraints

- Zero changes to existing test files (test_ma.c, test_rsi.c, test_util.c, etc.)
- Zero new library dependencies in ta_regtest
- Existing ta_regtest behavior unchanged without `--codegen`
- Error loudly if a requested language's server is missing (no silent skips)
- POSIX only (macOS/Linux)

---

## Phase 1: ta_regtest side (the consumer)

### Task 1: Update codegen_pipe for flexible command execution

Currently `codegen_pipe_open` hardcodes `execl(binary_path, "ta_codegen", "serve", NULL)`. We need it to accept an arbitrary command with arguments so it can spawn different servers per language.

**Files:**
- Modify: `src/tools/ta_regtest/codegen_pipe.h`
- Modify: `src/tools/ta_regtest/codegen_pipe.c`

**Step 1: Update the header**

Change `codegen_pipe_open` to accept a NULL-terminated argv array instead of a single binary path:

```c
/* In codegen_pipe.h, replace the codegen_pipe_open declaration */

/* Start a JSON-RPC subprocess.
 * argv: NULL-terminated array of strings (program + args).
 *   e.g. {"./ta_codegen", "serve", NULL}
 *   e.g. {"java", "-cp", "ta_codegen_java", "TaCodegenServe", NULL}
 * Returns TA_TEST_PASS on success, error code on failure.
 */
ErrorNumber codegen_pipe_open(CodegenPipe *cp, const char *const argv[]);
```

**Step 2: Update the implementation**

In `codegen_pipe.c`, change `codegen_pipe_open` to use `execvp` with the argv array:

```c
/* In codegen_pipe_open, replace the execl call (line 52) with: */
execvp(argv[0], (char *const *)argv);
```

And update the signature to match the new header.

**Step 3: Build to verify compilation**

```bash
cd /Users/chadfurman/projects/ta-lib/cmake-build && make ta_regtest -j4
```

Expected: Compile error in test_codegen.c because it still calls `codegen_pipe_open(&cp, "./ta_codegen")` with the old signature. That's fine — we'll fix it in Task 2.

**Step 4: Commit**

```bash
git add src/tools/ta_regtest/codegen_pipe.h src/tools/ta_regtest/codegen_pipe.c
git commit -m "refactor(regtest): codegen_pipe_open takes argv array for flexible command execution"
```

---

### Task 2: Rewrite test_codegen with doRangeTest callbacks

Replace the hand-written test cases with `doRangeTest()`-based callbacks. This is the core architectural change.

**Files:**
- Modify: `src/tools/ta_regtest/test_codegen.h`
- Rewrite: `src/tools/ta_regtest/test_codegen.c`

**Step 1: Update the header**

```c
/* test_codegen.h — replace entire contents */
#ifndef TEST_CODEGEN_H
#define TEST_CODEGEN_H

#include "ta_error_number.h"
#include "ta_test_priv.h"

/* Run codegen verification tests against one or more languages.
 * languageFilter: comma-separated list of languages to test (NULL = test all).
 *   Valid values: "rust", "c", "java", "dotnet", "swig"
 * functionFilter: CSV list of function names to test (NULL = test all).
 * Errors loudly if a requested language's server cannot be started.
 */
ErrorNumber test_codegen(const TA_History *history,
                         const char *languageFilter,
                         const char *functionFilter);

#endif
```

**Step 2: Write the new test_codegen.c**

This is the big file. Key components:

1. **Language → command mapping** — knows how to spawn each language's server
2. **CodegenRangeTestParam struct** — opaqueData for doRangeTest callbacks, carries input arrays, params, pipe handle, and a codegen error flag
3. **Per-function doRangeTest callbacks** — call C reference + send to codegen pipe + compare
4. **JSON helpers** — same minimal helpers as before (reused)
5. **`test_codegen_for_language()`** — spawns one language's server, runs all doRangeTest callbacks
6. **`test_codegen()`** — loops over languages, calls `test_codegen_for_language()`

```c
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
static const char *const argv_dotnet[]= {"dotnet", "ta_codegen_dotnet/ta_codegen_serve.dll", NULL};
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
} CodegenTestDef;

static const CodegenTestDef CODEGEN_TESTS[] = {
    {"MULT", "TA_MULT", codegen_range_mult, TA_FUNC_UNST_NONE, 1, 0, 0,  1},
    {"SMA",  "TA_SMA",  codegen_range_sma,  TA_FUNC_UNST_NONE, 1, 1, 30, 0},
    {"RSI",  "TA_RSI",  codegen_range_rsi,  TA_FUNC_UNST_RSI,  1, 1, 14, 0},
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
                            (void *)&params, def->nbOutput, 0);

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
```

**Step 3: Build and verify compilation**

```bash
cd /Users/chadfurman/projects/ta-lib/cmake-build && make ta_regtest -j4
```

Expected: Compile error in `ta_regtest.c` because `test_codegen()` signature changed (now takes 3 args). Fixed in Task 3.

**Step 4: Commit**

```bash
git add src/tools/ta_regtest/test_codegen.h src/tools/ta_regtest/test_codegen.c
git commit -m "feat(regtest): rewrite test_codegen with doRangeTest callbacks and multi-language support"
```

---

### Task 3: Update ta_regtest.c for --codegen[=lang] syntax

Change `--codegen` to optionally accept a language filter: `--codegen`, `--codegen=rust`, `--codegen=rust,java`.

**Files:**
- Modify: `src/tools/ta_regtest/ta_regtest.c`

**Step 1: Add language filter variable and update arg parsing**

```c
/* Near line 89, change: */
static int doCodegenTest = 0;
/* To: */
static int doCodegenTest = 0;
static const char *codegenLanguageFilter = NULL;

/* Near line 135, change the --codegen parsing from: */
else if( strcmp(argv[i], "--codegen") == 0 )
{
    doCodegenTest = 1;
}
/* To: */
else if( strcmp(argv[i], "--codegen") == 0 )
{
    doCodegenTest = 1;
}
else if( strncmp(argv[i], "--codegen=", 10) == 0 )
{
    doCodegenTest = 1;
    codegenLanguageFilter = argv[i] + 10;
}
```

**Step 2: Update the test_codegen call**

```c
/* In test_codegen_with_simulator (line 256), change: */
retValue = test_codegen(&history, functionFilter);
/* To: */
retValue = test_codegen(&history, codegenLanguageFilter, functionFilter);
```

**Step 3: Update printUsage**

```c
/* Near line 372, change: */
printf( "    --codegen\n" );
printf( "       After normal tests, also verify ta_codegen output\n" );
printf( "\n" );
printf( "       Requires ./ta_codegen binary in the bin directory.\n" );
/* To: */
printf( "    --codegen[=LANG[,LANG,...]]\n" );
printf( "       After normal tests, verify ta_codegen output against C reference.\n" );
printf( "       Languages: rust, c, java, dotnet, swig (default: all)\n" );
printf( "       Example: --codegen=rust,java\n" );
printf( "\n" );
printf( "       Requires language server binaries in the bin directory.\n" );
printf( "       Build with: ta_codegen build\n" );
```

**Step 4: Build and verify**

```bash
cd /Users/chadfurman/projects/ta-lib/cmake-build && make ta_regtest -j4
```

Expected: Compiles successfully.

**Step 5: Smoke test with Rust only**

```bash
cd /Users/chadfurman/projects/ta-lib/bin && ./ta_regtest --codegen=rust
```

Expected: Runs full doRangeTest suite for MULT, SMA, RSI against Rust. Should pass since `ta_codegen serve` already handles these functions.

**Step 6: Verify error on missing language**

```bash
cd /Users/chadfurman/projects/ta-lib/bin && ./ta_regtest --codegen=java
```

Expected: Errors loudly: "FAILED: Cannot start Java server (run: ta_codegen build --lang=java)"

**Step 7: Commit**

```bash
git add src/tools/ta_regtest/ta_regtest.c
git commit -m "feat(regtest): support --codegen=lang syntax for per-language testing"
```

---

## Phase 2: ta_codegen server generation

### Task 4: Add server generation infrastructure to ta_codegen

Add a `generate-servers` command to ta_codegen that generates a JSON-RPC server wrapper alongside each language's normal output.

**Files:**
- Modify: `tools/ta_codegen/src/main.rs`
- Create: `tools/ta_codegen/src/server_gen.rs`

**Step 1: Create server_gen.rs with the generation trait**

This module generates a JSON-RPC server source file for each language. It uses the `FuncDef` IR to know which functions exist and their signatures.

```rust
// tools/ta_codegen/src/server_gen.rs

use crate::ir::{FuncDef, ParamType};

/// Generate a C JSON-RPC server source file.
pub fn generate_c_server(funcs: &[FuncDef]) -> String {
    // Implementation in Task 5
    todo!()
}

/// Generate a Java JSON-RPC server source file.
pub fn generate_java_server(funcs: &[FuncDef]) -> String {
    // Implementation in Task 6
    todo!()
}

/// Generate a .NET (C#) JSON-RPC server source file.
pub fn generate_dotnet_server(funcs: &[FuncDef]) -> String {
    // Implementation in Task 7
    todo!()
}

/// Generate a Python JSON-RPC server script (uses SWIG bindings).
pub fn generate_swig_server(funcs: &[FuncDef]) -> String {
    // Implementation in Task 8
    todo!()
}
```

**Step 2: Add `generate-servers` command to main.rs**

```rust
// In main.rs, add to command matching:
"generate-servers" => {
    // Collect all function definitions (same as generate)
    let funcs: Vec<FuncDef> = /* ... same loading logic as generate ... */;

    // Generate server source files
    let c_server = server_gen::generate_c_server(&funcs);
    std::fs::write("../../ta_codegen_output/c/ta_codegen_serve.c", c_server)?;

    let java_server = server_gen::generate_java_server(&funcs);
    std::fs::write("../../ta_codegen_output/java/TaCodegenServe.java", java_server)?;

    let dotnet_server = server_gen::generate_dotnet_server(&funcs);
    std::fs::write("../../ta_codegen_output/dotnet/TaCodegenServe.cs", dotnet_server)?;

    let swig_server = server_gen::generate_swig_server(&funcs);
    std::fs::write("../../ta_codegen_output/swig/ta_codegen_serve.py", swig_server)?;

    println!("Server source files generated.");
}
```

**Step 3: Register module**

```rust
// In lib.rs or main.rs, add:
mod server_gen;
```

**Step 4: Verify it compiles**

```bash
cd /Users/chadfurman/projects/ta-lib/tools/ta_codegen && cargo check
```

**Step 5: Commit**

```bash
git add tools/ta_codegen/src/server_gen.rs tools/ta_codegen/src/main.rs
git commit -m "feat(ta_codegen): add server generation infrastructure and generate-servers command"
```

---

### Task 5: Generate C JSON-RPC server

Implement `generate_c_server()` — generates a standalone C file that reads JSON-RPC from stdin, dispatches to the generated C functions, writes responses to stdout.

**Files:**
- Modify: `tools/ta_codegen/src/server_gen.rs`

**Step 1: Implement generate_c_server**

The generated C server needs:
- Minimal JSON parsing (same pattern as test_codegen.c)
- A dispatch function mapping method names to TA function calls
- stdin/stdout loop

The generated code should include the generated function implementations inline (via `#include "ta_SMA.c"` etc.) OR link against them separately. Linking separately is cleaner.

Key: the generated C functions use `TA_RetCode`, `TA_Real` etc. from `ta_func.h`. The server needs these types. For a standalone server, define minimal type aliases at the top.

```rust
pub fn generate_c_server(funcs: &[FuncDef]) -> String {
    let mut s = String::new();

    // Header
    s.push_str("/* Auto-generated JSON-RPC server for ta_codegen C output */\n");
    s.push_str("#include <stdio.h>\n");
    s.push_str("#include <stdlib.h>\n");
    s.push_str("#include <string.h>\n");
    s.push_str("#include <math.h>\n\n");

    // Type definitions (standalone, no ta_func.h dependency)
    s.push_str("typedef int TA_RetCode;\n");
    s.push_str("typedef double TA_Real;\n");
    s.push_str("typedef int TA_Integer;\n");
    s.push_str("#define TA_SUCCESS 0\n");
    s.push_str("#define TA_BAD_PARAM 2\n");
    s.push_str("#define TA_OUT_OF_RANGE_START_INDEX 12\n");
    s.push_str("#define TA_OUT_OF_RANGE_END_INDEX 13\n\n");

    // Include generated function implementations
    for func in funcs {
        s.push_str(&format!("#include \"ta_{}.c\"\n", func.name));
    }
    s.push_str("\n");

    // JSON helpers (minimal, same pattern as test_codegen.c)
    s.push_str(&generate_c_json_helpers());

    // Dispatch function
    s.push_str(&generate_c_dispatch(funcs));

    // Main loop
    s.push_str("int main(void) {\n");
    s.push_str("    char line[65536];\n");
    s.push_str("    char response[65536];\n");
    s.push_str("    while( fgets(line, sizeof(line), stdin) ) {\n");
    s.push_str("        handle_request(line, response, sizeof(response));\n");
    s.push_str("        printf(\"%s\\n\", response);\n");
    s.push_str("        fflush(stdout);\n");
    s.push_str("    }\n");
    s.push_str("    return 0;\n");
    s.push_str("}\n");

    s
}
```

The `generate_c_dispatch` function emits a chain of `strcmp` calls checking the method name and calling the appropriate generated C function, extracting params from JSON and building the JSON response.

**Step 2: Test generation**

```bash
cd /Users/chadfurman/projects/ta-lib/tools/ta_codegen && cargo run -- generate-servers
cat ../../ta_codegen_output/c/ta_codegen_serve.c | head -50
```

Expected: Valid C source code.

**Step 3: Test compilation of generated server**

```bash
cd /Users/chadfurman/projects/ta-lib/ta_codegen_output/c
gcc -o ta_codegen_serve_c ta_codegen_serve.c -lm -I../../include
```

Note: may need to adjust include paths or type definitions. The goal is a standalone binary.

**Step 4: Test the server manually**

```bash
echo '{"method":"TA_SMA","params":{"startIdx":0,"endIdx":4,"inReal":[1,2,3,4,5],"optInTimePeriod":3}}' | ./ta_codegen_serve_c
```

Expected: `{"retCode":0,"outBegIdx":2,"outNBElement":3,"outReal":[2.0,3.0,4.0]}`

**Step 5: Commit**

```bash
git add tools/ta_codegen/src/server_gen.rs
git commit -m "feat(ta_codegen): generate C JSON-RPC server from IR"
```

---

### Task 6: Generate Java JSON-RPC server

Implement `generate_java_server()`. Java has no external JSON dependency needed — use simple string parsing (same approach as C) or `javax.json` if available.

**Files:**
- Modify: `tools/ta_codegen/src/server_gen.rs`

**Step 1: Implement generate_java_server**

The generated Java server needs:
- A main class `TaCodegenServe` with `public static void main(String[] args)`
- BufferedReader on stdin, dispatch method calls
- Import the generated Core_*.java files (or include them inline)

Key difference from C: Java generated code uses `MInteger` for output params and methods like `core.sma()`. The server needs to instantiate `Core` and call methods on it.

```rust
pub fn generate_java_server(funcs: &[FuncDef]) -> String {
    let mut s = String::new();

    s.push_str("/* Auto-generated JSON-RPC server for ta_codegen Java output */\n");
    s.push_str("import java.io.*;\n\n");

    // MInteger helper class (same as TA-Lib's)
    s.push_str("class MInteger { public int value; }\n\n");

    // RetCode enum
    s.push_str("enum RetCode {\n");
    s.push_str("    Success, BadParam, OutOfRangeStartIndex, OutOfRangeEndIndex;\n");
    s.push_str("    public int toInt() {\n");
    s.push_str("        switch(this) {\n");
    s.push_str("            case Success: return 0;\n");
    s.push_str("            case BadParam: return 2;\n");
    s.push_str("            case OutOfRangeStartIndex: return 12;\n");
    s.push_str("            case OutOfRangeEndIndex: return 13;\n");
    s.push_str("            default: return 5000;\n");
    s.push_str("        }\n");
    s.push_str("    }\n");
    s.push_str("}\n\n");

    // Include Core class with all generated methods
    // (paste generated Core_*.java method bodies into a single Core class)

    // Main server class with dispatch
    // ...

    s
}
```

**Step 2: Test generation and compilation**

```bash
cd /Users/chadfurman/projects/ta-lib/tools/ta_codegen && cargo run -- generate-servers
cd ../../ta_codegen_output/java
javac TaCodegenServe.java Core_*.java
```

**Step 3: Test manually**

```bash
echo '{"method":"TA_SMA","params":{"startIdx":0,"endIdx":4,"inReal":[1,2,3,4,5],"optInTimePeriod":3}}' | java -cp . TaCodegenServe
```

**Step 4: Commit**

```bash
git add tools/ta_codegen/src/server_gen.rs
git commit -m "feat(ta_codegen): generate Java JSON-RPC server from IR"
```

---

### Task 7: Generate .NET (C#) JSON-RPC server

**Prerequisite:** The .NET backend currently only generates C++/CLI header declarations, not full implementations. Before this task, the .NET backend (`tools/ta_codegen/src/backends/dotnet.rs`) must be extended to generate complete C# implementations (similar to Java). This is a separate piece of work.

**If .NET backend is extended to generate C#:**

Implement `generate_dotnet_server()`. C# has `System.Text.Json` built-in.

**Files:**
- Modify: `tools/ta_codegen/src/server_gen.rs`
- May need to modify: `tools/ta_codegen/src/backends/dotnet.rs` (extend to generate C#)

**Step 1: Implement generate_dotnet_server**

```rust
pub fn generate_dotnet_server(funcs: &[FuncDef]) -> String {
    let mut s = String::new();
    s.push_str("// Auto-generated JSON-RPC server for ta_codegen .NET output\n");
    s.push_str("using System;\n");
    s.push_str("using System.Text.Json;\n\n");
    // ... dispatch logic similar to Java ...
    s
}
```

**Step 2: Test**

```bash
cd ta_codegen_output/dotnet
dotnet new console --name TaCodegenServe --force
# Copy generated .cs files
dotnet run
```

**Step 3: Commit**

```bash
git add tools/ta_codegen/src/server_gen.rs
git commit -m "feat(ta_codegen): generate .NET JSON-RPC server from IR"
```

---

### Task 8: Generate SWIG/Python JSON-RPC server

SWIG generates Python bindings that wrap the C implementation. The Python server imports the SWIG module and dispatches JSON-RPC calls through it.

**Prerequisite:** SWIG bindings must be compiled first (`swig -python`, then compile the C wrapper).

**Files:**
- Modify: `tools/ta_codegen/src/server_gen.rs`

**Step 1: Implement generate_swig_server**

```rust
pub fn generate_swig_server(funcs: &[FuncDef]) -> String {
    let mut s = String::new();

    s.push_str("#!/usr/bin/env python3\n");
    s.push_str("\"\"\"Auto-generated JSON-RPC server for ta_codegen SWIG/Python output.\"\"\"\n");
    s.push_str("import sys\n");
    s.push_str("import json\n");
    s.push_str("import ta_lib  # SWIG-generated module\n\n");

    // Dispatch function
    s.push_str("def handle_request(req):\n");
    s.push_str("    method = req.get('method', '')\n");
    s.push_str("    params = req.get('params', {})\n");

    for func in funcs {
        let name = &func.name;
        s.push_str(&format!("    if method == 'TA_{name}':\n"));
        s.push_str(&format!("        return handle_{name}(params)\n",
                            name = name.to_lowercase()));
    }

    s.push_str("    return {'error': f'Unknown method: {method}'}\n\n");

    // Per-function handlers
    for func in funcs {
        // Generate handler that calls ta_lib.TA_XXX via SWIG
        // Extract params, call function, build response dict
    }

    // Main loop
    s.push_str("if __name__ == '__main__':\n");
    s.push_str("    for line in sys.stdin:\n");
    s.push_str("        req = json.loads(line.strip())\n");
    s.push_str("        resp = handle_request(req)\n");
    s.push_str("        print(json.dumps(resp), flush=True)\n");

    s
}
```

**Step 2: Test (requires SWIG + Python)**

```bash
# Build SWIG bindings first
cd ta_codegen_output/swig
swig -python ta_SMA.swg  # generates ta_lib_wrap.c + ta_lib.py
gcc -shared -fPIC -o _ta_lib.so ta_lib_wrap.c -I/usr/include/python3 -lm

# Test server
echo '{"method":"TA_SMA",...}' | python3 ta_codegen_serve.py
```

**Step 3: Commit**

```bash
git add tools/ta_codegen/src/server_gen.rs
git commit -m "feat(ta_codegen): generate SWIG/Python JSON-RPC server from IR"
```

---

### Task 9: Add `ta_codegen build` command

Add a `build` subcommand that compiles the generated server for each language. Auto-detects available toolchains and warns (but doesn't error) for missing ones.

**Files:**
- Modify: `tools/ta_codegen/src/main.rs`

**Step 1: Add build command**

```rust
"build" => {
    let lang_filter: Option<Vec<&str>> = /* parse --lang=X,Y */;

    let languages = vec![
        ("c",      build_c_server),
        ("java",   build_java_server),
        ("dotnet", build_dotnet_server),
        ("swig",   build_swig_server),
    ];
    // Note: Rust server is built as part of ta_codegen itself (cargo build)

    for (name, builder) in &languages {
        if let Some(ref filter) = lang_filter {
            if !filter.contains(name) { continue; }
        }
        println!("Building {} server...", name);
        match builder() {
            Ok(()) => println!("  {} server: OK", name),
            Err(e) => println!("  {} server: FAILED ({})", name, e),
        }
    }
}
```

**Step 2: Implement per-language build functions**

Each function shells out to the appropriate compiler:

```rust
fn build_c_server() -> Result<(), String> {
    let status = std::process::Command::new("gcc")
        .args(&["-o", "../../bin/ta_codegen_serve_c",
                "../../ta_codegen_output/c/ta_codegen_serve.c",
                "-lm", "-O2"])
        .status()
        .map_err(|e| format!("gcc not found: {}", e))?;
    if !status.success() {
        return Err("compilation failed".into());
    }
    Ok(())
}

fn build_java_server() -> Result<(), String> {
    // javac -d bin/ta_codegen_java ta_codegen_output/java/*.java
    // ...
    Ok(())
}

fn build_dotnet_server() -> Result<(), String> {
    // dotnet publish -o bin/ta_codegen_dotnet
    // ...
    Ok(())
}

fn build_swig_server() -> Result<(), String> {
    // swig -python ...; gcc -shared ...; cp server script to bin/
    // ...
    Ok(())
}
```

**Step 3: Test**

```bash
cd /Users/chadfurman/projects/ta-lib/tools/ta_codegen
cargo run -- generate-servers
cargo run -- build --lang=c
ls ../../bin/ta_codegen_serve_c
```

**Step 4: Commit**

```bash
git add tools/ta_codegen/src/main.rs
git commit -m "feat(ta_codegen): add build command to compile language servers"
```

---

## Phase 3: Integration

### Task 10: CMake integration

Add CMake targets to build ta_codegen, generate servers, and compile them.

**Files:**
- Modify: `CMakeLists.txt`

**Step 1: Add targets**

```cmake
# Build ta_codegen itself (already exists as ta_codegen_bin)
# Add: generate servers + build them

add_custom_target(ta_codegen_servers
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR}/tools/ta_codegen
            cargo run --release -- generate-servers
    COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_SOURCE_DIR}/tools/ta_codegen
            cargo run --release -- build
    DEPENDS ta_codegen_bin
    COMMENT "Generating and building codegen language servers"
)
```

**Step 2: Verify**

```bash
cd /Users/chadfurman/projects/ta-lib/cmake-build && cmake .. && make ta_codegen_servers
```

**Step 3: Commit**

```bash
git add CMakeLists.txt
git commit -m "feat(cmake): add ta_codegen_servers target for multi-language server builds"
```

---

### Task 11: End-to-end multi-language test

Verify the full pipeline works for each available language.

**Files:** None (verification only)

**Step 1: Build everything**

```bash
cd /Users/chadfurman/projects/ta-lib/cmake-build
cmake .. -DCMAKE_BUILD_TYPE=Release
make ta_regtest ta_codegen_servers -j4
```

**Step 2: Test Rust (should work)**

```bash
cd /Users/chadfurman/projects/ta-lib/bin && ./ta_regtest --codegen=rust
```

Expected: All MULT, SMA, RSI pass with full doRangeTest coverage.

**Step 3: Test C (should work if gcc available)**

```bash
cd /Users/chadfurman/projects/ta-lib/bin && ./ta_regtest --codegen=c
```

**Step 4: Test Java (if JDK available)**

```bash
cd /Users/chadfurman/projects/ta-lib/bin && ./ta_regtest --codegen=java
```

**Step 5: Test all available**

```bash
cd /Users/chadfurman/projects/ta-lib/bin && ./ta_regtest --codegen
```

Expected: Errors loudly for any language whose server isn't built.

**Step 6: Verify no regressions without --codegen**

```bash
cd /Users/chadfurman/projects/ta-lib/bin && ./ta_regtest
```

Expected: Runs exactly as before, no codegen tests.

**Step 7: Commit (if any fixes needed)**

```bash
git commit -m "fix(regtest): fixes from multi-language e2e testing"
```

---

## Summary of what gets built

| Component | What | Where |
|-----------|------|-------|
| ta_regtest `--codegen[=lang]` | Consumer: spawns servers, runs doRangeTest, compares | `src/tools/ta_regtest/` |
| `ta_codegen generate-servers` | Generates JSON-RPC server source for each language | `tools/ta_codegen/` → `ta_codegen_output/` |
| `ta_codegen build` | Compiles servers for available toolchains | `tools/ta_codegen/` → `bin/` |
| C server | `ta_codegen_serve_c` binary | `bin/ta_codegen_serve_c` |
| Rust server | Built-in `ta_codegen serve` | `bin/ta_codegen` |
| Java server | `TaCodegenServe.class` | `bin/ta_codegen_java/` |
| .NET server | `ta_codegen_serve.dll` | `bin/ta_codegen_dotnet/` |
| SWIG/Python server | `ta_codegen_serve.py` + `_ta_lib.so` | `bin/` |
