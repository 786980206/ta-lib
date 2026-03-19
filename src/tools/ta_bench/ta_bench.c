/* ta_bench — Generic performance benchmark for ALL TA-Lib indicators.
 *
 * Uses ta_abstract (TA_ForEachFunc, TA_CallFunc) to iterate all indicators
 * generically. Compares C-ref (direct call) against codegen servers
 * (JSON-RPC with load_data + use_preloaded + server-side iteration).
 *
 * Usage:
 *   ./ta_bench [--points=N] [--iters=N] [--language=c,rust] [--function=RSI,SMA]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef __APPLE__
#include <mach/mach_time.h>
#endif

#include "ta_libc.h"
#include "codegen_pipe.h"

/* ---- Configuration ---- */

#define MAX_POINTS        200000
#define DEFAULT_POINTS    100000
#define DEFAULT_ITERS     100
#define MAX_FUNCTIONS     200
#define JSON_BUF_SIZE     (32 * 1024 * 1024)

/* ---- Timing ---- */

static long long get_nanotime(void) {
#ifdef __APPLE__
    static mach_timebase_info_data_t info = {0, 0};
    if( info.denom == 0 ) mach_timebase_info(&info);
    uint64_t t = mach_absolute_time();
    return (long long)(t * info.numer / info.denom);
#else
    struct timespec ts;
    if( clock_gettime(CLOCK_MONOTONIC, &ts) == 0 )
        return (long long)ts.tv_sec * 1000000000LL + (long long)ts.tv_nsec;
    return 0;
#endif
}

/* ---- Test data ---- */

static TA_Real *g_open, *g_high, *g_low, *g_close, *g_volume, *g_oi;
static int g_nPoints;

static void generate_price_data(int n) {
    g_nPoints = n;
    g_open   = calloc(n, sizeof(TA_Real));
    g_high   = calloc(n, sizeof(TA_Real));
    g_low    = calloc(n, sizeof(TA_Real));
    g_close  = calloc(n, sizeof(TA_Real));
    g_volume = calloc(n, sizeof(TA_Real));
    g_oi     = calloc(n, sizeof(TA_Real));
    unsigned int seed = 42;
    double price = 100.0;
    for( int i = 0; i < n; i++ ) {
        seed = seed * 1103515245 + 12345;
        double r = ((double)(seed >> 16) / 32768.0) - 1.0;
        double o = price, c = price + r * 2.0;
        double h = fmax(o, c) + fabs(r) * 0.5;
        double l = fmin(o, c) - fabs(r) * 0.5;
        if( l < 1.0 ) l = 1.0;
        g_open[i] = o; g_high[i] = h; g_low[i] = l; g_close[i] = c;
        g_volume[i] = 1000000.0 + r * 500000.0;
        price = c; if( price < 1.0 ) price = 1.0;
    }
}

/* ---- JSON helpers ---- */

static int json_write_double_array(char *buf, int sz, const TA_Real *arr, int n) {
    int pos = 0;
    pos += snprintf(buf+pos, sz-pos, "[");
    for( int i = 0; i < n; i++ ) {
        if( i > 0 ) pos += snprintf(buf+pos, sz-pos, ",");
        pos += snprintf(buf+pos, sz-pos, "%.10g", arr[i]);
    }
    pos += snprintf(buf+pos, sz-pos, "]");
    return pos;
}

static const char *json_find_field(const char *json, const char *field, int *len) {
    char pat[128]; snprintf(pat, sizeof(pat), "\"%s\":", field);
    const char *p = strstr(json, pat);
    if( !p ) return NULL;
    p += strlen(pat); while( *p == ' ' ) p++;
    const char *end = p;
    if( *end == '[' ) { int d=1; end++; while(d>0&&*end){if(*end=='[')d++;if(*end==']')d--;end++;} }
    else { while(*end&&*end!=','&&*end!='}')end++; }
    *len = (int)(end - p); return p;
}

/* ---- Language servers ---- */

typedef struct {
    const char *name;
    const char *display;
    const char *const *argv;
    CodegenPipe cp;
    int active;
} BenchLanguage;

