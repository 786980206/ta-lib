use ta_lib::ta_func::TaFloat;

#[test]
fn test_f64_constants() {
    assert_eq!(f64::ta_zero(), 0.0);
    assert_eq!(f64::ta_one(), 1.0);
    assert!(f64::ta_epsilon() > 0.0);
    assert!(f64::ta_epsilon() < 1e-10);
}

#[test]
fn test_f32_constants() {
    assert_eq!(f32::ta_zero(), 0.0f32);
    assert_eq!(f32::ta_one(), 1.0f32);
    assert!(f32::ta_epsilon() > 0.0f32);
}

#[test]
fn test_f64_conversions() {
    assert_eq!(f64::ta_from_f64(3.14), 3.14_f64);
    assert_eq!(f64::ta_from_i32(42), 42.0_f64);
    assert_eq!(3.14_f64.ta_to_f64(), 3.14);
}

#[test]
fn test_f32_conversions() {
    let v: f32 = f32::ta_from_f64(3.14);
    assert!((v - 3.14_f32).abs() < 1e-6);
    assert_eq!(f32::ta_from_i32(42), 42.0_f32);
    assert!((42.0_f32.ta_to_f64() - 42.0).abs() < 1e-10);
}

#[test]
fn test_f64_math_ops() {
    assert_eq!(4.0_f64.ta_sqrt(), 2.0);
    assert_eq!((-3.5_f64).ta_abs(), 3.5);
    assert_eq!(2.3_f64.ta_ceil(), 3.0);
    assert_eq!(2.7_f64.ta_floor(), 2.0);
    assert_eq!(2.5_f64.ta_round(), 3.0);
}

#[test]
fn test_f32_math_ops() {
    assert_eq!(4.0_f32.ta_sqrt(), 2.0_f32);
    assert_eq!((-3.5_f32).ta_abs(), 3.5_f32);
    assert_eq!(2.3_f32.ta_ceil(), 3.0_f32);
    assert_eq!(2.7_f32.ta_floor(), 2.0_f32);
    assert_eq!(2.5_f32.ta_round(), 3.0_f32);
}

#[test]
fn test_f64_trig() {
    let pi = std::f64::consts::PI;
    assert!((pi.ta_sin()).abs() < 1e-15);
    assert!((0.0_f64.ta_cos() - 1.0).abs() < 1e-15);
    assert!((1.0_f64.ta_atan() - std::f64::consts::FRAC_PI_4).abs() < 1e-15);
}

#[test]
fn test_f32_trig() {
    let pi = std::f32::consts::PI;
    assert!((pi.ta_sin()).abs() < 1e-6);
    assert!((0.0_f32.ta_cos() - 1.0_f32).abs() < 1e-6);
    assert!((1.0_f32.ta_atan() - std::f32::consts::FRAC_PI_4).abs() < 1e-6);
}

#[test]
fn test_f64_log_exp() {
    assert!((1.0_f64.ta_exp() - std::f64::consts::E).abs() < 1e-14);
    assert!((std::f64::consts::E.ta_ln() - 1.0).abs() < 1e-15);
    assert!((100.0_f64.ta_log10() - 2.0).abs() < 1e-15);
}

#[test]
fn test_f32_log_exp() {
    assert!((1.0_f32.ta_exp() - std::f32::consts::E).abs() < 1e-5);
    assert!((std::f32::consts::E.ta_ln() - 1.0_f32).abs() < 1e-6);
    assert!((100.0_f32.ta_log10() - 2.0_f32).abs() < 1e-6);
}

#[test]
fn test_f64_hyperbolic() {
    assert!((0.0_f64.ta_sinh()).abs() < 1e-15);
    assert!((0.0_f64.ta_cosh() - 1.0).abs() < 1e-15);
    assert!((0.0_f64.ta_tanh()).abs() < 1e-15);
}

#[test]
fn test_f32_hyperbolic() {
    assert!((0.0_f32.ta_sinh()).abs() < 1e-6);
    assert!((0.0_f32.ta_cosh() - 1.0_f32).abs() < 1e-6);
    assert!((0.0_f32.ta_tanh()).abs() < 1e-6);
}

#[test]
fn test_f64_inverse_trig() {
    assert!((0.0_f64.ta_asin()).abs() < 1e-15);
    assert!((1.0_f64.ta_acos()).abs() < 1e-15);
    assert!((0.0_f64.ta_tan()).abs() < 1e-15);
}

#[test]
fn test_f32_inverse_trig() {
    assert!((0.0_f32.ta_asin()).abs() < 1e-6);
    assert!((1.0_f32.ta_acos()).abs() < 1e-6);
    assert!((0.0_f32.ta_tan()).abs() < 1e-6);
}

#[test]
fn test_operator_traits() {
    fn add_em<T: TaFloat>(a: T, b: T) -> T { a + b }
    fn sub_em<T: TaFloat>(a: T, b: T) -> T { a - b }
    fn mul_em<T: TaFloat>(a: T, b: T) -> T { a * b }
    fn div_em<T: TaFloat>(a: T, b: T) -> T { a / b }
    fn rem_em<T: TaFloat>(a: T, b: T) -> T { a % b }
    fn neg_em<T: TaFloat>(a: T) -> T { -a }

    assert_eq!(add_em(1.0_f64, 2.0), 3.0);
    assert_eq!(sub_em(5.0_f32, 3.0_f32), 2.0_f32);
    assert_eq!(mul_em(2.0_f64, 3.0), 6.0);
    assert_eq!(div_em(6.0_f32, 2.0_f32), 3.0_f32);
    assert_eq!(rem_em(7.0_f64, 3.0), 1.0);
    assert_eq!(neg_em(5.0_f64), -5.0);
}
