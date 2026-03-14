use std::collections::HashMap;
use std::path::Path;

use crate::ir::{Expr, HelperDef, Statement, VarType};
use crate::parser::c_source::parse_helper_file;

/// Registry of helper functions available for inlining.
pub struct HelperRegistry {
    helpers: HashMap<String, HelperDef>,
}

impl HelperRegistry {
    /// Build the registry by scanning `base_dir/helpers/*.c`.
    pub fn from_dir(base_dir: &Path) -> Self {
        let mut helpers = HashMap::new();
        let helpers_dir = base_dir.join("helpers");

        if let Ok(entries) = std::fs::read_dir(&helpers_dir) {
            for entry in entries.filter_map(Result::ok) {
                let path = entry.path();
                if path.extension().and_then(|e| e.to_str()) == Some("c") {
                    let parsed = parse_helper_file(&path);
                    for helper in parsed {
                        helpers.insert(helper.name.clone(), helper);
                    }
                }
            }
        }

        HelperRegistry { helpers }
    }

    /// Create an empty registry (for tests that don't need helper inlining).
    pub fn empty() -> Self {
        HelperRegistry {
            helpers: HashMap::new(),
        }
    }

    /// Look up a helper by function name.
    pub fn get(&self, name: &str) -> Option<&HelperDef> {
        self.helpers.get(name)
    }
}

/// Substitute helper parameters with actual arguments in an expression.
/// Recurses into ALL `Expr` variants. No `_ =>` fallback.
pub fn substitute_expr(expr: &Expr, subs: &HashMap<String, Expr>) -> Expr {
    match expr {
        Expr::Var(name) => subs
            .get(name.as_str())
            .cloned()
            .unwrap_or_else(|| expr.clone()),
        Expr::Literal(_) | Expr::IntLiteral(_) | Expr::PointerDeref(_) => expr.clone(),
        Expr::BinOp(l, op, r) => Expr::BinOp(
            Box::new(substitute_expr(l, subs)),
            op.clone(),
            Box::new(substitute_expr(r, subs)),
        ),
        Expr::FuncCall(name, args) => Expr::FuncCall(
            name.clone(),
            args.iter().map(|a| substitute_expr(a, subs)).collect(),
        ),
        Expr::ArrayAccess(name, idx) => {
            Expr::ArrayAccess(name.clone(), Box::new(substitute_expr(idx, subs)))
        }
        Expr::Ternary(cond, then_e, else_e) => Expr::Ternary(
            Box::new(substitute_expr(cond, subs)),
            Box::new(substitute_expr(then_e, subs)),
            Box::new(substitute_expr(else_e, subs)),
        ),
        Expr::Cast(vt, inner) => Expr::Cast(vt.clone(), Box::new(substitute_expr(inner, subs))),
        Expr::Not(inner) => Expr::Not(Box::new(substitute_expr(inner, subs))),
        Expr::AddressOf(inner) => Expr::AddressOf(Box::new(substitute_expr(inner, subs))),
        Expr::PostIncrement(inner) => {
            Expr::PostIncrement(Box::new(substitute_expr(inner, subs)))
        }
        Expr::PostDecrement(inner) => {
            Expr::PostDecrement(Box::new(substitute_expr(inner, subs)))
        }
        Expr::PreIncrement(inner) => {
            Expr::PreIncrement(Box::new(substitute_expr(inner, subs)))
        }
        Expr::PreDecrement(inner) => {
            Expr::PreDecrement(Box::new(substitute_expr(inner, subs)))
        }
    }
}

/// Try to inline a helper call as a single expression.
/// Returns `Some(inlined_expr)` for single-expression helpers (body is one `Return`),
/// `None` for multi-statement helpers.
pub fn try_inline_expr(helper: &HelperDef, args: &[Expr]) -> Option<Expr> {
    if helper.body.len() == 1 {
        if let Statement::Return {
            value: Some(ret_expr),
        } = &helper.body[0]
        {
            let subs: HashMap<String, Expr> = helper
                .params
                .iter()
                .zip(args.iter())
                .map(|(p, a)| (p.name.clone(), a.clone()))
                .collect();
            return Some(substitute_expr(ret_expr, &subs));
        }
    }
    None
}

