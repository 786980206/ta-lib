/* ta_bench — Performance benchmark for TA-Lib indicators.
 *
 * Compares C reference (direct call, linked) against codegen language
 * servers using the load_data + use_preloaded protocol:
 *   1. Generate deterministic OHLCV data
 *   2. Send load_data to each server (triggers language-specific warmup)
 *   3. Run each indicator with varying ranges, server-side iteration
 *   4. Report per-indicator per-language timing
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
#define MAX_FUNCTIONS     200
#define DEFAULT_POINTS    100000
#define DEFAULT_ITERS     100
#define JSON_BUF_SIZE     (32 * 1024 * 1024)   /* 32 MB for load_data */

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

/* ---- Deterministic test data (LCG PRNG, seed 42) ---- */

static double g_open[MAX_POINTS];
static double g_high[MAX_POINTS];
static double g_low[MAX_POINTS];
static double g_close[MAX_POINTS];
static double g_volume[MAX_POINTS];

/* Working copies for C-ref (protect against mutation) */
static double g_wOpen[MAX_POINTS];
static double g_wHigh[MAX_POINTS];
static double g_wLow[MAX_POINTS];
static double g_wClose[MAX_POINTS];
static double g_wVolume[MAX_POINTS];

static void generate_price_data(int n)
{
    unsigned int seed = 42;
    double price = 100.0;
    for( int i = 0; i < n; i++ )
    {
        seed = seed * 1103515245 + 12345;
        double r = ((double)(seed >> 16) / 32768.0) - 1.0;
        double change = r * 2.0;
        double o = price;
        double c = price + change;
        double h = fmax(o, c) + fabs(r) * 0.5;
        double l = fmin(o, c) - fabs(r) * 0.5;
        if( l < 1.0 ) l = 1.0;
        g_open[i] = o; g_high[i] = h; g_low[i] = l; g_close[i] = c;
        g_volume[i] = 1000000.0 + r * 500000.0;
        price = c;
        if( price < 1.0 ) price = 1.0;
    }
}

static void copy_close(int n) {
    memcpy(g_wClose, g_close, n * sizeof(double));
}
static void copy_hlc(int n) {
    memcpy(g_wHigh, g_high, n * sizeof(double));
    memcpy(g_wLow, g_low, n * sizeof(double));
    memcpy(g_wClose, g_close, n * sizeof(double));
}

/* ---- JSON helpers ---- */

static int json_write_double_array(char *buf, int buf_size, const double *arr, int n)
{
    int pos = 0;
    pos += snprintf(buf + pos, buf_size - pos, "[");
    for( int i = 0; i < n; i++ )
    {
        if( i > 0 ) pos += snprintf(buf + pos, buf_size - pos, ",");
        pos += snprintf(buf + pos, buf_size - pos, "%.10g", arr[i]);
    }
    pos += snprintf(buf + pos, buf_size - pos, "]");
    return pos;
}

static const char *json_find_field(const char *json, const char *field, int *len)
{
    char pattern[128];
    snprintf(pattern, sizeof(pattern), "\"%s\":", field);
    const char *p = strstr(json, pattern);
    if( !p ) return NULL;
    p += strlen(pattern);
    while( *p == ' ' ) p++;
    const char *end = p;
    if( *end == '[' ) { int depth = 1; end++;
        while( depth > 0 && *end ) { if(*end=='[') depth++; if(*end==']') depth--; end++; }
    } else { while( *end && *end != ',' && *end != '}' ) end++; }
    *len = (int)(end - p);
    return p;
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
    {"c",      "C",      argv_c,      {0}, 0},
    {"rust",   "Rust",   argv_rust,   {0}, 0},
    {"java",   "Java",   argv_java,   {0}, 0},
    {"dotnet", ".NET",   argv_dotnet, {0}, 0},
};
#define NUM_LANGUAGES (sizeof(LANGUAGES)/sizeof(LANGUAGES[0]))

/* ---- Indicator definitions ---- */

volatile double g_sink;

typedef struct {
    const char *name;
    int is_price; /* 1 = uses OHLCV, 0 = uses close only */
    const char *params_json; /* optional params as JSON fragment */
    /* C-ref function: runs indicator, returns ns/call */
    long long (*run_ref)(int startIdx, int endIdx, int n, int iters);
} BenchIndicator;

