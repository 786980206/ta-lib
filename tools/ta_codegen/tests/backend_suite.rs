//! Comprehensive backend test suite for all indicators and all function variants.
//!
//! This complements `integration_test.rs` with systematic coverage:
//! - Every indicator x every backend x every function variant
//! - Cross-call resolution (MA calling SMA/EMA)
//! - Logic vs guarded validation checks
//! - Indicator-specific feature tests (unstable period, enums, etc.)

use std::collections::HashMap;
use std::path::Path;
use ta_codegen_lib::backends;
use ta_codegen_lib::ir;
use ta_codegen_lib::parser;
use ta_codegen_lib::registry::Registry;

// ---------------------------------------------------------------------------
// Test infrastructure
// ---------------------------------------------------------------------------

/// Load a function definition from its .yaml + .c files.
fn load_indicator(name: &str) -> (ir::FuncDef, HashMap<String, ir::EnumDef>) {
    let base = Path::new(env!("CARGO_MANIFEST_DIR")).join("../../ta_func_defs");
    let yaml_path = base.join(format!("{}/{}.yaml", name, name));
    let c_path = base.join(format!("{}/{}.c", name, name));

    let enums = if name == "ma" {
        let enums_path = base.join("enums.yaml");
        parser::enums::load_enums(&enums_path)
    } else {
        HashMap::new()
    };

    let mut func_def = parser::yaml::parse_yaml(&yaml_path);
    let parsed = parser::c_source::parse_c_source(&c_path);
    func_def.body = parsed
        .functions
        .first()
        .expect("C source must contain at least one function")
        .body
        .clone();
    func_def.lookback = Some(ir::LookbackExpr::Code(parsed.lookback_body));

    (func_def, enums)
}

/// All backend outputs for a single indicator.
struct AllOutputs {
    c: String,
    rust: String,
    java: String,
    dotnet: String,
    swig: String,
}

fn make_registry() -> Registry {
    let base = Path::new(env!("CARGO_MANIFEST_DIR")).join("../../ta_func_defs");
    Registry::from_dir(&base)
}

fn generate_all(func: &ir::FuncDef, enums: &HashMap<String, ir::EnumDef>) -> AllOutputs {
    let registry = make_registry();
    AllOutputs {
        c: backends::c::generate(func, enums, &registry),
        rust: backends::rust_lang::generate(func, enums, &registry),
        java: backends::java::generate(func, enums, &registry),
        dotnet: backends::dotnet::generate(func, enums, &registry),
        swig: backends::swig::generate(func, enums, &registry),
    }
}

// ---------------------------------------------------------------------------
// Macros for reducing test boilerplate
// ---------------------------------------------------------------------------

/// Test that all C variants exist for a given indicator.
/// C variants: TA_<NAME>_Lookback, TA_<NAME>(, TA_<NAME>_Logic(, #define TA_INT_<NAME>,
///             TA_S_<NAME>(, TA_S_<NAME>_Logic(
macro_rules! test_c_variants {
    ($test_name:ident, $indicator:expr, $upper:expr) => {
        #[test]
        fn $test_name() {
            let (func, enums) = load_indicator($indicator);
            let out = generate_all(&func, &enums);
            let c = &out.c;

            assert!(
                c.contains(&format!("TA_{}_Lookback", $upper)),
                "C: missing TA_{}_Lookback",
                $upper
            );
            assert!(
                c.contains(&format!("TA_{}(", $upper))
                    || c.contains(&format!("TA_{} (", $upper)),
                "C: missing TA_{}",
                $upper
            );
            assert!(
                c.contains(&format!("TA_{}_Logic(", $upper)),
                "C: missing TA_{}_Logic",
                $upper
            );
            assert!(
                c.contains(&format!("#define TA_INT_{}", $upper)),
                "C: missing #define TA_INT_{}",
                $upper
            );
            assert!(
                c.contains(&format!("TA_S_{}(", $upper))
                    || c.contains(&format!("TA_S_{} (", $upper)),
                "C: missing TA_S_{}",
                $upper
            );
            assert!(
                c.contains(&format!("TA_S_{}_Logic(", $upper)),
                "C: missing TA_S_{}_Logic",
                $upper
            );
        }
    };
}

