//! Shared expression-tree walker for the language backends.
//!
//! The recursive descent over [`Expr`] — matching each variant and recursing into
//! its sub-expressions — has the same *shape* in the C, Rust and Java backends;
//! only the leaf formatting (operator tokens, cast syntax, variable-name mapping,
//! call dispatch) differs per language. [`ExprEmitter`] captures that split: the
//! trait owns the one exhaustive variant dispatch in [`ExprEmitter::walk`], and each
//! backend implements only the language-specific leaf hooks. Variants that render
//! identically in every backend (numeric/integer literals, logical `!`) have default
//! hook implementations here so no backend repeats them.
//!
//! A backend wires itself in by defining a small emitter struct that bundles its
//! render context (e.g. `CRenderCtx` plus the registry/helper services) and
//! implementing the leaf hooks; its free `render_expr` then becomes a thin
//! `emitter.walk(expr)`. Hooks recurse by calling [`ExprEmitter::walk`] on
//! sub-expressions, so the dispatch stays in one place.

use crate::ir::{BinOp, Expr, VarType};

/// Per-language leaf formatting for the shared [`walk`](ExprEmitter::walk) dispatch.
///
/// Implementors provide the language-specific hooks; the default `walk` owns the
/// exhaustive match over [`Expr`] variants and routes each to its hook. The three
/// universally-identical leaves ([`literal`](ExprEmitter::literal),
/// [`int_literal`](ExprEmitter::int_literal), [`not`](ExprEmitter::not)) have shared
/// defaults.
pub trait ExprEmitter {
    /// Render an `Expr::Var` reference (identifier or backend-specific constant mapping).
    fn var(&self, name: &str) -> String;

    /// Render an `Expr::ArrayAccess` (`name[idx]`); recurse into `idx` via [`walk`](Self::walk).
    fn array_access(&self, name: &str, idx: &Expr) -> String;

    /// Render an `Expr::BinOp`; recurse into `left`/`right` via [`walk`](Self::walk).
    fn binop(&self, left: &Expr, op: &BinOp, right: &Expr) -> String;

    /// Render an `Expr::Cast` to `ty`; recurse into `inner` via [`walk`](Self::walk).
    fn cast(&self, ty: &VarType, inner: &Expr) -> String;

    /// Render an `Expr::FuncCall` (builtin/helper/cross-indicator call dispatch).
    fn func_call(&self, name: &str, args: &[Expr]) -> String;

    /// Render an `Expr::PointerDeref` (`*name`).
    fn pointer_deref(&self, name: &str) -> String;

    /// Render an `Expr::AddressOf`; recurse into `inner` via [`walk`](Self::walk).
    fn address_of(&self, inner: &Expr) -> String;

    /// Render an `Expr::PostIncrement` (`inner++`).
    fn post_increment(&self, inner: &Expr) -> String;

    /// Render an `Expr::PostDecrement` (`inner--`).
    fn post_decrement(&self, inner: &Expr) -> String;

    /// Render an `Expr::PreIncrement` (`++inner`).
    fn pre_increment(&self, inner: &Expr) -> String;

    /// Render an `Expr::PreDecrement` (`--inner`).
    fn pre_decrement(&self, inner: &Expr) -> String;

    /// Render an `Expr::Ternary` (`cond ? then : else`).
    fn ternary(&self, cond: &Expr, then_expr: &Expr, else_expr: &Expr) -> String;

    /// Render an `Expr::Literal` (floating-point constant). Whole values gain a
    /// `.0` suffix (`3` → `3.0`); others use Rust's default `f64` formatting. This
    /// is byte-identical across the C, Rust and Java backends.
    fn literal(&self, f: f64) -> String {
        #[allow(clippy::float_cmp)]
        let is_whole = f == f.floor() && f.abs() < 1e15;
        if is_whole {
            #[allow(clippy::cast_possible_truncation)]
            let i = f as i64;
            format!("{i}.0")
        } else {
            format!("{f}")
        }
    }

    /// Render an `Expr::IntLiteral` (integer constant). Identical across backends.
    fn int_literal(&self, i: i64) -> String {
        format!("{i}")
    }

    /// Render an `Expr::Not` (`!(inner)`). Identical across backends.
    fn not(&self, inner: &Expr) -> String {
        format!("!({})", self.walk(inner))
    }

    /// The owned recursion: match `expr`'s variant and dispatch to the
    /// corresponding leaf hook. This is the single copy of the `Expr` tree-walk
    /// that every backend shares; the match is intentionally exhaustive (no
    /// wildcard arm) so a new IR variant forces every backend to handle it.
    fn walk(&self, expr: &Expr) -> String {
        match expr {
            Expr::Literal(f) => self.literal(*f),
            Expr::IntLiteral(i) => self.int_literal(*i),
            Expr::Var(name) => self.var(name),
            Expr::ArrayAccess(name, idx) => self.array_access(name, idx),
            Expr::BinOp(left, op, right) => self.binop(left, op, right),
            Expr::Cast(ty, inner) => self.cast(ty, inner),
            Expr::Not(inner) => self.not(inner),
            Expr::FuncCall(name, args) => self.func_call(name, args),
            Expr::PointerDeref(name) => self.pointer_deref(name),
            Expr::AddressOf(inner) => self.address_of(inner),
            Expr::PostIncrement(inner) => self.post_increment(inner),
            Expr::PostDecrement(inner) => self.post_decrement(inner),
            Expr::PreIncrement(inner) => self.pre_increment(inner),
            Expr::PreDecrement(inner) => self.pre_decrement(inner),
            Expr::Ternary(cond, then_expr, else_expr) => self.ternary(cond, then_expr, else_expr),
        }
    }
}
