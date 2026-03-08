use crate::ir::*;

pub fn generate(func: &FuncDef) -> String {
    let mut out = String::new();
    out.push_str(&gen_header(func));
    out.push_str(&gen_lookback(func));
    out.push_str(&gen_func(func, false)); // double-precision
    out.push_str(&gen_func(func, true)); // single-precision
    out
}

fn gen_header(_func: &FuncDef) -> String {
    let mut out = String::new();
    out.push_str(
        "/* TA-LIB Copyright (c) 1999-2025, Mario Fortier\n\
         * All rights reserved.\n\
         *\n\
         * Redistribution and use in source and binary forms, with or\n\
         * without modification, are permitted provided that the following\n\
         * conditions are met:\n\
         *\n\
         * - Redistributions of source code must retain the above copyright\n\
         *   notice, this list of conditions and the following disclaimer.\n\
         *\n\
         * - Redistributions in binary form must reproduce the above copyright\n\
         *   notice, this list of conditions and the following disclaimer in\n\
         *   the documentation and/or other materials provided with the\n\
         *   distribution.\n\
         *\n\
         * - Neither name of author nor the names of its contributors\n\
         *   may be used to endorse or promote products derived from this\n\
         *   software without specific prior written permission.\n\
         *\n\
         * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS\n\
         * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT\n\
         * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS\n\
         * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE\n\
         * REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,\n\
         * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES\n\
         * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS\n\
         * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS\n\
         * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,\n\
         * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE\n\
         * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,\n\
         * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.\n\
         */\n\n",
    );

    out.push_str(
        "#include <string.h>\n\
         #include <math.h>\n\
         #include \"ta_func.h\"\n\n",
    );

    out
}

fn gen_lookback(func: &FuncDef) -> String {
    let name = &func.name;

    let has_opt_params = !func.optional_inputs.is_empty();

    // Build parameter list for signature
    let param_str = if has_opt_params {
        let params: Vec<String> = func
            .optional_inputs
            .iter()
            .map(|opt| {
                let c_type = match opt.param_type {
                    ParamType::Real => "double",
                    ParamType::Integer => "int",
                };
                format!("{} {}", c_type, opt.name)
            })
            .collect();
        format!(" {} ", params.join(", "))
    } else {
        " void ".to_string()
    };

    let body = match &func.lookback {
        LookbackExpr::Literal(n) => format!("   return {};\n", n),
        LookbackExpr::ParamMinus(param, offset) => {
            format!("   return {} - {};\n", param, offset)
        }
        LookbackExpr::Code(stmts) => render_lookback_code(stmts),
    };

    format!(
        "TA_LIB_API int TA_{}_Lookback({})\n\
         {{\n\
         {}\
         }}\n\n",
        name, param_str, body
    )
}