/// Test that all Rust variants exist for a given indicator.
/// For indicators WITH optional inputs: <name>_lookback, fn <name>(, fn <name>_logic(,
///     <name>_unsafe, fn <name>_s(, fn <name>_logic_s(, <name>_unsafe_s
/// For indicators WITHOUT optional inputs (mult): <name>_lookback, fn <name>(,
///     <name>_unsafe, fn <name>_s(, <name>_unsafe_s (no _logic variants)
macro_rules! test_rust_variants {
    ($test_name:ident, $indicator:expr, $snake:expr, has_opt_inputs: true) => {
        #[test]
        fn $test_name() {
            let (func, enums) = load_indicator($indicator);
            let out = generate_all(&func, &enums);
            let r = &out.rust;

            assert!(
                r.contains(&format!("{}_lookback", $snake)),
                "Rust: missing {}_lookback",
                $snake
            );
            assert!(
                r.contains(&format!("fn {}(", $snake))
                    || r.contains(&format!("fn {}(\n", $snake)),
                "Rust: missing fn {}",
                $snake
            );
            assert!(
                r.contains(&format!("fn {}_logic(", $snake))
                    || r.contains(&format!("fn {}_logic(\n", $snake)),
                "Rust: missing fn {}_logic",
                $snake
            );
            assert!(
                r.contains(&format!("{}_unsafe", $snake)),
                "Rust: missing {}_unsafe placeholder",
                $snake
            );
            assert!(
                r.contains(&format!("fn {}_s(", $snake))
                    || r.contains(&format!("fn {}_s(\n", $snake)),
                "Rust: missing fn {}_s",
                $snake
            );
            assert!(
                r.contains(&format!("fn {}_logic_s(", $snake))
                    || r.contains(&format!("fn {}_logic_s(\n", $snake)),
                "Rust: missing fn {}_logic_s",
                $snake
            );
            assert!(
                r.contains(&format!("{}_unsafe_s", $snake)),
                "Rust: missing {}_unsafe_s placeholder",
                $snake
            );
        }
    };
    ($test_name:ident, $indicator:expr, $snake:expr, has_opt_inputs: false) => {
        #[test]
        fn $test_name() {
            let (func, enums) = load_indicator($indicator);
            let out = generate_all(&func, &enums);
            let r = &out.rust;

            assert!(
                r.contains(&format!("{}_lookback", $snake)),
                "Rust: missing {}_lookback",
                $snake
            );
            assert!(
                r.contains(&format!("fn {}(", $snake))
                    || r.contains(&format!("fn {}(\n", $snake)),
                "Rust: missing fn {}",
                $snake
            );
            // No _logic variant for functions without optional inputs
            assert!(
                !r.contains(&format!("fn {}_logic(", $snake)),
                "Rust: should NOT have {}_logic (no optional inputs)",
                $snake
            );
            assert!(
                r.contains(&format!("{}_unsafe", $snake)),
                "Rust: missing {}_unsafe placeholder",
                $snake
            );
            assert!(
                r.contains(&format!("fn {}_s(", $snake))
                    || r.contains(&format!("fn {}_s(\n", $snake)),
                "Rust: missing fn {}_s",
                $snake
            );
            assert!(
                r.contains(&format!("{}_unsafe_s", $snake)),
                "Rust: missing {}_unsafe_s placeholder",
                $snake
            );
        }
    };
}

/// Test that all Java variants exist for a given indicator.
/// Java variants: <name>Lookback, public RetCode <name>(, <name>Logic(
macro_rules! test_java_variants {
    ($test_name:ident, $indicator:expr, $lower:expr) => {
        #[test]
        fn $test_name() {
            let (func, enums) = load_indicator($indicator);
            let out = generate_all(&func, &enums);
            let j = &out.java;

            assert!(
                j.contains(&format!("{}Lookback(", $lower)),
                "Java: missing {}Lookback",
                $lower
            );
            assert!(
                j.contains(&format!("RetCode {}(", $lower))
                    || j.contains(&format!("RetCode {} (", $lower)),
                "Java: missing {} function",
                $lower
            );
            assert!(
                j.contains(&format!("{}Logic(", $lower)),
                "Java: missing {}Logic",
                $lower
            );
        }
    };
}

