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
        "{}: C missing TA_{}_Lookback",
        name,
        upper
    );
    assert!(
        c.contains(&format!("TA_{}(", upper)) || c.contains(&format!("TA_{} (", upper)),
        "{}: C missing TA_{}",
        name,
        upper
    );
    assert!(
        c.contains(&format!("TA_{}_Logic(", upper)),
        "{}: C missing TA_{}_Logic",
        name,
        upper
    );
    assert!(
        c.contains(&format!("#define TA_INT_{}", upper)),
        "{}: C missing #define TA_INT_{}",
        name,
        upper
    );
    assert!(
        c.contains(&format!("TA_S_{}(", upper)) || c.contains(&format!("TA_S_{} (", upper)),
        "{}: C missing TA_S_{}",
        name,
        upper
    );
    assert!(
        c.contains(&format!("TA_S_{}_Logic(", upper)),
        "{}: C missing TA_S_{}_Logic",
        name,
        upper
    );
}

/// Check that all Rust generic variants exist for a given indicator.
fn check_rust_generic_variants(r: &str, snake: &str, name: &str) {
    // Lookback (non-generic)
    assert!(
        r.contains(&format!("{}_lookback", snake)),
        "{}: Rust missing {}_lookback",
        name,
        snake
    );
    // Guarded generic
    assert!(
        r.contains(&format!("fn {}<T: TaFloat>", snake)),
        "{}: Rust missing fn {}<T: TaFloat>",
        name,
        snake
    );
    // Unguarded generic (real algorithm, bounds-checked)
    assert!(
        r.contains(&format!("fn {}_unguarded<T: TaFloat>", snake)),
        "{}: Rust missing fn {}_unguarded<T: TaFloat>",
        name,
        snake
    );
    // Unchecked guarded (unsafe)
    assert!(
        r.contains(&format!("fn {}_unchecked<T: TaFloat>", snake)),
        "{}: Rust missing fn {}_unchecked<T: TaFloat>",
        name,
        snake
    );
    // Unguarded unchecked (unsafe, real algorithm)
    assert!(
        r.contains(&format!("fn {}_unguarded_unchecked<T: TaFloat>", snake)),
        "{}: Rust missing fn {}_unguarded_unchecked<T: TaFloat>",
        name,
        snake
    );
}

/// Check that all Java variants exist for a given indicator.
fn check_java_variants(j: &str, lower: &str, name: &str) {
    assert!(
        j.contains(&format!("{}Lookback(", lower)),
        "{}: Java missing {}Lookback",
        name,
        lower
    );
    assert!(
        j.contains(&format!("RetCode {}(", lower)) || j.contains(&format!("RetCode {} (", lower)),
        "{}: Java missing {} function",
        name,
        lower
    );
    assert!(
        j.contains(&format!("{}Logic(", lower)),
        "{}: Java missing {}Logic",
        name,
        lower
    );
}

/// Check that all .NET variants exist for a given indicator.
fn check_dotnet_variants(d: &str, pascal: &str, upper: &str, name: &str) {
    assert!(
        d.contains(&format!("{}Lookback(", pascal)),
        "{}: .NET missing {}Lookback",
        name,
        pascal
    );
    assert!(
        d.contains(&format!("{}(", pascal)) || d.contains(&format!("{} (", pascal)),
        "{}: .NET missing {} function",
        name,
        pascal
    );
    assert!(
        d.contains(&format!("{}Logic(", pascal)),
        "{}: .NET missing {}Logic declaration",
        name,
        pascal
    );
    assert!(
        d.contains(&format!("#define TA_{} ", upper))
            || d.contains(&format!("#define TA_{}\n", upper)),
        "{}: .NET missing #define TA_{}",
        name,
        upper
    );
    assert!(
        d.contains(&format!("#define TA_{}_Logic", upper)),
        "{}: .NET missing #define TA_{}_Logic",
        name,
        upper
    );
    assert!(
        d.contains(&format!("#define TA_INT_{}", upper)),
        "{}: .NET missing #define TA_INT_{}",
        name,
        upper
    );
}

/// Check that all SWIG variants exist for a given indicator.
fn check_swig_variants(s: &str, upper: &str, name: &str) {
    assert!(
        s.contains(&format!("TA_{}(", upper)) || s.contains(&format!("TA_{} (", upper)),
        "{}: SWIG missing TA_{}",
        name,
        upper
    );
    assert!(
        s.contains(&format!("TA_{}_Logic(", upper)),
        "{}: SWIG missing TA_{}_Logic",
        name,
        upper
    );
    assert!(
        s.contains(&format!("TA_{}_Lookback", upper)),
        "{}: SWIG missing TA_{}_Lookback",
        name,
        upper
    );
}

