use std::collections::HashMap;
use std::path::Path;

use crate::ir::{Expr, HelperDef, Statement};
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
