use std::cell::Cell;
use std::collections::HashMap;

use crate::candle_settings::{detect_candle_settings, emit_java_unpacking};
use crate::helper_registry::{hoist_block_helpers, try_inline_expr, HelperRegistry};
use crate::ir::{BinOp, EnumDef, Expr, FuncDef, LookbackExpr, ParamType, Statement, VarType};
use crate::parser::enums::lookup_variant;
use crate::registry::{Lang, Registry};

/// Check if a statement list contains a return with ALLOC_ERR value.
fn contains_alloc_err_return(stmts: &[Statement]) -> bool {
    stmts.iter().any(|s| matches!(s, Statement::Return { value: Some(Expr::Var(name)) } if name == "ALLOC_ERR"))
}

#[allow(clippy::implicit_hasher)]
pub fn generate(
    func: &FuncDef,
    enums: &HashMap<String, EnumDef>,
    registry: &Registry,
    helpers: &HelperRegistry,
) -> String {
    let mut out = String::new();
    out.push_str("/* Generated */\n");
    out.push_str(&gen_lookback(func, enums, registry, helpers));
    out.push_str(&gen_func(func, false, false, enums, registry, helpers)); // double-precision guarded
    out.push_str(&gen_func(func, false, true, enums, registry, helpers)); // double-precision logic (unguarded)
    out.push_str(&gen_func(func, true, false, enums, registry, helpers)); // single-precision guarded
    out.push_str(&gen_func(func, true, true, enums, registry, helpers)); // single-precision logic (unguarded)
    out
}

fn gen_lookback(
    func: &FuncDef,
    enums: &HashMap<String, EnumDef>,
    registry: &Registry,
    helpers: &HelperRegistry,
) -> String {
    let name = func.name.to_lowercase();

    // Build parameter list for signature
    let param_str = if func.optional_inputs.is_empty() {
        " ".to_string()
    } else {
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
    };

    let body = match &func.lookback {
        Some(LookbackExpr::Literal(n)) => format!("      return {n};"),
        Some(LookbackExpr::ParamMinus(param, offset)) => {
            format!("      return {param} - {offset};")
        }
        Some(LookbackExpr::Code(stmts)) => render_lookback_code(stmts, enums, registry, helpers),
        None => "      return 0;".to_string(),
    };

    format!(
        "   public int {name}Lookback({param_str})\n\
         \x20  {{\n\
         {body}\n\
         \x20  }}\n"
    )
}