// ---------------------------------------------------------------------------
// Block inlining for multi-statement helpers
// ---------------------------------------------------------------------------

/// Substitute params in a statement, renaming local vars to avoid collisions.
/// Handles all `Statement` variants exhaustively.
#[allow(clippy::too_many_lines)]
pub fn substitute_statement(
    stmt: &Statement,
    subs: &HashMap<String, Expr>,
    suffix: usize,
) -> Statement {
    match stmt {
        Statement::VarDecl {
            var_type,
            name,
            init,
        } => Statement::VarDecl {
            var_type: var_type.clone(),
            name: format!("{name}_{suffix}"),
            init: init.as_ref().map(|e| substitute_expr(e, subs)),
        },
        Statement::Assign {
            target,
            value,
            compound,
        } => {
            let new_target = rename_local_var_in_expr(
                &substitute_expr(target, subs),
                subs,
                suffix,
            );
            Statement::Assign {
                target: new_target,
                value: rename_local_var_in_expr(
                    &substitute_expr(value, subs),
                    subs,
                    suffix,
                ),
                compound: *compound,
            }
        }
        Statement::While { condition, body } => Statement::While {
            condition: rename_local_var_in_expr(
                &substitute_expr(condition, subs),
                subs,
                suffix,
            ),
            body: body
                .iter()
                .map(|s| substitute_statement(s, subs, suffix))
                .collect(),
        },
        Statement::DoWhile { condition, body } => Statement::DoWhile {
            condition: rename_local_var_in_expr(
                &substitute_expr(condition, subs),
                subs,
                suffix,
            ),
            body: body
                .iter()
                .map(|s| substitute_statement(s, subs, suffix))
                .collect(),
        },
        Statement::For { var, count, body } => Statement::For {
            var: format!("{var}_{suffix}"),
            count: rename_local_var_in_expr(
                &substitute_expr(count, subs),
                subs,
                suffix,
            ),
            body: body
                .iter()
                .map(|s| substitute_statement(s, subs, suffix))
                .collect(),
        },
        Statement::ForC {
            init,
            condition,
            update,
            body,
        } => Statement::ForC {
            init: Box::new(substitute_statement(init, subs, suffix)),
            condition: rename_local_var_in_expr(
                &substitute_expr(condition, subs),
                subs,
                suffix,
            ),
            update: Box::new(substitute_statement(update, subs, suffix)),
            body: body
                .iter()
                .map(|s| substitute_statement(s, subs, suffix))
                .collect(),
        },
        Statement::If {
            condition,
            then_body,
            else_body,
        } => Statement::If {
            condition: rename_local_var_in_expr(
                &substitute_expr(condition, subs),
                subs,
                suffix,
            ),
            then_body: then_body
                .iter()
                .map(|s| substitute_statement(s, subs, suffix))
                .collect(),
            else_body: else_body
                .iter()
                .map(|s| substitute_statement(s, subs, suffix))
                .collect(),
        },
        Statement::Return { value } => Statement::Return {
            value: value.as_ref().map(|e| {
                rename_local_var_in_expr(&substitute_expr(e, subs), subs, suffix)
            }),
        },
        Statement::Switch {
            expr,
            cases,
            default,
        } => Statement::Switch {
            expr: rename_local_var_in_expr(
                &substitute_expr(expr, subs),
                subs,
                suffix,
            ),
            cases: cases
                .iter()
                .map(|(label, stmts)| {
                    (
                        label.clone(),
                        stmts
                            .iter()
                            .map(|s| substitute_statement(s, subs, suffix))
                            .collect(),
                    )
                })
                .collect(),
            default: default
                .iter()
                .map(|s| substitute_statement(s, subs, suffix))
                .collect(),
        },
        Statement::Block { body } => Statement::Block {
            body: body
                .iter()
                .map(|s| substitute_statement(s, subs, suffix))
                .collect(),
        },
        Statement::Break => Statement::Break,
        Statement::Continue => Statement::Continue,
    }
}

