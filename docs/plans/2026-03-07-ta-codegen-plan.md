# ta_codegen MULT Prototype Implementation Plan

> **For Claude:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Build a new Rust-based code generator that reads YAML + logic definition files and produces native MULT implementations for C, Rust, Java, .NET, and SWIG — plus a JSON-RPC validation server.

**Architecture:** Function definitions live in `ta_func_defs/mult/` as YAML metadata + pseudocode logic. The generator parses these into a typed IR, then each backend renders the IR to native code. Output goes to `ta_codegen_output/` for comparison against existing gen_code output.

**Tech Stack:** Rust, serde + serde_yaml, serde_json (for JSON-RPC)

**Design doc:** `docs/plans/2026-03-07-ta-codegen-design.md`

---

### Task 1: Scaffold the Crate and Create MULT Definition Files

**Files:**
- Create: `tools/ta_codegen/Cargo.toml`
- Create: `tools/ta_codegen/src/main.rs`
- Create: `ta_func_defs/mult/mult.yaml`
- Create: `ta_func_defs/mult/mult.logic`

**Step 1: Create the crate**

```bash
mkdir -p tools/ta_codegen/src
mkdir -p ta_func_defs/mult
```

`tools/ta_codegen/Cargo.toml`:
```toml
[package]
name = "ta-codegen"
version = "0.1.0"
edition = "2021"

[[bin]]
name = "ta_codegen"
path = "src/main.rs"

[dependencies]
serde = { version = "1", features = ["derive"] }
serde_yaml = "0.9"
serde_json = "1"
```

`tools/ta_codegen/src/main.rs`:
```rust
fn main() {
    println!("ta_codegen: not yet implemented");
}
```

**Step 2: Create MULT definition files**

`ta_func_defs/mult/mult.yaml`:
```yaml
name: MULT
group: Math Operators
inputs:
  - name: inReal0
    type: real
  - name: inReal1
    type: real
outputs:
  - name: outReal
    type: real
lookback: 0
```

`ta_func_defs/mult/mult.logic`:
```
index outIdx = 0
index i = startIdx
while i <= endIdx {
    outReal[outIdx] = inReal0[i] * inReal1[i]
    outIdx += 1
    i += 1
}
outBegIdx = startIdx
outNBElement = outIdx
```

**Step 3: Verify the crate builds**

```bash
cd tools/ta_codegen && cargo build
```
Expected: Compiles, prints placeholder message.

**Step 4: Commit**

```bash
git add tools/ta_codegen/ ta_func_defs/
git commit -m "Scaffold ta_codegen crate and MULT definition files"
```

---

### Task 2: IR Data Types and YAML Parser

**Files:**
- Create: `tools/ta_codegen/src/ir.rs`
- Create: `tools/ta_codegen/src/parser.rs`
- Create: `tools/ta_codegen/src/parser/yaml.rs`
- Modify: `tools/ta_codegen/src/main.rs`

The IR (Intermediate Representation) is the core data structure. Everything depends on it.

**Step 1: Define the IR types**

`tools/ta_codegen/src/ir.rs`:
```rust
/// A complete function definition (metadata + logic).
#[derive(Debug, Clone)]
pub struct FuncDef {
    pub name: String,          // "MULT"
    pub group: String,         // "Math Operators"
    pub inputs: Vec<Input>,
    pub optional_inputs: Vec<OptInput>,
    pub outputs: Vec<Output>,
    pub lookback: LookbackExpr,
    pub body: Vec<Statement>,  // parsed from .logic file
}

#[derive(Debug, Clone)]
pub struct Input {
    pub name: String,
    pub param_type: ParamType,
}

#[derive(Debug, Clone)]
pub struct OptInput {
    pub name: String,
    pub param_type: ParamType,
    pub range: Option<(i32, i32)>,
    pub default: Option<i32>,
}

#[derive(Debug, Clone)]
pub struct Output {
    pub name: String,
    pub param_type: ParamType,
}

#[derive(Debug, Clone, PartialEq)]
pub enum ParamType {
    Real,
    Integer,
}

/// Lookback can be a literal or an expression referencing an optional input.
#[derive(Debug, Clone)]
pub enum LookbackExpr {
    Literal(i32),
    ParamMinus(String, i32),  // e.g., "optInTimePeriod - 1"
}

// --- Logic AST ---

#[derive(Debug, Clone)]
pub enum Statement {
    VarDecl {
        var_type: VarType,
        name: String,
        init: Expr,
    },
    Assign {
        target: Expr,
        value: Expr,
    },
    While {
        condition: Expr,
        body: Vec<Statement>,
    },
}

#[derive(Debug, Clone, PartialEq)]
pub enum VarType {
    Real,
    Integer,
    Index,
}

#[derive(Debug, Clone)]
pub enum Expr {
    Literal(f64),
    IntLiteral(i64),
    Var(String),
    ArrayAccess(String, Box<Expr>),  // arr[idx]
    BinOp(Box<Expr>, BinOp, Box<Expr>),
    Cast(VarType, Box<Expr>),        // to_real(x), to_int(x)
}

#[derive(Debug, Clone)]
pub enum BinOp {
    Add,
    Sub,
    Mul,
    Div,
    LessEq,
    Less,
    Greater,
    GreaterEq,
    Eq,
}
```

