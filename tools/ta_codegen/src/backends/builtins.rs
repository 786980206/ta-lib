//! Typed taxonomy of builtin function calls shared by the language backends.
//!
//! Indicator source calls a handful of `<math.h>` functions (`sqrt`, `sin`,
//! `max`, …) by name as `Expr::FuncCall`. Each backend used to classify those
//! names against its own `const MATH_FUNCTIONS: &[&str]` list — three copies that
//! had already drifted (e.g. only the Rust list carried a stray lowercase `abs`).
//! [`MathFn`] replaces all three with one classifier, so a name is recognised as a
//! math builtin in exactly one place and the compiler enforces that every backend
//! handles each variant.
//!
//! Name aliases that render identically within every backend collapse into one
//! variant: `max`/`fmax` → [`MathFn::Max`], `min`/`fmin` → [`MathFn::Min`],
//! `fabs`/`ABS` → [`MathFn::Abs`]. Each backend starts from [`MathFn::canonical`]
//! and applies its own small remap (C uses `fmax`/`fmin`/`fabs`; Java prefixes
//! `Math.`; Rust emits method calls and uses `ln` for `Log`).

/// A `<math.h>` builtin math function callable from indicator source.
#[derive(Clone, Copy)]
pub enum MathFn {
    Atan,
    Sqrt,
    Floor,
    Ceil,
    Log,
    Cos,
    Sin,
    Tan,
    Acos,
    Asin,
    Exp,
    Cosh,
    Sinh,
    Tanh,
    Log10,
    Abs,
    Max,
    Min,
}

impl MathFn {
    /// Classify a `FuncCall` name as a math builtin, or `None` if it is not one.
    /// The single source of truth that replaced the per-backend `MATH_FUNCTIONS`
    /// lists.
    pub fn from_name(name: &str) -> Option<Self> {
        Some(match name {
            "atan" => Self::Atan,
            "sqrt" => Self::Sqrt,
            "floor" => Self::Floor,
            "ceil" => Self::Ceil,
            "log" => Self::Log,
            "cos" => Self::Cos,
            "sin" => Self::Sin,
            "tan" => Self::Tan,
            "acos" => Self::Acos,
            "asin" => Self::Asin,
            "exp" => Self::Exp,
            "cosh" => Self::Cosh,
            "sinh" => Self::Sinh,
            "tanh" => Self::Tanh,
            "log10" => Self::Log10,
            "fabs" | "ABS" => Self::Abs,
            "max" | "fmax" => Self::Max,
            "min" | "fmin" => Self::Min,
            _ => return None,
        })
    }

    /// The canonical lowercase math name (`Abs` → `"abs"`, `Max` → `"max"`, …).
    /// Backends start from this and apply their own remaps where the language name
    /// differs (e.g. C maps `Max`/`Min`/`Abs` to `fmax`/`fmin`/`fabs`).
    pub fn canonical(self) -> &'static str {
        match self {
            Self::Atan => "atan",
            Self::Sqrt => "sqrt",
            Self::Floor => "floor",
            Self::Ceil => "ceil",
            Self::Log => "log",
            Self::Cos => "cos",
            Self::Sin => "sin",
            Self::Tan => "tan",
            Self::Acos => "acos",
            Self::Asin => "asin",
            Self::Exp => "exp",
            Self::Cosh => "cosh",
            Self::Sinh => "sinh",
            Self::Tanh => "tanh",
            Self::Log10 => "log10",
            Self::Abs => "abs",
            Self::Max => "max",
            Self::Min => "min",
        }
    }
}
