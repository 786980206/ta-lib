use std::cell::Cell;
use std::collections::HashMap;

use crate::candle_settings::{detect_candle_settings, emit_rust_unpacking};
use crate::helper_registry::{hoist_block_helpers, try_inline_expr, HelperRegistry};
use crate::ir::{
    BinOp, EnumDef, Expr, FuncDef, LookbackExpr, OptInput, ParamType, Statement, VarType,
};
use crate::parser::enums::lookup_variant;
use crate::registry::Registry;

/// Check if a statement list contains a return with ALLOC_ERR value.
fn contains_alloc_err_return(stmts: &[Statement]) -> bool {
    stmts.iter().any(|s| matches!(s, Statement::Return { value: Some(Expr::Var(name)) } if name == "ALLOC_ERR"))
}

/// Controls how the Rust renderer emits code.
pub struct RustRenderCtx {
    /// If true, emit `T` instead of `f64`/`f32` for Real types, wrap literals in `T::ta_from_f64()`, etc.
    pub generic: bool,
    /// If true, emit `get_unchecked()` / `get_unchecked_mut()` instead of `[]` for array access.
    pub unchecked: bool,
    /// Variable names declared as `VarType::Integer` or `VarType::Index` (usize in Rust).
    /// Used by type inference in expression rendering.
    pub index_vars: std::collections::HashSet<String>,
    /// Variable names declared as `VarType::Real` (T in Rust generic mode).
    pub real_vars: std::collections::HashSet<String>,
    /// Variable names declared as `VarType::RealPointer` or `VarType::IntPointer` (Vec<T> / Vec<i32>).
    /// These need `&name` / `&mut name[..]` conversion when passed to cross-indicator calls.
    pub vec_vars: std::collections::HashSet<String>,
    /// Variable names declared as `VarType::RealArray` (e.g., `[T; N]`).
    /// These need `&mut name` when passed in output position to cross-indicator calls.
    pub real_array_vars: std::collections::HashSet<String>,
    /// Output parameter names that are integer (i32) arrays (e.g., outInteger, outMaxIdx).
    /// Values assigned to these arrays need `as i32` cast when they are usize-typed.
    pub int_output_names: std::collections::HashSet<String>,
    /// Variable names declared as `VarType::IntPointer` (Vec<i32>).
    /// Array accesses on these produce i32 values. Assignments to these need i32 values.
    pub int_vec_vars: std::collections::HashSet<String>,
    /// If true, we're inside a lookback function (returns usize, not RetCode).
    /// Return values that are i32-typed will be cast to usize.
    pub is_lookback: bool,
}

impl RustRenderCtx {
    pub fn concrete() -> Self {
        RustRenderCtx {
            generic: false,
            unchecked: false,
            index_vars: std::collections::HashSet::new(),
            real_vars: std::collections::HashSet::new(),
            vec_vars: std::collections::HashSet::new(),
            real_array_vars: std::collections::HashSet::new(),
            int_output_names: std::collections::HashSet::new(),
            int_vec_vars: std::collections::HashSet::new(),
            is_lookback: false,
        }
    }
}

/// Check if an array variable is a Vec<i32> or [i32; N] (integer array).
/// Elements produce i32 values. Assignments need i32 cast.
fn is_int_array_or_vec(name: &str, ctx: &RustRenderCtx) -> bool {
    ctx.int_vec_vars.contains(name)
        || is_int_array_var(name)
        || ctx.int_output_names.contains(name)
}

#[allow(clippy::implicit_hasher)]
pub fn generate(
    func: &FuncDef,
    enums: &HashMap<String, EnumDef>,
    registry: &Registry,
    helpers: &HelperRegistry,
) -> String {
    let mut out = String::new();
    out.push_str(&gen_header());
    out.push_str(&gen_imports());
    out.push_str(&gen_impl_block(func, enums, registry, helpers));
    out.push_str(&gen_footer());
    out
}

fn gen_header() -> String {
    let mut out = String::new();
    out.push_str("/* TA-LIB Copyright (c) 1999-2025, Mario Fortier\n");
    out.push_str(" * All rights reserved.\n");
    out.push_str(" *\n");
    out.push_str(" * Redistribution and use in source and binary forms, with or\n");
    out.push_str(" * without modification, are permitted provided that the following\n");
    out.push_str(" * conditions are met:\n");
    out.push_str(" *\n");
    out.push_str(" * - Redistributions of source code must retain the above copyright\n");
    out.push_str(" *   notice, this list of conditions and the following disclaimer.\n");
    out.push_str(" *\n");
    out.push_str(" * - Redistributions in binary form must reproduce the above copyright\n");
    out.push_str(" *   notice, this list of conditions and the following disclaimer in\n");
    out.push_str(" *   the documentation and/or other materials provided with the\n");
    out.push_str(" *   distribution.\n");
    out.push_str(" *\n");
    out.push_str(" * - Neither name of author nor the names of its contributors\n");
    out.push_str(" *   may be used to endorse or promote products derived from this\n");
    out.push_str(" *   software without specific prior written permission.\n");
    out.push_str(" *\n");
    out.push_str(" * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS\n");
    out.push_str(" * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT\n");
    out.push_str(" * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS\n");
    out.push_str(" * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE\n");
    out.push_str(" * REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,\n");
    out.push_str(" * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES\n");
    out.push_str(" * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS\n");
    out.push_str(" * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS\n");
    out.push_str(" * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,\n");
    out.push_str(" * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE\n");
    out.push_str(" * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,\n");
    out.push_str(" * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.\n");
    out.push_str(" */\n\n");
    out.push_str("/* Important:\n");
    out.push_str(" *  This file is automatically generated by the utility gen_code.\n");
    out.push_str(" *  Any modifications will be lost on next execution of gen_code.\n");
    out.push_str(" *\n");
    out.push_str(" *  Modifications should instead be done with the \"C\" source file\n");
    out.push_str(" *  in ta-lib\\src\\ta_func\n");
    out.push_str(" */\n\n");
    out
}

fn gen_imports() -> String {
    "// Import types from parent module\n\
     use super::*;\n\n"
        .to_string()
}

fn gen_impl_block(func: &FuncDef, enums: &HashMap<String, EnumDef>, registry: &Registry, helpers: &HelperRegistry) -> String {
    let mut out = String::new();
    let snake = func.name.to_lowercase();

    out.push_str(
        "// Allow non-snake-case names to maintain TA-Lib API compatibility\n\
         #[allow(non_snake_case)]\n\
         #[allow(unused_variables)]\n\
         #[allow(dead_code)]\n\
         #[allow(unused_mut)]\n\
         #[allow(unused_assignments)]\n\
         impl Core {\n",
    );

    out.push_str(&gen_lookback(func, &snake, enums, registry, helpers));

    // Guarded: validates params, delegates to unguarded
    out.push_str(&gen_guarded_func(func, &snake, enums, registry, helpers));

    // Collect variable type info from function body for type inference
    let mut index_vars = std::collections::HashSet::new();
    let mut real_vars = std::collections::HashSet::new();
    let mut vec_vars = std::collections::HashSet::new();
    let mut real_array_vars = std::collections::HashSet::new();
    let mut int_vec_vars = std::collections::HashSet::new();
    collect_var_types(&func.body, &mut index_vars, &mut real_vars, &mut vec_vars, &mut real_array_vars, &mut int_vec_vars);
    // Also add parameter names
    index_vars.insert("startIdx".to_string());
    index_vars.insert("endIdx".to_string());
    index_vars.insert("outBegIdx".to_string());
    index_vars.insert("outNBElement".to_string());

    // Collect integer output names for i32 cast detection
    let int_output_set: std::collections::HashSet<String> = func.outputs.iter()
        .filter(|o| o.param_type == ParamType::Integer)
        .map(|o| o.name.clone())
        .collect();

    // Unguarded: real algorithm, bounds-checked array access
    let safe_ctx = RustRenderCtx {
        generic: true,
        unchecked: false,
        index_vars: index_vars.clone(),
        real_vars: real_vars.clone(),
        vec_vars: vec_vars.clone(),
        real_array_vars: real_array_vars.clone(),
        int_output_names: int_output_set.clone(),
        int_vec_vars: int_vec_vars.clone(),
        is_lookback: false,
    };
    out.push_str(&gen_unguarded_func(
        func, &snake, &safe_ctx, enums, registry, helpers,
    ));

    // Unchecked: validates params, delegates to unguarded_unchecked
    out.push_str(&gen_unchecked_func(func, &snake, enums, registry, helpers));

    // Unguarded unchecked: real algorithm, unchecked array access
    let unsafe_ctx = RustRenderCtx {
        generic: true,
        unchecked: true,
        index_vars,
        real_vars,
        vec_vars,
        real_array_vars,
        int_output_names: int_output_set,
        int_vec_vars,
        is_lookback: false,
    };
    out.push_str(&gen_unguarded_func(
        func,
        &snake,
        &unsafe_ctx,
        enums,
        registry,
        helpers,
    ));

    out.push_str("}\n");
    out
}

fn gen_lookback(
    func: &FuncDef,
    snake: &str,
    enums: &HashMap<String, EnumDef>,
    registry: &Registry,
    helpers: &HelperRegistry,
) -> String {
    let mut out = String::new();
    out.push_str(&format!("    /// Lookback period for [`Core::{snake}`].\n"));
    out.push_str("    ///\n");
    out.push_str("    /// # Arguments\n");
    out.push_str("    ///\n");

    let has_opt_inputs = !func.optional_inputs.is_empty();

    if has_opt_inputs {
        // Document optional params
        for opt in &func.optional_inputs {
            if let (Some(default), Some((lo, hi))) = (opt.default, opt.range) {
                #[allow(clippy::cast_possible_truncation)]
                let default_i64 = default as i64;
                out.push_str(&format!(
                    "    /// * `{}` - Number of period (default: {}, range: {}..={})\n",
                    opt.name, default_i64, lo, hi
                ));
            }
        }

        // Build parameter list
        let mut params = Vec::new();
        for opt in &func.optional_inputs {
            let rust_type = match opt.param_type {
                ParamType::Real => "f64",
                ParamType::Integer | ParamType::Enum(_) | ParamType::Price(_) => "i32",
            };
            params.push(format!("mut {}: {}", opt.name, rust_type));
        }

        out.push_str(&format!(
            "    pub fn {}_lookback(&self, {}) -> usize {{\n",
            snake,
            params.join(", ")
        ));

        // Param validation
        for opt in &func.optional_inputs {
            out.push_str(&gen_opt_param_validation(opt, "        ", true));
        }

        // Return lookback expression
        match &func.lookback {
            Some(LookbackExpr::Literal(n)) => {
                out.push_str(&format!("        return {n};\n"));
            }
            Some(LookbackExpr::ParamMinus(param, offset)) => {
                out.push_str(&format!("        return ({param} - {offset}) as usize;\n"));
            }
            Some(LookbackExpr::Code(stmts)) => {
                out.push_str(&render_lookback_code(stmts, enums, registry, helpers));
            }
            None => {
                out.push_str("        return 0;\n");
            }
        }
    } else {
        out.push_str(&format!("    pub fn {snake}_lookback(&self) -> usize {{\n"));
        match &func.lookback {
            Some(LookbackExpr::Literal(n)) => {
                out.push_str(&format!("        return {n};\n"));
            }
            Some(LookbackExpr::ParamMinus(param, offset)) => {
                out.push_str(&format!("        return ({param} - {offset}) as usize;\n"));
            }
            Some(LookbackExpr::Code(stmts)) => {
                out.push_str(&render_lookback_code(stmts, enums, registry, helpers));
            }
            None => {
                out.push_str("        return 0;\n");
            }
        }
    }

    out.push_str("    }\n");
    out
}

/// Generate the guarded public function.
/// Validates params, delegates to `{snake}_unguarded`.
fn gen_guarded_func(
    func: &FuncDef,
    snake: &str,
    _enums: &HashMap<String, EnumDef>,
    _registry: &Registry,
    _helpers: &HelperRegistry,
) -> String {
    let mut out = String::new();

    // Doc comments
    let title = func
        .description
        .as_deref()
        .or(func.hint.as_deref())
        .unwrap_or(&func.group);
    out.push_str(&format!("    /// {title}\n"));
    out.push_str("    ///\n");
    out.push_str("    /// # Arguments\n");
    out.push_str("    ///\n");
    out.push_str("    /// * `startIdx` - Start index for calculation range\n");
    out.push_str("    /// * `endIdx` - End index for calculation range (inclusive)\n");
    for input in &func.inputs {
        out.push_str(&format!(
            "    /// * `{}` - Input price series\n",
            input.name
        ));
    }
    for opt in &func.optional_inputs {
        if let (Some(default), Some((lo, hi))) = (opt.default, opt.range) {
            out.push_str(&format!(
                "    /// * `{}` - Number of period (default: {}, range: {}..={})\n",
                opt.name,
                {
                    #[allow(clippy::cast_possible_truncation)]
                    let d = default as i64;
                    d
                },
                lo,
                hi
            ));
        }
    }
    out.push_str("    /// * `outBegIdx` - First valid output index\n");
    out.push_str("    /// * `outNBElement` - Number of valid output elements\n");
    for output in &func.outputs {
        out.push_str(&format!("    /// * `{}` - Output values\n", output.name));
    }

    // Function signature
    out.push_str(&format!("    pub fn {snake}<T: TaFloat>(\n"));
    out.push_str("        &self,\n");
    out.push_str("        startIdx: usize,\n");
    out.push_str("        endIdx: usize,\n");
    out.push_str(&gen_generic_params(func));
    out.push_str("        outBegIdx: &mut usize,\n");
    out.push_str("        outNBElement: &mut usize,\n");
    out.push_str(&gen_generic_output_params(func));
    out.push_str("    ) -> RetCode {\n");

    // Range check
    out.push_str("        if endIdx < startIdx {\n");
    out.push_str("            return RetCode::OutOfRangeStartIndex;\n");
    out.push_str("        }\n");

    // Param validation
    for opt in &func.optional_inputs {
        out.push_str(&gen_opt_param_validation(opt, "        ", false));
    }

    // Delegate to unguarded function
    out.push_str(&format!("        return self.{snake}_unguarded(\n"));
    out.push_str("            startIdx,\n");
    out.push_str("            endIdx,\n");
    for input in &func.inputs {
        out.push_str(&format!("            {},\n", input.name));
    }
    for opt in &func.optional_inputs {
        out.push_str(&format!("            {},\n", opt.name));
    }
    out.push_str("            outBegIdx,\n");
    out.push_str("            outNBElement,\n");
    for output in &func.outputs {
        out.push_str(&format!("            {},\n", output.name));
    }
    out.push_str("        );\n");
    out.push_str("    }\n");

    out
}

