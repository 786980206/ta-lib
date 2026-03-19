/* ta_bench — Performance benchmark for TA-Lib indicators.
 *
 * Compares C reference (direct call, linked) against codegen language
 * servers (JSON-RPC). Uses larger dataset and multi-iteration averaging
 * for stable, meaningful measurements.
 *
 * Usage:
 *   ./ta_bench                                # all indicators, all languages
 *   ./ta_bench --points=100000 --iters=50     # 100k points, 50 iterations
 *   ./ta_bench --language=c,rust              # filter languages
 *   ./ta_bench --function=RSI,SMA             # filter indicators
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

#define MAX_FUNCTIONS     200
#define MAX_OUTPUTS       3
#define DEFAULT_POINTS    10000
#define DEFAULT_ITERS     20
#define DEFAULT_WARMUP    3

/* JSON buffer: 100k doubles × ~20 chars = ~2MB per array, need room for 6 arrays + overhead */
#define JSON_BUF_SIZE     (16 * 1024 * 1024)   /* 16 MB */

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

static void generate_price_data(double *open, double *high, double *low,
                                double *close, double *volume, int n)
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
        open[i] = o; high[i] = h; low[i] = l; close[i] = c;
        volume[i] = 1000000.0 + r * 500000.0;
        price = c;
        if( price < 1.0 ) price = 1.0;
    }
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
    /* Find end: number ends at , or } */
    const char *end = p;
    if( *end == '[' ) { /* skip array */ int depth = 1; end++;
        while( depth > 0 && *end ) { if(*end=='[') depth++; if(*end==']') depth--; end++; }
    } else {
        while( *end && *end != ',' && *end != '}' ) end++;
    }
    *len = (int)(end - p);
    return p;
}

/* ---- Language server definitions ---- */

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

typedef struct {
    const char *name;
    /* Builds JSON request into buf. Returns length written. */
    int (*build_request)(char *buf, int buf_size,
                         const double *open, const double *high, const double *low,
                         const double *close, const double *volume, int n);
    /* Runs C reference. Returns average ns over iters. */
    long long (*run_ref)(const double *open, const double *high, const double *low,
                         const double *close, const double *volume, int n, int iters);
} BenchIndicator;

volatile double g_sink; /* prevent optimization */

/* ---- Indicator implementations ---- */

static int build_RSI(char *buf, int sz, const double *o, const double *h,
                     const double *l, const double *c, const double *v, int n)
{
    (void)o; (void)h; (void)l; (void)v;
    int pos = snprintf(buf, sz, "{\"method\":\"TA_RSI\",\"params\":{\"startIdx\":0,\"endIdx\":%d,"
                       "\"optInTimePeriod\":14,\"inReal\":", n-1);
    pos += json_write_double_array(buf+pos, sz-pos, c, n);
    pos += snprintf(buf+pos, sz-pos, "}}");
    return pos;
}

static long long run_RSI_ref(const double *o, const double *h, const double *l,
                             const double *c, const double *v, int n, int iters)
{
    double *out = malloc(n * sizeof(double));
    int beg, nb;
    (void)o; (void)h; (void)l; (void)v;
    TA_RSI(0, n-1, c, 14, &beg, &nb, out);
    long long t0 = get_nanotime();
    for( int i = 0; i < iters; i++ ) {
        TA_RSI(0, n-1, c, 14, &beg, &nb, out);
        g_sink = out[0];
    }
    long long elapsed = (get_nanotime() - t0) / iters;
    free(out);
    return elapsed;
}

static int build_SMA(char *buf, int sz, const double *o, const double *h,
                     const double *l, const double *c, const double *v, int n)
{
    (void)o; (void)h; (void)l; (void)v;
    int pos = snprintf(buf, sz, "{\"method\":\"TA_SMA\",\"params\":{\"startIdx\":0,\"endIdx\":%d,"
                       "\"optInTimePeriod\":20,\"inReal\":", n-1);
    pos += json_write_double_array(buf+pos, sz-pos, c, n);
    pos += snprintf(buf+pos, sz-pos, "}}");
    return pos;
}

