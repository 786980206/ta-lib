use ta_lib::ta_func::{Compatibility, Core, FuncUnstId, RetCode};

#[test]
fn test_rsi_lookback() {
    let core = Core::new();

    // Default period (i32::MIN) should resolve to 14
    assert_eq!(core.rsi_lookback(i32::MIN), 14);

    // Explicit period 14
    assert_eq!(core.rsi_lookback(14), 14);

    // Period 30
    assert_eq!(core.rsi_lookback(30), 30);

    // Period below minimum (1) should return -1
    assert_eq!(core.rsi_lookback(1), -1);
}

#[test]
fn test_rsi_lookback_unstable_period() {
    let mut core = Core::new();
    core.set_unstable_period(FuncUnstId::Rsi, 10);

    // Lookback for period 14 should be 14 + 10 = 24
    assert_eq!(core.rsi_lookback(14), 24);
}

#[test]
fn test_rsi_lookback_metastock() {
    let mut core = Core::new();
    core.set_compatibility(Compatibility::Metastock);

    // Lookback for period 14 should be 14 - 1 = 13 in Metastock mode
    assert_eq!(core.rsi_lookback(14), 13);
}

#[test]
fn test_rsi_basic() {
    let core = Core::new();

    let input: Vec<f64> = vec![
        44.0, 44.34, 44.09, 43.61, 44.33, 44.83, 44.32, 44.55, 43.93, 44.05, 43.80, 43.64,
        43.82, 44.29, 44.09, 44.15, 43.61, 44.33, 44.83, 44.32, 44.55, 43.93, 44.05, 43.80,
        43.64, 43.82, 44.29, 44.09, 44.15, 43.61,
    ];

    let mut out_real = vec![0.0_f64; input.len()];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    let result = core.rsi(
        0,
        input.len() - 1,
        &input,
        14,
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut out_real,
    );

    assert_eq!(result, RetCode::Success);
    assert_eq!(out_beg_idx, 14);
    assert!(out_nb_element > 0);

    // All RSI values should be in valid range [0, 100]
    for i in 0..out_nb_element {
        assert!(
            out_real[i] >= 0.0 && out_real[i] <= 100.0,
            "RSI value out of range at index {}: {}",
            i,
            out_real[i]
        );
    }
}

#[test]
fn test_rsi_all_same_prices() {
    let core = Core::new();

    let input = vec![50.0_f64; 30];
    let mut out_real = vec![0.0_f64; 30];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    let result = core.rsi(
        0,
        input.len() - 1,
        &input,
        14,
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut out_real,
    );

    assert_eq!(result, RetCode::Success);
    assert!(out_nb_element > 0);

    // No gain or loss → TA_IS_ZERO triggers → RSI = 0.0
    for i in 0..out_nb_element {
        assert!(
            (out_real[i] - 0.0).abs() < 1e-10,
            "Expected RSI 0.0 for flat prices at index {}, got {}",
            i,
            out_real[i]
        );
    }
}

#[test]
fn test_rsi_all_ascending() {
    let core = Core::new();

    let input: Vec<f64> = (0..30).map(|i| 40.0 + i as f64).collect();
    let mut out_real = vec![0.0_f64; 30];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    let result = core.rsi(
        0,
        input.len() - 1,
        &input,
        14,
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut out_real,
    );

    assert_eq!(result, RetCode::Success);
    assert!(out_nb_element > 0);

    // All gains, no losses → RSI should be 100.0
    for i in 0..out_nb_element {
        assert!(
            (out_real[i] - 100.0).abs() < 1e-10,
            "Expected RSI 100.0 for ascending prices at index {}, got {}",
            i,
            out_real[i]
        );
    }
}

