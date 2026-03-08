use std::collections::HashMap;
use crate::ir::*;
use crate::registry::Registry;

pub fn generate(func: &FuncDef, _enums: &HashMap<String, EnumDef>, _registry: &Registry) -> String {
    let mut out = String::new();
    out.push_str(&gen_comment_block(func));
    out.push_str(&gen_func_decl(func, false));
    out.push('\n');
    out.push_str(&gen_func_decl(func, true));
    out.push('\n');
    out.push_str(&gen_lookback_decl(func));
    out.push('\n');
    out
}

/// Generate the comment block describing the function.
fn gen_comment_block(func: &FuncDef) -> String {
    let mut out = String::new();
    let default_desc = format!("TA_{}", func.name);
    let desc = func.description.as_deref().or(func.hint.as_deref()).unwrap_or(&default_desc);

    out.push_str("/*\n");
    out.push_str(&format!(" * TA_{} - {}\n", func.name, desc));
    out.push_str(" *\n");

    // Input type summary
    let input_types: Vec<&str> = func
        .inputs
        .iter()
        .map(|i| match i.param_type {
            ParamType::Real => "double",
            ParamType::Integer | ParamType::Enum(_) => "int",
        })
        .collect();
    out.push_str(&format!(" * Input  = {}\n", input_types.join(", ")));

    // Output type summary
    let output_types: Vec<&str> = func
        .outputs
        .iter()
        .map(|o| match o.param_type {
            ParamType::Real => "double",
            ParamType::Integer | ParamType::Enum(_) => "int",
        })
        .collect();
    out.push_str(&format!(" * Output = {}\n", output_types.join(", ")));

    // Optional parameters section
    if !func.optional_inputs.is_empty() {
        out.push_str(" *\n");
        out.push_str(" * Optional Parameters\n");
        out.push_str(" * -------------------\n");
        for opt in &func.optional_inputs {
            let range_str = match opt.range {
                Some((min, max)) => format!("(From {} to {})", min, max),
                None => String::new(),
            };
            out.push_str(&format!(" * {}:{}\n", opt.name, range_str));
        }
    }

    out.push_str(" *\n");
    out.push_str(" */\n");
    out
}

/// A parameter with an optional trailing comment (placed after the comma).
struct SwigParam {
    text: String,
    trailing_comment: Option<String>,
}

/// Generate a function declaration with SWIG typemap markers.
/// When `logic` is true, generates the Logic variant (TA_<NAME>_Logic).
fn gen_func_decl(func: &FuncDef, logic: bool) -> String {
    let mut out = String::new();
    let prefix = if logic {
        format!("TA_{}_Logic", func.name)
    } else {
        format!("TA_{}", func.name)
    };

    // Build parameter list with SWIG typemap markers
    let mut params: Vec<SwigParam> = Vec::new();

    params.push(SwigParam {
        text: "int           START_IDX".to_string(),
        trailing_comment: None,
    });
    params.push(SwigParam {
        text: "int           END_IDX".to_string(),
        trailing_comment: None,
    });

    for input in &func.inputs {
        let c_type = match input.param_type {
            ParamType::Real => "const double",
            ParamType::Integer | ParamType::Enum(_) => "const int",
        };
        params.push(SwigParam {
            text: format!("{} *IN_ARRAY /* {} */", c_type, input.name),
            trailing_comment: None,
        });
    }

    for opt in &func.optional_inputs {
        let (c_type, marker) = match opt.param_type {
            ParamType::Real => ("double", "OPT_REAL"),
            ParamType::Integer => ("int", "OPT_INT"),
            ParamType::Enum(_) => ("int", "OPT_INT"),
        };
        let trailing = opt
            .range
            .map(|(min, max)| format!(" /* From {} to {} */", min, max));
        params.push(SwigParam {
            text: format!("{}           {} /* {} */", c_type, marker, opt.name),
            trailing_comment: trailing,
        });
    }

    params.push(SwigParam {
        text: "int          *BEG_IDX".to_string(),
        trailing_comment: None,
    });
    params.push(SwigParam {
        text: "int          *OUT_SIZE".to_string(),
        trailing_comment: None,
    });

    for output in &func.outputs {
        let c_type = match output.param_type {
            ParamType::Real => "double",
            ParamType::Integer | ParamType::Enum(_) => "int",
        };
        let padded = format!("{:width$}*OUT_ARRAY /* {} */", c_type, output.name, width = 13);
        params.push(SwigParam {
            text: padded,
            trailing_comment: None,
        });
    }

    // Format the function signature
    let sig_prefix = format!("TA_RetCode {}( ", prefix);
    let indent = " ".repeat(sig_prefix.len());

    out.push_str(&sig_prefix);
    let last = params.len() - 1;
    for (i, param) in params.iter().enumerate() {
        if i > 0 {
            out.push_str(&format!("\n{}", indent));
        }
        out.push_str(&param.text);
        if i < last {
            out.push(',');
            if let Some(ref comment) = param.trailing_comment {
                out.push_str(comment);
            }
        }
    }
    out.push_str(" );\n");

    out
}

/// Generate the lookback function declaration.
fn gen_lookback_decl(func: &FuncDef) -> String {
    match &func.lookback {
        Some(LookbackExpr::Literal(_)) | None => {
            format!("int TA_{}_Lookback( void );\n", func.name)
        }
        Some(LookbackExpr::ParamMinus(param, _)) => {
            let opt = func
                .optional_inputs
                .iter()
                .find(|o| o.name == *param);
            let c_type = match opt {
                Some(o) => match o.param_type {
                    ParamType::Real => "double",
                    ParamType::Integer | ParamType::Enum(_) => "int",
                },
                None => "int",
            };
            let range_comment = match opt.and_then(|o| o.range) {
                Some((min, max)) => format!("  /* From {} to {} */", min, max),
                None => String::new(),
            };
            format!(
                "int TA_{}_Lookback( {}           {} );{}\n",
                func.name, c_type, param, range_comment
            )
        }
        Some(LookbackExpr::Code(_)) => {
            if func.optional_inputs.is_empty() {
                return format!("int TA_{}_Lookback( void );\n", func.name);
            }
            // Code lookback uses optional params
            let params: Vec<String> = func.optional_inputs.iter().map(|opt| {
                let c_type = match opt.param_type {
                    ParamType::Real => "double",
                    ParamType::Integer | ParamType::Enum(_) => "int",
                };
                let range_comment = match opt.range {
                    Some((min, max)) => format!("  /* From {} to {} */", min, max),
                    None => String::new(),
                };
                format!("{}           {}{}", c_type, opt.name, range_comment)
            }).collect();
            return format!(
                "int TA_{}_Lookback( {} );\n",
                func.name, params.join(", ")
            );
        }
    }
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
    fn test_swig_generates_logic_declaration() {
        let func = load_sma();
        let enums = HashMap::new();
        let registry = make_registry();
        let output = generate(&func, &enums, &registry);

        // Should contain the logic variant declaration
        assert!(output.contains("TA_SMA_Logic("), "Missing TA_SMA_Logic declaration");

        // Should still contain the regular declaration
        assert!(output.contains("TA_SMA(") || output.contains("TA_RetCode TA_SMA("),
            "Missing regular TA_SMA declaration");
    }
}