static long long run_SMA_ref(const double *o, const double *h, const double *l,
                             const double *c, const double *v, int n, int iters)
{
    double *out = malloc(n * sizeof(double));
    int beg, nb;
    (void)o; (void)h; (void)l; (void)v;
    TA_SMA(0, n-1, c, 20, &beg, &nb, out);
    long long t0 = get_nanotime();
    for( int i = 0; i < iters; i++ ) {
        TA_SMA(0, n-1, c, 20, &beg, &nb, out);
        g_sink = out[0];
    }
    long long elapsed = (get_nanotime() - t0) / iters;
    free(out);
    return elapsed;
}

static int build_EMA(char *buf, int sz, const double *o, const double *h,
                     const double *l, const double *c, const double *v, int n)
{
    (void)o; (void)h; (void)l; (void)v;
    int pos = snprintf(buf, sz, "{\"method\":\"TA_EMA\",\"params\":{\"startIdx\":0,\"endIdx\":%d,"
                       "\"optInTimePeriod\":20,\"inReal\":", n-1);
    pos += json_write_double_array(buf+pos, sz-pos, c, n);
    pos += snprintf(buf+pos, sz-pos, "}}");
    return pos;
}

static long long run_EMA_ref(const double *o, const double *h, const double *l,
                             const double *c, const double *v, int n, int iters)
{
    double *out = malloc(n * sizeof(double));
    int beg, nb;
    (void)o; (void)h; (void)l; (void)v;
    TA_EMA(0, n-1, c, 20, &beg, &nb, out);
    long long t0 = get_nanotime();
    for( int i = 0; i < iters; i++ ) {
        TA_EMA(0, n-1, c, 20, &beg, &nb, out);
        g_sink = out[0];
    }
    long long elapsed = (get_nanotime() - t0) / iters;
    free(out);
    return elapsed;
}

static int build_MACD(char *buf, int sz, const double *o, const double *h,
                      const double *l, const double *c, const double *v, int n)
{
    (void)o; (void)h; (void)l; (void)v;
    int pos = snprintf(buf, sz, "{\"method\":\"TA_MACD\",\"params\":{\"startIdx\":0,\"endIdx\":%d,"
                       "\"optInFastPeriod\":12,\"optInSlowPeriod\":26,\"optInSignalPeriod\":9,"
                       "\"inReal\":", n-1);
    pos += json_write_double_array(buf+pos, sz-pos, c, n);
    pos += snprintf(buf+pos, sz-pos, "}}");
    return pos;
}

static long long run_MACD_ref(const double *o, const double *h, const double *l,
                              const double *c, const double *v, int n, int iters)
{
    double *out1 = malloc(n * sizeof(double));
    double *out2 = malloc(n * sizeof(double));
    double *out3 = malloc(n * sizeof(double));
    int beg, nb;
    (void)o; (void)h; (void)l; (void)v;
    TA_MACD(0, n-1, c, 12, 26, 9, &beg, &nb, out1, out2, out3);
    long long t0 = get_nanotime();
    for( int i = 0; i < iters; i++ ) {
        TA_MACD(0, n-1, c, 12, 26, 9, &beg, &nb, out1, out2, out3);
        g_sink = out1[0];
    }
    long long elapsed = (get_nanotime() - t0) / iters;
    free(out1); free(out2); free(out3);
    return elapsed;
}

static int build_STOCH(char *buf, int sz, const double *o, const double *h,
                       const double *l, const double *c, const double *v, int n)
{
    (void)o; (void)v;
    int pos = snprintf(buf, sz, "{\"method\":\"TA_STOCH\",\"params\":{\"startIdx\":0,\"endIdx\":%d,"
                       "\"optInFastK_Period\":5,\"optInSlowK_Period\":3,"
                       "\"optInSlowK_MAType\":0,\"optInSlowD_Period\":3,"
                       "\"optInSlowD_MAType\":0,\"inHigh\":", n-1);
    pos += json_write_double_array(buf+pos, sz-pos, h, n);
    pos += snprintf(buf+pos, sz-pos, ",\"inLow\":");
    pos += json_write_double_array(buf+pos, sz-pos, l, n);
    pos += snprintf(buf+pos, sz-pos, ",\"inClose\":");
    pos += json_write_double_array(buf+pos, sz-pos, c, n);
    pos += snprintf(buf+pos, sz-pos, "}}");
    return pos;
}

