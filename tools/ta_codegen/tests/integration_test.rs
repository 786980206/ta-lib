use std::collections::HashMap;
use std::path::Path;
use ta_codegen_lib::backends;
use ta_codegen_lib::ir;
use ta_codegen_lib::parser;
use ta_codegen_lib::registry::Registry;

/// Empty enum map for tests that don't use enums.
fn no_enums() -> HashMap<String, ir::EnumDef> {
    HashMap::new()
}

/// Load enums from the shared enums.yaml.
fn load_enums() -> HashMap<String, ir::EnumDef> {
    let base = Path::new(env!("CARGO_MANIFEST_DIR"));
    let enums_path = base.join("../../ta_func_defs/enums.yaml");
    parser::enums::load_enums(&enums_path)
}

/// Build registry for cross-call resolution.
fn make_registry() -> Registry {
    let base = Path::new(env!("CARGO_MANIFEST_DIR")).join("../../ta_func_defs");
    Registry::from_dir(&base)
}

/// Helper: parse mult.yaml + mult.c and build a FuncDef.
fn load_mult() -> ir::FuncDef {
    let base = Path::new(env!("CARGO_MANIFEST_DIR"));
    let yaml_path = base.join("../../ta_func_defs/mult/mult.yaml");
    let c_path = base.join("../../ta_func_defs/mult/mult.c");

    let mut func_def = parser::yaml::parse_yaml(&yaml_path);
    let parsed = parser::c_source::parse_c_source(&c_path);
    func_def.body = parsed.functions[0].body.clone();
    func_def.lookback = Some(ir::LookbackExpr::Code(parsed.lookback_body));
    func_def
}

/// Helper: parse sma.yaml + sma.c and build a FuncDef.
fn load_sma() -> ir::FuncDef {
    let base = Path::new(env!("CARGO_MANIFEST_DIR"));
    let yaml_path = base.join("../../ta_func_defs/sma/sma.yaml");
    let c_path = base.join("../../ta_func_defs/sma/sma.c");

    let mut func_def = parser::yaml::parse_yaml(&yaml_path);
    let parsed = parser::c_source::parse_c_source(&c_path);
    func_def.body = parsed
        .functions
        .first()
        .expect("C source must contain at least one function")
        .body
        .clone();
    func_def.lookback = Some(ir::LookbackExpr::Code(parsed.lookback_body));
    func_def
}

/// Helper: load any function definition from its .yaml + .c files.
fn load_func(name: &str) -> ir::FuncDef {
    let base = Path::new(env!("CARGO_MANIFEST_DIR"));
    let yaml_path = base.join(format!("../../ta_func_defs/{}/{}.yaml", name, name));
    let c_path = base.join(format!("../../ta_func_defs/{}/{}.c", name, name));

    let mut func_def = parser::yaml::parse_yaml(&yaml_path);
    let parsed = parser::c_source::parse_c_source(&c_path);
    func_def.body = parsed
        .functions
        .first()
        .expect("C source must contain at least one function")
        .body
        .clone();
    func_def.lookback = Some(ir::LookbackExpr::Code(parsed.lookback_body));
    func_def
}

// ---------------------------------------------------------------------------
// C source parser -- MULT from .c file
// ---------------------------------------------------------------------------

#[test]
fn test_mult_from_c_generates_all_backends() {
    let func = load_mult();
    let enums = no_enums();
    let c_out = backends::c::generate(&func, &enums, &make_registry());
    let rust_out = backends::rust_lang::generate(&func, &enums, &make_registry());
    let java_out = backends::java::generate(&func, &enums, &make_registry());
    let dotnet_out = backends::dotnet::generate(&func, &enums, &make_registry());
    let swig_out = backends::swig::generate(&func, &enums, &make_registry());

    assert!(!c_out.is_empty(), "C output from .c source is empty");
    assert!(!rust_out.is_empty(), "Rust output from .c source is empty");
    assert!(!java_out.is_empty(), "Java output from .c source is empty");
    assert!(!dotnet_out.is_empty(), "Dotnet output from .c source is empty");
    assert!(!swig_out.is_empty(), "SWIG output from .c source is empty");

    // Verify key content in C output
    assert!(
        c_out.contains("TA_SUCCESS"),
        "C output from .c source missing TA_SUCCESS"
    );
    assert!(
        c_out.contains("TA_MULT_Lookback"),
        "C output from .c source missing lookback"
    );
}