fn gen_func(func: &FuncDef, single_precision: bool) -> String {
    let mut out = String::new();

    let prefix = if single_precision {
        format!("TA_S_{}", func.name)
    } else {
        format!("TA_{}", func.name)
    };

    let ret_type = if single_precision {
        "TA_RetCode"
    } else {
        "TA_LIB_API TA_RetCode"
    };

    // Build parameter list
    let mut params: Vec<String> = Vec::new();
    params.push("int    startIdx".to_string());
    params.push("int    endIdx".to_string());

    for input in &func.inputs {
        let c_type = if single_precision {
            match input.param_type {
                ParamType::Real => "const float",
                ParamType::Integer => "const int",
            }
        } else {
            match input.param_type {
                ParamType::Real => "const double",
                ParamType::Integer => "const int",
            }
        };
        params.push(format!("{} {}[]", c_type, input.name));
    }

    for opt in &func.optional_inputs {
        let c_type = match opt.param_type {
            ParamType::Real => "double",
            ParamType::Integer => "int",
        };
        params.push(format!("{} {}", c_type, opt.name));
    }

    // Output scalars (always present)
    params.push("int          *outBegIdx".to_string());
    params.push("int          *outNBElement".to_string());

    for output in &func.outputs {
        let c_type = match output.param_type {
            ParamType::Real => "double",
            ParamType::Integer => "int",
        };
        params.push(format!("{}        {}[]", c_type, output.name));
    }

    // Format the function signature
    let indent = " ".repeat(ret_type.len() + 1 + prefix.len() + 2);
    out.push_str(&format!("{} {}( ", ret_type, prefix));
    for (i, param) in params.iter().enumerate() {
        if i > 0 {
            out.push_str(&format!(",\n{}", indent));
        }
        out.push_str(param);
    }
    out.push_str(" )\n");

    // Function body
    out.push_str("{\n");

    // Declare local variables from body
    for stmt in &func.body {
        if let Statement::VarDecl { var_type, name, .. } = stmt {
            let c_type = match var_type {
                VarType::Real => "double",
                VarType::Integer => "int",
                VarType::Index => "int",
            };
            out.push_str(&format!("   {} {};\n", c_type, name));
        }
    }
    // Return statements are handled by body rendering; skip has no standalone decls.

    out.push('\n');

    // Validation
    out.push_str("   if( startIdx < 0 )\n");
    out.push_str("      return TA_OUT_OF_RANGE_START_INDEX;\n");
    out.push_str("   if( (endIdx < 0) || (endIdx < startIdx) )\n");
    out.push_str("      return TA_OUT_OF_RANGE_END_INDEX;\n");
    out.push('\n');

    // Emit VarDecl initializations (the declarations were already emitted above)
    for stmt in &func.body {
        if let Statement::VarDecl { name, init: Some(init), .. } = stmt {
            out.push_str(&format!(
                "   {} = {};\n",
                name,
                render_expr(init, single_precision)
            ));
        }
    }

    // Render remaining body statements (skip VarDecl since we already handled those)
    for stmt in &func.body {
        if matches!(stmt, Statement::VarDecl { .. }) {
            continue;
        }
        out.push_str(&render_statement(stmt, 3, single_precision));
    }

    out.push_str("\n   return TA_SUCCESS;\n");
    out.push_str("}\n\n");

    out
}

