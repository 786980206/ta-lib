use ta_lib::ta_func::{Core, RetCode};

#[test]
fn test_sma_basic() {
    // Test data: 5 values
    let input: [f64; 5] = [1.0, 2.0, 3.0, 4.0, 5.0];
    let mut out_real = [0.0f64; 5];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    // SMA with period 3
    let result = Core::sma(
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
    // Test data: 5 values as f32
    let input: [f32; 5] = [1.0, 2.0, 3.0, 4.0, 5.0];
    let mut out_real = [0.0f64; 5];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    // SMA with period 3
    let result = Core::sma_s(
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
    assert_eq!(Core::sma_lookback(3), 2); // period-1
    assert_eq!(Core::sma_lookback(10), 9);
    assert_eq!(Core::sma_lookback(1), -1); // period 1 is below min (2), returns -1
    assert_eq!(Core::sma_lookback(30), 29); // default value case: TA_INTEGER_DEFAULT resolves to 30
}

#[test]
fn test_sma_period_1() {
    // SMA with period 1 should just return the input values
    let input: [f64; 5] = [1.0, 2.0, 3.0, 4.0, 5.0];
    let mut out_real = [0.0f64; 5];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    let result = Core::sma(
        0,
        4,
        &input,
        1,
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut out_real,
    );

    assert_eq!(result, RetCode::Success);
    assert_eq!(out_beg_idx, 0);
    assert_eq!(out_nb_element, 5);

    for i in 0..5 {
        assert!((out_real[i] - input[i]).abs() < 1e-10);
    }
}

#[test]
fn test_sma_partial_range() {
    let input: [f64; 10] = [1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0];
    let mut out_real = [0.0f64; 10];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    // Calculate SMA only from index 3 to 7
    let result = Core::sma(
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