/// Collect local variable names declared in a helper body (VarDecl names).
fn collect_local_names(body: &[Statement]) -> Vec<String> {
    let mut names = Vec::new();
    for stmt in body {
        if let Statement::VarDecl { name, .. } = stmt {
            names.push(name.clone());
        }
    }
    names
}

/// After parameter substitution, rename any remaining references to local
/// variables (declared via `VarDecl` in the helper body) by appending `_suffix`.
///
/// This is needed because `substitute_expr` only replaces parameter names.
/// Local variables like `range`, `tmp`, `avg` also need unique names
/// to avoid collisions when the same helper is inlined multiple times.
fn rename_local_var_in_expr(
    expr: &Expr,
    _subs: &HashMap<String, Expr>,
    _suffix: usize,
) -> Expr {
    // The local-var renaming is already handled by substitute_statement:
    // VarDecl renames the declaration, and Assign targets that are Var(name)
    // get renamed. But we need to handle references to those locals in
    // arbitrary expression positions too. We do this in a second pass
    // (see inline_block) rather than here, to keep this function simple.
    // The actual renaming is done by building a second subs map for locals.
    expr.clone()
}

/// Inline a multi-statement helper. Returns (substituted body, temp var name).
///
/// The body has parameter names replaced with argument expressions, local
/// variable names suffixed with `_N` to avoid collisions, and `Return`
/// statements replaced with assignments to the temp var.
pub fn inline_block(
    helper: &HelperDef,
    args: &[Expr],
    counter: &mut usize,
) -> (Vec<Statement>, String) {
    let suffix = *counter;
    *counter += 1;

    // Build parameter substitution map
    let subs: HashMap<String, Expr> = helper
        .params
        .iter()
        .zip(args.iter())
        .map(|(p, a)| (p.name.clone(), a.clone()))
        .collect();

    // Collect local variable names that need renaming
    let locals = collect_local_names(&helper.body);

    // Build a second substitution map for local variable renaming
    let mut local_subs: HashMap<String, Expr> = subs.clone();
    for local in &locals {
        if !subs.contains_key(local) {
            local_subs.insert(
                local.clone(),
                Expr::Var(format!("{local}_{suffix}")),
            );
        }
    }

    let temp_name = format!(
        "_{}_{suffix}",
        helper.name.trim_start_matches("ta_")
    );

    let mut body: Vec<Statement> = helper
        .body
        .iter()
        .map(|s| substitute_statement(s, &local_subs, suffix))
        .collect();

    replace_returns_with_assign(&mut body, &temp_name);

    (body, temp_name)
}

/// Replace `Return { value: Some(expr) }` with
/// `Assign { target: Var(temp_name), value: expr }` throughout a statement list.
/// Recurses into nested `If`, `Switch`, `While`, `DoWhile`, `For`, `ForC`, `Block`.
#[allow(clippy::match_same_arms)]
fn replace_returns_with_assign(body: &mut [Statement], temp_name: &str) {
    for stmt in body.iter_mut() {
        match stmt {
            Statement::Return { value: Some(expr) } => {
                *stmt = Statement::Assign {
                    target: Expr::Var(temp_name.to_string()),
                    value: expr.clone(),
                    compound: false,
                };
            }
            Statement::If {
                then_body,
                else_body,
                ..
            } => {
                replace_returns_with_assign(then_body, temp_name);
                replace_returns_with_assign(else_body, temp_name);
            }
            Statement::Switch {
                cases, default, ..
            } => {
                for (_, stmts) in cases.iter_mut() {
                    replace_returns_with_assign(stmts, temp_name);
                }
                replace_returns_with_assign(default, temp_name);
            }
            Statement::While { body, .. } | Statement::DoWhile { body, .. } => {
                replace_returns_with_assign(body, temp_name);
            }
            Statement::For { body, .. } | Statement::ForC { body, .. } => {
                replace_returns_with_assign(body, temp_name);
            }
            Statement::Block { body } => {
                replace_returns_with_assign(body, temp_name);
            }
            Statement::Return { value: None }
            | Statement::VarDecl { .. }
            | Statement::Assign { .. }
            | Statement::Break
            | Statement::Continue => {}
        }
    }
}