fn render_statement(stmt: &Statement, indent: usize, single_precision: bool) -> String {
    let pad = " ".repeat(indent);
    match stmt {
        Statement::VarDecl {
            var_type,
            name,
            init,
        } => {
            let c_type = match var_type {
                VarType::Real => "double",
                VarType::Integer => "int",
                VarType::Index => "int",
            };
            match init {
                Some(init_expr) => format!(
                    "{}{} {} = {};\n",
                    pad,
                    c_type,
                    name,
                    render_expr(init_expr, single_precision)
                ),
                None => format!("{}{} {};\n", pad, c_type, name),
            }
        }
        Statement::Assign { target, value, compound } => {
            // Statement-level FuncCall: when target is Var("_"), render just the expansion
            if let Expr::Var(tname) = target {
                if tname == "_" {
                    if let Expr::FuncCall(fname, args) = value {
                        return format!(
                            "{}{};\n",
                            pad,
                            render_func_call(fname, args, single_precision)
                        );
                    }
                }
            }
            // Only fold compound assignments if the original source used +=/-=/etc.
            if *compound {
                if let (Expr::Var(tname), Expr::BinOp(left, op, right)) = (target, value) {
                    if let Expr::Var(lname) = left.as_ref() {
                        if lname == tname {
                            let op_str = match op {
                                BinOp::Add => "+=",
                                BinOp::Sub => "-=",
                                BinOp::Mul => "*=",
                                BinOp::Div => "/=",
                                _ => "",
                            };
                            if !op_str.is_empty() {
                                let target_str = render_assign_target(target, single_precision);
                                return format!(
                                    "{}{}{} {};\n",
                                    pad,
                                    target_str,
                                    op_str,
                                    render_expr(right, single_precision)
                                );
                            }
                        }
                    }
                }
            }
            let target_str = render_assign_target(target, single_precision);
            let value_str = render_expr(value, single_precision);
            format!("{}{}= {};\n", pad, target_str, value_str)
        }
        Statement::While { condition, body } => {
            let mut out = format!(
                "{}while( {} )\n{}{{\n",
                pad,
                render_expr(condition, single_precision),
                pad
            );
            for s in body {
                out.push_str(&render_statement(s, indent + 3, single_precision));
            }
            out.push_str(&format!("{}}}\n", pad));
            out
        }
        Statement::If {
            condition,
            then_body,
            else_body,
        } => {
            let mut out = format!(
                "{}if( {} )\n{}{{\n",
                pad,
                render_expr(condition, single_precision),
                pad
            );
            for s in then_body {
                out.push_str(&render_statement(s, indent + 3, single_precision));
            }
            if else_body.is_empty() {
                out.push_str(&format!("{}}}\n", pad));
            } else {
                out.push_str(&format!("{}}} else ", pad));
                // Check if the else body is a single if statement (else-if chain)
                if else_body.len() == 1 {
                    if let Statement::If { .. } = &else_body[0] {
                        let if_str = render_statement(&else_body[0], indent, single_precision);
                        out.push_str(if_str.trim_start());
                        return out;
                    }
                }
                out.push_str(&format!("\n{}{{\n", pad));
                for s in else_body {
                    out.push_str(&render_statement(s, indent + 3, single_precision));
                }
                out.push_str(&format!("{}}}\n", pad));
            }
            out
        }
        Statement::Return { value } => {
            let ret_val = match value.as_str() {
                "SUCCESS" => "TA_SUCCESS",
                "BadParam" => "TA_BAD_PARAM",
                "OutOfRangeEndIndex" => "TA_OUT_OF_RANGE_END_INDEX",
                "OutOfRangeStartIndex" => "TA_OUT_OF_RANGE_START_INDEX",
                _ => value.as_str(),
            };
            format!("{}return {};\n", pad, ret_val)
        }
        Statement::For { var, count, body } => {
            let mut out = format!(
                "{}for( {} = {}; {} > 0; {}-- )\n{}{{\n",
                pad,
                var,
                render_expr(count, single_precision),
                var,
                var,
                pad
            );
            for s in body {
                out.push_str(&render_statement(s, indent + 3, single_precision));
            }
            out.push_str(&format!("{}}}\n", pad));
            out
        }
        Statement::Block { body } => {
            let mut out = String::new();
            for s in body {
                out.push_str(&render_statement(s, indent, single_precision));
            }
            out
        }
    }
}

fn render_assign_target(expr: &Expr, single_precision: bool) -> String {
    match expr {
        Expr::Var(name) if name == "outBegIdx" || name == "outNBElement" => {
            format!("*{} ", name)
        }
        Expr::Var(name) => format!("{} ", name),
        Expr::ArrayAccess(name, idx) => {
            format!("{}[{}] ", name, render_expr(idx, single_precision))
        }
        _ => render_expr(expr, single_precision),
    }
}

fn render_expr(expr: &Expr, single_precision: bool) -> String {
    match expr {
        Expr::Literal(f) => {
            if *f == f.floor() && f.abs() < 1e15 {
                format!("{}", *f as i64)
            } else {
                format!("{}", f)
            }
        }
        Expr::IntLiteral(i) => format!("{}", i),
        Expr::Var(name) => match name.as_str() {
            "COMPATIBILITY" => "TA_GLOBALS_COMPATIBILITY".to_string(),
            "METASTOCK" => {
                "ENUM_VALUE(Compatibility,TA_COMPATIBILITY_METASTOCK,Metastock)".to_string()
            }
            _ => name.clone(),
        },
        Expr::ArrayAccess(name, idx) => {
            format!("{}[{}]", name, render_expr(idx, single_precision))
        }
        Expr::BinOp(left, op, right) => {
            let op_str = match op {
                BinOp::Add => "+",
                BinOp::Sub => "-",
                BinOp::Mul => "*",
                BinOp::Div => "/",
                BinOp::LessEq => "<=",
                BinOp::Less => "<",
                BinOp::Greater => ">",
                BinOp::GreaterEq => ">=",
                BinOp::Eq => "==",
                BinOp::NotEq => "!=",
                BinOp::And => "&&",
                BinOp::Or => "||",
            };
            format!(
                "({}{}{})",
                render_expr(left, single_precision),
                op_str,
                render_expr(right, single_precision)
            )
        }
        Expr::Cast(var_type, inner) => {
            let c_type = match var_type {
                VarType::Real => "double",
                VarType::Integer => "int",
                VarType::Index => "int",
            };
            format!("(({}){})", c_type, render_expr(inner, single_precision))
        }
        Expr::Not(inner) => {
            format!("!({})", render_expr(inner, single_precision))
        }
        Expr::FuncCall(name, args) => render_func_call(name, args, single_precision),
    }
}