#[test]
fn test_rsi_all_descending() {
    let core = Core::new();

    let input: Vec<f64> = (0..30).map(|i| 70.0 - i as f64).collect();
    let mut out_real = vec![0.0_f64; 30];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    let result = core.rsi(
        0,
        input.len() - 1,
        &input,
        14,
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut out_real,
    );

    assert_eq!(result, RetCode::Success);
    assert!(out_nb_element > 0);

    // All losses, no gains → RSI should be 0.0
    for i in 0..out_nb_element {
        assert!(
            (out_real[i] - 0.0).abs() < 1e-10,
            "Expected RSI 0.0 for descending prices at index {}, got {}",
            i,
            out_real[i]
        );
    }
}

#[test]
fn test_rsi_single_precision() {
    let core = Core::new();

    let input_f64: Vec<f64> = vec![
        44.0, 44.34, 44.09, 43.61, 44.33, 44.83, 44.32, 44.55, 43.93, 44.05, 43.80, 43.64,
        43.82, 44.29, 44.09, 44.15, 43.61, 44.33, 44.83, 44.32, 44.55, 43.93, 44.05, 43.80,
        43.64, 43.82, 44.29, 44.09, 44.15, 43.61,
    ];
    let input_f32: Vec<f32> = input_f64.iter().map(|&v| v as f32).collect();

    let mut out_f64 = vec![0.0_f64; input_f64.len()];
    let mut out_f32 = vec![0.0_f64; input_f32.len()];
    let mut beg_f64: usize = 0;
    let mut beg_f32: usize = 0;
    let mut nb_f64: usize = 0;
    let mut nb_f32: usize = 0;

    let result_f64 = core.rsi(
        0,
        input_f64.len() - 1,
        &input_f64,
        14,
        &mut beg_f64,
        &mut nb_f64,
        &mut out_f64,
    );

    let result_f32 = core.rsi_s(
        0,
        input_f32.len() - 1,
        &input_f32,
        14,
        &mut beg_f32,
        &mut nb_f32,
        &mut out_f32,
    );

    assert_eq!(result_f64, RetCode::Success);
    assert_eq!(result_f32, RetCode::Success);
    assert_eq!(beg_f64, beg_f32);
    assert_eq!(nb_f64, nb_f32);

    // Single precision results should be close to double precision
    let epsilon = 1e-4;
    for i in 0..nb_f64 {
        assert!(
            (out_f64[i] - out_f32[i]).abs() < epsilon,
            "Single/double precision mismatch at index {}: f64={}, f32={}",
            i,
            out_f64[i],
            out_f32[i]
        );
    }
}

#[test]
fn test_rsi_period_1() {
    let core = Core::new();

    let input: Vec<f64> = vec![1.0, 2.0, 3.0, 4.0, 5.0];
    let mut out_real = vec![0.0_f64; 5];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    // Period 1 is below the minimum valid range (2..=100000) — should return BadParam
    let result = core.rsi(
        0,
        input.len() - 1,
        &input,
        1,
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut out_real,
    );

    assert_eq!(result, RetCode::BadParam);
}

#[test]
fn test_rsi_error_conditions() {
    let core = Core::new();
    let input = vec![50.0_f64; 30];
    let mut out_real = vec![0.0_f64; 30];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    // Period 0 → BadParam
    let result = core.rsi(
        0,
        input.len() - 1,
        &input,
        0,
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut out_real,
    );
    assert_eq!(result, RetCode::BadParam);

    // Period 1 → BadParam (minimum is 2)
    let result = core.rsi(
        0,
        input.len() - 1,
        &input,
        1,
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut out_real,
    );
    assert_eq!(result, RetCode::BadParam);

    // Period 100001 → BadParam (maximum is 100000)
    let result = core.rsi(
        0,
        input.len() - 1,
        &input,
        100001,
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut out_real,
    );
    assert_eq!(result, RetCode::BadParam);

    // endIdx < startIdx → OutOfRangeEndIndex
    let result = core.rsi(
        10,
        5,
        &input,
        14,
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut out_real,
    );
    assert_eq!(result, RetCode::OutOfRangeEndIndex);
}