**Step 2: Write the YAML parser**

`tools/ta_codegen/src/parser.rs`:
```rust
pub mod yaml;
pub mod logic;
```

`tools/ta_codegen/src/parser/yaml.rs`:
```rust
use serde::Deserialize;
use crate::ir::{FuncDef, Input, OptInput, Output, ParamType, LookbackExpr};
use std::path::Path;

#[derive(Deserialize)]
struct YamlFuncDef {
    name: String,
    group: String,
    inputs: Vec<YamlParam>,
    #[serde(default)]
    optional_inputs: Vec<YamlOptParam>,
    outputs: Vec<YamlParam>,
    lookback: serde_yaml::Value,
}

#[derive(Deserialize)]
struct YamlParam {
    name: String,
    #[serde(rename = "type")]
    param_type: String,
}

#[derive(Deserialize)]
struct YamlOptParam {
    name: String,
    #[serde(rename = "type")]
    param_type: String,
    range: Option<Vec<i32>>,
    default: Option<i32>,
}

fn parse_param_type(s: &str) -> ParamType {
    match s {
        "real" => ParamType::Real,
        "integer" => ParamType::Integer,
        _ => panic!("Unknown param type: {}", s),
    }
}

fn parse_lookback(value: &serde_yaml::Value) -> LookbackExpr {
    match value {
        serde_yaml::Value::Number(n) => {
            LookbackExpr::Literal(n.as_i64().unwrap() as i32)
        }
        serde_yaml::Value::String(s) => {
            // Parse "optInTimePeriod - 1" style expressions
            let parts: Vec<&str> = s.split_whitespace().collect();
            if parts.len() == 3 && parts[1] == "-" {
                let param = parts[0].to_string();
                let offset: i32 = parts[2].parse().unwrap();
                LookbackExpr::ParamMinus(param, offset)
            } else {
                panic!("Unsupported lookback expression: {}", s);
            }
        }
        _ => panic!("Unsupported lookback value"),
    }
}

pub fn parse_yaml(path: &Path) -> (String, String, Vec<Input>, Vec<OptInput>, Vec<Output>, LookbackExpr) {
    let content = std::fs::read_to_string(path)
        .unwrap_or_else(|e| panic!("Failed to read {}: {}", path.display(), e));
    let yaml: YamlFuncDef = serde_yaml::from_str(&content)
        .unwrap_or_else(|e| panic!("Failed to parse {}: {}", path.display(), e));

    let inputs = yaml.inputs.iter().map(|p| Input {
        name: p.name.clone(),
        param_type: parse_param_type(&p.param_type),
    }).collect();

    let optional_inputs = yaml.optional_inputs.iter().map(|p| OptInput {
        name: p.name.clone(),
        param_type: parse_param_type(&p.param_type),
        range: p.range.as_ref().map(|r| (r[0], r[1])),
        default: p.default,
    }).collect();

    let outputs = yaml.outputs.iter().map(|p| Output {
        name: p.name.clone(),
        param_type: parse_param_type(&p.param_type),
    }).collect();

    let lookback = parse_lookback(&yaml.lookback);

    (yaml.name, yaml.group, inputs, optional_inputs, outputs, lookback)
}
```

**Step 3: Wire into main.rs and test**