static const char *const argv_c[]      = {"./ta_codegen_serve_c", NULL};
static const char *const argv_rust[]   = {"./ta_codegen_serve_rust", NULL};
static const char *const argv_java[]   = {"java", "-cp", "ta_codegen_java", "TaCodegenServe", NULL};
static const char *const argv_dotnet[] = {"dotnet", "ta_codegen_dotnet/TaCodegenServe.dll", NULL};

static BenchLanguage LANGUAGES[] = {
    {"c",      "C",      argv_c,      {{0}}, 0},
    {"rust",   "Rust",   argv_rust,   {{0}}, 0},
    {"java",   "Java",   argv_java,   {{0}}, 0},
    {"dotnet", ".NET",   argv_dotnet, {{0}}, 0},
};
#define NUM_LANGUAGES (sizeof(LANGUAGES)/sizeof(LANGUAGES[0]))

/* ---- Send load_data ---- */

static int send_load_data(BenchLanguage *lang, char *buf, int sz, char *resp, int rsz) {
    int pos = snprintf(buf, sz, "{\"method\":\"load_data\",\"params\":{\"open\":");
    pos += json_write_double_array(buf+pos, sz-pos, g_open, g_nPoints);
    pos += snprintf(buf+pos, sz-pos, ",\"high\":");
    pos += json_write_double_array(buf+pos, sz-pos, g_high, g_nPoints);
    pos += snprintf(buf+pos, sz-pos, ",\"low\":");
    pos += json_write_double_array(buf+pos, sz-pos, g_low, g_nPoints);
    pos += snprintf(buf+pos, sz-pos, ",\"close\":");
    pos += json_write_double_array(buf+pos, sz-pos, g_close, g_nPoints);
    pos += snprintf(buf+pos, sz-pos, ",\"volume\":");
    pos += json_write_double_array(buf+pos, sz-pos, g_volume, g_nPoints);
    pos += snprintf(buf+pos, sz-pos, ",\"openInterest\":");
    pos += json_write_double_array(buf+pos, sz-pos, g_oi, g_nPoints);
    pos += snprintf(buf+pos, sz-pos, "}}");
    if( codegen_pipe_call(&lang->cp, buf, resp, rsz) != TA_TEST_PASS ) return -1;
    return (strstr(resp, "\"ok\"") != NULL) ? 0 : -1;
}

/* ---- Build server request (use_preloaded, no inline data) ---- */

static int build_bench_request(char *buf, int sz, const TA_FuncInfo *fi,
                                int startIdx, int endIdx, int iters) {
    int pos = snprintf(buf, sz,
        "{\"method\":\"TA_%s\",\"params\":{\"startIdx\":%d,\"endIdx\":%d,\"use_preloaded\":1,\"iters\":%d",
        fi->name, startIdx, endIdx, iters);

    /* Add optional params with default values */
    for( unsigned int i = 0; i < fi->nbOptInput; i++ ) {
        const TA_OptInputParameterInfo *optInfo;
        TA_GetOptInputParameterInfo(fi->handle, i, &optInfo);
        if( optInfo->type == TA_OptInput_RealRange ) {
            pos += snprintf(buf+pos, sz-pos, ",\"%s\":%.15g",
                            optInfo->paramName, optInfo->defaultValue);
        } else {
            pos += snprintf(buf+pos, sz-pos, ",\"%s\":%d",
                            optInfo->paramName, (int)optInfo->defaultValue);
        }
    }
    pos += snprintf(buf+pos, sz-pos, "}}");
    return pos;
}

/* ---- C-ref: setup + call via ta_abstract ---- */

static void setup_ref_inputs(TA_ParamHolder *ph, const TA_FuncInfo *fi) {
    for( unsigned int i = 0; i < fi->nbInput; i++ ) {
        const TA_InputParameterInfo *info;
        TA_GetInputParameterInfo(fi->handle, i, &info);
        if( info->type == TA_Input_Price )
            TA_SetInputParamPricePtr(ph, i, g_open, g_high, g_low, g_close, g_volume, g_oi);
        else if( info->type == TA_Input_Real )
            TA_SetInputParamRealPtr(ph, i, g_close);
        else if( info->type == TA_Input_Integer )
            TA_SetInputParamIntegerPtr(ph, i, (const TA_Integer *)g_close); /* rare */
    }
}