// ---------------------------------------------------------------------------
// Parser sanity checks -- MULT
// ---------------------------------------------------------------------------

#[test]
fn test_parse_mult_yaml() {
    let func = load_mult();
    assert_eq!(func.name, "MULT");
    assert_eq!(func.group, "Math Operators");
    assert_eq!(func.inputs.len(), 2);
    assert_eq!(func.outputs.len(), 1);
    assert!(func.optional_inputs.is_empty());
}

#[test]
fn test_parse_mult_yaml_enriched() {
    let func = load_mult();
    assert_eq!(func.camel_case.as_deref(), Some("Mult"));
    assert_eq!(func.hint.as_deref(), Some("Vector Arithmetic Mult"));
}

#[test]
fn test_parse_mult_body() {
    let func = load_mult();
    assert!(
        !func.body.is_empty(),
        "Body should contain parsed statements"
    );
}

// ---------------------------------------------------------------------------
// Parser sanity checks -- SMA
// ---------------------------------------------------------------------------

#[test]
fn test_parse_sma_yaml() {
    let func = load_sma();
    assert_eq!(func.name, "SMA");
    assert_eq!(func.group, "Overlap Studies");
    assert_eq!(func.camel_case.as_deref(), Some("Sma"));
    assert_eq!(func.hint.as_deref(), Some("Simple Moving Average"));
    assert!(func.flags.contains(&"overlap".to_string()));
    assert_eq!(func.inputs.len(), 1);
    assert_eq!(func.outputs.len(), 1);
    assert_eq!(func.optional_inputs.len(), 1);
    assert_eq!(func.optional_inputs[0].name, "optInTimePeriod");
    assert_eq!(func.optional_inputs[0].default, Some(30.0));
    assert_eq!(func.optional_inputs[0].range, Some((2, 100000)));
    assert_eq!(
        func.optional_inputs[0].display_name.as_deref(),
        Some("Time Period")
    );
    assert_eq!(
        func.optional_inputs[0].hint.as_deref(),
        Some("Number of period")
    );
    assert!(func.outputs[0].flags.contains(&"line".to_string()));
    assert_eq!(func.optional_inputs[0].suggested, Some((4.0, 200.0, 1.0)));
}

#[test]
fn test_parse_sma_body() {
    let func = load_sma();
    assert!(
        !func.body.is_empty(),
        "SMA body should contain parsed statements"
    );
    let has_if = func.body.iter().any(|s| matches!(s, ir::Statement::If { .. }));
    let has_while = func.body.iter().any(|s| matches!(s, ir::Statement::While { .. }));
    assert!(has_if, "SMA body should contain if statements");
    assert!(has_while, "SMA body should contain while loops");
    let has_nested_return = func.body.iter().any(|s| {
        if let ir::Statement::If { then_body, .. } = s {
            then_body.iter().any(|ts| matches!(ts, ir::Statement::Return { .. }))
        } else {
            false
        }
    });
    assert!(has_nested_return, "SMA body should contain a return inside an if");
}

// ---------------------------------------------------------------------------
// C backend
// ---------------------------------------------------------------------------

