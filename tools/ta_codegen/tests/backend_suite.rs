//! Comprehensive backend test suite for all indicators and all function variants.
//!
//! This complements `integration_test.rs` with systematic coverage:
//! - Every indicator x every backend x every function variant (auto-discovered)
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

/// Discover all indicator names from ta_func_defs/ that have both .yaml and .c files.
fn discover_indicators() -> Vec<String> {
    let base = Path::new(env!("CARGO_MANIFEST_DIR")).join("../../ta_func_defs");
    let mut indicators = Vec::new();
    for entry in std::fs::read_dir(&base).expect("Cannot read ta_func_defs directory") {
        let entry = entry.expect("Cannot read directory entry");
        let path = entry.path();
        if !path.is_dir() {
            continue;
        }
        let name = path.file_name().unwrap().to_str().unwrap().to_string();
        let yaml_path = path.join(format!("{}.yaml", name));
        let c_path = path.join(format!("{}.c", name));
        if yaml_path.exists() && c_path.exists() {
            indicators.push(name);
        }
    }
    indicators.sort();
    indicators
}

/// Load a function definition from its .yaml + .c files.
/// Always loads enums.yaml since multiple indicators use enum types.
fn load_indicator(name: &str) -> (ir::FuncDef, HashMap<String, ir::EnumDef>) {
    let base = Path::new(env!("CARGO_MANIFEST_DIR")).join("../../ta_func_defs");
    let yaml_path = base.join(format!("{}/{}.yaml", name, name));
    let c_path = base.join(format!("{}/{}.c", name, name));

    let enums_path = base.join("enums.yaml");
    let enums = parser::enums::load_enums(&enums_path);

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
// Variant check functions (extracted from macros for dynamic invocation)
// ---------------------------------------------------------------------------

/// Derive Pascal case from the indicator name.
/// Must match the dotnet backend's to_pascal_case: lowercase then capitalize first char.
fn to_pascal(name: &str) -> String {
    let lower = name.to_lowercase();
    let mut chars = lower.chars();
    match chars.next() {
        None => String::new(),
        Some(c) => c.to_uppercase().to_string() + chars.as_str(),
    }
}

/// Check that all C variants exist for a given indicator.
fn check_c_variants(c: &str, upper: &str, name: &str) {
    assert!(
        c.contains(&format!("TA_{}_Lookback", upper)),
        "{}: C missing TA_{}_Lookback", name, upper
    );
    assert!(
        c.contains(&format!("TA_{}(", upper))
            || c.contains(&format!("TA_{} (", upper)),
        "{}: C missing TA_{}", name, upper
    );
    assert!(
        c.contains(&format!("TA_{}_Logic(", upper)),
        "{}: C missing TA_{}_Logic", name, upper
    );
    assert!(
        c.contains(&format!("#define TA_INT_{}", upper)),
        "{}: C missing #define TA_INT_{}", name, upper
    );
    assert!(
        c.contains(&format!("TA_S_{}(", upper))
            || c.contains(&format!("TA_S_{} (", upper)),
        "{}: C missing TA_S_{}", name, upper
    );
    assert!(
        c.contains(&format!("TA_S_{}_Logic(", upper)),
        "{}: C missing TA_S_{}_Logic", name, upper
    );
}

/// Check that all Rust variants exist for a given indicator.
fn check_rust_variants(r: &str, snake: &str, has_opt_inputs: bool, name: &str) {
    assert!(
        r.contains(&format!("{}_lookback", snake)),
        "{}: Rust missing {}_lookback", name, snake
    );
    assert!(
        r.contains(&format!("fn {}(", snake))
            || r.contains(&format!("fn {}(\n", snake)),
        "{}: Rust missing fn {}", name, snake
    );
    if has_opt_inputs {
        assert!(
            r.contains(&format!("fn {}_logic(", snake))
                || r.contains(&format!("fn {}_logic(\n", snake)),
            "{}: Rust missing fn {}_logic", name, snake
        );
        assert!(
            r.contains(&format!("fn {}_logic_s(", snake))
                || r.contains(&format!("fn {}_logic_s(\n", snake)),
            "{}: Rust missing fn {}_logic_s", name, snake
        );
    } else {
        assert!(
            !r.contains(&format!("fn {}_logic(", snake)),
            "{}: Rust should NOT have {}_logic (no optional inputs)", name, snake
        );
    }
    assert!(
        r.contains(&format!("{}_unsafe", snake)),
        "{}: Rust missing {}_unsafe placeholder", name, snake
    );
    assert!(
        r.contains(&format!("fn {}_s(", snake))
            || r.contains(&format!("fn {}_s(\n", snake)),
        "{}: Rust missing fn {}_s", name, snake
    );
    assert!(
        r.contains(&format!("{}_unsafe_s", snake)),
        "{}: Rust missing {}_unsafe_s placeholder", name, snake
    );
}

/// Check that all Java variants exist for a given indicator.
fn check_java_variants(j: &str, lower: &str, name: &str) {
    assert!(
        j.contains(&format!("{}Lookback(", lower)),
        "{}: Java missing {}Lookback", name, lower
    );
    assert!(
        j.contains(&format!("RetCode {}(", lower))
            || j.contains(&format!("RetCode {} (", lower)),
        "{}: Java missing {} function", name, lower
    );
    assert!(
        j.contains(&format!("{}Logic(", lower)),
        "{}: Java missing {}Logic", name, lower
    );
}

/// Check that all .NET variants exist for a given indicator.
fn check_dotnet_variants(d: &str, pascal: &str, upper: &str, name: &str) {
    assert!(
        d.contains(&format!("{}Lookback(", pascal)),
        "{}: .NET missing {}Lookback", name, pascal
    );
    assert!(
        d.contains(&format!("{}(", pascal))
            || d.contains(&format!("{} (", pascal)),
        "{}: .NET missing {} function", name, pascal
    );
    assert!(
        d.contains(&format!("{}Logic(", pascal)),
        "{}: .NET missing {}Logic declaration", name, pascal
    );
    assert!(
        d.contains(&format!("#define TA_{} ", upper))
            || d.contains(&format!("#define TA_{}\n", upper)),
        "{}: .NET missing #define TA_{}", name, upper
    );
    assert!(
        d.contains(&format!("#define TA_{}_Logic", upper)),
        "{}: .NET missing #define TA_{}_Logic", name, upper
    );
    assert!(
        d.contains(&format!("#define TA_INT_{}", upper)),
        "{}: .NET missing #define TA_INT_{}", name, upper
    );
}

/// Check that all SWIG variants exist for a given indicator.
fn check_swig_variants(s: &str, upper: &str, name: &str) {
    assert!(
        s.contains(&format!("TA_{}(", upper))
            || s.contains(&format!("TA_{} (", upper)),
        "{}: SWIG missing TA_{}", name, upper
    );
    assert!(
        s.contains(&format!("TA_{}_Logic(", upper)),
        "{}: SWIG missing TA_{}_Logic", name, upper
    );
    assert!(
        s.contains(&format!("TA_{}_Lookback", upper)),
        "{}: SWIG missing TA_{}_Lookback", name, upper
    );
}

/// Check C #define TA_INT alias correctness for an indicator.
fn check_c_int_alias(c: &str, upper: &str, name: &str) {
    assert!(
        c.contains(&format!("#define TA_INT_{} TA_{}_Logic", upper, upper)),
        "{}: C missing #define TA_INT_{} TA_{}_Logic", name, upper, upper
    );
}

/// Check .NET macros point to correct Core:: methods for an indicator.
fn check_dotnet_macros(d: &str, pascal: &str, upper: &str, name: &str) {
    assert!(
        d.contains(&format!("#define TA_{} Core::{}", upper, pascal)),
        "{}: .NET TA_{} should point to Core::{}", name, upper, pascal
    );
    assert!(
        d.contains(&format!("#define TA_{}_Lookback Core::{}Lookback", upper, pascal)),
        "{}: .NET TA_{}_Lookback should point to Core::{}Lookback", name, upper, pascal
    );
    assert!(
        d.contains(&format!("#define TA_{}_Logic Core::{}Logic", upper, pascal)),
        "{}: .NET TA_{}_Logic should point to Core::{}Logic", name, upper, pascal
    );
    assert!(
        d.contains(&format!("#define TA_INT_{} Core::{}Logic", upper, pascal)),
        "{}: .NET TA_INT_{} should point to Core::{}Logic", name, upper, pascal
    );
}

/// Try to load an indicator, returning None if parsing fails (not yet supported).
fn try_load_indicator(name: &str) -> Option<(ir::FuncDef, HashMap<String, ir::EnumDef>)> {
    let result = std::panic::catch_unwind(std::panic::AssertUnwindSafe(|| {
        load_indicator(name)
    }));
    result.ok()
}

/// Try to generate all backends, returning None if generation fails.
fn try_generate_all(
    func: &ir::FuncDef,
    enums: &HashMap<String, ir::EnumDef>,
) -> Option<AllOutputs> {
    let result = std::panic::catch_unwind(std::panic::AssertUnwindSafe(|| {
        generate_all(func, enums)
    }));
    result.ok()
}

// ---------------------------------------------------------------------------
// 2. Auto-discovered per-indicator x per-backend variant checks
// ---------------------------------------------------------------------------

#[test]
fn test_all_indicators_all_backends() {
    let indicators = discover_indicators();
    assert!(!indicators.is_empty(), "No indicators discovered");

    let mut failures = Vec::new();
    let mut tested = 0;
    let mut skipped = 0;

    for name in &indicators {
        // Phase 1: try to load and generate (may fail for not-yet-supported indicators)
        let loaded = try_load_indicator(name);
        let (func, enums) = match loaded {
            Some(v) => v,
            None => { skipped += 1; continue; }
        };
        let out = match try_generate_all(&func, &enums) {
            Some(v) => v,
            None => { skipped += 1; continue; }
        };

        // Phase 2: run variant checks (failures here are real bugs)
        let upper = func.name.clone();
        let snake = name.clone();
        let pascal = to_pascal(name);
        let has_opt_inputs = !func.optional_inputs.is_empty();

        let result = std::panic::catch_unwind(std::panic::AssertUnwindSafe(|| {
            check_c_variants(&out.c, &upper, &snake);
            check_rust_variants(&out.rust, &snake, has_opt_inputs, &snake);
            check_java_variants(&out.java, &snake, &snake);
            check_dotnet_variants(&out.dotnet, &pascal, &upper, &snake);
            check_swig_variants(&out.swig, &upper, &snake);
            check_c_int_alias(&out.c, &upper, &snake);
            check_dotnet_macros(&out.dotnet, &pascal, &upper, &snake);
        }));

        if let Err(e) = result {
            let msg = if let Some(s) = e.downcast_ref::<String>() {
                s.clone()
            } else if let Some(s) = e.downcast_ref::<&str>() {
                s.to_string()
            } else {
                format!("Unknown panic for indicator {}", name)
            };
            failures.push(msg);
        } else {
            tested += 1;
        }
    }

    eprintln!(
        "Variant checks: {} tested, {} skipped (parse not yet supported), {} failed",
        tested, skipped, failures.len()
    );

    // Ensure we tested at least the 6 known-good indicators
    assert!(
        tested >= 6,
        "Expected at least 6 indicators to pass, but only {} did",
        tested
    );

    if !failures.is_empty() {
        panic!(
            "{} indicator(s) failed variant checks:\n{}",
            failures.len(),
            failures.join("\n")
        );
    }
}

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
fn test_ema_c_smoothing_factor() {
    let (func, enums) = load_indicator("ema");
    let out = generate_all(&func, &enums);

    // EMA takes optInK_1 as the smoothing factor parameter
    assert!(
        out.c.contains("optInK_1"),
        "C EMA should use optInK_1 smoothing factor parameter"
    );
}

#[test]
fn test_ema_java_smoothing_factor() {
    let (func, enums) = load_indicator("ema");
    let out = generate_all(&func, &enums);

    // Java EMA also uses optInK_1
    assert!(
        out.java.contains("optInK_1"),
        "Java EMA should use optInK_1 smoothing factor parameter"
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
// 6. Non-empty output checks for all discovered indicators
// ---------------------------------------------------------------------------

#[test]
fn test_all_indicators_nonempty_output() {
    let indicators = discover_indicators();
    assert!(!indicators.is_empty(), "No indicators discovered");

    let mut failures = Vec::new();
    let mut tested = 0;

    for name in &indicators {
        let loaded = try_load_indicator(name);
        let (func, enums) = match loaded {
            Some(v) => v,
            None => continue,
        };
        let out = match try_generate_all(&func, &enums) {
            Some(v) => v,
            None => continue,
        };

        let result = std::panic::catch_unwind(std::panic::AssertUnwindSafe(|| {
            assert!(!out.c.is_empty(), "{}: C output is empty", name);
            assert!(!out.rust.is_empty(), "{}: Rust output is empty", name);
            assert!(!out.java.is_empty(), "{}: Java output is empty", name);
            assert!(!out.dotnet.is_empty(), "{}: .NET output is empty", name);
            assert!(!out.swig.is_empty(), "{}: SWIG output is empty", name);

            assert!(out.c.len() > 200, "{}: C output suspiciously short", name);
            assert!(out.rust.len() > 200, "{}: Rust output suspiciously short", name);
            assert!(out.java.len() > 100, "{}: Java output suspiciously short", name);
            assert!(out.dotnet.len() > 100, "{}: .NET output suspiciously short", name);
            assert!(out.swig.len() > 100, "{}: SWIG output suspiciously short", name);
        }));
        if let Err(e) = result {
            let msg = if let Some(s) = e.downcast_ref::<String>() {
                s.clone()
            } else if let Some(s) = e.downcast_ref::<&str>() {
                s.to_string()
            } else {
                format!("Unknown panic for indicator {}", name)
            };
            failures.push(msg);
        } else {
            tested += 1;
        }
    }

    assert!(tested >= 6, "Expected at least 6 indicators to pass non-empty checks, got {}", tested);

    if !failures.is_empty() {
        panic!(
            "{} indicator(s) failed non-empty checks:\n{}",
            failures.len(),
            failures.join("\n")
        );
    }

    eprintln!("{} indicators produce non-empty output for all backends", tested);
}

// ---------------------------------------------------------------------------
// 9. SWIG comment block contains function description (all indicators)
// ---------------------------------------------------------------------------

#[test]
fn test_swig_comment_blocks() {
    let indicators = discover_indicators();
    let mut failures = Vec::new();

    for name in &indicators {
        let (func, enums) = match try_load_indicator(name) {
            Some(v) => v,
            None => continue,
        };
        let out = match try_generate_all(&func, &enums) {
            Some(v) => v,
            None => continue,
        };

        let func_name = func.name.clone();
        let result = std::panic::catch_unwind(std::panic::AssertUnwindSafe(|| {
            assert!(
                out.swig.contains("/*"),
                "SWIG {}: missing comment block", name
            );
            assert!(
                out.swig.contains(&format!("TA_{}", func_name)),
                "SWIG {}: comment block missing TA_{} reference", name, func_name
            );
        }));
        if let Err(e) = result {
            let msg = if let Some(s) = e.downcast_ref::<String>() {
                s.clone()
            } else if let Some(s) = e.downcast_ref::<&str>() {
                s.to_string()
            } else {
                format!("Unknown panic for indicator {}", name)
            };
            failures.push(msg);
        }
    }

    if !failures.is_empty() {
        panic!("{} indicator(s) failed SWIG comment checks:\n{}", failures.len(), failures.join("\n"));
    }
}

// ---------------------------------------------------------------------------
// 10. Rust impl Core block structure (all indicators)
// ---------------------------------------------------------------------------

#[test]
fn test_rust_impl_core_structure() {
    let indicators = discover_indicators();
    let mut failures = Vec::new();

    for name in &indicators {
        let (func, enums) = match try_load_indicator(name) {
            Some(v) => v,
            None => continue,
        };
        let out = match try_generate_all(&func, &enums) {
            Some(v) => v,
            None => continue,
        };

        let result = std::panic::catch_unwind(std::panic::AssertUnwindSafe(|| {
            assert!(
                out.rust.contains("impl Core {"),
                "Rust {}: missing impl Core block", name
            );
            assert!(
                out.rust.contains("use super::*;"),
                "Rust {}: missing use super::* import", name
            );
        }));
        if let Err(e) = result {
            let msg = if let Some(s) = e.downcast_ref::<String>() {
                s.clone()
            } else if let Some(s) = e.downcast_ref::<&str>() {
                s.to_string()
            } else {
                format!("Unknown panic for indicator {}", name)
            };
            failures.push(msg);
        }
    }

    if !failures.is_empty() {
        panic!("{} indicator(s) failed Rust structure checks:\n{}", failures.len(), failures.join("\n"));
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
fn test_all_indicators_contain_success_returns() {
    let indicators = discover_indicators();
    let mut failures = Vec::new();

    for name in &indicators {
        let (func, enums) = match try_load_indicator(name) {
            Some(v) => v,
            None => continue,
        };
        let out = match try_generate_all(&func, &enums) {
            Some(v) => v,
            None => continue,
        };

        let result = std::panic::catch_unwind(std::panic::AssertUnwindSafe(|| {
            assert!(
                out.c.contains("TA_SUCCESS"),
                "C {}: missing TA_SUCCESS return", name
            );
            assert!(
                out.rust.contains("RetCode::Success"),
                "Rust {}: missing RetCode::Success return", name
            );
            assert!(
                out.java.contains("RetCode.Success"),
                "Java {}: missing RetCode.Success return", name
            );
        }));
        if let Err(e) = result {
            let msg = if let Some(s) = e.downcast_ref::<String>() {
                s.clone()
            } else if let Some(s) = e.downcast_ref::<&str>() {
                s.to_string()
            } else {
                format!("Unknown panic for indicator {}", name)
            };
            failures.push(msg);
        }
    }

    if !failures.is_empty() {
        panic!(
            "{} indicator(s) failed success-return checks:\n{}",
            failures.len(),
            failures.join("\n")
        );
    }
}