static long long run_ref(const TA_FuncInfo *fi, int startIdx, int endIdx, int iters) {
    TA_ParamHolder *ph;
    if( TA_ParamHolderAlloc(fi->handle, &ph) != TA_SUCCESS ) return -1;
    setup_ref_inputs(ph, fi);

    /* Allocate output buffers */
    int maxOut = endIdx - startIdx + 1;
    TA_Real **realOuts = calloc(fi->nbOutput, sizeof(TA_Real *));
    TA_Integer **intOuts = calloc(fi->nbOutput, sizeof(TA_Integer *));
    for( unsigned int i = 0; i < fi->nbOutput; i++ ) {
        const TA_OutputParameterInfo *outInfo;
        TA_GetOutputParameterInfo(fi->handle, i, &outInfo);
        if( outInfo->type == TA_Output_Real ) {
            realOuts[i] = calloc(maxOut, sizeof(TA_Real));
            TA_SetOutputParamRealPtr(ph, i, realOuts[i]);
        } else {
            intOuts[i] = calloc(maxOut, sizeof(TA_Integer));
            TA_SetOutputParamIntegerPtr(ph, i, intOuts[i]);
        }
    }

    /* Warmup */
    TA_Integer beg, nb;
    TA_CallFunc(ph, startIdx, endIdx, &beg, &nb);

    /* Timed loop */
    long long t0 = get_nanotime();
    for( int i = 0; i < iters; i++ ) {
        TA_CallFunc(ph, startIdx, endIdx, &beg, &nb);
    }
    long long elapsed = (get_nanotime() - t0) / iters;

    for( unsigned int i = 0; i < fi->nbOutput; i++ ) {
        free(realOuts[i]); free(intOuts[i]);
    }
    free(realOuts); free(intOuts);
    TA_ParamHolderFree(ph);
    return elapsed;
}

/* ---- Per-indicator benchmark callback ---- */

typedef struct {
    const char *functionFilter;
    const char *langFilter;
    char *reqBuf;
    char *respBuf;
    int iters;
    int count;
} BenchContext;

static int lang_matches(const char *filter, const char *name) {
    if( !filter ) return 1;
    return strstr(filter, name) != NULL;
}

static int func_matches(const char *filter, const char *name) {
    if( !filter ) return 1;
    /* Comma-separated substring match */
    char buf[512]; strncpy(buf, filter, sizeof(buf)-1); buf[sizeof(buf)-1]='\0';
    for( char *tok = strtok(buf, ","); tok; tok = strtok(NULL, ",") )
        if( strcasestr(name, tok) ) return 1;
    return 0;
}

static void bench_one_function(const TA_FuncInfo *fi, void *opaque) {
    BenchContext *ctx = (BenchContext *)opaque;
    if( !func_matches(ctx->functionFilter, fi->name) ) return;

    int startIdx = 0;
    int endIdx = g_nPoints - 1;

    /* C-ref */
    long long ref_ns = run_ref(fi, startIdx, endIdx, ctx->iters);
    printf("%-20s %10lld", fi->name, ref_ns);

    /* Each language server */
    build_bench_request(ctx->reqBuf, JSON_BUF_SIZE, fi, startIdx, endIdx, ctx->iters);

    for( unsigned int li = 0; li < NUM_LANGUAGES; li++ ) {
        if( !LANGUAGES[li].active ) continue;

        if( codegen_pipe_call(&LANGUAGES[li].cp, ctx->reqBuf, ctx->respBuf, JSON_BUF_SIZE) != TA_TEST_PASS ) {
            printf(" %10s", "ERR");
            continue;
        }
        int len;
        const char *t = json_find_field(ctx->respBuf, "timing_ns", &len);
        if( !t ) { printf(" %10s", "ERR"); continue; }

        long long srv_ns = strtoll(t, NULL, 10);
        double ratio = (ref_ns > 0) ? (double)srv_ns / (double)ref_ns : 0.0;
        const char *clr = (ratio > 1.10) ? "\033[31m" : (ratio < 0.90) ? "\033[32m" : "";
        const char *rst = (*clr) ? "\033[0m" : "";
        printf(" %s%10lld%s", clr, srv_ns, rst);
    }
    printf("\n");
    ctx->count++;
}

