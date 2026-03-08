//! Generates JSON-RPC server source files for each target language.
//!
//! Each generated server reads JSON-RPC requests from stdin, dispatches to
//! the generated TA function implementations, and writes JSON responses to stdout.
//! All servers speak the same protocol as the existing Rust server in server.rs.

use crate::ir::{FuncDef, ParamType};
use std::path::Path;

/// Replace @@CORE_XXX@@ markers in the Java server template with actual
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
                    lines.push(format!("    {}", trimmed));
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

/// Generate a standalone C JSON-RPC server source file.
///
/// The generated file #includes the generated ta_*.c files and provides
/// a main() loop that reads JSON-RPC from stdin.
/// Generate a minimal ta_func.h stub for standalone compilation of the C server.
///
/// This file provides just the type definitions that the generated ta_*.c files
/// expect, without pulling in the full TA-Lib headers.
pub fn generate_c_header_stub() -> String {
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

    // Unstable period: always 0 for standalone server
    s.push_str("#define TA_GLOBALS_UNSTABLE_PERIOD(id, name) 0\n");
    s.push_str("#define TA_FUNC_UNST_EMA 0\n");
    s.push_str("#define TA_FUNC_UNST_RSI 1\n");
    s.push_str("#define TA_FUNC_UNST_NONE 0\n\n");

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
    s.push_str("#include <math.h>\n\n");

    // Include generated function implementations.
    // Order matters: functions that are called by others must come first.
    // Simple heuristic: include in sorted order, then move MA to the end
    // since it dispatches to SMA, EMA, WMA, etc.
    let mut sorted_names: Vec<&str> = funcs.iter().map(|f| f.name.as_str()).collect();
    sorted_names.sort();
    // Move MA to end if present (it calls other functions)
    if let Some(pos) = sorted_names.iter().position(|n| *n == "MA") {
        let ma = sorted_names.remove(pos);
        sorted_names.push(ma);
    }
    for name in &sorted_names {
        s.push_str(&format!("#include \"ta_{}.c\"\n", name));
    }
    s.push_str("\n");

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

"#
    .to_string()
}

fn generate_c_dispatch(funcs: &[FuncDef]) -> String {
    let mut s = String::new();

    // Static buffers for input arrays
    s.push_str("static double g_inBuf0[MAX_ARRAY_SIZE];\n");
    s.push_str("static double g_inBuf1[MAX_ARRAY_SIZE];\n");
    s.push_str("static double g_outBuf[MAX_ARRAY_SIZE];\n\n");

    s.push_str("static void handle_request(const char *json, char *resp, int resp_size) {\n");

    // Extract method name
    s.push_str("    int methodLen = 0;\n");
    s.push_str("    const char *method = json_find_string(json, \"method\", &methodLen);\n");
    s.push_str("    if( !method ) {\n");
    s.push_str("        snprintf(resp, resp_size, \"{\\\"error\\\":\\\"Missing method field\\\"}\");\n");
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

        // Extract input arrays
        let input_names: Vec<&str> = func
            .inputs
            .iter()
            .filter(|inp| inp.param_type == ParamType::Real)
            .map(|inp| inp.name.as_str())
            .collect();

        for (j, name) in input_names.iter().enumerate() {
            let buf = format!("g_inBuf{}", j);
            s.push_str(&format!(
                "        int n{j} = json_find_double_array(json, \"{name}\", {buf}, MAX_ARRAY_SIZE);\n",
            ));
            // Suppress unused warning
            s.push_str(&format!("        (void)n{};\n", j));
        }

        // Extract optional params
        for opt in &func.optional_inputs {
            s.push_str(&format!(
                "        int {} = json_find_int(json, \"{}\");\n",
                opt.name, opt.name
            ));
        }

        // Declare output variables
        s.push_str("        int outBegIdx = 0, outNBElement = 0;\n");

        // Call the function
        s.push_str(&format!("        TA_RetCode rc = TA_{}(\n", func.name));
        s.push_str("            startIdx, endIdx,\n");

        // Input arrays
        for (j, _name) in input_names.iter().enumerate() {
            s.push_str(&format!("            g_inBuf{},\n", j));
        }

        // Optional params
        for opt in &func.optional_inputs {
            s.push_str(&format!("            {},\n", opt.name));
        }

        // Output params
        s.push_str("            &outBegIdx, &outNBElement, g_outBuf);\n");

        // Build response
        s.push_str("        int pos = snprintf(resp, resp_size,\n");
        s.push_str("            \"{\\\"retCode\\\":%d,\\\"outBegIdx\\\":%d,\\\"outNBElement\\\":%d,\\\"outReal\\\":\",\n");
        s.push_str("            (int)rc, outBegIdx, outNBElement);\n");
        s.push_str("        pos += json_write_double_array(resp + pos, resp_size - pos,\n");
        s.push_str("                                       g_outBuf, outNBElement);\n");
        s.push_str("        snprintf(resp + pos, resp_size - pos, \"}\");\n");

        s.push_str("    }\n");
    }

    // Unknown method
    s.push_str("    else {\n");
    s.push_str("        snprintf(resp, resp_size,\n");
    s.push_str("            \"{\\\"error\\\":\\\"Unknown method: %.*s\\\"}\", methodLen, method);\n");
    s.push_str("    }\n");

    s.push_str("}\n\n");
    s
}

