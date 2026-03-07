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
    let body = match &func.lookback {
        LookbackExpr::Literal(n) => format!("   return {};\n", n),
        LookbackExpr::ParamMinus(param, offset) => {
            format!("   return {} - {};\n", param, offset)
        }
    };

    format!(
        "TA_LIB_API int TA_{}_Lookback( void )\n\
         {{\n\
         {}\
         }}\n\n",
        name, body
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

    out.push('\n');

    // Validation
    out.push_str("   if( startIdx < 0 )\n");
    out.push_str("      return TA_OUT_OF_RANGE_START_INDEX;\n");
    out.push_str("   if( (endIdx < 0) || (endIdx < startIdx) )\n");
    out.push_str("      return TA_OUT_OF_RANGE_END_INDEX;\n");
    out.push('\n');

    // Emit VarDecl initializations (the declarations were already emitted above)
    for stmt in &func.body {
        if let Statement::VarDecl { name, init, .. } = stmt {
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
            format!(
                "{}{} {} = {};\n",
                pad,
                c_type,
                name,
                render_expr(init, single_precision)
            )
        }
        Statement::Assign { target, value } => {
            // Detect compound assignment: x = x + expr => x += expr
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
    }
}