/// Generate the unguarded function (real algorithm, bounds-checked or unchecked array access).
/// When `ctx.unchecked == false`: `pub fn {snake}_unguarded<T: TaFloat>(...)`
/// When `ctx.unchecked == true`: `pub unsafe fn {snake}_unguarded_unchecked<T: TaFloat>(...)`
#[allow(clippy::too_many_lines)]
fn gen_unguarded_func(
    func: &FuncDef,
    snake: &str,
    ctx: &RustRenderCtx,
    enums: &HashMap<String, EnumDef>,
    registry: &Registry,
    helpers: &HelperRegistry,
) -> String {
    let mut out = String::new();
    let func_name = if ctx.unchecked {
        format!("{snake}_unguarded_unchecked")
    } else {
        format!("{snake}_unguarded")
    };
    let visibility = if ctx.unchecked {
        "pub unsafe fn"
    } else {
        "pub fn"
    };

    // Function signature
    out.push_str(&format!("    {visibility} {func_name}<T: TaFloat>(\n"));
    out.push_str("        &self,\n");
    out.push_str("        mut startIdx: usize,\n");
    out.push_str("        endIdx: usize,\n");
    out.push_str(&gen_generic_params(func));
    out.push_str("        outBegIdx: &mut usize,\n");
    out.push_str("        outNBElement: &mut usize,\n");
    out.push_str(&gen_generic_output_params(func));
    out.push_str("    ) -> RetCode {\n");

    // Declare local variables (excluding loop iterators consumed by for-loops)
    let for_loop_vars = collect_for_loop_vars(&func.body);
    let var_inits: std::collections::HashMap<String, &Expr> = func
        .body
        .iter()
        .filter_map(|s| {
            if let Statement::VarDecl {
                name,
                init: Some(init),
                ..
            } = s
            {
                Some((name.clone(), init))
            } else {
                None
            }
        })
        .collect();

    // Collect names of OptInput Real params for generic wrapping
    let opt_real_params: Vec<String> = func
        .optional_inputs
        .iter()
        .filter(|o| o.param_type == ParamType::Real)
        .map(|o| o.name.clone())
        .collect();

    for stmt in &func.body {
        if let Statement::VarDecl { var_type, name, .. } = stmt {
            if for_loop_vars.contains(name) {
                continue;
            }
            let total_assigns = count_assignments(name, &func.body);
            // With default initialization, the let itself is an assignment,
            // so any body assignment means we need mut (threshold is > 0, not > 1)
            let needs_mut = total_assigns > 0;
            match var_type {
                VarType::RealArray(size) => {
                    let elem = if ctx.generic { "T::ta_zero()" } else { "0.0_f64" };
                    let ty = if ctx.generic { "T" } else { "f64" };
                    out.push_str(&format!(
                        "        let mut {name}: [{ty}; {size} as usize] = [{elem}; {size} as usize];\n"
                    ));
                }
                VarType::IntArray(size) => {
                    out.push_str(&format!(
                        "        let mut {name}: [i32; {size} as usize] = [0i32; {size} as usize];\n"
                    ));
                }
                _ => {
                    let rust_type = match var_type {
                        VarType::Real => {
                            if ctx.generic { "T" } else { "f64" }
                        }
                        VarType::Integer | VarType::Index => "usize",
                        VarType::RetCodeType => "RetCode",
                        VarType::RealPointer => {
                            if ctx.generic { "Vec<T>" } else { "Vec<f64>" }
                        }
                        VarType::IntPointer => "Vec<i32>",
                        VarType::RealArray(_) | VarType::IntArray(_) => unreachable!(),
                    };
                    // Always initialize to avoid "used binding isn't initialized" errors
                    let default_val = match var_type {
                        VarType::Real => {
                            if ctx.generic { "T::ta_zero()" } else { "0.0_f64" }
                        }
                        VarType::Integer | VarType::Index => "0_usize",
                        VarType::RetCodeType => "RetCode::Success",
                        VarType::RealPointer => "Vec::new()",
                        VarType::IntPointer => "Vec::new()",
                        VarType::RealArray(_) | VarType::IntArray(_) => unreachable!(),
                    };
                    if needs_mut {
                        out.push_str(&format!("        let mut {name}: {rust_type} = {default_val};\n"));
                    } else {
                        out.push_str(&format!("        let {name}: {rust_type} = {default_val};\n"));
                    }
                }
            }
        }
    }

    // Emit candle settings unpacking (only for referenced settings)
    let candle_used = detect_candle_settings(&func.body);
    if !candle_used.is_empty() {
        out.push_str(&emit_rust_unpacking(&candle_used, 8));
    }

    // Collect output array names for cast insertion
    let output_names: Vec<String> = func.outputs.iter().map(|o| o.name.clone()).collect();
    // (int_output_names tracked via ctx.int_output_names for i32 array cast detection)

    // Collect variables that have both VarDecl init AND a body assignment
    let body_assigned: std::collections::HashSet<String> = func
        .body
        .iter()
        .filter_map(|s| {
            if let Statement::Assign {
                target: Expr::Var(name),
                ..
            } = s
            {
                Some(name.clone())
            } else {
                None
            }
        })
        .collect();

    let inline_counter = Cell::new(0);

    // Emit VarDecl initializations only when there's no body assignment for the same var
    for stmt in &func.body {
        if let Statement::VarDecl {
            name,
            var_type: vt,
            init: Some(init),
        } = stmt
        {
            if for_loop_vars.contains(name) {
                continue;
            }
            if body_assigned.contains(name) {
                continue;
            }
            // Hoist multi-statement helpers from init expressions
            let mut hoisted = Vec::new();
            let mut cnt = inline_counter.get();
            let new_init = hoist_block_helpers(init, helpers, &mut hoisted, &mut cnt);
            inline_counter.set(cnt);
            out.push_str(&render_hoisted_blocks(
                &hoisted, 8, ctx, &for_loop_vars, &var_inits,
                &output_names, &opt_real_params, enums, registry,
                helpers, &inline_counter,
            ));
            let rendered_init = render_expr(&new_init, ctx, &opt_real_params, registry, helpers);
            // Wrap integer values assigned to T-typed variables
            let wrapped_init = if ctx.generic && (ctx.real_vars.contains(name) || *vt == VarType::Real) && expr_is_untyped_integer(&new_init) {
                format!("T::ta_from_i32({rendered_init} as i32)")
            } else {
                rendered_init
            };
            out.push_str(&format!("        {} = {};\n", name, wrapped_init));
        }
    }

    // Render body statements
    for stmt in &func.body {
        if matches!(stmt, Statement::VarDecl { .. }) {
            continue;
        }
        out.push_str(&render_statement(
            stmt,
            8,
            ctx,
            &for_loop_vars,
            &var_inits,
            &output_names,
            &opt_real_params,
            enums,
            registry,
            helpers,
            &inline_counter,
        ));
    }

    out.push_str("    }\n");

    out
}

/// Generate the unchecked function: validates params, delegates to `{snake}_unguarded_unchecked`.
fn gen_unchecked_func(
    func: &FuncDef,
    snake: &str,
    _enums: &HashMap<String, EnumDef>,
    _registry: &Registry,
    _helpers: &HelperRegistry,
) -> String {
    let mut out = String::new();

    out.push_str(&format!(
        "    pub unsafe fn {snake}_unchecked<T: TaFloat>(\n"
    ));
    out.push_str("        &self,\n");
    out.push_str("        startIdx: usize,\n");
    out.push_str("        endIdx: usize,\n");
    out.push_str(&gen_generic_params(func));
    out.push_str("        outBegIdx: &mut usize,\n");
    out.push_str("        outNBElement: &mut usize,\n");
    out.push_str(&gen_generic_output_params(func));
    out.push_str("    ) -> RetCode {\n");

    out.push_str("        if endIdx < startIdx {\n");
    out.push_str("            return RetCode::OutOfRangeStartIndex;\n");
    out.push_str("        }\n");

    for opt in &func.optional_inputs {
        out.push_str(&gen_opt_param_validation(opt, "        ", false));
    }

    out.push_str(&format!(
        "        return self.{snake}_unguarded_unchecked(\n"
    ));
    out.push_str("            startIdx,\n");
    out.push_str("            endIdx,\n");
    for input in &func.inputs {
        out.push_str(&format!("            {},\n", input.name));
    }
    for opt in &func.optional_inputs {
        out.push_str(&format!("            {},\n", opt.name));
    }
    out.push_str("            outBegIdx,\n");
    out.push_str("            outNBElement,\n");
    for output in &func.outputs {
        out.push_str(&format!("            {},\n", output.name));
    }
    out.push_str("        );\n");
    out.push_str("    }\n");

    out
}

/// Generate generic input parameter declarations for a function signature.
fn gen_generic_params(func: &FuncDef) -> String {
    let mut out = String::new();
    for input in &func.inputs {
        let param_type = match input.param_type {
            ParamType::Real => "&[T]",
            ParamType::Integer | ParamType::Enum(_) | ParamType::Price(_) => "&[i32]",
        };
        out.push_str(&format!("        {}: {},\n", input.name, param_type));
    }
    for opt in &func.optional_inputs {
        let rust_type = match opt.param_type {
            ParamType::Real => "f64",
            ParamType::Integer | ParamType::Enum(_) | ParamType::Price(_) => "i32",
        };
        out.push_str(&format!("        mut {}: {},\n", opt.name, rust_type));
    }
    out
}

/// Generate generic output parameter declarations for a function signature.
fn gen_generic_output_params(func: &FuncDef) -> String {
    let mut out = String::new();
    for output in &func.outputs {
        let param_type = match output.param_type {
            ParamType::Real => "&mut [T]",
            ParamType::Integer | ParamType::Enum(_) | ParamType::Price(_) => "&mut [i32]",
        };
        out.push_str(&format!("        {}: {},\n", output.name, param_type));
    }
    out
}

/// Generate optional parameter validation code.
fn gen_opt_param_validation(opt: &OptInput, pad: &str, is_lookback: bool) -> String {
    let mut out = String::new();
    let name = &opt.name;

    if opt.param_type == ParamType::Integer {
        if let Some(default) = opt.default {
            out.push_str(&format!("{pad}if (({name}) as i32) == (i32::MIN) {{\n"));
            #[allow(clippy::cast_possible_truncation)]
            let default_i64 = default as i64;
            out.push_str(&format!("{pad}    {name} = {default_i64};\n"));

            if let Some((lo, hi)) = opt.range {
                let err_return = if is_lookback {
                    "return usize::MAX;"
                } else {
                    "return RetCode::BadParam;"
                };
                out.push_str(&format!(
                    "{pad}}} else if ((({name}) as i32) < {lo}) || ((({name}) as i32) > {hi}) {{\n"
                ));
                out.push_str(&format!("{pad}    {err_return}\n"));
            }

            out.push_str(&format!("{pad}}}\n"));
        }
    }

    out
}

/// Collect variable type information from VarDecl statements (recursively).
fn collect_var_types(
    body: &[Statement],
    index_vars: &mut std::collections::HashSet<String>,
    real_vars: &mut std::collections::HashSet<String>,
    vec_vars: &mut std::collections::HashSet<String>,
    real_array_vars: &mut std::collections::HashSet<String>,
    int_vec_vars: &mut std::collections::HashSet<String>,
) {
    for stmt in body {
        match stmt {
            Statement::VarDecl { var_type, name, .. } => {
                match var_type {
                    VarType::Integer | VarType::Index => { index_vars.insert(name.clone()); }
                    VarType::Real => { real_vars.insert(name.clone()); }
                    VarType::RealPointer => { vec_vars.insert(name.clone()); }
                    VarType::IntPointer => { vec_vars.insert(name.clone()); int_vec_vars.insert(name.clone()); }
                    VarType::IntArray(_) => { index_vars.insert(name.clone()); int_vec_vars.insert(name.clone()); }
                    VarType::RealArray(_) => { real_array_vars.insert(name.clone()); }
                    _ => {}
                }
            }
            Statement::If { then_body, else_body, .. } => {
                collect_var_types(then_body, index_vars, real_vars, vec_vars, real_array_vars, int_vec_vars);
                collect_var_types(else_body, index_vars, real_vars, vec_vars, real_array_vars, int_vec_vars);
            }
            Statement::While { body: while_body, .. }
            | Statement::DoWhile { body: while_body, .. } => {
                collect_var_types(while_body, index_vars, real_vars, vec_vars, real_array_vars, int_vec_vars);
            }
            Statement::For { body: for_body, .. } => {
                collect_var_types(for_body, index_vars, real_vars, vec_vars, real_array_vars, int_vec_vars);
            }
            Statement::ForC { body: for_body, .. } => {
                collect_var_types(for_body, index_vars, real_vars, vec_vars, real_array_vars, int_vec_vars);
            }
            Statement::Block { body: block_body } => {
                collect_var_types(block_body, index_vars, real_vars, vec_vars, real_array_vars, int_vec_vars);
            }
            Statement::Switch { cases, default, .. } => {
                for (_, case_body) in cases {
                    collect_var_types(case_body, index_vars, real_vars, vec_vars, real_array_vars, int_vec_vars);
                }
                collect_var_types(default, index_vars, real_vars, vec_vars, real_array_vars, int_vec_vars);
            }
            _ => {}
        }
    }
}

/// Count how many times a variable is assigned in the body (including `VarDecl` inits).
fn count_assignments(name: &str, body: &[Statement]) -> usize {
    count_assignments_inner(name, body, false)
}

/// Count increment/decrement operations on a variable embedded in expressions.
fn count_increments_in_expr(name: &str, expr: &Expr) -> usize {
    match expr {
        Expr::PostIncrement(inner) | Expr::PostDecrement(inner)
        | Expr::PreIncrement(inner) | Expr::PreDecrement(inner) => {
            if let Expr::Var(vname) = inner.as_ref() {
                if vname == name { return 1; }
            }
            count_increments_in_expr(name, inner)
        }
        // &var in a function call means the variable will be mutably borrowed
        Expr::AddressOf(inner) => {
            if let Expr::Var(vname) = inner.as_ref() {
                if vname == name { return 1; }
            }
            count_increments_in_expr(name, inner)
        }
        Expr::BinOp(left, _, right) => {
            count_increments_in_expr(name, left) + count_increments_in_expr(name, right)
        }
        Expr::ArrayAccess(_, idx) => count_increments_in_expr(name, idx),
        Expr::FuncCall(_, args) => args.iter().map(|a| count_increments_in_expr(name, a)).sum(),
        Expr::Not(inner) | Expr::Cast(_, inner) => {
            count_increments_in_expr(name, inner)
        }
        Expr::Ternary(cond, then_expr, else_expr) => {
            count_increments_in_expr(name, cond)
                + count_increments_in_expr(name, then_expr)
                + count_increments_in_expr(name, else_expr)
        }
        _ => 0,
    }
}

fn count_assignments_inner(name: &str, body: &[Statement], in_loop: bool) -> usize {
    let mut count = 0;
    for stmt in body {
        match stmt {
            Statement::VarDecl {
                name: vname, init, ..
            } => {
                if vname == name && init.is_some() {
                    count += 1;
                }
            }
            Statement::Assign { target, value, .. } => {
                if let Expr::Var(tname) = target {
                    if tname == name {
                        count += if in_loop { 2 } else { 1 };
                    }
                }
                // Also count increment/decrement embedded in expressions
                count += count_increments_in_expr(name, target);
                count += count_increments_in_expr(name, value);
            }
            Statement::While {
                body: while_body, ..
            }
            | Statement::DoWhile {
                body: while_body, ..
            } => {
                count += count_assignments_inner(name, while_body, true);
            }
            Statement::For { body: for_body, .. } => {
                count += count_assignments_inner(name, for_body, true);
            }
            Statement::ForC { init, update, body: for_body, .. } => {
                count += count_assignments_inner(name, &[init.as_ref().clone()], in_loop);
                count += count_assignments_inner(name, &[update.as_ref().clone()], true);
                count += count_assignments_inner(name, for_body, true);
            }
            Statement::Block { body: block_body } => {
                count += count_assignments_inner(name, block_body, in_loop);
            }
            Statement::If {
                then_body,
                else_body,
                ..
            } => {
                count += count_assignments_inner(name, then_body, in_loop);
                count += count_assignments_inner(name, else_body, in_loop);
            }
            Statement::Return { .. } | Statement::Break | Statement::Continue => {}
            Statement::Switch { cases, default, .. } => {
                for (_, case_body) in cases {
                    count += count_assignments_inner(name, case_body, in_loop);
                }
                count += count_assignments_inner(name, default, in_loop);
            }
        }
    }
    count
}

