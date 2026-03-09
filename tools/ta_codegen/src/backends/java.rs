use std::collections::HashMap;
use crate::ir::*;
use crate::parser::enums::lookup_variant;
use crate::registry::{Lang, Registry};

pub fn generate(func: &FuncDef, enums: &HashMap<String, EnumDef>, registry: &Registry) -> String {
    let mut out = String::new();
    out.push_str("/* Generated */\n");
    out.push_str(&gen_lookback(func, enums, registry));
    out.push_str(&gen_func(func, false, false, enums, registry)); // double-precision guarded
    out.push_str(&gen_func(func, false, true, enums, registry));  // double-precision logic (unguarded)
    out.push_str(&gen_func(func, true, false, enums, registry));  // single-precision guarded
    out.push_str(&gen_func(func, true, true, enums, registry));   // single-precision logic (unguarded)
    out
}

fn gen_lookback(func: &FuncDef, enums: &HashMap<String, EnumDef>, registry: &Registry) -> String {
    let name = func.name.to_lowercase();

    // Build parameter list for signature
    let param_str = if !func.optional_inputs.is_empty() {
        let params: Vec<String> = func
            .optional_inputs
            .iter()
            .map(|opt| {
                let java_type = match &opt.param_type {
                    ParamType::Real => "double",
                    ParamType::Integer => "int",
                    ParamType::Enum(ref name) => name.as_str(),
                    ParamType::Price(_) => unreachable!("Price expanded during parsing"),
                };
                format!("{} {}", java_type, opt.name)
            })
            .collect();
        format!(" {} ", params.join(", "))
    } else {
        " ".to_string()
    };

    let body = match &func.lookback {
        Some(LookbackExpr::Literal(n)) => format!("      return {};", n),
        Some(LookbackExpr::ParamMinus(param, offset)) => {
            format!("      return {} - {};", param, offset)
        }
        Some(LookbackExpr::Code(stmts)) => render_lookback_code(stmts, enums, registry),
        None => "      return 0;".to_string(),
    };

    format!(
        "   public int {}Lookback({})\n\
         \x20  {{\n\
         {}\n\
         \x20  }}\n",
        name, param_str, body
    )
}

fn gen_func(func: &FuncDef, single_precision: bool, logic: bool, enums: &HashMap<String, EnumDef>, registry: &Registry) -> String {
    let mut out = String::new();
    let base_name = func.name.to_lowercase();
    let name = if logic {
        format!("{}Logic", base_name)
    } else {
        base_name
    };

    // Build parameter list
    let mut params: Vec<String> = Vec::new();
    params.push("int startIdx".to_string());
    params.push("int endIdx".to_string());

    for input in &func.inputs {
        let java_type = if single_precision {
            match &input.param_type {
                ParamType::Real => "float",
                ParamType::Integer | ParamType::Enum(_) | ParamType::Price(_) => "int",
            }
        } else {
            match &input.param_type {
                ParamType::Real => "double",
                ParamType::Integer | ParamType::Enum(_) | ParamType::Price(_) => "int",
            }
        };
        params.push(format!("{} {}[]", java_type, input.name));
    }

    for opt in &func.optional_inputs {
        let java_type = match &opt.param_type {
            ParamType::Real => "double",
            ParamType::Integer => "int",
            ParamType::Enum(ref name) => name.as_str(),
            ParamType::Price(_) => unreachable!("Price expanded during parsing"),
        };
        params.push(format!("{} {}", java_type, opt.name));
    }

    params.push("MInteger outBegIdx".to_string());
    params.push("MInteger outNBElement".to_string());

    for output in &func.outputs {
        let java_type = match &output.param_type {
            ParamType::Real => "double",
            ParamType::Integer | ParamType::Enum(_) | ParamType::Price(_) => "int",
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
                VarType::RetCodeType => "RetCode",
            };
            out.push_str(&format!("      {} {};\n", java_type, name));
        }
    }

    // Validation (omitted for Logic/unguarded variant)
    if !logic {
        out.push_str("      if( startIdx < 0 ) {\n");
        out.push_str("         return RetCode.OutOfRangeStartIndex ;\n");
        out.push_str("      }\n");
        out.push_str("      if( (endIdx < 0) || (endIdx < startIdx)) {\n");
        out.push_str("         return RetCode.OutOfRangeEndIndex ;\n");
        out.push_str("      }\n");
    }

    // Emit VarDecl initializations
    for stmt in &func.body {
        if let Statement::VarDecl { name, init: Some(init), .. } = stmt {
            out.push_str(&format!(
                "      {} = {};\n",
                name,
                render_expr(init, single_precision, registry)
            ));
        }
    }

    // Render body statements (skip VarDecls)
    for stmt in &func.body {
        if matches!(stmt, Statement::VarDecl { .. }) {
            continue;
        }
        out.push_str(&render_statement(stmt, 6, single_precision, enums, registry));
    }

    // Assign output scalars and return
    out.push_str("      return RetCode.Success ;\n");
    out.push_str("   }\n");

    out
}