#[test]
fn test_c_backend_generates_mult() {
    let func = load_mult();
    let output = backends::c::generate(&func, &no_enums(), &make_registry());
    assert!(
        output.contains("TA_MULT_Lookback"),
        "C output missing lookback function"
    );
    assert!(
        output.contains("TA_RetCode TA_MULT(") || output.contains("TA_MULT("),
        "C output missing TA_MULT function"
    );
    assert!(
        output.contains("TA_RetCode TA_S_MULT(") || output.contains("TA_S_MULT("),
        "C output missing single-precision TA_S_MULT function"
    );
    assert!(
        output.contains("TA_SUCCESS"),
        "C output missing TA_SUCCESS return"
    );
    assert!(
        output.contains("inReal0[i]*inReal1[i]") || output.contains("inReal0[i] * inReal1[i]"),
        "C output missing multiplication expression"
    );
}

// ---------------------------------------------------------------------------
// Rust backend
// ---------------------------------------------------------------------------

#[test]
fn test_rust_backend_generates_mult() {
    let func = load_mult();
    let output = backends::rust_lang::generate(&func, &no_enums(), &make_registry());
    assert!(
        output.contains("mult_lookback") || output.contains("Lookback"),
        "Rust output missing lookback function"
    );
    assert!(
        output.contains("fn mult") || output.contains("fn s_mult") || output.contains("MULT"),
        "Rust output missing mult function"
    );
    assert!(
        output.contains("f64") || output.contains("f32"),
        "Rust output missing type annotations"
    );
}

// Reference comparison removed: the reference file in rust/src/ta_func/mult.rs
// was generated by the old gen_code system and uses different patterns (FOR_EACH_OUTPUT)
// than the new C-source-based ta_codegen output. Functional equivalence is validated
// by the JSON-RPC server tests in validate.sh.

#[test]
fn test_rust_sma_from_c_produces_valid_output() {
    let func = load_sma();
    let output = backends::rust_lang::generate(&func, &no_enums(), &make_registry());

    assert!(output.contains("sma_lookback"), "Missing sma_lookback function");
    assert!(output.contains("fn sma_logic"), "Missing sma_logic internal function");
    assert!(output.contains("RetCode::Success"), "Missing Success return");
    assert!(output.contains("optInTimePeriod"), "Missing optInTimePeriod");
    assert!(output.contains("periodTotal"), "Missing periodTotal variable");
    assert!(output.contains("lookbackTotal"), "Missing lookbackTotal variable");
    assert!(output.contains("optInTimePeriod - 1"), "Missing lookback expression");
    assert!(output.contains("i += 1") || output.contains("i = i + 1"),
        "Missing increment pattern");
}

// ---------------------------------------------------------------------------
// Java backend
// ---------------------------------------------------------------------------

#[test]
fn test_java_backend_generates_mult() {
    let func = load_mult();
    let output = backends::java::generate(&func, &no_enums(), &make_registry());
    assert!(
        output.contains("multLookback") || output.contains("Lookback"),
        "Java output missing lookback method"
    );
    assert!(
        output.contains("mult(") || output.contains("RetCode"),
        "Java output missing mult method"
    );
    assert!(
        output.contains("MInteger") || output.contains("outBegIdx"),
        "Java output missing MInteger output params"
    );
    assert!(
        output.contains("Success") || output.contains("RetCode"),
        "Java output missing success return"
    );
}

// ---------------------------------------------------------------------------
// .NET backend
// ---------------------------------------------------------------------------

#[test]
fn test_dotnet_backend_generates_mult() {
    let func = load_mult();
    let output = backends::dotnet::generate(&func, &no_enums(), &make_registry());
    assert!(
        output.contains("MultLookback") || output.contains("Lookback"),
        ".NET output missing lookback"
    );
    assert!(
        output.contains("Mult") || output.contains("MULT"),
        ".NET output missing Mult function"
    );
    assert!(
        output.contains("SubArray") || output.contains("cli::array"),
        ".NET output missing managed array types"
    );
}

// ---------------------------------------------------------------------------
// SWIG backend
// ---------------------------------------------------------------------------

