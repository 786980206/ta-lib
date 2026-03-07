use std::path::Path;
use ta_codegen_lib::backends;
use ta_codegen_lib::ir;
use ta_codegen_lib::parser;

/// Helper: parse mult.yaml + mult.logic and build a FuncDef.
fn load_mult() -> ir::FuncDef {
    let base = Path::new(env!("CARGO_MANIFEST_DIR"));
    let yaml_path = base.join("../../ta_func_defs/mult/mult.yaml");
    let logic_path = base.join("../../ta_func_defs/mult/mult.logic");

    let (name, group, description, inputs, opt_inputs, outputs, lookback) =
        parser::yaml::parse_yaml(&yaml_path);
    let body = parser::logic::parse_logic(&logic_path);

    ir::FuncDef {
        name,
        group,
        description,
        inputs,
        optional_inputs: opt_inputs,
        outputs,
        lookback,
        body,
    }
}

/// Helper: parse sma.yaml + sma.logic and build a FuncDef.
fn load_sma() -> ir::FuncDef {
    let base = Path::new(env!("CARGO_MANIFEST_DIR"));
    let yaml_path = base.join("../../ta_func_defs/sma/sma.yaml");
    let logic_path = base.join("../../ta_func_defs/sma/sma.logic");

    let (name, group, description, inputs, opt_inputs, outputs, lookback) =
        parser::yaml::parse_yaml(&yaml_path);
    let body = parser::logic::parse_logic(&logic_path);

    ir::FuncDef {
        name,
        group,
        description,
        inputs,
        optional_inputs: opt_inputs,
        outputs,
        lookback,
        body,
    }
}

// ---------------------------------------------------------------------------
// Parser sanity checks — MULT
// ---------------------------------------------------------------------------

#[test]
fn test_parse_mult_yaml() {
    let func = load_mult();
    assert_eq!(func.name, "MULT");
    assert_eq!(func.group, "Math Operators");
    assert_eq!(func.inputs.len(), 2);
    assert_eq!(func.outputs.len(), 1);
    assert!(func.optional_inputs.is_empty());
    assert!(matches!(func.lookback, ir::LookbackExpr::Literal(0)));
}

#[test]
fn test_parse_mult_logic() {
    let func = load_mult();
    assert!(
        !func.body.is_empty(),
        "Body should contain parsed statements"
    );
}

// ---------------------------------------------------------------------------
// Parser sanity checks — SMA
// ---------------------------------------------------------------------------

#[test]
fn test_parse_sma_yaml() {
    let func = load_sma();
    assert_eq!(func.name, "SMA");
    assert_eq!(func.group, "Overlap Studies");
    assert_eq!(func.description.as_deref(), Some("Simple Moving Average"));
    assert_eq!(func.inputs.len(), 1);
    assert_eq!(func.outputs.len(), 1);
    assert_eq!(func.optional_inputs.len(), 1);
    assert_eq!(func.optional_inputs[0].name, "optInTimePeriod");
    assert_eq!(func.optional_inputs[0].default, Some(30));
    assert_eq!(func.optional_inputs[0].range, Some((2, 100000)));
    assert!(matches!(
        func.lookback,
        ir::LookbackExpr::ParamMinus(_, 1)
    ));
}

#[test]
fn test_parse_sma_logic() {
    let func = load_sma();
    assert!(
        !func.body.is_empty(),
        "SMA body should contain parsed statements"
    );
    // SMA logic has VarDecls, assignments, if statements, while loops, and returns
    let has_if = func.body.iter().any(|s| matches!(s, ir::Statement::If { .. }));
    let has_while = func.body.iter().any(|s| matches!(s, ir::Statement::While { .. }));
    let _has_return = func.body.iter().any(|s| matches!(s, ir::Statement::Return { .. }));
    assert!(has_if, "SMA body should contain if statements");
    assert!(has_while, "SMA body should contain while loops");
    // Return is inside an if body, not top-level
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
    let output = backends::c::generate(&func);
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
    let output = backends::rust_lang::generate(&func);
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

#[test]
fn test_rust_mult_matches_reference() {
    let base = Path::new(env!("CARGO_MANIFEST_DIR"));
    let reference_path = base.join("../../rust/src/ta_func/mult.rs");

    if !reference_path.exists() {
        eprintln!(
            "Skipping reference comparison: {} not found",
            reference_path.display()
        );
        return;
    }

    let func = load_mult();
    let output = backends::rust_lang::generate(&func);
    let reference = std::fs::read_to_string(&reference_path).unwrap();

    assert_eq!(output, reference, "Generated MULT Rust should match reference exactly");
}

#[test]
fn test_rust_sma_matches_reference() {
    let base = Path::new(env!("CARGO_MANIFEST_DIR"));
    let reference_path = base.join("../../rust/src/ta_func/sma.rs");

    if !reference_path.exists() {
        eprintln!(
            "Skipping reference comparison: {} not found",
            reference_path.display()
        );
        return;
    }

    let func = load_sma();
    let output = backends::rust_lang::generate(&func);
    let reference = std::fs::read_to_string(&reference_path).unwrap();

    assert_eq!(output, reference, "Generated SMA Rust should match reference exactly");
}

// ---------------------------------------------------------------------------
// Java backend
// ---------------------------------------------------------------------------

#[test]
fn test_java_backend_generates_mult() {
    let func = load_mult();
    let output = backends::java::generate(&func);
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
    let output = backends::dotnet::generate(&func);
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
    let output = backends::swig::generate(&func);
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
        output.contains("Lookback") || output.contains("lookback"),
        "SWIG output missing lookback"
    );
}

// ---------------------------------------------------------------------------
// SMA: all backends produce non-empty output
// ---------------------------------------------------------------------------

#[test]
fn test_sma_all_backends_generate() {
    let func = load_sma();

    let c_out = backends::c::generate(&func);
    let rust_out = backends::rust_lang::generate(&func);
    let java_out = backends::java::generate(&func);
    let dotnet_out = backends::dotnet::generate(&func);
    let swig_out = backends::swig::generate(&func);

    assert!(!c_out.is_empty(), "C output is empty");
    assert!(!rust_out.is_empty(), "Rust output is empty");
    assert!(!java_out.is_empty(), "Java output is empty");
    assert!(!dotnet_out.is_empty(), "Dotnet output is empty");
    assert!(!swig_out.is_empty(), "SWIG output is empty");

    // SMA should have optInTimePeriod in various forms
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

    let c_out = backends::c::generate(&func);
    let rust_out = backends::rust_lang::generate(&func);
    let java_out = backends::java::generate(&func);
    let dotnet_out = backends::dotnet::generate(&func);
    let swig_out = backends::swig::generate(&func);

    assert!(!c_out.is_empty(), "C output is empty");
    assert!(!rust_out.is_empty(), "Rust output is empty");
    assert!(!java_out.is_empty(), "Java output is empty");
    assert!(!dotnet_out.is_empty(), "Dotnet output is empty");
    assert!(!swig_out.is_empty(), "SWIG output is empty");

    // Each backend should produce a reasonable amount of output
    assert!(c_out.len() > 100, "C output suspiciously short");
    assert!(rust_out.len() > 100, "Rust output suspiciously short");
    assert!(java_out.len() > 100, "Java output suspiciously short");
    assert!(dotnet_out.len() > 100, "Dotnet output suspiciously short");
    assert!(swig_out.len() > 100, "SWIG output suspiciously short");
}
