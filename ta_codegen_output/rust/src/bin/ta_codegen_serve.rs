#![allow(non_snake_case, unused_variables, clippy::all)]

use serde_json::{self, Value};
use std::io::{self, BufRead, Write};
use std::time::Instant;
use ta_lib::{Core, RetCode, FuncUnstId, Compatibility, TaFloat};

fn parse_f64_array(val: &Value) -> Vec<f64> {
    match val.as_array() {
        Some(arr) => arr.iter().filter_map(|v| v.as_f64()).collect(),
        None => Vec::new(),
    }
}

fn retcode_to_int(rc: RetCode) -> i32 {
    match rc {
        RetCode::Success => 0,
        RetCode::BadParam => 2,
        RetCode::AllocErr => 3,
        RetCode::InternalError => 5000,
        RetCode::OutOfRangeStartIndex => 12,
        RetCode::OutOfRangeEndIndex => 13,
    }
}

fn func_unst_id_from_int(id: usize) -> Option<FuncUnstId> {
    match id {
        0 => Some(FuncUnstId::Adx),
        1 => Some(FuncUnstId::Adxr),
        2 => Some(FuncUnstId::Atr),
        3 => Some(FuncUnstId::Cmo),
        4 => Some(FuncUnstId::Dx),
        5 => Some(FuncUnstId::Ema),
        6 => Some(FuncUnstId::HtDcPeriod),
        7 => Some(FuncUnstId::HtDcPhase),
        8 => Some(FuncUnstId::HtPhasor),
        9 => Some(FuncUnstId::HtSine),
        10 => Some(FuncUnstId::HtTrendline),
        11 => Some(FuncUnstId::HtTrendMode),
        12 => Some(FuncUnstId::Imi),
        13 => Some(FuncUnstId::Kama),
        14 => Some(FuncUnstId::Mama),
        15 => Some(FuncUnstId::Mfi),
        16 => Some(FuncUnstId::MinusDI),
        17 => Some(FuncUnstId::MinusDM),
        18 => Some(FuncUnstId::Natr),
        19 => Some(FuncUnstId::PlusDI),
        20 => Some(FuncUnstId::PlusDM),
        21 => Some(FuncUnstId::Rsi),
        22 => Some(FuncUnstId::StochRsi),
        23 => Some(FuncUnstId::T3),
        _ => None,
    }
}