/* ---- C-ref implementations ---- */

static long long ref_SMA(int s, int e, int n, int iters) {
    double *out = malloc(n * sizeof(double)); int beg, nb;
    copy_close(n);
    TA_SMA(s, e, g_wClose, 20, &beg, &nb, out); /* warmup */
    long long t0 = get_nanotime();
    for( int i = 0; i < iters; i++ ) {
        copy_close(n);
        TA_SMA(s, e, g_wClose, 20, &beg, &nb, out);
        g_sink = out[0];
    }
    long long r = (get_nanotime() - t0) / iters; free(out); return r;
}

static long long ref_EMA(int s, int e, int n, int iters) {
    double *out = malloc(n * sizeof(double)); int beg, nb;
    copy_close(n);
    TA_EMA(s, e, g_wClose, 20, &beg, &nb, out);
    long long t0 = get_nanotime();
    for( int i = 0; i < iters; i++ ) {
        copy_close(n);
        TA_EMA(s, e, g_wClose, 20, &beg, &nb, out);
        g_sink = out[0];
    }
    long long r = (get_nanotime() - t0) / iters; free(out); return r;
}

static long long ref_RSI(int s, int e, int n, int iters) {
    double *out = malloc(n * sizeof(double)); int beg, nb;
    copy_close(n);
    TA_RSI(s, e, g_wClose, 14, &beg, &nb, out);
    long long t0 = get_nanotime();
    for( int i = 0; i < iters; i++ ) {
        copy_close(n);
        TA_RSI(s, e, g_wClose, 14, &beg, &nb, out);
        g_sink = out[0];
    }
    long long r = (get_nanotime() - t0) / iters; free(out); return r;
}

static long long ref_MACD(int s, int e, int n, int iters) {
    double *o1 = malloc(n*sizeof(double)), *o2 = malloc(n*sizeof(double)), *o3 = malloc(n*sizeof(double));
    int beg, nb;
    copy_close(n);
    TA_MACD(s, e, g_wClose, 12, 26, 9, &beg, &nb, o1, o2, o3);
    long long t0 = get_nanotime();
    for( int i = 0; i < iters; i++ ) {
        copy_close(n);
        TA_MACD(s, e, g_wClose, 12, 26, 9, &beg, &nb, o1, o2, o3);
        g_sink = o1[0];
    }
    long long r = (get_nanotime() - t0) / iters; free(o1); free(o2); free(o3); return r;
}

static long long ref_STOCH(int s, int e, int n, int iters) {
    double *outK = malloc(n*sizeof(double)), *outD = malloc(n*sizeof(double));
    int beg, nb;
    copy_hlc(n);
    TA_STOCH(s, e, g_wHigh, g_wLow, g_wClose, 5, 3, TA_MAType_SMA, 3, TA_MAType_SMA, &beg, &nb, outK, outD);
    long long t0 = get_nanotime();
    for( int i = 0; i < iters; i++ ) {
        copy_hlc(n);
        TA_STOCH(s, e, g_wHigh, g_wLow, g_wClose, 5, 3, TA_MAType_SMA, 3, TA_MAType_SMA, &beg, &nb, outK, outD);
        g_sink = outK[0];
    }
    long long r = (get_nanotime() - t0) / iters; free(outK); free(outD); return r;
}

static long long ref_BBANDS(int s, int e, int n, int iters) {
    double *oU = malloc(n*sizeof(double)), *oM = malloc(n*sizeof(double)), *oL = malloc(n*sizeof(double));
    int beg, nb;
    copy_close(n);
    TA_BBANDS(s, e, g_wClose, 20, 2.0, 2.0, TA_MAType_SMA, &beg, &nb, oU, oM, oL);
    long long t0 = get_nanotime();
    for( int i = 0; i < iters; i++ ) {
        copy_close(n);
        TA_BBANDS(s, e, g_wClose, 20, 2.0, 2.0, TA_MAType_SMA, &beg, &nb, oU, oM, oL);
        g_sink = oU[0];
    }
    long long r = (get_nanotime() - t0) / iters; free(oU); free(oM); free(oL); return r;
}

/* ---- Indicator table ---- */

