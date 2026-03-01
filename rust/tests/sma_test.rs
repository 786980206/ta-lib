use ta_lib::ta_func::{Core, RetCode};

#[test]
fn test_sma_basic() {
    let core = Core::new();
    // Test data: 5 values
    let input: [f64; 5] = [1.0, 2.0, 3.0, 4.0, 5.0];
    let mut out_real = [0.0f64; 5];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    // SMA with period 3
    let result = core.sma(
        0, // startIdx
        4, // endIdx (last index)
        &input,
        3, // optInTimePeriod
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut out_real,
    );

    assert_eq!(result, RetCode::Success);
    assert_eq!(out_beg_idx, 2); // lookback is period-1 = 2
    assert_eq!(out_nb_element, 3); // 3 output values

    // SMA(1,2,3) = 2.0
    // SMA(2,3,4) = 3.0
    // SMA(3,4,5) = 4.0
    assert!((out_real[0] - 2.0).abs() < 1e-10);
    assert!((out_real[1] - 3.0).abs() < 1e-10);
    assert!((out_real[2] - 4.0).abs() < 1e-10);
}

#[test]
fn test_sma_single_precision() {
    let core = Core::new();
    // Test data: 5 values as f32
    let input: [f32; 5] = [1.0, 2.0, 3.0, 4.0, 5.0];
    let mut out_real = [0.0f64; 5];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    // SMA with period 3
    let result = core.sma_s(
        0, // startIdx
        4, // endIdx (last index)
        &input,
        3, // optInTimePeriod
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut out_real,
    );

    assert_eq!(result, RetCode::Success);
    assert_eq!(out_beg_idx, 2);
    assert_eq!(out_nb_element, 3);

    assert!((out_real[0] - 2.0).abs() < 1e-10);
    assert!((out_real[1] - 3.0).abs() < 1e-10);
    assert!((out_real[2] - 4.0).abs() < 1e-10);
}

#[test]
fn test_sma_lookback() {
    let core = Core::new();
    assert_eq!(core.sma_lookback(3), 2); // period-1
    assert_eq!(core.sma_lookback(10), 9);
    assert_eq!(core.sma_lookback(1), -1); // period 1 is below min (2), returns -1
    assert_eq!(core.sma_lookback(30), 29); // default value case: TA_INTEGER_DEFAULT resolves to 30
}

#[test]
fn test_sma_minimum_period() {
    let core = Core::new();
    // SMA with period 2 (the minimum valid period)
    let input: [f64; 5] = [1.0, 2.0, 3.0, 4.0, 5.0];
    let mut out_real = [0.0f64; 5];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    let result = core.sma(
        0,
        4,
        &input,
        2,
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut out_real,
    );

    assert_eq!(result, RetCode::Success);
    assert_eq!(out_beg_idx, 1); // lookback = period-1 = 1
    assert_eq!(out_nb_element, 4);

    // SMA(1,2)/2 = 1.5, SMA(2,3)/2 = 2.5, SMA(3,4)/2 = 3.5, SMA(4,5)/2 = 4.5
    assert!((out_real[0] - 1.5).abs() < 1e-10);
    assert!((out_real[1] - 2.5).abs() < 1e-10);
    assert!((out_real[2] - 3.5).abs() < 1e-10);
    assert!((out_real[3] - 4.5).abs() < 1e-10);
}

#[test]
fn test_sma_error_conditions() {
    let core = Core::new();
    let input: [f64; 5] = [1.0, 2.0, 3.0, 4.0, 5.0];
    let mut out_real = [0.0f64; 5];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    // Period 1 is below minimum (2) — should return BadParam
    let result = core.sma(
        0,
        4,
        &input,
        1,
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut out_real,
    );
    assert_eq!(result, RetCode::BadParam);

    // Period 0 is below minimum — should return BadParam
    let result = core.sma(
        0,
        4,
        &input,
        0,
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut out_real,
    );
    assert_eq!(result, RetCode::BadParam);

    // Period 100001 is above maximum (100000) — should return BadParam
    let result = core.sma(
        0,
        4,
        &input,
        100001,
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut out_real,
    );
    assert_eq!(result, RetCode::BadParam);

    // endIdx < startIdx — should return OutOfRangeEndIndex
    let result = core.sma(
        4,
        0,
        &input,
        3,
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut out_real,
    );
    assert_eq!(result, RetCode::OutOfRangeEndIndex);

    // i32::MIN should use default period (30) — with enough data, returns Success
    let large_input = [1.0f64; 50];
    let mut large_out = [0.0f64; 50];
    let result = core.sma(
        0,
        49,
        &large_input,
        i32::MIN,
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut large_out,
    );
    assert_eq!(result, RetCode::Success);
    assert_eq!(out_beg_idx, 29); // default period 30, lookback = 29
}

#[test]
fn test_sma_s_error_conditions() {
    let core = Core::new();
    let input: [f32; 5] = [1.0, 2.0, 3.0, 4.0, 5.0];
    let mut out_real = [0.0f64; 5];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    // Period below minimum — should return BadParam
    let result = core.sma_s(
        0,
        4,
        &input,
        1,
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut out_real,
    );
    assert_eq!(result, RetCode::BadParam);

    // i32::MIN should use default period (30)
    let large_input = [1.0f32; 50];
    let mut large_out = [0.0f64; 50];
    let result = core.sma_s(
        0,
        49,
        &large_input,
        i32::MIN,
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut large_out,
    );
    assert_eq!(result, RetCode::Success);
    assert_eq!(out_beg_idx, 29);
}

#[test]
fn test_sma_partial_range() {
    let core = Core::new();
    let input: [f64; 10] = [1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0];
    let mut out_real = [0.0f64; 10];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    // Calculate SMA only from index 3 to 7
    let result = core.sma(
        3, // startIdx
        7, // endIdx
        &input,
        3, // optInTimePeriod
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut out_real,
    );

    assert_eq!(result, RetCode::Success);
    assert_eq!(out_beg_idx, 3); // starts at 3 (meets lookback requirement)
    assert_eq!(out_nb_element, 5); // 5 values from index 3 to 7

    // SMA at index 3: (2+3+4)/3 = 3.0
    // SMA at index 4: (3+4+5)/3 = 4.0
    // etc.
    assert!((out_real[0] - 3.0).abs() < 1e-10);
    assert!((out_real[1] - 4.0).abs() < 1e-10);
    assert!((out_real[2] - 5.0).abs() < 1e-10);
    assert!((out_real[3] - 6.0).abs() < 1e-10);
    assert!((out_real[4] - 7.0).abs() < 1e-10);
}