#[test]
fn test_swig_backend_generates_mult() {
    let func = load_mult();
    let output = backends::swig::generate(&func, &no_enums(), &make_registry());
    assert!(
        output.contains("TA_MULT") || output.contains("MULT"),
        "SWIG output missing TA_MULT"
    );
    assert!(
        output.contains("IN_ARRAY") || output.contains("INPUT"),
        "SWIG output missing input array typemap"
    );
    assert!(
        output.contains("OUT_ARRAY") || output.contains("OUTPUT"),
        "SWIG output missing output array typemap"
    );
    assert!(
        output.contains("Lookback") || output.contains("lookback") || output.contains("_Lookback"),
        "SWIG output missing lookback"
    );
}

// ---------------------------------------------------------------------------
// SMA from C source: all backends, lookback, internal function
// ---------------------------------------------------------------------------

#[test]
fn test_sma_from_c_generates_all_backends() {
    let func = load_sma();
    let enums = no_enums();
    let c_out = backends::c::generate(&func, &enums, &make_registry());
    let rust_out = backends::rust_lang::generate(&func, &enums, &make_registry());
    let java_out = backends::java::generate(&func, &enums, &make_registry());
    let dotnet_out = backends::dotnet::generate(&func, &enums, &make_registry());
    let swig_out = backends::swig::generate(&func, &enums, &make_registry());

    assert!(!c_out.is_empty(), "C output from .c source is empty");
    assert!(!rust_out.is_empty(), "Rust output from .c source is empty");
    assert!(!java_out.is_empty(), "Java output from .c source is empty");
    assert!(!dotnet_out.is_empty(), "Dotnet output from .c source is empty");
    assert!(!swig_out.is_empty(), "SWIG output from .c source is empty");

    assert!(
        c_out.contains("TA_SUCCESS"),
        "C output from .c source missing TA_SUCCESS"
    );
    assert!(
        c_out.contains("TA_SMA_Lookback"),
        "C output from .c source missing lookback"
    );
    assert!(
        c_out.contains("optInTimePeriod"),
        "C output missing optInTimePeriod"
    );
    assert!(
        c_out.contains("optInTimePeriod - 1") || c_out.contains("optInTimePeriod-1"),
        "C lookback missing optInTimePeriod - 1"
    );
}

#[test]
fn test_sma_from_c_lookback_body() {
    let func = load_sma();
    match &func.lookback {
        Some(ir::LookbackExpr::Code(stmts)) => {
            assert!(!stmts.is_empty(), "Lookback body should not be empty");
            let has_return = stmts.iter().any(|s| matches!(s, ir::Statement::Return { .. }));
            assert!(has_return, "Lookback body should contain a return statement");
        }
        other => panic!("Expected LookbackExpr::Code, got {:?}", other),
    }
}

#[test]
fn test_sma_from_c_has_logic_function() {
    let base = Path::new(env!("CARGO_MANIFEST_DIR"));
    let c_path = base.join("../../ta_func_defs/sma/sma.c");
    let parsed = parser::c_source::parse_c_source(&c_path);

    assert_eq!(parsed.functions.len(), 1, "Should have one function");
    assert_eq!(parsed.functions[0].name, "sma", "Function name should be sma");
    assert!(!parsed.functions[0].body.is_empty(), "Function body should not be empty");
}

// ---------------------------------------------------------------------------
// SMA: all backends produce non-empty output
// ---------------------------------------------------------------------------