static BenchIndicator INDICATORS[] = {
    {"SMA",    0, "\"optInTimePeriod\":20",    ref_SMA},
    {"EMA",    0, "\"optInTimePeriod\":20",    ref_EMA},
    {"RSI",    0, "\"optInTimePeriod\":14",    ref_RSI},
    {"MACD",   0, "\"optInFastPeriod\":12,\"optInSlowPeriod\":26,\"optInSignalPeriod\":9", ref_MACD},
    {"STOCH",  1, "\"optInFastK_Period\":5,\"optInSlowK_Period\":3,\"optInSlowK_MAType\":0,\"optInSlowD_Period\":3,\"optInSlowD_MAType\":0", ref_STOCH},
    {"BBANDS", 0, "\"optInTimePeriod\":20,\"optInNbDevUp\":2.0,\"optInNbDevDn\":2.0,\"optInMAType\":0", ref_BBANDS},
};
#define NUM_INDICATORS (sizeof(INDICATORS)/sizeof(INDICATORS[0]))

/* ---- Server communication ---- */

static int send_load_data(BenchLanguage *lang, char *buf, int buf_size, char *resp, int resp_size, int n)
{
    int pos = snprintf(buf, buf_size, "{\"method\":\"load_data\",\"params\":{\"open\":");
    pos += json_write_double_array(buf+pos, buf_size-pos, g_open, n);
    pos += snprintf(buf+pos, buf_size-pos, ",\"high\":");
    pos += json_write_double_array(buf+pos, buf_size-pos, g_high, n);
    pos += snprintf(buf+pos, buf_size-pos, ",\"low\":");
    pos += json_write_double_array(buf+pos, buf_size-pos, g_low, n);
    pos += snprintf(buf+pos, buf_size-pos, ",\"close\":");
    pos += json_write_double_array(buf+pos, buf_size-pos, g_close, n);
    pos += snprintf(buf+pos, buf_size-pos, ",\"volume\":");
    pos += json_write_double_array(buf+pos, buf_size-pos, g_volume, n);
    pos += snprintf(buf+pos, buf_size-pos, ",\"openInterest\":");
    /* Send zeros for OI */
    pos += snprintf(buf+pos, buf_size-pos, "[");
    for( int i = 0; i < n; i++ ) pos += snprintf(buf+pos, buf_size-pos, "%s0", i?",":"");
    pos += snprintf(buf+pos, buf_size-pos, "]}}");

    if( codegen_pipe_call(&lang->cp, buf, resp, resp_size) != TA_TEST_PASS )
        return -1;
    return (strstr(resp, "\"ok\"") != NULL) ? 0 : -1;
}

static long long bench_indicator(BenchLanguage *lang, BenchIndicator *ind,
                                  int startIdx, int endIdx, int iters,
                                  char *buf, int buf_size, char *resp, int resp_size)
{
    int pos = snprintf(buf, buf_size,
        "{\"method\":\"TA_%s\",\"params\":{\"startIdx\":%d,\"endIdx\":%d,%s,"
        "\"use_preloaded\":1,\"iters\":%d}}",
        ind->name, startIdx, endIdx, ind->params_json, iters);
    (void)pos;

    if( codegen_pipe_call(&lang->cp, buf, resp, resp_size) != TA_TEST_PASS )
        return -1;

    int len;
    const char *t = json_find_field(resp, "timing_ns", &len);
    return t ? strtoll(t, NULL, 10) : -1;
}

/* ---- CLI helpers ---- */

static int language_matches(const char *filter, const char *name) {
    if( !filter ) return 1;
    return strstr(filter, name) != NULL;
}

static int function_matches(const char *filter, const char *name) {
    if( !filter ) return 1;
    char buf[512]; strncpy(buf, filter, sizeof(buf)-1); buf[sizeof(buf)-1]='\0';
    char *tok = strtok(buf, ",");
    while( tok ) { if( strcasestr(name, tok) ) return 1; tok = strtok(NULL, ","); }
    return 0;
}

/* ---- Main ---- */

