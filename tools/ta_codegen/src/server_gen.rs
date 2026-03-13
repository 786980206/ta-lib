//! Generates JSON-RPC server source files for each target language.
//!
//! Each generated server reads JSON-RPC requests from stdin, dispatches to
//! the generated TA function implementations, and writes JSON responses to stdout.
//! All servers speak the same protocol as the existing Rust server in server.rs.

use crate::ir::{FuncDef, Input, OptInput, Output, ParamType};
use std::path::Path;

/// Generate the JSON response key for an output at position `idx` among all outputs.
///
/// Naming convention (matches ta_regtest expectations):
/// - Real outputs: index 0 → `"outReal"`, index 1 → `"outReal1"`, index 2 → `"outReal2"`
/// - Integer outputs: index 0 → `"outInteger"`, index 1 → `"outInteger1"`
///
/// Counters are per-type: two real outputs and one integer output yield
/// `"outReal"`, `"outReal1"`, `"outInteger"` (not `"outInteger2"`).
fn output_json_key(outputs: &[Output], idx: usize) -> String {
    let out = &outputs[idx];
    // Count how many outputs of the same type appear before this one.
    let type_rank = outputs[..idx]
        .iter()
        .filter(|o| o.param_type == out.param_type)
        .count();
    match out.param_type {
        ParamType::Integer => {
            if type_rank == 0 {
                "outInteger".to_string()
            } else {
                format!("outInteger{type_rank}")
            }
        }
        _ => {
            if type_rank == 0 {
                "outReal".to_string()
            } else {
                format!("outReal{type_rank}")
            }
        }
    }
}

/// Expand a list of inputs into individual array parameter names.
///
/// - `ParamType::Real` → keeps the input's own name (e.g. `"inReal"`)
/// - `ParamType::Price(components)` → one name per component, capitalised:
///   `["high", "low", "close"]` → `["inHigh", "inLow", "inClose"]`
/// - All other types (Integer, Enum) are skipped.
fn expand_input_names(inputs: &[Input]) -> Vec<String> {
    let mut names = Vec::new();
    for inp in inputs {
        match &inp.param_type {
            ParamType::Real => names.push(inp.name.clone()),
            ParamType::Price(components) => {
                for comp in components {
                    let name = format!(
                        "in{}{}",
                        comp[..1].to_uppercase(),
                        &comp[1..]
                    );
                    names.push(name);
                }
            }
            _ => {} // Integer / Enum inputs are not array parameters
        }
    }
    names
}

/// Map function name to its unstable period ID (integer value).
/// Returns None for functions without unstable period.
/// IDs must match the `TA_FuncUnstId` enum in `include/ta_defs.h`.
fn func_unst_id(name: &str) -> Option<i32> {
    match name {
        "ADX" => Some(0),        // TA_FUNC_UNST_ADX
        "ADXR" => Some(1),       // TA_FUNC_UNST_ADXR
        "ATR" => Some(2),        // TA_FUNC_UNST_ATR
        "CMO" => Some(3),        // TA_FUNC_UNST_CMO
        "DX" => Some(4),         // TA_FUNC_UNST_DX
        "EMA" => Some(5),        // TA_FUNC_UNST_EMA
        "HT_DCPERIOD" => Some(6), // TA_FUNC_UNST_HT_DCPERIOD
        "HT_DCPHASE" => Some(7), // TA_FUNC_UNST_HT_DCPHASE
        "HT_PHASOR" => Some(8),  // TA_FUNC_UNST_HT_PHASOR
        "HT_SINE" => Some(9),    // TA_FUNC_UNST_HT_SINE
        "HT_TRENDLINE" => Some(10), // TA_FUNC_UNST_HT_TRENDLINE
        "HT_TRENDMODE" => Some(11), // TA_FUNC_UNST_HT_TRENDMODE
        "IMI" => Some(12),       // TA_FUNC_UNST_IMI
        "KAMA" => Some(13),      // TA_FUNC_UNST_KAMA
        "MAMA" => Some(14),      // TA_FUNC_UNST_MAMA
        "MFI" => Some(15),       // TA_FUNC_UNST_MFI
        "MINUS_DI" => Some(16),  // TA_FUNC_UNST_MINUS_DI
        "MINUS_DM" => Some(17),  // TA_FUNC_UNST_MINUS_DM
        "NATR" => Some(18),      // TA_FUNC_UNST_NATR
        "PLUS_DI" => Some(19),   // TA_FUNC_UNST_PLUS_DI
        "PLUS_DM" => Some(20),   // TA_FUNC_UNST_PLUS_DM
        "RSI" => Some(21),       // TA_FUNC_UNST_RSI
        "STOCHRSI" => Some(22),  // TA_FUNC_UNST_STOCHRSI
        "T3" => Some(23),        // TA_FUNC_UNST_T3
        _ => None,
    }
}

/// Replace @@`CORE_XXX`@@ markers in the Java server template with actual
/// method bodies read from the generated Core_*.java files.
pub fn inline_java_core_methods(template: &str, java_dir: &Path, funcs: &[FuncDef]) -> String {
    let mut result = template.to_string();
    for func in funcs {
        let marker = format!("    // @@CORE_{}@@", func.name);
        let core_path = java_dir.join(format!("Core_{}.java", func.name));
        let replacement = if core_path.exists() {
            let content = std::fs::read_to_string(&core_path).unwrap();
            // Strip /* Generated */ prefix, remove duplicate consecutive return statements,
            // and indent properly
            let mut lines: Vec<String> = Vec::new();
            let mut prev_was_return = false;
            for line in content.lines() {
                let trimmed = line.strip_prefix("/* Generated */").unwrap_or(line);
                let is_return = trimmed.trim().starts_with("return ");
                // Skip duplicate consecutive return statements (Java treats these as errors)
                if is_return && prev_was_return {
                    continue;
                }
                prev_was_return = is_return;
                if trimmed.trim().is_empty() {
                    lines.push(String::new());
                } else {
                    lines.push(format!("    {trimmed}"));
                }
            }
            lines.join("\n")
        } else {
            format!("    // WARNING: {} not found", core_path.display())
        };
        result = result.replace(&marker, &replacement);
    }
    result
}

/// Build the C parameter string for a lookback function.
///
/// Lookback functions only take optional inputs (those affect the lookback period).
/// Returns an empty string if the function has no optional inputs.
fn build_lookback_param_str(func: &FuncDef) -> String {
    if func.optional_inputs.is_empty() {
        return "void".to_string();
    }
    func.optional_inputs
        .iter()
        .map(opt_input_to_c_param)
        .collect::<Vec<_>>()
        .join(", ")
}

/// Build the C parameter string for the full indicator function (and _Logic variant).
///
/// Order: startIdx, endIdx, inputs, optional inputs, outBegIdx, outNBElement, outputs.
fn build_full_param_str(func: &FuncDef) -> String {
    let mut params: Vec<String> = vec!["int startIdx".to_string(), "int endIdx".to_string()];

    for input in &func.inputs {
        match &input.param_type {
            ParamType::Real => params.push(format!("const double {}[]", input.name)),
            ParamType::Price(components) => {
                for comp in components {
                    let name = format!("in{}{}", &comp[..1].to_uppercase(), &comp[1..]);
                    params.push(format!("const double {name}[]"));
                }
            }
            ParamType::Integer => params.push(format!("const int {}[]", input.name)),
            ParamType::Enum(_) => params.push(format!("int {}", input.name)),
        }
    }

    for opt in &func.optional_inputs {
        params.push(opt_input_to_c_param(opt));
    }

    params.push("int *outBegIdx".to_string());
    params.push("int *outNBElement".to_string());

    for out in &func.outputs {
        match out.param_type {
            ParamType::Integer => params.push(format!("int {}[]", out.name)),
            _ => params.push(format!("double {}[]", out.name)),
        }
    }

    params.join(", ")
}

/// Map an optional input to its C parameter declaration.
fn opt_input_to_c_param(opt: &OptInput) -> String {
    match &opt.param_type {
        ParamType::Real => format!("double {}", opt.name),
        _ => format!("int {}", opt.name),
    }
}