/// Test that all .NET variants exist for a given indicator.
/// .NET variants: <Pascal>Lookback, <Pascal>(, <Pascal>Logic(,
///     #define TA_<UPPER>, #define TA_<UPPER>_Logic, #define TA_INT_<UPPER>
macro_rules! test_dotnet_variants {
    ($test_name:ident, $indicator:expr, $pascal:expr, $upper:expr) => {
        #[test]
        fn $test_name() {
            let (func, enums) = load_indicator($indicator);
            let out = generate_all(&func, &enums);
            let d = &out.dotnet;

            assert!(
                d.contains(&format!("{}Lookback(", $pascal)),
                ".NET: missing {}Lookback",
                $pascal
            );
            assert!(
                d.contains(&format!("{}(", $pascal))
                    || d.contains(&format!("{} (", $pascal)),
                ".NET: missing {} function",
                $pascal
            );
            assert!(
                d.contains(&format!("{}Logic(", $pascal)),
                ".NET: missing {}Logic declaration",
                $pascal
            );
            assert!(
                d.contains(&format!("#define TA_{} ", $upper))
                    || d.contains(&format!("#define TA_{}\n", $upper)),
                ".NET: missing #define TA_{}",
                $upper
            );
            assert!(
                d.contains(&format!("#define TA_{}_Logic", $upper)),
                ".NET: missing #define TA_{}_Logic",
                $upper
            );
            assert!(
                d.contains(&format!("#define TA_INT_{}", $upper)),
                ".NET: missing #define TA_INT_{}",
                $upper
            );
        }
    };
}

/// Test that all SWIG variants exist for a given indicator.
/// SWIG variants: TA_<NAME>(, TA_<NAME>_Logic(, TA_<NAME>_Lookback
macro_rules! test_swig_variants {
    ($test_name:ident, $indicator:expr, $upper:expr) => {
        #[test]
        fn $test_name() {
            let (func, enums) = load_indicator($indicator);
            let out = generate_all(&func, &enums);
            let s = &out.swig;

            assert!(
                s.contains(&format!("TA_{}(", $upper))
                    || s.contains(&format!("TA_{} (", $upper)),
                "SWIG: missing TA_{}",
                $upper
            );
            assert!(
                s.contains(&format!("TA_{}_Logic(", $upper)),
                "SWIG: missing TA_{}_Logic",
                $upper
            );
            assert!(
                s.contains(&format!("TA_{}_Lookback", $upper)),
                "SWIG: missing TA_{}_Lookback",
                $upper
            );
        }
    };
}

// ---------------------------------------------------------------------------
// 2. Per-indicator x per-backend variant checks
// ---------------------------------------------------------------------------

// --- SMA ---
test_c_variants!(test_sma_c_variants, "sma", "SMA");
test_rust_variants!(test_sma_rust_variants, "sma", "sma", has_opt_inputs: true);
test_java_variants!(test_sma_java_variants, "sma", "sma");
test_dotnet_variants!(test_sma_dotnet_variants, "sma", "Sma", "SMA");
test_swig_variants!(test_sma_swig_variants, "sma", "SMA");

// --- RSI ---
test_c_variants!(test_rsi_c_variants, "rsi", "RSI");
test_rust_variants!(test_rsi_rust_variants, "rsi", "rsi", has_opt_inputs: true);
test_java_variants!(test_rsi_java_variants, "rsi", "rsi");
test_dotnet_variants!(test_rsi_dotnet_variants, "rsi", "Rsi", "RSI");
test_swig_variants!(test_rsi_swig_variants, "rsi", "RSI");

// --- EMA ---
test_c_variants!(test_ema_c_variants, "ema", "EMA");
test_rust_variants!(test_ema_rust_variants, "ema", "ema", has_opt_inputs: true);
test_java_variants!(test_ema_java_variants, "ema", "ema");
test_dotnet_variants!(test_ema_dotnet_variants, "ema", "Ema", "EMA");
test_swig_variants!(test_ema_swig_variants, "ema", "EMA");

// --- WMA ---
test_c_variants!(test_wma_c_variants, "wma", "WMA");
test_rust_variants!(test_wma_rust_variants, "wma", "wma", has_opt_inputs: true);
test_java_variants!(test_wma_java_variants, "wma", "wma");
test_dotnet_variants!(test_wma_dotnet_variants, "wma", "Wma", "WMA");
test_swig_variants!(test_wma_swig_variants, "wma", "WMA");

// --- MA ---
test_c_variants!(test_ma_c_variants, "ma", "MA");
test_rust_variants!(test_ma_rust_variants, "ma", "ma", has_opt_inputs: true);
test_java_variants!(test_ma_java_variants, "ma", "ma");
test_dotnet_variants!(test_ma_dotnet_variants, "ma", "Ma", "MA");
test_swig_variants!(test_ma_swig_variants, "ma", "MA");