fn collect_for_loop_vars(body: &[Statement]) -> Vec<String> {
    let mut vars = Vec::new();
    let decls: std::collections::HashMap<String, &Expr> = body
        .iter()
        .filter_map(|s| {
            if let Statement::VarDecl {
                name,
                init: Some(init),
                var_type,
            } = s
            {
                if *var_type == VarType::Index {
                    return Some((name.clone(), init));
                }
            }
            None
        })
        .collect();

    for stmt in body {
        match stmt {
            Statement::While {
                condition,
                body: while_body,
            } => {
                if let Some(iter_var) = detect_for_pattern(condition, while_body, &decls) {
                    vars.push(iter_var);
                }
            }
            Statement::For { .. }
            | Statement::ForC { .. }
            | Statement::Block { .. }
            | Statement::VarDecl { .. }
            | Statement::Assign { .. }
            | Statement::If { .. }
            | Statement::Return { .. }
            | Statement::Break
            | Statement::Continue
            | Statement::Switch { .. }
            | Statement::DoWhile { .. } => {}
        }
    }
    vars
}

fn detect_for_pattern(
    condition: &Expr,
    while_body: &[Statement],
    decls: &std::collections::HashMap<String, &Expr>,
) -> Option<String> {
    if let Expr::BinOp(left, BinOp::LessEq, _right) = condition {
        if let Expr::Var(iter_name) = left.as_ref() {
            if decls.contains_key(iter_name) {
                if let Some(Statement::Assign {
                    target: Expr::Var(tname),
                    value,
                    ..
                }) = while_body.last()
                {
                    if tname == iter_name {
                        if let Expr::BinOp(l, BinOp::Add, r) = value {
                            if let (Expr::Var(ln), Expr::IntLiteral(1)) = (l.as_ref(), r.as_ref()) {
                                if ln == iter_name {
                                    return Some(iter_name.clone());
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    None
}

/// Extracts the init value if `stmt` is a single `Assign { target: Var(var_name), value, .. }`.
/// Returns `None` for multi-assignment blocks or mismatched targets.
fn extract_init_value<'a>(stmt: &'a Statement, var_name: &str) -> Option<&'a Expr> {
    if let Statement::Assign {
        target: Expr::Var(tname),
        value,
        ..
    } = stmt
    {
        if tname == var_name {
            return Some(value);
        }
    }
    None
}

/// Returns `true` if `stmt` is `var_name = var_name + 1` (simple increment by 1).
fn is_simple_increment(stmt: &Statement, var_name: &str) -> bool {
    if let Statement::Assign {
        target: Expr::Var(tname),
        value: Expr::BinOp(left, BinOp::Add, right),
        ..
    } = stmt
    {
        if tname != var_name {
            return false;
        }
        if let Expr::Var(lname) = left.as_ref() {
            if lname == var_name {
                return matches!(right.as_ref(), Expr::IntLiteral(1));
            }
        }
    }
    false
}

/// Render hoisted block-inline helpers as Rust code (temp var decl + body).
#[allow(clippy::too_many_arguments)]
fn render_hoisted_blocks(
    hoisted: &[(String, VarType, Vec<Statement>)],
    indent: usize,
    ctx: &RustRenderCtx,
    for_loop_vars: &[String],
    var_inits: &std::collections::HashMap<String, &Expr>,
    output_names: &[String],
    opt_real_params: &[String],
    enums: &HashMap<String, EnumDef>,
    registry: &Registry,
    helpers: &HelperRegistry,
    inline_counter: &Cell<usize>,
) -> String {
    let pad = " ".repeat(indent);
    let mut out = String::new();
    for (temp_name, var_type, body) in hoisted {
        let decl_line = match var_type {
            VarType::RealArray(size) => {
                let elem = if ctx.generic { "T::ta_zero()" } else { "0.0_f64" };
                let ty = if ctx.generic { "T" } else { "f64" };
                format!("{pad}let mut {temp_name}: [{ty}; {size} as usize] = [{elem}; {size} as usize];\n")
            }
            VarType::IntArray(size) => {
                format!("{pad}let mut {temp_name}: [i32; {size} as usize] = [0i32; {size} as usize];\n")
            }
            _ => {
                let rust_type = match var_type {
                    VarType::Real => {
                        if ctx.generic { "T" } else { "f64" }
                    }
                    VarType::Integer | VarType::Index => "usize",
                    VarType::RetCodeType => "RetCode",
                    VarType::RealPointer => {
                        if ctx.generic { "Vec<T>" } else { "Vec<f64>" }
                    }
                    VarType::IntPointer => "Vec<i32>",
                    VarType::RealArray(_) | VarType::IntArray(_) => unreachable!(),
                };
                format!("{pad}let mut {temp_name}: {rust_type};\n")
            }
        };
        out.push_str(&decl_line);
        // Emit VarDecl statements from the hoisted body (these are local vars
        // of the helper function that need inline declaration)
        for stmt in body {
            if let Statement::VarDecl { var_type: vt, name, .. } = stmt {
                let local_type = match vt {
                    VarType::Real => {
                        if ctx.generic { "T" } else { "f64" }
                    }
                    VarType::Integer | VarType::Index => "usize",
                    VarType::RetCodeType => "RetCode",
                    VarType::RealPointer => {
                        if ctx.generic { "Vec<T>" } else { "Vec<f64>" }
                    }
                    VarType::IntPointer => "Vec<i32>",
                    VarType::RealArray(size) => {
                        out.push_str(&format!(
                            "{pad}let mut {name}: [{ty}; {size} as usize] = [{elem}; {size} as usize];\n",
                            ty = if ctx.generic { "T" } else { "f64" },
                            elem = if ctx.generic { "T::ta_zero()" } else { "0.0_f64" },
                        ));
                        continue;
                    }
                    VarType::IntArray(size) => {
                        out.push_str(&format!(
                            "{pad}let mut {name}: [i32; {size} as usize] = [0i32; {size} as usize];\n"
                        ));
                        continue;
                    }
                };
                let default_val = match vt {
                    VarType::Real => {
                        if ctx.generic { "T::ta_zero()" } else { "0.0_f64" }
                    }
                    VarType::Integer | VarType::Index => "0_usize",
                    VarType::RetCodeType => "RetCode::Success",
                    VarType::RealPointer => "Vec::new()",
                    VarType::IntPointer => "Vec::new()",
                    VarType::RealArray(_) | VarType::IntArray(_) => unreachable!(),
                };
                out.push_str(&format!("{pad}let mut {name}: {local_type} = {default_val};\n"));
            }
        }
        for stmt in body {
            out.push_str(&render_statement(
                stmt,
                indent,
                ctx,
                for_loop_vars,
                var_inits,
                output_names,
                opt_real_params,
                enums,
                registry,
                helpers,
                inline_counter,
            ));
        }
    }
    out
}

#[allow(clippy::too_many_lines, clippy::cognitive_complexity, clippy::too_many_arguments)]
pub fn render_statement(
    stmt: &Statement,
    indent: usize,
    ctx: &RustRenderCtx,
    for_loop_vars: &[String],
    var_inits: &std::collections::HashMap<String, &Expr>,
    output_names: &[String],
    opt_real_params: &[String],
    enums: &HashMap<String, EnumDef>,
    registry: &Registry,
    helpers: &HelperRegistry,
    inline_counter: &Cell<usize>,
) -> String {
    let pad = " ".repeat(indent);
    match stmt {
        Statement::VarDecl { var_type, name, .. } => {
            // VarDecl at function top-level is handled by the separate declaration pass.
            // VarDecl inside blocks/loops/ifs needs inline declaration.
            // We always emit here; the top-level pass skips VarDecls to avoid duplicates.
            // The top-level code pre-emits declarations for all body-level VarDecls,
            // so if this VarDecl is at top level, this is a no-op duplicate that will
            // be filtered by the caller. For nested VarDecls (inside blocks), this is needed.
            if indent <= 8 {
                // Top-level VarDecl already handled
                return String::new();
            }
            let rust_type = match var_type {
                VarType::Real => {
                    if ctx.generic { "T" } else { "f64" }
                }
                VarType::Integer | VarType::Index => "usize",
                VarType::RetCodeType => "RetCode",
                VarType::RealPointer => {
                    if ctx.generic { "Vec<T>" } else { "Vec<f64>" }
                }
                VarType::IntPointer => "Vec<i32>",
                VarType::RealArray(size) => {
                    let elem = if ctx.generic { "T::ta_zero()" } else { "0.0_f64" };
                    let ty = if ctx.generic { "T" } else { "f64" };
                    return format!("{pad}let mut {name}: [{ty}; {size} as usize] = [{elem}; {size} as usize];\n");
                }
                VarType::IntArray(size) => {
                    return format!("{pad}let mut {name}: [i32; {size} as usize] = [0i32; {size} as usize];\n");
                }
            };
            let default_val = match var_type {
                VarType::Real => {
                    if ctx.generic { "T::ta_zero()" } else { "0.0_f64" }
                }
                VarType::Integer | VarType::Index => "0_usize",
                VarType::RetCodeType => "RetCode::Success",
                VarType::RealPointer => "Vec::new()",
                VarType::IntPointer => "Vec::new()",
                VarType::RealArray(_) | VarType::IntArray(_) => unreachable!(),
            };
            format!("{pad}let mut {name}: {rust_type} = {default_val};\n")
        }
        Statement::Block { body: block_body } => {
            let mut out = String::new();
            for s in block_body {
                out.push_str(&render_statement(
                    s,
                    indent,
                    ctx,
                    for_loop_vars,
                    var_inits,
                    output_names,
                    opt_real_params,
                    enums,
                    registry,
                    helpers,
                inline_counter,
                ));
            }
            out
        }
        Statement::For {
            var,
            count,
            body: for_body,
        } => {
            let mut out = format!(
                "{}for {} in (1..={}).rev() {{\n",
                pad,
                var,
                render_expr(count, ctx, opt_real_params, registry, helpers)
            );
            for s in for_body {
                out.push_str(&render_statement(
                    s,
                    indent + 4,
                    ctx,
                    for_loop_vars,
                    var_inits,
                    output_names,
                    opt_real_params,
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
            body: for_body,
        } => {
            // Range-iteration fast path: for(i=start; i<=end; i++) → for i in (start as usize)..=(end as usize)
            if let Expr::BinOp(cond_left, BinOp::LessEq, cond_right) = condition {
                if let Expr::Var(iter_name) = cond_left.as_ref() {
                    if let Some(start_expr) = extract_init_value(init, iter_name) {
                        if is_simple_increment(update, iter_name) {
                            let start_str = render_expr(start_expr, ctx, opt_real_params, registry, helpers);
                            let end_str = render_expr(cond_right, ctx, opt_real_params, registry, helpers);
                            let mut out = format!(
                                "{pad}for {iter_name} in ({start_str} as usize)..=({end_str} as usize) {{\n"
                            );
                            for s in for_body {
                                out.push_str(&render_statement(
                                    s,
                                    indent + 4,
                                    ctx,
                                    for_loop_vars,
                                    var_inits,
                                    output_names,
                                    opt_real_params,
                                    enums,
                                    registry,
                                    helpers,
                                inline_counter,
                                ));
                            }
                            out.push_str(&format!("{pad}}}\n"));
                            return out;
                        }
                    }
                }
            }
            // Generic fallback: init; while cond { body; update; }
            // Collect init statements (may be a Block with multiple assigns)
            let init_stmts = match init.as_ref() {
                Statement::Block { body: block_body } => block_body.clone(),
                other => vec![other.clone()],
            };
            // Collect update statements (may be a Block with multiple assigns)
            let update_stmts = match update.as_ref() {
                Statement::Block { body: block_body } => block_body.clone(),
                other => vec![other.clone()],
            };
            let cond_str =
                render_expr(condition, ctx, opt_real_params, registry, helpers);
            // Build single-line comment summarizing the original C for loop
            let init_parts: Vec<String> = init_stmts
                .iter()
                .map(|s| {
                    render_statement(
                        s, 0, ctx, for_loop_vars, var_inits, output_names,
                        opt_real_params, enums, registry, helpers, inline_counter,
                    )
                    .trim()
                    .trim_end_matches(';')
                    .to_string()
                })
                .collect();
            let update_parts: Vec<String> = update_stmts
                .iter()
                .map(|s| {
                    render_statement(
                        s, 0, ctx, for_loop_vars, var_inits, output_names,
                        opt_real_params, enums, registry, helpers, inline_counter,
                    )
                    .trim()
                    .trim_end_matches(';')
                    .to_string()
                })
                .collect();
            let mut out = format!(
                "{pad}// for( {}; {cond_str}; {} )\n",
                init_parts.join(", "),
                update_parts.join(", "),
            );
            // Emit init statements
            for s in &init_stmts {
                out.push_str(&render_statement(
                    s, indent, ctx, for_loop_vars, var_inits, output_names,
                    opt_real_params, enums, registry, helpers, inline_counter,
                ));
            }
            out.push_str(&format!(
                "{pad}while {cond_str} {{\n"
            ));
            for s in for_body {
                out.push_str(&render_statement(
                    s,
                    indent + 4,
                    ctx,
                    for_loop_vars,
                    var_inits,
                    output_names,
                    opt_real_params,
                    enums,
                    registry,
                    helpers,
                inline_counter,
                ));
            }
            // Emit update statements inside the while body
            for s in &update_stmts {
                out.push_str(&render_statement(
                    s, indent + 4, ctx, for_loop_vars, var_inits, output_names,
                    opt_real_params, enums, registry, helpers, inline_counter,
                ));
            }
            out.push_str(&format!("{pad}}}\n"));
            out
        }
        Statement::Assign {
            target,
            value,
            compound,
        } => {
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
                            fname, args, ctx, opt_real_params, registry, helpers,
                        );
                        // Skip empty renders (e.g. free() returns "")
                        if rendered.is_empty() {
                            return String::new();
                        }
                        return format!("{pad}{rendered};\n");
                    }
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
                &hoisted, indent, ctx, for_loop_vars, var_inits,
                output_names, opt_real_params, enums, registry,
                helpers, inline_counter,
            );

            // Emit dummy variable declaration for duplicate &mut borrows in cross-indicator calls
            if has_duplicate_address_of(&new_value) {
                out.push_str(&format!("{pad}let mut _dup_out: usize = 0_usize;\n"));
            }

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
                                    render_assign_target(target, ctx, opt_real_params, registry, helpers);
                                let rhs_str = render_expr(right, ctx, opt_real_params, registry, helpers);
                                // Check if the target is T-typed (Real variable)
                                let target_is_real = ctx.real_vars.contains(tname)
                                    || (!ctx.index_vars.contains(tname)
                                        && !is_likely_index_var(tname)
                                        && !is_i32_opt_in_param(tname)
                                        && !tname.ends_with("_avgPeriod")
                                        && !tname.ends_with("_rangeType"));
                                // Wrap integer RHS in compound assignments to T-typed variables
                                let rhs_wrapped = if ctx.generic && target_is_real {
                                    if expr_is_untyped_integer(right) {
                                        format!("T::ta_from_i32({rhs_str} as i32)")
                                    } else if expr_is_i32_typed(right) {
                                        format!("T::ta_from_i32({rhs_str})")
                                    } else if expr_is_known_usize_ctx(right, ctx) && !expr_is_float_typed_ctx(right, Some(ctx)) {
                                        format!("T::ta_from_i32(({rhs_str}) as i32)")
                                    } else {
                                        rhs_str
                                    }
                                } else if ctx.generic && !target_is_real
                                    && is_likely_index_var(tname)
                                    && expr_is_i32_typed(right)
                                {
                                    // usize target, i32 RHS: cast to usize
                                    format!("({rhs_str}) as usize")
                                } else {
                                    rhs_str
                                };
                                out.push_str(&format!(
                                    "{}{} {} {};\n",
                                    pad,
                                    target_str,
                                    op_str,
                                    rhs_wrapped
                                ));
                                return out;
                            }
                        }
                    }
                }
            }
            let target_str = render_assign_target(target, ctx, opt_real_params, registry, helpers);
            // When target is an optIn Real param (f64 in sig), render value WITHOUT
            // optIn Real wrapping to avoid T::ta_from_f64() on the value side
            let target_is_opt_real_param = if let Expr::Var(tname) = target {
                ctx.generic && opt_real_params.contains(tname)
            } else {
                false
            };
            let value_str = if target_is_opt_real_param {
                // Render without opt_real_params wrapping so optIn Real values stay f64
                let empty_opt: Vec<String> = Vec::new();
                render_expr(&new_value, ctx, &empty_opt, registry, helpers)
            } else {
                render_expr(&new_value, ctx, opt_real_params, registry, helpers)
            };
            let needs_f64_cast = if ctx.generic {
                false
            } else if let Expr::ArrayAccess(name, _) = target {
                output_names.contains(name) && expr_has_uncast_array_access(&new_value)
            } else {
                false
            };
            // Check if we're assigning an i32-typed expression to a non-i32 target variable
            // (e.g., usize var = optInTimePeriod which is i32,
            //  or curPeriod = localPeriodArray[i] where array is Vec<i32>)
            let value_is_i32 = expr_is_i32_typed(&new_value)
                || matches!(new_value, Expr::Var(ref v) if is_i32_opt_in_param(v) || v.ends_with("_avgPeriod") || v.ends_with("_rangeType"))
                || matches!(&new_value, Expr::ArrayAccess(ref name, _) if is_int_array_or_vec(name, ctx));
            let needs_usize_cast = if let Expr::Var(tname) = target {
                !output_names.iter().any(|n| n == tname)
                    && !is_i32_opt_in_param(tname)
                    && !tname.ends_with("_avgPeriod")
                    && !tname.ends_with("_rangeType")
                    && !ctx.real_vars.contains(tname)
                    && value_is_i32
            } else {
                false
            };
            // Check if target is an i32 optIn param and value is usize
            // (e.g., optInFastPeriod = tempInteger where tempInteger is usize)
            let needs_i32_cast = if let Expr::Var(tname) = target {
                is_i32_opt_in_param(tname)
                    && !expr_is_i32_typed(&new_value)
                    && !matches!(new_value, Expr::IntLiteral(_))
                    && (expr_is_known_usize_ctx(&new_value, ctx)
                        || matches!(new_value, Expr::Var(ref v) if ctx.index_vars.contains(v) || is_likely_index_var(v)))
            } else {
                false
            };
            // Check if target is an integer output/local array (e.g., outInteger[idx] = usize_val,
            // sortedPeriods[i] = longestPeriod, localPeriodArray[i] = tempInt)
            // Values assigned to i32 arrays need `as i32` cast when usize-typed
            let needs_int_output_cast = if let Expr::ArrayAccess(name, _) = target {
                (ctx.int_output_names.contains(name) || is_int_array_or_vec(name, ctx))
                    && !expr_is_i32_typed(&new_value)
                    && !matches!(new_value, Expr::IntLiteral(_))
                    && (expr_is_known_usize_ctx(&new_value, ctx)
                        || matches!(&new_value, Expr::Var(v) if ctx.index_vars.contains(v) || is_likely_index_var(v))
                        || matches!(&new_value, Expr::BinOp(_, _, _)))
            } else {
                false
            };
            // Wrap integer values assigned to T-typed variables in generic context
            let needs_t_wrap = if ctx.generic {
                if let Expr::Var(tname) = target {
                    // Target is T-typed if it's in the real_vars set (from VarDecl)
                    // or matches naming heuristics for Real variables
                    (ctx.real_vars.contains(tname)
                        || (!ctx.index_vars.contains(tname)
                            && !is_likely_index_var(tname)
                            && !is_i32_opt_in_param(tname)
                            && !tname.ends_with("_avgPeriod")
                            && !tname.ends_with("_rangeType")
                            && !output_names.iter().any(|n| n == tname)))
                        && (expr_is_untyped_integer(&new_value) || expr_is_i32_typed(&new_value)
                            || expr_is_known_usize_ctx(&new_value, ctx))
                } else if let Expr::ArrayAccess(name, _) = target {
                    // Array target: Real arrays (output, temp, local) need T values
                    // But NOT IntArray/IntPointer targets (periods, usedFlag, localPeriodArray, etc.)
                    // and NOT integer output arrays (outInteger, outMaxIdx, etc.)
                    !name.contains("Int") && !name.contains("integer")
                        && !ctx.index_vars.contains(name)
                        && !is_int_array_var(name)
                        && !ctx.int_output_names.contains(name)
                        && !ctx.int_vec_vars.contains(name)
                        && (expr_is_untyped_integer(&new_value) || expr_is_i32_typed(&new_value)
                            || expr_is_known_usize_ctx(&new_value, ctx))
                } else {
                    false
                }
            } else {
                false
            };
            // Check if target is a Vec<T> variable and value is a slice/output param
            // (buffer aliasing pattern in BBANDS, STOCH, etc.)
            let needs_to_vec = if let Expr::Var(tname) = target {
                if ctx.vec_vars.contains(tname) || is_vec_local_var(tname) {
                    if let Expr::Var(vname) = &new_value {
                        output_names.contains(vname) || vname.starts_with("in")
                    } else {
                        false
                    }
                } else {
                    false
                }
            } else {
                false
            };
            if needs_to_vec {
                out.push_str(&format!("{pad}{target_str} = {value_str}.to_vec();\n"));
            } else if needs_int_output_cast {
                out.push_str(&format!("{pad}{target_str} = ({value_str}) as i32;\n"));
            } else if needs_f64_cast {
                out.push_str(&format!("{pad}{target_str} = ({value_str}) as f64;\n"));
            } else if needs_t_wrap {
                if expr_is_i32_typed(&new_value) {
                    out.push_str(&format!("{pad}{target_str} = T::ta_from_i32({value_str});\n"));
                } else if expr_is_known_usize_ctx(&new_value, ctx) {
                    out.push_str(&format!("{pad}{target_str} = T::ta_from_i32(({value_str}) as i32);\n"));
                } else {
                    out.push_str(&format!("{pad}{target_str} = T::ta_from_i32({value_str} as i32);\n"));
                }
            } else if needs_i32_cast {
                out.push_str(&format!("{pad}{target_str} = ({value_str}) as i32;\n"));
            } else if needs_usize_cast {
                out.push_str(&format!("{pad}{target_str} = ({value_str}) as usize;\n"));
            } else {
                out.push_str(&format!("{pad}{target_str} = {value_str};\n"));
            }
            out
        }
        Statement::While {
            condition,
            body: while_body,
        } => {
            if let Expr::BinOp(left, BinOp::LessEq, right) = condition {
                if let Expr::Var(iter_name) = left.as_ref() {
                    if for_loop_vars.contains(iter_name) {
                        let start_expr = if let Some(init) = var_inits.get(iter_name) {
                            render_expr(init, ctx, opt_real_params, registry, helpers)
                        } else {
                            iter_name.clone()
                        };
                        let end_expr = render_expr(right, ctx, opt_real_params, registry, helpers);
                        let mut out = format!(
                            "{pad}for {iter_name} in ({start_expr} as usize)..=({end_expr} as usize) {{\n"
                        );
                        for s in &while_body[..while_body.len() - 1] {
                            out.push_str(&render_statement(
                                s,
                                indent + 4,
                                ctx,
                                for_loop_vars,
                                var_inits,
                                output_names,
                                opt_real_params,
                                enums,
                                registry,
                                helpers,
                            inline_counter,
                            ));
                        }
                        out.push_str(&format!("{pad}}}\n"));
                        return out;
                    }
                }
            }
            let mut out = format!(
                "{}while {} {{\n",
                pad,
                render_expr(condition, ctx, opt_real_params, registry, helpers)
            );
            for s in while_body {
                out.push_str(&render_statement(
                    s,
                    indent + 4,
                    ctx,
                    for_loop_vars,
                    var_inits,
                    output_names,
                    opt_real_params,
                    enums,
                    registry,
                    helpers,
                inline_counter,
                ));
            }
            out.push_str(&format!("{pad}}}\n"));
            out
        }
        Statement::DoWhile {
            condition,
            body: while_body,
        } => {
            let mut out = format!("{pad}loop {{\n");
            for s in while_body {
                out.push_str(&render_statement(
                    s,
                    indent + 4,
                    ctx,
                    for_loop_vars,
                    var_inits,
                    output_names,
                    opt_real_params,
                    enums,
                    registry,
                    helpers,
                inline_counter,
                ));
            }
            out.push_str(&format!(
                "{}    if !({}) {{ break; }}\n",
                pad,
                render_expr(condition, ctx, opt_real_params, registry, helpers)
            ));
            out.push_str(&format!("{pad}}}\n"));
            out
        }
        Statement::If {
            condition,
            then_body,
            else_body,
        } => {
            // Skip post-allocation null-check blocks (dead code in Rust — Vec::new() never fails)
            if contains_alloc_err_return(then_body) {
                return String::new();
            }
            let mut out = format!(
                "{}if {} {{\n",
                pad,
                render_condition(condition, ctx, opt_real_params, registry, helpers)
            );
            for s in then_body {
                out.push_str(&render_statement(
                    s,
                    indent + 4,
                    ctx,
                    for_loop_vars,
                    var_inits,
                    output_names,
                    opt_real_params,
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
                            ctx,
                            for_loop_vars,
                            var_inits,
                            output_names,
                            opt_real_params,
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
                        indent + 4,
                        ctx,
                        for_loop_vars,
                        var_inits,
                        output_names,
                        opt_real_params,
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
                let rendered = render_return_expr(expr, ctx, opt_real_params, registry, helpers);
                // In lookback functions, return value must be usize. Cast any i32/mixed expression.
                let is_already_usize = matches!(expr, Expr::Var(ref n) if n == "retValue" || n == "lookbackTotal" || n == "emaLookback")
                    || expr_is_known_usize_ctx(expr, ctx)
                    || expr_returns_usize(expr);
                if ctx.is_lookback && !is_already_usize
                    && !matches!(expr, Expr::Var(ref n) if n == "SUCCESS" || n == "BadParam" || n.starts_with("RetCode"))
                {
                    format!("{pad}return ({rendered}) as usize;\n")
                } else {
                    format!("{pad}return {rendered};\n")
                }
            }
            None => format!("{pad}return;\n"),
        },
        Statement::Break => format!("{pad}break;\n"),
        Statement::Continue => format!("{pad}continue;\n"),
        Statement::Switch {
            expr,
            cases,
            default,
        } => {
            let mut out = format!(
                "{}match {} {{\n",
                pad,
                render_expr(expr, ctx, opt_real_params, registry, helpers)
            );
            for (label, case_body) in cases {
                let rust_label = render_switch_label(label, enums);
                out.push_str(&format!("{pad}    {rust_label} => {{\n"));
                for s in case_body {
                    out.push_str(&render_statement(
                        s,
                        indent + 8,
                        ctx,
                        for_loop_vars,
                        var_inits,
                        output_names,
                        opt_real_params,
                        enums,
                        registry,
                        helpers,
                    inline_counter,
                    ));
                }
                out.push_str(&format!("{pad}    }}\n"));
            }
            if !default.is_empty() {
                out.push_str(&format!("{pad}    _ => {{\n"));
                for s in default {
                    out.push_str(&render_statement(
                        s,
                        indent + 8,
                        ctx,
                        for_loop_vars,
                        var_inits,
                        output_names,
                        opt_real_params,
                        enums,
                        registry,
                        helpers,
                    inline_counter,
                    ));
                }
                out.push_str(&format!("{pad}    }}\n"));
            }
            out.push_str(&format!("{pad}}}\n"));
            out
        }
    }
}

fn render_switch_label(label: &str, enums: &HashMap<String, EnumDef>) -> String {
    if let Some((_enum_name, variant)) = lookup_variant(label, enums) {
        format!("{}", variant.value)
    } else {
        label.to_string()
    }
}

fn expr_has_uncast_array_access(expr: &Expr) -> bool {
    match expr {
        Expr::ArrayAccess(_, _) => true,
        Expr::Cast(_, _)
        | Expr::Literal(_)
        | Expr::IntLiteral(_)
        | Expr::Var(_)
        | Expr::PointerDeref(_)
        | Expr::AddressOf(_)
        | Expr::PostIncrement(_)
        | Expr::PostDecrement(_)
        | Expr::PreIncrement(_)
        | Expr::PreDecrement(_) => false,
        Expr::BinOp(left, _, right) => {
            expr_has_uncast_array_access(left) || expr_has_uncast_array_access(right)
        }
        Expr::Not(inner) => expr_has_uncast_array_access(inner),
        Expr::FuncCall(_, args) => args.iter().any(expr_has_uncast_array_access),
        Expr::Ternary(cond, then_expr, else_expr) => {
            expr_has_uncast_array_access(cond)
                || expr_has_uncast_array_access(then_expr)
                || expr_has_uncast_array_access(else_expr)
        }
    }
}

fn render_assign_target(
    expr: &Expr,
    ctx: &RustRenderCtx,
    opt_real_params: &[String],
    registry: &Registry,
    helpers: &HelperRegistry,
) -> String {
    match expr {
        Expr::Var(name) if name == "outBegIdx" || name == "outNBElement" => {
            format!("(*{name})")
        }
        Expr::Var(name) => name.clone(),
        Expr::ArrayAccess(name, idx) => {
            let idx_rendered = render_index_expr(idx, ctx, opt_real_params, registry, helpers);
            if ctx.unchecked {
                format!("(*{name}.get_unchecked_mut({idx_rendered}))")
            } else {
                format!("{name}[{idx_rendered}]")
            }
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
        | Expr::Ternary(_, _, _) => render_expr(expr, ctx, opt_real_params, registry, helpers),
    }
}

fn op_precedence(op: &BinOp) -> u8 {
    match op {
        BinOp::Or => 1,
        BinOp::And => 2,
        BinOp::Eq | BinOp::NotEq => 3,
        BinOp::Less | BinOp::LessEq | BinOp::Greater | BinOp::GreaterEq => 4,
        BinOp::Add | BinOp::Sub | BinOp::Shr | BinOp::Shl => 5,
        BinOp::Mul | BinOp::Div | BinOp::Mod => 6,
    }
}

fn render_binop_operand(
    expr: &Expr,
    parent_op: &BinOp,
    is_left: bool,
    ctx: &RustRenderCtx,
    opt_real_params: &[String],
    registry: &Registry,
    helpers: &HelperRegistry,
) -> String {
    match expr {
        Expr::Cast(_, _) => format!("({})", render_expr(expr, ctx, opt_real_params, registry, helpers)),
        Expr::BinOp(_, child_op, _) => {
            let parent_prec = op_precedence(parent_op);
            let child_prec = op_precedence(child_op);
            if child_prec < parent_prec || (!is_left && child_prec == parent_prec) {
                format!("({})", render_expr(expr, ctx, opt_real_params, registry, helpers))
            } else {
                render_expr(expr, ctx, opt_real_params, registry, helpers)
            }
        }
        Expr::Ternary(_, _, _) if matches!(parent_op, BinOp::And | BinOp::Or) => {
            // Ternary producing integer 1/0 used in boolean context needs != 0
            let rendered = render_expr(expr, ctx, opt_real_params, registry, helpers);
            format!("({rendered} != 0)")
        }
        Expr::FuncCall(fname, args) if matches!(parent_op, BinOp::And | BinOp::Or) => {
            // Check if this is a helper function that inlines to a ternary returning 1/0
            if let Some(helper) = helpers.get(fname) {
                if let Some(inlined) = try_inline_expr(helper, args) {
                    if matches!(inlined, Expr::Ternary(_, _, _)) {
                        let rendered = render_expr(expr, ctx, opt_real_params, registry, helpers);
                        return format!("({rendered} != 0)");
                    }
                }
            }
            render_expr(expr, ctx, opt_real_params, registry, helpers)
        }
        Expr::Literal(_)
        | Expr::IntLiteral(_)
        | Expr::Var(_)
        | Expr::ArrayAccess(_, _)
        | Expr::Not(_)
        | Expr::FuncCall(_, _)
        | Expr::PointerDeref(_)
        | Expr::AddressOf(_)
        | Expr::PostIncrement(_)
        | Expr::PostDecrement(_)
        | Expr::PreIncrement(_)
        | Expr::PreDecrement(_)
        | Expr::Ternary(_, _, _) => render_expr(expr, ctx, opt_real_params, registry, helpers),
    }
}

fn render_return_expr(
    expr: &Expr,
    ctx: &RustRenderCtx,
    opt_real_params: &[String],
    registry: &Registry,
    helpers: &HelperRegistry,
) -> String {
    if let Expr::Var(name) = expr {
        return match name.as_str() {
            "SUCCESS" => "RetCode::Success".to_string(),
            "BadParam" => "RetCode::BadParam".to_string(),
            "OutOfRangeEndIndex" => "RetCode::OutOfRangeEndIndex".to_string(),
            "OutOfRangeStartIndex" => "RetCode::OutOfRangeStartIndex".to_string(),
            "ALLOC_ERR" => "RetCode::AllocErr".to_string(),
            "INTERNAL_ERROR" => "RetCode::InternalError".to_string(),
            _ => render_expr(expr, ctx, opt_real_params, registry, helpers),
        };
    }
    render_expr(expr, ctx, opt_real_params, registry, helpers)
}

/// Render a condition expression, ensuring it's boolean-typed.
/// Bare integer/usize variables get `!= 0` wrapping.
fn render_condition(
    expr: &Expr,
    ctx: &RustRenderCtx,
    opt_real_params: &[String],
    registry: &Registry,
    helpers: &HelperRegistry,
) -> String {
    // Bare Var used as condition: needs != 0 if it's an integer/usize
    if let Expr::Var(name) = expr {
        if ctx.index_vars.contains(name) || is_likely_index_var(name)
            || is_i32_opt_in_param(name)
        {
            let rendered = render_expr(expr, ctx, opt_real_params, registry, helpers);
            return format!("{rendered} != 0");
        }
    }
    // Not(Var) → Var == 0 for integer vars
    if let Expr::Not(inner) = expr {
        if let Expr::Var(name) = inner.as_ref() {
            if ctx.index_vars.contains(name) || is_likely_index_var(name)
                || is_i32_opt_in_param(name)
            {
                let rendered = render_expr(inner, ctx, opt_real_params, registry, helpers);
                return format!("{rendered} == 0");
            }
        }
    }
    // Ternary producing integer used as condition: needs != 0
    if let Expr::Ternary(_, then_expr, _) = expr {
        if expr_is_untyped_integer(then_expr) || matches!(then_expr.as_ref(), Expr::IntLiteral(_)) {
            let rendered = render_expr(expr, ctx, opt_real_params, registry, helpers);
            return format!("({rendered} != 0)");
        }
    }
    // FuncCall that inlines to ternary producing integer: needs != 0
    if let Expr::FuncCall(fname, args) = expr {
        if let Some(helper) = helpers.get(fname) {
            if let Some(inlined) = try_inline_expr(helper, args) {
                if let Expr::Ternary(_, ref then_expr, _) = inlined {
                    if expr_is_untyped_integer(then_expr) || matches!(then_expr.as_ref(), Expr::IntLiteral(_)) {
                        let rendered = render_expr(expr, ctx, opt_real_params, registry, helpers);
                        return format!("({rendered} != 0)");
                    }
                }
            }
        }
    }
    render_expr(expr, ctx, opt_real_params, registry, helpers)
}

#[allow(clippy::too_many_lines)]
fn render_expr(
    expr: &Expr,
    ctx: &RustRenderCtx,
    opt_real_params: &[String],
    registry: &Registry,
    helpers: &HelperRegistry,
) -> String {
    match expr {
        Expr::Literal(f) => {
            #[allow(clippy::float_cmp)]
            let is_whole = *f == f.floor() && f.abs() < 1e15;
            let lit_str = if is_whole {
                #[allow(clippy::cast_possible_truncation)]
                let i = *f as i64;
                format!("{i}.0")
            } else {
                format!("{f}")
            };
            if ctx.generic {
                format!("T::ta_from_f64({lit_str})")
            } else {
                lit_str
            }
        }
        Expr::IntLiteral(i) => format!("{i}"),
        Expr::Var(name) => match name.as_str() {
            "COMPATIBILITY" => "(self.compatibility)".to_string(),
            "METASTOCK" => "Compatibility::Metastock".to_string(),
            "DEFAULT" => "Compatibility::Default".to_string(),
            "BAD_PARAM" => "RetCode::BadParam".to_string(),
            "SUCCESS" => "RetCode::Success".to_string(),
            "ALLOC_ERR" => "RetCode::AllocErr".to_string(),
            "INTERNAL_ERROR" => "RetCode::InternalError".to_string(),
            "TA_MAType_SMA" => "0".to_string(),
            "TA_MAType_EMA" => "1".to_string(),
            "TA_MAType_WMA" => "2".to_string(),
            "TA_MAType_DEMA" => "3".to_string(),
            "TA_MAType_TEMA" => "4".to_string(),
            "TA_MAType_TRIMA" => "5".to_string(),
            "TA_MAType_KAMA" => "6".to_string(),
            "TA_MAType_MAMA" => "7".to_string(),
            "TA_MAType_T3" => "8".to_string(),
            _ => {
                if ctx.generic && opt_real_params.contains(name) {
                    format!("T::ta_from_f64({name})")
                } else {
                    name.clone()
                }
            }
        },
        Expr::ArrayAccess(name, idx) => {
            let idx_rendered = render_index_expr(idx, ctx, opt_real_params, registry, helpers);
            if ctx.unchecked {
                format!("(*{name}.get_unchecked({idx_rendered}))")
            } else {
                format!("{name}[{idx_rendered}]")
            }
        }
        Expr::FuncCall(fname, args) => {
            render_func_call(fname, args, ctx, opt_real_params, registry, helpers)
        }
        Expr::BinOp(left, op, right) => {
            let op_str = match op {
                BinOp::Add => " + ",
                BinOp::Sub => " - ",
                BinOp::Mul => " * ",
                BinOp::Div => " / ",
                BinOp::Mod => " % ",
                BinOp::LessEq => " <= ",
                BinOp::Less => " < ",
                BinOp::Greater => " > ",
                BinOp::GreaterEq => " >= ",
                BinOp::Eq => " == ",
                BinOp::NotEq => " != ",
                BinOp::And => " && ",
                BinOp::Or => " || ",
                BinOp::Shr => " >> ",
                BinOp::Shl => " << ",
            };
            let is_arithmetic = matches!(op, BinOp::Add | BinOp::Sub | BinOp::Mul | BinOp::Div | BinOp::Mod | BinOp::Shr | BinOp::Shl);
            let mut left_str = render_binop_operand(left, op, true, ctx, opt_real_params, registry, helpers);
            let mut right_str = render_binop_operand(right, op, false, ctx, opt_real_params, registry, helpers);
            if is_arithmetic {
                // When in generic context, opt_real_params are wrapped to T by render_expr,
                // so they should be treated as float-typed, not i32-typed
                let left_is_opt_real = ctx.generic && matches!(left.as_ref(), Expr::Var(n) if opt_real_params.contains(n));
                let right_is_opt_real = ctx.generic && matches!(right.as_ref(), Expr::Var(n) if opt_real_params.contains(n));
                let left_is_float = expr_is_float_typed_ctx(left, Some(ctx)) || left_is_opt_real;
                let right_is_float = expr_is_float_typed_ctx(right, Some(ctx)) || right_is_opt_real;
                let left_is_i32 = expr_is_i32_typed(left) && !left_is_opt_real;
                let right_is_i32 = expr_is_i32_typed(right) && !right_is_opt_real;
                let left_is_int_lit = matches!(left.as_ref(), Expr::IntLiteral(_));
                let right_is_int_lit = matches!(right.as_ref(), Expr::IntLiteral(_));

                if ctx.generic {
                    let left_is_untyped_int = expr_is_untyped_integer(left);
                    let right_is_untyped_int = expr_is_untyped_integer(right);
                    // Wrap IntLiterals with T::ta_from_i32() when doing arithmetic with T-typed expressions
                    if left_is_int_lit && right_is_float {
                        if let Expr::IntLiteral(v) = left.as_ref() {
                            left_str = format!("T::ta_from_i32({v})");
                        }
                    }
                    if right_is_int_lit && left_is_float {
                        if let Expr::IntLiteral(v) = right.as_ref() {
                            right_str = format!("T::ta_from_i32({v})");
                        }
                    }
                    // Wrap i32 variables with T::ta_from_i32() when doing arithmetic with T-typed expressions
                    // But NOT if the variable is also float-typed (e.g., optInK_1 is Real despite optIn prefix)
                    if left_is_i32 && right_is_float && !left_is_int_lit && !left_is_float {
                        left_str = format!("T::ta_from_i32({left_str})");
                    }
                    if right_is_i32 && left_is_float && !right_is_int_lit && !right_is_float {
                        right_str = format!("T::ta_from_i32({right_str})");
                    }
                    // Wrap untyped-integer expressions (ternaries, int arithmetic) when
                    // doing arithmetic with T-typed expressions
                    if left_is_untyped_int && !left_is_int_lit && right_is_float {
                        left_str = format!("T::ta_from_i32({left_str} as i32)");
                    }
                    if right_is_untyped_int && !right_is_int_lit && left_is_float {
                        right_str = format!("T::ta_from_i32({right_str} as i32)");
                    }
                    // Wrap usize-typed expressions when doing arithmetic with T-typed expressions
                    // Only wrap if the expression is provably usize AND wasn't already handled by i32 wrapping
                    let left_is_known_usize = expr_is_known_usize_ctx(left, ctx);
                    let right_is_known_usize = expr_is_known_usize_ctx(right, ctx);
                    // Also detect BinOps that render as usize due to inner i32-to-usize coercion
                    let left_eff_usize = left_is_known_usize
                        || expr_binop_renders_as_usize(left, ctx);
                    let right_eff_usize = right_is_known_usize
                        || expr_binop_renders_as_usize(right, ctx);
                    if left_eff_usize && right_is_float && !left_is_i32 {
                        left_str = format!("T::ta_from_i32(({left_str}) as i32)");
                    }
                    if right_eff_usize && left_is_float && !right_is_i32 {
                        right_str = format!("T::ta_from_i32(({right_str}) as i32)");
                    }
                }
                // Cast i32 operands to usize when mixed with usize-typed operands (not float)
                // Also detect i32 array accesses (IntArray/IntPointer)
                let arith_left_is_i32_arr = matches!(left.as_ref(), Expr::ArrayAccess(ref name, _) if is_int_array_or_vec(name, ctx));
                let arith_right_is_i32_arr = matches!(right.as_ref(), Expr::ArrayAccess(ref name, _) if is_int_array_or_vec(name, ctx));
                let left_is_i32_eff = left_is_i32 || arith_left_is_i32_arr;
                let right_is_i32_eff = right_is_i32 || arith_right_is_i32_arr;
                let left_is_usize = !left_is_i32_eff && !left_is_float && !left_is_int_lit;
                let right_is_usize = !right_is_i32_eff && !right_is_float && !right_is_int_lit;
                if left_is_i32_eff && right_is_usize {
                    left_str = format!("({left_str}) as usize");
                }
                if right_is_i32_eff && left_is_usize {
                    right_str = format!("({right_str}) as usize");
                }
                // When both sides appear i32-typed but one actually renders as usize
                // (e.g., Cast(Integer, usize_expr) drops the cast), fix the mismatch.
                if left_is_i32_eff && right_is_i32_eff && !left_is_int_lit && !right_is_int_lit {
                    let left_renders_usize = expr_renders_as_usize_despite_i32(left, ctx);
                    let right_renders_usize = expr_renders_as_usize_despite_i32(right, ctx);
                    if left_renders_usize && !right_renders_usize {
                        right_str = format!("({right_str}) as usize");
                    }
                    if right_renders_usize && !left_renders_usize {
                        left_str = format!("({left_str}) as usize");
                    }
                }
            }
            // For comparison operators, cast i32 to usize when mixed (not float)
            // and wrap IntLiterals with T::ta_zero() / T::ta_from_i32() when comparing with T-typed exprs
            if matches!(op, BinOp::Less | BinOp::LessEq | BinOp::Greater | BinOp::GreaterEq | BinOp::Eq | BinOp::NotEq) {
                let cmp_left_is_opt_real = ctx.generic && matches!(left.as_ref(), Expr::Var(n) if opt_real_params.contains(n));
                let cmp_right_is_opt_real = ctx.generic && matches!(right.as_ref(), Expr::Var(n) if opt_real_params.contains(n));
                let left_is_i32 = expr_is_i32_typed(left) && !cmp_left_is_opt_real;
                let right_is_i32 = expr_is_i32_typed(right) && !cmp_right_is_opt_real;
                let left_is_float = expr_is_float_typed_ctx(left, Some(ctx)) || cmp_left_is_opt_real;
                let right_is_float = expr_is_float_typed_ctx(right, Some(ctx)) || cmp_right_is_opt_real;
                let left_is_int_lit = matches!(left.as_ref(), Expr::IntLiteral(_));
                let right_is_int_lit = matches!(right.as_ref(), Expr::IntLiteral(_));
                if ctx.generic {
                    let left_is_untyped_int = expr_is_untyped_integer(left);
                    let right_is_untyped_int = expr_is_untyped_integer(right);
                    // Wrap IntLiteral when compared against T-typed expression
                    if right_is_int_lit && left_is_float {
                        if let Expr::IntLiteral(v) = right.as_ref() {
                            right_str = format!("T::ta_from_i32({v})");
                        }
                    }
                    if left_is_int_lit && right_is_float {
                        if let Expr::IntLiteral(v) = left.as_ref() {
                            left_str = format!("T::ta_from_i32({v})");
                        }
                    }
                    // Wrap i32 variables with T::ta_from_i32() when comparing with T-typed expressions
                    // But NOT if the variable is also float-typed (e.g., optInK_1 is Real despite optIn prefix)
                    if left_is_i32 && right_is_float && !left_is_int_lit && !left_is_float {
                        left_str = format!("T::ta_from_i32({left_str})");
                    }
                    if right_is_i32 && left_is_float && !right_is_int_lit && !right_is_float {
                        right_str = format!("T::ta_from_i32({right_str})");
                    }
                    // Wrap untyped-integer expressions (ternaries, int arithmetic)
                    // when compared with T-typed expressions
                    if left_is_untyped_int && !left_is_int_lit && right_is_float {
                        left_str = format!("T::ta_from_i32({left_str} as i32)");
                    }
                    if right_is_untyped_int && !right_is_int_lit && left_is_float {
                        right_str = format!("T::ta_from_i32({right_str} as i32)");
                    }
                    // Wrap usize-typed expressions when compared with T-typed expressions
                    // (e.g., daysInTrend < 0.5 * smoothPeriod in ht_trendmode)
                    // Only apply when the other side is GENUINELY float (not just matching
                    // a naming heuristic while being usize in the context)
                    let cmp_left_is_known_usize = expr_is_known_usize_ctx(left, ctx);
                    let cmp_right_is_known_usize = expr_is_known_usize_ctx(right, ctx);
                    if cmp_left_is_known_usize && right_is_float && !cmp_right_is_known_usize && !left_is_i32 && !left_is_int_lit {
                        left_str = format!("T::ta_from_i32(({left_str}) as i32)");
                    }
                    if cmp_right_is_known_usize && left_is_float && !cmp_left_is_known_usize && !right_is_i32 && !right_is_int_lit {
                        right_str = format!("T::ta_from_i32(({right_str}) as i32)");
                    }
                }
                // Also detect i32 array accesses (IntArray/IntPointer) using context
                let left_is_i32_arr = matches!(left.as_ref(), Expr::ArrayAccess(ref name, _) if is_int_array_or_vec(name, ctx));
                let right_is_i32_arr = matches!(right.as_ref(), Expr::ArrayAccess(ref name, _) if is_int_array_or_vec(name, ctx));
                let left_is_i32_eff = left_is_i32 || left_is_i32_arr;
                let right_is_i32_eff = right_is_i32 || right_is_i32_arr;
                if left_is_i32_eff && !right_is_i32_eff && !right_is_float && !right_is_int_lit {
                    left_str = format!("({left_str}) as usize");
                }
                if right_is_i32_eff && !left_is_i32_eff && !left_is_float && !left_is_int_lit {
                    right_str = format!("({right_str}) as usize");
                }
            }
            format!("{left_str}{op_str}{right_str}")
        }
        Expr::Cast(var_type, inner) => {
            if ctx.generic && *var_type == VarType::Real {
                if expr_is_integer(inner) || expr_is_known_usize_ctx(inner, ctx) {
                    let rendered = render_expr(inner, ctx, opt_real_params, registry, helpers);
                    // optIn* params are i32, other integer-typed vars are usize after our mapping
                    if expr_is_i32_typed(inner) || matches!(inner.as_ref(), Expr::IntLiteral(_)) {
                        format!("T::ta_from_i32({rendered})")
                    } else {
                        format!("T::ta_from_i32(({rendered}) as i32)")
                    }
                } else {
                    format!(
                        "T::ta_from_f64(({}).ta_to_f64())",
                        render_expr(inner, ctx, opt_real_params, registry, helpers)
                    )
                }
            } else if ctx.generic && matches!(var_type, VarType::Integer | VarType::Index) {
                let rendered = render_expr(inner, ctx, opt_real_params, registry, helpers);
                if expr_is_i32_typed(inner) || matches!(inner.as_ref(), Expr::IntLiteral(_)) {
                    // Already i32: just cast to usize
                    format!("({rendered}) as usize")
                } else if expr_is_known_usize_ctx(inner, ctx) || expr_is_integer(inner) || expr_returns_usize(inner) {
                    // Already usize: no cast needed
                    rendered
                } else {
                    // T or unknown type: go through f64 first
                    let target = if matches!(var_type, VarType::Integer) { "i32" } else { "usize" };
                    format!("({rendered}).ta_to_f64() as {target}")
                }
            } else {
                let rust_type = match var_type {
                    VarType::Real => "f64",
                    VarType::Integer | VarType::Index => "usize",
                    VarType::RetCodeType => "RetCode",
                    VarType::RealPointer | VarType::IntPointer => "/* ptr cast */",
                    VarType::RealArray(_) | VarType::IntArray(_) => "/* array cast */",
                };
                format!(
                    "({}) as {}",
                    render_expr(inner, ctx, opt_real_params, registry, helpers),
                    rust_type
                )
            }
        }
        Expr::Not(inner) => {
            format!("!({})", render_expr(inner, ctx, opt_real_params, registry, helpers))
        }
        Expr::PointerDeref(name) => format!("(*{name})"),
        Expr::AddressOf(inner) => {
            // address-of not idiomatic in Rust; render inner expression directly
            render_expr(inner, ctx, opt_real_params, registry, helpers)
        }
        Expr::PostIncrement(inner) => {
            let rendered = render_expr(inner, ctx, opt_real_params, registry, helpers);
            format!("{{ let _v = {rendered}; {rendered} += 1; _v }}")
        }
        Expr::PostDecrement(inner) => {
            let rendered = render_expr(inner, ctx, opt_real_params, registry, helpers);
            format!("{{ let _v = {rendered}; {rendered} -= 1; _v }}")
        }
        Expr::PreIncrement(inner) => {
            let rendered = render_expr(inner, ctx, opt_real_params, registry, helpers);
            format!("{{ {rendered} += 1; {rendered} }}")
        }
        Expr::PreDecrement(inner) => {
            let rendered = render_expr(inner, ctx, opt_real_params, registry, helpers);
            format!("{{ {rendered} -= 1; {rendered} }}")
        }
        Expr::Ternary(cond, then_expr, else_expr) => {
            // Use render_condition for the ternary condition when it's a non-boolean
            // expression (integer variable, ternary producing integer, etc.)
            let cond_needs_bool = match cond.as_ref() {
                Expr::Ternary(_, t, _) => expr_is_untyped_integer(t) || matches!(t.as_ref(), Expr::IntLiteral(_)),
                Expr::Var(name) => ctx.index_vars.contains(name) || is_likely_index_var(name) || is_i32_opt_in_param(name),
                Expr::Not(inner) => matches!(inner.as_ref(), Expr::Var(name) if ctx.index_vars.contains(name) || is_likely_index_var(name)),
                // FuncCall that inlines to integer-producing ternary (e.g., ta_realbodygapup)
                Expr::FuncCall(fname, args) => {
                    if let Some(helper) = helpers.get(fname) {
                        if let Some(inlined) = try_inline_expr(helper, args) {
                            if let Expr::Ternary(_, ref t, _) = inlined {
                                expr_is_untyped_integer(t) || matches!(t.as_ref(), Expr::IntLiteral(_))
                            } else { false }
                        } else { is_integer_returning_helper(fname) }
                    } else { is_integer_returning_helper(fname) }
                }
                _ => false,
            };
            let cond_str = if cond_needs_bool {
                render_condition(cond, ctx, opt_real_params, registry, helpers)
            } else {
                render_expr(cond, ctx, opt_real_params, registry, helpers)
            };
            let then_str = render_expr(then_expr, ctx, opt_real_params, registry, helpers);
            let else_str = render_expr(else_expr, ctx, opt_real_params, registry, helpers);
            format!(
                "if {} {{ {} }} else {{ {} }}",
                cond_str, then_str, else_str
            )
        }
    }
}

/// Check if an expression is clearly integer-typed (for Cast optimization in generic mode).
/// When true, `T::ta_from_i32(expr as i32)` will be used instead of `T::ta_from_f64(expr.ta_to_f64())`.
fn expr_is_integer(expr: &Expr) -> bool {
    match expr {
        Expr::IntLiteral(_) => true,
        Expr::Var(name) => {
            is_i32_opt_in_param(name) || name.ends_with("_avgPeriod")
                || name.ends_with("_rangeType")
        }
        Expr::Cast(VarType::Integer | VarType::Index, _) => true,
        Expr::BinOp(left, _, right) => expr_is_integer(left) && expr_is_integer(right),
        _ => false,
    }
}

/// Check if an optIn parameter name is i32 (Integer type, not Real type).
/// Real optIn params (optInAcceleration, optInFastLimit, optInSlowLimit, optInNbDevUp/Dn,
/// optInMaximum, optInPenetration, optInVFactor) are f64, NOT i32.
fn is_i32_opt_in_param(name: &str) -> bool {
    if !name.starts_with("optIn") {
        return false;
    }
    // Known Real optIn params that are f64
    !matches!(name,
        "optInAcceleration" | "optInMaximum" | "optInOffsetOnReverse"
        | "optInFastLimit" | "optInSlowLimit"
        | "optInNbDevUp" | "optInNbDevDn" | "optInNbDev"
        | "optInPenetration" | "optInVFactor"
        | "optInStartValue" | "optInPercentage"
        | "optInAccelerationInitLong" | "optInAccelerationLong" | "optInAccelerationMaxLong"
        | "optInAccelerationInitShort" | "optInAccelerationShort" | "optInAccelerationMaxShort"
    )
}

/// Check if an expression is likely T-typed (float/Real) in generic context.
/// Used to decide whether an IntLiteral should be wrapped with `T::ta_from_i32()`.
/// Conservative: only returns true when there's strong evidence the expression produces T.
fn expr_is_float_typed(expr: &Expr) -> bool {
    expr_is_float_typed_ctx(expr, None)
}

fn expr_is_float_typed_ctx(expr: &Expr, ctx: Option<&RustRenderCtx>) -> bool {
    match expr {
        Expr::Literal(_) => true,
        Expr::Var(name) => {
            // Check context's real_vars set first
            if let Some(c) = ctx {
                if c.real_vars.contains(name) {
                    return true;
                }
                // If declared as index/integer in VarDecl, it's NOT float
                // Only use explicit declarations, not naming heuristics (which overlap)
                if c.index_vars.contains(name) {
                    return false;
                }
            }
            // Only match known float-typed variable patterns.
            // Exclude anything that could be an integer/index variable.
            name.starts_with("temp") || name.starts_with("prev")
                || name.starts_with("sum") || name.starts_with("diff")
                || name.ends_with("PeriodTotal")
                || name == "k" || name == "k1"
                || name.starts_with("factor") || name.ends_with("_factor")
                || name.starts_with("_true_range")
                || name.starts_with("_candlerange")
                || name.starts_with("_periodTotal")
                || name.starts_with("_meanValue")
                || name.starts_with("_tempReal")
        }
        Expr::ArrayAccess(name, _) => {
            // Check context's real_array_vars set
            if let Some(c) = ctx {
                if c.real_array_vars.contains(name) {
                    return true;
                }
            }
            // Real arrays: input arrays, temp buffers, output Real arrays
            name.starts_with("in") || name.starts_with("temp")
                || (name.starts_with("out") && !name.contains("Int") && !name.contains("integer"))
                || name.contains("_Odd") || name.contains("_Even")
                || name.starts_with("detrender") || name.starts_with("Q1")
                || name.starts_with("jI") || name.starts_with("jQ")
        }
        Expr::FuncCall(name, _) => {
            // Math functions and ta_ methods return T, but NOT integer-returning helpers
            if is_integer_returning_helper(name) {
                return false;
            }
            name.starts_with("ta_") || name.contains("_from_")
                || matches!(name.as_str(),
                    "sqrt" | "sin" | "cos" | "tan" | "asin" | "acos" | "atan"
                    | "exp" | "log" | "log10" | "ceil" | "floor" | "abs" | "fabs"
                    | "cosh" | "sinh" | "tanh" | "max" | "fmax" | "min" | "fmin"
                    | "IS_ZERO" | "PER_TO_K"
                )
        }
        Expr::BinOp(left, op, right) => {
            matches!(op, BinOp::Add | BinOp::Sub | BinOp::Mul | BinOp::Div)
                && (expr_is_float_typed_ctx(left, ctx) || expr_is_float_typed_ctx(right, ctx))
        }
        Expr::Cast(VarType::Real, _) => true,
        Expr::Ternary(_, then_expr, _) => expr_is_float_typed_ctx(then_expr, ctx),
        _ => false,
    }
}

/// Check if an expression is likely i32-typed (integer optIn params, unstable_period access, etc.)
/// Note: Real optIn params (optInAcceleration, optInFastLimit, optInSlowLimit, etc.) are f64, not i32.
fn expr_is_i32_typed(expr: &Expr) -> bool {
    match expr {
        Expr::Var(name) => {
            is_i32_opt_in_param(name) || name.ends_with("_avgPeriod")
                || name.ends_with("_rangeType")
        }
        Expr::FuncCall(name, args) => {
            if name == "UNSTABLE_PERIOD" {
                return true; // unstable_period array contains i32 values
            }
            // max(a,b) / min(a,b) preserve the type of their arguments.
            // If all args are i32-typed, the result is i32.
            if matches!(name.as_str(), "max" | "min" | "fmax" | "fmin") {
                return args.iter().all(|a| expr_is_i32_typed(a));
            }
            false
        }
        Expr::BinOp(left, op, right) if matches!(op, BinOp::Add | BinOp::Sub | BinOp::Mul | BinOp::Div | BinOp::Shr | BinOp::Shl | BinOp::Mod) => {
            expr_is_i32_typed(left) && (expr_is_i32_typed(right) || matches!(right.as_ref(), Expr::IntLiteral(_)))
                || expr_is_i32_typed(right) && matches!(left.as_ref(), Expr::IntLiteral(_))
        }
        Expr::Cast(VarType::Integer, _inner) => {
            true
        }
        _ => false,
    }
}

/// Check if an expression produces an untyped integer (IntLiteral, ternary with int branches, etc.)
/// These need wrapping with `T::ta_from_i32()` when used in a T-typed context.
fn expr_is_untyped_integer(expr: &Expr) -> bool {
    match expr {
        Expr::IntLiteral(_) => true,
        Expr::Ternary(_, then_expr, else_expr) => {
            expr_is_untyped_integer(then_expr) || expr_is_untyped_integer(else_expr)
        }
        Expr::FuncCall(name, _) => {
            // Integer-returning helpers inline to integer ternaries
            is_integer_returning_helper(name)
        }
        Expr::BinOp(left, op, right) if matches!(op, BinOp::Add | BinOp::Sub | BinOp::Mul | BinOp::Div | BinOp::Mod) => {
            let left_is_int = expr_is_untyped_integer(left) || matches!(left.as_ref(), Expr::IntLiteral(_));
            let right_is_int = expr_is_untyped_integer(right) || matches!(right.as_ref(), Expr::IntLiteral(_));
            left_is_int && right_is_int && !expr_is_i32_typed(left) && !expr_is_i32_typed(right)
        }
        _ => false,
    }
}

/// Check if an expression is already usize-typed (to avoid redundant `as usize` casts).
fn expr_is_usize(expr: &Expr) -> bool {
    matches!(expr, Expr::Cast(VarType::Index | VarType::Integer, _))
}

/// Check if an expression is provably usize-typed (for T-wrapping in arithmetic).
/// Uses the context's `index_vars` set when available, falls back to naming heuristics.
fn expr_is_known_usize_ctx(expr: &Expr, ctx: &RustRenderCtx) -> bool {
    match expr {
        Expr::Cast(VarType::Index | VarType::Integer, _) => true,
        Expr::Var(name) => {
            // Real vars are never usize, even if name matches heuristics
            if ctx.real_vars.contains(name) { return false; }
            ctx.index_vars.contains(name) || is_likely_index_var(name)
        }
        Expr::PointerDeref(name) => {
            // *outBegIdx, *outNBElement are usize
            ctx.index_vars.contains(name) || is_likely_index_var(name)
                || name == "outBegIdx" || name == "outNBElement"
        }
        Expr::BinOp(left, op, right) if matches!(op, BinOp::Add | BinOp::Sub | BinOp::Mul | BinOp::Div) => {
            (expr_is_known_usize_ctx(left, ctx) || matches!(left.as_ref(), Expr::IntLiteral(_)))
                && (expr_is_known_usize_ctx(right, ctx) || matches!(right.as_ref(), Expr::IntLiteral(_)))
        }
        _ => false,
    }
}



/// Check if an expression considered "i32-typed" by `expr_is_i32_typed` actually
/// renders as usize due to containing a `Cast(Integer/Index, inner)` where `inner`
/// is already usize. Used to detect BinOps with mixed rendered types.
fn expr_renders_as_usize_despite_i32(expr: &Expr, ctx: &RustRenderCtx) -> bool {
    match expr {
        Expr::Cast(VarType::Integer | VarType::Index, inner) => {
            // The Cast handler renders as identity (no `as usize`) when inner is
            // already usize-typed, making the whole expr usize at runtime
            expr_is_known_usize_ctx(inner, ctx)
                || expr_is_integer(inner)
                || expr_returns_usize(inner)
        }
        Expr::BinOp(left, _, right) => {
            expr_renders_as_usize_despite_i32(left, ctx)
                || expr_renders_as_usize_despite_i32(right, ctx)
        }
        _ => false,
    }
}

/// Check if a BinOp expression evaluates to usize after rendering, considering
/// that the BinOp handler casts i32 operands to usize when mixed with usize.
/// This detects expressions like `optInTimePeriod - (today - highestIdx)` where
/// optInTimePeriod is i32 but gets cast to usize at render time.
fn expr_binop_renders_as_usize(expr: &Expr, ctx: &RustRenderCtx) -> bool {
    if let Expr::BinOp(left, op, right) = expr {
        if !matches!(op, BinOp::Add | BinOp::Sub | BinOp::Mul | BinOp::Div) {
            return false;
        }
        let l_usize = expr_is_known_usize_ctx(left, ctx)
            || matches!(left.as_ref(), Expr::IntLiteral(_));
        let r_usize = expr_is_known_usize_ctx(right, ctx)
            || matches!(right.as_ref(), Expr::IntLiteral(_));
        let l_i32 = expr_is_i32_typed(left);
        let r_i32 = expr_is_i32_typed(right);
        // If one side is usize and the other is i32, the handler casts i32 to usize
        // Also if one side is a sub-BinOp that itself renders as usize
        let l_eff_usize = l_usize || expr_binop_renders_as_usize(left, ctx)
            || expr_renders_as_usize_despite_i32(left, ctx);
        let r_eff_usize = r_usize || expr_binop_renders_as_usize(right, ctx)
            || expr_renders_as_usize_despite_i32(right, ctx);
        // Mixed: one side usize, other i32 => renders as usize
        (l_eff_usize && r_i32) || (r_eff_usize && l_i32)
            // Both usize
            || (l_eff_usize && r_eff_usize)
    } else {
        false
    }
}

/// Render an array index expression, adding `as usize` when needed.
fn render_index_expr(
    idx: &Expr,
    ctx: &RustRenderCtx,
    opt_real_params: &[String],
    registry: &Registry,
    helpers: &HelperRegistry,
) -> String {
    let rendered = render_expr(idx, ctx, opt_real_params, registry, helpers);
    if expr_is_usize(idx) {
        rendered
    } else {
        format!("({rendered}) as usize")
    }
}

/// Render a complex lookback body (`LookbackExpr::Code`) into Rust code.
fn render_lookback_code(
    stmts: &[Statement],
    enums: &HashMap<String, EnumDef>,
    registry: &Registry,
    helpers: &HelperRegistry,
) -> String {
    let mut out = String::new();
    let empty_for_loop_vars: Vec<String> = Vec::new();
    let empty_var_inits: std::collections::HashMap<String, &Expr> =
        std::collections::HashMap::new();
    let empty_output_names: Vec<String> = Vec::new();
    let empty_opt_real_params: Vec<String> = Vec::new();

    for stmt in stmts {
        if let Statement::VarDecl { var_type, name, .. } = stmt {
            let total_assigns = count_assignments(name, stmts);
            // With default initialization, the let itself is an assignment,
            // so any body assignment means we need mut (threshold is > 0, not > 1)
            let needs_mut = total_assigns > 0;
            match var_type {
                VarType::RealArray(size) => {
                    out.push_str(&format!(
                        "        let mut {name}: [f64; {size} as usize] = [0.0_f64; {size} as usize];\n"
                    ));
                }
                VarType::IntArray(size) => {
                    out.push_str(&format!(
                        "        let mut {name}: [i32; {size} as usize] = [0i32; {size} as usize];\n"
                    ));
                }
                _ => {
                    let rust_type = match var_type {
                        VarType::Real => "f64",
                        VarType::Integer | VarType::Index => "usize",
                        VarType::RetCodeType => "RetCode",
                        VarType::RealPointer => "Vec<f64>",
                        VarType::IntPointer => "Vec<i32>",
                        VarType::RealArray(_) | VarType::IntArray(_) => unreachable!(),
                    };
                    // Always initialize — lookback is always concrete (non-generic)
                    let default_val = match var_type {
                        VarType::Real => "0.0_f64",
                        VarType::Integer | VarType::Index => "0_usize",
                        VarType::RetCodeType => "RetCode::Success",
                        VarType::RealPointer | VarType::IntPointer => "Vec::new()",
                        VarType::RealArray(_) | VarType::IntArray(_) => unreachable!(),
                    };
                    if needs_mut {
                        out.push_str(&format!("        let mut {name}: {rust_type} = {default_val};\n"));
                    } else {
                        out.push_str(&format!("        let {name}: {rust_type} = {default_val};\n"));
                    }
                }
            }
        }
    }

    // Emit candle settings unpacking for lookback body
    let candle_used = detect_candle_settings(stmts);
    if !candle_used.is_empty() {
        out.push_str(&emit_rust_unpacking(&candle_used, 8));
    }

    let mut lookback_ctx = RustRenderCtx::concrete();
    lookback_ctx.is_lookback = true;
    let inline_counter = Cell::new(0);
    for stmt in stmts {
        if matches!(stmt, Statement::VarDecl { .. }) {
            continue;
        }
        out.push_str(&render_statement(
            stmt,
            8,
            &lookback_ctx,
            &empty_for_loop_vars,
            &empty_var_inits,
            &empty_output_names,
            &empty_opt_real_params,
            enums,
            registry,
            helpers,
            &inline_counter,
        ));
    }

    out
}

fn to_pascal_case(s: &str) -> String {
    // Direct mapping for known FuncUnstId names
    match s {
        "HT_DCPERIOD" => return "HtDcPeriod".to_string(),
        "HT_DCPHASE" => return "HtDcPhase".to_string(),
        "HT_PHASOR" => return "HtPhasor".to_string(),
        "HT_SINE" => return "HtSine".to_string(),
        "HT_TRENDLINE" => return "HtTrendline".to_string(),
        "HT_TRENDMODE" => return "HtTrendMode".to_string(),
        "MINUS_DI" => return "MinusDI".to_string(),
        "MINUS_DM" => return "MinusDM".to_string(),
        "PLUS_DI" => return "PlusDI".to_string(),
        "PLUS_DM" => return "PlusDM".to_string(),
        "STOCH_RSI" | "STOCHRSI" => return "StochRsi".to_string(),
        _ => {}
    }
    s.split('_')
        .filter(|part| !part.is_empty())
        .map(|part| {
            let lower = part.to_lowercase();
            let mut chars = lower.chars();
            match chars.next() {
                None => String::new(),
                Some(c) => c.to_uppercase().collect::<String>() + chars.as_str(),
            }
        })
        .collect()
}

/// Known math functions that map to `TaFloat` trait methods (generic) or `f64` methods (concrete).
/// 2-arg functions (`max`, `min`, `fmax`, `fmin`) render as `a.max(b)` / `a.min(b)`.
/// `ABS` maps to `abs` / `ta_abs`.
const MATH_FUNCTIONS: &[&str] = &[
    "sqrt", "sin", "cos", "tan", "asin", "acos", "atan", "exp", "log", "log10", "ceil", "floor",
    "abs", "fabs", "cosh", "sinh", "tanh", "ABS", "max", "fmax", "min", "fmin",
];

/// Scan an expression tree for `sizeof(TYPE)` and return the type name.
/// Used by `malloc` to determine the Rust Vec element type.
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
fn decompose_rust_array_ref(
    expr: &Expr,
    ctx: &RustRenderCtx,
    opt_real_params: &[String],
    registry: &Registry,
    helpers: &HelperRegistry,
) -> (String, String) {
    match expr {
        Expr::AddressOf(inner) => if let Expr::ArrayAccess(name, offset) = inner.as_ref() {
            let off = render_index_expr(offset, ctx, opt_real_params, registry, helpers);
            (name.clone(), off)
        } else {
            let s = render_expr(expr, ctx, opt_real_params, registry, helpers);
            (s, "0".to_string())
        },
        Expr::Var(name) => (name.clone(), "0".to_string()),
        _ => {
            let s = render_expr(expr, ctx, opt_real_params, registry, helpers);
            (s, "0".to_string())
        }
    }
}

#[allow(clippy::too_many_lines)]
fn render_func_call(
    fname: &str,
    args: &[Expr],
    ctx: &RustRenderCtx,
    opt_real_params: &[String],
    registry: &Registry,
    helpers: &HelperRegistry,
) -> String {
    // Check if this is a call to a helper function that can be inlined
    if let Some(helper) = helpers.get(fname) {
        if let Some(inlined_expr) = try_inline_expr(helper, args) {
            return render_expr(&inlined_expr, ctx, opt_real_params, registry, helpers);
        }
        // Multi-statement helpers: Task 10 will handle
    }
    if fname == "UNSTABLE_PERIOD" {
        if let Some(Expr::Var(func_name)) = args.first() {
            let base = func_name
                .strip_prefix("FUNC_UNST_")
                .unwrap_or(func_name);
            let pascal = to_pascal_case(base);
            return format!("self.unstable_period[FuncUnstId::{pascal} as usize]");
        }
        "self.unstable_period[0]".to_string()
    } else if fname == "COMPATIBILITY" {
        "self.compatibility".to_string()
    } else if fname == "IS_ZERO" {
        if let Some(arg) = args.first() {
            let x = render_expr(arg, ctx, opt_real_params, registry, helpers);
            if ctx.generic {
                return format!("{x}.ta_abs() < T::ta_epsilon()");
            }
            return format!("((-(0.00000000000001)) < {x}) && ({x} < (0.00000000000001))");
        }
        "false".to_string()
    } else if fname == "ARRAY_COPY" {
        if args.len() == 5 {
            let dst = render_expr(&args[0], ctx, opt_real_params, registry, helpers);
            let dst_off = render_expr(&args[1], ctx, opt_real_params, registry, helpers);
            let src = render_expr(&args[2], ctx, opt_real_params, registry, helpers);
            let src_off = render_expr(&args[3], ctx, opt_real_params, registry, helpers);
            let count = render_expr(&args[4], ctx, opt_real_params, registry, helpers);
            return format!(
                "{{\n            let _n = ({count}) as usize;\n            let _di = ({dst_off}) as usize;\n            let _si = ({src_off}) as usize;\n            {dst}[_di.._di + _n].copy_from_slice(&{src}[_si.._si + _n]);\n        }}"
            );
        }
        "/* ARRAY_COPY: bad args */".to_string()
    } else if fname == "PER_TO_K" {
        if let Some(arg) = args.first() {
            let x = render_expr(arg, ctx, opt_real_params, registry, helpers);
            if ctx.generic {
                return format!("T::ta_from_f64(2.0) / (T::ta_from_i32({x}) + T::ta_one())");
            }
            return format!("2.0_f64 / (({x}) as f64 + 1.0_f64)");
        }
        if ctx.generic {
            "T::ta_zero()".to_string()
        } else {
            "0.0_f64".to_string()
        }
    } else if fname.ends_with("_Lookback") {
        let rust_name = fname.to_lowercase();
        let rendered_args: Vec<String> = args
            .iter()
            .map(|a| {
                // Real optIn params stay as f64 in lookback calls (no T-wrapping, no i32 cast)
                let is_opt_real = matches!(a, Expr::Var(n) if !is_i32_opt_in_param(n) && n.starts_with("optIn"));
                if is_opt_real {
                    // Render without T-wrapping
                    let empty_opt: Vec<String> = Vec::new();
                    return render_expr(a, ctx, &empty_opt, registry, helpers);
                }
                // Float literals are Real optIn values — don't cast to i32
                if matches!(a, Expr::Literal(_)) {
                    let empty_opt: Vec<String> = Vec::new();
                    return render_expr(a, ctx, &empty_opt, registry, helpers);
                }
                let rendered = render_expr(a, ctx, opt_real_params, registry, helpers);
                // Lookback functions take i32 params for Integer optIns; cast non-i32 args
                if !expr_is_i32_typed(a) && !matches!(a, Expr::IntLiteral(_)) {
                    format!("({rendered}) as i32")
                } else {
                    rendered
                }
            })
            .collect();
        format!("self.{}({})", rust_name, rendered_args.join(", "))
    } else if fname.ends_with("_lookback") {
        let rendered_args: Vec<String> = args
            .iter()
            .map(|a| {
                // Real optIn params stay as f64 in lookback calls (no T-wrapping, no i32 cast)
                let is_opt_real = matches!(a, Expr::Var(n) if !is_i32_opt_in_param(n) && n.starts_with("optIn"));
                if is_opt_real {
                    let empty_opt: Vec<String> = Vec::new();
                    return render_expr(a, ctx, &empty_opt, registry, helpers);
                }
                // Float literals are Real optIn values — don't cast to i32
                if matches!(a, Expr::Literal(_)) {
                    let empty_opt: Vec<String> = Vec::new();
                    return render_expr(a, ctx, &empty_opt, registry, helpers);
                }
                let rendered = render_expr(a, ctx, opt_real_params, registry, helpers);
                // Lookback functions take i32 params for Integer optIns; cast non-i32 args
                if !expr_is_i32_typed(a) && !matches!(a, Expr::IntLiteral(_)) {
                    format!("({rendered}) as i32")
                } else {
                    rendered
                }
            })
            .collect();
        format!("self.{}({})", fname, rendered_args.join(", "))
    } else if is_math_function(fname) {
        // Math functions take priority over the indicator registry.
        // `atan(x)` in source means the C math function, not a cross-indicator call.
        //
        // 2-arg: max/fmax → a.max(b), min/fmin → a.min(b)
        // 1-arg: ABS/fabs → .ta_abs() (generic) or .abs() (concrete)
        // 1-arg: all others → .ta_{fname}() (generic) or .{fname}() (concrete)
        match fname {
            "max" | "fmax" => {
                if args.len() >= 2 {
                    let a = render_expr(&args[0], ctx, opt_real_params, registry, helpers);
                    let b = render_expr(&args[1], ctx, opt_real_params, registry, helpers);
                    return format!("({a}).max({b})");
                }
            }
            "min" | "fmin" => {
                if args.len() >= 2 {
                    let a = render_expr(&args[0], ctx, opt_real_params, registry, helpers);
                    let b = render_expr(&args[1], ctx, opt_real_params, registry, helpers);
                    return format!("({a}).min({b})");
                }
            }
            _ => {}
        }
        if let Some(arg) = args.first() {
            let x = render_expr(arg, ctx, opt_real_params, registry, helpers);
            if ctx.generic {
                let method = if fname == "fabs" || fname == "ABS" {
                    "ta_abs".to_string()
                } else if fname == "log" {
                    "ta_ln".to_string()
                } else {
                    format!("ta_{fname}")
                };
                // Wrap integer literals/expressions so we can call TaFloat methods on them
                let x_wrapped = if matches!(arg, Expr::IntLiteral(_)) {
                    if let Expr::IntLiteral(v) = arg {
                        format!("T::ta_from_i32({v})")
                    } else {
                        x
                    }
                } else if expr_is_untyped_integer(arg) {
                    format!("T::ta_from_i32({x} as i32)")
                } else {
                    x
                };
                return format!("{x_wrapped}.{method}()");
            }
            // Concrete (non-generic) path: use f64 method call syntax; fabs/ABS -> abs, log -> ln
            let method = match fname {
                "fabs" | "ABS" => "abs",
                "log" => "ln",
                other => other,
            };
            return format!("({x}).{method}()");
        }
        format!("{fname}()")
    } else if fname == "sizeof" {
        // sizeof(TYPE) → 1: normalizes byte counts to element counts for Rust array operations
        "1".to_string()
    } else if fname == "malloc" {
        // malloc(N * sizeof(TYPE)) → vec![default; N as usize]
        // sizeof renders as 1, so the arg is already the element count
        if let Some(arg) = args.first() {
            let size = render_expr(arg, ctx, opt_real_params, registry, helpers);
            match find_sizeof_type(arg).as_deref() {
                Some("int") => format!("vec![0_i32; ({size}) as usize]"),
                _ => {
                    if ctx.generic {
                        format!("vec![T::ta_zero(); ({size}) as usize]")
                    } else {
                        format!("vec![0.0_f64; ({size}) as usize]")
                    }
                }
            }
        } else {
            "vec![]".to_string()
        }
    } else if fname == "free" {
        // No-op in Rust (Vec/Box drops automatically)
        String::new()
    } else if fname == "memcpy" || fname == "memmove" {
        // memcpy/memmove(dst, src, count) → slice copy
        if args.len() >= 3 {
            let (dst_arr, dst_off) =
                decompose_rust_array_ref(&args[0], ctx, opt_real_params, registry, helpers);
            let (src_arr, src_off) =
                decompose_rust_array_ref(&args[1], ctx, opt_real_params, registry, helpers);
            let count = render_expr(&args[2], ctx, opt_real_params, registry, helpers);
            format!(
                "{{\n            let _n = ({count}) as usize;\
                 \n            let _di = ({dst_off}) as usize;\
                 \n            let _si = ({src_off}) as usize;\
                 \n            {dst_arr}[_di.._di + _n].copy_from_slice(&{src_arr}[_si.._si + _n]);\
                 \n        }}"
            )
        } else {
            format!("/* {fname}: bad args */")
        }
    } else if fname == "memset" {
        // memset(buf, 0, count) → slice fill
        if args.len() >= 3 {
            let (arr, off) =
                decompose_rust_array_ref(&args[0], ctx, opt_real_params, registry, helpers);
            let count = render_expr(&args[2], ctx, opt_real_params, registry, helpers);
            let fill_val = match find_sizeof_type(&args[2]).as_deref() {
                Some("int") => "0_i32".to_string(),
                _ => {
                    if ctx.generic {
                        "T::ta_zero()".to_string()
                    } else {
                        "0.0_f64".to_string()
                    }
                }
            };
            format!(
                "{{\n            let _n = ({count}) as usize;\
                 \n            let _si = ({off}) as usize;\
                 \n            {arr}[_si.._si + _n].fill({fill_val});\
                 \n        }}"
            )
        } else {
            "/* memset: bad args */".to_string()
        }
    } else if fname == "ta_candleaverage" || fname == "ta_candlerange" {
        let rendered_args: Vec<String> = args
            .iter()
            .map(|a| render_expr(a, ctx, opt_real_params, registry, helpers))
            .collect();
        format!("self.{}({})", fname, rendered_args.join(", "))
    } else if registry.contains(fname) {
        let rust_name = if ctx.generic {
            format!("{fname}_unguarded")
        } else {
            format!("{fname}_logic")
        };
        let rendered_args = render_cross_indicator_args(args, ctx, opt_real_params, registry, helpers);
        format!("self.{}({})", rust_name, rendered_args.join(", "))
    } else if is_ta_function(fname) {
        let rust_name = fname.to_lowercase();
        let rendered_args = render_cross_indicator_args(args, ctx, opt_real_params, registry, helpers);
        format!("self.{}({})", rust_name, rendered_args.join(", "))
    } else {
        let rendered_args: Vec<String> = args
            .iter()
            .map(|a| render_expr(a, ctx, opt_real_params, registry, helpers))
            .collect();
        format!("{}({})", fname, rendered_args.join(", "))
    }
}

/// Render all arguments for a cross-indicator call, detecting input vs output positions.
/// Cross-indicator signatures follow: startIdx, endIdx, inputs..., opts..., &outBegIdx, &outNBElement, outputs...
/// The two AddressOf args (outBegIdx, outNBElement) mark the boundary.
/// Input-position Vec locals use `&name` (coerces to `&[T]`).
/// Output-position Vec locals use `&mut name[..]` (coerces to `&mut [T]`).
fn render_cross_indicator_args(
    args: &[Expr],
    ctx: &RustRenderCtx,
    opt_real_params: &[String],
    registry: &Registry,
    helpers: &HelperRegistry,
) -> Vec<String> {
    // Find the outBegIdx/outNBElement boundary: two consecutive AddressOf args.
    // Everything after the second one is output slice/array position.
    // Don't use last AddressOf because outputs can also be AddressOf (e.g., &prevATR for scalar T).
    let output_start = find_output_boundary(args);

    // Collect output variable names for aliasing detection
    let output_vars: Vec<&str> = args[output_start..].iter()
        .filter_map(|a| if let Expr::Var(n) = a { Some(n.as_str()) } else { None })
        .collect();

    // Detect duplicate AddressOf vars (e.g., &tempInt used for both outBegIdx and outNBElement)
    let mut seen_address_of: std::collections::HashSet<String> = std::collections::HashSet::new();
    // Track which args need a pre-declared dummy (second mutable borrow of same var)
    let mut dup_vars: Vec<(usize, String)> = Vec::new();
    for (i, arg) in args.iter().enumerate() {
        if let Expr::AddressOf(inner) = arg {
            if let Expr::Var(name) = inner.as_ref() {
                if !seen_address_of.insert(name.clone()) {
                    dup_vars.push((i, name.clone()));
                }
            }
        }
    }

    args.iter()
        .enumerate()
        .map(|(i, arg)| {
            let is_output = i >= output_start;
            // Detect input-output aliasing: same Vec var used as both input and output
            if !is_output {
                if let Expr::Var(name) = arg {
                    if (ctx.vec_vars.contains(name) || is_vec_local_var(name))
                        && output_vars.contains(&name.as_str())
                    {
                        // Clone to avoid borrow conflict
                        return format!("&{name}.clone()");
                    }
                }
            }
            // Detect duplicate &mut borrows: use the pre-declared dummy variable
            if let Some((_, _)) = dup_vars.iter().find(|(idx, _)| *idx == i) {
                return "&mut _dup_out".to_string();
            }
            render_cross_indicator_arg(arg, i, is_output, ctx, opt_real_params, registry, helpers)
        })
        .collect()
}

/// Render a single argument for a cross-indicator call.
/// - `AddressOf(Var(name))` → `&mut name` (C `&scalar` becomes Rust `&mut scalar`)
/// - `Var(name)` where name is a Vec local → `&name` for inputs, `&mut name[..]` for outputs
/// - First two args (idx 0,1 = startIdx, endIdx) cast i32 to usize
/// - Scalar T vars in output position get `std::slice::from_mut()` wrapping
/// - Literal values and optIn Real params are rendered as f64 (not T-wrapped)
fn render_cross_indicator_arg(
    arg: &Expr,
    position: usize,
    is_output_position: bool,
    ctx: &RustRenderCtx,
    opt_real_params: &[String],
    registry: &Registry,
    helpers: &HelperRegistry,
) -> String {
    match arg {
        // &outBegIdxDummy -> &mut outBegIdxDummy
        // Special handling for Vec and scalar T vars in output position
        Expr::AddressOf(inner) => {
            if let Expr::Var(name) = inner.as_ref() {
                if is_output_position && (ctx.vec_vars.contains(name) || is_vec_local_var(name)) {
                    return format!("&mut {name}[..]");
                }
                if is_output_position && ctx.real_vars.contains(name) {
                    return format!("std::slice::from_mut(&mut {name})");
                }
            }
            let rendered = render_expr(inner, ctx, opt_real_params, registry, helpers);
            format!("&mut {rendered}")
        }
        // Vec<T> local variables: &name for input position, &mut name[..] for output position
        Expr::Var(name) if ctx.vec_vars.contains(name) || is_vec_local_var(name) => {
            if is_output_position {
                format!("&mut {name}[..]")
            } else {
                format!("&{name}")
            }
        }
        // Literal values in cross-indicator calls: render as raw f64 (not T-wrapped)
        // because the callee's optIn Real params are f64
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
        // optIn Real params: render without T-wrapping for cross-indicator calls
        Expr::Var(name) if !is_i32_opt_in_param(name) && name.starts_with("optIn") => {
            name.clone()
        }
        // RealArray vars (e.g., [T; N]): &mut name in output position, &name in input
        Expr::Var(name) if ctx.real_array_vars.contains(name) => {
            if is_output_position {
                format!("&mut {name}")
            } else {
                format!("&{name}")
            }
        }
        _ => {
            let rendered = render_expr(arg, ctx, opt_real_params, registry, helpers);
            // First two positions are startIdx, endIdx (usize) — cast i32 args
            if position <= 1 && (expr_is_i32_typed(arg) || matches!(arg, Expr::BinOp(_, _, _) if has_any_i32_operand(arg))) {
                format!("({rendered}) as usize")
            // Output position: scalar T vars need slice wrapping
            } else if is_output_position {
                if let Expr::Var(name) = arg {
                    if ctx.real_vars.contains(name) {
                        return format!("std::slice::from_mut(&mut {name})");
                    }
                }
                rendered
            // Non-startIdx/endIdx, non-output position: if a usize variable is passed
            // where an i32 param is expected (e.g., curPeriod to ma_unguarded), cast to i32
            } else if position > 1 && !is_output_position {
                if let Expr::Var(name) = arg {
                    if (ctx.index_vars.contains(name) || is_likely_index_var(name))
                        && !name.starts_with("in") && !name.starts_with("out")
                    {
                        return format!("({rendered}) as i32");
                    }
                }
                rendered
            } else {
                rendered
            }
        }
    }
}

/// Find the output boundary in cross-indicator call args.
/// Cross-indicator signatures are: startIdx, endIdx, inputs..., opts..., &outBegIdx, &outNBElement, outputs...
/// The boundary is after the outBegIdx/outNBElement pair. These can be:
/// - AddressOf pairs: `&outBegIdx1, &outNbElement1`
/// - Var pairs when passing through from caller: `outBegIdx, outNBElement`
/// Returns the index of the first output arg.
fn find_output_boundary(args: &[Expr]) -> usize {
    // Look for consecutive AddressOf pairs first (starting from position 2+)
    for i in 2..args.len().saturating_sub(1) {
        if matches!(&args[i], Expr::AddressOf(_)) && matches!(&args[i + 1], Expr::AddressOf(_)) {
            return i + 2;
        }
    }
    // Also check for Var pairs that look like outBegIdx/outNBElement
    for i in 2..args.len().saturating_sub(1) {
        if is_beg_nb_var(&args[i]) && is_beg_nb_var(&args[i + 1]) {
            return i + 2;
        }
    }
    // Fallback: no boundary found, all args are non-output
    args.len()
}

/// Check if a Var expression looks like an outBegIdx or outNBElement parameter.
fn is_beg_nb_var(expr: &Expr) -> bool {
    match expr {
        Expr::Var(name) => {
            let lower = name.to_lowercase();
            lower.contains("begidx") || lower.contains("nbelement")
        }
        Expr::AddressOf(inner) => is_beg_nb_var(inner),
        _ => false,
    }
}

/// Check if a FuncCall expression has duplicate AddressOf args (same var borrowed mutably twice).
fn has_duplicate_address_of(expr: &Expr) -> bool {
    if let Expr::FuncCall(_, args) = expr {
        let mut seen = std::collections::HashSet::new();
        for arg in args {
            if let Expr::AddressOf(inner) = arg {
                if let Expr::Var(name) = inner.as_ref() {
                    if !seen.insert(name.clone()) {
                        return true;
                    }
                }
            }
        }
    }
    false
}

/// Check if a BinOp expression contains any i32-typed operands.
fn has_any_i32_operand(expr: &Expr) -> bool {
    match expr {
        Expr::BinOp(left, _, right) => {
            expr_is_i32_typed(left) || expr_is_i32_typed(right)
                || has_any_i32_operand(left) || has_any_i32_operand(right)
        }
        _ => expr_is_i32_typed(expr),
    }
}

/// Check if a variable name is likely a Vec<T> local variable (allocated via malloc).
/// These need `&` to convert to `&[T]` when passed to cross-indicator calls.
fn is_vec_local_var(name: &str) -> bool {
    name.starts_with("tempBuffer")
        || name.starts_with("localBuffer")
        || name.starts_with("buffer")
        || name.starts_with("localOutput")
        || name.starts_with("tempOutput")
}

/// Check if an expression returns usize (e.g., lookback function calls, UNSTABLE_PERIOD).
fn expr_returns_usize(expr: &Expr) -> bool {
    match expr {
        Expr::FuncCall(name, _) => {
            name.ends_with("_lookback") || name.ends_with("_Lookback")
                || name == "UNSTABLE_PERIOD"
        }
        _ => false,
    }
}

/// Check if a variable name is an IntArray (i32 element array).
/// These should NOT be wrapped with T::ta_from_i32() when assigned to.
fn is_int_array_var(name: &str) -> bool {
    matches!(name,
        "periods" | "usedFlag" | "sortedPeriods"
    )
}

fn is_math_function(name: &str) -> bool {
    MATH_FUNCTIONS.contains(&name)
}

/// Helper functions that return int (not double/T).
/// These must NOT be treated as float-typed by `expr_is_float_typed`.
fn is_integer_returning_helper(name: &str) -> bool {
    matches!(name,
        "ta_candlecolor" | "ta_realbodygapup" | "ta_realbodygapdown"
        | "ta_candlegapup" | "ta_candlegapdown"
    )
}

/// Check if a variable name is likely an index/counter (usize) rather than a Real (T) variable.
fn is_likely_index_var(name: &str) -> bool {
    // Never match optIn params — they are i32 in the function signature
    if name.starts_with("optIn") {
        return false;
    }
    name == "startIdx" || name == "endIdx" || name == "lookbackTotal"
        || name == "trailingIdx" || name == "today" || name == "i"
        || name == "outIdx" || name == "nbInitialElementNeeded"
        || name == "nbElement" || name == "nbElementToOutput"
        || name.ends_with("Idx")
        || name == "outBegIdx" || name == "outNBElement"
        || name.starts_with("nb")
        || name == "j" || name == "count"
        || name == "outputSize" || name == "lookbackTotal"
        || name.ends_with("Dummy") || name.ends_with("_idx")
        || name == "highestIdx" || name == "lowestIdx"
        || name == "isLong" || name == "isShort"
        || name == "currentBar"
        || name == "tempInteger" || name == "tempInt"
        || name == "tempMAType"
        || name == "retValue"
        || name == "trend" || name == "daysInTrend"
        || name == "patternResult" || name == "patternIdx"
        || name == "maxPeriod" || name == "longestPeriod"
        || name == "longestIndex" || name == "divider"
        || name == "curPeriod"
}

fn is_ta_function(name: &str) -> bool {
    !name.is_empty()
        && name.chars().all(|c| c.is_ascii_uppercase() || c == '_')
        && !matches!(
            name,
            "UNSTABLE_PERIOD"
                | "IS_ZERO"
                | "ARRAY_COPY"
                | "PER_TO_K"
                | "COMPATIBILITY"
                | "METASTOCK"
                | "DEFAULT"
        )
        && !name.ends_with("_Lookback")
}

fn gen_footer() -> String {
    "/* Generated */\n\n\
     /***************/\n\
     /* End of File */\n\
     /***************/\n"
        .to_string()
}