/// Generate a standalone C JSON-RPC server source file.
///
/// The generated file #includes the generated ta_*.c files and provides
/// a `main()` loop that reads JSON-RPC from stdin.
/// Generate a minimal `ta_func.h` stub for standalone compilation of the C server.
///
/// This file provides just the type definitions that the generated ta_*.c files
/// expect, without pulling in the full TA-Lib headers.
pub fn generate_c_header_stub(funcs: &[FuncDef]) -> String {
    let mut s = String::new();
    s.push_str("/* Auto-generated ta_func.h stub for standalone server compilation. */\n");
    s.push_str("#ifndef TA_FUNC_H\n");
    s.push_str("#define TA_FUNC_H\n\n");
    s.push_str("typedef int TA_RetCode;\n");
    s.push_str("typedef double TA_Real;\n");
    s.push_str("typedef int TA_Integer;\n");
    s.push_str("#define TA_SUCCESS 0\n");
    s.push_str("#define TA_BAD_PARAM 2\n");
    s.push_str("#define TA_OUT_OF_RANGE_START_INDEX 12\n");
    s.push_str("#define TA_OUT_OF_RANGE_END_INDEX 13\n");
    s.push_str("#define TA_ALLOC_ERR 3\n");
    s.push_str("#define TA_LIB_API\n\n");

    // Cross-language macro stubs for standalone compilation

    // Unstable period: backed by a global array, settable via JSON-RPC
    s.push_str("#define TA_FUNC_UNST_ADX 0\n");
    s.push_str("#define TA_FUNC_UNST_ADXR 1\n");
    s.push_str("#define TA_FUNC_UNST_ATR 2\n");
    s.push_str("#define TA_FUNC_UNST_CMO 3\n");
    s.push_str("#define TA_FUNC_UNST_DX 4\n");
    s.push_str("#define TA_FUNC_UNST_EMA 5\n");
    s.push_str("#define TA_FUNC_UNST_HT_DCPERIOD 6\n");
    s.push_str("#define TA_FUNC_UNST_HT_DCPHASE 7\n");
    s.push_str("#define TA_FUNC_UNST_HT_PHASOR 8\n");
    s.push_str("#define TA_FUNC_UNST_HT_SINE 9\n");
    s.push_str("#define TA_FUNC_UNST_HT_TRENDLINE 10\n");
    s.push_str("#define TA_FUNC_UNST_HT_TRENDMODE 11\n");
    s.push_str("#define TA_FUNC_UNST_IMI 12\n");
    s.push_str("#define TA_FUNC_UNST_KAMA 13\n");
    s.push_str("#define TA_FUNC_UNST_MAMA 14\n");
    s.push_str("#define TA_FUNC_UNST_MFI 15\n");
    s.push_str("#define TA_FUNC_UNST_MINUS_DI 16\n");
    s.push_str("#define TA_FUNC_UNST_MINUS_DM 17\n");
    s.push_str("#define TA_FUNC_UNST_NATR 18\n");
    s.push_str("#define TA_FUNC_UNST_PLUS_DI 19\n");
    s.push_str("#define TA_FUNC_UNST_PLUS_DM 20\n");
    s.push_str("#define TA_FUNC_UNST_RSI 21\n");
    s.push_str("#define TA_FUNC_UNST_STOCHRSI 22\n");
    s.push_str("#define TA_FUNC_UNST_T3 23\n");
    s.push_str("#define TA_FUNC_UNST_ALL 24\n");
    s.push_str("#define TA_FUNC_UNST_NONE 99\n");
    s.push_str("int ta_unstable_period[TA_FUNC_UNST_ALL];\n");
    s.push_str("#define TA_GLOBALS_UNSTABLE_PERIOD(id, name) ta_unstable_period[id]\n");
    s.push_str("void TA_SetUnstablePeriod(int id, int period) {\n");
    s.push_str("    if (id >= 0 && id < TA_FUNC_UNST_ALL) ta_unstable_period[id] = period;\n");
    s.push_str("}\n\n");

    // Compatibility mode: always default
    s.push_str("#define TA_GLOBALS_COMPATIBILITY 0\n");
    s.push_str("#define TA_COMPATIBILITY_DEFAULT 0\n");
    s.push_str("#define TA_COMPATIBILITY_METASTOCK 1\n");
    s.push_str("#define ENUM_VALUE(type, c_val, rust_val) (c_val)\n\n");

    // Epsilon comparison
    s.push_str("#define TA_IS_ZERO(v) ((-(0.00000001)) < (v) && (v) < (0.00000001))\n");
    s.push_str("#define TA_IS_ZERO_OR_NEG(v) ((v) < (0.00000001))\n\n");

    // Array operations
    s.push_str("#include <string.h>\n");
    s.push_str("#define ARRAY_MEMMOVE(dst, dstIdx, src, srcIdx, count) \\\n");
    s.push_str("    memmove(&(dst)[dstIdx], &(src)[srcIdx], (count) * sizeof(double))\n");
    s.push_str("#define ARRAY_MEMMOVEMIX(dst, dstIdx, src, srcIdx, count) \\\n");
    s.push_str("    do { for(int _i=0; _i<(count); _i++) (dst)[(dstIdx)+_i] = (double)(src)[(srcIdx)+_i]; } while(0)\n\n");

    // Enum types used by generated functions (e.g., MA dispatch)
    s.push_str("typedef int TA_MAType;\n");
    s.push_str("#define TA_MAType_SMA   0\n");
    s.push_str("#define TA_MAType_EMA   1\n");
    s.push_str("#define TA_MAType_WMA   2\n");
    s.push_str("#define TA_MAType_DEMA  3\n");
    s.push_str("#define TA_MAType_TEMA  4\n");
    s.push_str("#define TA_MAType_TRIMA 5\n");
    s.push_str("#define TA_MAType_KAMA  6\n");
    s.push_str("#define TA_MAType_MAMA  7\n");
    s.push_str("#define TA_MAType_T3    8\n");
    s.push_str("#define ENUM_CASE(type, c_val, pascal_val) (c_val)\n\n");

    // Forward declarations for all indicators — prevents "implicit declaration" errors
    // in the unity build when an early-alphabet function (e.g. ACCBANDS) calls a
    // late-alphabet internal helper (e.g. TA_INT_SMA).
    s.push_str("/* Forward declarations for all indicators */\n");
    for func in funcs {
        let upper = func.name.to_uppercase();
        let lookback_params = build_lookback_param_str(func);
        let full_params = build_full_param_str(func);
        s.push_str(&format!("extern int TA_{upper}_Lookback({lookback_params});\n"));
        s.push_str(&format!(
            "extern TA_RetCode TA_{upper}({full_params});\n"
        ));
        s.push_str(&format!(
            "extern TA_RetCode TA_{upper}_Logic({full_params});\n"
        ));
        s.push_str(&format!("#define TA_INT_{upper} TA_{upper}_Logic\n"));
    }
    s.push('\n');

    s.push_str("/* Internal helper forward declarations */\n");
    s.push_str("extern void stddev_using_precalc_ma(const double inReal[], const double inMovAvg[], int inMovAvgBegIdx, int inMovAvgNbElement, int timePeriod, double output[]);\n");
    s.push('\n');

    s.push_str("#endif /* TA_FUNC_H */\n");
    s
}

pub fn generate_c_server(funcs: &[FuncDef]) -> String {
    let mut s = String::new();

    // Header
    s.push_str("/* Auto-generated JSON-RPC server for ta_codegen C output.\n");
    s.push_str(" * Reads JSON-RPC requests from stdin, writes responses to stdout.\n");
    s.push_str(" * Build: gcc -o ta_codegen_serve_c ta_codegen_serve.c -lm -O2\n");
    s.push_str(" */\n");
    s.push_str("#include <stdio.h>\n");
    s.push_str("#include <stdlib.h>\n");
    s.push_str("#include <string.h>\n");
    s.push_str("#include <math.h>\n");
    s.push_str("#include <time.h>\n\n");

    // Include generated function implementations.
    // Order matters: functions that are called by others must come first.
    // Simple heuristic: include in sorted order, then move MA to the end
    // since it dispatches to SMA, EMA, WMA, etc.
    let mut sorted_names: Vec<&str> = funcs.iter().map(|f| f.name.as_str()).collect();
    sorted_names.sort_unstable();
    // Move MA to end if present (it calls other functions)
    if let Some(pos) = sorted_names.iter().position(|n| *n == "MA") {
        let ma = sorted_names.remove(pos);
        sorted_names.push(ma);
    }
    for name in &sorted_names {
        s.push_str(&format!("#include \"ta_{name}.c\"\n"));
    }
    s.push('\n');

    // JSON helpers
    s.push_str(&generate_c_json_helpers());

    // Dispatch function
    s.push_str(&generate_c_dispatch(funcs));

    // Main loop
    s.push_str("int main(void) {\n");
    s.push_str("    char line[262144];\n");
    s.push_str("    char response[262144];\n");
    s.push_str("    while( fgets(line, sizeof(line), stdin) ) {\n");
    s.push_str("        handle_request(line, response, sizeof(response));\n");
    s.push_str("        printf(\"%s\\n\", response);\n");
    s.push_str("        fflush(stdout);\n");
    s.push_str("    }\n");
    s.push_str("    return 0;\n");
    s.push_str("}\n");

    s
}