// --- MULT ---
test_c_variants!(test_mult_c_variants, "mult", "MULT");
test_rust_variants!(test_mult_rust_variants, "mult", "mult", has_opt_inputs: false);
test_java_variants!(test_mult_java_variants, "mult", "mult");
test_dotnet_variants!(test_mult_dotnet_variants, "mult", "Mult", "MULT");
test_swig_variants!(test_mult_swig_variants, "mult", "MULT");

// ---------------------------------------------------------------------------
// 3. Cross-call resolution tests (MA calls sma/ema lookback + logic)
// ---------------------------------------------------------------------------

#[test]
fn test_ma_c_cross_calls() {
    let (func, enums) = load_indicator("ma");
    let out = generate_all(&func, &enums);
    let c = &out.c;

    assert!(
        c.contains("TA_SMA_Lookback("),
        "C: MA should call TA_SMA_Lookback"
    );
    assert!(
        c.contains("TA_EMA_Lookback("),
        "C: MA should call TA_EMA_Lookback"
    );
    assert!(
        c.contains("TA_INT_SMA("),
        "C: MA should call TA_INT_SMA (sma_logic)"
    );
    assert!(
        c.contains("TA_INT_EMA("),
        "C: MA should call TA_INT_EMA (ema_logic)"
    );
}

#[test]
fn test_ma_java_cross_calls() {
    let (func, enums) = load_indicator("ma");
    let out = generate_all(&func, &enums);
    let j = &out.java;

    assert!(
        j.contains("smaLookback("),
        "Java: MA should call smaLookback"
    );
    assert!(
        j.contains("emaLookback("),
        "Java: MA should call emaLookback"
    );
    assert!(j.contains("smaLogic("), "Java: MA should call smaLogic");
    assert!(j.contains("emaLogic("), "Java: MA should call emaLogic");
}

#[test]
fn test_ma_rust_cross_calls() {
    let (func, enums) = load_indicator("ma");
    let out = generate_all(&func, &enums);
    let r = &out.rust;

    // In Rust, cross-calls stay as prefix-free names with self.
    assert!(
        r.contains("self.sma_lookback("),
        "Rust: MA should call self.sma_lookback"
    );
    assert!(
        r.contains("self.ema_lookback("),
        "Rust: MA should call self.ema_lookback"
    );
    assert!(
        r.contains("self.sma_logic("),
        "Rust: MA should call self.sma_logic"
    );
    assert!(
        r.contains("self.ema_logic("),
        "Rust: MA should call self.ema_logic"
    );
}

// ---------------------------------------------------------------------------
// 4. Logic vs guarded validation tests
// ---------------------------------------------------------------------------

/// Helper: extract the section of output between `start_marker` and `end_marker`.
/// If `end_marker` is not found, returns everything after `start_marker`.
fn extract_section(output: &str, start_marker: &str, end_marker: &str) -> String {
    let start = output
        .find(start_marker)
        .unwrap_or_else(|| panic!("Could not find '{}' in output", start_marker));
    let rest = &output[start..];
    let end = rest.find(end_marker).unwrap_or(rest.len());
    rest[..end].to_string()
}

#[test]
fn test_c_sma_guarded_has_validation() {
    let (func, enums) = load_indicator("sma");
    let out = generate_all(&func, &enums);

    // Extract guarded function (between TA_SMA( and TA_SMA_Logic)
    let guarded = extract_section(&out.c, "TA_RetCode TA_SMA(", "TA_SMA_Logic(");
    assert!(
        guarded.contains("TA_OUT_OF_RANGE_START_INDEX"),
        "C guarded SMA should have start index validation"
    );
    assert!(
        guarded.contains("TA_OUT_OF_RANGE_END_INDEX"),
        "C guarded SMA should have end index validation"
    );
}

#[test]
fn test_c_sma_logic_omits_validation() {
    let (func, enums) = load_indicator("sma");
    let out = generate_all(&func, &enums);

    // Extract logic function (between TA_SMA_Logic( and #define TA_INT_SMA)
    let logic = extract_section(&out.c, "TA_SMA_Logic(", "#define TA_INT_SMA");
    assert!(
        !logic.contains("TA_OUT_OF_RANGE_START_INDEX"),
        "C logic SMA should NOT have start index validation"
    );
    assert!(
        !logic.contains("TA_OUT_OF_RANGE_END_INDEX"),
        "C logic SMA should NOT have end index validation"
    );
}

