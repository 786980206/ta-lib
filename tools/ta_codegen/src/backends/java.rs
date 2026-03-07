use crate::ir::*;

pub fn generate(func: &FuncDef) -> String {
    let mut out = String::new();
    out.push_str("/* Generated */\n");
    out.push_str(&gen_lookback(func));
    out.push_str(&gen_func(func, false)); // double-precision
    out.push_str(&gen_func(func, true)); // single-precision (float inputs)
    out
}

fn gen_lookback(func: &FuncDef) -> String {
    let name = func.name.to_lowercase();
    let body = match &func.lookback {
        LookbackExpr::Literal(n) => format!("      return {};", n),
        LookbackExpr::ParamMinus(param, offset) => {
            format!("      return {} - {};", param, offset)
        }
    };

    format!(
        "   public int {}Lookback( )\n\
         \x20  {{\n\
         {}\n\
         \x20  }}\n",
        name, body
    )
}

fn gen_func(func: &FuncDef, single_precision: bool) -> String {
    let mut out = String::new();
    let name = func.name.to_lowercase();

    // Build parameter list
    let mut params: Vec<String> = Vec::new();
    params.push("int startIdx".to_string());
    params.push("int endIdx".to_string());

    for input in &func.inputs {
        let java_type = if single_precision {
            match input.param_type {
                ParamType::Real => "float",
                ParamType::Integer => "int",
            }
        } else {
            match input.param_type {
                ParamType::Real => "double",
                ParamType::Integer => "int",
            }
        };
        params.push(format!("{} {}[]", java_type, input.name));
    }

    for opt in &func.optional_inputs {
        let java_type = match opt.param_type {
            ParamType::Real => "double",
            ParamType::Integer => "int",
        };
        params.push(format!("{} {}", java_type, opt.name));
    }

    params.push("MInteger outBegIdx".to_string());
    params.push("MInteger outNBElement".to_string());

    for output in &func.outputs {
        let java_type = match output.param_type {
            ParamType::Real => "double",
            ParamType::Integer => "int",
        };
        params.push(format!("{} {}[]", java_type, output.name));
    }

    // Format signature
    let sig_prefix = format!("   public RetCode {}( ", name);
    let indent = " ".repeat(sig_prefix.len());
    out.push_str(&sig_prefix);
    for (i, param) in params.iter().enumerate() {
        if i > 0 {
            out.push_str(&format!(",\n{}", indent));
        }
        out.push_str(param);
    }
    out.push_str(" )\n");

    // Body
    out.push_str("   {\n");

    // Declare local variables
    for stmt in &func.body {
        if let Statement::VarDecl { var_type, name, .. } = stmt {
            let java_type = match var_type {
                VarType::Real => "double",
                VarType::Integer => "int",
                VarType::Index => "int",
            };
            out.push_str(&format!("      {} {};\n", java_type, name));
        }
    }

    // Validation
    out.push_str("      if( startIdx < 0 ) {\n");
    out.push_str("         return RetCode.OutOfRangeStartIndex ;\n");
    out.push_str("      }\n");
    out.push_str("      if( (endIdx < 0) || (endIdx < startIdx)) {\n");
    out.push_str("         return RetCode.OutOfRangeEndIndex ;\n");
    out.push_str("      }\n");

    // Emit VarDecl initializations
    for stmt in &func.body {
        if let Statement::VarDecl { name, init: Some(init), .. } = stmt {
            out.push_str(&format!(
                "      {} = {};\n",
                name,
                render_expr(init, single_precision)
            ));
        }
    }

    // Render body statements (skip VarDecls)
    for stmt in &func.body {
        if matches!(stmt, Statement::VarDecl { .. }) {
            continue;
        }
        out.push_str(&render_statement(stmt, 6, single_precision));
    }

    // Assign output scalars and return
    out.push_str("      return RetCode.Success ;\n");
    out.push_str("   }\n");

    out
}

fn render_statement(stmt: &Statement, indent: usize, single_precision: bool) -> String {
    let pad = " ".repeat(indent);
    match stmt {
        Statement::VarDecl { .. } => String::new(),
        Statement::Assign { target, value, compound } => {
            // Handle output scalar assignments via .value
            if let Expr::Var(name) = target {
                if name == "outBegIdx" || name == "outNBElement" {
                    return format!(
                        "{}{}.value = {};\n",
                        pad,
                        name,
                        render_expr(value, single_precision)
                    );
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
                                    "{}{} {} {};\n",
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
            format!("{}{} = {};\n", pad, target_str, value_str)
        }
        Statement::While { condition, body } => {
            let mut out = format!(
                "{}while( {} ) {{\n",
                pad,
                render_expr(condition, single_precision)
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
                "{}if( {} ) {{\n",
                pad,
                render_expr(condition, single_precision)
            );
            for s in then_body {
                out.push_str(&render_statement(s, indent + 3, single_precision));
            }
            if else_body.is_empty() {
                out.push_str(&format!("{}}}\n", pad));
            } else {
                out.push_str(&format!("{}}} else ", pad));
                if else_body.len() == 1 {
                    if let Statement::If { .. } = &else_body[0] {
                        let if_str = render_statement(&else_body[0], indent, single_precision);
                        out.push_str(if_str.trim_start());
                        return out;
                    }
                }
                out.push_str("{\n");
                for s in else_body {
                    out.push_str(&render_statement(s, indent + 3, single_precision));
                }
                out.push_str(&format!("{}}}\n", pad));
            }
            out
        }
        Statement::Return { value } => {
            let ret_val = match value.as_str() {
                "SUCCESS" => "RetCode.Success",
                "BadParam" => "RetCode.BadParam",
                "OutOfRangeEndIndex" => "RetCode.OutOfRangeEndIndex",
                "OutOfRangeStartIndex" => "RetCode.OutOfRangeStartIndex",
                _ => value.as_str(),
            };
            format!("{}return {} ;\n", pad, ret_val)
        }
    }
}

fn render_assign_target(expr: &Expr, single_precision: bool) -> String {
    match expr {
        Expr::Var(name) => name.clone(),
        Expr::ArrayAccess(name, idx) => {
            format!("{}[{}]", name, render_expr(idx, single_precision))
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
        Expr::Var(name) => name.clone(),
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
            let java_type = match var_type {
                VarType::Real => "double",
                VarType::Integer => "int",
                VarType::Index => "int",
            };
            format!("(({}){}))", java_type, render_expr(inner, single_precision))
        }
        Expr::Not(inner) => {
            format!("!({})", render_expr(inner, single_precision))
        }
    }
}