/* ---- Main ---- */

int main(int argc, char *argv[]) {
    int n_points = DEFAULT_POINTS;
    int n_iters  = DEFAULT_ITERS;
    const char *lang_filter = NULL;
    const char *func_filter = NULL;

    for( int i = 1; i < argc; i++ ) {
        if( strncmp(argv[i], "--points=", 9) == 0 )       n_points = atoi(argv[i]+9);
        else if( strncmp(argv[i], "--iters=", 8) == 0 )    n_iters = atoi(argv[i]+8);
        else if( strncmp(argv[i], "--language=", 11) == 0 ) lang_filter = argv[i]+11;
        else if( strncmp(argv[i], "--function=", 11) == 0 ) func_filter = argv[i]+11;
    }
    if( n_points > MAX_POINTS ) n_points = MAX_POINTS;

    TA_Initialize();
    generate_price_data(n_points);

    printf("ta_bench: %d points, %d iters (server-side)\n\n", n_points, n_iters);

    /* Start servers + load data */
    char *reqBuf  = malloc(JSON_BUF_SIZE);
    char *respBuf = malloc(JSON_BUF_SIZE);

    for( unsigned int li = 0; li < NUM_LANGUAGES; li++ ) {
        if( !lang_matches(lang_filter, LANGUAGES[li].name) ) continue;
        if( codegen_pipe_open(&LANGUAGES[li].cp, LANGUAGES[li].argv) == TA_TEST_PASS ) {
            LANGUAGES[li].active = 1;
            printf("  Started %s server (pid %d)\n", LANGUAGES[li].display, LANGUAGES[li].cp.child_pid);
        } else {
            printf("  FAILED to start %s server\n", LANGUAGES[li].display);
        }
    }

    printf("  Loading %d points into servers...\n", n_points);
    for( unsigned int li = 0; li < NUM_LANGUAGES; li++ ) {
        if( !LANGUAGES[li].active ) continue;
        if( send_load_data(&LANGUAGES[li], reqBuf, JSON_BUF_SIZE, respBuf, JSON_BUF_SIZE) != 0 ) {
            printf("    %s: load_data FAILED\n", LANGUAGES[li].display);
            LANGUAGES[li].active = 0;
        } else {
            printf("    %s: ready\n", LANGUAGES[li].display);
        }
    }
    printf("\n");

    /* Header */
    printf("%-20s %10s", "Function", "C-ref");
    for( unsigned int li = 0; li < NUM_LANGUAGES; li++ )
        if( LANGUAGES[li].active )
            printf(" %10s", LANGUAGES[li].display);
    printf("\n");
    printf("%-20s %10s", "--------", "------");
    for( unsigned int li = 0; li < NUM_LANGUAGES; li++ )
        if( LANGUAGES[li].active )
            printf(" %10s", "------");
    printf("\n");

    /* Run all indicators */
    BenchContext ctx = {
        .functionFilter = func_filter,
        .langFilter     = lang_filter,
        .reqBuf         = reqBuf,
        .respBuf        = respBuf,
        .iters          = n_iters,
        .count          = 0,
    };
    TA_ForEachFunc(bench_one_function, &ctx);

    printf("\n%d indicators benchmarked (%d points, %d iters)\n", ctx.count, n_points, n_iters);
    printf("(red >10%% slower, green >10%% faster than C-ref)\n");

    /* Cleanup */
    for( unsigned int li = 0; li < NUM_LANGUAGES; li++ )
        if( LANGUAGES[li].active )
            codegen_pipe_close(&LANGUAGES[li].cp);
    free(reqBuf); free(respBuf);
    free(g_open); free(g_high); free(g_low); free(g_close); free(g_volume); free(g_oi);
    TA_Shutdown();
    return 0;
}
