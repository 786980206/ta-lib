mod bench_data;
mod test_data;

use std::time::Instant;
use ta_lib::{Core, RetCode};

fn retcode_to_int(rc: RetCode) -> i32 {
    match rc {
        RetCode::Success => 0,
        RetCode::BadParam => 2,
        RetCode::OutOfRangeStartIndex => 13,
        RetCode::OutOfRangeEndIndex => 14,
        RetCode::AllocErr => 3,
        RetCode::InternalError => 5000,
    }
}

fn print_array(arr: &[f64]) {
    print!("[");
    for (i, v) in arr.iter().enumerate() {
        if i > 0 {
            print!(", ");
        }
        print!("{:.17e}", v);
    }
    print!("]");
}

fn print_comma(first: &mut bool) {
    if !*first {
        print!(",\n");
    }
    *first = false;
}

fn run_sma(core: &Core, in_real: &[f64], period: i32, start_idx: usize, end_idx: usize, first: &mut bool) {
    let mut out_real = vec![0.0_f64; in_real.len()];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    let t0 = Instant::now();
    let rc = core.sma(
        start_idx, end_idx, in_real,
        period, &mut out_beg_idx, &mut out_nb_element, &mut out_real,
    );
    let elapsed = t0.elapsed().as_nanos();

    print_comma(first);
    print!(
        "  {{\"function\": \"SMA\", \"params\": {{\"period\": {}, \"startIdx\": {}, \"endIdx\": {}, \"n\": {}}}, ",
        period, start_idx, end_idx, in_real.len()
    );
    print!(
        "\"retCode\": {}, \"outBegIdx\": {}, \"outNBElement\": {}, \"output\": ",
        retcode_to_int(rc), out_beg_idx, out_nb_element
    );
    print_array(&out_real[..out_nb_element]);
    print!(", \"elapsed_ns\": {}}}", elapsed);
}

fn run_rsi(core: &Core, in_real: &[f64], period: i32, start_idx: usize, end_idx: usize, first: &mut bool) {
    let mut out_real = vec![0.0_f64; in_real.len()];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    let t0 = Instant::now();
    let rc = core.rsi(
        start_idx, end_idx, in_real,
        period, &mut out_beg_idx, &mut out_nb_element, &mut out_real,
    );
    let elapsed = t0.elapsed().as_nanos();

    print_comma(first);
    print!(
        "  {{\"function\": \"RSI\", \"params\": {{\"period\": {}, \"startIdx\": {}, \"endIdx\": {}, \"n\": {}}}, ",
        period, start_idx, end_idx, in_real.len()
    );
    print!(
        "\"retCode\": {}, \"outBegIdx\": {}, \"outNBElement\": {}, \"output\": ",
        retcode_to_int(rc), out_beg_idx, out_nb_element
    );
    print_array(&out_real[..out_nb_element]);
    print!(", \"elapsed_ns\": {}}}", elapsed);
}

fn run_mult(core: &Core, in_real0: &[f64], in_real1: &[f64], start_idx: usize, end_idx: usize, first: &mut bool) {
    let mut out_real = vec![0.0_f64; in_real0.len()];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    let t0 = Instant::now();
    let rc = core.mult(
        start_idx, end_idx, in_real0, in_real1,
        &mut out_beg_idx, &mut out_nb_element, &mut out_real,
    );
    let elapsed = t0.elapsed().as_nanos();

    print_comma(first);
    print!(
        "  {{\"function\": \"MULT\", \"params\": {{\"startIdx\": {}, \"endIdx\": {}, \"n\": {}}}, ",
        start_idx, end_idx, in_real0.len()
    );
    print!(
        "\"retCode\": {}, \"outBegIdx\": {}, \"outNBElement\": {}, \"output\": ",
        retcode_to_int(rc), out_beg_idx, out_nb_element
    );
    print_array(&out_real[..out_nb_element]);
    print!(", \"elapsed_ns\": {}}}", elapsed);
}

fn main() {
    let core = Core::new();
    let mut first = true;
    let end_idx = test_data::TEST_PRICES.len() - 1;

    // Warmup call to prime instruction cache / branch predictor
    {
        let mut out = vec![0.0_f64; test_data::TEST_PRICES.len()];
        let mut beg: usize = 0;
        let mut nb: usize = 0;
        let _ = core.sma(0, end_idx, &test_data::TEST_PRICES, 5, &mut beg, &mut nb, &mut out);
    }

    println!("[");

    // === Small correctness tests (100 points) ===

    run_sma(&core, &test_data::TEST_PRICES, 5, 0, end_idx, &mut first);
    run_sma(&core, &test_data::TEST_PRICES, 10, 0, end_idx, &mut first);
    run_sma(&core, &test_data::TEST_PRICES, 30, 0, end_idx, &mut first);

    run_rsi(&core, &test_data::TEST_PRICES, 14, 0, end_idx, &mut first);
    run_rsi(&core, &test_data::TEST_PRICES, 7, 0, end_idx, &mut first);

    run_mult(&core, &test_data::TEST_PRICES, &test_data::TEST_PRICES_2, 0, end_idx, &mut first);
    run_mult(&core, &test_data::TEST_PRICES, &test_data::TEST_PRICES_2, 10, 50, &mut first);

    // === Benchmark tests (100k points) ===
    let bench_end = bench_data::BENCH_PRICES.len() - 1;

    run_sma(&core, &bench_data::BENCH_PRICES, 50, 0, bench_end, &mut first);
    run_sma(&core, &bench_data::BENCH_PRICES, 200, 0, bench_end, &mut first);

    run_rsi(&core, &bench_data::BENCH_PRICES, 14, 0, bench_end, &mut first);

    run_mult(&core, &bench_data::BENCH_PRICES, &bench_data::BENCH_PRICES_2, 0, bench_end, &mut first);

    println!("\n]");
}