#[test]
fn test_sma_all_backends_generate() {
    let func = load_sma();
    let enums = no_enums();

    let c_out = backends::c::generate(&func, &enums, &make_registry());
    let rust_out = backends::rust_lang::generate(&func, &enums, &make_registry());
    let java_out = backends::java::generate(&func, &enums, &make_registry());
    let dotnet_out = backends::dotnet::generate(&func, &enums, &make_registry());
    let swig_out = backends::swig::generate(&func, &enums, &make_registry());

    assert!(!c_out.is_empty(), "C output is empty");
    assert!(!rust_out.is_empty(), "Rust output is empty");
    assert!(!java_out.is_empty(), "Java output is empty");
    assert!(!dotnet_out.is_empty(), "Dotnet output is empty");
    assert!(!swig_out.is_empty(), "SWIG output is empty");

    assert!(c_out.contains("optInTimePeriod"), "C output missing optInTimePeriod");
    assert!(rust_out.contains("optInTimePeriod"), "Rust output missing optInTimePeriod");
    assert!(java_out.contains("optInTimePeriod"), "Java output missing optInTimePeriod");
    assert!(swig_out.contains("OPT_INT"), "SWIG output missing OPT_INT typemap");
}

// ---------------------------------------------------------------------------
// All backends produce non-empty output (MULT)
// ---------------------------------------------------------------------------

#[test]
fn test_all_backends_produce_nonempty_output() {
    let func = load_mult();
    let enums = no_enums();

    let c_out = backends::c::generate(&func, &enums, &make_registry());
    let rust_out = backends::rust_lang::generate(&func, &enums, &make_registry());
    let java_out = backends::java::generate(&func, &enums, &make_registry());
    let dotnet_out = backends::dotnet::generate(&func, &enums, &make_registry());
    let swig_out = backends::swig::generate(&func, &enums, &make_registry());

    assert!(!c_out.is_empty(), "C output is empty");
    assert!(!rust_out.is_empty(), "Rust output is empty");
    assert!(!java_out.is_empty(), "Java output is empty");
    assert!(!dotnet_out.is_empty(), "Dotnet output is empty");
    assert!(!swig_out.is_empty(), "SWIG output is empty");

    assert!(c_out.len() > 100, "C output suspiciously short");
    assert!(rust_out.len() > 100, "Rust output suspiciously short");
    assert!(java_out.len() > 100, "Java output suspiciously short");
    assert!(dotnet_out.len() > 100, "Dotnet output suspiciously short");
    assert!(swig_out.len() > 100, "SWIG output suspiciously short");
}

// ---------------------------------------------------------------------------
// WMA, RSI, EMA, MA: all backends produce non-empty output
// ---------------------------------------------------------------------------

#[test]
fn test_wma_generates_all_backends() {
    let func = load_func("wma");
    let enums = no_enums();
    assert_eq!(func.name, "WMA");
    assert_eq!(func.camel_case.as_deref(), Some("Wma"));
    assert_eq!(func.hint.as_deref(), Some("Weighted Moving Average"));
    assert!(func.flags.contains(&"overlap".to_string()));

    let c_out = backends::c::generate(&func, &enums, &make_registry());
    let rust_out = backends::rust_lang::generate(&func, &enums, &make_registry());
    let java_out = backends::java::generate(&func, &enums, &make_registry());

    assert!(c_out.contains("TA_WMA_Lookback"), "C missing lookback");
    assert!(c_out.contains("optInTimePeriod"), "C missing optInTimePeriod");
    assert!(rust_out.contains("wma_lookback"), "Rust missing lookback");
    assert!(!java_out.is_empty(), "Java output is empty");
}

#[test]
fn test_rsi_generates_all_backends() {
    let func = load_func("rsi");
    let enums = no_enums();
    assert_eq!(func.name, "RSI");
    assert_eq!(func.camel_case.as_deref(), Some("Rsi"));
    assert_eq!(func.hint.as_deref(), Some("Relative Strength Index"));
    assert!(func.flags.contains(&"unstable_period".to_string()));

    let c_out = backends::c::generate(&func, &enums, &make_registry());
    let rust_out = backends::rust_lang::generate(&func, &enums, &make_registry());

    assert!(c_out.contains("TA_RSI_Lookback"), "C missing lookback");
    assert!(c_out.contains("TA_GLOBALS_UNSTABLE_PERIOD"), "C missing UNSTABLE_PERIOD");
    assert!(c_out.contains("TA_GLOBALS_COMPATIBILITY"), "C missing COMPATIBILITY");
    assert!(c_out.contains("TA_IS_ZERO"), "C missing IS_ZERO");
    assert!(rust_out.contains("rsi_lookback"), "Rust missing lookback");
    assert!(rust_out.contains("unstable_period"), "Rust missing unstable_period");
}