static long long run_STOCH_ref(const double *o, const double *h, const double *l,
                               const double *c, const double *v, int n, int iters)
{
    double *outK = malloc(n * sizeof(double));
    double *outD = malloc(n * sizeof(double));
    int beg, nb;
    (void)o; (void)v;
    TA_STOCH(0, n-1, h, l, c, 5, 3, TA_MAType_SMA, 3, TA_MAType_SMA, &beg, &nb, outK, outD);
    long long t0 = get_nanotime();
    for( int i = 0; i < iters; i++ ) {
        TA_STOCH(0, n-1, h, l, c, 5, 3, TA_MAType_SMA, 3, TA_MAType_SMA, &beg, &nb, outK, outD);
        g_sink = outK[0];
    }
    long long elapsed = (get_nanotime() - t0) / iters;
    free(outK); free(outD);
    return elapsed;
}

static int build_BBANDS(char *buf, int sz, const double *o, const double *h,
                        const double *l, const double *c, const double *v, int n)
{
    (void)o; (void)h; (void)l; (void)v;
    int pos = snprintf(buf, sz, "{\"method\":\"TA_BBANDS\",\"params\":{\"startIdx\":0,\"endIdx\":%d,"
                       "\"optInTimePeriod\":20,\"optInNbDevUp\":2.0,\"optInNbDevDn\":2.0,"
                       "\"optInMAType\":0,\"inReal\":", n-1);
    pos += json_write_double_array(buf+pos, sz-pos, c, n);
    pos += snprintf(buf+pos, sz-pos, "}}");
    return pos;
}

static long long run_BBANDS_ref(const double *o, const double *h, const double *l,
                                const double *c, const double *v, int n, int iters)
{
    double *outU = malloc(n * sizeof(double));
    double *outM = malloc(n * sizeof(double));
    double *outL = malloc(n * sizeof(double));
    int beg, nb;
    (void)o; (void)h; (void)l; (void)v;
    TA_BBANDS(0, n-1, c, 20, 2.0, 2.0, TA_MAType_SMA, &beg, &nb, outU, outM, outL);
    long long t0 = get_nanotime();
    for( int i = 0; i < iters; i++ ) {
        TA_BBANDS(0, n-1, c, 20, 2.0, 2.0, TA_MAType_SMA, &beg, &nb, outU, outM, outL);
        g_sink = outU[0];
    }
    long long elapsed = (get_nanotime() - t0) / iters;
    free(outU); free(outM); free(outL);
    return elapsed;
}

/* ---- All indicators ---- */

static BenchIndicator INDICATORS[] = {
    {"SMA",    build_SMA,    run_SMA_ref},
    {"EMA",    build_EMA,    run_EMA_ref},
    {"RSI",    build_RSI,    run_RSI_ref},
    {"MACD",   build_MACD,   run_MACD_ref},
    {"STOCH",  build_STOCH,  run_STOCH_ref},
    {"BBANDS", build_BBANDS, run_BBANDS_ref},
};
#define NUM_INDICATORS (sizeof(INDICATORS)/sizeof(INDICATORS[0]))

/* ---- Server benchmarking ---- */

static long long bench_server(BenchLanguage *lang, const char *request,
                              char *response, int resp_size, int iters, int warmup)
{
    /* Warmup calls */
    for( int i = 0; i < warmup; i++ )
        codegen_pipe_call(&lang->cp, request, response, resp_size);

    /* Timed calls — extract timing_ns from server response */
    long long total_ns = 0;
    int count = 0;
    for( int i = 0; i < iters; i++ )
    {
        if( codegen_pipe_call(&lang->cp, request, response, resp_size) != TA_TEST_PASS )
            continue;
        int len;
        const char *t = json_find_field(response, "timing_ns", &len);
        if( t ) {
            total_ns += strtoll(t, NULL, 10);
            count++;
        }
    }
    return (count > 0) ? total_ns / count : -1;
}

/* ---- CLI parsing ---- */

static int language_matches(const char *filter, const char *name)
{
    if( !filter ) return 1;
    return strstr(filter, name) != NULL;
}