/// Check C #define TA_INT alias correctness for an indicator.
fn check_c_int_alias(c: &str, upper: &str, name: &str) {
    assert!(
        c.contains(&format!("#define TA_INT_{} TA_{}_Logic", upper, upper)),
        "{}: C missing #define TA_INT_{} TA_{}_Logic",
        name,
        upper,
        upper
    );
}

/// Check .NET macros point to correct Core:: methods for an indicator.
fn check_dotnet_macros(d: &str, pascal: &str, upper: &str, name: &str) {
    assert!(
        d.contains(&format!("#define TA_{} Core::{}", upper, pascal)),
        "{}: .NET TA_{} should point to Core::{}",
        name,
        upper,
        pascal
    );
    assert!(
        d.contains(&format!(
            "#define TA_{}_Lookback Core::{}Lookback",
            upper, pascal
        )),
        "{}: .NET TA_{}_Lookback should point to Core::{}Lookback",
        name,
        upper,
        pascal
    );
    assert!(
        d.contains(&format!("#define TA_{}_Logic Core::{}Logic", upper, pascal)),
        "{}: .NET TA_{}_Logic should point to Core::{}Logic",
        name,
        upper,
        pascal
    );
    assert!(
        d.contains(&format!("#define TA_INT_{} Core::{}Logic", upper, pascal)),
        "{}: .NET TA_INT_{} should point to Core::{}Logic",
        name,
        upper,
        pascal
    );
}

/// Try to load an indicator, returning None if parsing fails (not yet supported).
fn try_load_indicator(name: &str) -> Option<(ir::FuncDef, HashMap<String, ir::EnumDef>)> {
    let result = std::panic::catch_unwind(std::panic::AssertUnwindSafe(|| load_indicator(name)));
    result.ok()
}