fn render_statement(stmt: &Statement, indent: usize, single_precision: bool, enums: &HashMap<String, EnumDef>, registry: &Registry) -> String {
    let pad = " ".repeat(indent);
    match stmt {
        Statement::VarDecl { .. } => String::new(),
        Statement::Assign { target, value, compound } => {
            // Statement-level FuncCall: when target is Var("_"), render just the expansion
            if let Expr::Var(tname) = target {
                if tname == "_" {
                    if let Expr::FuncCall(fname, args) = value {
                        return format!(
                            "{}{};\n",
                            pad,
                            render_func_call(fname, args, single_precision, registry)
                        );
                    }
                }
            }
            // Handle output scalar assignments via .value
            if let Expr::Var(name) = target {
                if name == "outBegIdx" || name == "outNBElement" {
                    return format!(
                        "{}{}.value = {};\n",
                        pad,
                        name,
                        render_expr(value, single_precision, registry)
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
                                BinOp::Mod | BinOp::LessEq | BinOp::Less
                                | BinOp::Greater | BinOp::GreaterEq | BinOp::Eq
                                | BinOp::NotEq | BinOp::And | BinOp::Or
                                | BinOp::Shr | BinOp::Shl => "",
                            };
                            if !op_str.is_empty() {
                                let target_str = render_assign_target(target, single_precision, registry);
                                return format!(
                                    "{}{} {} {};\n",
                                    pad,
                                    target_str,
                                    op_str,
                                    render_expr(right, single_precision, registry)
                                );
                            }
                        }
                    }
                }
            }

            let target_str = render_assign_target(target, single_precision, registry);
            let value_str = render_expr(value, single_precision, registry);
            format!("{}{} = {};\n", pad, target_str, value_str)
        }
        Statement::While { condition, body } => {
            let mut out = format!(
                "{}while( {} ) {{\n",
                pad,
                render_expr(condition, single_precision, registry)
            );
            for s in body {
                out.push_str(&render_statement(s, indent + 3, single_precision, enums, registry));
            }
            out.push_str(&format!("{}}}\n", pad));
            out
        }
        Statement::DoWhile { condition, body } => {
            let mut out = format!("{}do {{\n", pad);
            for s in body {
                out.push_str(&render_statement(s, indent + 3, single_precision, enums, registry));
            }
            out.push_str(&format!("{}}} while( {} );\n", pad, render_expr(condition, single_precision, registry)));
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
                render_expr(condition, single_precision, registry)
            );
            for s in then_body {
                out.push_str(&render_statement(s, indent + 3, single_precision, enums, registry));
            }
            if else_body.is_empty() {
                out.push_str(&format!("{}}}\n", pad));
            } else {
                out.push_str(&format!("{}}} else ", pad));
                if else_body.len() == 1 {
                    if let Statement::If { .. } = &else_body[0] {
                        let if_str = render_statement(&else_body[0], indent, single_precision, enums, registry);
                        out.push_str(if_str.trim_start());
                        return out;
                    }
                }
                out.push_str("{\n");
                for s in else_body {
                    out.push_str(&render_statement(s, indent + 3, single_precision, enums, registry));
                }
                out.push_str(&format!("{}}}\n", pad));
            }
            out
        }
        Statement::Return { value } => {
            match value {
                Some(expr) => {
                    let rendered = render_return_expr(expr, single_precision, registry);
                    format!("{}return {} ;\n", pad, rendered)
                }
                None => format!("{}return ;\n", pad),
            }
        }
        Statement::For { var, count, body } => {
            let mut out = format!(
                "{}for( {} = {}; {} > 0; {}-- ) {{\n",
                pad,
                var,
                render_expr(count, single_precision, registry),
                var,
                var,
            );
            for s in body {
                out.push_str(&render_statement(s, indent + 3, single_precision, enums, registry));
            }
            out.push_str(&format!("{}}}\n", pad));
            out
        }
        Statement::ForC { init, condition, update, body } => {
            let init_str = render_statement(init, 0, single_precision, enums, registry).trim().trim_end_matches(';').to_string();
            let update_str = render_statement(update, 0, single_precision, enums, registry).trim().trim_end_matches(';').to_string();
            let mut out = format!(
                "{}for( {}; {}; {} ) {{\n",
                pad, init_str.trim(), render_expr(condition, single_precision, registry), update_str.trim()
            );
            for s in body {
                out.push_str(&render_statement(s, indent + 3, single_precision, enums, registry));
            }
            out.push_str(&format!("{}}}\n", pad));
            out
        }
        Statement::Block { body } => {
            let mut out = String::new();
            for s in body {
                out.push_str(&render_statement(s, indent, single_precision, enums, registry));
            }
            out
        }
        Statement::Break => format!("{}break;\n", pad),
        Statement::Continue => format!("{}continue;\n", pad),
        Statement::Switch { expr, cases, default } => {
            let mut out = format!("{}switch( {} )\n{}{{\n", pad, render_expr(expr, single_precision, registry), pad);
            for (label, case_body) in cases {
                let java_label = render_java_switch_label(label, enums);
                out.push_str(&format!("{}case {}:\n", pad, java_label));
                for s in case_body {
                    out.push_str(&render_statement(s, indent + 3, single_precision, enums, registry));
                }
                out.push_str(&format!("{}   break;\n", pad));
            }
            if !default.is_empty() {
                out.push_str(&format!("{}default:\n", pad));
                for s in default {
                    out.push_str(&render_statement(s, indent + 3, single_precision, enums, registry));
                }
                out.push_str(&format!("{}   break;\n", pad));
            }
            out.push_str(&format!("{}}}\n", pad));
            out
        }
    }
}

