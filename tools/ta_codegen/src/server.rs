use serde_json::{json, Value};
use std::io::{self, BufRead, Write};
use ta_lib::ta_func::{Core, RetCode};

pub fn run_server() {
    let core = Core::new();
    let stdin = io::stdin();
    let stdout = io::stdout();
    let mut stdout = stdout.lock();

    for line in stdin.lock().lines() {
        let line = line.unwrap();
        if line.trim().is_empty() {
            continue;
        }

        let request: Value = match serde_json::from_str(&line) {
            Ok(v) => v,
            Err(e) => {
                let resp = json!({"error": format!("Parse error: {}", e)});
                writeln!(stdout, "{}", serde_json::to_string(&resp).unwrap()).unwrap();
                stdout.flush().unwrap();
                continue;
            }
        };

        let method = match request["method"].as_str() {
            Some(m) => m,
            None => {
                let resp = json!({"error": "Missing 'method' field"});
                writeln!(stdout, "{}", serde_json::to_string(&resp).unwrap()).unwrap();
                stdout.flush().unwrap();
                continue;
            }
        };
        let params = &request["params"];

        let response = match method {
            "TA_MULT" => handle_mult(&core, params),
            "TA_MULT_Lookback" => handle_mult_lookback(&core),
            "TA_SMA" => handle_sma(&core, params),
            "TA_SMA_Lookback" => handle_sma_lookback(&core, params),
            "TA_RSI" => handle_rsi(&core, params),
            "TA_RSI_Lookback" => handle_rsi_lookback(&core, params),
            // EMA not yet in ta-lib Rust crate — uncomment when available:
            // "TA_EMA" => handle_ema(&core, params),
            // "TA_EMA_Lookback" => handle_ema_lookback(&core, params),
            _ => json!({"error": format!("Unknown method: {}", method)}),
        };

        writeln!(stdout, "{}", serde_json::to_string(&response).unwrap()).unwrap();
        stdout.flush().unwrap();
    }
}

fn handle_mult(core: &Core, params: &Value) -> Value {
    let start_idx = params["startIdx"].as_i64().unwrap() as usize;
    let end_idx = params["endIdx"].as_i64().unwrap() as usize;
    let in_real0: Vec<f64> = params["inReal0"]
        .as_array()
        .unwrap()
        .iter()
        .map(|v| v.as_f64().unwrap())
        .collect();
    let in_real1: Vec<f64> = params["inReal1"]
        .as_array()
        .unwrap()
        .iter()
        .map(|v| v.as_f64().unwrap())
        .collect();

    let mut out_real = vec![0.0f64; end_idx - start_idx + 1];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    let rc = core.mult(
        start_idx,
        end_idx,
        &in_real0,
        &in_real1,
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut out_real,
    );

    out_real.truncate(out_nb_element);

    json!({
        "retCode": retcode_to_int(rc),
        "outBegIdx": out_beg_idx,
        "outNBElement": out_nb_element,
        "outReal": out_real,
    })
}

fn handle_mult_lookback(core: &Core) -> Value {
    json!({"lookback": core.mult_lookback()})
}

fn handle_sma(core: &Core, params: &Value) -> Value {
    let start_idx = params["startIdx"].as_i64().unwrap() as usize;
    let end_idx = params["endIdx"].as_i64().unwrap() as usize;
    let in_real: Vec<f64> = params["inReal"]
        .as_array()
        .unwrap()
        .iter()
        .map(|v| v.as_f64().unwrap())
        .collect();
    let opt_in_time_period = params["optInTimePeriod"].as_i64().unwrap() as i32;

    let mut out_real = vec![0.0f64; end_idx - start_idx + 1];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    let rc = core.sma(
        start_idx,
        end_idx,
        &in_real,
        opt_in_time_period,
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut out_real,
    );

    out_real.truncate(out_nb_element);

    json!({
        "retCode": retcode_to_int(rc),
        "outBegIdx": out_beg_idx,
        "outNBElement": out_nb_element,
        "outReal": out_real,
    })
}

fn handle_sma_lookback(core: &Core, params: &Value) -> Value {
    let opt_in_time_period = params["optInTimePeriod"].as_i64().unwrap_or(30) as i32;
    json!({"lookback": core.sma_lookback(opt_in_time_period)})
}

fn handle_rsi(core: &Core, params: &Value) -> Value {
    let start_idx = params["startIdx"].as_i64().unwrap() as usize;
    let end_idx = params["endIdx"].as_i64().unwrap() as usize;
    let in_real: Vec<f64> = params["inReal"]
        .as_array()
        .unwrap()
        .iter()
        .map(|v| v.as_f64().unwrap())
        .collect();
    let opt_in_time_period = params["optInTimePeriod"].as_i64().unwrap() as i32;

    let mut out_real = vec![0.0f64; end_idx - start_idx + 1];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    let rc = core.rsi(
        start_idx,
        end_idx,
        &in_real,
        opt_in_time_period,
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut out_real,
    );

    out_real.truncate(out_nb_element);

    json!({
        "retCode": retcode_to_int(rc),
        "outBegIdx": out_beg_idx,
        "outNBElement": out_nb_element,
        "outReal": out_real,
    })
}

fn handle_rsi_lookback(core: &Core, params: &Value) -> Value {
    let opt_in_time_period = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
    json!({"lookback": core.rsi_lookback(opt_in_time_period)})
}

fn retcode_to_int(rc: RetCode) -> i32 {
    match rc {
        RetCode::Success => 0,
        RetCode::BadParam => 2,
        RetCode::OutOfRangeStartIndex => 12,
        RetCode::OutOfRangeEndIndex => 13,
        RetCode::AllocErr => 3,
        RetCode::InternalError => 5000,
    }
}
