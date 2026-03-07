# Design: ta_codegen — Multi-Language Generator from YAML + Logic Files

## Problem

The current gen_code system generates TA-Lib functions for multiple languages (C, Rust, Java, .NET, SWIG/Python/Perl) from C source templates with cross-language macros. While powerful, the macro system is intimidating to contributors and tightly couples all languages to C syntax. The barrier to contribution is high.

## Solution

Replace the C-template-with-macros approach with a cleaner two-file format per function:
1. **YAML metadata** — declares inputs, outputs, optional params, lookback
2. **Logic pseudocode** — expresses the algorithm in a restricted, language-agnostic syntax

A new Rust-based generator (`ta_codegen`) reads these files, builds a typed intermediate representation (IR), and renders native code for each target language through backend plugins.

## Architecture

```
ta_func_defs/              ← function definitions (source of truth)
├── mult/
│   ├── mult.yaml          ← metadata
│   └── mult.logic         ← algorithm
├── sma/
│   ├── sma.yaml
│   └── sma.logic
└── rsi/
    ├── rsi.yaml
    └── rsi.logic

tools/ta_codegen/          ← Rust crate (the generator)
├── Cargo.toml
├── src/
│   ├── main.rs            ← CLI entry point
│   ├── parser/            ← YAML + logic file parsers
│   ├── ir.rs              ← Intermediate representation (typed AST)
│   ├── backends/          ← Code generators per language
│   │   ├── c.rs
│   │   ├── rust_lang.rs
│   │   ├── java.rs
│   │   ├── dotnet.rs
│   │   └── swig.rs
│   └── server.rs          ← JSON-RPC validation server
```

### Data Flow

```
mult.yaml + mult.logic
        |
    Parser (YAML + logic)
        |
    IR (typed AST)
        |
    +------+------+------+------+------+
    C    Rust   Java  .NET  SWIG
```

The IR is the single source of truth. Each backend is a pure function: IR → string of native code.

## Function Definition Format

### Metadata (mult.yaml)

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

More complex example (SMA):

```yaml
name: SMA
group: Overlap Studies
inputs:
  - name: inReal
    type: real
optional_inputs:
  - name: optInTimePeriod
    type: integer
    range: [2, 100000]
    default: 30
outputs:
  - name: outReal
    type: real
lookback: optInTimePeriod - 1
```

### Logic (mult.logic)

C-like restricted syntax — no macros, no preprocessor, just the algorithm. See `docs/ta_codegen_logic_syntax.md` for the full reference.

```c
size_t outIdx = 0;
size_t i = startIdx;
while( i <= endIdx ) {
    outReal[outIdx] = inReal0[i] * inReal1[i];
    outIdx += 1;
    i += 1;
}
outNBElement = outIdx;
outBegIdx = startIdx;
```

Types: `double`, `int`, `size_t` (mapped per language — e.g., `size_t` → `usize` in Rust, `int` in Java).

Key constructs:
- Variable declarations: `double x = 0.0;`, `size_t i;`
- Control flow: `if() {}`, `else if() {}`, `else {}`, `while() {}`, `for()`, `switch/case`, `break`, `continue`
- Casts: `(double)x`, `(size_t)x`, `(int)x`
- Function calls: `SMA(...)`, `SMA_Lookback(...)` (no prefix — generator adds per language)
- Built-ins: `UNSTABLE_PERIOD(RSI)`, `COMPATIBILITY`, `IS_ZERO(x)`, `ARRAY_COPY(...)`
- Math: `sqrt()`, `floor()`, `fabs()`, etc.
- Early return: `return SUCCESS;`

The generator handles parameter validation, signatures, lookback, and single-precision variants automatically from YAML metadata. The logic file is **only the algorithm**.

## Output

ta_codegen writes to its own output directory, separate from the existing source tree:

```
ta_codegen_output/
├── c/
│   └── ta_MULT.c
├── rust/
│   └── mult.rs
├── java/
│   └── Core_MULT.java
├── dotnet/
│   └── Core_MULT.h
└── swig/
    └── ta_MULT.swg
```

The existing gen_code continues to generate its own output. The two systems coexist. Validation is done by diffing old output vs new output.

## Target Languages

| Language | Output | Notes |
|----------|--------|-------|
| C | Standard TA-Lib C function | Primary implementation |
| Rust | Method on Core struct (f64 + f32 + lookback) | Pure Rust, no macros |
| Java | Method in Core.java | Java-native types |
| .NET | C++/CLI managed wrapper | Matches existing format |
| SWIG | Interface definition | Python + Perl bindings |

## JSON-RPC Validation Server

ta_codegen also generates a Rust JSON-RPC server binary that exposes every generated function over a standard protocol. This enables language-agnostic validation without FFI.

### Protocol

Newline-delimited JSON-RPC over stdin/stdout (no HTTP for prototype).

Request:
```json
{
  "method": "TA_MULT",
  "params": {
    "startIdx": 0,
    "endIdx": 251,
    "inReal0": [91.5, 94.81, ...],
    "inReal1": [91.5, 94.81, ...]
  }
}
```

Response:
```json
{
  "retCode": 0,
  "outBegIdx": 0,
  "outNBElement": 252,
  "outReal": [8372.25, 8988.9361, ...]
}
```

### Validation Harness

A small harness (Python or Rust) that:
1. Runs C ta_regtest to capture reference outputs
2. Sends the same inputs to the JSON-RPC server
3. Compares results using ta_regtest's tolerance rules

This keeps ta_regtest completely untouched while proving the validation path works for any language that can run a JSON-RPC server.

## Scope

Incremental function-by-function implementation, each validated against existing gen_code output:

1. **MULT** (complete) — basic arithmetic, while loops, array access
2. **SMA** — `if`/`else`, casts, `return`, optional params, lookback expressions
3. **RSI** — `for` countdown, `UNSTABLE_PERIOD`, `COMPATIBILITY`, `IS_ZERO`, `break`/`continue`
4. **EMA** — function calls (`SMA_Lookback`, `FUNCTION_CALL`)
5. **MA** — `switch`/`case`, dispatcher pattern, temp buffer allocation

Success criteria per function:
1. YAML + logic files fully describe the function
2. `ta_codegen generate` produces valid code for all 5 backends
3. Generated Rust code matches existing gen_code Rust output (diff comparison)
4. JSON-RPC server responds correctly to function calls

## Relationship to Existing Systems

- **gen_code**: Continues to work. ta_codegen is additive, not a replacement. Both coexist.
- **ta_regtest**: Untouched. Used as the C oracle. JSON-RPC harness compares against it.
- **FFI bridge (today's work)**: Still works for direct Rust validation via ta_regtest_rust. Separate concern from ta_codegen.
- **ta_defs.h macros**: Not used by ta_codegen. The whole point is to not need them.

## Future Vision

Once ta_codegen can generate all ~160 functions for all languages and the output matches gen_code, it becomes the replacement. Contributors write YAML + logic files instead of C-with-macros. The JSON-RPC server becomes the universal validation path for any language. New languages are added by writing a new backend — no macros, no conditional compilation.