fn render_java_switch_label(label: &str, enums: &HashMap<String, EnumDef>) -> String {
    if let Some((enum_name, variant)) = lookup_variant(label, enums) {
        format!("{}.{}", enum_name, variant.pascal_name)
    } else {
        label.to_string()
    }
}

fn render_assign_target(expr: &Expr, single_precision: bool, registry: &Registry) -> String {
    match expr {
        Expr::Var(name) => name.clone(),
        Expr::ArrayAccess(name, idx) => {
            format!("{}[{}]", name, render_expr(idx, single_precision, registry))
        }
        Expr::Literal(_) | Expr::IntLiteral(_) | Expr::BinOp(_, _, _)
        | Expr::Cast(_, _) | Expr::Not(_) | Expr::FuncCall(_, _)
        | Expr::PointerDeref(_) | Expr::PostIncrement(_) | Expr::PostDecrement(_)
        | Expr::Ternary(_, _, _)
        => render_expr(expr, single_precision, registry),
    }
}

/// Render a return expression, mapping known enum values to Java constants.
fn render_return_expr(expr: &Expr, single_precision: bool, registry: &Registry) -> String {
    if let Expr::Var(name) = expr {
        return match name.as_str() {
            "SUCCESS" => "RetCode.Success".to_string(),
            "BadParam" => "RetCode.BadParam".to_string(),
            "OutOfRangeEndIndex" => "RetCode.OutOfRangeEndIndex".to_string(),
            "OutOfRangeStartIndex" => "RetCode.OutOfRangeStartIndex".to_string(),
            _ => render_expr(expr, single_precision, registry),
        };
    }
    render_expr(expr, single_precision, registry)
}