#[test]
fn test_java_sma_guarded_has_validation() {
    let (func, enums) = load_indicator("sma");
    let out = generate_all(&func, &enums);

    // Extract guarded function (between "RetCode sma(" and "smaLogic(")
    let guarded = extract_section(&out.java, "RetCode sma(", "smaLogic(");
    assert!(
        guarded.contains("OutOfRangeStartIndex"),
        "Java guarded SMA should have start index validation"
    );
}

#[test]
fn test_java_sma_logic_omits_validation() {
    let (func, enums) = load_indicator("sma");
    let out = generate_all(&func, &enums);

    // Extract logic function (find smaLogic, get section until next "public RetCode")
    let logic_start = out.java.find("smaLogic(").expect("Missing smaLogic");
    let logic_section = &out.java[logic_start..];
    // Look for next public function or end
    let end = logic_section
        .find("public RetCode sma(")
        .or_else(|| logic_section.find("public int"))
        .unwrap_or(logic_section.len());
    let logic = &logic_section[..end];
    assert!(
        !logic.contains("OutOfRangeStartIndex"),
        "Java logic SMA should NOT have start index validation"
    );
}

#[test]
fn test_rust_sma_guarded_has_validation() {
    let (func, enums) = load_indicator("sma");
    let out = generate_all(&func, &enums);

    // The guarded Rust function delegates to _logic, but first validates params.
    // For Rust, the public func (sma) should have endIdx < startIdx check
    let guarded = extract_section(&out.rust, "pub fn sma(", "fn sma_logic(");
    assert!(
        guarded.contains("endIdx < startIdx"),
        "Rust guarded SMA should have endIdx < startIdx check"
    );
}

#[test]
fn test_rust_sma_logic_omits_validation() {
    let (func, enums) = load_indicator("sma");
    let out = generate_all(&func, &enums);

    // The logic function should not have the range check
    let logic_start = out.rust.find("fn sma_logic(").expect("Missing sma_logic");
    let logic_section = &out.rust[logic_start..];
    let end = logic_section
        .find("pub fn sma_s(")
        .unwrap_or(logic_section.len());
    let logic = &logic_section[..end];
    assert!(
        !logic.contains("OutOfRangeStartIndex"),
        "Rust logic SMA should NOT have range validation"
    );
}

// Also test a different indicator for validation (RSI)
#[test]
fn test_c_rsi_logic_omits_validation() {
    let (func, enums) = load_indicator("rsi");
    let out = generate_all(&func, &enums);

    let logic = extract_section(&out.c, "TA_RSI_Logic(", "#define TA_INT_RSI");
    assert!(
        !logic.contains("TA_OUT_OF_RANGE_START_INDEX"),
        "C logic RSI should NOT have start index validation"
    );
}

#[test]
fn test_c_rsi_guarded_has_validation() {
    let (func, enums) = load_indicator("rsi");
    let out = generate_all(&func, &enums);

    let guarded = extract_section(&out.c, "TA_RetCode TA_RSI(", "TA_RSI_Logic(");
    assert!(
        guarded.contains("TA_OUT_OF_RANGE_START_INDEX"),
        "C guarded RSI should have start index validation"
    );
}

// ---------------------------------------------------------------------------
// 5. Indicator-specific feature tests
// ---------------------------------------------------------------------------

// --- RSI: unstable period + compatibility + IS_ZERO ---

#[test]
fn test_rsi_c_unstable_period() {
    let (func, enums) = load_indicator("rsi");
    let out = generate_all(&func, &enums);

    assert!(
        out.c.contains("TA_GLOBALS_UNSTABLE_PERIOD"),
        "C RSI should use TA_GLOBALS_UNSTABLE_PERIOD"
    );
    assert!(
        out.c.contains("TA_GLOBALS_COMPATIBILITY"),
        "C RSI should use TA_GLOBALS_COMPATIBILITY"
    );
    assert!(
        out.c.contains("TA_IS_ZERO"),
        "C RSI should use TA_IS_ZERO"
    );
}

