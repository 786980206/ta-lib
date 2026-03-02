#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#ifdef __APPLE__
#include <mach/mach_time.h>
#endif

#include "ta_libc.h"
#include "test_data.h"
#include "bench_data.h"

/* Timing helpers */
static uint64_t now_ns(void) {
#ifdef __APPLE__
    static mach_timebase_info_data_t info = {0, 0};
    if (info.denom == 0) mach_timebase_info(&info);
    return mach_absolute_time() * info.numer / info.denom;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ULL + (uint64_t)ts.tv_nsec;
#endif
}

/* Print a double array as JSON */
static void print_double_array(const double *arr, int len) {
    printf("[");
    for (int i = 0; i < len; i++) {
        if (i > 0) printf(", ");
        printf("%.17g", arr[i]);
    }
    printf("]");
}

/* Run SMA */
static void run_sma(const double *inReal, int inLen,
                    int period, int startIdx, int endIdx, int *first) {
    double *outReal = (double *)calloc(inLen, sizeof(double));
    int outBegIdx = 0, outNBElement = 0;

    uint64_t t0 = now_ns();
    TA_RetCode rc = TA_SMA(startIdx, endIdx, inReal,
                           period, &outBegIdx, &outNBElement, outReal);
    uint64_t elapsed = now_ns() - t0;

    if (!*first) printf(",\n");
    *first = 0;

    printf("  {\"function\": \"SMA\", \"params\": {\"period\": %d, \"startIdx\": %d, \"endIdx\": %d, \"n\": %d}, ",
           period, startIdx, endIdx, inLen);
    printf("\"retCode\": %d, \"outBegIdx\": %d, \"outNBElement\": %d, \"output\": ",
           (int)rc, outBegIdx, outNBElement);
    print_double_array(outReal, outNBElement);
    printf(", \"elapsed_ns\": %llu}", (unsigned long long)elapsed);

    free(outReal);
}

/* Run RSI */
static void run_rsi(const double *inReal, int inLen,
                    int period, int startIdx, int endIdx, int *first) {
    double *outReal = (double *)calloc(inLen, sizeof(double));
    int outBegIdx = 0, outNBElement = 0;

    uint64_t t0 = now_ns();
    TA_RetCode rc = TA_RSI(startIdx, endIdx, inReal,
                           period, &outBegIdx, &outNBElement, outReal);
    uint64_t elapsed = now_ns() - t0;

    if (!*first) printf(",\n");
    *first = 0;

    printf("  {\"function\": \"RSI\", \"params\": {\"period\": %d, \"startIdx\": %d, \"endIdx\": %d, \"n\": %d}, ",
           period, startIdx, endIdx, inLen);
    printf("\"retCode\": %d, \"outBegIdx\": %d, \"outNBElement\": %d, \"output\": ",
           (int)rc, outBegIdx, outNBElement);
    print_double_array(outReal, outNBElement);
    printf(", \"elapsed_ns\": %llu}", (unsigned long long)elapsed);

    free(outReal);
}

/* Run MULT */
static void run_mult(const double *inReal0, const double *inReal1, int inLen,
                     int startIdx, int endIdx, int *first) {
    double *outReal = (double *)calloc(inLen, sizeof(double));
    int outBegIdx = 0, outNBElement = 0;

    uint64_t t0 = now_ns();
    TA_RetCode rc = TA_MULT(startIdx, endIdx, inReal0, inReal1,
                            &outBegIdx, &outNBElement, outReal);
    uint64_t elapsed = now_ns() - t0;

    if (!*first) printf(",\n");
    *first = 0;

    printf("  {\"function\": \"MULT\", \"params\": {\"startIdx\": %d, \"endIdx\": %d, \"n\": %d}, ",
           startIdx, endIdx, inLen);
    printf("\"retCode\": %d, \"outBegIdx\": %d, \"outNBElement\": %d, \"output\": ",
           (int)rc, outBegIdx, outNBElement);
    print_double_array(outReal, outNBElement);
    printf(", \"elapsed_ns\": %llu}", (unsigned long long)elapsed);

    free(outReal);
}

int main(void) {
    TA_RetCode rc = TA_Initialize();
    if (rc != TA_SUCCESS) {
        fprintf(stderr, "TA_Initialize failed: %d\n", (int)rc);
        return 1;
    }

    int first = 1;

    /* Warmup call to prime instruction cache / branch predictor */
    {
        double warmup_out[TEST_PRICES_LEN];
        int wb = 0, wn = 0;
        TA_SMA(0, TEST_PRICES_LEN - 1, TEST_PRICES, 5, &wb, &wn, warmup_out);
    }

    printf("[\n");

    /* === Small correctness tests (100 points) === */
    run_sma(TEST_PRICES, TEST_PRICES_LEN, 5,  0, TEST_PRICES_LEN - 1, &first);
    run_sma(TEST_PRICES, TEST_PRICES_LEN, 10, 0, TEST_PRICES_LEN - 1, &first);
    run_sma(TEST_PRICES, TEST_PRICES_LEN, 30, 0, TEST_PRICES_LEN - 1, &first);

    run_rsi(TEST_PRICES, TEST_PRICES_LEN, 14, 0, TEST_PRICES_LEN - 1, &first);
    run_rsi(TEST_PRICES, TEST_PRICES_LEN, 7,  0, TEST_PRICES_LEN - 1, &first);

    run_mult(TEST_PRICES, TEST_PRICES_2, TEST_PRICES_LEN, 0, TEST_PRICES_LEN - 1, &first);
    run_mult(TEST_PRICES, TEST_PRICES_2, TEST_PRICES_LEN, 10, 50, &first);

    /* === Benchmark tests (100k points) === */
    run_sma(BENCH_PRICES, BENCH_PRICES_LEN, 50,  0, BENCH_PRICES_LEN - 1, &first);
    run_sma(BENCH_PRICES, BENCH_PRICES_LEN, 200, 0, BENCH_PRICES_LEN - 1, &first);

    run_rsi(BENCH_PRICES, BENCH_PRICES_LEN, 14, 0, BENCH_PRICES_LEN - 1, &first);

    run_mult(BENCH_PRICES, BENCH_PRICES_2, BENCH_PRICES_LEN, 0, BENCH_PRICES_LEN - 1, &first);

    printf("\n]\n");

    TA_Shutdown();
    return 0;
}