fn render_expr(expr: &Expr, single_precision: bool, registry: &Registry) -> String {
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
            "COMPATIBILITY" => "this.compatibility".to_string(),
            "METASTOCK" => "Compatibility.Metastock".to_string(),
            "DEFAULT" => "Compatibility.Default".to_string(),
            "BAD_PARAM" => "RetCode.BadParam".to_string(),
            "SUCCESS" => "RetCode.Success".to_string(),
            _ => name.clone(),
        },
        Expr::ArrayAccess(name, idx) => {
            format!("{}[{}]", name, render_expr(idx, single_precision, registry))
        }
        Expr::BinOp(left, op, right) => {
            let op_str = match op {
                BinOp::Add => "+",
                BinOp::Sub => "-",
                BinOp::Mul => "*",
                BinOp::Div => "/",
                BinOp::Mod => "%",
                BinOp::LessEq => "<=",
                BinOp::Less => "<",
                BinOp::Greater => ">",
                BinOp::GreaterEq => ">=",
                BinOp::Eq => "==",
                BinOp::NotEq => "!=",
                BinOp::And => "&&",
                BinOp::Or => "||",
                BinOp::Shr => ">>",
                BinOp::Shl => "<<",
            };
            format!(
                "({}{}{})",
                render_expr(left, single_precision, registry),
                op_str,
                render_expr(right, single_precision, registry)
            )
        }
        Expr::Cast(var_type, inner) => {
            let java_type = match var_type {
                VarType::Real => "double",
                VarType::Integer => "int",
                VarType::Index => "int",
                VarType::RetCodeType => "RetCode",
            };
            format!("(({}){})", java_type, render_expr(inner, single_precision, registry))
        }
        Expr::Not(inner) => {
            format!("!({})", render_expr(inner, single_precision, registry))
        }
        Expr::FuncCall(name, args) => render_func_call(name, args, single_precision, registry),
        Expr::PointerDeref(name) => {
            // Java has no pointer dereference; output params are MInteger .value
            format!("{}.value", name)
        }
        Expr::PostIncrement(inner) => format!("{}++", render_expr(inner, single_precision, registry)),
        Expr::PostDecrement(inner) => format!("{}--", render_expr(inner, single_precision, registry)),
        Expr::Ternary(cond, then_expr, else_expr) => {
            format!(
                "({}) ? ({}) : ({})",
                render_expr(cond, single_precision, registry),
                render_expr(then_expr, single_precision, registry),
                render_expr(else_expr, single_precision, registry)
            )
        }
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