#[test]
fn test_rsi_rust_unstable_period() {
    let (func, enums) = load_indicator("rsi");
    let out = generate_all(&func, &enums);

    assert!(
        out.rust.contains("unstable_period"),
        "Rust RSI should reference unstable_period"
    );
}

#[test]
fn test_rsi_java_unstable_period() {
    let (func, enums) = load_indicator("rsi");
    let out = generate_all(&func, &enums);

    assert!(
        out.java.contains("this.unstablePeriod"),
        "Java RSI should reference this.unstablePeriod"
    );
    assert!(
        out.java.contains("this.compatibility"),
        "Java RSI should reference this.compatibility"
    );
}

// --- EMA: unstable period + ARRAY_COPY ---

#[test]
fn test_ema_c_unstable_period() {
    let (func, enums) = load_indicator("ema");
    let out = generate_all(&func, &enums);

    assert!(
        out.c.contains("TA_GLOBALS_UNSTABLE_PERIOD"),
        "C EMA should use TA_GLOBALS_UNSTABLE_PERIOD"
    );
}

#[test]
fn test_ema_c_per_to_k() {
    let (func, enums) = load_indicator("ema");
    let out = generate_all(&func, &enums);

    // EMA uses PER_TO_K to compute the smoothing factor k
    assert!(
        out.c.contains("2.0 / ((double)"),
        "C EMA should contain PER_TO_K expansion (2.0 / ((double)...))"
    );
}

#[test]
fn test_ema_java_per_to_k() {
    let (func, enums) = load_indicator("ema");
    let out = generate_all(&func, &enums);

    // Java EMA also uses PER_TO_K
    assert!(
        out.java.contains("2.0 / ((double)"),
        "Java EMA should contain PER_TO_K expansion"
    );
}

#[test]
fn test_ema_rust_unstable_period() {
    let (func, enums) = load_indicator("ema");
    let out = generate_all(&func, &enums);

    assert!(
        out.rust.contains("unstable_period"),
        "Rust EMA should reference unstable_period"
    );
}

// --- MA: switch/case with enum labels ---

#[test]
fn test_ma_c_switch_statement() {
    let (func, enums) = load_indicator("ma");
    let out = generate_all(&func, &enums);

    assert!(
        out.c.contains("switch(") || out.c.contains("switch ("),
        "C MA should contain a switch statement"
    );
    // Should use ENUM_CASE macro in C for enum labels
    assert!(
        out.c.contains("ENUM_CASE("),
        "C MA should use ENUM_CASE for switch labels"
    );
}

#[test]
fn test_ma_java_switch_statement() {
    let (func, enums) = load_indicator("ma");
    let out = generate_all(&func, &enums);

    assert!(
        out.java.contains("switch(") || out.java.contains("switch ("),
        "Java MA should contain a switch statement"
    );
    // Java uses Type.Variant for switch labels
    assert!(
        out.java.contains("MAType.Sma") || out.java.contains("MAType.Ema"),
        "Java MA should use MAType enum labels"
    );
}

#[test]
fn test_ma_rust_switch_statement() {
    let (func, enums) = load_indicator("ma");
    let out = generate_all(&func, &enums);

    // Rust uses match instead of switch
    assert!(
        out.rust.contains("match "),
        "Rust MA should contain a match statement"
    );
}

// --- MULT: simple expression, no optional inputs ---

#[test]
fn test_mult_simplicity() {
    let (func, enums) = load_indicator("mult");
    let out = generate_all(&func, &enums);

    // MULT has no optional inputs
    assert!(
        func.optional_inputs.is_empty(),
        "MULT should have no optional inputs"
    );

    // MULT has exactly 2 inputs
    assert_eq!(func.inputs.len(), 2, "MULT should have exactly 2 inputs");

    // MULT has exactly 1 output
    assert_eq!(func.outputs.len(), 1, "MULT should have exactly 1 output");

    // C output should have multiplication
    assert!(
        out.c.contains("inReal0[") && out.c.contains("inReal1["),
        "C MULT should reference both input arrays"
    );

    // No unstable period, no COMPATIBILITY
    assert!(
        !out.c.contains("UNSTABLE_PERIOD"),
        "C MULT should NOT use UNSTABLE_PERIOD"
    );
}

// ---------------------------------------------------------------------------
// 6. Non-empty output checks for all indicators across all backends
// ---------------------------------------------------------------------------