fn generate_c_json_helpers() -> String {
    r#"/* ---- Minimal JSON helpers ---- */

#define MAX_ARRAY_SIZE 65536

static int json_find_int(const char *json, const char *field) {
    char pattern[256];
    snprintf(pattern, sizeof(pattern), "\"%s\":", field);
    const char *p = strstr(json, pattern);
    if( !p ) return 0;
    p += strlen(pattern);
    while( *p == ' ' ) p++;
    return atoi(p);
}

static double json_find_double(const char *json, const char *field) {
    char pattern[256];
    snprintf(pattern, sizeof(pattern), "\"%s\":", field);
    const char *p = strstr(json, pattern);
    if( !p ) return 0.0;
    p += strlen(pattern);
    while( *p == ' ' ) p++;
    return strtod(p, NULL);
}

static int json_find_double_array(const char *json, const char *field,
                                   double *out, int max_count) {
    char pattern[256];
    snprintf(pattern, sizeof(pattern), "\"%s\":", field);
    const char *p = strstr(json, pattern);
    if( !p ) return 0;
    p += strlen(pattern);
    while( *p == ' ' ) p++;
    if( *p != '[' ) return 0;
    p++;
    int count = 0;
    while( *p && *p != ']' && count < max_count ) {
        while( *p == ' ' || *p == ',' ) p++;
        if( *p == ']' ) break;
        out[count] = strtod(p, (char **)&p);
        count++;
    }
    return count;
}

static const char *json_find_string(const char *json, const char *field,
                                     int *len) {
    char pattern[256];
    snprintf(pattern, sizeof(pattern), "\"%s\":\"", field);
    const char *p = strstr(json, pattern);
    if( !p ) return NULL;
    p += strlen(pattern);
    const char *start = p;
    while( *p && *p != '"' ) p++;
    *len = (int)(p - start);
    return start;
}

static int json_write_double_array(char *buf, int buf_size,
                                    const double *data, int count) {
    int pos = 0;
    buf[pos++] = '[';
    for( int i = 0; i < count; i++ ) {
        if( i > 0 ) pos += snprintf(buf + pos, buf_size - pos, ",");
        pos += snprintf(buf + pos, buf_size - pos, "%.15g", data[i]);
    }
    buf[pos++] = ']';
    buf[pos] = '\0';
    return pos;
}

static int json_write_int_array(char *buf, int buf_size,
                                 const int *data, int count) {
    int pos = 0;
    buf[pos++] = '[';
    for( int i = 0; i < count; i++ ) {
        if( i > 0 ) pos += snprintf(buf + pos, buf_size - pos, ",");
        pos += snprintf(buf + pos, buf_size - pos, "%d", data[i]);
    }
    buf[pos++] = ']';
    buf[pos] = '\0';
    return pos;
}

static long get_nanotime(void) {
    struct timespec ts;
    if( clock_gettime(CLOCK_MONOTONIC, &ts) == 0 ) {
        return (long)ts.tv_sec * 1000000000LL + (long)ts.tv_nsec;
    }
    return 0;
}

"#
    .to_string()
}

#[allow(clippy::too_many_lines)]
fn generate_c_dispatch(funcs: &[FuncDef]) -> String {
    let mut s = String::new();

    // Static buffers for input arrays — up to 5 for full OHLCV (open, high, low, close, volume)
    // plus one extra for functions like BETA that take two real arrays.
    s.push_str("static double g_inBuf0[MAX_ARRAY_SIZE];\n");
    s.push_str("static double g_inBuf1[MAX_ARRAY_SIZE];\n");
    s.push_str("static double g_inBuf2[MAX_ARRAY_SIZE];\n");
    s.push_str("static double g_inBuf3[MAX_ARRAY_SIZE];\n");
    s.push_str("static double g_inBuf4[MAX_ARRAY_SIZE];\n");
    // Real output buffers — up to 3 for MACD/BBANDS (macd, signal, hist) or STOCH (slowK, slowD)
    s.push_str("static double g_outBuf0[MAX_ARRAY_SIZE];\n");
    s.push_str("static double g_outBuf1[MAX_ARRAY_SIZE];\n");
    s.push_str("static double g_outBuf2[MAX_ARRAY_SIZE];\n");
    // Integer output buffers — for CDL* patterns (1 output) and MINMAXINDEX (2 outputs)
    s.push_str("static int g_outIntBuf0[MAX_ARRAY_SIZE];\n");
    s.push_str("static int g_outIntBuf1[MAX_ARRAY_SIZE];\n\n");

    s.push_str("static void handle_request(const char *json, char *resp, int resp_size) {\n");

    // Extract method name
    s.push_str("    int methodLen = 0;\n");
    s.push_str("    const char *method = json_find_string(json, \"method\", &methodLen);\n");
    s.push_str("    if( !method ) {\n");
    s.push_str(
        "        snprintf(resp, resp_size, \"{\\\"error\\\":\\\"Missing method field\\\"}\");\n",
    );
    s.push_str("        return;\n");
    s.push_str("    }\n\n");

    // Dispatch each function
    for (i, func) in funcs.iter().enumerate() {
        let method_name = format!("TA_{}", func.name);
        let cond = if i == 0 { "if" } else { "else if" };

        s.push_str(&format!(
            "    {} ( methodLen == {} && strncmp(method, \"{}\", {}) == 0 ) {{\n",
            cond,
            method_name.len(),
            method_name,
            method_name.len()
        ));

        // Extract common params
        s.push_str("        int startIdx = json_find_int(json, \"startIdx\");\n");
        s.push_str("        int endIdx = json_find_int(json, \"endIdx\");\n");

        // Extract input arrays — Real inputs use their own name; Price inputs expand to
        // individual component arrays (e.g. "inHigh", "inLow", "inClose").
        let input_names = expand_input_names(&func.inputs);

        for (j, name) in input_names.iter().enumerate() {
            let buf = format!("g_inBuf{j}");
            s.push_str(&format!(
                "        int n{j} = json_find_double_array(json, \"{name}\", {buf}, MAX_ARRAY_SIZE);\n",
            ));
            // Suppress unused warning
            s.push_str(&format!("        (void)n{j};\n"));
        }

        // Extract optional params
        for opt in &func.optional_inputs {
            if opt.param_type == ParamType::Real {
                s.push_str(&format!(
                    "        double {} = json_find_double(json, \"{}\");\n",
                    opt.name, opt.name
                ));
            } else {
                s.push_str(&format!(
                    "        int {} = json_find_int(json, \"{}\");\n",
                    opt.name, opt.name
                ));
            }
        }

        // Apply unstable period if provided
        if let Some(id) = func_unst_id(&func.name) {
            s.push_str(&format!(
                "        TA_SetUnstablePeriod({id}, json_find_int(json, \"unstablePeriod\"));\n"
            ));
        }

        // Declare output variables
        s.push_str("        int outBegIdx = 0, outNBElement = 0;\n");

        // Timing capture
        s.push_str("        long start_ns = get_nanotime();\n");

        // Call the function
        s.push_str(&format!("        TA_RetCode rc = TA_{}(\n", func.name));
        s.push_str("            startIdx, endIdx,\n");

        // Input arrays
        for (j, _name) in input_names.iter().enumerate() {
            s.push_str(&format!("            g_inBuf{j},\n"));
        }

        // Optional params
        for opt in &func.optional_inputs {
            s.push_str(&format!("            {},\n", opt.name));
        }

        // Output scalar params + output array params (one per output).
        // Real outputs → g_outBuf{real_idx}, integer outputs → g_outIntBuf{int_idx}.
        let outputs = &func.outputs;
        s.push_str("            &outBegIdx, &outNBElement");
        {
            let mut real_idx = 0usize;
            let mut int_idx = 0usize;
            for out in outputs {
                if out.param_type == ParamType::Integer {
                    s.push_str(&format!(", g_outIntBuf{int_idx}"));
                    int_idx += 1;
                } else {
                    s.push_str(&format!(", g_outBuf{real_idx}"));
                    real_idx += 1;
                }
            }
        }
        s.push_str(");\n");

        // Calculate elapsed time
        s.push_str("        long end_ns = get_nanotime();\n");
        s.push_str("        long elapsed_ns = end_ns - start_ns;\n");

        // Build response with correct key names and serialisers per output type.
        s.push_str("        int pos = snprintf(resp, resp_size,\n");
        s.push_str("            \"{\\\"retCode\\\":%d,\\\"outBegIdx\\\":%d,\\\"outNBElement\\\":%d,\\\"timing_ns\\\":%ld\",\n");
        s.push_str("            (int)rc, outBegIdx, outNBElement, elapsed_ns);\n");
        {
            let mut real_idx = 0usize;
            let mut int_idx = 0usize;
            for (k, out) in outputs.iter().enumerate() {
                let key = output_json_key(outputs, k);
                s.push_str(&format!(
                    "        pos += snprintf(resp + pos, resp_size - pos, \",\\\"{key}\\\":\");\n"
                ));
                if out.param_type == ParamType::Integer {
                    s.push_str(&format!(
                        "        pos += json_write_int_array(resp + pos, resp_size - pos, g_outIntBuf{int_idx}, outNBElement);\n"
                    ));
                    int_idx += 1;
                } else {
                    s.push_str(&format!(
                        "        pos += json_write_double_array(resp + pos, resp_size - pos, g_outBuf{real_idx}, outNBElement);\n"
                    ));
                    real_idx += 1;
                }
            }
        }
        s.push_str("        snprintf(resp + pos, resp_size - pos, \"}\");\n");

        s.push_str("    }\n");
    }

    // Lookback dispatch for each function
    for func in funcs {
        let method_name = format!("TA_{}_Lookback", func.name);

        s.push_str(&format!(
            "    else if ( methodLen == {} && strncmp(method, \"{}\", {}) == 0 ) {{\n",
            method_name.len(),
            method_name,
            method_name.len()
        ));

        // Extract optional params
        for opt in &func.optional_inputs {
            if opt.param_type == ParamType::Real {
                s.push_str(&format!(
                    "        double {} = json_find_double(json, \"{}\");\n",
                    opt.name, opt.name
                ));
            } else {
                s.push_str(&format!(
                    "        int {} = json_find_int(json, \"{}\");\n",
                    opt.name, opt.name
                ));
            }
        }

        // Call lookback function
        s.push_str(&format!(
            "        int lookback = TA_{}_Lookback(",
            func.name
        ));
        let opt_names: Vec<String> = func
            .optional_inputs
            .iter()
            .map(|o| o.name.clone())
            .collect();
        s.push_str(&opt_names.join(", "));
        s.push_str(");\n");

        // Build response
        s.push_str("        snprintf(resp, resp_size,\n");
        s.push_str("            \"{\\\"lookback\\\":%d}\", lookback);\n");
        s.push_str("    }\n");
    }

    // list_functions method — returns {"functions":["TA_SMA","TA_RSI",...]}
    s.push_str("    else if ( methodLen == 14 && strncmp(method, \"list_functions\", 14) == 0 ) {\n");
    s.push_str("        int pos = snprintf(resp, resp_size, \"{\\\"functions\\\":[\");\n");
    for (i, func) in funcs.iter().enumerate() {
        let comma = if i > 0 { "," } else { "" };
        s.push_str(&format!(
            "        pos += snprintf(resp + pos, resp_size - pos, \"{}\\\"TA_{}\\\"\");\n",
            comma, func.name
        ));
    }
    s.push_str("        snprintf(resp + pos, resp_size - pos, \"]}\");\n");
    s.push_str("    }\n");

    // set_unstable_period method — {"method":"set_unstable_period","params":{"id":21,"period":10}}
    s.push_str("    else if ( methodLen == 19 && strncmp(method, \"set_unstable_period\", 19) == 0 ) {\n");
    s.push_str("        int id = json_find_int(json, \"id\");\n");
    s.push_str("        int period = json_find_int(json, \"period\");\n");
    s.push_str("        TA_SetUnstablePeriod(id, period);\n");
    s.push_str("        snprintf(resp, resp_size, \"{\\\"status\\\":\\\"ok\\\"}\");\n");
    s.push_str("    }\n");

    // Unknown method
    s.push_str("    else {\n");
    s.push_str("        snprintf(resp, resp_size,\n");
    s.push_str(
        "            \"{\\\"error\\\":\\\"Unknown method: %.*s\\\"}\", methodLen, method);\n",
    );
    s.push_str("    }\n");

    s.push_str("}\n\n");
    s
}