Update `tools/ta_codegen/src/main.rs`:
```rust
mod ir;
mod parser;

use std::path::Path;

fn main() {
    let yaml_path = Path::new("../../ta_func_defs/mult/mult.yaml");
    let (name, group, inputs, opt_inputs, outputs, lookback) =
        parser::yaml::parse_yaml(yaml_path);

    println!("Parsed: {} ({})", name, group);
    println!("  Inputs: {:?}", inputs);
    println!("  OptInputs: {:?}", opt_inputs);
    println!("  Outputs: {:?}", outputs);
    println!("  Lookback: {:?}", lookback);
}
```

**Step 4: Build and run**

```bash
cd tools/ta_codegen && cargo run
```
Expected: Prints parsed MULT metadata.

**Step 5: Commit**

```bash
git add tools/ta_codegen/src/
git commit -m "Add IR types and YAML parser for function metadata"
```

---

### Task 3: Logic File Parser

**Files:**
- Create: `tools/ta_codegen/src/parser/logic.rs`
- Modify: `tools/ta_codegen/src/main.rs`

Parse the `.logic` pseudocode into `Vec<Statement>`. For the MULT prototype, the parser needs to handle:
- Variable declarations: `index outIdx = 0`
- Assignment: `outBegIdx = startIdx`
- Array assignment: `outReal[outIdx] = expr`
- While loops: `while condition { ... }`
- Binary expressions: `inReal0[i] * inReal1[i]`, `i + 1`
- Array access: `inReal0[i]`
- Compound assignment: `outIdx += 1`

**Step 1: Write the logic parser**

`tools/ta_codegen/src/parser/logic.rs`:

This is a simple recursive descent parser. It tokenizes the input first, then parses tokens into statements.

The parser should:
1. Tokenize: split into words, operators, braces, brackets
2. Parse statements line by line (or brace-delimited for while blocks)
3. Parse expressions with proper precedence (arithmetic > comparison)

For MULT, the logic is only 8 lines. The parser doesn't need to be complete — just enough for these constructs. It will grow as more functions are added.

Key token types: `Ident`, `Number`, `Op(+,-,*,/,<=,>=,==,+=)`, `LBrace`, `RBrace`, `LBracket`, `RBracket`, `Assign(=)`, `While`, `VarType(index/real/integer)`

Key parse functions:
- `parse_statements()` → `Vec<Statement>`
- `parse_statement()` → `Statement` (dispatches on first token)
- `parse_expr()` → `Expr` (handles binary ops, array access, literals, vars)

**Step 2: Wire into main.rs to parse mult.logic**

After YAML parsing, also parse the logic file and build a complete `FuncDef`:

```rust
let logic_path = Path::new("../../ta_func_defs/mult/mult.logic");
let body = parser::logic::parse_logic(logic_path);

let func_def = ir::FuncDef {
    name, group, inputs, optional_inputs: opt_inputs,
    outputs, lookback, body,
};
println!("Parsed {} statements", func_def.body.len());
```

**Step 3: Build and run**

```bash
cd tools/ta_codegen && cargo run
```
Expected: Prints parsed metadata + "Parsed 8 statements" (or similar).

**Step 4: Add a unit test**

Write a test that parses `mult.logic` and verifies the AST structure — correct number of statements, first statement is a VarDecl of type Index named "outIdx", etc.

**Step 5: Commit**

```bash
git add tools/ta_codegen/src/
git commit -m "Add logic file parser with support for MULT constructs"
```

---

### Task 4: C Backend

**Files:**
- Create: `tools/ta_codegen/src/backends/mod.rs`
- Create: `tools/ta_codegen/src/backends/c.rs`
- Modify: `tools/ta_codegen/src/main.rs`

This is the reference backend. It produces a C file matching the format of `src/ta_func/ta_MULT.c`.

**Reference output** (what the C backend must produce for MULT):

The generated C file needs:
1. Copyright header (standard TA-Lib boilerplate)
2. `TA_MULT_Lookback()` function returning `lookback` value
3. `TA_MULT()` double-precision function with:
   - Parameter validation (startIdx, endIdx range checks)
   - The logic body rendered as C
   - outBegIdx/outNBElement writeback
4. `TA_S_MULT()` single-precision variant (float inputs, double output)