int main(int argc, char *argv[])
{
    int n_points = DEFAULT_POINTS;
    int n_iters  = DEFAULT_ITERS;
    const char *lang_filter = NULL;
    const char *func_filter = NULL;

    for( int i = 1; i < argc; i++ ) {
        if( strncmp(argv[i], "--points=", 9) == 0 )      n_points = atoi(argv[i]+9);
        else if( strncmp(argv[i], "--iters=", 8) == 0 )   n_iters = atoi(argv[i]+8);
        else if( strncmp(argv[i], "--language=", 11) == 0 ) lang_filter = argv[i]+11;
        else if( strncmp(argv[i], "--function=", 11) == 0 ) func_filter = argv[i]+11;
    }
    if( n_points > MAX_POINTS ) n_points = MAX_POINTS;

    TA_Initialize();

    printf("ta_bench: %d points, %d iters (server-side)\n\n", n_points, n_iters);

    /* Generate test data */
    generate_price_data(n_points);

    /* Start servers */
    for( unsigned li = 0; li < NUM_LANGUAGES; li++ ) {
        if( !language_matches(lang_filter, LANGUAGES[li].name) ) continue;
        if( codegen_pipe_open(&LANGUAGES[li].cp, LANGUAGES[li].argv) == TA_TEST_PASS ) {
            LANGUAGES[li].active = 1;
            printf("  Started %s server (pid %d)\n", LANGUAGES[li].display, LANGUAGES[li].cp.child_pid);
        } else {
            printf("  FAILED to start %s server\n", LANGUAGES[li].display);
        }
    }

    /* Allocate JSON buffers */
    char *request  = malloc(JSON_BUF_SIZE);
    char *response = malloc(JSON_BUF_SIZE);

    /* Send load_data to each server */
    printf("  Loading %d points into servers...\n", n_points);
    for( unsigned li = 0; li < NUM_LANGUAGES; li++ ) {
        if( !LANGUAGES[li].active ) continue;
        if( send_load_data(&LANGUAGES[li], request, JSON_BUF_SIZE, response, JSON_BUF_SIZE, n_points) != 0 ) {
            printf("    %s: load_data FAILED\n", LANGUAGES[li].display);
            LANGUAGES[li].active = 0;
        } else {
            printf("    %s: ready\n", LANGUAGES[li].display);
        }
    }
    printf("\n");

    /* Print header */
    printf("%-10s %10s", "Function", "C-ref");
    for( unsigned li = 0; li < NUM_LANGUAGES; li++ )
        if( LANGUAGES[li].active )
            printf(" %10s", LANGUAGES[li].display);
    printf("\n");
    printf("%-10s %10s", "--------", "------");
    for( unsigned li = 0; li < NUM_LANGUAGES; li++ )
        if( LANGUAGES[li].active )
            printf(" %10s", "------");
    printf("\n");

    /* Run benchmarks — full range for now */
    for( unsigned fi = 0; fi < NUM_INDICATORS; fi++ )
    {
        BenchIndicator *ind = &INDICATORS[fi];
        if( !function_matches(func_filter, ind->name) ) continue;

        int startIdx = 0;
        int endIdx = n_points - 1;

        /* C reference (direct call with mutation protection) */
        long long ref_ns = ind->run_ref(startIdx, endIdx, n_points, n_iters);
        printf("%-10s %10lld", ind->name, ref_ns);

        /* Each language server */
        for( unsigned li = 0; li < NUM_LANGUAGES; li++ )
        {
            if( !LANGUAGES[li].active ) continue;
            long long srv_ns = bench_indicator(&LANGUAGES[li], ind, startIdx, endIdx, n_iters,
                                               request, JSON_BUF_SIZE, response, JSON_BUF_SIZE);
            if( srv_ns < 0 ) {
                printf(" %10s", "ERR");
            } else {
                double ratio = (ref_ns > 0) ? (double)srv_ns / (double)ref_ns : 0.0;
                const char *clr = (ratio > 1.10) ? "\033[31m" : (ratio < 0.90) ? "\033[32m" : "";
                const char *rst = (*clr) ? "\033[0m" : "";
                printf(" %s%10lld%s", clr, srv_ns, rst);
            }
        }
        printf("\n");
    }

    printf("\n(times in ns, avg over %d server-side iterations on %d points)\n", n_iters, n_points);
    printf("(C-ref includes memcpy for mutation protection; red >10%% slower, green >10%% faster)\n");

    /* Cleanup */
    for( unsigned li = 0; li < NUM_LANGUAGES; li++ )
        if( LANGUAGES[li].active )
            codegen_pipe_close(&LANGUAGES[li].cp);
    free(request); free(response);
    TA_Shutdown();
    return 0;
}
