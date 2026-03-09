use std::collections::HashMap;
use crate::ir::*;
use crate::registry::Registry;

pub fn generate(func: &FuncDef, _enums: &HashMap<String, EnumDef>, _registry: &Registry) -> String {
    let mut out = String::new();
    let pascal = to_pascal_case(&func.name);

    out.push_str(&gen_lookback(func, &pascal));
    out.push('\n');
    out.push_str("#if defined( _MANAGED ) && defined( USE_SUBARRAY )\n");
    out.push_str(&gen_subarray_decl(func, &pascal, false));
    out.push('\n');
    out.push_str(&gen_subarray_decl(func, &pascal, true));
    out.push('\n');
    out.push_str(&gen_cli_array_dispatch(func, &pascal, false));
    out.push_str(&gen_cli_array_dispatch(func, &pascal, true));
    out.push_str("#elif defined( _MANAGED )\n");
    out.push_str(&gen_cli_array_decl(func, &pascal, false));
    out.push_str(&gen_cli_array_decl(func, &pascal, true));
    out.push_str("#endif\n");
    out.push('\n');

    // Logic variant declarations (same signatures, different name)
    out.push_str("#if defined( _MANAGED ) && defined( USE_SUBARRAY )\n");
    let logic_pascal = format!("{}Logic", pascal);
    out.push_str(&gen_subarray_decl(func, &logic_pascal, false));
    out.push('\n');
    out.push_str(&gen_subarray_decl(func, &logic_pascal, true));
    out.push('\n');
    out.push_str(&gen_cli_array_dispatch(func, &logic_pascal, false));
    out.push_str(&gen_cli_array_dispatch(func, &logic_pascal, true));
    out.push_str("#elif defined( _MANAGED )\n");
    out.push_str(&gen_cli_array_decl(func, &logic_pascal, false));
    out.push_str(&gen_cli_array_decl(func, &logic_pascal, true));
    out.push_str("#endif\n");
    out.push('\n');

    out.push_str(&gen_macros(func, &pascal));

    out
}

fn to_pascal_case(name: &str) -> String {
    let lower = name.to_lowercase();
    let mut chars = lower.chars();
    match chars.next() {
        None => String::new(),
        Some(c) => c.to_uppercase().to_string() + chars.as_str(),
    }
}

/// Map a ParamType to the C++/CLI type string for optional inputs.
fn opt_input_type(pt: &ParamType) -> &'static str {
    match pt {
        ParamType::Real => "double",
        ParamType::Integer => "int",
        ParamType::Enum(_) | ParamType::Price(_) => "int",
    }
}

/// Map a ParamType to a C++/CLI type string for inputs (non-single-precision).
fn input_type(pt: &ParamType, single_precision: bool) -> &'static str {
    if single_precision {
        match pt {
            ParamType::Real => "float",
            ParamType::Integer | ParamType::Enum(_) | ParamType::Price(_) => "int",
        }
    } else {
        match pt {
            ParamType::Real => "double",
            ParamType::Integer | ParamType::Enum(_) | ParamType::Price(_) => "int",
        }
    }
}

/// Map a ParamType to a C++/CLI type string for outputs.
fn output_type(pt: &ParamType) -> &'static str {
    match pt {
        ParamType::Real => "double",
        ParamType::Integer | ParamType::Enum(_) | ParamType::Price(_) => "int",
    }
}