**Key type mappings for C:**
- `real` → `double` (or `float` for single-precision inputs)
- `integer` → `int`
- `index` → `int`
- Array input: `const double inReal[]`
- Array output: `double outReal[]`
- Output scalar: `int *outBegIdx`
- Return type: `TA_RetCode`
- Success: `TA_SUCCESS`

**Step 1: Create the backend module**

`tools/ta_codegen/src/backends/mod.rs`:
```rust
pub mod c;
pub mod rust_lang;
pub mod java;
pub mod dotnet;
pub mod swig;
```

**Step 2: Implement the C backend**

`tools/ta_codegen/src/backends/c.rs`:

The C backend needs these functions:
- `generate(func: &FuncDef) -> String` — main entry point, returns full file content
- `gen_lookback(func: &FuncDef) -> String` — lookback function
- `gen_double_func(func: &FuncDef) -> String` — main double-precision function
- `gen_single_func(func: &FuncDef) -> String` — single-precision variant
- `render_statement(stmt: &Statement) -> String` — renders a statement as C
- `render_expr(expr: &Expr) -> String` — renders an expression as C

Expression rendering for C:
- `Var("x")` → `"x"`
- `ArrayAccess("arr", idx)` → `"arr[{idx}]"`
- `BinOp(l, Mul, r)` → `"({l}*{r})"`
- `IntLiteral(0)` → `"0"`
- `Cast(Real, e)` → `"(double)({e})"`

Statement rendering for C:
- `VarDecl { type: Index, name, init }` → `"int {name} = {init};"`
- `Assign { target, value }` → `"{target} = {value};"`
- `While { cond, body }` → `"while( {cond} )\n{\n{body}\n}"`

For output scalar parameters, use `*outBegIdx` (pointer dereference) in C.

**Step 3: Wire into main.rs**

After parsing, call the C backend and write output:
```rust
let c_output = backends::c::generate(&func_def);
let out_dir = Path::new("../../ta_codegen_output/c");
std::fs::create_dir_all(out_dir).unwrap();
std::fs::write(out_dir.join(format!("ta_{}.c", func_def.name)), &c_output).unwrap();
println!("Generated C: ta_{}.c", func_def.name);
```

**Step 4: Build, run, and compare**

```bash
cd tools/ta_codegen && cargo run
diff ../../ta_codegen_output/c/ta_MULT.c ../../src/ta_func/ta_MULT.c
```

The diff won't be zero (the existing file has gen_code markers, multi-language conditional blocks, etc.) but the **C-only portions** should be functionally equivalent — same function signatures, same logic, same validation. Compare manually.

**Step 5: Commit**

```bash
git add tools/ta_codegen/src/backends/
git commit -m "Add C backend for ta_codegen, generates MULT"
```

---

### Task 5: Rust Backend

**Files:**
- Create: `tools/ta_codegen/src/backends/rust_lang.rs`

Produces Rust code matching `rust/src/ta_func/mult.rs`.

**Key type mappings for Rust:**
- `real` → `f64` (or `f32` for single-precision)
- `integer` → `i32`
- `index` → `usize`
- Array input: `&[f64]` or `&[f32]`
- Array output: `&mut [f64]`
- Output scalar: `&mut usize` (for outBegIdx/outNBElement)
- Return type: `RetCode`
- Success: `RetCode::Success`
- Function name: `mult` (snake_case)
- Method on `&self`

**Key differences from C:**
- No negative index checks (usize is unsigned)
- `(*outNBElement) = outIdx;` style dereference
- Array access is the same syntax: `arr[i]`
- Cast: `as f64` instead of `(double)`
- Loop: `for i in start..=end` (but while loops also work)

**Compare against:** `rust/src/ta_func/mult.rs`

**Step 1: Implement, Step 2: Generate, Step 3: Compare, Step 4: Commit**

Same pattern as Task 4. Compare output against existing `mult.rs`.

```bash
git commit -m "Add Rust backend for ta_codegen, generates MULT"
```

---

### Task 6: Java Backend

**Files:**
- Create: `tools/ta_codegen/src/backends/java.rs`

Produces Java method code matching the MULT section in `Core.java`.