/// Generate a Java JSON-RPC server source file.
///
/// Generates a single TaCodegenServe.java with all necessary classes inline
/// (`RetCode` enum, `MInteger`, Core class with methods, main server loop).
#[allow(clippy::too_many_lines)]
pub fn generate_java_server(funcs: &[FuncDef]) -> String {
    let mut s = String::new();

    s.push_str("/* Auto-generated JSON-RPC server for ta_codegen Java output.\n");
    s.push_str(" * Build: javac TaCodegenServe.java && java TaCodegenServe\n");
    s.push_str(" */\n");
    s.push_str("import java.io.*;\n");
    s.push_str("import java.util.*;\n\n");

    // RetCode enum
    s.push_str("enum RetCode {\n");
    s.push_str("    Success, BadParam, OutOfRangeStartIndex, OutOfRangeEndIndex, AllocErr, InternalError;\n");
    s.push_str("    public int toInt() {\n");
    s.push_str("        switch(this) {\n");
    s.push_str("            case Success: return 0;\n");
    s.push_str("            case BadParam: return 2;\n");
    s.push_str("            case OutOfRangeStartIndex: return 12;\n");
    s.push_str("            case OutOfRangeEndIndex: return 13;\n");
    s.push_str("            case AllocErr: return 3;\n");
    s.push_str("            default: return 5000;\n");
    s.push_str("        }\n");
    s.push_str("    }\n");
    s.push_str("}\n\n");

    // MInteger helper
    s.push_str("class MInteger { public int value; }\n\n");

    // FuncUnstId and Compatibility enums (referenced by generated Core methods)
    s.push_str("enum FuncUnstId {\n");
    s.push_str("    Adx, Adxr, Atr, Cmo, Dx, Ema,\n");
    s.push_str("    HtDcPeriod, HtDcPhase, HtPhasor, HtSine, HtTrendline, HtTrendMode,\n");
    s.push_str("    Imi, Kama, Mama, Mfi, MinusDI, MinusDM,\n");
    s.push_str("    Natr, PlusDI, PlusDM, Rsi, StochRsi, T3, None;\n");
    s.push_str("}\n\n");

    s.push_str("enum Compatibility {\n");
    s.push_str("    Default, Metastock;\n");
    s.push_str("}\n\n");

    // Core class — method bodies are inlined by the caller via inline_java_core_methods()
    s.push_str("class Core {\n");
    s.push_str("    int lookbackTotal, i, outIdx, trailingIdx;\n");
    s.push_str("    int[] unstablePeriod = new int[FuncUnstId.values().length];\n");
    s.push_str("    Compatibility compatibility = Compatibility.Default;\n");
    s.push_str("    int nbElement;\n\n");
    for func in funcs {
        s.push_str(&format!("    // @@CORE_{}@@\n", func.name));
    }
    s.push_str("}\n\n");

    // Main server class
    s.push_str("public class TaCodegenServe {\n");
    s.push_str("    static Core core = new Core();\n\n");

    // JSON helpers
    s.push_str("    static int jsonInt(String json, String field) {\n");
    s.push_str("        int idx = json.indexOf('\"' + field + '\"');\n");
    s.push_str("        if (idx < 0) return 0;\n");
    s.push_str("        idx = json.indexOf(':', idx) + 1;\n");
    s.push_str("        while (idx < json.length() && json.charAt(idx) == ' ') idx++;\n");
    s.push_str("        int end = idx;\n");
    s.push_str("        while (end < json.length() && \"0123456789-\".indexOf(json.charAt(end)) >= 0) end++;\n");
    s.push_str("        return Integer.parseInt(json.substring(idx, end));\n");
    s.push_str("    }\n\n");

    s.push_str("    static double jsonDouble(String json, String field) {\n");
    s.push_str("        int idx = json.indexOf('\"' + field + '\"');\n");
    s.push_str("        if (idx < 0) return 0.0;\n");
    s.push_str("        idx = json.indexOf(':', idx) + 1;\n");
    s.push_str("        while (idx < json.length() && json.charAt(idx) == ' ') idx++;\n");
    s.push_str("        int end = idx;\n");
    s.push_str("        while (end < json.length() && \"0123456789-.eE+\".indexOf(json.charAt(end)) >= 0) end++;\n");
    s.push_str("        return Double.parseDouble(json.substring(idx, end));\n");
    s.push_str("    }\n\n");

    s.push_str("    static double[] jsonDoubleArray(String json, String field) {\n");
    s.push_str("        int idx = json.indexOf('\"' + field + '\"');\n");
    s.push_str("        if (idx < 0) return new double[0];\n");
    s.push_str("        idx = json.indexOf('[', idx);\n");
    s.push_str("        int end = json.indexOf(']', idx);\n");
    s.push_str("        String inner = json.substring(idx + 1, end).trim();\n");
    s.push_str("        if (inner.isEmpty()) return new double[0];\n");
    s.push_str("        String[] parts = inner.split(\",\");\n");
    s.push_str("        double[] result = new double[parts.length];\n");
    s.push_str("        for (int i = 0; i < parts.length; i++)\n");
    s.push_str("            result[i] = Double.parseDouble(parts[i].trim());\n");
    s.push_str("        return result;\n");
    s.push_str("    }\n\n");

    s.push_str("    static String doubleArrayToJson(double[] arr, int count) {\n");
    s.push_str("        StringBuilder sb = new StringBuilder(\"[\");\n");
    s.push_str("        for (int i = 0; i < count; i++) {\n");
    s.push_str("            if (i > 0) sb.append(',');\n");
    s.push_str("            sb.append(arr[i]);\n");
    s.push_str("        }\n");
    s.push_str("        sb.append(']');\n");
    s.push_str("        return sb.toString();\n");
    s.push_str("    }\n\n");

    s.push_str("    static String intArrayToJson(int[] arr, int count) {\n");
    s.push_str("        StringBuilder sb = new StringBuilder(\"[\");\n");
    s.push_str("        for (int i = 0; i < count; i++) {\n");
    s.push_str("            if (i > 0) sb.append(',');\n");
    s.push_str("            sb.append(arr[i]);\n");
    s.push_str("        }\n");
    s.push_str("        sb.append(']');\n");
    s.push_str("        return sb.toString();\n");
    s.push_str("    }\n\n");

    // Dispatch method
    s.push_str("    static String handleRequest(String json) {\n");

    for (i, func) in funcs.iter().enumerate() {
        let method_name = format!("TA_{}", func.name);
        let cond = if i == 0 { "if" } else { "else if" };
        let func_lower = func.name.to_lowercase();

        s.push_str(&format!(
            "        {cond} (json.contains(\"\\\"{method_name}\\\"\")) {{\n"
        ));
        s.push_str("            int startIdx = jsonInt(json, \"startIdx\");\n");
        s.push_str("            int endIdx = jsonInt(json, \"endIdx\");\n");

        // Inputs — Real inputs use their own name; Price inputs expand to individual
        // component arrays (e.g. "inHigh", "inLow", "inClose").
        let input_names = expand_input_names(&func.inputs);

        for name in &input_names {
            s.push_str(&format!(
                "            double[] {name} = jsonDoubleArray(json, \"{name}\");\n"
            ));
        }

        // Optional params
        for opt in &func.optional_inputs {
            if opt.param_type == ParamType::Real {
                s.push_str(&format!(
                    "            double {} = jsonDouble(json, \"{}\");\n",
                    opt.name, opt.name
                ));
            } else {
                s.push_str(&format!(
                    "            int {} = jsonInt(json, \"{}\");\n",
                    opt.name, opt.name
                ));
            }
        }

        // Apply unstable period if provided
        if let Some(id) = func_unst_id(&func.name) {
            s.push_str(&format!(
                "            core.unstablePeriod[{id}] = jsonInt(json, \"unstablePeriod\");\n"
            ));
        }

        // Outputs — one array per output, typed correctly (double[] or int[])
        let outputs = &func.outputs;
        for (k, out) in outputs.iter().enumerate() {
            let arr_name = format!("outArr{k}");
            if out.param_type == ParamType::Integer {
                s.push_str(&format!(
                    "            int[] {arr_name} = new int[endIdx - startIdx + 1];\n"
                ));
            } else {
                s.push_str(&format!(
                    "            double[] {arr_name} = new double[endIdx - startIdx + 1];\n"
                ));
            }
        }
        s.push_str("            MInteger outBegIdx = new MInteger();\n");
        s.push_str("            MInteger outNBElement = new MInteger();\n");

        // Timing capture
        s.push_str("            long startNs = System.nanoTime();\n");

        // Call
        s.push_str(&format!("            RetCode rc = core.{func_lower}(\n"));
        s.push_str("                startIdx, endIdx,\n");
        for name in &input_names {
            s.push_str(&format!("                {name},\n"));
        }
        for opt in &func.optional_inputs {
            s.push_str(&format!("                {},\n", opt.name));
        }
        s.push_str("                outBegIdx, outNBElement");
        for k in 0..outputs.len() {
            s.push_str(&format!(", outArr{k}"));
        }
        s.push_str(");\n");

        // Timing capture
        s.push_str("            long endNs = System.nanoTime();\n");
        s.push_str("            long elapsedNs = endNs - startNs;\n");

        // Response — use correct key names and serialisers per output type
        s.push_str("            StringBuilder sb = new StringBuilder();\n");
        s.push_str("            sb.append(\"{\\\"retCode\\\":\").append(rc.toInt());\n");
        s.push_str(
            "            sb.append(\",\\\"outBegIdx\\\":\").append(outBegIdx.value);\n",
        );
        s.push_str(
            "            sb.append(\",\\\"outNBElement\\\":\").append(outNBElement.value);\n",
        );
        for (k, out) in outputs.iter().enumerate() {
            let arr_name = format!("outArr{k}");
            let key = output_json_key(outputs, k);
            if out.param_type == ParamType::Integer {
                s.push_str(&format!(
                    "            sb.append(\",\\\"{key}\\\":\").append(intArrayToJson({arr_name}, outNBElement.value));\n"
                ));
            } else {
                s.push_str(&format!(
                    "            sb.append(\",\\\"{key}\\\":\").append(doubleArrayToJson({arr_name}, outNBElement.value));\n"
                ));
            }
        }
        s.push_str("            sb.append(\",\\\"timing_ns\\\":\").append(elapsedNs);\n");
        s.push_str("            sb.append(\"}\");\n");
        s.push_str("            return sb.toString();\n");

        s.push_str("        }\n");
    }

    // list_functions method — returns {"functions":["TA_SMA","TA_RSI",...]}
    s.push_str("        else if (json.contains(\"\\\"list_functions\\\"\")) {\n");
    s.push_str("            StringBuilder sb = new StringBuilder(\"{\\\"functions\\\":[\");\n");
    for (i, func) in funcs.iter().enumerate() {
        if i > 0 {
            s.push_str("            sb.append(\",\");\n");
        }
        s.push_str(&format!("            sb.append(\"\\\"TA_{}\\\"\");\n", func.name));
    }
    s.push_str("            sb.append(\"]}\");\n");
    s.push_str("            return sb.toString();\n");
    s.push_str("        }\n");

    // set_unstable_period method — {"method":"set_unstable_period","params":{"id":21,"period":10}}
    s.push_str("        else if (json.contains(\"\\\"set_unstable_period\\\"\")) {\n");
    s.push_str("            int id = jsonInt(json, \"id\");\n");
    s.push_str("            int period = jsonInt(json, \"period\");\n");
    s.push_str("            if (id >= 0 && id < core.unstablePeriod.length) {\n");
    s.push_str("                core.unstablePeriod[id] = period;\n");
    s.push_str("                return \"{\\\"status\\\":\\\"ok\\\"}\"; \n");
    s.push_str("            }\n");
    s.push_str("            return \"{\\\"error\\\":\\\"Invalid id\\\"}\"; \n");
    s.push_str("        }\n");

    s.push_str("        else {\n");
    s.push_str("            return \"{\\\"error\\\":\\\"Unknown method\\\"}\";\n");
    s.push_str("        }\n");
    s.push_str("    }\n\n");

    // Main method
    s.push_str("    public static void main(String[] args) throws Exception {\n");
    s.push_str(
        "        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));\n",
    );
    s.push_str("        String line;\n");
    s.push_str("        while ((line = reader.readLine()) != null) {\n");
    s.push_str("            if (line.trim().isEmpty()) continue;\n");
    s.push_str("            System.out.println(handleRequest(line));\n");
    s.push_str("            System.out.flush();\n");
    s.push_str("        }\n");
    s.push_str("    }\n");
    s.push_str("}\n");

    s
}