fn gen_lookback(func: &FuncDef, pascal: &str) -> String {
    let params = match &func.lookback {
        Some(LookbackExpr::Literal(_)) | None => "void".to_string(),
        Some(LookbackExpr::ParamMinus(param, _)) => {
            // Find the opt input to get range info
            let opt = func.optional_inputs.iter().find(|o| o.name == *param);
            if let Some(opt) = opt {
                let c_type = opt_input_type(&opt.param_type);
                if let Some((lo, hi)) = opt.range {
                    format!(
                        "{}           {} );\
                     /* From {} to {} */",
                        c_type, param, lo, hi
                    )
                } else {
                    format!("{}           {}", c_type, param)
                }
            } else {
                "void".to_string()
            }
        }
        Some(LookbackExpr::Code(_)) => {
            if func.optional_inputs.is_empty() {
                "void".to_string()
            } else {
                let param_parts: Vec<String> = func.optional_inputs.iter().map(|opt| {
                    let c_type = opt_input_type(&opt.param_type);
                    let range = opt.range.map(|r| format!("  /* From {} to {} */", r.0, r.1)).unwrap_or_default();
                    format!("{}           {}{}", c_type, opt.name, range)
                }).collect();
                param_parts.join(", ")
            }
        }
    };

    format!("         static int {}Lookback( {} );\n", pascal, params)
}

fn gen_subarray_decl(func: &FuncDef, pascal: &str, single_precision: bool) -> String {
    let mut params: Vec<String> = Vec::new();
    params.push("int    startIdx".to_string());
    params.push("int    endIdx".to_string());

    for input in &func.inputs {
        let typ = input_type(&input.param_type, single_precision);
        params.push(format!("SubArray<{}>^ {}", typ, input.name));
    }

    for opt in &func.optional_inputs {
        let typ = opt_input_type(&opt.param_type);
        params.push(format!("{} {}", typ, opt.name));
    }

    params.push("[Out]int%    outBegIdx".to_string());
    params.push("[Out]int%    outNBElement".to_string());

    for output in &func.outputs {
        let typ = output_type(&output.param_type);
        params.push(format!("SubArray<{}>^  {}", typ, output.name));
    }

    format_decl(pascal, &params)
}

fn gen_cli_array_dispatch(func: &FuncDef, pascal: &str, single_precision: bool) -> String {
    let mut params: Vec<String> = Vec::new();
    params.push("int    startIdx".to_string());
    params.push("int    endIdx".to_string());

    for input in &func.inputs {
        let typ = input_type(&input.param_type, single_precision);
        params.push(format!("cli::array<{}>^ {}", typ, input.name));
    }

    for opt in &func.optional_inputs {
        let typ = opt_input_type(&opt.param_type);
        params.push(format!("{} {}", typ, opt.name));
    }

    params.push("[Out]int%    outBegIdx".to_string());
    params.push("[Out]int%    outNBElement".to_string());

    for output in &func.outputs {
        let typ = output_type(&output.param_type);
        params.push(format!("cli::array<{}>^  {}", typ, output.name));
    }

    let mut out = format_decl_inline(pascal, &params);

    // Build dispatch call body
    out.push_str(&format!("         {{ return {}( startIdx, endIdx,\n", pascal));

    // Wrap inputs
    for input in &func.inputs {
        let typ = input_type(&input.param_type, single_precision);
        out.push_str(&format!(
            "                         gcnew SubArrayFrom1D<{}>({},0),\n",
            typ, input.name
        ));
    }

    // Pass through optional inputs
    for opt in &func.optional_inputs {
        out.push_str(&format!("                         {},\n", opt.name));
    }

    // Pass through output scalars
    out.push_str("             outBegIdx,\n");
    out.push_str("             outNBElement,\n");

    // Wrap outputs
    for (i, output) in func.outputs.iter().enumerate() {
        let typ = output_type(&output.param_type);
        if i == func.outputs.len() - 1 {
            out.push_str(&format!(
                "               gcnew SubArrayFrom1D<{}>({},0) );\n",
                typ, output.name
            ));
        } else {
            out.push_str(&format!(
                "               gcnew SubArrayFrom1D<{}>({},0),\n",
                typ, output.name
            ));
        }
    }

    out.push_str("         }\n");

    out
}