/// Render a FuncCall expression to Java code.
fn render_func_call(fname: &str, args: &[Expr], single_precision: bool, registry: &Registry) -> String {
    if fname == "UNSTABLE_PERIOD" {
        // UNSTABLE_PERIOD(RSI) -> this.unstablePeriod[FuncUnstId.Rsi.ordinal()]
        if let Some(Expr::Var(func_name)) = args.first() {
            let pascal = to_pascal_case(func_name);
            return format!("this.unstablePeriod[FuncUnstId.{}.ordinal()]", pascal);
        }
        "this.unstablePeriod[0]".to_string()
    } else if fname == "COMPATIBILITY" {
        // COMPATIBILITY() -> this.compatibility
        "this.compatibility".to_string()
    } else if fname == "IS_ZERO" {
        // IS_ZERO(x) -> inline epsilon check
        if let Some(arg) = args.first() {
            let x = render_expr(arg, single_precision, registry);
            return format!(
                "((-0.00000000000001 < {}) && ({} < 0.00000000000001))",
                x, x
            );
        }
        "false".to_string()
    } else if fname == "ARRAY_COPY" {
        // ARRAY_COPY(dst, dstOff, src, srcOff, count)
        // -> System.arraycopy(src, srcOff, dst, dstOff, count) (note arg reordering)
        if args.len() == 5 {
            let dst = render_expr(&args[0], single_precision, registry);
            let dst_off = render_expr(&args[1], single_precision, registry);
            let src = render_expr(&args[2], single_precision, registry);
            let src_off = render_expr(&args[3], single_precision, registry);
            let count = render_expr(&args[4], single_precision, registry);
            return format!(
                "System.arraycopy({},{},{},{},{})",
                src, src_off, dst, dst_off, count
            );
        }
        "/* ARRAY_COPY: bad args */".to_string()
    } else if fname == "PER_TO_K" {
        // PER_TO_K(period) -> (2.0 / ((double)(period) + 1.0))
        if let Some(arg) = args.first() {
            let x = render_expr(arg, single_precision, registry);
            return format!("(2.0 / ((double)({}) + 1.0))", x);
        }
        "0.0".to_string()
    } else {
        // Use registry for cross-call resolution
        let java_name = registry.resolve_call(fname, Lang::Java);
        let rendered: Vec<String> = args.iter().map(|a| render_expr(a, single_precision, registry)).collect();
        format!("{}({})", java_name, rendered.join(", "))
    }
}

/// Render a complex lookback body (LookbackExpr::Code) into Java code.
fn render_lookback_code(stmts: &[Statement], enums: &HashMap<String, EnumDef>, registry: &Registry) -> String {
    let mut out = String::new();

    // Declare local variables
    for stmt in stmts {
        if let Statement::VarDecl { var_type, name, .. } = stmt {
            let java_type = match var_type {
                VarType::Real => "double",
                VarType::Integer => "int",
                VarType::Index => "int",
                VarType::RetCodeType => "RetCode",
            };
            out.push_str(&format!("      {} {};\n", java_type, name));
        }
    }

    // Emit VarDecl initializations
    for stmt in stmts {
        if let Statement::VarDecl { name, init: Some(init), .. } = stmt {
            out.push_str(&format!(
                "      {} = {};\n",
                name,
                render_expr(init, false, registry)
            ));
        }
    }

    // Render non-VarDecl statements
    for stmt in stmts {
        if matches!(stmt, Statement::VarDecl { .. }) {
            continue;
        }
        out.push_str(&render_statement(stmt, 6, false, enums, registry));
    }

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
    fn test_java_generates_logic_variant() {
        let func = load_sma();
        let enums = HashMap::new();
        let registry = make_registry();
        let output = generate(&func, &enums, &registry);

        // Should contain the logic variant
        assert!(output.contains("smaLogic("), "Missing smaLogic function");

        // Logic variant should NOT have validation
        // Find the smaLogic section and verify no validation
        let logic_pos = output.find("smaLogic( ").unwrap();
        let logic_section = &output[logic_pos..];
        let next_fn_pos = logic_section.find("   public RetCode").unwrap_or(logic_section.len());
        let logic_body = &logic_section[..next_fn_pos];
        assert!(
            !logic_body.contains("OutOfRangeStartIndex"),
            "Logic variant should not contain validation"
        );

        // The guarded variant should have validation
        let guarded_pos = output.find("public RetCode sma( ").unwrap();
        let guarded_section = &output[guarded_pos..];
        let guarded_end = guarded_section.find("public RetCode smaLogic(").unwrap_or(guarded_section.len());
        let guarded_body = &guarded_section[..guarded_end];
        assert!(
            guarded_body.contains("OutOfRangeStartIndex"),
            "Guarded variant should contain validation"
        );
    }
}