#[test]
fn test_rsi_default_period() {
    let core = Core::new();

    // i32::MIN should use default period 14
    assert_eq!(core.rsi_lookback(i32::MIN), 14);

    // Verify the function also works with i32::MIN as period
    let input = vec![50.0_f64; 30];
    let mut out_real = vec![0.0_f64; 30];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    let result = core.rsi(
        0,
        input.len() - 1,
        &input,
        i32::MIN,
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut out_real,
    );

    assert_eq!(result, RetCode::Success);
    assert_eq!(out_beg_idx, 14); // default period 14, lookback = 14
}

#[test]
fn test_rsi_partial_range() {
    let core = Core::new();

    let input: Vec<f64> = vec![
        44.0, 44.34, 44.09, 43.61, 44.33, 44.83, 44.32, 44.55, 43.93, 44.05, 43.80, 43.64,
        43.82, 44.29, 44.09, 44.15, 43.61, 44.33, 44.83, 44.32, 44.55, 43.93, 44.05, 43.80,
        43.64, 43.82, 44.29, 44.09, 44.15, 43.61,
    ];

    let mut out_real = vec![0.0_f64; input.len()];
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;

    // Partial range: startIdx = 20, endIdx = 28
    let result = core.rsi(
        20,
        28,
        &input,
        14,
        &mut out_beg_idx,
        &mut out_nb_element,
        &mut out_real,
    );

    assert_eq!(result, RetCode::Success);
    // startIdx 20 > lookback 14, so out_beg_idx should be 20
    assert_eq!(out_beg_idx, 20);
    assert!(out_nb_element > 0);
    assert_eq!(out_nb_element, 9); // indices 20 through 28 inclusive

    // All RSI values should be in valid range
    for i in 0..out_nb_element {
        assert!(
            out_real[i] >= 0.0 && out_real[i] <= 100.0,
            "RSI value out of range at index {}: {}",
            i,
            out_real[i]
        );
    }
}

#[test]
fn test_rsi_unstable_period_behavior() {
    // Without unstable period
    let core_stable = Core::new();

    let input: Vec<f64> = vec![
        44.0, 44.34, 44.09, 43.61, 44.33, 44.83, 44.32, 44.55, 43.93, 44.05, 43.80, 43.64,
        43.82, 44.29, 44.09, 44.15, 43.61, 44.33, 44.83, 44.32, 44.55, 43.93, 44.05, 43.80,
        43.64, 43.82, 44.29, 44.09, 44.15, 43.61,
    ];

    let mut out_stable = vec![0.0_f64; input.len()];
    let mut beg_stable: usize = 0;
    let mut nb_stable: usize = 0;

    let result_stable = core_stable.rsi(
        0,
        input.len() - 1,
        &input,
        14,
        &mut beg_stable,
        &mut nb_stable,
        &mut out_stable,
    );
    assert_eq!(result_stable, RetCode::Success);
    assert_eq!(beg_stable, 14); // period 14, no unstable period

    // With unstable period of 5
    let mut core_unstable = Core::new();
    core_unstable.set_unstable_period(FuncUnstId::Rsi, 5);

    let mut out_unstable = vec![0.0_f64; input.len()];
    let mut beg_unstable: usize = 0;
    let mut nb_unstable: usize = 0;

    let result_unstable = core_unstable.rsi(
        0,
        input.len() - 1,
        &input,
        14,
        &mut beg_unstable,
        &mut nb_unstable,
        &mut out_unstable,
    );
    assert_eq!(result_unstable, RetCode::Success);

    // out_beg_idx should be period + unstable = 14 + 5 = 19
    assert_eq!(beg_unstable, 19);

    // Fewer output elements because of larger lookback
    assert!(nb_unstable < nb_stable);
    assert_eq!(nb_unstable, nb_stable - 5);

    // All unstable RSI values should still be in valid range
    for i in 0..nb_unstable {
        assert!(
            out_unstable[i] >= 0.0 && out_unstable[i] <= 100.0,
            "RSI value out of range at index {}: {}",
            i,
            out_unstable[i]
        );
    }
}