/// Generate a .NET (C#) JSON-RPC server source file.
///
/// Note: The .NET backend currently generates C++/CLI headers, not full C# implementations.
/// This generates a placeholder that will work once the backend is extended.
#[allow(clippy::too_many_lines)]
pub fn generate_dotnet_server(funcs: &[FuncDef]) -> String {
    let mut s = String::new();

    s.push_str("// Auto-generated JSON-RPC server for ta_codegen .NET output.\n");
    s.push_str("// Uses P/Invoke to call the generated C shared library.\n");
    s.push_str("// Requires: dotnet 8.0+, libta_codegen_funcs.dylib/.so in bin/\n");
    s.push_str("using System;\n");
    s.push_str("using System.IO;\n");
    s.push_str("using System.Text.Json;\n");
    s.push_str("using System.Runtime.InteropServices;\n");
    s.push_str("using System.Diagnostics;\n\n");

    s.push_str("public class TaCodegenServe {\n\n");

    // P/Invoke for unstable period setter
    s.push_str("    [DllImport(\"ta_codegen_funcs\", EntryPoint = \"TA_SetUnstablePeriod\")]\n");
    s.push_str("    static extern void TA_SetUnstablePeriod(int id, int period);\n\n");

    // P/Invoke declarations
    for func in funcs {
        let func_upper = &func.name;

        // Expand Price inputs into individual component arrays.
        let input_names = expand_input_names(&func.inputs);

        s.push_str(&format!(
            "    [DllImport(\"ta_codegen_funcs\", EntryPoint = \"TA_{func_upper}\")]\n"
        ));
        s.push_str(&format!("    static extern int TA_{func_upper}(\n"));
        s.push_str("        int startIdx, int endIdx,\n");

        for name in &input_names {
            s.push_str(&format!("        double[] {name},\n"));
        }

        for opt in &func.optional_inputs {
            let cs_type = if opt.param_type == ParamType::Real {
                "double"
            } else {
                "int"
            };
            s.push_str(&format!("        {cs_type} {},\n", opt.name));
        }

        s.push_str("        out int outBegIdx, out int outNBElement");
        for (k, out) in func.outputs.iter().enumerate() {
            let arr_name = format!("outArr{k}");
            let cs_arr_type = if out.param_type == ParamType::Integer { "int[]" } else { "double[]" };
            s.push_str(&format!(",\n        {cs_arr_type} {arr_name}"));
        }
        s.push_str(");\n\n");
    }

    // Dispatch method
    s.push_str("    static string HandleRequest(string json) {\n");
    s.push_str("        try {\n");
    s.push_str("            using var doc = JsonDocument.Parse(json);\n");
    s.push_str("            var root = doc.RootElement;\n");
    s.push_str("            string method = root.GetProperty(\"method\").GetString()!;\n");
    s.push_str("            var p = root.GetProperty(\"params\");\n");
    s.push_str("            int startIdx = p.GetProperty(\"startIdx\").GetInt32();\n");
    s.push_str("            int endIdx = p.GetProperty(\"endIdx\").GetInt32();\n");
    s.push_str("            int n = endIdx - startIdx + 1;\n\n");

    for (i, func) in funcs.iter().enumerate() {
        let method_name = format!("TA_{}", func.name);
        let cond = if i == 0 { "if" } else { "else if" };

        // Expand Price inputs into individual component arrays.
        let input_names = expand_input_names(&func.inputs);

        s.push_str(&format!(
            "            {cond} (method == \"{method_name}\") {{\n"
        ));

        // Extract input arrays — Real inputs use their own name; Price inputs expand
        // to individual component arrays (e.g. "inHigh", "inLow", "inClose").
        for name in &input_names {
            s.push_str(&format!(
                "                double[] {name} = GetDoubleArray(p, \"{name}\");\n"
            ));
        }

        // Extract optional params
        for opt in &func.optional_inputs {
            if opt.param_type == ParamType::Real {
                let default = opt.default.unwrap_or(0.0);
                s.push_str(&format!(
                    "                double {} = p.TryGetProperty(\"{}\", out var _{0}Val) ? _{0}Val.GetDouble() : {};\n",
                    opt.name, opt.name, default
                ));
            } else {
                #[allow(clippy::cast_possible_truncation)]
                let default = opt.default.unwrap_or(0.0) as i64;
                s.push_str(&format!(
                    "                int {} = p.TryGetProperty(\"{}\", out var _{0}Val) ? _{0}Val.GetInt32() : {};\n",
                    opt.name, opt.name, default
                ));
            }
        }

        // Apply unstable period if provided
        if let Some(id) = func_unst_id(&func.name) {
            s.push_str("                int unstablePeriod = p.TryGetProperty(\"unstablePeriod\", out var _upVal) ? _upVal.GetInt32() : 0;\n");
            s.push_str(&format!(
                "                TA_SetUnstablePeriod({id}, unstablePeriod);\n"
            ));
        }

        // Allocate output arrays — typed correctly (double[] or int[]) per output
        let outputs = &func.outputs;
        for (k, out) in outputs.iter().enumerate() {
            let arr_name = format!("outArr{k}");
            if out.param_type == ParamType::Integer {
                s.push_str(&format!(
                    "                int[] {arr_name} = new int[n];\n"
                ));
            } else {
                s.push_str(&format!(
                    "                double[] {arr_name} = new double[n];\n"
                ));
            }
        }

        // Time the function call
        s.push_str("                var timer = Stopwatch.StartNew();\n");

        // Call
        s.push_str(&format!(
            "                int rc = TA_{}(startIdx, endIdx, ",
            func.name
        ));
        for name in &input_names {
            s.push_str(&format!("{name}, "));
        }
        for opt in &func.optional_inputs {
            s.push_str(&format!("{}, ", opt.name));
        }
        s.push_str("out int outBegIdx, out int outNBElement");
        for k in 0..outputs.len() {
            s.push_str(&format!(", outArr{k}"));
        }
        s.push_str(");\n");
        s.push_str("                timer.Stop();\n");
        s.push_str("                long elapsedNs = timer.ElapsedTicks * 1000000000 / Stopwatch.Frequency;\n");

        // Build response — correct key names and serialisers per output type
        s.push_str("                var sb = new System.Text.StringBuilder();\n");
        s.push_str("                sb.Append($\"{{\\\"retCode\\\":{rc},\\\"outBegIdx\\\":{outBegIdx},\\\"outNBElement\\\":{outNBElement}\");\n");
        for (k, out) in outputs.iter().enumerate() {
            let arr_name = format!("outArr{k}");
            let key = output_json_key(outputs, k);
            if out.param_type == ParamType::Integer {
                s.push_str(&format!(
                    "                sb.Append($\",\\\"{key}\\\":\"); sb.Append(FormatIntArray({arr_name}, outNBElement));\n"
                ));
            } else {
                s.push_str(&format!(
                    "                sb.Append($\",\\\"{key}\\\":\"); sb.Append(FormatArray({arr_name}, outNBElement));\n"
                ));
            }
        }
        s.push_str("                sb.Append($\",\\\"timing_ns\\\":{elapsedNs}\");\n");
        s.push_str("                sb.Append(\"}\");\n");
        s.push_str("                return sb.ToString();\n");
        s.push_str("            }\n");
    }

    // list_functions method — returns {"functions":["TA_SMA","TA_RSI",...]}
    s.push_str("            else if (method == \"list_functions\") {\n");
    s.push_str("                var sb = new System.Text.StringBuilder(\"{\\\"functions\\\":[\");\n");
    for (i, func) in funcs.iter().enumerate() {
        if i > 0 {
            s.push_str("                sb.Append(\",\");\n");
        }
        s.push_str(&format!(
            "                sb.Append(\"\\\"TA_{}\\\"\");\n",
            func.name
        ));
    }
    s.push_str("                sb.Append(\"]}\");\n");
    s.push_str("                return sb.ToString();\n");
    s.push_str("            }\n");

    // set_unstable_period method — {"method":"set_unstable_period","params":{"id":21,"period":10}}
    s.push_str("            else if (method == \"set_unstable_period\") {\n");
    s.push_str("                int id = p.GetProperty(\"id\").GetInt32();\n");
    s.push_str("                int period = p.GetProperty(\"period\").GetInt32();\n");
    s.push_str("                TA_SetUnstablePeriod(id, period);\n");
    s.push_str("                return \"{\\\"status\\\":\\\"ok\\\"}\";\n");
    s.push_str("            }\n");

    s.push_str("            else {\n");
    s.push_str("                return $\"{{\\\"error\\\":\\\"Unknown method: {method}\\\"}}\";\n");
    s.push_str("            }\n");
    s.push_str("        } catch (Exception ex) {\n");
    s.push_str("            return $\"{{\\\"error\\\":\\\"{ex.Message.Replace(\"\\\"\", \"'\")}\\\"}}\";\n");
    s.push_str("        }\n");
    s.push_str("    }\n\n");

    // Helper: extract double array from JSON
    s.push_str("    static double[] GetDoubleArray(JsonElement p, string name) {\n");
    s.push_str("        var arr = p.GetProperty(name);\n");
    s.push_str("        double[] result = new double[arr.GetArrayLength()];\n");
    s.push_str("        for (int i = 0; i < result.Length; i++)\n");
    s.push_str("            result[i] = arr[i].GetDouble();\n");
    s.push_str("        return result;\n");
    s.push_str("    }\n\n");

    // Helper: format a double array as a JSON array string
    s.push_str("    static string FormatArray(double[] arr, int count) {\n");
    s.push_str("        var parts = new string[count];\n");
    s.push_str("        for (int i = 0; i < count; i++)\n");
    s.push_str("            parts[i] = arr[i].ToString(\"G15\");\n");
    s.push_str("        return \"[\" + string.Join(\",\", parts) + \"]\";\n");
    s.push_str("    }\n\n");

    // Helper: format an int array as a JSON array string
    s.push_str("    static string FormatIntArray(int[] arr, int count) {\n");
    s.push_str("        var parts = new string[count];\n");
    s.push_str("        for (int i = 0; i < count; i++)\n");
    s.push_str("            parts[i] = arr[i].ToString();\n");
    s.push_str("        return \"[\" + string.Join(\",\", parts) + \"]\";\n");
    s.push_str("    }\n\n");

    // Main
    s.push_str("    static void Main(string[] args) {\n");
    s.push_str("        string? line;\n");
    s.push_str("        while ((line = Console.ReadLine()) != null) {\n");
    s.push_str("            if (string.IsNullOrWhiteSpace(line)) continue;\n");
    s.push_str("            Console.WriteLine(HandleRequest(line));\n");
    s.push_str("            Console.Out.Flush();\n");
    s.push_str("        }\n");
    s.push_str("    }\n");
    s.push_str("}\n");

    s
}