#[test]
fn test_ema_generates_all_backends() {
    let func = load_func("ema");
    let enums = no_enums();
    assert_eq!(func.name, "EMA");
    assert_eq!(func.camel_case.as_deref(), Some("Ema"));
    assert_eq!(func.hint.as_deref(), Some("Exponential Moving Average"));
    assert!(func.flags.contains(&"overlap".to_string()));
    assert!(func.flags.contains(&"unstable_period".to_string()));

    let c_out = backends::c::generate(&func, &enums, &make_registry());
    let rust_out = backends::rust_lang::generate(&func, &enums, &make_registry());

    assert!(c_out.contains("TA_EMA_Lookback"), "C missing lookback");
    assert!(c_out.contains("TA_GLOBALS_UNSTABLE_PERIOD"), "C missing UNSTABLE_PERIOD");
    assert!(rust_out.contains("ema_lookback"), "Rust missing lookback");
}

#[test]
fn test_ma_generates_all_backends() {
    let func = load_func("ma");
    let enums = load_enums();
    assert_eq!(func.name, "MA");
    assert_eq!(func.camel_case.as_deref(), Some("Ma"));
    assert_eq!(func.hint.as_deref(), Some("Moving average"));
    assert!(func.flags.contains(&"overlap".to_string()));
    assert_eq!(func.optional_inputs.len(), 2);

    let c_out = backends::c::generate(&func, &enums, &make_registry());
    let rust_out = backends::rust_lang::generate(&func, &enums, &make_registry());

    assert!(c_out.contains("TA_MA_Lookback"), "C missing lookback");
    assert!(c_out.contains("TA_SMA_Lookback"), "C missing TA_SMA_Lookback call");
    assert!(c_out.contains("TA_EMA_Lookback"), "C missing TA_EMA_Lookback call");
    assert!(rust_out.contains("ma_lookback"), "Rust missing lookback");
}

// ---------------------------------------------------------------------------
// Rust backend: verify _logic variant names (renamed from int_)
// ---------------------------------------------------------------------------

#[test]
fn test_rust_generates_logic_variant() {
    let func = load_sma();
    let output = backends::rust_lang::generate(&func, &no_enums(), &make_registry());

    // _logic variants (renamed from int_)
    assert!(output.contains("fn sma_logic("), "Missing sma_logic function");
    assert!(output.contains("fn sma_logic_s("), "Missing sma_logic_s function");

    // Guarded functions should delegate to _logic
    assert!(output.contains("self.sma_logic("), "Guarded fn should delegate to sma_logic");
    assert!(output.contains("self.sma_logic_s("), "Guarded fn should delegate to sma_logic_s");

    // Should NOT contain the old int_ naming
    assert!(!output.contains("fn int_sma("), "Should not contain old int_sma naming");
    assert!(!output.contains("fn int_sma_s("), "Should not contain old int_sma_s naming");

    // Unsafe variant placeholder should be present
    assert!(output.contains("sma_unsafe"), "Missing sma_unsafe placeholder");
    assert!(output.contains("sma_unsafe_s"), "Missing sma_unsafe_s placeholder");
}

#[test]
fn test_rust_mult_generates_logic_names() {
    let func = load_mult();
    let output = backends::rust_lang::generate(&func, &no_enums(), &make_registry());

    // MULT has no optional inputs, so no separate _logic function.
    // But unsafe placeholders should still exist.
    assert!(output.contains("mult_unsafe"), "Missing mult_unsafe placeholder");
    assert!(output.contains("mult_unsafe_s"), "Missing mult_unsafe_s placeholder");
}