fn handle_request(core: &mut Core, line: &str) -> String {
    let req: Value = match serde_json::from_str(line) {
        Ok(v) => v,
        Err(e) => return format!("{{\"error\":\"Parse error: {}\"}}", e),
    };
    let method = match req["method"].as_str() {
        Some(m) => m,
        None => return "{\"error\":\"Missing method field\"}".to_string(),
    };
    let params = &req["params"];

    match method {
        "TA_ACCBANDS" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(20) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBuf1: Vec<f64> = vec![0.0f64; out_size];
            let mut outBuf2: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.accbands::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                &inClose,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0, &mut outBuf1, &mut outBuf2,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp["outReal1"] = serde_json::json!(&outBuf1[..outNBElement]);
            resp["outReal2"] = serde_json::json!(&outBuf2[..outNBElement]);
            resp.to_string()
        }
        "TA_ACOS" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.acos::<f64>(
                startIdx, endIdx,
                &inReal,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_AD" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let inVolume: Vec<f64> = parse_f64_array(&params["inVolume"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.ad::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                &inClose,
                &inVolume,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_ADD" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal0: Vec<f64> = parse_f64_array(&params["inReal0"]);
            let inReal1: Vec<f64> = parse_f64_array(&params["inReal1"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.add::<f64>(
                startIdx, endIdx,
                &inReal0,
                &inReal1,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_ADOSC" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let inVolume: Vec<f64> = parse_f64_array(&params["inVolume"]);
            let optInFastPeriod = params["optInFastPeriod"].as_i64().unwrap_or(3) as i32;
            let optInSlowPeriod = params["optInSlowPeriod"].as_i64().unwrap_or(10) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.adosc::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                &inClose,
                &inVolume,
                optInFastPeriod,
                optInSlowPeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_ADX" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            if let Some(period) = params["unstablePeriod"].as_i64() {
                core.unstable_period[0] = period as i32;
            }
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.adx::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                &inClose,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_ADXR" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            if let Some(period) = params["unstablePeriod"].as_i64() {
                core.unstable_period[1] = period as i32;
            }
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.adxr::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                &inClose,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_APO" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInFastPeriod = params["optInFastPeriod"].as_i64().unwrap_or(12) as i32;
            let optInSlowPeriod = params["optInSlowPeriod"].as_i64().unwrap_or(26) as i32;
            let optInMAType = params["optInMAType"].as_i64().unwrap_or(0) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.apo::<f64>(
                startIdx, endIdx,
                &inReal,
                optInFastPeriod,
                optInSlowPeriod,
                optInMAType,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_AROON" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBuf1: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.aroon::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0, &mut outBuf1,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp["outReal1"] = serde_json::json!(&outBuf1[..outNBElement]);
            resp.to_string()
        }
        "TA_AROONOSC" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.aroonosc::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_ASIN" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.asin::<f64>(
                startIdx, endIdx,
                &inReal,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_ATAN" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.atan::<f64>(
                startIdx, endIdx,
                &inReal,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_ATR" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            if let Some(period) = params["unstablePeriod"].as_i64() {
                core.unstable_period[2] = period as i32;
            }
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.atr::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                &inClose,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_AVGDEV" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.avgdev::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_AVGPRICE" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.avgprice::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_BBANDS" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(5) as i32;
            let optInNbDevUp = params["optInNbDevUp"].as_f64().unwrap_or(2.0) as f64;
            let optInNbDevDn = params["optInNbDevDn"].as_f64().unwrap_or(2.0) as f64;
            let optInMAType = params["optInMAType"].as_i64().unwrap_or(0) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBuf1: Vec<f64> = vec![0.0f64; out_size];
            let mut outBuf2: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.bbands::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                optInNbDevUp,
                optInNbDevDn,
                optInMAType,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0, &mut outBuf1, &mut outBuf2,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp["outReal1"] = serde_json::json!(&outBuf1[..outNBElement]);
            resp["outReal2"] = serde_json::json!(&outBuf2[..outNBElement]);
            resp.to_string()
        }
        "TA_BETA" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal0: Vec<f64> = parse_f64_array(&params["inReal0"]);
            let inReal1: Vec<f64> = parse_f64_array(&params["inReal1"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(5) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.beta::<f64>(
                startIdx, endIdx,
                &inReal0,
                &inReal1,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_BOP" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.bop::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CCI" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cci::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                &inClose,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDL2CROWS" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdl2crows::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDL3BLACKCROWS" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdl3blackcrows::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDL3INSIDE" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdl3inside::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDL3LINESTRIKE" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdl3linestrike::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDL3OUTSIDE" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdl3outside::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDL3STARSINSOUTH" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdl3starsinsouth::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDL3WHITESOLDIERS" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdl3whitesoldiers::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLABANDONEDBABY" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let optInPenetration = params["optInPenetration"].as_f64().unwrap_or(0.3) as f64;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlabandonedbaby::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                optInPenetration,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLADVANCEBLOCK" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdladvanceblock::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLBELTHOLD" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlbelthold::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLBREAKAWAY" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlbreakaway::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLCLOSINGMARUBOZU" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlclosingmarubozu::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLCONCEALBABYSWALL" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlconcealbabyswall::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLCOUNTERATTACK" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlcounterattack::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLDARKCLOUDCOVER" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let optInPenetration = params["optInPenetration"].as_f64().unwrap_or(0.5) as f64;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdldarkcloudcover::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                optInPenetration,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLDOJI" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdldoji::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLDOJISTAR" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdldojistar::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLDRAGONFLYDOJI" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdldragonflydoji::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLENGULFING" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlengulfing::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLEVENINGDOJISTAR" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let optInPenetration = params["optInPenetration"].as_f64().unwrap_or(0.3) as f64;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdleveningdojistar::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                optInPenetration,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLEVENINGSTAR" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let optInPenetration = params["optInPenetration"].as_f64().unwrap_or(0.3) as f64;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdleveningstar::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                optInPenetration,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLGAPSIDESIDEWHITE" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlgapsidesidewhite::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLGRAVESTONEDOJI" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlgravestonedoji::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLHAMMER" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlhammer::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLHANGINGMAN" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlhangingman::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLHARAMI" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlharami::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLHARAMICROSS" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlharamicross::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLHIGHWAVE" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlhighwave::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLHIKKAKE" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlhikkake::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLHIKKAKEMOD" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlhikkakemod::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLHOMINGPIGEON" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlhomingpigeon::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLIDENTICAL3CROWS" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlidentical3crows::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLINNECK" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlinneck::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLINVERTEDHAMMER" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlinvertedhammer::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLKICKING" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlkicking::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLKICKINGBYLENGTH" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlkickingbylength::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLLADDERBOTTOM" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlladderbottom::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLLONGLEGGEDDOJI" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdllongleggeddoji::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLLONGLINE" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdllongline::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLMARUBOZU" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlmarubozu::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLMATCHINGLOW" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlmatchinglow::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLMATHOLD" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let optInPenetration = params["optInPenetration"].as_f64().unwrap_or(0.5) as f64;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlmathold::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                optInPenetration,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLMORNINGDOJISTAR" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let optInPenetration = params["optInPenetration"].as_f64().unwrap_or(0.3) as f64;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlmorningdojistar::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                optInPenetration,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLMORNINGSTAR" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let optInPenetration = params["optInPenetration"].as_f64().unwrap_or(0.3) as f64;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlmorningstar::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                optInPenetration,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLONNECK" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlonneck::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLPIERCING" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlpiercing::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLRICKSHAWMAN" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlrickshawman::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLRISEFALL3METHODS" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlrisefall3methods::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLSEPARATINGLINES" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlseparatinglines::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLSHOOTINGSTAR" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlshootingstar::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLSHORTLINE" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlshortline::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLSPINNINGTOP" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlspinningtop::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLSTALLEDPATTERN" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlstalledpattern::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLSTICKSANDWICH" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlsticksandwich::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLTAKURI" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdltakuri::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLTASUKIGAP" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdltasukigap::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLTHRUSTING" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlthrusting::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLTRISTAR" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdltristar::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLUNIQUE3RIVER" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlunique3river::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLUPSIDEGAP2CROWS" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlupsidegap2crows::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CDLXSIDEGAP3METHODS" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cdlxsidegap3methods::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CEIL" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.ceil::<f64>(
                startIdx, endIdx,
                &inReal,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CMO" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            if let Some(period) = params["unstablePeriod"].as_i64() {
                core.unstable_period[3] = period as i32;
            }
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cmo::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_CORREL" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal0: Vec<f64> = parse_f64_array(&params["inReal0"]);
            let inReal1: Vec<f64> = parse_f64_array(&params["inReal1"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(30) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.correl::<f64>(
                startIdx, endIdx,
                &inReal0,
                &inReal1,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_COS" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cos::<f64>(
                startIdx, endIdx,
                &inReal,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_COSH" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.cosh::<f64>(
                startIdx, endIdx,
                &inReal,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_DEMA" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(30) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.dema::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_DIV" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal0: Vec<f64> = parse_f64_array(&params["inReal0"]);
            let inReal1: Vec<f64> = parse_f64_array(&params["inReal1"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.div::<f64>(
                startIdx, endIdx,
                &inReal0,
                &inReal1,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_DX" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            if let Some(period) = params["unstablePeriod"].as_i64() {
                core.unstable_period[4] = period as i32;
            }
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.dx::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                &inClose,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_EMA" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(30) as i32;
            if let Some(period) = params["unstablePeriod"].as_i64() {
                core.unstable_period[5] = period as i32;
            }
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.ema::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_EXP" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.exp::<f64>(
                startIdx, endIdx,
                &inReal,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_FLOOR" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.floor::<f64>(
                startIdx, endIdx,
                &inReal,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_HT_DCPERIOD" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            if let Some(period) = params["unstablePeriod"].as_i64() {
                core.unstable_period[6] = period as i32;
            }
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.ht_dcperiod::<f64>(
                startIdx, endIdx,
                &inReal,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_HT_DCPHASE" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            if let Some(period) = params["unstablePeriod"].as_i64() {
                core.unstable_period[7] = period as i32;
            }
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.ht_dcphase::<f64>(
                startIdx, endIdx,
                &inReal,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_HT_PHASOR" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            if let Some(period) = params["unstablePeriod"].as_i64() {
                core.unstable_period[8] = period as i32;
            }
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBuf1: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.ht_phasor::<f64>(
                startIdx, endIdx,
                &inReal,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0, &mut outBuf1,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp["outReal1"] = serde_json::json!(&outBuf1[..outNBElement]);
            resp.to_string()
        }
        "TA_HT_SINE" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            if let Some(period) = params["unstablePeriod"].as_i64() {
                core.unstable_period[9] = period as i32;
            }
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBuf1: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.ht_sine::<f64>(
                startIdx, endIdx,
                &inReal,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0, &mut outBuf1,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp["outReal1"] = serde_json::json!(&outBuf1[..outNBElement]);
            resp.to_string()
        }
        "TA_HT_TRENDLINE" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            if let Some(period) = params["unstablePeriod"].as_i64() {
                core.unstable_period[10] = period as i32;
            }
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.ht_trendline::<f64>(
                startIdx, endIdx,
                &inReal,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_HT_TRENDMODE" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            if let Some(period) = params["unstablePeriod"].as_i64() {
                core.unstable_period[11] = period as i32;
            }
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.ht_trendmode::<f64>(
                startIdx, endIdx,
                &inReal,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_IMI" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inOpen: Vec<f64> = parse_f64_array(&params["inOpen"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            if let Some(period) = params["unstablePeriod"].as_i64() {
                core.unstable_period[12] = period as i32;
            }
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.imi::<f64>(
                startIdx, endIdx,
                &inOpen,
                &inClose,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_KAMA" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(30) as i32;
            if let Some(period) = params["unstablePeriod"].as_i64() {
                core.unstable_period[13] = period as i32;
            }
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.kama::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_LINEARREG" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.linearreg::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_LINEARREG_ANGLE" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.linearreg_angle::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_LINEARREG_INTERCEPT" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.linearreg_intercept::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_LINEARREG_SLOPE" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.linearreg_slope::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_LN" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.ln::<f64>(
                startIdx, endIdx,
                &inReal,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_LOG10" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.log10::<f64>(
                startIdx, endIdx,
                &inReal,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_MA" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(30) as i32;
            let optInMAType = params["optInMAType"].as_i64().unwrap_or(0) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.ma::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                optInMAType,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_MACD" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInFastPeriod = params["optInFastPeriod"].as_i64().unwrap_or(12) as i32;
            let optInSlowPeriod = params["optInSlowPeriod"].as_i64().unwrap_or(26) as i32;
            let optInSignalPeriod = params["optInSignalPeriod"].as_i64().unwrap_or(9) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBuf1: Vec<f64> = vec![0.0f64; out_size];
            let mut outBuf2: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.macd::<f64>(
                startIdx, endIdx,
                &inReal,
                optInFastPeriod,
                optInSlowPeriod,
                optInSignalPeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0, &mut outBuf1, &mut outBuf2,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp["outReal1"] = serde_json::json!(&outBuf1[..outNBElement]);
            resp["outReal2"] = serde_json::json!(&outBuf2[..outNBElement]);
            resp.to_string()
        }
        "TA_MACDEXT" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInFastPeriod = params["optInFastPeriod"].as_i64().unwrap_or(12) as i32;
            let optInFastMAType = params["optInFastMAType"].as_i64().unwrap_or(0) as i32;
            let optInSlowPeriod = params["optInSlowPeriod"].as_i64().unwrap_or(26) as i32;
            let optInSlowMAType = params["optInSlowMAType"].as_i64().unwrap_or(0) as i32;
            let optInSignalPeriod = params["optInSignalPeriod"].as_i64().unwrap_or(9) as i32;
            let optInSignalMAType = params["optInSignalMAType"].as_i64().unwrap_or(0) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBuf1: Vec<f64> = vec![0.0f64; out_size];
            let mut outBuf2: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.macdext::<f64>(
                startIdx, endIdx,
                &inReal,
                optInFastPeriod,
                optInFastMAType,
                optInSlowPeriod,
                optInSlowMAType,
                optInSignalPeriod,
                optInSignalMAType,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0, &mut outBuf1, &mut outBuf2,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp["outReal1"] = serde_json::json!(&outBuf1[..outNBElement]);
            resp["outReal2"] = serde_json::json!(&outBuf2[..outNBElement]);
            resp.to_string()
        }
        "TA_MACDFIX" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInSignalPeriod = params["optInSignalPeriod"].as_i64().unwrap_or(9) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBuf1: Vec<f64> = vec![0.0f64; out_size];
            let mut outBuf2: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.macdfix::<f64>(
                startIdx, endIdx,
                &inReal,
                optInSignalPeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0, &mut outBuf1, &mut outBuf2,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp["outReal1"] = serde_json::json!(&outBuf1[..outNBElement]);
            resp["outReal2"] = serde_json::json!(&outBuf2[..outNBElement]);
            resp.to_string()
        }
        "TA_MAMA" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInFastLimit = params["optInFastLimit"].as_f64().unwrap_or(0.5) as f64;
            let optInSlowLimit = params["optInSlowLimit"].as_f64().unwrap_or(0.05) as f64;
            if let Some(period) = params["unstablePeriod"].as_i64() {
                core.unstable_period[14] = period as i32;
            }
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBuf1: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.mama::<f64>(
                startIdx, endIdx,
                &inReal,
                optInFastLimit,
                optInSlowLimit,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0, &mut outBuf1,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp["outReal1"] = serde_json::json!(&outBuf1[..outNBElement]);
            resp.to_string()
        }
        "TA_MAVP" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal0: Vec<f64> = parse_f64_array(&params["inReal0"]);
            let inReal1: Vec<f64> = parse_f64_array(&params["inReal1"]);
            let optInMinPeriod = params["optInMinPeriod"].as_i64().unwrap_or(2) as i32;
            let optInMaxPeriod = params["optInMaxPeriod"].as_i64().unwrap_or(30) as i32;
            let optInMAType = params["optInMAType"].as_i64().unwrap_or(0) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.mavp::<f64>(
                startIdx, endIdx,
                &inReal0,
                &inReal1,
                optInMinPeriod,
                optInMaxPeriod,
                optInMAType,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_MAX" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(30) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.max::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_MAXINDEX" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(30) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.maxindex::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_MEDPRICE" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.medprice::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_MFI" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let inVolume: Vec<f64> = parse_f64_array(&params["inVolume"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            if let Some(period) = params["unstablePeriod"].as_i64() {
                core.unstable_period[15] = period as i32;
            }
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.mfi::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                &inClose,
                &inVolume,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_MIDPOINT" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.midpoint::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_MIDPRICE" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.midprice::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_MIN" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(30) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.min::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_MININDEX" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(30) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.minindex::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_MINMAX" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(30) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBuf1: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.minmax::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0, &mut outBuf1,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp["outReal1"] = serde_json::json!(&outBuf1[..outNBElement]);
            resp.to_string()
        }
        "TA_MINMAXINDEX" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(30) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outIntBuf0: Vec<i32> = vec![0i32; out_size];
            let mut outIntBuf1: Vec<i32> = vec![0i32; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.minmaxindex::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outIntBuf0, &mut outIntBuf1,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outInteger"] = serde_json::json!(&outIntBuf0[..outNBElement]);
            resp["outInteger1"] = serde_json::json!(&outIntBuf1[..outNBElement]);
            resp.to_string()
        }
        "TA_MINUS_DI" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            if let Some(period) = params["unstablePeriod"].as_i64() {
                core.unstable_period[16] = period as i32;
            }
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.minus_di::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                &inClose,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_MINUS_DM" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            if let Some(period) = params["unstablePeriod"].as_i64() {
                core.unstable_period[17] = period as i32;
            }
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.minus_dm::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_MOM" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(10) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.mom::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_MULT" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal0: Vec<f64> = parse_f64_array(&params["inReal0"]);
            let inReal1: Vec<f64> = parse_f64_array(&params["inReal1"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.mult::<f64>(
                startIdx, endIdx,
                &inReal0,
                &inReal1,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_NATR" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            if let Some(period) = params["unstablePeriod"].as_i64() {
                core.unstable_period[18] = period as i32;
            }
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.natr::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                &inClose,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_NVI" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let inVolume: Vec<f64> = parse_f64_array(&params["inVolume"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.nvi::<f64>(
                startIdx, endIdx,
                &inClose,
                &inVolume,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_OBV" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let inVolume: Vec<f64> = parse_f64_array(&params["inVolume"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.obv::<f64>(
                startIdx, endIdx,
                &inReal,
                &inVolume,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_PLUS_DI" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            if let Some(period) = params["unstablePeriod"].as_i64() {
                core.unstable_period[19] = period as i32;
            }
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.plus_di::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                &inClose,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_PLUS_DM" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            if let Some(period) = params["unstablePeriod"].as_i64() {
                core.unstable_period[20] = period as i32;
            }
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.plus_dm::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_PPO" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInFastPeriod = params["optInFastPeriod"].as_i64().unwrap_or(12) as i32;
            let optInSlowPeriod = params["optInSlowPeriod"].as_i64().unwrap_or(26) as i32;
            let optInMAType = params["optInMAType"].as_i64().unwrap_or(0) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.ppo::<f64>(
                startIdx, endIdx,
                &inReal,
                optInFastPeriod,
                optInSlowPeriod,
                optInMAType,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_PVI" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let inVolume: Vec<f64> = parse_f64_array(&params["inVolume"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.pvi::<f64>(
                startIdx, endIdx,
                &inClose,
                &inVolume,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_ROC" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(10) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.roc::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_ROCP" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(10) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.rocp::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_ROCR" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(10) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.rocr::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_ROCR100" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(10) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.rocr100::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_RSI" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            if let Some(period) = params["unstablePeriod"].as_i64() {
                core.unstable_period[21] = period as i32;
            }
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.rsi::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_SAR" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let optInAcceleration = params["optInAcceleration"].as_f64().unwrap_or(0.02) as f64;
            let optInMaximum = params["optInMaximum"].as_f64().unwrap_or(0.2) as f64;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.sar::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                optInAcceleration,
                optInMaximum,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_SAREXT" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let optInStartValue = params["optInStartValue"].as_f64().unwrap_or(0.0) as f64;
            let optInOffsetOnReverse = params["optInOffsetOnReverse"].as_f64().unwrap_or(0.0) as f64;
            let optInAccelerationInitLong = params["optInAccelerationInitLong"].as_f64().unwrap_or(0.02) as f64;
            let optInAccelerationLong = params["optInAccelerationLong"].as_f64().unwrap_or(0.02) as f64;
            let optInAccelerationMaxLong = params["optInAccelerationMaxLong"].as_f64().unwrap_or(0.2) as f64;
            let optInAccelerationInitShort = params["optInAccelerationInitShort"].as_f64().unwrap_or(0.02) as f64;
            let optInAccelerationShort = params["optInAccelerationShort"].as_f64().unwrap_or(0.02) as f64;
            let optInAccelerationMaxShort = params["optInAccelerationMaxShort"].as_f64().unwrap_or(0.2) as f64;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.sarext::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                optInStartValue,
                optInOffsetOnReverse,
                optInAccelerationInitLong,
                optInAccelerationLong,
                optInAccelerationMaxLong,
                optInAccelerationInitShort,
                optInAccelerationShort,
                optInAccelerationMaxShort,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_SIN" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.sin::<f64>(
                startIdx, endIdx,
                &inReal,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_SINH" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.sinh::<f64>(
                startIdx, endIdx,
                &inReal,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_SMA" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(30) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.sma::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_SQRT" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.sqrt::<f64>(
                startIdx, endIdx,
                &inReal,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_STDDEV" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(5) as i32;
            let optInNbDev = params["optInNbDev"].as_f64().unwrap_or(1.0) as f64;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.stddev::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                optInNbDev,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_STOCH" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let optInFastK_Period = params["optInFastK_Period"].as_i64().unwrap_or(5) as i32;
            let optInSlowK_Period = params["optInSlowK_Period"].as_i64().unwrap_or(3) as i32;
            let optInSlowK_MAType = params["optInSlowK_MAType"].as_i64().unwrap_or(0) as i32;
            let optInSlowD_Period = params["optInSlowD_Period"].as_i64().unwrap_or(3) as i32;
            let optInSlowD_MAType = params["optInSlowD_MAType"].as_i64().unwrap_or(0) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBuf1: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.stoch::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                &inClose,
                optInFastK_Period,
                optInSlowK_Period,
                optInSlowK_MAType,
                optInSlowD_Period,
                optInSlowD_MAType,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0, &mut outBuf1,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp["outReal1"] = serde_json::json!(&outBuf1[..outNBElement]);
            resp.to_string()
        }
        "TA_STOCHF" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let optInFastK_Period = params["optInFastK_Period"].as_i64().unwrap_or(5) as i32;
            let optInFastD_Period = params["optInFastD_Period"].as_i64().unwrap_or(3) as i32;
            let optInFastD_MAType = params["optInFastD_MAType"].as_i64().unwrap_or(0) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBuf1: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.stochf::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                &inClose,
                optInFastK_Period,
                optInFastD_Period,
                optInFastD_MAType,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0, &mut outBuf1,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp["outReal1"] = serde_json::json!(&outBuf1[..outNBElement]);
            resp.to_string()
        }
        "TA_STOCHRSI" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            let optInFastK_Period = params["optInFastK_Period"].as_i64().unwrap_or(5) as i32;
            let optInFastD_Period = params["optInFastD_Period"].as_i64().unwrap_or(3) as i32;
            let optInFastD_MAType = params["optInFastD_MAType"].as_i64().unwrap_or(0) as i32;
            if let Some(period) = params["unstablePeriod"].as_i64() {
                core.unstable_period[22] = period as i32;
            }
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBuf1: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.stochrsi::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                optInFastK_Period,
                optInFastD_Period,
                optInFastD_MAType,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0, &mut outBuf1,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp["outReal1"] = serde_json::json!(&outBuf1[..outNBElement]);
            resp.to_string()
        }
        "TA_SUB" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal0: Vec<f64> = parse_f64_array(&params["inReal0"]);
            let inReal1: Vec<f64> = parse_f64_array(&params["inReal1"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.sub::<f64>(
                startIdx, endIdx,
                &inReal0,
                &inReal1,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_SUM" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(30) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.sum::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_T3" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(5) as i32;
            let optInVFactor = params["optInVFactor"].as_f64().unwrap_or(0.7) as f64;
            if let Some(period) = params["unstablePeriod"].as_i64() {
                core.unstable_period[23] = period as i32;
            }
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.t3::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                optInVFactor,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_TAN" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.tan::<f64>(
                startIdx, endIdx,
                &inReal,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_TANH" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.tanh::<f64>(
                startIdx, endIdx,
                &inReal,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_TEMA" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(30) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.tema::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_TRANGE" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.trange::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_TRIMA" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(30) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.trima::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_TRIX" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(30) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.trix::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_TSF" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.tsf::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_TYPPRICE" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.typprice::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_ULTOSC" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let optInTimePeriod1 = params["optInTimePeriod1"].as_i64().unwrap_or(7) as i32;
            let optInTimePeriod2 = params["optInTimePeriod2"].as_i64().unwrap_or(14) as i32;
            let optInTimePeriod3 = params["optInTimePeriod3"].as_i64().unwrap_or(28) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.ultosc::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                &inClose,
                optInTimePeriod1,
                optInTimePeriod2,
                optInTimePeriod3,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_VAR" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(5) as i32;
            let optInNbDev = params["optInNbDev"].as_f64().unwrap_or(1.0) as f64;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.var::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                optInNbDev,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_WCLPRICE" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.wclprice::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                &inClose,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_WILLR" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inHigh: Vec<f64> = parse_f64_array(&params["inHigh"]);
            let inLow: Vec<f64> = parse_f64_array(&params["inLow"]);
            let inClose: Vec<f64> = parse_f64_array(&params["inClose"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(14) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.willr::<f64>(
                startIdx, endIdx,
                &inHigh,
                &inLow,
                &inClose,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "TA_WMA" => {
            let startIdx = params["startIdx"].as_u64().unwrap_or(0) as usize;
            let endIdx = params["endIdx"].as_u64().unwrap_or(0) as usize;
            let inReal: Vec<f64> = parse_f64_array(&params["inReal"]);
            let optInTimePeriod = params["optInTimePeriod"].as_i64().unwrap_or(30) as i32;
            let out_size = if endIdx >= startIdx { endIdx - startIdx + 1 } else { 0 };
            let mut outBuf0: Vec<f64> = vec![0.0f64; out_size];
            let mut outBegIdx: usize = 0;
            let mut outNBElement: usize = 0;
            let start_time = Instant::now();
            let rc = core.wma::<f64>(
                startIdx, endIdx,
                &inReal,
                optInTimePeriod,
                &mut outBegIdx, &mut outNBElement, &mut outBuf0,
            );
            let elapsed_ns = start_time.elapsed().as_nanos() as u64;
            let mut resp = serde_json::json!({
                "retCode": retcode_to_int(rc),
                "outBegIdx": outBegIdx,
                "outNBElement": outNBElement,
                "timing_ns": elapsed_ns,
            });
            resp["outReal"] = serde_json::json!(&outBuf0[..outNBElement]);
            resp.to_string()
        }
        "list_functions" => {
            let funcs: Vec<&str> = vec![
                "TA_ACCBANDS",
                "TA_ACOS",
                "TA_AD",
                "TA_ADD",
                "TA_ADOSC",
                "TA_ADX",
                "TA_ADXR",
                "TA_APO",
                "TA_AROON",
                "TA_AROONOSC",
                "TA_ASIN",
                "TA_ATAN",
                "TA_ATR",
                "TA_AVGDEV",
                "TA_AVGPRICE",
                "TA_BBANDS",
                "TA_BETA",
                "TA_BOP",
                "TA_CCI",
                "TA_CDL2CROWS",
                "TA_CDL3BLACKCROWS",
                "TA_CDL3INSIDE",
                "TA_CDL3LINESTRIKE",
                "TA_CDL3OUTSIDE",
                "TA_CDL3STARSINSOUTH",
                "TA_CDL3WHITESOLDIERS",
                "TA_CDLABANDONEDBABY",
                "TA_CDLADVANCEBLOCK",
                "TA_CDLBELTHOLD",
                "TA_CDLBREAKAWAY",
                "TA_CDLCLOSINGMARUBOZU",
                "TA_CDLCONCEALBABYSWALL",
                "TA_CDLCOUNTERATTACK",
                "TA_CDLDARKCLOUDCOVER",
                "TA_CDLDOJI",
                "TA_CDLDOJISTAR",
                "TA_CDLDRAGONFLYDOJI",
                "TA_CDLENGULFING",
                "TA_CDLEVENINGDOJISTAR",
                "TA_CDLEVENINGSTAR",
                "TA_CDLGAPSIDESIDEWHITE",
                "TA_CDLGRAVESTONEDOJI",
                "TA_CDLHAMMER",
                "TA_CDLHANGINGMAN",
                "TA_CDLHARAMI",
                "TA_CDLHARAMICROSS",
                "TA_CDLHIGHWAVE",
                "TA_CDLHIKKAKE",
                "TA_CDLHIKKAKEMOD",
                "TA_CDLHOMINGPIGEON",
                "TA_CDLIDENTICAL3CROWS",
                "TA_CDLINNECK",
                "TA_CDLINVERTEDHAMMER",
                "TA_CDLKICKING",
                "TA_CDLKICKINGBYLENGTH",
                "TA_CDLLADDERBOTTOM",
                "TA_CDLLONGLEGGEDDOJI",
                "TA_CDLLONGLINE",
                "TA_CDLMARUBOZU",
                "TA_CDLMATCHINGLOW",
                "TA_CDLMATHOLD",
                "TA_CDLMORNINGDOJISTAR",
                "TA_CDLMORNINGSTAR",
                "TA_CDLONNECK",
                "TA_CDLPIERCING",
                "TA_CDLRICKSHAWMAN",
                "TA_CDLRISEFALL3METHODS",
                "TA_CDLSEPARATINGLINES",
                "TA_CDLSHOOTINGSTAR",
                "TA_CDLSHORTLINE",
                "TA_CDLSPINNINGTOP",
                "TA_CDLSTALLEDPATTERN",
                "TA_CDLSTICKSANDWICH",
                "TA_CDLTAKURI",
                "TA_CDLTASUKIGAP",
                "TA_CDLTHRUSTING",
                "TA_CDLTRISTAR",
                "TA_CDLUNIQUE3RIVER",
                "TA_CDLUPSIDEGAP2CROWS",
                "TA_CDLXSIDEGAP3METHODS",
                "TA_CEIL",
                "TA_CMO",
                "TA_CORREL",
                "TA_COS",
                "TA_COSH",
                "TA_DEMA",
                "TA_DIV",
                "TA_DX",
                "TA_EMA",
                "TA_EXP",
                "TA_FLOOR",
                "TA_HT_DCPERIOD",
                "TA_HT_DCPHASE",
                "TA_HT_PHASOR",
                "TA_HT_SINE",
                "TA_HT_TRENDLINE",
                "TA_HT_TRENDMODE",
                "TA_IMI",
                "TA_KAMA",
                "TA_LINEARREG",
                "TA_LINEARREG_ANGLE",
                "TA_LINEARREG_INTERCEPT",
                "TA_LINEARREG_SLOPE",
                "TA_LN",
                "TA_LOG10",
                "TA_MA",
                "TA_MACD",
                "TA_MACDEXT",
                "TA_MACDFIX",
                "TA_MAMA",
                "TA_MAVP",
                "TA_MAX",
                "TA_MAXINDEX",
                "TA_MEDPRICE",
                "TA_MFI",
                "TA_MIDPOINT",
                "TA_MIDPRICE",
                "TA_MIN",
                "TA_MININDEX",
                "TA_MINMAX",
                "TA_MINMAXINDEX",
                "TA_MINUS_DI",
                "TA_MINUS_DM",
                "TA_MOM",
                "TA_MULT",
                "TA_NATR",
                "TA_NVI",
                "TA_OBV",
                "TA_PLUS_DI",
                "TA_PLUS_DM",
                "TA_PPO",
                "TA_PVI",
                "TA_ROC",
                "TA_ROCP",
                "TA_ROCR",
                "TA_ROCR100",
                "TA_RSI",
                "TA_SAR",
                "TA_SAREXT",
                "TA_SIN",
                "TA_SINH",
                "TA_SMA",
                "TA_SQRT",
                "TA_STDDEV",
                "TA_STOCH",
                "TA_STOCHF",
                "TA_STOCHRSI",
                "TA_SUB",
                "TA_SUM",
                "TA_T3",
                "TA_TAN",
                "TA_TANH",
                "TA_TEMA",
                "TA_TRANGE",
                "TA_TRIMA",
                "TA_TRIX",
                "TA_TSF",
                "TA_TYPPRICE",
                "TA_ULTOSC",
                "TA_VAR",
                "TA_WCLPRICE",
                "TA_WILLR",
                "TA_WMA",
            ];
            serde_json::json!({ "functions": funcs }).to_string()
        }
        "set_unstable_period" => {
            let id = params["id"].as_u64().unwrap_or(99) as usize;
            let period = params["period"].as_i64().unwrap_or(0) as i32;
            if id < FuncUnstId::FuncUnstAll as usize {
                core.unstable_period[id] = period;
                "{\"status\":\"ok\"}".to_string()
            } else {
                "{\"error\":\"Invalid unstable period id\"}".to_string()
            }
        }
        "set_compatibility" => {
            let mode = params["mode"].as_u64().unwrap_or(0);
            core.compatibility = match mode {
                1 => Compatibility::Metastock,
                _ => Compatibility::Default,
            };
            "{\"status\":\"ok\"}".to_string()
        }
        _ => {
            format!("{{\"error\":\"Unknown method: {}\"}}", method)
        }
    }
}

fn main() {
    let mut core = Core::new();
    let stdin = io::stdin();
    let stdout = io::stdout();
    let mut stdout = stdout.lock();
    for line in stdin.lock().lines() {
        let line = match line {
            Ok(l) => l,
            Err(_) => break,
        };
        let line = line.trim();
        if line.is_empty() {
            continue;
        }
        let resp = handle_request(&mut core, line);
        writeln!(stdout, "{}", resp).ok();
        stdout.flush().ok();
    }
}