/// Try to generate all backends, returning None if generation fails.
fn try_generate_all(
    func: &ir::FuncDef,
    enums: &HashMap<String, ir::EnumDef>,
) -> Option<AllOutputs> {
    let result =
        std::panic::catch_unwind(std::panic::AssertUnwindSafe(|| generate_all(func, enums)));
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
            None => {
                skipped += 1;
                continue;
            }
        };
        let out = match try_generate_all(&func, &enums) {
            Some(v) => v,
            None => {
                skipped += 1;
                continue;
            }
        };

        // Phase 2: run variant checks (failures here are real bugs)
        let upper = func.name.clone();
        let snake = name.clone();
        let pascal = to_pascal(name);

        let result = std::panic::catch_unwind(std::panic::AssertUnwindSafe(|| {
            check_c_variants(&out.c, &upper, &snake);
            check_rust_generic_variants(&out.rust, &snake, &snake);
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
        tested,
        skipped,
        failures.len()
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

    // In Rust, cross-calls use self.{name}_unguarded for the algorithm
    assert!(
        r.contains("self.sma_lookback("),
        "Rust: MA should call self.sma_lookback"
    );
    assert!(
        r.contains("self.ema_lookback("),
        "Rust: MA should call self.ema_lookback"
    );
    assert!(
        r.contains("self.sma_unguarded("),
        "Rust: MA should call self.sma_unguarded"
    );
    assert!(
        r.contains("self.ema_unguarded("),
        "Rust: MA should call self.ema_unguarded"
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

    // The guarded Rust function delegates to _unguarded, but first validates params.
    let guarded = extract_section(
        &out.rust,
        "pub fn sma<T: TaFloat>",
        "pub fn sma_unguarded<T: TaFloat>",
    );
    assert!(
        guarded.contains("endIdx < startIdx"),
        "Rust guarded SMA should have endIdx < startIdx check"
    );
}

#[test]
fn test_rust_sma_unguarded_omits_validation() {
    let (func, enums) = load_indicator("sma");
    let out = generate_all(&func, &enums);

    // The unguarded function should not have the range check
    let unguarded_start = out
        .rust
        .find("pub fn sma_unguarded<T: TaFloat>")
        .expect("Missing sma_unguarded");
    let unguarded_section = &out.rust[unguarded_start..];
    let end = unguarded_section
        .find("pub unsafe fn sma_unchecked")
        .unwrap_or(unguarded_section.len());
    let unguarded = &unguarded_section[..end];
    assert!(
        !unguarded.contains("OutOfRangeStartIndex"),
        "Rust unguarded SMA should NOT have range validation"
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
    // TA_IS_ZERO was expanded in source to its inline form by replace_macros.py
    assert!(
        out.c.contains("-0.00000001"),
        "C RSI should use inline zero-check (TA_IS_ZERO was expanded)"
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
            assert!(
                out.rust.len() > 200,
                "{}: Rust output suspiciously short",
                name
            );
            assert!(
                out.java.len() > 100,
                "{}: Java output suspiciously short",
                name
            );
            assert!(
                out.dotnet.len() > 100,
                "{}: .NET output suspiciously short",
                name
            );
            assert!(
                out.swig.len() > 100,
                "{}: SWIG output suspiciously short",
                name
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
        } else {
            tested += 1;
        }
    }

    assert!(
        tested >= 6,
        "Expected at least 6 indicators to pass non-empty checks, got {}",
        tested
    );

    if !failures.is_empty() {
        panic!(
            "{} indicator(s) failed non-empty checks:\n{}",
            failures.len(),
            failures.join("\n")
        );
    }

    eprintln!(
        "{} indicators produce non-empty output for all backends",
        tested
    );
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
                "SWIG {}: missing comment block",
                name
            );
            assert!(
                out.swig.contains(&format!("TA_{}", func_name)),
                "SWIG {}: comment block missing TA_{} reference",
                name,
                func_name
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
            "{} indicator(s) failed SWIG comment checks:\n{}",
            failures.len(),
            failures.join("\n")
        );
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
                "Rust {}: missing impl Core block",
                name
            );
            assert!(
                out.rust.contains("use super::*;"),
                "Rust {}: missing use super::* import",
                name
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
            "{} indicator(s) failed Rust structure checks:\n{}",
            failures.len(),
            failures.join("\n")
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
                "C {}: missing TA_SUCCESS return",
                name
            );
            assert!(
                out.rust.contains("RetCode::Success"),
                "Rust {}: missing RetCode::Success return",
                name
            );
            assert!(
                out.java.contains("RetCode.Success"),
                "Java {}: missing RetCode.Success return",
                name
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

// ---------------------------------------------------------------------------
// Rust generic output smoke test
// ---------------------------------------------------------------------------

#[test]
fn test_rust_generic_output_smoke() {
    let (func, enums) = load_indicator("sma");
    let out = generate_all(&func, &enums);
    let r = &out.rust;

    // 1. Generic signatures present
    assert!(
        r.contains("<T: TaFloat>"),
        "Rust SMA should use generic <T: TaFloat> signatures"
    );

    // 2. No _s suffix methods
    assert!(
        !r.contains("fn sma_s(") && !r.contains("fn sma_s<"),
        "Rust SMA should NOT contain _s suffixed methods"
    );

    // 3. Output params use generic T
    assert!(
        r.contains("&mut [T]"),
        "Rust SMA output params should use generic type &mut [T]"
    );

    // 4. Input params use generic T
    assert!(
        r.contains("&[T]"),
        "Rust SMA input params should use generic type &[T]"
    );

    // 5. No f64-specific function signatures (except lookback which is non-generic)
    // The guarded/unguarded/unchecked functions should NOT have f64 in their signature
    assert!(
        !r.contains("fn sma(&self") && !r.contains("pub fn sma(&self"),
        "Rust SMA should use generic signature, not concrete f64"
    );

    // 6. Verify also for an indicator with optional Real inputs (if any exist)
    // For now SMA is sufficient as it covers the common case
}

// ---------------------------------------------------------------------------
// ForC init/update Block rendering: comma-separated, not semicolons
// ---------------------------------------------------------------------------

#[test]
fn c_for_loop_multi_init_comma_separated() {
    use ta_codegen_lib::ir::*;

    // Build synthetic ForC: for(j=0, i=startIdx; i<=endIdx; i=i+1, j=j+1)
    let init = Box::new(Statement::Block {
        body: vec![
            Statement::Assign {
                target: Expr::Var("j".into()),
                value: Expr::Literal(0.0),
                compound: false,
            },
            Statement::Assign {
                target: Expr::Var("i".into()),
                value: Expr::Var("startIdx".into()),
                compound: false,
            },
        ],
    });
    let condition = Expr::BinOp(
        Box::new(Expr::Var("i".into())),
        BinOp::LessEq,
        Box::new(Expr::Var("endIdx".into())),
    );
    let update = Box::new(Statement::Block {
        body: vec![
            Statement::Assign {
                target: Expr::Var("i".into()),
                value: Expr::BinOp(
                    Box::new(Expr::Var("i".into())),
                    BinOp::Add,
                    Box::new(Expr::Literal(1.0)),
                ),
                compound: false,
            },
            Statement::Assign {
                target: Expr::Var("j".into()),
                value: Expr::BinOp(
                    Box::new(Expr::Var("j".into())),
                    BinOp::Add,
                    Box::new(Expr::Literal(1.0)),
                ),
                compound: false,
            },
        ],
    });
    let stmt = Statement::ForC {
        init,
        condition,
        update,
        body: vec![],
    };

    let enums = HashMap::new();
    let registry = make_registry();
    let rendered = backends::c::render_statement(&stmt, 0, false, &enums, &registry);

    // Should produce: for( j = 0, i = startIdx; ... ; i = i + 1, j = j + 1 )
    // NOT: for( j = 0;\ni = startIdx; ... )
    assert!(
        !rendered.contains(";\n"),
        "ForC init/update should use commas, not semicolons: {rendered}"
    );
    assert!(
        rendered.contains(", "),
        "ForC init/update should be comma-separated: {rendered}"
    );
}

#[test]
fn java_for_loop_multi_init_comma_separated() {
    use ta_codegen_lib::ir::*;

    // Build synthetic ForC: for(j=0, i=startIdx; i<=endIdx; i=i+1, j=j+1)
    let init = Box::new(Statement::Block {
        body: vec![
            Statement::Assign {
                target: Expr::Var("j".into()),
                value: Expr::Literal(0.0),
                compound: false,
            },
            Statement::Assign {
                target: Expr::Var("i".into()),
                value: Expr::Var("startIdx".into()),
                compound: false,
            },
        ],
    });
    let condition = Expr::BinOp(
        Box::new(Expr::Var("i".into())),
        BinOp::LessEq,
        Box::new(Expr::Var("endIdx".into())),
    );
    let update = Box::new(Statement::Block {
        body: vec![
            Statement::Assign {
                target: Expr::Var("i".into()),
                value: Expr::BinOp(
                    Box::new(Expr::Var("i".into())),
                    BinOp::Add,
                    Box::new(Expr::Literal(1.0)),
                ),
                compound: false,
            },
            Statement::Assign {
                target: Expr::Var("j".into()),
                value: Expr::BinOp(
                    Box::new(Expr::Var("j".into())),
                    BinOp::Add,
                    Box::new(Expr::Literal(1.0)),
                ),
                compound: false,
            },
        ],
    });
    let stmt = Statement::ForC {
        init,
        condition,
        update,
        body: vec![],
    };

    let enums = HashMap::new();
    let registry = make_registry();
    let rendered = backends::java::render_statement(&stmt, 0, false, &enums, &registry);

    // Should produce: for( j = 0, i = startIdx; ... ; i = i + 1, j = j + 1 )
    // NOT: for( j = 0;\ni = startIdx; ... )
    assert!(
        !rendered.contains(";\n"),
        "Java ForC init/update should use commas, not semicolons: {rendered}"
    );
    assert!(
        rendered.contains(", "),
        "Java ForC init/update should be comma-separated: {rendered}"
    );
}

// ---------------------------------------------------------------------------
// Rust ForC range iteration optimization
// ---------------------------------------------------------------------------

#[test]
fn rust_forc_emits_range_iteration_when_possible() {
    use ta_codegen_lib::backends::rust_lang::{render_statement, RustRenderCtx};
    use ta_codegen_lib::ir::*;

    // Build synthetic ForC: for(i=startIdx; i<=endIdx; i++)
    // Single counter, <= condition, simple increment by 1
    let init = Box::new(Statement::Assign {
        target: Expr::Var("i".into()),
        value: Expr::Var("startIdx".into()),
        compound: false,
    });
    let condition = Expr::BinOp(
        Box::new(Expr::Var("i".into())),
        BinOp::LessEq,
        Box::new(Expr::Var("endIdx".into())),
    );
    let update = Box::new(Statement::Assign {
        target: Expr::Var("i".into()),
        value: Expr::BinOp(
            Box::new(Expr::Var("i".into())),
            BinOp::Add,
            Box::new(Expr::IntLiteral(1)),
        ),
        compound: false,
    });
    let stmt = Statement::ForC {
        init,
        condition,
        update,
        body: vec![],
    };

    let ctx = RustRenderCtx::concrete();
    let for_loop_vars: Vec<String> = vec![];
    let var_inits: std::collections::HashMap<String, &Expr> = std::collections::HashMap::new();
    let output_names: Vec<String> = vec![];
    let opt_real_params: Vec<String> = vec![];
    let enums = HashMap::new();
    let registry = make_registry();

    let rendered = render_statement(
        &stmt,
        0,
        &ctx,
        &for_loop_vars,
        &var_inits,
        &output_names,
        &opt_real_params,
        &enums,
        &registry,
    );

    assert!(
        rendered.contains("..="),
        "Simple ForC should emit range iteration: {rendered}"
    );
    assert!(
        !rendered.contains("while "),
        "Simple ForC should not fall through to while: {rendered}"
    );
}

// ---------------------------------------------------------------------------
// 14. SWIG naming alignment with C exports
// ---------------------------------------------------------------------------

/// Verify that every function name declared by the SWIG backend is also
/// exported by the C backend.  Specifically:
/// - `TA_{NAME}(` in SWIG → `TA_{NAME}(` in C
/// - `TA_{NAME}_Logic(` in SWIG → `TA_{NAME}_Logic(` in C
/// - `TA_{NAME}_Logic(` in SWIG → `#define TA_INT_{NAME}` in C (alias)
#[test]
fn swig_names_match_c_exports() {
    let indicators = discover_indicators();
    let registry = make_registry();
    let mut failures = Vec::new();

    for name in &indicators {
        let loaded = try_load_indicator(name);
        let (func, enums) = match loaded {
            Some(v) => v,
            None => continue,
        };

        let upper = func.name.clone();

        let c_out_result = std::panic::catch_unwind(std::panic::AssertUnwindSafe(|| {
            backends::c::generate(&func, &enums, &registry)
        }));
        let swig_out_result = std::panic::catch_unwind(std::panic::AssertUnwindSafe(|| {
            backends::swig::generate(&func, &enums, &registry)
        }));

        let (c_out, swig_out) = match (c_out_result, swig_out_result) {
            (Ok(c), Ok(s)) => (c, s),
            _ => continue,
        };

        let result = std::panic::catch_unwind(std::panic::AssertUnwindSafe(|| {
            // SWIG declares TA_{NAME} — C must export it
            if swig_out.contains(&format!("TA_{}(", upper)) {
                assert!(
                    c_out.contains(&format!("TA_{}(", upper))
                        || c_out.contains(&format!("TA_{} (", upper)),
                    "{}: SWIG declares TA_{} but C doesn't export it",
                    name,
                    upper
                );
            }

            // SWIG declares TA_{NAME}_Logic — C must export it and alias it via TA_INT_{NAME}
            if swig_out.contains(&format!("TA_{}_Logic(", upper)) {
                assert!(
                    c_out.contains(&format!("TA_{}_Logic(", upper)),
                    "{}: SWIG declares TA_{}_Logic but C doesn't export it",
                    name,
                    upper
                );
                assert!(
                    c_out.contains(&format!("#define TA_INT_{}", upper)),
                    "{}: SWIG declares TA_{}_Logic but C is missing #define TA_INT_{}",
                    name,
                    upper,
                    upper
                );
            }
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
            "{} indicator(s) failed SWIG/C naming alignment:\n{}",
            failures.len(),
            failures.join("\n")
        );
    }
}

// ---------------------------------------------------------------------------
// 15. HT_TRENDMODE: verify Hilbert transform macros parse and generate
// ---------------------------------------------------------------------------

#[test]
fn ht_trendmode_parses_and_generates() {
    let (func, enums) = load_indicator("ht_trendmode");
    let _outputs = generate_all(&func, &enums);
    // If we get here without panic, parsing and generation succeeded
}

#[test]
fn rust_forc_multi_init_falls_through_to_while() {
    use ta_codegen_lib::backends::rust_lang::{render_statement, RustRenderCtx};
    use ta_codegen_lib::ir::*;

    // Build ForC with multi-init Block — should NOT get range optimization
    let init = Box::new(Statement::Block {
        body: vec![
            Statement::Assign {
                target: Expr::Var("j".into()),
                value: Expr::Literal(0.0),
                compound: false,
            },
            Statement::Assign {
                target: Expr::Var("i".into()),
                value: Expr::Var("startIdx".into()),
                compound: false,
            },
        ],
    });
    let condition = Expr::BinOp(
        Box::new(Expr::Var("i".into())),
        BinOp::LessEq,
        Box::new(Expr::Var("endIdx".into())),
    );
    let update = Box::new(Statement::Block {
        body: vec![
            Statement::Assign {
                target: Expr::Var("i".into()),
                value: Expr::BinOp(
                    Box::new(Expr::Var("i".into())),
                    BinOp::Add,
                    Box::new(Expr::Literal(1.0)),
                ),
                compound: false,
            },
            Statement::Assign {
                target: Expr::Var("j".into()),
                value: Expr::BinOp(
                    Box::new(Expr::Var("j".into())),
                    BinOp::Add,
                    Box::new(Expr::Literal(1.0)),
                ),
                compound: false,
            },
        ],
    });
    let stmt = Statement::ForC {
        init,
        condition,
        update,
        body: vec![],
    };

    let ctx = RustRenderCtx::concrete();
    let for_loop_vars: Vec<String> = vec![];
    let var_inits: std::collections::HashMap<String, &Expr> = std::collections::HashMap::new();
    let output_names: Vec<String> = vec![];
    let opt_real_params: Vec<String> = vec![];
    let enums = HashMap::new();
    let registry = make_registry();

    let rendered = render_statement(
        &stmt,
        0,
        &ctx,
        &for_loop_vars,
        &var_inits,
        &output_names,
        &opt_real_params,
        &enums,
        &registry,
    );

    assert!(
        rendered.contains("while "),
        "Multi-init ForC should fall through to while: {rendered}"
    );
}

// ---------------------------------------------------------------------------
// 16. Math function idiomatic rendering per backend
// ---------------------------------------------------------------------------

#[test]
fn backends_render_max_min_fmax_fmin_abs() {
    use ta_codegen_lib::backends;
    use ta_codegen_lib::ir::{
        Expr, FuncDef, Input, LookbackExpr, Output, ParamType, Statement, VarType,
    };

    // Build a synthetic FuncDef whose body assigns each math function to a variable.
    // Variable a = max(x, y)
    // Variable b = min(x, y)
    // Variable c = fmax(x, y)
    // Variable d = fmin(x, y)
    // Variable e = ABS(x)
    let make_assign = |var: &str, func: &str, args: Vec<Expr>| Statement::Assign {
        target: Expr::Var(var.to_string()),
        value: Expr::FuncCall(func.to_string(), args),
        compound: false,
    };

    let x = Expr::Var("x".to_string());
    let y = Expr::Var("y".to_string());

    let body = vec![
        Statement::VarDecl {
            var_type: VarType::Real,
            name: "x".to_string(),
            init: Some(Expr::Literal(1.0)),
        },
        Statement::VarDecl {
            var_type: VarType::Real,
            name: "y".to_string(),
            init: Some(Expr::Literal(2.0)),
        },
        Statement::VarDecl {
            var_type: VarType::Real,
            name: "a".to_string(),
            init: None,
        },
        Statement::VarDecl {
            var_type: VarType::Real,
            name: "b".to_string(),
            init: None,
        },
        Statement::VarDecl {
            var_type: VarType::Real,
            name: "c".to_string(),
            init: None,
        },
        Statement::VarDecl {
            var_type: VarType::Real,
            name: "d".to_string(),
            init: None,
        },
        Statement::VarDecl {
            var_type: VarType::Real,
            name: "e".to_string(),
            init: None,
        },
        make_assign("a", "max", vec![x.clone(), y.clone()]),
        make_assign("b", "min", vec![x.clone(), y.clone()]),
        make_assign("c", "fmax", vec![x.clone(), y.clone()]),
        make_assign("d", "fmin", vec![x.clone(), y.clone()]),
        make_assign("e", "ABS", vec![x.clone()]),
    ];

    let func = FuncDef {
        name: "TESTFUNC".to_string(),
        group: "Test".to_string(),
        description: None,
        camel_case: None,
        hint: None,
        flags: vec![],
        inputs: vec![Input {
            name: "inReal".to_string(),
            param_type: ParamType::Real,
        }],
        optional_inputs: vec![],
        outputs: vec![Output {
            name: "outReal".to_string(),
            param_type: ParamType::Real,
            flags: vec![],
        }],
        lookback: Some(LookbackExpr::Literal(0)),
        body,
    };

    let enums = std::collections::HashMap::new();
    let registry = make_registry();

    let c_out = backends::c::generate(&func, &enums, &registry);
    let java_out = backends::java::generate(&func, &enums, &registry);
    let rust_out = backends::rust_lang::generate(&func, &enums, &registry);

    // C: max(a,b) → fmax(a,b), min(a,b) → fmin(a,b), ABS(x) → fabs(x)
    assert!(
        c_out.contains("fmax("),
        "C: max/fmax should render as fmax(): {c_out}"
    );
    assert!(
        c_out.contains("fmin("),
        "C: min/fmin should render as fmin(): {c_out}"
    );
    assert!(
        c_out.contains("fabs("),
        "C: ABS should render as fabs(): {c_out}"
    );
    // C must NOT emit bare max() or min() (which are not in C99 <math.h>)
    assert!(
        !c_out.contains("= max(") && !c_out.contains("= min("),
        "C: must not emit bare max()/min() calls"
    );
    // C must NOT emit ABS() calls
    assert!(
        !c_out.contains("ABS("),
        "C: must not emit ABS() calls"
    );

    // Java: max/fmax → Math.max, min/fmin → Math.min, ABS → Math.abs
    assert!(
        java_out.contains("Math.max("),
        "Java: max/fmax should render as Math.max(): {java_out}"
    );
    assert!(
        java_out.contains("Math.min("),
        "Java: min/fmin should render as Math.min(): {java_out}"
    );
    assert!(
        java_out.contains("Math.abs("),
        "Java: ABS should render as Math.abs(): {java_out}"
    );

    // Rust: max/fmax → .max(), min/fmin → .min(), ABS → .ta_abs() (generic) or .abs()
    assert!(
        rust_out.contains(".max("),
        "Rust: max/fmax should render as .max(): {rust_out}"
    );
    assert!(
        rust_out.contains(".min("),
        "Rust: min/fmin should render as .min(): {rust_out}"
    );
    assert!(
        rust_out.contains(".ta_abs()") || rust_out.contains(".abs()"),
        "Rust: ABS should render as .ta_abs() or .abs(): {rust_out}"
    );
    // Rust must NOT emit bare ABS() free-function calls
    assert!(
        !rust_out.contains("ABS("),
        "Rust: must not emit bare ABS() calls"
    );
}

#[test]
fn backends_render_math_functions_idiomatically() {
    let (func, enums) = load_indicator("ht_trendmode");
    let registry = make_registry();

    let c_out = backends::c::generate(&func, &enums, &registry);
    let java_out = backends::java::generate(&func, &enums, &registry);
    let rust_out = backends::rust_lang::generate(&func, &enums, &registry);

    // C: plain atan() from <math.h>
    assert!(
        c_out.contains("atan("),
        "C backend should render atan() as plain C math call: {}",
        &c_out[c_out.find("atan").unwrap_or(0)..c_out.find("atan").unwrap_or(0) + 40]
    );
    // C: must NOT produce TA_atan
    assert!(
        !c_out.contains("TA_atan(") && !c_out.contains("TA_S_atan("),
        "C backend must not prefix math functions with TA_"
    );

    // Java: Math.atan()
    assert!(
        java_out.contains("Math.atan("),
        "Java backend should render Math.atan()"
    );
    // Java: fabs renders as Math.abs, not Math.fabs
    let java_fabs = java_out.contains("Math.abs(");
    let java_wrong_fabs = java_out.contains("Math.fabs(");
    if java_out.contains("fabs(") || java_out.contains("Math.abs(") || java_out.contains("Math.fabs(") {
        assert!(java_fabs, "Java backend should render fabs as Math.abs");
        assert!(!java_wrong_fabs, "Java backend must not render Math.fabs");
    }

    // Rust generic: method call syntax via TaFloat trait
    assert!(
        rust_out.contains(".ta_atan()"),
        "Rust generic backend should render atan as .ta_atan() method call"
    );
    // Rust must NOT produce bare atan() free-function calls (but .ta_atan() is fine)
    let has_bare_atan = rust_out
        .match_indices("atan(")
        .any(|(i, _)| !rust_out[..i].ends_with("ta_") && !rust_out[..i].ends_with('.'));
    assert!(
        !has_bare_atan,
        "Rust backend must not render math functions as free-function calls"
    );
}

#[test]
fn report_failing_parse_indicators() {
    let indicators = discover_indicators();
    let mut failing = Vec::new();
    for name in &indicators {
        let base = std::path::Path::new(env!("CARGO_MANIFEST_DIR")).join("../../ta_func_defs");
        let c_path = base.join(format!("{}/{}.c", name, name));
        let result = std::panic::catch_unwind(std::panic::AssertUnwindSafe(|| {
            parser::c_source::parse_c_source(&c_path);
        }));
        if let Err(e) = result {
            let msg = if let Some(s) = e.downcast_ref::<String>() {
                s.clone()
            } else if let Some(s) = e.downcast_ref::<&str>() {
                s.to_string()
            } else {
                "unknown panic".to_string()
            };
            failing.push(format!("{}: {}", name, msg));
        }
    }
    for f in &failing {
        eprintln!("PARSE_FAIL: {}", f);
    }
    eprintln!("Total failing: {} / {}", failing.len(), indicators.len());
}

#[test]
fn helper_def_stores_params_and_body() {
    use ta_codegen_lib::ir::{BinOp, Expr, HelperDef, HelperParam, Statement, VarType};

    let helper = HelperDef {
        name: "ta_realbody".to_string(),
        return_type: VarType::Real,
        params: vec![
            HelperParam { name: "close".to_string(), var_type: VarType::Real },
            HelperParam { name: "open".to_string(), var_type: VarType::Real },
        ],
        body: vec![Statement::Return {
            value: Some(Expr::FuncCall(
                "fabs".to_string(),
                vec![Expr::BinOp(
                    Box::new(Expr::Var("close".to_string())),
                    BinOp::Sub,
                    Box::new(Expr::Var("open".to_string())),
                )],
            )),
        }],
    };
    assert_eq!(helper.name, "ta_realbody");
    assert_eq!(helper.params.len(), 2);
    assert_eq!(helper.params[0].name, "close");
}

#[test]
fn parse_helper_file_extracts_functions() {
    use ta_codegen_lib::parser::c_source::parse_helper_file_str;

    let source = r#"
double ta_realbody(double close, double open) {
    return fabs(close - open);
}

int ta_candlecolor(double close, double open) {
    return (close >= open) ? 1 : -1;
}
"#;

    let helpers = parse_helper_file_str(source);
    assert_eq!(helpers.len(), 2);
    assert_eq!(helpers[0].name, "ta_realbody");
    assert_eq!(helpers[0].params.len(), 2);
    assert_eq!(helpers[0].params[0].name, "close");
    assert_eq!(helpers[1].name, "ta_candlecolor");
    assert_eq!(helpers[1].params.len(), 2);
}

#[test]
fn parse_helper_with_switch() {
    use ta_codegen_lib::parser::c_source::parse_helper_file_str;
    use ta_codegen_lib::ir::Statement;

    let source = r#"
double ta_candlerange(int rangeType, double open, double high, double low, double close) {
    switch (rangeType) {
        case 0: return fabs(close - open);
        case 1: return high - low;
        case 2: return high - low - fabs(close - open);
        default: return 0.0;
    }
}
"#;

    let helpers = parse_helper_file_str(source);
    assert_eq!(helpers.len(), 1);
    assert_eq!(helpers[0].name, "ta_candlerange");
    assert_eq!(helpers[0].params.len(), 5);
    assert!(matches!(helpers[0].body[0], Statement::Switch { .. }));
}

#[test]
fn parse_helper_file_reads_from_disk() {
    use ta_codegen_lib::parser::c_source::parse_helper_file;
    let path = std::path::Path::new(env!("CARGO_MANIFEST_DIR"))
        .join("../../ta_func_defs/helpers/candlestick.c");
    let helpers = parse_helper_file(&path);
    assert_eq!(helpers.len(), 11);
    assert!(helpers.iter().any(|h| h.name == "ta_realbody" && h.params.len() == 2));
    assert!(helpers.iter().any(|h| h.name == "ta_candleaverage" && h.params.len() == 8));
}

#[test]
fn helper_registry_loads_from_disk() {
    use ta_codegen_lib::helper_registry::HelperRegistry;

    let base = std::path::Path::new(env!("CARGO_MANIFEST_DIR")).join("../../ta_func_defs");
    let registry = HelperRegistry::from_dir(&base);

    // Should find all helpers from candlestick.c, range.c, rounding.c
    assert!(registry.get("ta_realbody").is_some());
    assert!(registry.get("ta_candlerange").is_some());
    assert!(registry.get("ta_true_range").is_some());
    assert!(registry.get("ta_round_pos").is_some());
    assert!(registry.get("ta_sar_rounding").is_some());
    assert!(registry.get("ta_candleaverage").is_some());

    // Should NOT contain indicator functions
    assert!(registry.get("sma").is_none());
    assert!(registry.get("ema").is_none());
}