fn gen_cli_array_decl(func: &FuncDef, pascal: &str, single_precision: bool) -> String {
    let mut params: Vec<String> = Vec::new();
    params.push("int    startIdx".to_string());
    params.push("int    endIdx".to_string());

    for input in &func.inputs {
        let typ = input_type(&input.param_type, single_precision);
        params.push(format!("cli::array<{}>^ {}", typ, input.name));
    }

    for opt in &func.optional_inputs {
        let typ = opt_input_type(&opt.param_type);
        params.push(format!("{} {}", typ, opt.name));
    }

    params.push("[Out]int%    outBegIdx".to_string());
    params.push("[Out]int%    outNBElement".to_string());

    for output in &func.outputs {
        let typ = output_type(&output.param_type);
        params.push(format!("cli::array<{}>^  {}", typ, output.name));
    }

    format_decl(pascal, &params)
}

fn gen_macros(_func: &FuncDef, pascal: &str) -> String {
    let upper = pascal.to_uppercase();
    format!(
        "         #define TA_{} Core::{}\n\
         \x20        #define TA_{}_Lookback Core::{}Lookback\n\
         \x20        #define TA_{}_Logic Core::{}Logic\n\
         \x20        #define TA_INT_{} Core::{}Logic\n",
        upper, pascal,
        upper, pascal,
        upper, pascal,
        upper, pascal
    )
}

/// Format a declaration-only signature (semicolon terminated).
fn format_decl(pascal: &str, params: &[String]) -> String {
    let prefix = format!("         static enum class RetCode {}( ", pascal);
    let indent = " ".repeat(prefix.len());
    let mut out = prefix;
    for (i, param) in params.iter().enumerate() {
        if i > 0 {
            out.push_str(&format!(",\n{}", indent));
        }
        out.push_str(param);
    }
    out.push_str(" );\n");
    out
}

/// Format a declaration with inline body (no semicolon, open for body).
fn format_decl_inline(pascal: &str, params: &[String]) -> String {
    let prefix = format!("         static enum class RetCode {}( ", pascal);
    let indent = " ".repeat(prefix.len());
    let mut out = prefix;
    for (i, param) in params.iter().enumerate() {
        if i > 0 {
            out.push_str(&format!(",\n{}", indent));
        }
        out.push_str(param);
    }
    out.push_str(" )\n");
    out
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::path::Path;
    use crate::parser;
    use crate::registry::Registry;

    fn make_registry() -> Registry {
        let base = Path::new(env!("CARGO_MANIFEST_DIR")).join("../../ta_func_defs");
        Registry::from_dir(&base)
    }

    fn load_sma() -> FuncDef {
        let base = Path::new(env!("CARGO_MANIFEST_DIR"));
        let yaml_path = base.join("../../ta_func_defs/sma/sma.yaml");
        let c_path = base.join("../../ta_func_defs/sma/sma.c");
        let mut func_def = parser::yaml::parse_yaml(&yaml_path);
        let parsed = parser::c_source::parse_c_source(&c_path);
        func_def.body = parsed.functions[0].body.clone();
        func_def.lookback = Some(LookbackExpr::Code(parsed.lookback_body));
        func_def
    }

    #[test]
    fn test_dotnet_generates_logic_declarations() {
        let func = load_sma();
        let enums = HashMap::new();
        let registry = make_registry();
        let output = generate(&func, &enums, &registry);

        // Should contain logic variant declaration
        assert!(output.contains("SmaLogic("), "Missing SmaLogic declaration");

        // Should contain the TA_INT_SMA macro
        assert!(output.contains("#define TA_INT_SMA"), "Missing #define TA_INT_SMA");

        // Should contain the TA_SMA_Logic macro
        assert!(output.contains("#define TA_SMA_Logic Core::SmaLogic"), "Missing #define TA_SMA_Logic");

        // Should contain the TA_INT_SMA macro pointing to Core::SmaLogic
        assert!(output.contains("#define TA_INT_SMA Core::SmaLogic"), "Missing #define TA_INT_SMA Core::SmaLogic");
    }
}
