use crate::ir::*;

pub fn generate(func: &FuncDef) -> String {
    let mut out = String::new();
    out.push_str(&gen_comment_block(func));
    out.push_str(&gen_func_decl(func));
    out.push('\n');
    out.push_str(&gen_lookback_decl(func));
    out.push('\n');
    out
}

/// Generate the comment block describing the function.
fn gen_comment_block(func: &FuncDef) -> String {
    let mut out = String::new();
    let default_desc = format!("TA_{}", func.name);
    let desc = func.description.as_deref().unwrap_or(&default_desc);

    out.push_str("/*\n");
    out.push_str(&format!(" * TA_{} - {}\n", func.name, desc));
    out.push_str(" *\n");

    // Input type summary
    let input_types: Vec<&str> = func
        .inputs
        .iter()
        .map(|i| match i.param_type {
            ParamType::Real => "double",
            ParamType::Integer => "int",
        })
        .collect();
    out.push_str(&format!(" * Input  = {}\n", input_types.join(", ")));

    // Output type summary
    let output_types: Vec<&str> = func
        .outputs
        .iter()
        .map(|o| match o.param_type {
            ParamType::Real => "double",
            ParamType::Integer => "int",
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

/// Generate the main function declaration with SWIG typemap markers.
fn gen_func_decl(func: &FuncDef) -> String {
    let mut out = String::new();
    let prefix = format!("TA_{}", func.name);

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
            ParamType::Integer => "const int",
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
            ParamType::Integer => "int",
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
        LookbackExpr::Literal(_) => {
            format!("int TA_{}_Lookback( void );\n", func.name)
        }
        LookbackExpr::ParamMinus(param, _) => {
            let opt = func
                .optional_inputs
                .iter()
                .find(|o| o.name == *param);
            let c_type = match opt {
                Some(o) => match o.param_type {
                    ParamType::Real => "double",
                    ParamType::Integer => "int",
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
    }
}
