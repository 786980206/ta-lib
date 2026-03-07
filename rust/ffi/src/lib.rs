//! FFI wrappers for TA-Lib Rust implementations.
//!
//! This crate provides `extern "C"` functions that match the C TA-Lib API signatures,
//! allowing the Rust implementations to be linked into C binaries (e.g., ta_regtest).
//!
//! Global state (unstable periods, compatibility mode) is managed by the C library.
//! Each wrapper reads the current state from C globals and applies it to a local
//! `Core` before calling the Rust implementation.

#![allow(non_snake_case)]

use std::os::raw::{c_double, c_float, c_int, c_uint};

use ta_lib::ta_func::{Compatibility, Core, FuncUnstId, RetCode};

// ---------------------------------------------------------------------------
// C global state accessors (defined in ta_utility.c / ta_global.c)
// These are resolved from ta-lib-static at link time.
// ---------------------------------------------------------------------------
extern "C" {
    fn TA_GetUnstablePeriod(id: c_int) -> c_uint;
    fn TA_GetCompatibility() -> c_int;
}

/// Build a Core instance whose state mirrors the C globals.
///
/// Reads all unstable periods and the compatibility mode from the C library
/// so the Rust implementations produce results consistent with the C state.
fn core_from_c_globals() -> Core {
    let mut core = Core::new();

    // Sync all unstable periods from C globals
    let all = FuncUnstId::FuncUnstAll as usize;
    for i in 0..all {
        let period = unsafe { TA_GetUnstablePeriod(i as c_int) };
        core.unstable_period[i] = period as i32;
    }

    // Sync compatibility mode
    let compat = unsafe { TA_GetCompatibility() };
    core.compatibility = if compat == 0 {
        Compatibility::Default
    } else {
        Compatibility::Metastock
    };

    core
}

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
    let core = core_from_c_globals();
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
    let core = core_from_c_globals();
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
    let core = core_from_c_globals();
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
    let core = core_from_c_globals();
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
    let core = core_from_c_globals();
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
    let core = core_from_c_globals();
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
    let core = core_from_c_globals();
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
    let core = core_from_c_globals();
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
    let core = core_from_c_globals();
    core.rsi_lookback(optInTimePeriod)
}