macro_rules! test_all_backends_nonempty {
    ($test_name:ident, $indicator:expr) => {
        #[test]
        fn $test_name() {
            let (func, enums) = load_indicator($indicator);
            let out = generate_all(&func, &enums);

            assert!(
                !out.c.is_empty(),
                "{}: C output is empty",
                $indicator
            );
            assert!(
                !out.rust.is_empty(),
                "{}: Rust output is empty",
                $indicator
            );
            assert!(
                !out.java.is_empty(),
                "{}: Java output is empty",
                $indicator
            );
            assert!(
                !out.dotnet.is_empty(),
                "{}: .NET output is empty",
                $indicator
            );
            assert!(
                !out.swig.is_empty(),
                "{}: SWIG output is empty",
                $indicator
            );

            // Sanity: outputs should have meaningful length
            assert!(out.c.len() > 200, "{}: C output suspiciously short", $indicator);
            assert!(out.rust.len() > 200, "{}: Rust output suspiciously short", $indicator);
            assert!(out.java.len() > 100, "{}: Java output suspiciously short", $indicator);
            assert!(out.dotnet.len() > 100, "{}: .NET output suspiciously short", $indicator);
            assert!(out.swig.len() > 100, "{}: SWIG output suspiciously short", $indicator);
        }
    };
}

test_all_backends_nonempty!(test_sma_all_backends_nonempty, "sma");
test_all_backends_nonempty!(test_rsi_all_backends_nonempty, "rsi");
test_all_backends_nonempty!(test_ema_all_backends_nonempty, "ema");
test_all_backends_nonempty!(test_wma_all_backends_nonempty, "wma");
test_all_backends_nonempty!(test_ma_all_backends_nonempty, "ma");
test_all_backends_nonempty!(test_mult_all_backends_nonempty, "mult");

// ---------------------------------------------------------------------------
// 7. C #define TA_INT alias correctness
// ---------------------------------------------------------------------------

macro_rules! test_c_int_alias {
    ($test_name:ident, $indicator:expr, $upper:expr) => {
        #[test]
        fn $test_name() {
            let (func, enums) = load_indicator($indicator);
            let out = generate_all(&func, &enums);
            assert!(
                out.c.contains(&format!(
                    "#define TA_INT_{} TA_{}_Logic",
                    $upper, $upper
                )),
                "C: missing #define TA_INT_{} TA_{}_Logic",
                $upper,
                $upper
            );
        }
    };
}

test_c_int_alias!(test_sma_c_int_alias, "sma", "SMA");
test_c_int_alias!(test_rsi_c_int_alias, "rsi", "RSI");
test_c_int_alias!(test_ema_c_int_alias, "ema", "EMA");
test_c_int_alias!(test_wma_c_int_alias, "wma", "WMA");
test_c_int_alias!(test_ma_c_int_alias, "ma", "MA");
test_c_int_alias!(test_mult_c_int_alias, "mult", "MULT");

// ---------------------------------------------------------------------------
// 8. .NET macros point to correct Core:: methods
// ---------------------------------------------------------------------------

macro_rules! test_dotnet_macros {
    ($test_name:ident, $indicator:expr, $pascal:expr, $upper:expr) => {
        #[test]
        fn $test_name() {
            let (func, enums) = load_indicator($indicator);
            let out = generate_all(&func, &enums);
            let d = &out.dotnet;

            assert!(
                d.contains(&format!("#define TA_{} Core::{}", $upper, $pascal)),
                ".NET: TA_{} should point to Core::{}",
                $upper,
                $pascal
            );
            assert!(
                d.contains(&format!(
                    "#define TA_{}_Lookback Core::{}Lookback",
                    $upper, $pascal
                )),
                ".NET: TA_{}_Lookback should point to Core::{}Lookback",
                $upper,
                $pascal
            );
            assert!(
                d.contains(&format!(
                    "#define TA_{}_Logic Core::{}Logic",
                    $upper, $pascal
                )),
                ".NET: TA_{}_Logic should point to Core::{}Logic",
                $upper,
                $pascal
            );
            assert!(
                d.contains(&format!(
                    "#define TA_INT_{} Core::{}Logic",
                    $upper, $pascal
                )),
                ".NET: TA_INT_{} should point to Core::{}Logic",
                $upper,
                $pascal
            );
        }
    };
}