/// Walk an expression tree, replacing multi-statement helper `FuncCall`s with
/// `Var(temp_name)`. The hoisted blocks (declaration + body) are collected in
/// `hoisted` and should be emitted before the containing statement.
///
/// Inner calls are hoisted first (depth-first), so nested helpers like
/// `ta_candleaverage` calling `ta_candlerange` work correctly.
pub fn hoist_block_helpers(
    expr: &Expr,
    helpers: &HelperRegistry,
    hoisted: &mut Vec<(String, VarType, Vec<Statement>)>,
    counter: &mut usize,
) -> Expr {
    match expr {
        Expr::FuncCall(name, args) => {
            // First recurse into args (inner calls get hoisted first)
            let new_args: Vec<Expr> = args
                .iter()
                .map(|a| hoist_block_helpers(a, helpers, hoisted, counter))
                .collect();
            // Check if this is a multi-statement helper
            if let Some(helper) = helpers.get(name) {
                if try_inline_expr(helper, &new_args).is_none() {
                    let (body, temp_name) =
                        inline_block(helper, &new_args, counter);
                    hoisted.push((
                        temp_name.clone(),
                        helper.return_type.clone(),
                        body,
                    ));
                    return Expr::Var(temp_name);
                }
            }
            Expr::FuncCall(name.clone(), new_args)
        }
        Expr::BinOp(l, op, r) => Expr::BinOp(
            Box::new(hoist_block_helpers(l, helpers, hoisted, counter)),
            op.clone(),
            Box::new(hoist_block_helpers(r, helpers, hoisted, counter)),
        ),
        Expr::Ternary(cond, then_e, else_e) => Expr::Ternary(
            Box::new(hoist_block_helpers(cond, helpers, hoisted, counter)),
            Box::new(hoist_block_helpers(then_e, helpers, hoisted, counter)),
            Box::new(hoist_block_helpers(else_e, helpers, hoisted, counter)),
        ),
        Expr::Cast(vt, inner) => Expr::Cast(
            vt.clone(),
            Box::new(hoist_block_helpers(inner, helpers, hoisted, counter)),
        ),
        Expr::Not(inner) => {
            Expr::Not(Box::new(hoist_block_helpers(inner, helpers, hoisted, counter)))
        }
        Expr::AddressOf(inner) => Expr::AddressOf(Box::new(hoist_block_helpers(
            inner, helpers, hoisted, counter,
        ))),
        Expr::PostIncrement(inner) => Expr::PostIncrement(Box::new(
            hoist_block_helpers(inner, helpers, hoisted, counter),
        )),
        Expr::PostDecrement(inner) => Expr::PostDecrement(Box::new(
            hoist_block_helpers(inner, helpers, hoisted, counter),
        )),
        Expr::PreIncrement(inner) => Expr::PreIncrement(Box::new(
            hoist_block_helpers(inner, helpers, hoisted, counter),
        )),
        Expr::PreDecrement(inner) => Expr::PreDecrement(Box::new(
            hoist_block_helpers(inner, helpers, hoisted, counter),
        )),
        Expr::ArrayAccess(name, idx) => Expr::ArrayAccess(
            name.clone(),
            Box::new(hoist_block_helpers(idx, helpers, hoisted, counter)),
        ),
        Expr::Var(name) => {
            // A bare Var cannot be a helper call; just clone.
            Expr::Var(name.clone())
        }
        Expr::Literal(_) | Expr::IntLiteral(_) | Expr::PointerDeref(_) => {
            expr.clone()
        }
    }
}
