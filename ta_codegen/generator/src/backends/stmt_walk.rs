//! Shared statement-tree walker for the language backends.
//!
//! The companion to [`ExprEmitter`](super::expr_walk::ExprEmitter): where that
//! owns the `Expr` dispatch, [`StatementEmitter`] owns the one exhaustive
//! `Statement`-variant dispatch in [`StatementEmitter::walk_stmt`] and threads the
//! current `indent` through it. Each backend implements the per-variant leaf hooks
//! (which are language-specific — brace style, indentation step, helper hoisting)
//! and recurses into child statements via [`walk_stmt`](StatementEmitter::walk_stmt).
//!
//! Three variants render identically across the C/Rust/Java backends — `break;`,
//! `continue;`, and a bare statement [`Block`](crate::ir::Statement::Block) (its
//! children rendered at the same indent) — so they have shared defaults here and no
//! backend repeats them. A backend wires itself in with a small emitter struct that
//! bundles its render context plus the enum/registry/helper services; its
//! `render_stmt` then becomes a thin `emitter.walk_stmt(stmt, indent)`.

use crate::ir::{CircBuf, Expr, Statement, VarType};

/// Per-language leaf formatting for the shared [`walk_stmt`](StatementEmitter::walk_stmt)
/// dispatch. Implementors provide the per-variant hooks; the default `walk_stmt` owns
/// the exhaustive match over [`Statement`] variants and routes each to its hook,
/// passing the current `indent`. The three universally-identical variants
/// (`Break`/`Continue`/`Block`) have shared defaults.
pub trait StatementEmitter {
    /// Render a `Statement::VarDecl` (`type name [= init];`).
    fn var_decl(&self, var_type: &VarType, name: &str, init: &Option<Expr>, indent: usize)
        -> String;

    /// Render a `Statement::Assign` (`target = value;`, possibly compound/folded).
    fn assign(&self, target: &Expr, value: &Expr, compound: bool, indent: usize) -> String;

    /// Render a `Statement::Expr` (an expression evaluated for its side effects).
    fn expr_stmt(&self, e: &Expr, indent: usize) -> String;

    /// Render a `Statement::While`; recurse into `body` via [`walk_stmt`](Self::walk_stmt).
    fn while_loop(&self, condition: &Expr, body: &[Statement], indent: usize) -> String;

    /// Render a `Statement::DoWhile`; recurse into `body` via [`walk_stmt`](Self::walk_stmt).
    fn do_while(&self, condition: &Expr, body: &[Statement], indent: usize) -> String;

    /// Render a `Statement::If`; recurse into the bodies via [`walk_stmt`](Self::walk_stmt).
    fn if_stmt(
        &self,
        condition: &Expr,
        then_body: &[Statement],
        else_body: &[Statement],
        indent: usize,
    ) -> String;

    /// Render a `Statement::Return` (`return [value];`).
    fn return_stmt(&self, value: &Option<Expr>, indent: usize) -> String;

    /// Render a `Statement::For` (TA-Lib's countdown loop); recurse via [`walk_stmt`](Self::walk_stmt).
    fn for_loop(&self, var: &str, count: &Expr, body: &[Statement], indent: usize) -> String;

    /// Render a `Statement::ForC` (C-style `for(init; cond; update)`); recurse via
    /// [`walk_stmt`](Self::walk_stmt).
    fn for_c(
        &self,
        init: &Statement,
        condition: &Expr,
        update: &Statement,
        body: &[Statement],
        indent: usize,
    ) -> String;

    /// Render a `Statement::Switch`; recurse into the case/default bodies via
    /// [`walk_stmt`](Self::walk_stmt).
    fn switch(
        &self,
        expr: &Expr,
        cases: &[(String, Vec<Statement>)],
        default: &[Statement],
        indent: usize,
    ) -> String;

    /// Render a `Statement::CircBuf` (a `CIRCBUF_*` op). Language-specific lowering.
    fn circ_buf(&self, op: &CircBuf, indent: usize) -> String;

    /// Render a `Statement::Break` (`break;`). Identical across backends.
    fn break_stmt(&self, indent: usize) -> String {
        format!("{}break;\n", " ".repeat(indent))
    }

    /// Render a `Statement::Continue` (`continue;`). Identical across backends.
    fn continue_stmt(&self, indent: usize) -> String {
        format!("{}continue;\n", " ".repeat(indent))
    }

    /// Render a `Statement::Block` — its child statements at the same indent.
    /// Identical across backends.
    fn block(&self, body: &[Statement], indent: usize) -> String {
        let mut out = String::new();
        for s in body {
            out.push_str(&self.walk_stmt(s, indent));
        }
        out
    }

    /// The owned recursion: match `stmt`'s variant and dispatch to the corresponding
    /// leaf hook, threading `indent`. This is the single copy of the `Statement`
    /// tree-walk that every backend shares; the match is intentionally exhaustive (no
    /// wildcard arm) so a new IR variant forces every backend to handle it.
    fn walk_stmt(&self, stmt: &Statement, indent: usize) -> String {
        match stmt {
            Statement::VarDecl { var_type, name, init } => {
                self.var_decl(var_type, name, init, indent)
            }
            Statement::Assign { target, value, compound } => {
                self.assign(target, value, *compound, indent)
            }
            Statement::Expr(e) => self.expr_stmt(e, indent),
            Statement::While { condition, body } => self.while_loop(condition, body, indent),
            Statement::DoWhile { condition, body } => self.do_while(condition, body, indent),
            Statement::If { condition, then_body, else_body } => {
                self.if_stmt(condition, then_body, else_body, indent)
            }
            Statement::Return { value } => self.return_stmt(value, indent),
            Statement::Break => self.break_stmt(indent),
            Statement::Continue => self.continue_stmt(indent),
            Statement::For { var, count, body } => self.for_loop(var, count, body, indent),
            Statement::ForC { init, condition, update, body } => {
                self.for_c(init, condition, update, body, indent)
            }
            Statement::Block { body } => self.block(body, indent),
            Statement::Switch { expr, cases, default } => self.switch(expr, cases, default, indent),
            Statement::CircBuf(op) => self.circ_buf(op, indent),
        }
    }
}