/// Generate a SWIG interface file (.i) that includes Python 3 typemaps
/// and function declarations from the generated .swg files.
/// This is compiled with `swig -python` + gcc to produce `_ta_lib.so`.
pub fn generate_swig_interface(funcs: &[FuncDef]) -> String {
    let mut s = String::new();

    s.push_str("%module ta_lib\n\n");

    // Inline C header block — type definitions needed by the SWIG wrapper.
    // We do NOT #include "ta_func.h" here because it would define TA_SetUnstablePeriod
    // again (already defined in the unity source compiled alongside this wrapper).
    s.push_str("%{\n");
    s.push_str("typedef int TA_RetCode;\n");
    s.push_str("typedef double TA_Real;\n");
    s.push_str("typedef int TA_Integer;\n");
    s.push_str("#define TA_SUCCESS 0\n");
    s.push_str("#define TA_INTEGER_DEFAULT (-2147483648)\n");
    s.push_str("#define TA_REAL_DEFAULT (-4e+37)\n");
    // Unstable period setter (defined in unity source via ta_func.h)
    s.push_str("extern void TA_SetUnstablePeriod(int id, int period);\n");
    // Forward-declare all TA functions so the wrapper can call them
    for func in funcs {
        // Expand Price inputs into individual component arrays for the C signature.
        let input_names = expand_input_names(&func.inputs);

        s.push_str(&format!("extern TA_RetCode TA_{}(int, int", func.name));
        for _ in &input_names {
            s.push_str(", const double*");
        }
        for opt in &func.optional_inputs {
            if opt.param_type == ParamType::Real {
                s.push_str(", double");
            } else {
                s.push_str(", int");
            }
        }
        s.push_str(", int*, int*");
        for out in &func.outputs {
            if out.param_type == ParamType::Integer {
                s.push_str(", int*");
            } else {
                s.push_str(", double*");
            }
        }
        s.push_str(");\n");

        // Lookback
        s.push_str(&format!("extern int TA_{}_Lookback(", func.name));
        let opt_params: Vec<String> = func
            .optional_inputs
            .iter()
            .map(|opt| {
                if opt.param_type == ParamType::Real {
                    "double".to_string()
                } else {
                    "int".to_string()
                }
            })
            .collect();
        s.push_str(&opt_params.join(", "));
        if opt_params.is_empty() {
            s.push_str("void");
        }
        s.push_str(");\n");
    }
    s.push_str("%}\n\n");

    // Constants and functions visible to Python
    s.push_str("#define TA_SUCCESS 0\n");
    s.push_str("#define TA_FUNC_UNST_ADX 0\n");
    s.push_str("#define TA_FUNC_UNST_ADXR 1\n");
    s.push_str("#define TA_FUNC_UNST_ATR 2\n");
    s.push_str("#define TA_FUNC_UNST_CMO 3\n");
    s.push_str("#define TA_FUNC_UNST_DX 4\n");
    s.push_str("#define TA_FUNC_UNST_EMA 5\n");
    s.push_str("#define TA_FUNC_UNST_HT_DCPERIOD 6\n");
    s.push_str("#define TA_FUNC_UNST_HT_DCPHASE 7\n");
    s.push_str("#define TA_FUNC_UNST_HT_PHASOR 8\n");
    s.push_str("#define TA_FUNC_UNST_HT_SINE 9\n");
    s.push_str("#define TA_FUNC_UNST_HT_TRENDLINE 10\n");
    s.push_str("#define TA_FUNC_UNST_HT_TRENDMODE 11\n");
    s.push_str("#define TA_FUNC_UNST_IMI 12\n");
    s.push_str("#define TA_FUNC_UNST_KAMA 13\n");
    s.push_str("#define TA_FUNC_UNST_MAMA 14\n");
    s.push_str("#define TA_FUNC_UNST_MFI 15\n");
    s.push_str("#define TA_FUNC_UNST_MINUS_DI 16\n");
    s.push_str("#define TA_FUNC_UNST_MINUS_DM 17\n");
    s.push_str("#define TA_FUNC_UNST_NATR 18\n");
    s.push_str("#define TA_FUNC_UNST_PLUS_DI 19\n");
    s.push_str("#define TA_FUNC_UNST_PLUS_DM 20\n");
    s.push_str("#define TA_FUNC_UNST_RSI 21\n");
    s.push_str("#define TA_FUNC_UNST_STOCHRSI 22\n");
    s.push_str("#define TA_FUNC_UNST_T3 23\n");
    s.push_str("extern void TA_SetUnstablePeriod(int id, int period);\n\n");

    // ---- Python 3 typemaps (adapted from ta_libc.python.swg) ----
    s.push_str(&generate_swig_python3_typemaps());

    // ---- Function declarations from generated .swg files ----
    // These use the special parameter names (START_IDX, IN_ARRAY, etc.)
    // that the typemaps above match on.
    for func in funcs {
        s.push_str(&format!("\n/* TA_{} */\n", func.name));

        // Include the generated .swg file
        s.push_str(&format!("%include \"ta_{}.swg\"\n", func.name));
    }

    s
}