#[allow(clippy::too_many_lines)]
fn gen_func(
    func: &FuncDef,
    single_precision: bool,
    logic: bool,
    enums: &HashMap<String, EnumDef>,
    registry: &Registry,
    helpers: &HelperRegistry,
) -> String {
    let mut out = String::new();
    let base_name = func.name.to_lowercase();
    let name = if logic {
        format!("{base_name}Logic")
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
    let sig_prefix = format!("   public RetCode {name}( ");
    let indent = " ".repeat(sig_prefix.len());
    out.push_str(&sig_prefix);
    for (i, param) in params.iter().enumerate() {
        if i > 0 {
            out.push_str(&format!(",\n{indent}"));
        }
        out.push_str(param);
    }
    out.push_str(" )\n");

    // Body
    out.push_str("   {\n");

    // Declare local variables
    for stmt in &func.body {
        if let Statement::VarDecl { var_type, name, .. } = stmt {
            let java_decl = match var_type {
                VarType::Real => format!("double {name}"),
                VarType::Integer | VarType::Index => format!("int {name}"),
                VarType::RetCodeType => format!("RetCode {name}"),
                VarType::RealPointer => format!("double[] {name}"),
                VarType::IntPointer => format!("int[] {name}"),
                VarType::RealArray(size) => format!("double[] {name} = new double[{size}]"),
                VarType::IntArray(size) => format!("int[] {name} = new int[{size}]"),
            };
            out.push_str(&format!("      {java_decl};\n"));
        }
    }

    // Emit candle settings unpacking (only for referenced settings)
    let candle_used = detect_candle_settings(&func.body);
    if !candle_used.is_empty() {
        out.push_str(&emit_java_unpacking(&candle_used, 6));
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

    let inline_counter = Cell::new(0);

    // Emit VarDecl initializations
    for stmt in &func.body {
        if let Statement::VarDecl {
            name,
            init: Some(init),
            ..
        } = stmt
        {
            // Hoist multi-statement helpers from init expressions
            let mut hoisted_vec = Vec::new();
            let mut cnt = inline_counter.get();
            let new_init = hoist_block_helpers(
                init, helpers, &mut hoisted_vec, &mut cnt,
            );
            inline_counter.set(cnt);
            out.push_str(&render_hoisted_blocks(
                &hoisted_vec,
                6,
                single_precision,
                enums,
                registry,
                helpers,
                &inline_counter,
            ));
            out.push_str(&format!(
                "      {} = {};\n",
                name,
                render_expr(&new_init, single_precision, registry, helpers)
            ));
        }
    }

    // Render body statements (skip VarDecls)
    for stmt in &func.body {
        if matches!(stmt, Statement::VarDecl { .. }) {
            continue;
        }
        out.push_str(&render_statement(
            stmt,
            6,
            single_precision,
            enums,
            registry,
            helpers,
            &inline_counter,
        ));
    }

    // Assign output scalars and return
    out.push_str("      return RetCode.Success ;\n");
    out.push_str("   }\n");

    out
}

/// Render a ForC init or update clause. If it's a Block with multiple
/// statements, comma-separate them instead of using semicolons.
fn render_forc_part(
    stmt: &Statement,
    single_precision: bool,
    enums: &HashMap<String, EnumDef>,
    registry: &Registry,
    helpers: &HelperRegistry,
    inline_counter: &Cell<usize>,
) -> String {
    match stmt {
        Statement::Block { body } => body
            .iter()
            .map(|s| {
                render_statement(
                    s, 0, single_precision, enums, registry, helpers, inline_counter,
                )
                .trim()
                .trim_end_matches(';')
                .to_string()
            })
            .collect::<Vec<_>>()
            .join(", "),
        _ => render_statement(
            stmt, 0, single_precision, enums, registry, helpers, inline_counter,
        )
        .trim()
        .trim_end_matches(';')
        .to_string(),
    }
}

/// Render hoisted block-inline helpers as Java code (temp var decl + body).
fn render_hoisted_blocks(
    hoisted: &[(String, VarType, Vec<Statement>)],
    indent: usize,
    single_precision: bool,
    enums: &HashMap<String, EnumDef>,
    registry: &Registry,
    helpers: &HelperRegistry,
    inline_counter: &Cell<usize>,
) -> String {
    let pad = " ".repeat(indent);
    let mut out = String::new();
    for (temp_name, var_type, body) in hoisted {
        let java_decl = match var_type {
            VarType::Real => format!("double {temp_name}"),
            VarType::Integer | VarType::Index => format!("int {temp_name}"),
            VarType::RetCodeType => format!("RetCode {temp_name}"),
            VarType::RealPointer => format!("double[] {temp_name}"),
            VarType::IntPointer => format!("int[] {temp_name}"),
            VarType::RealArray(size) => format!("double[] {temp_name} = new double[{size}]"),
            VarType::IntArray(size) => format!("int[] {temp_name} = new int[{size}]"),
        };
        out.push_str(&format!("{pad}{java_decl};\n"));
        for stmt in body {
            out.push_str(&render_statement(
                stmt,
                indent,
                single_precision,
                enums,
                registry,
                helpers,
                inline_counter,
            ));
        }
    }
    out
}

#[allow(clippy::too_many_lines)]
pub fn render_statement(
    stmt: &Statement,
    indent: usize,
    single_precision: bool,
    enums: &HashMap<String, EnumDef>,
    registry: &Registry,
    helpers: &HelperRegistry,
    inline_counter: &Cell<usize>,
) -> String {
    let pad = " ".repeat(indent);
    match stmt {
        Statement::VarDecl { .. } => String::new(),
        Statement::Assign {
            target,
            value,
            compound,
        } => {
            // Statement-level expression: when target is Var("_"), render as standalone
            if let Expr::Var(tname) = target {
                if tname == "_" {
                    // Skip bare variable statements (no side effects — e.g. inlined identity helpers)
                    if matches!(value, Expr::Var(_)) {
                        return String::new();
                    }
                    if let Expr::FuncCall(fname, args) = value {
                        // Check if helper inlines to a bare variable (identity helper)
                        if let Some(helper) = helpers.get(fname) {
                            if let Some(inlined) = try_inline_expr(helper, args) {
                                if matches!(inlined, Expr::Var(_)) {
                                    return String::new();
                                }
                            }
                        }
                        let rendered = render_func_call(
                            fname, args, single_precision, registry, helpers,
                        );
                        // Skip empty renders (e.g. free() returns "")
                        if rendered.is_empty() {
                            return String::new();
                        }
                        return format!("{pad}{rendered};\n");
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
                        render_expr(value, single_precision, registry, helpers)
                    );
                }
            }

            // Hoist multi-statement helpers from the value expression
            let mut hoisted = Vec::new();
            let mut cnt = inline_counter.get();
            let new_value = hoist_block_helpers(
                value, helpers, &mut hoisted, &mut cnt,
            );
            inline_counter.set(cnt);
            let mut out = render_hoisted_blocks(
                &hoisted, indent, single_precision, enums, registry,
                helpers, inline_counter,
            );

            // Only fold compound assignments if the original source used +=/-=/etc.
            if *compound {
                if let (Expr::Var(tname), Expr::BinOp(left, op, right)) = (target, &new_value) {
                    if let Expr::Var(lname) = left.as_ref() {
                        if lname == tname {
                            let op_str = match op {
                                BinOp::Add => "+=",
                                BinOp::Sub => "-=",
                                BinOp::Mul => "*=",
                                BinOp::Div => "/=",
                                BinOp::Mod
                                | BinOp::LessEq
                                | BinOp::Less
                                | BinOp::Greater
                                | BinOp::GreaterEq
                                | BinOp::Eq
                                | BinOp::NotEq
                                | BinOp::And
                                | BinOp::Or
                                | BinOp::Shr
                                | BinOp::Shl => "",
                            };
                            if !op_str.is_empty() {
                                let target_str =
                                    render_assign_target(target, single_precision, registry, helpers);
                                out.push_str(&format!(
                                    "{}{} {} {};\n",
                                    pad,
                                    target_str,
                                    op_str,
                                    render_expr(right, single_precision, registry, helpers)
                                ));
                                return out;
                            }
                        }
                    }
                }
            }

            let target_str = render_assign_target(target, single_precision, registry, helpers);
            let value_str = render_expr(&new_value, single_precision, registry, helpers);
            out.push_str(&format!("{pad}{target_str} = {value_str};\n"));
            out
        }
        Statement::While { condition, body } => {
            let mut out = format!(
                "{}while( {} ) {{\n",
                pad,
                render_expr(condition, single_precision, registry, helpers)
            );
            for s in body {
                out.push_str(&render_statement(
                    s,
                    indent + 3,
                    single_precision,
                    enums,
                    registry,
                    helpers,
                    inline_counter,
                ));
            }
            out.push_str(&format!("{pad}}}\n"));
            out
        }
        Statement::DoWhile { condition, body } => {
            let mut out = format!("{pad}do {{\n");
            for s in body {
                out.push_str(&render_statement(
                    s,
                    indent + 3,
                    single_precision,
                    enums,
                    registry,
                    helpers,
                    inline_counter,
                ));
            }
            out.push_str(&format!(
                "{}}} while( {} );\n",
                pad,
                render_expr(condition, single_precision, registry, helpers)
            ));
            out
        }
        Statement::If {
            condition,
            then_body,
            else_body,
        } => {
            // Skip post-allocation null-check blocks (dead code in Java — `new` never returns null)
            if contains_alloc_err_return(then_body) {
                return String::new();
            }
            let mut out = format!(
                "{}if( {} ) {{\n",
                pad,
                render_expr(condition, single_precision, registry, helpers)
            );
            for s in then_body {
                out.push_str(&render_statement(
                    s,
                    indent + 3,
                    single_precision,
                    enums,
                    registry,
                    helpers,
                    inline_counter,
                ));
            }
            if else_body.is_empty() {
                out.push_str(&format!("{pad}}}\n"));
            } else {
                out.push_str(&format!("{pad}}} else "));
                if else_body.len() == 1 {
                    if let Statement::If { .. } = &else_body[0] {
                        let if_str = render_statement(
                            &else_body[0],
                            indent,
                            single_precision,
                            enums,
                            registry,
                            helpers,
                            inline_counter,
                        );
                        out.push_str(if_str.trim_start());
                        return out;
                    }
                }
                out.push_str("{\n");
                for s in else_body {
                    out.push_str(&render_statement(
                        s,
                        indent + 3,
                        single_precision,
                        enums,
                        registry,
                        helpers,
                        inline_counter,
                    ));
                }
                out.push_str(&format!("{pad}}}\n"));
            }
            out
        }
        Statement::Return { value } => match value {
            Some(expr) => {
                let rendered = render_return_expr(expr, single_precision, registry, helpers);
                format!("{pad}return {rendered} ;\n")
            }
            None => format!("{pad}return ;\n"),
        },
        Statement::For { var, count, body } => {
            let mut out = format!(
                "{}for( {} = {}; {} > 0; {}-- ) {{\n",
                pad,
                var,
                render_expr(count, single_precision, registry, helpers),
                var,
                var,
            );
            for s in body {
                out.push_str(&render_statement(
                    s,
                    indent + 3,
                    single_precision,
                    enums,
                    registry,
                    helpers,
                    inline_counter,
                ));
            }
            out.push_str(&format!("{pad}}}\n"));
            out
        }
        Statement::ForC {
            init,
            condition,
            update,
            body,
        } => {
            let init_str = render_forc_part(
                init, single_precision, enums, registry, helpers, inline_counter,
            );
            let update_str = render_forc_part(
                update, single_precision, enums, registry, helpers, inline_counter,
            );
            let mut out = format!(
                "{}for( {}; {}; {} ) {{\n",
                pad,
                init_str.trim(),
                render_expr(condition, single_precision, registry, helpers),
                update_str.trim()
            );
            for s in body {
                out.push_str(&render_statement(
                    s,
                    indent + 3,
                    single_precision,
                    enums,
                    registry,
                    helpers,
                    inline_counter,
                ));
            }
            out.push_str(&format!("{pad}}}\n"));
            out
        }
        Statement::Block { body } => {
            let mut out = String::new();
            for s in body {
                out.push_str(&render_statement(
                    s,
                    indent,
                    single_precision,
                    enums,
                    registry,
                    helpers,
                    inline_counter,
                ));
            }
            out
        }
        Statement::Break => format!("{pad}break;\n"),
        Statement::Continue => format!("{pad}continue;\n"),
        Statement::Switch {
            expr,
            cases,
            default,
        } => {
            let mut out = format!(
                "{}switch( {} )\n{}{{\n",
                pad,
                render_expr(expr, single_precision, registry, helpers),
                pad
            );
            for (label, case_body) in cases {
                let java_label = render_java_switch_label(label, enums);
                out.push_str(&format!("{pad}case {java_label}:\n"));
                for s in case_body {
                    out.push_str(&render_statement(
                        s,
                        indent + 3,
                        single_precision,
                        enums,
                        registry,
                        helpers,
                        inline_counter,
                    ));
                }
                out.push_str(&format!("{pad}   break;\n"));
            }
            if !default.is_empty() {
                out.push_str(&format!("{pad}default:\n"));
                for s in default {
                    out.push_str(&render_statement(
                        s,
                        indent + 3,
                        single_precision,
                        enums,
                        registry,
                        helpers,
                        inline_counter,
                    ));
                }
                out.push_str(&format!("{pad}   break;\n"));
            }
            out.push_str(&format!("{pad}}}\n"));
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

fn render_assign_target(
    expr: &Expr,
    single_precision: bool,
    registry: &Registry,
    helpers: &HelperRegistry,
) -> String {
    match expr {
        Expr::Var(name) => name.clone(),
        Expr::ArrayAccess(name, idx) => {
            format!("{}[{}]", name, render_expr(idx, single_precision, registry, helpers))
        }
        Expr::Literal(_)
        | Expr::IntLiteral(_)
        | Expr::BinOp(_, _, _)
        | Expr::Cast(_, _)
        | Expr::Not(_)
        | Expr::FuncCall(_, _)
        | Expr::PointerDeref(_)
        | Expr::AddressOf(_)
        | Expr::PostIncrement(_)
        | Expr::PostDecrement(_)
        | Expr::PreIncrement(_)
        | Expr::PreDecrement(_)
        | Expr::Ternary(_, _, _) => render_expr(expr, single_precision, registry, helpers),
    }
}

/// Render a return expression, mapping known enum values to Java constants.
fn render_return_expr(
    expr: &Expr,
    single_precision: bool,
    registry: &Registry,
    helpers: &HelperRegistry,
) -> String {
    if let Expr::Var(name) = expr {
        return match name.as_str() {
            "SUCCESS" => "RetCode.Success".to_string(),
            "BadParam" => "RetCode.BadParam".to_string(),
            "OutOfRangeEndIndex" => "RetCode.OutOfRangeEndIndex".to_string(),
            "OutOfRangeStartIndex" => "RetCode.OutOfRangeStartIndex".to_string(),
            _ => render_expr(expr, single_precision, registry, helpers),
        };
    }
    render_expr(expr, single_precision, registry, helpers)
}

fn render_expr(
    expr: &Expr,
    single_precision: bool,
    registry: &Registry,
    helpers: &HelperRegistry,
) -> String {
    match expr {
        Expr::Literal(f) => {
            #[allow(clippy::float_cmp)]
            let is_whole = *f == f.floor() && f.abs() < 1e15;
            if is_whole {
                #[allow(clippy::cast_possible_truncation)]
                let i = *f as i64;
                format!("{i}.0")
            } else {
                format!("{f}")
            }
        }
        Expr::IntLiteral(i) => format!("{i}"),
        Expr::Var(name) => match name.as_str() {
            "COMPATIBILITY" => "this.compatibility".to_string(),
            "METASTOCK" => "Compatibility.Metastock".to_string(),
            "DEFAULT" => "Compatibility.Default".to_string(),
            "BAD_PARAM" => "RetCode.BadParam".to_string(),
            "SUCCESS" => "RetCode.Success".to_string(),
            "ALLOC_ERR" => "RetCode.AllocErr".to_string(),
            "INTERNAL_ERROR" => "RetCode.InternalError".to_string(),
            _ => name.clone(),
        },
        Expr::ArrayAccess(name, idx) => {
            format!("{}[{}]", name, render_expr(idx, single_precision, registry, helpers))
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
                render_expr(left, single_precision, registry, helpers),
                op_str,
                render_expr(right, single_precision, registry, helpers)
            )
        }
        Expr::Cast(var_type, inner) => {
            let java_type = match var_type {
                VarType::Real => "double",
                VarType::Integer | VarType::Index => "int",
                VarType::RetCodeType => "RetCode",
                VarType::RealPointer => "double[]",
                VarType::IntPointer => "int[]",
                VarType::RealArray(_) | VarType::IntArray(_) => "/* array cast */",
            };
            format!(
                "(({}){})",
                java_type,
                render_expr(inner, single_precision, registry, helpers)
            )
        }
        Expr::Not(inner) => {
            format!("!({})", render_expr(inner, single_precision, registry, helpers))
        }
        Expr::FuncCall(name, args) => render_func_call(name, args, single_precision, registry, helpers),
        Expr::PointerDeref(name) => {
            // Java has no pointer dereference; output params are MInteger .value
            format!("{name}.value")
        }
        Expr::AddressOf(inner) => {
            // Java has no address-of; render the inner expression directly
            render_expr(inner, single_precision, registry, helpers)
        }
        Expr::PostIncrement(inner) => {
            format!("{}++", render_expr(inner, single_precision, registry, helpers))
        }
        Expr::PostDecrement(inner) => {
            format!("{}--", render_expr(inner, single_precision, registry, helpers))
        }
        Expr::PreIncrement(inner) => {
            format!("++{}", render_expr(inner, single_precision, registry, helpers))
        }
        Expr::PreDecrement(inner) => {
            format!("--{}", render_expr(inner, single_precision, registry, helpers))
        }
        Expr::Ternary(cond, then_expr, else_expr) => {
            format!(
                "(({}) ? ({}) : ({}))",
                render_expr(cond, single_precision, registry, helpers),
                render_expr(then_expr, single_precision, registry, helpers),
                render_expr(else_expr, single_precision, registry, helpers)
            )
        }
    }
}

/// Convert a function identifier to `PascalCase`.
/// e.g., "RSI" -> "Rsi", "SMA" -> "Sma"
fn to_pascal_case(s: &str) -> String {
    let lower = s.to_lowercase();
    let mut chars = lower.chars();
    match chars.next() {
        None => String::new(),
        Some(c) => c.to_uppercase().collect::<String>() + chars.as_str(),
    }
}

/// Render a `FuncCall` expression to Java code.
fn render_func_call(
    fname: &str,
    args: &[Expr],
    single_precision: bool,
    registry: &Registry,
    helpers: &HelperRegistry,
) -> String {
    // Check if this is a call to a helper function that can be inlined
    if let Some(helper) = helpers.get(fname) {
        if let Some(inlined_expr) = try_inline_expr(helper, args) {
            return render_expr(&inlined_expr, single_precision, registry, helpers);
        }
        // Multi-statement helpers: Task 10 will handle
    }

    if fname == "UNSTABLE_PERIOD" {
        // UNSTABLE_PERIOD(RSI) -> this.unstablePeriod[FuncUnstId.Rsi.ordinal()]
        // UNSTABLE_PERIOD(FUNC_UNST_ATR) -> strip FUNC_UNST_ prefix first
        if let Some(Expr::Var(func_name)) = args.first() {
            let base = func_name
                .strip_prefix("FUNC_UNST_")
                .unwrap_or(func_name);
            let pascal = to_pascal_case(base);
            return format!("this.unstablePeriod[FuncUnstId.{pascal}.ordinal()]");
        }
        "this.unstablePeriod[0]".to_string()
    } else if fname == "COMPATIBILITY" {
        // COMPATIBILITY() -> this.compatibility
        "this.compatibility".to_string()
    } else if fname == "IS_ZERO" {
        // IS_ZERO(x) -> inline epsilon check
        if let Some(arg) = args.first() {
            let x = render_expr(arg, single_precision, registry, helpers);
            return format!("((-0.00000000000001 < {x}) && ({x} < 0.00000000000001))");
        }
        "false".to_string()
    } else if fname == "ARRAY_COPY" {
        // ARRAY_COPY(dst, dstOff, src, srcOff, count)
        // -> System.arraycopy(src, srcOff, dst, dstOff, count) (note arg reordering)
        if args.len() == 5 {
            let dst = render_expr(&args[0], single_precision, registry, helpers);
            let dst_off = render_expr(&args[1], single_precision, registry, helpers);
            let src = render_expr(&args[2], single_precision, registry, helpers);
            let src_off = render_expr(&args[3], single_precision, registry, helpers);
            let count = render_expr(&args[4], single_precision, registry, helpers);
            return format!("System.arraycopy({src},{src_off},{dst},{dst_off},{count})");
        }
        "/* ARRAY_COPY: bad args */".to_string()
    } else if fname == "PER_TO_K" {
        // PER_TO_K(period) -> (2.0 / ((double)(period) + 1.0))
        if let Some(arg) = args.first() {
            let x = render_expr(arg, single_precision, registry, helpers);
            return format!("(2.0 / ((double)({x}) + 1.0))");
        }
        "0.0".to_string()
    } else if MATH_FUNCTIONS.contains(&fname) {
        // Java uses Math.func() for standard math functions.
        // fabs/ABS → Math.abs; max/fmax → Math.max; min/fmin → Math.min
        let java_name = match fname {
            "fabs" | "ABS" => "abs",
            "fmax" => "max",
            "fmin" => "min",
            other => other,
        };
        let rendered: Vec<String> = args
            .iter()
            .map(|a| render_expr(a, single_precision, registry, helpers))
            .collect();
        format!("Math.{}({})", java_name, rendered.join(", "))
    } else if fname == "sizeof" {
        // sizeof(TYPE) → 1: normalizes byte counts to element counts for Java array operations
        "1".to_string()
    } else if fname == "malloc" {
        // malloc(N * sizeof(TYPE)) → new TYPE_JAVA[(int)(N)]
        // sizeof renders as 1, so the arg is already the element count
        if let Some(arg) = args.first() {
            let java_type = match find_sizeof_type(arg).as_deref() {
                Some("int") => "int",
                Some("float") => "float",
                _ => "double",
            };
            let size = render_expr(arg, single_precision, registry, helpers);
            format!("new {java_type}[(int)({size})]")
        } else {
            "new double[0]".to_string()
        }
    } else if fname == "free" {
        // No-op in Java (garbage collector handles deallocation)
        String::new()
    } else if fname == "memcpy" || fname == "memmove" {
        // memcpy/memmove(dst, src, count) → System.arraycopy(src, srcOff, dst, dstOff, count)
        if args.len() >= 3 {
            let (dst_arr, dst_off) =
                decompose_java_array_ref(&args[0], single_precision, registry, helpers);
            let (src_arr, src_off) =
                decompose_java_array_ref(&args[1], single_precision, registry, helpers);
            let count = render_expr(&args[2], single_precision, registry, helpers);
            format!("System.arraycopy({src_arr}, {src_off}, {dst_arr}, {dst_off}, {count})")
        } else {
            format!("/* {fname}: bad args */")
        }
    } else if fname == "memset" {
        // memset(buf, 0, count) → java.util.Arrays.fill(buf, off, off+count, fillVal)
        if args.len() >= 3 {
            let (arr, off) =
                decompose_java_array_ref(&args[0], single_precision, registry, helpers);
            let count = render_expr(&args[2], single_precision, registry, helpers);
            let fill_val = match find_sizeof_type(&args[2]).as_deref() {
                Some("int") => "0",
                _ => "0.0",
            };
            if off == "0" {
                format!("java.util.Arrays.fill({arr}, 0, (int)({count}), {fill_val})")
            } else {
                format!(
                    "java.util.Arrays.fill({arr}, {off}, ({off}) + (int)({count}), {fill_val})"
                )
            }
        } else {
            "/* memset: bad args */".to_string()
        }
    } else {
        // Use registry for cross-call resolution
        let java_name = registry.resolve_call(fname, Lang::Java);
        let rendered: Vec<String> = args
            .iter()
            .map(|a| render_expr(a, single_precision, registry, helpers))
            .collect();
        format!("{}({})", java_name, rendered.join(", "))
    }
}

/// Math functions that map to `java.lang.Math` methods.
/// `fabs`/`ABS` → `Math.abs`; `max`/`fmax` → `Math.max`; `min`/`fmin` → `Math.min`.
const MATH_FUNCTIONS: &[&str] = &[
    "atan", "sqrt", "fabs", "floor", "ceil", "log", "cos", "sin", "tan", "acos", "asin", "exp",
    "cosh", "sinh", "tanh", "log10", "ABS", "max", "min", "fmax", "fmin",
];

/// Scan an expression tree for `sizeof(TYPE)` and return the type name.
/// Used by `malloc` to determine the Java array element type.
fn find_sizeof_type(expr: &Expr) -> Option<String> {
    match expr {
        Expr::FuncCall(name, args) if name == "sizeof" => args
            .first()
            .and_then(|a| match a {
                Expr::Var(type_name) => Some(type_name.clone()),
                _ => None,
            }),
        Expr::BinOp(left, _, right) => {
            find_sizeof_type(left).or_else(|| find_sizeof_type(right))
        }
        Expr::Cast(_, inner) => find_sizeof_type(inner),
        _ => None,
    }
}

/// Decompose an expression into (array_name, offset) for array copy operations.
/// `Var("arr")` → `("arr", "0")`; `AddressOf(ArrayAccess("arr", idx))` → `("arr", rendered_idx)`
fn decompose_java_array_ref(
    expr: &Expr,
    single_precision: bool,
    registry: &Registry,
    helpers: &HelperRegistry,
) -> (String, String) {
    match expr {
        Expr::AddressOf(inner) => match inner.as_ref() {
            Expr::ArrayAccess(name, offset) => {
                let off = render_expr(offset, single_precision, registry, helpers);
                (name.clone(), off)
            }
            _ => {
                let s = render_expr(expr, single_precision, registry, helpers);
                (s, "0".to_string())
            }
        },
        Expr::Var(name) => (name.clone(), "0".to_string()),
        _ => {
            let s = render_expr(expr, single_precision, registry, helpers);
            (s, "0".to_string())
        }
    }
}

/// Render a complex lookback body (`LookbackExpr::Code`) into Java code.
fn render_lookback_code(
    stmts: &[Statement],
    enums: &HashMap<String, EnumDef>,
    registry: &Registry,
    helpers: &HelperRegistry,
) -> String {
    let mut out = String::new();
    let inline_counter = Cell::new(0);

    // Declare local variables
    for stmt in stmts {
        if let Statement::VarDecl { var_type, name, .. } = stmt {
            let java_decl = match var_type {
                VarType::Real => format!("double {name}"),
                VarType::Integer | VarType::Index => format!("int {name}"),
                VarType::RetCodeType => format!("RetCode {name}"),
                VarType::RealPointer => format!("double[] {name}"),
                VarType::IntPointer => format!("int[] {name}"),
                VarType::RealArray(size) => format!("double[] {name} = new double[{size}]"),
                VarType::IntArray(size) => format!("int[] {name} = new int[{size}]"),
            };
            out.push_str(&format!("      {java_decl};\n"));
        }
    }

    // Emit candle settings unpacking for lookback body
    let candle_used = detect_candle_settings(stmts);
    if !candle_used.is_empty() {
        out.push_str(&emit_java_unpacking(&candle_used, 6));
    }

    // Emit VarDecl initializations
    for stmt in stmts {
        if let Statement::VarDecl {
            name,
            init: Some(init),
            ..
        } = stmt
        {
            out.push_str(&format!(
                "      {} = {};\n",
                name,
                render_expr(init, false, registry, helpers)
            ));
        }
    }

    // Render non-VarDecl statements
    for stmt in stmts {
        if matches!(stmt, Statement::VarDecl { .. }) {
            continue;
        }
        out.push_str(&render_statement(
            stmt, 6, false, enums, registry, helpers, &inline_counter,
        ));
    }

    out
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::parser;
    use crate::registry::Registry;
    use std::path::Path;

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
        let output = generate(&func, &enums, &registry, &HelperRegistry::empty());

        // Should contain the logic variant
        assert!(output.contains("smaLogic("), "Missing smaLogic function");

        // Logic variant should NOT have validation
        // Find the smaLogic section and verify no validation
        let logic_pos = output.find("smaLogic( ").unwrap();
        let logic_section = &output[logic_pos..];
        let next_fn_pos = logic_section
            .find("   public RetCode")
            .unwrap_or(logic_section.len());
        let logic_body = &logic_section[..next_fn_pos];
        assert!(
            !logic_body.contains("OutOfRangeStartIndex"),
            "Logic variant should not contain validation"
        );

        // The guarded variant should have validation
        let guarded_pos = output.find("public RetCode sma( ").unwrap();
        let guarded_section = &output[guarded_pos..];
        let guarded_end = guarded_section
            .find("public RetCode smaLogic(")
            .unwrap_or(guarded_section.len());
        let guarded_body = &guarded_section[..guarded_end];
        assert!(
            guarded_body.contains("OutOfRangeStartIndex"),
            "Guarded variant should contain validation"
        );
    }
}
