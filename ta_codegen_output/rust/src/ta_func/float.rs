//! Sealed floating-point trait for TA-Lib generic indicator functions.
//!
//! [`TaFloat`] is implemented for [`f32`] and [`f64`]. It cannot be implemented
//! outside this crate (sealed via `private::Sealed`).
//!
//! All trait methods use a `ta_` prefix to avoid name collisions with inherent
//! `f32`/`f64` methods in the standard library.

/// Sealed floating-point trait for generic TA-Lib indicator functions.
///
/// Provides constants, conversions, and math operations needed by
/// generated indicator code. All methods delegate to built-in intrinsics
/// and compile to single CPU instructions after monomorphization.
///
/// # Sealed
///
/// This trait cannot be implemented outside this crate. This allows
/// adding methods in future versions without breaking changes.
pub trait TaFloat:
    private::Sealed
    + Copy
    + PartialEq
    + PartialOrd
    + std::ops::Add<Output = Self>
    + std::ops::Sub<Output = Self>
    + std::ops::Mul<Output = Self>
    + std::ops::Div<Output = Self>
    + std::ops::Rem<Output = Self>
    + std::ops::Neg<Output = Self>
    + std::ops::AddAssign
    + std::ops::SubAssign
    + std::ops::MulAssign
    + std::ops::DivAssign
    + std::ops::RemAssign
{
    /// The additive identity (0.0).
    fn ta_zero() -> Self;
    /// The multiplicative identity (1.0).
    fn ta_one() -> Self;
    /// Machine epsilon for near-zero comparison.
    fn ta_epsilon() -> Self;

    /// Convert from `f64`. For `f64` this is identity; for `f32` it narrows.
    fn ta_from_f64(v: f64) -> Self;
    /// Convert from `i32`.
    fn ta_from_i32(v: i32) -> Self;
    /// Convert to `f64`. For `f64` this is identity; for `f32` it widens.
    fn ta_to_f64(self) -> f64;

    /// Absolute value.
    fn ta_abs(self) -> Self;
    /// Square root.
    fn ta_sqrt(self) -> Self;
    /// Ceiling (round up).
    fn ta_ceil(self) -> Self;
    /// Floor (round down).
    fn ta_floor(self) -> Self;
    /// Round to nearest integer.
    fn ta_round(self) -> Self;

    /// Sine.
    fn ta_sin(self) -> Self;
    /// Cosine.
    fn ta_cos(self) -> Self;
    /// Tangent.
    fn ta_tan(self) -> Self;
    /// Arcsine.
    fn ta_asin(self) -> Self;
    /// Arccosine.
    fn ta_acos(self) -> Self;
    /// Arctangent.
    fn ta_atan(self) -> Self;

    /// Hyperbolic sine.
    fn ta_sinh(self) -> Self;
    /// Hyperbolic cosine.
    fn ta_cosh(self) -> Self;
    /// Hyperbolic tangent.
    fn ta_tanh(self) -> Self;

    /// Natural logarithm.
    fn ta_ln(self) -> Self;
    /// Base-10 logarithm.
    fn ta_log10(self) -> Self;
    /// Exponential (e^self).
    fn ta_exp(self) -> Self;

    /// Minimum of two values.
    fn min(self, other: Self) -> Self;
    /// Maximum of two values.
    fn max(self, other: Self) -> Self;
}

macro_rules! impl_ta_float {
    ($t:ty, $epsilon:expr) => {
        impl TaFloat for $t {
            #[inline(always)] fn ta_zero() -> Self { 0.0 }
            #[inline(always)] fn ta_one() -> Self { 1.0 }
            #[inline(always)] fn ta_epsilon() -> Self { $epsilon }

            #[inline(always)] fn ta_from_f64(v: f64) -> Self { v as Self }
            #[inline(always)] fn ta_from_i32(v: i32) -> Self { v as Self }
            #[inline(always)] fn ta_to_f64(self) -> f64 { self as f64 }

            #[inline(always)] fn ta_abs(self) -> Self { <$t>::abs(self) }
            #[inline(always)] fn ta_sqrt(self) -> Self { <$t>::sqrt(self) }
            #[inline(always)] fn ta_ceil(self) -> Self { <$t>::ceil(self) }
            #[inline(always)] fn ta_floor(self) -> Self { <$t>::floor(self) }
            #[inline(always)] fn ta_round(self) -> Self { <$t>::round(self) }

            #[inline(always)] fn ta_sin(self) -> Self { <$t>::sin(self) }
            #[inline(always)] fn ta_cos(self) -> Self { <$t>::cos(self) }
            #[inline(always)] fn ta_tan(self) -> Self { <$t>::tan(self) }
            #[inline(always)] fn ta_asin(self) -> Self { <$t>::asin(self) }
            #[inline(always)] fn ta_acos(self) -> Self { <$t>::acos(self) }
            #[inline(always)] fn ta_atan(self) -> Self { <$t>::atan(self) }

            #[inline(always)] fn ta_sinh(self) -> Self { <$t>::sinh(self) }
            #[inline(always)] fn ta_cosh(self) -> Self { <$t>::cosh(self) }
            #[inline(always)] fn ta_tanh(self) -> Self { <$t>::tanh(self) }

            #[inline(always)] fn ta_ln(self) -> Self { <$t>::ln(self) }
            #[inline(always)] fn ta_log10(self) -> Self { <$t>::log10(self) }
            #[inline(always)] fn ta_exp(self) -> Self { <$t>::exp(self) }

            #[inline(always)] fn min(self, other: Self) -> Self { <$t>::min(self, other) }
            #[inline(always)] fn max(self, other: Self) -> Self { <$t>::max(self, other) }
        }
    };
}

impl_ta_float!(f64, 1e-14);
impl_ta_float!(f32, 1e-6);

mod private {
    /// Sealed trait -- prevents external implementations of [`super::TaFloat`].
    pub trait Sealed {}
    impl Sealed for f32 {}
    impl Sealed for f64 {}
}