#[allow(clippy::too_many_lines)]
fn generate_swig_python3_typemaps() -> String {
    // Python 3 typemaps for SWIG, adapted from the existing ta_libc.python.swg
    r#"/* ---- Python 3 typemaps for TA-Lib functions ---- */

%{
static int convert_darray(PyObject *input, double *ptr, int size) {
    int i, len;
    if (!PySequence_Check(input)) {
        PyErr_SetString(PyExc_TypeError, "Expecting a sequence");
        return 0;
    }
    len = (int)PyObject_Length(input);
    if (len > size) len = size;
    for (i = 0; i < len; i++) {
        PyObject *o = PySequence_GetItem(input, i);
        if (PyFloat_Check(o)) {
            ptr[i] = PyFloat_AsDouble(o);
        } else if (PyLong_Check(o)) {
            ptr[i] = (double)PyLong_AsLong(o);
        } else {
            PyErr_SetString(PyExc_ValueError, "Expecting a sequence of numbers");
            Py_DECREF(o);
            return 0;
        }
        Py_DECREF(o);
    }
    return 1;
}
%}

/* TA_RetCode: return None on success, raise exception on failure */
%typemap(out) TA_RetCode {
    if ($1 != TA_SUCCESS) {
        char text[200];
        snprintf(text, sizeof(text)-1, "TA function failed with code %d", $1);
        PyErr_SetString(PyExc_RuntimeError, text);
        SWIG_fail;
    }
    Py_INCREF(Py_None);
    $result = Py_None;
}

/* START_IDX and END_IDX */
%typemap(in) int START_IDX (int startIdx) {
    $1 = (int)PyLong_AsLong($input);
    if ($1 < 0) $1 = 0;
    startIdx = $1;
}

%typemap(in) int END_IDX (int endIdx) {
    $1 = (int)PyLong_AsLong($input);
    if ($1 < startIdx1) $1 = startIdx1;
    endIdx = $1;
}

/* Input arrays */
%typemap(in) const double *IN_ARRAY {
    int array_size = endIdx2 + 1;
    $1 = ($1_ltype) calloc(array_size, sizeof($*1_ltype));
    if (!convert_darray($input, $1, array_size)) goto fail;
}

%typemap(freearg) const double *IN_ARRAY
    "free($1);";

/* Optional integer params */
%typemap(default) int OPT_INT
    "$1 = TA_INTEGER_DEFAULT;"

%typemap(in) int OPT_INT {
    if (PyLong_Check($input)) {
        $1 = ($1_ltype)PyLong_AsLong($input);
    }
}

/* outBegIdx */
%typemap(in,numinputs=0) int *BEG_IDX(int temp = 0)
    "$1 = &temp;";

%typemap(argout) int *BEG_IDX {
    if (result == TA_SUCCESS) {
        PyObject *o = PyLong_FromLong((long)(*$1));
        $result = SWIG_Python_AppendOutput($result, o, 0);
    }
}

/* outNBElement */
%typemap(arginit) int *OUT_SIZE
    "int outNbElement = 0;";

%typemap(in,numinputs=0) int *OUT_SIZE
    "$1 = &outNbElement;";

/* Output arrays */
%typemap(in,numinputs=0) double *OUT_ARRAY, int *OUT_ARRAY
    "/* $1 ignored on input */";

%typemap(check) double *OUT_ARRAY, int *OUT_ARRAY {
    int array_size = endIdx2 - startIdx1 + 1;
    $1 = ($1_ltype) calloc(array_size, sizeof($*1_ltype));
}

%typemap(argout) double *OUT_ARRAY {
    if (result == TA_SUCCESS) {
        int idx;
        PyObject *list = PyList_New(outNbElement);
        for (idx = 0; idx < outNbElement; idx++) {
            PyObject *o = PyFloat_FromDouble($1[idx]);
            PyList_SET_ITEM(list, idx, o);
        }
        $result = SWIG_Python_AppendOutput($result, list, 0);
    }
}

%typemap(argout) int *OUT_ARRAY {
    if (result == TA_SUCCESS) {
        int idx;
        PyObject *list = PyList_New(outNbElement);
        for (idx = 0; idx < outNbElement; idx++) {
            PyObject *o = PyLong_FromLong($1[idx]);
            PyList_SET_ITEM(list, idx, o);
        }
        $result = SWIG_Python_AppendOutput($result, list, 0);
    }
}

%typemap(freearg) double *OUT_ARRAY, int *OUT_ARRAY
    "free($1);";

"#
    .to_string()
}