test_dotnet_macros!(test_sma_dotnet_macros, "sma", "Sma", "SMA");
test_dotnet_macros!(test_rsi_dotnet_macros, "rsi", "Rsi", "RSI");
test_dotnet_macros!(test_ema_dotnet_macros, "ema", "Ema", "EMA");
test_dotnet_macros!(test_wma_dotnet_macros, "wma", "Wma", "WMA");
test_dotnet_macros!(test_ma_dotnet_macros, "ma", "Ma", "MA");
test_dotnet_macros!(test_mult_dotnet_macros, "mult", "Mult", "MULT");

// ---------------------------------------------------------------------------
// 9. SWIG comment block contains function description
// ---------------------------------------------------------------------------

#[test]
fn test_swig_comment_blocks() {
    let indicators = ["sma", "rsi", "ema", "wma", "ma", "mult"];
    for name in &indicators {
        let (func, enums) = load_indicator(name);
        let out = generate_all(&func, &enums);

        assert!(
            out.swig.contains("/*"),
            "SWIG {}: missing comment block",
            name
        );
        assert!(
            out.swig.contains(&format!("TA_{}", func.name)),
            "SWIG {}: comment block missing TA_{} reference",
            name,
            func.name
        );
    }
}

// ---------------------------------------------------------------------------
// 10. Rust impl Core block structure
// ---------------------------------------------------------------------------

#[test]
fn test_rust_impl_core_structure() {
    let indicators = ["sma", "rsi", "ema", "wma", "ma", "mult"];
    for name in &indicators {
        let (func, enums) = load_indicator(name);
        let out = generate_all(&func, &enums);

        assert!(
            out.rust.contains("impl Core {"),
            "Rust {}: missing impl Core block",
            name
        );
        assert!(
            out.rust.contains("use super::*;"),
            "Rust {}: missing use super::* import",
            name
        );
    }
}

// ---------------------------------------------------------------------------
// 11. WMA-specific: verify lookback uses optInTimePeriod
// ---------------------------------------------------------------------------

#[test]
fn test_wma_lookback_uses_time_period() {
    let (func, enums) = load_indicator("wma");
    let out = generate_all(&func, &enums);

    assert!(
        out.c.contains("optInTimePeriod"),
        "C WMA should reference optInTimePeriod"
    );
    assert!(
        out.rust.contains("optInTimePeriod"),
        "Rust WMA should reference optInTimePeriod"
    );
    assert!(
        out.java.contains("optInTimePeriod"),
        "Java WMA should reference optInTimePeriod"
    );
}

// ---------------------------------------------------------------------------
// 12. MA has 2 optional inputs (timePeriod + MAType enum)
// ---------------------------------------------------------------------------

#[test]
fn test_ma_has_two_optional_inputs() {
    let (func, _enums) = load_indicator("ma");
    assert_eq!(
        func.optional_inputs.len(),
        2,
        "MA should have 2 optional inputs"
    );

    // One should be an enum type
    let has_enum = func
        .optional_inputs
        .iter()
        .any(|opt| matches!(opt.param_type, ir::ParamType::Enum(_)));
    assert!(has_enum, "MA should have an enum optional input (MAType)");
}

// ---------------------------------------------------------------------------
// 13. Validate TA_SUCCESS / RetCode::Success presence in function bodies
// ---------------------------------------------------------------------------

#[test]
fn test_c_outputs_contain_ta_success() {
    let indicators = ["sma", "rsi", "ema", "wma", "ma", "mult"];
    for name in &indicators {
        let (func, enums) = load_indicator(name);
        let out = generate_all(&func, &enums);
        assert!(
            out.c.contains("TA_SUCCESS"),
            "C {}: missing TA_SUCCESS return",
            name
        );
    }
}

#[test]
fn test_rust_outputs_contain_retcode_success() {
    let indicators = ["sma", "rsi", "ema", "wma", "ma", "mult"];
    for name in &indicators {
        let (func, enums) = load_indicator(name);
        let out = generate_all(&func, &enums);
        assert!(
            out.rust.contains("RetCode::Success"),
            "Rust {}: missing RetCode::Success return",
            name
        );
    }
}

#[test]
fn test_java_outputs_contain_retcode_success() {
    let indicators = ["sma", "rsi", "ema", "wma", "ma", "mult"];
    for name in &indicators {
        let (func, enums) = load_indicator(name);
        let out = generate_all(&func, &enums);
        assert!(
            out.java.contains("RetCode.Success"),
            "Java {}: missing RetCode.Success return",
            name
        );
    }
}
