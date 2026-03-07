//! FFI wrappers for TA-Lib Rust implementations.
//!
//! This crate provides `extern "C"` functions that match the C TA-Lib API signatures,
//! allowing the Rust implementations to be linked into C binaries (e.g., ta_regtest).

#![allow(non_snake_case)]

use std::os::raw::{c_double, c_float, c_int};

use ta_lib::ta_func::{Core, RetCode};

/// Convert a Rust `RetCode` to the corresponding C `TA_RetCode` integer value.
///
/// The C and Rust enums have DIFFERENT discriminant values, so we must map explicitly.
fn retcode_to_c(rc: RetCode) -> c_int {
    match rc {
        RetCode::Success => 0,
        RetCode::BadParam => 2,
        RetCode::AllocErr => 3,
        RetCode::OutOfRangeStartIndex => 12,
        RetCode::OutOfRangeEndIndex => 13,
        RetCode::InternalError => 5000,
    }
}

// ---------------------------------------------------------------------------
// MULT
// ---------------------------------------------------------------------------

#[no_mangle]
pub unsafe extern "C" fn TA_MULT(
    startIdx: c_int,
    endIdx: c_int,
    inReal0: *const c_double,
    inReal1: *const c_double,
    outBegIdx: *mut c_int,
    outNBElement: *mut c_int,
    outReal: *mut c_double,
) -> c_int {
    let core = Core::new();
    let len = (endIdx + 1) as usize;
    let input0 = std::slice::from_raw_parts(inReal0, len);
    let input1 = std::slice::from_raw_parts(inReal1, len);
    let out = std::slice::from_raw_parts_mut(outReal, len);

    let mut beg: usize = 0;
    let mut nb: usize = 0;
    let rc = core.mult(startIdx as usize, endIdx as usize, input0, input1, &mut beg, &mut nb, out);

    *outBegIdx = beg as c_int;
    *outNBElement = nb as c_int;
    retcode_to_c(rc)
}

#[no_mangle]
pub unsafe extern "C" fn TA_S_MULT(
    startIdx: c_int,
    endIdx: c_int,
    inReal0: *const c_float,
    inReal1: *const c_float,
    outBegIdx: *mut c_int,
    outNBElement: *mut c_int,
    outReal: *mut c_double,
) -> c_int {
    let core = Core::new();
    let len = (endIdx + 1) as usize;
    let input0 = std::slice::from_raw_parts(inReal0, len);
    let input1 = std::slice::from_raw_parts(inReal1, len);
    let out = std::slice::from_raw_parts_mut(outReal, len);

    let mut beg: usize = 0;
    let mut nb: usize = 0;
    let rc = core.mult_s(startIdx as usize, endIdx as usize, input0, input1, &mut beg, &mut nb, out);

    *outBegIdx = beg as c_int;
    *outNBElement = nb as c_int;
    retcode_to_c(rc)
}

#[no_mangle]
pub unsafe extern "C" fn TA_MULT_Lookback() -> c_int {
    let core = Core::new();
    core.mult_lookback()
}

// ---------------------------------------------------------------------------
// SMA
// ---------------------------------------------------------------------------

#[no_mangle]
pub unsafe extern "C" fn TA_SMA(
    startIdx: c_int,
    endIdx: c_int,
    inReal: *const c_double,
    optInTimePeriod: c_int,
    outBegIdx: *mut c_int,
    outNBElement: *mut c_int,
    outReal: *mut c_double,
) -> c_int {
    let core = Core::new();
    let len = (endIdx + 1) as usize;
    let input = std::slice::from_raw_parts(inReal, len);
    let out = std::slice::from_raw_parts_mut(outReal, len);

    let mut beg: usize = 0;
    let mut nb: usize = 0;
    let rc = core.sma(startIdx as usize, endIdx as usize, input, optInTimePeriod, &mut beg, &mut nb, out);

    *outBegIdx = beg as c_int;
    *outNBElement = nb as c_int;
    retcode_to_c(rc)
}

#[no_mangle]
pub unsafe extern "C" fn TA_S_SMA(
    startIdx: c_int,
    endIdx: c_int,
    inReal: *const c_float,
    optInTimePeriod: c_int,
    outBegIdx: *mut c_int,
    outNBElement: *mut c_int,
    outReal: *mut c_double,
) -> c_int {
    let core = Core::new();
    let len = (endIdx + 1) as usize;
    let input = std::slice::from_raw_parts(inReal, len);
    let out = std::slice::from_raw_parts_mut(outReal, len);

    let mut beg: usize = 0;
    let mut nb: usize = 0;
    let rc = core.sma_s(startIdx as usize, endIdx as usize, input, optInTimePeriod, &mut beg, &mut nb, out);

    *outBegIdx = beg as c_int;
    *outNBElement = nb as c_int;
    retcode_to_c(rc)
}

#[no_mangle]
pub unsafe extern "C" fn TA_SMA_Lookback(optInTimePeriod: c_int) -> c_int {
    let core = Core::new();
    core.sma_lookback(optInTimePeriod)
}

// ---------------------------------------------------------------------------
// RSI
// ---------------------------------------------------------------------------

#[no_mangle]
pub unsafe extern "C" fn TA_RSI(
    startIdx: c_int,
    endIdx: c_int,
    inReal: *const c_double,
    optInTimePeriod: c_int,
    outBegIdx: *mut c_int,
    outNBElement: *mut c_int,
    outReal: *mut c_double,
) -> c_int {
    let core = Core::new();
    let len = (endIdx + 1) as usize;
    let input = std::slice::from_raw_parts(inReal, len);
    let out = std::slice::from_raw_parts_mut(outReal, len);

    let mut beg: usize = 0;
    let mut nb: usize = 0;
    let rc = core.rsi(startIdx as usize, endIdx as usize, input, optInTimePeriod, &mut beg, &mut nb, out);

    *outBegIdx = beg as c_int;
    *outNBElement = nb as c_int;
    retcode_to_c(rc)
}

#[no_mangle]
pub unsafe extern "C" fn TA_S_RSI(
    startIdx: c_int,
    endIdx: c_int,
    inReal: *const c_float,
    optInTimePeriod: c_int,
    outBegIdx: *mut c_int,
    outNBElement: *mut c_int,
    outReal: *mut c_double,
) -> c_int {
    let core = Core::new();
    let len = (endIdx + 1) as usize;
    let input = std::slice::from_raw_parts(inReal, len);
    let out = std::slice::from_raw_parts_mut(outReal, len);

    let mut beg: usize = 0;
    let mut nb: usize = 0;
    let rc = core.rsi_s(startIdx as usize, endIdx as usize, input, optInTimePeriod, &mut beg, &mut nb, out);

    *outBegIdx = beg as c_int;
    *outNBElement = nb as c_int;
    retcode_to_c(rc)
}

#[no_mangle]
pub unsafe extern "C" fn TA_RSI_Lookback(optInTimePeriod: c_int) -> c_int {
    let core = Core::new();
    core.rsi_lookback(optInTimePeriod)
}