/// Generate a Java JSON-RPC server source file.
///
/// Generates a single TaCodegenServe.java with all necessary classes inline
/// (RetCode enum, MInteger, Core class with methods, main server loop).
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
    s.push_str("    Ema, Rsi, None;\n");
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

    // Dispatch method
    s.push_str("    static String handleRequest(String json) {\n");

    for (i, func) in funcs.iter().enumerate() {
        let method_name = format!("TA_{}", func.name);
        let cond = if i == 0 {
            "if"
        } else {
            "else if"
        };
        let func_lower = func.name.to_lowercase();

        s.push_str(&format!(
            "        {} (json.contains(\"\\\"{}\\\"\")) {{\n",
            cond, method_name
        ));
        s.push_str("            int startIdx = jsonInt(json, \"startIdx\");\n");
        s.push_str("            int endIdx = jsonInt(json, \"endIdx\");\n");

        // Inputs
        let real_inputs: Vec<&str> = func
            .inputs
            .iter()
            .filter(|inp| inp.param_type == ParamType::Real)
            .map(|inp| inp.name.as_str())
            .collect();

        for name in &real_inputs {
            s.push_str(&format!(
                "            double[] {} = jsonDoubleArray(json, \"{}\");\n",
                name, name
            ));
        }

        // Optional params
        for opt in &func.optional_inputs {
            s.push_str(&format!(
                "            int {} = jsonInt(json, \"{}\");\n",
                opt.name, opt.name
            ));
        }

        // Outputs
        s.push_str("            double[] outReal = new double[endIdx - startIdx + 1];\n");
        s.push_str("            MInteger outBegIdx = new MInteger();\n");
        s.push_str("            MInteger outNBElement = new MInteger();\n");

        // Call
        s.push_str(&format!("            RetCode rc = core.{}(\n", func_lower));
        s.push_str("                startIdx, endIdx,\n");
        for name in &real_inputs {
            s.push_str(&format!("                {},\n", name));
        }
        for opt in &func.optional_inputs {
            s.push_str(&format!("                {},\n", opt.name));
        }
        s.push_str("                outBegIdx, outNBElement, outReal);\n");

        // Response
        s.push_str("            return \"{\\\"retCode\\\":\" + rc.toInt() +\n");
        s.push_str("                \",\\\"outBegIdx\\\":\" + outBegIdx.value +\n");
        s.push_str("                \",\\\"outNBElement\\\":\" + outNBElement.value +\n");
        s.push_str("                \",\\\"outReal\\\":\" + doubleArrayToJson(outReal, outNBElement.value) + \"}\";\n");

        s.push_str("        }\n");
    }

    s.push_str("        return \"{\\\"error\\\":\\\"Unknown method\\\"}\";\n");
    s.push_str("    }\n\n");

    // Main method
    s.push_str("    public static void main(String[] args) throws Exception {\n");
    s.push_str("        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));\n");
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
pub fn generate_dotnet_server(funcs: &[FuncDef]) -> String {
    let mut s = String::new();

    s.push_str("// Auto-generated JSON-RPC server for ta_codegen .NET output.\n");
    s.push_str("// Uses P/Invoke to call the generated C shared library.\n");
    s.push_str("// Requires: dotnet 8.0+, libta_codegen_funcs.dylib/.so in bin/\n");
    s.push_str("using System;\n");
    s.push_str("using System.IO;\n");
    s.push_str("using System.Text.Json;\n");
    s.push_str("using System.Runtime.InteropServices;\n\n");

    s.push_str("public class TaCodegenServe {\n\n");

    // P/Invoke declarations
    for func in funcs {
        let func_upper = &func.name;

        let real_inputs: Vec<&str> = func
            .inputs
            .iter()
            .filter(|inp| inp.param_type == ParamType::Real)
            .map(|inp| inp.name.as_str())
            .collect();

        s.push_str(&format!(
            "    [DllImport(\"ta_codegen_funcs\", EntryPoint = \"TA_{}\")]\n",
            func_upper
        ));
        s.push_str(&format!(
            "    static extern int TA_{}(\n",
            func_upper
        ));
        s.push_str("        int startIdx, int endIdx,\n");

        for name in &real_inputs {
            s.push_str(&format!("        double[] {},\n", name));
        }

        for opt in &func.optional_inputs {
            s.push_str(&format!("        int {},\n", opt.name));
        }

        s.push_str("        out int outBegIdx, out int outNBElement,\n");
        s.push_str("        double[] outReal);\n\n");
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

        let real_inputs: Vec<&str> = func
            .inputs
            .iter()
            .filter(|inp| inp.param_type == ParamType::Real)
            .map(|inp| inp.name.as_str())
            .collect();

        s.push_str(&format!(
            "            {} (method == \"{}\") {{\n",
            cond, method_name
        ));

        // Extract input arrays
        for name in &real_inputs {
            s.push_str(&format!(
                "                double[] {} = GetDoubleArray(p, \"{}\");\n",
                name, name
            ));
        }

        // Extract optional params
        for opt in &func.optional_inputs {
            let default = opt.default.unwrap_or(0);
            s.push_str(&format!(
                "                int {} = p.TryGetProperty(\"{}\", out var _{0}Val) ? _{0}Val.GetInt32() : {};\n",
                opt.name, opt.name, default
            ));
        }

        // Call and return
        s.push_str("                double[] outReal = new double[n];\n");
        s.push_str(&format!(
            "                int rc = TA_{}(startIdx, endIdx, ",
            func.name
        ));
        for name in &real_inputs {
            s.push_str(&format!("{}, ", name));
        }
        for opt in &func.optional_inputs {
            s.push_str(&format!("{}, ", opt.name));
        }
        s.push_str("out int outBegIdx, out int outNBElement, outReal);\n");
        s.push_str("                return FormatResponse(rc, outBegIdx, outNBElement, outReal);\n");
        s.push_str("            }\n");
    }

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

    // Helper: format JSON response
    s.push_str("    static string FormatResponse(int rc, int outBegIdx, int outNBElement, double[] outReal) {\n");
    s.push_str("        var parts = new string[outNBElement];\n");
    s.push_str("        for (int i = 0; i < outNBElement; i++)\n");
    s.push_str("            parts[i] = outReal[i].ToString(\"G15\");\n");
    s.push_str("        string arr = \"[\" + string.Join(\",\", parts) + \"]\";\n");
    s.push_str("        return $\"{{\\\"retCode\\\":{rc},\\\"outBegIdx\\\":{outBegIdx},\\\"outNBElement\\\":{outNBElement},\\\"outReal\\\":{arr}}}\";\n");
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

    // Inline C header block — type definitions needed by the generated C functions
    s.push_str("%{\n");
    s.push_str("#include \"ta_func.h\"\n");
    s.push_str("#define TA_SUCCESS 0\n");
    s.push_str("#define TA_INTEGER_DEFAULT (-2147483648)\n");
    s.push_str("#define TA_REAL_DEFAULT (-4e+37)\n");
    // Forward-declare all TA functions so the wrapper can call them
    for func in funcs {
        let real_inputs: Vec<&str> = func
            .inputs
            .iter()
            .filter(|inp| inp.param_type == ParamType::Real)
            .map(|inp| inp.name.as_str())
            .collect();

        s.push_str(&format!("extern TA_RetCode TA_{}(int, int", func.name));
        for _ in &real_inputs {
            s.push_str(", const double*");
        }
        for _ in &func.optional_inputs {
            s.push_str(", int");
        }
        s.push_str(", int*, int*, double*);\n");

        // Lookback
        s.push_str(&format!("extern int TA_{}_Lookback(", func.name));
        let opt_params: Vec<String> = func.optional_inputs.iter().map(|_| "int".to_string()).collect();
        s.push_str(&opt_params.join(", "));
        if opt_params.is_empty() {
            s.push_str("void");
        }
        s.push_str(");\n");
    }
    s.push_str("%}\n\n");

    // Constants visible to Python
    s.push_str("#define TA_SUCCESS 0\n\n");

    // ---- Python 3 typemaps (adapted from ta_libc.python.swg) ----
    s.push_str(&generate_swig_python3_typemaps());

    // ---- Function declarations from generated .swg files ----
    // These use the special parameter names (START_IDX, IN_ARRAY, etc.)
    // that the typemaps above match on.
    for func in funcs {
        s.push_str(&format!(
            "\n/* TA_{} */\n",
            func.name
        ));

        // Include the generated .swg file
        s.push_str(&format!("%include \"ta_{}.swg\"\n", func.name));
    }

    s
}

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
pub fn generate_swig_server(funcs: &[FuncDef]) -> String {
    let mut s = String::new();

    s.push_str("#!/usr/bin/env python3\n");
    s.push_str("\"\"\"Auto-generated JSON-RPC server for ta_codegen SWIG/Python output.\n");
    s.push_str("Uses the SWIG-generated ta_lib module to call TA functions.\n");
    s.push_str("\"\"\"\n");
    s.push_str("import sys\n");
    s.push_str("import os\n");
    s.push_str("import json\n\n");

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

        s.push_str(&format!("    if method == '{}':\n", method_name));
        s.push_str(&format!("        return handle_{}(params)\n", func_lower));
    }

    s.push_str("    return {'error': f'Unknown method: {method}'}\n\n");

    // Per-function handlers
    for func in funcs {
        let func_lower = func.name.to_lowercase();
        let func_upper = &func.name;

        s.push_str(&format!("def handle_{}(params):\n", func_lower));
        s.push_str("    start_idx = params.get('startIdx', 0)\n");
        s.push_str("    end_idx = params.get('endIdx', 0)\n");

        // Input arrays
        let real_inputs: Vec<&str> = func
            .inputs
            .iter()
            .filter(|inp| inp.param_type == ParamType::Real)
            .map(|inp| inp.name.as_str())
            .collect();

        for name in &real_inputs {
            s.push_str(&format!(
                "    {} = [float(x) for x in params.get('{}', [])]\n",
                name, name
            ));
        }

        // Optional params
        for opt in &func.optional_inputs {
            let default = opt.default.unwrap_or(0);
            s.push_str(&format!(
                "    {} = params.get('{}', {})\n",
                opt.name, opt.name, default
            ));
        }

        // Call via SWIG module — returns (outBegIdx, outReal) on success
        s.push_str("    try:\n");
        s.push_str(&format!("        result = ta_lib.TA_{}(\n", func_upper));
        s.push_str("            start_idx, end_idx,\n");
        for name in &real_inputs {
            s.push_str(&format!("            {},\n", name));
        }
        for opt in &func.optional_inputs {
            s.push_str(&format!("            {},\n", opt.name));
        }
        s.push_str("        )\n");

        // SWIG returns [None, outBegIdx, outReal_list] on TA_SUCCESS
        // result[0] is None (retCode mapped away), [1] is outBegIdx, [2] is outReal
        s.push_str("        out_beg = result[1]\n");
        s.push_str("        out_real = list(result[2])\n");
        s.push_str("        return {\n");
        s.push_str("            'retCode': 0,\n");
        s.push_str("            'outBegIdx': out_beg,\n");
        s.push_str("            'outNBElement': len(out_real),\n");
        s.push_str("            'outReal': out_real,\n");
        s.push_str("        }\n");
        s.push_str("    except RuntimeError as e:\n");
        s.push_str("        return {'error': str(e)}\n\n");
    }

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