/// Convert a function identifier to PascalCase.
/// e.g., "RSI" -> "Rsi", "SMA" -> "Sma"
fn to_pascal_case(s: &str) -> String {
    let lower = s.to_lowercase();
    let mut chars = lower.chars();
    match chars.next() {
        None => String::new(),
        Some(c) => c.to_uppercase().collect::<String>() + chars.as_str(),
    }
}

/// Render a FuncCall expression to C code.
fn render_func_call(fname: &str, args: &[Expr], single_precision: bool) -> String {
    if fname == "UNSTABLE_PERIOD" {
        // UNSTABLE_PERIOD(RSI) -> TA_GLOBALS_UNSTABLE_PERIOD(TA_FUNC_UNST_RSI,Rsi)
        if let Some(Expr::Var(func_name)) = args.first() {
            let upper = func_name.to_uppercase();
            let pascal = to_pascal_case(func_name);
            return format!(
                "TA_GLOBALS_UNSTABLE_PERIOD(TA_FUNC_UNST_{},{})",
                upper, pascal
            );
        }
        "TA_GLOBALS_UNSTABLE_PERIOD(0,0)".to_string()
    } else if fname == "IS_ZERO" {
        // IS_ZERO(x) -> TA_IS_ZERO(x)
        if let Some(arg) = args.first() {
            let x = render_expr(arg, single_precision);
            return format!("TA_IS_ZERO({})", x);
        }
        "TA_IS_ZERO(0)".to_string()
    } else if fname == "ARRAY_COPY" {
        // ARRAY_COPY(dst, dstOff, src, srcOff, count)
        if args.len() == 5 {
            let rendered: Vec<String> = args.iter().map(|a| render_expr(a, single_precision)).collect();
            let macro_name = if single_precision {
                "ARRAY_MEMMOVEMIX"
            } else {
                "ARRAY_MEMMOVE"
            };
            return format!(
                "{}({},{},{},{},{})",
                macro_name, rendered[0], rendered[1], rendered[2], rendered[3], rendered[4]
            );
        }
        "/* ARRAY_COPY: bad args */".to_string()
    } else if fname.ends_with("_Lookback") {
        // RSI_Lookback(args...) -> TA_RSI_Lookback(args...)
        let rendered: Vec<String> = args.iter().map(|a| render_expr(a, single_precision)).collect();
        format!("TA_{}({})", fname, rendered.join(","))
    } else {
        // Generic: prefix with TA_
        let rendered: Vec<String> = args.iter().map(|a| render_expr(a, single_precision)).collect();
        format!("TA_{}({})", fname, rendered.join(","))
    }
}

/// Render a complex lookback body (LookbackExpr::Code) into C code.
fn render_lookback_code(stmts: &[Statement]) -> String {
    let mut out = String::new();

    // Declare local variables
    for stmt in stmts {
        if let Statement::VarDecl { var_type, name, .. } = stmt {
            let c_type = match var_type {
                VarType::Real => "double",
                VarType::Integer => "int",
                VarType::Index => "int",
            };
            out.push_str(&format!("   {} {};\n", c_type, name));
        }
    }

    // Emit VarDecl initializations
    for stmt in stmts {
        if let Statement::VarDecl { name, init: Some(init), .. } = stmt {
            out.push_str(&format!(
                "   {} = {};\n",
                name,
                render_expr(init, false)
            ));
        }
    }

    // Render non-VarDecl statements
    for stmt in stmts {
        if matches!(stmt, Statement::VarDecl { .. }) {
            continue;
        }
        out.push_str(&render_statement(stmt, 3, false));
    }

    out
}