**Key type mappings for Java:**
- `real` → `double` (or `float` for single-precision)
- `integer` → `int`
- `index` → `int`
- Array input: `double inReal[]` or `float inReal[]`
- Array output: `double outReal[]`
- Output scalar: `MInteger outBegIdx` (accessed via `.value`)
- Return type: `RetCode`
- Success: `RetCode.Success`
- Function name: `mult` (camelCase)
- Method: `public RetCode mult(...)`

**Key differences from C:**
- Output scalars use `.value` instead of pointer dereference: `outBegIdx.value = startIdx;`
- `MInteger` wrapper class for output indices
- Negative index validation included (signed ints)
- No `const` keyword on array params
- Class method (no `static`)

**Compare against:** MULT method in `java/src/com/tictactec/ta/lib/Core.java`

```bash
git commit -m "Add Java backend for ta_codegen, generates MULT"
```

---

### Task 7: .NET Backend

**Files:**
- Create: `tools/ta_codegen/src/backends/dotnet.rs`

Produces C++/CLI header declarations matching the MULT section in `TA-Lib-Core.h`.

**Key type mappings for .NET:**
- `real` → `double` (or `float` for single-precision)
- `integer` → `int`
- Array input: `cli::array<double>^` and `SubArray<double>^` (two overloads)
- Array output: same
- Output scalar: `[Out]int% outBegIdx`
- Return type: `enum class RetCode`
- Function name: `Mult` (PascalCase)
- Static method: `static enum class RetCode Mult(...)`

**Key differences:**
- Two overload sets: `cli::array` and `SubArray` versions
- `SubArray` versions have the implementation
- `cli::array` versions dispatch to `SubArray` versions via `gcnew SubArrayFrom1D`
- Macro aliases: `#define TA_MULT Core::Mult`

**Compare against:** MULT section in `dotnet/src/Core/TA-Lib-Core.h`

```bash
git commit -m "Add .NET backend for ta_codegen, generates MULT"
```

---

### Task 8: SWIG Backend

**Files:**
- Create: `tools/ta_codegen/src/backends/swig.rs`

Produces SWIG interface definition matching MULT in `ta_func.swg`.

**Output format:**
```c
/*
 * TA_MULT - Vector Arithmetic Mult
 *
 * Input  = double, double
 * Output = double
 *
 */
TA_RetCode TA_MULT( int           START_IDX,
                    int           END_IDX,
                    const double *IN_ARRAY /* inReal0 */,
                    const double *IN_ARRAY /* inReal1 */,
                    int          *BEG_IDX,
                    int          *OUT_SIZE,
                    double       *OUT_ARRAY /* outReal */ );

int TA_MULT_Lookback( void );
```

**Key patterns:**
- Uses SWIG typemap markers: `START_IDX`, `END_IDX`, `IN_ARRAY`, `BEG_IDX`, `OUT_SIZE`, `OUT_ARRAY`
- Comment block with function description and I/O types
- Parameter names in comments after typemap markers
- Only double-precision (no single-precision variant in SWIG)
- Lookback function declaration

**Compare against:** MULT section in `swig/src/interface/ta_func.swg`

```bash
git commit -m "Add SWIG backend for ta_codegen, generates MULT"
```

---

### Task 9: JSON-RPC Validation Server

**Files:**
- Create: `tools/ta_codegen/src/server.rs`
- Modify: `tools/ta_codegen/src/main.rs` (add `serve` subcommand)

The server reads function definitions, compiles the logic into executable Rust, and serves function calls over stdin/stdout JSON-RPC.

**For the prototype**, the server can be simpler than a full JSON-RPC implementation: read one JSON request per line from stdin, execute, write one JSON response per line to stdout.

**Request format:**
```json
{"method": "TA_MULT", "params": {"startIdx": 0, "endIdx": 4, "inReal0": [1.0, 2.0, 3.0, 4.0, 5.0], "inReal1": [2.0, 3.0, 4.0, 5.0, 6.0]}}
```

**Response format:**
```json
{"retCode": 0, "outBegIdx": 0, "outNBElement": 5, "outReal": [2.0, 6.0, 12.0, 20.0, 30.0]}
```

**Implementation approach:**

For the prototype, the server doesn't need to interpret the logic AST at runtime. Instead, it uses the **generated Rust code** — the Rust backend already produces a working MULT implementation. The server imports and calls it.