/// Generate a Python JSON-RPC server script that uses the SWIG-generated
/// `ta_lib` module to call TA functions.
#[allow(clippy::too_many_lines)]
pub fn generate_swig_server(funcs: &[FuncDef]) -> String {
    let mut s = String::new();

    s.push_str("#!/usr/bin/env python3\n");
    s.push_str("\"\"\"Auto-generated JSON-RPC server for ta_codegen SWIG/Python output.\n");
    s.push_str("Uses the SWIG-generated ta_lib module to call TA functions.\n");
    s.push_str("\"\"\"\n");
    s.push_str("import sys\n");
    s.push_str("import os\n");
    s.push_str("import json\n");
    s.push_str("import time\n\n");

    // Add script directory to Python path so ta_lib module is found
    s.push_str("# Add script directory to path for SWIG module import\n");
    s.push_str("sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))\n");
    s.push_str("import ta_lib\n\n");

    // Dispatch
    s.push_str("def handle_request(req):\n");
    s.push_str("    method = req.get('method', '')\n");
    s.push_str("    params = req.get('params', {})\n\n");

    for func in funcs {
        let method_name = format!("TA_{}", func.name);
        let func_lower = func.name.to_lowercase();

        s.push_str(&format!("    if method == '{method_name}':\n"));
        s.push_str(&format!("        return handle_{func_lower}(params)\n"));
    }

    s.push_str("    if method == 'list_functions':\n");
    s.push_str("        return handle_list_functions()\n");
    s.push_str("    if method == 'set_unstable_period':\n");
    s.push_str("        return handle_set_unstable_period(params)\n");
    s.push_str("    return {'error': f'Unknown method: {method}'}\n\n");

    // Per-function handlers
    for func in funcs {
        let func_lower = func.name.to_lowercase();
        let func_upper = &func.name;

        s.push_str(&format!("def handle_{func_lower}(params):\n"));
        s.push_str("    start_idx = params.get('startIdx', 0)\n");
        s.push_str("    end_idx = params.get('endIdx', 0)\n");

        // Input arrays — Real inputs use their own name; Price inputs expand to individual
        // component arrays (e.g. "inHigh", "inLow", "inClose").
        let input_names = expand_input_names(&func.inputs);

        for name in &input_names {
            s.push_str(&format!(
                "    {name} = [float(x) for x in params.get('{name}', [])]\n"
            ));
        }

        // Optional params
        for opt in &func.optional_inputs {
            if opt.param_type == ParamType::Real {
                let default = opt.default.unwrap_or(0.0);
                s.push_str(&format!(
                    "    {} = float(params.get('{}', {}))\n",
                    opt.name, opt.name, default
                ));
            } else {
                #[allow(clippy::cast_possible_truncation)]
                let default = opt.default.unwrap_or(0.0) as i64;
                s.push_str(&format!(
                    "    {} = int(params.get('{}', {}))\n",
                    opt.name, opt.name, default
                ));
            }
        }

        // Apply unstable period if provided
        if let Some(id) = func_unst_id(&func.name) {
            s.push_str(&format!(
                "    ta_lib.TA_SetUnstablePeriod({id}, params.get('unstablePeriod', 0))\n"
            ));
        }

        // Call via SWIG module with timing.
        // SWIG returns a tuple: (None, outBegIdx, outArray0, outArray1, ...)
        // result[0] is None (retCode mapped away), [1] is outBegIdx, [2..] are output arrays.
        let outputs = &func.outputs;
        s.push_str("    try:\n");
        s.push_str("        start_ns = time.perf_counter_ns()\n");
        s.push_str(&format!("        result = ta_lib.TA_{func_upper}(\n"));
        s.push_str("            start_idx, end_idx,\n");
        for name in &input_names {
            s.push_str(&format!("            {name},\n"));
        }
        for opt in &func.optional_inputs {
            s.push_str(&format!("            {},\n", opt.name));
        }
        s.push_str("        )\n");
        s.push_str("        end_ns = time.perf_counter_ns()\n");
        s.push_str("        elapsed_ns = end_ns - start_ns\n");
        s.push_str("        out_beg = result[1]\n");
        for (k, _out) in outputs.iter().enumerate() {
            let arr_name = format!("out_arr{k}");
            s.push_str(&format!(
                "        {arr_name} = list(result[{}])\n",
                k + 2
            ));
        }
        s.push_str("        resp = {\n");
        s.push_str("            'retCode': 0,\n");
        s.push_str("            'outBegIdx': out_beg,\n");
        // outNBElement comes from first output's length
        let first_arr = if outputs.is_empty() {
            "[]".to_string()
        } else {
            "out_arr0".to_string()
        };
        s.push_str(&format!(
            "            'outNBElement': len({first_arr}),\n"
        ));
        for (k, _out) in outputs.iter().enumerate() {
            let arr_name = format!("out_arr{k}");
            let key = output_json_key(outputs, k);
            s.push_str(&format!("            '{key}': {arr_name},\n"));
        }
        s.push_str("            'timing_ns': elapsed_ns,\n");
        s.push_str("        }\n");
        s.push_str("        return resp\n");
        s.push_str("    except RuntimeError as e:\n");
        s.push_str("        return {'error': str(e)}\n\n");
    }

    // list_functions dispatch
    s.push_str("def handle_list_functions():\n");
    s.push_str("    functions = [\n");
    for func in funcs {
        s.push_str(&format!("        'TA_{}',\n", func.name));
    }
    s.push_str("    ]\n");
    s.push_str("    return {'functions': functions}\n\n");

    // set_unstable_period dispatch — {"method":"set_unstable_period","params":{"id":21,"period":10}}
    s.push_str("def handle_set_unstable_period(params):\n");
    s.push_str("    id = params.get('id', 0)\n");
    s.push_str("    period = params.get('period', 0)\n");
    s.push_str("    ta_lib.TA_SetUnstablePeriod(id, period)\n");
    s.push_str("    return {'status': 'ok'}\n\n");

    // Main loop
    s.push_str("if __name__ == '__main__':\n");
    s.push_str("    for line in sys.stdin:\n");
    s.push_str("        line = line.strip()\n");
    s.push_str("        if not line:\n");
    s.push_str("            continue\n");
    s.push_str("        try:\n");
    s.push_str("            req = json.loads(line)\n");
    s.push_str("            resp = handle_request(req)\n");
    s.push_str("            print(json.dumps(resp), flush=True)\n");
    s.push_str("        except Exception as e:\n");
    s.push_str("            print(json.dumps({'error': str(e)}), flush=True)\n");

    s
}