static int function_matches(const char *filter, const char *name)
{
    if( !filter ) return 1;
    /* Comma-separated filter, case-insensitive substring match */
    char buf[512];
    strncpy(buf, filter, sizeof(buf)-1);
    buf[sizeof(buf)-1] = '\0';
    char *tok = strtok(buf, ",");
    while( tok ) {
        if( strcasestr(name, tok) ) return 1;
        tok = strtok(NULL, ",");
    }
    return 0;
}

/* ---- Main ---- */

int main(int argc, char *argv[])
{
    int n_points = DEFAULT_POINTS;
    int n_iters  = DEFAULT_ITERS;
    int n_warmup = DEFAULT_WARMUP;
    const char *lang_filter = NULL;
    const char *func_filter = NULL;

    for( int i = 1; i < argc; i++ ) {
        if( strncmp(argv[i], "--points=", 9) == 0 )     n_points = atoi(argv[i]+9);
        else if( strncmp(argv[i], "--iters=", 8) == 0 )  n_iters = atoi(argv[i]+8);
        else if( strncmp(argv[i], "--warmup=", 9) == 0 ) n_warmup = atoi(argv[i]+9);
        else if( strncmp(argv[i], "--language=", 11) == 0 ) lang_filter = argv[i]+11;
        else if( strncmp(argv[i], "--function=", 11) == 0 ) func_filter = argv[i]+11;
    }

    TA_Initialize();

    printf("ta_bench: %d points, %d iters, %d warmup\n\n", n_points, n_iters, n_warmup);

    /* Generate test data */
    double *open   = malloc(n_points * sizeof(double));
    double *high   = malloc(n_points * sizeof(double));
    double *low    = malloc(n_points * sizeof(double));
    double *close  = malloc(n_points * sizeof(double));
    double *volume = malloc(n_points * sizeof(double));
    generate_price_data(open, high, low, close, volume, n_points);

    /* Start language servers */
    int any_server = 0;
    for( unsigned li = 0; li < NUM_LANGUAGES; li++ ) {
        if( !language_matches(lang_filter, LANGUAGES[li].name) ) continue;
        ErrorNumber err = codegen_pipe_open(&LANGUAGES[li].cp, LANGUAGES[li].argv);
        if( err == TA_TEST_PASS ) {
            LANGUAGES[li].active = 1;
            any_server = 1;
            printf("  Started %s server (pid %d)\n", LANGUAGES[li].display, LANGUAGES[li].cp.child_pid);
        } else {
            printf("  FAILED to start %s server\n", LANGUAGES[li].display);
        }
    }
    printf("\n");

    /* Allocate JSON buffers */
    char *request  = malloc(JSON_BUF_SIZE);
    char *response = malloc(JSON_BUF_SIZE);

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

    /* Run benchmarks */
    for( unsigned fi = 0; fi < NUM_INDICATORS; fi++ )
    {
        BenchIndicator *ind = &INDICATORS[fi];
        if( !function_matches(func_filter, ind->name) ) continue;

        /* C reference */
        long long ref_ns = ind->run_ref(open, high, low, close, volume, n_points, n_iters);

        printf("%-10s %10lld", ind->name, ref_ns);

        /* Build JSON request (once, reuse for all servers) */
        ind->build_request(request, JSON_BUF_SIZE, open, high, low, close, volume, n_points);

        /* Each language server */
        for( unsigned li = 0; li < NUM_LANGUAGES; li++ )
        {
            if( !LANGUAGES[li].active ) continue;

            long long srv_ns = bench_server(&LANGUAGES[li], request, response,
                                            JSON_BUF_SIZE, n_iters, n_warmup);

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

    /* Summary */
    printf("\n(times in nanoseconds, avg over %d calls on %d points)\n", n_iters, n_points);
    printf("(red = >10%% slower than C-ref, green = >10%% faster)\n");

    /* Cleanup */
    for( unsigned li = 0; li < NUM_LANGUAGES; li++ )
        if( LANGUAGES[li].active )
            codegen_pipe_close(&LANGUAGES[li].cp);

    free(request); free(response);
    free(open); free(high); free(low); free(close); free(volume);
    TA_Shutdown();
    return 0;
}