However, this creates a chicken-and-egg: the server needs the generated Rust code compiled in. The simplest approach: the server has hand-written dispatch that calls the ta-lib Rust crate (which already has MULT). This proves the JSON-RPC protocol works. Later, the server can be generated from the IR.

Alternative: the server interprets the IR directly (a tiny interpreter for the logic AST). This is more self-contained but more work.

**Recommended for prototype:** Use the existing `ta-lib` Rust crate. Add it as a dependency. The server dispatches `TA_MULT` calls to `Core::new().mult(...)`.

**Step 1: Add ta-lib dependency**

In `tools/ta_codegen/Cargo.toml`:
```toml
[dependencies]
ta-lib = { path = "../../rust" }
```

**Step 2: Implement the server**

`tools/ta_codegen/src/server.rs`:
- Read lines from stdin
- Parse as JSON
- Match `method` field to dispatch function
- For `TA_MULT`: extract params, call `core.mult(...)`, format response
- Write JSON response to stdout

**Step 3: Add CLI subcommand**

Update `main.rs` to support:
- `ta_codegen generate` — generate code for all backends
- `ta_codegen serve` — start JSON-RPC server

**Step 4: Test manually**

```bash
echo '{"method":"TA_MULT","params":{"startIdx":0,"endIdx":4,"inReal0":[1,2,3,4,5],"inReal1":[2,3,4,5,6]}}' | cargo run -- serve
```
Expected: `{"retCode":0,"outBegIdx":0,"outNBElement":5,"outReal":[2.0,6.0,12.0,20.0,30.0]}`

**Step 5: Commit**

```bash
git commit -m "Add JSON-RPC validation server for ta_codegen"
```

---

### Task 10: Validation — Diff and JSON-RPC Harness

**Files:**
- Create: `tools/ta_codegen/tests/validate_mult.sh` (or Python script)

**Step 1: Diff validation**

Compare generated output against existing gen_code output for each language. This is a manual/visual comparison for the prototype — the generated files won't be byte-identical (different formatting, missing gen_code markers) but should be functionally equivalent.

```bash
# Generate all backends
cd tools/ta_codegen && cargo run -- generate

# Compare C
echo "=== C ===" && diff <(grep -v "^/\*.*Generated\|GENCODE\|#if defined" ../../src/ta_func/ta_MULT.c) ../../ta_codegen_output/c/ta_MULT.c || true

# Compare Rust
echo "=== Rust ===" && diff ../../rust/src/ta_func/mult.rs ../../ta_codegen_output/rust/mult.rs || true
```

Document any intentional differences.

**Step 2: JSON-RPC harness**

Create a simple validation script that:
1. Starts the JSON-RPC server
2. Sends MULT calls with the ta_regtest reference data (252 bars of OHLCV)
3. Compares output against known-good values from running the C ta_regtest

The reference data lives in `src/ta_func/ta_gData*.c` files. For the prototype, hard-code a small test case.

**Step 3: Commit**

```bash
git add tools/ta_codegen/tests/
git commit -m "Add validation scripts for ta_codegen MULT output"
```

---

### Task 11: Integration Test and Cleanup

**Files:**
- Create: `tools/ta_codegen/tests/integration_test.rs`
- Modify: `tools/ta_codegen/src/main.rs` (polish CLI)

**Step 1: Rust integration test**

Write a Rust integration test that:
1. Parses `mult.yaml` + `mult.logic`
2. Generates code for each backend
3. Asserts the output is non-empty and contains expected markers (function name, parameter names)

```rust
#[test]
fn test_generate_mult_c() {
    // Parse, generate, assert output contains "TA_MULT" and "TA_RetCode"
}

#[test]
fn test_generate_mult_rust() {
    // Parse, generate, assert output contains "pub fn mult" and "RetCode"
}
```

**Step 2: Polish the CLI**

```
ta_codegen generate [--func=MULT] [--backend=c,rust,java,dotnet,swig] [--output-dir=path]
ta_codegen serve
```

Default: generate all functions for all backends.

**Step 3: Final verification**

```bash
cargo test
cargo run -- generate
ls -la ../../ta_codegen_output/*/
```

**Step 4: Commit**

```bash
git add tools/ta_codegen/
git commit -m "Add integration tests and polish ta_codegen CLI"
```
