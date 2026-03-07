# SMA Support in ta_codegen — Implementation Plan

> **For Claude:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Generate SMA for all 5 backends from YAML + C-like logic file, with output matching existing gen_code reference.

**Architecture:** Extend the parser/IR/backends to handle `if`/`else`, `return`, C-style casts, semicolons, and parenthesized conditions. Migrate MULT to the new C-like syntax first, then add SMA. The generator handles parameter validation, lookback, and the public/private function split automatically from YAML metadata.

**Tech Stack:** Rust (ta_codegen crate), YAML (serde_yaml), recursive descent parser

---

### Task 1: Migrate MULT logic to C-like syntax

**Files:**
- Modify: `ta_func_defs/mult/mult.logic`

**Step 1: Rewrite mult.logic in C-like syntax**

Replace current pseudocode:
```
index outIdx = 0
index i = startIdx
...
```

With C-like syntax (semicolons, C types, parens not needed for MULT since it has no if/while with parens yet — but add semicolons and types):
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

**Step 2: Run tests — they should FAIL** because the parser doesn't understand semicolons or `size_t` yet.

Run: `cd tools/ta_codegen && cargo test 2>&1 | tail -20`
Expected: FAIL — parser panics on `;` or `size_t`

**Step 3: Commit**

```bash
git add ta_func_defs/mult/mult.logic
git commit -m "Migrate mult.logic to C-like syntax (breaks parser — next commit fixes)"
```

---

### Task 2: Update parser for C-like syntax

**Files:**
- Modify: `tools/ta_codegen/src/parser/logic.rs`

This is the big parser change. We need:
1. **Semicolons** — tokenize `;`, treat as statement terminator (like newline currently does)
2. **Parentheses** — tokenize `(` and `)`, handle in conditions and cast expressions
3. **C type keywords** — `double` → `VarType::Real`, `int` → `VarType::Integer`, `size_t` → `VarType::Index`
4. **`if` / `else if` / `else`** — new statement type
5. **`return`** — new statement type (with return value identifier like `SUCCESS`)
6. **C-style casts** — `(double)expr`, `(int)expr`, `(size_t)expr`
7. **`!=` operator** — new comparison
8. **`&&` and `||`** — logical operators (new precedence level, below comparison)
9. **`!` prefix** — logical not (unary)
10. **`--` postfix** — decrement (for `i--` in for loops, later)

**Step 1: Add tokens**

Add to the `Token` enum:
```rust
Semicolon,
LParen,
RParen,
Bang,       // !
```

Add to two-char operators: `!=`, `&&`, `||`

Update the tokenizer to emit these tokens. Semicolons work like newlines (statement separator). `(` and `)` are single-char tokens.

**Step 2: Update type keyword parsing**

In `parse_var_decl` and `parse_statement`, recognize `double`, `int`, `size_t` alongside the old `real`, `integer`, `index` keywords:
```rust
"double" | "real" => VarType::Real,
"int" | "integer" => VarType::Integer,
"size_t" | "index" => VarType::Index,
```

**Step 3: Handle semicolons as statement separators**

In `skip_newlines`, also skip semicolons. Or better: after each statement parse, consume an optional trailing semicolon/newline. The simplest approach: treat `Semicolon` the same as `Newline` in `skip_newlines`.

**Step 4: Handle parenthesized conditions**

In `parse_while`, after consuming `while`, if the next token is `(`, consume it, parse the expression, then consume `)`. Otherwise fall back to current behavior (bare expression before `{`).

**Step 5: Add `if` / `else if` / `else` parsing**

New IR variant needed first (see Task 3). For parsing:
```rust
Some(Token::Ident(ref s)) if s == "if" => self.parse_if(),
```

`parse_if`:
- Consume `if`
- Consume `(` (optional — be lenient)
- Parse condition expression
- Consume `)` (if `(` was consumed)
- Consume `{`
- Parse body statements
- Consume `}`
- Check for `else if` or `else`:
  - If next tokens are `else` followed by `if`: recurse
  - If next token is `else`: consume, parse `{` body `}`
  - Otherwise: no else branch

**Step 6: Add `return` statement parsing**

```rust
Some(Token::Ident(ref s)) if s == "return" => self.parse_return(),
```

`parse_return`: consume `return`, parse an identifier (like `SUCCESS`), return `Statement::Return { value: String }`.

**Step 7: Add C-style cast parsing**

In `parse_primary`, if we see `LParen` followed by a type keyword (`double`, `int`, `size_t`) followed by `RParen`, it's a cast:
```rust
Token::LParen => {
    // Peek ahead: is this a cast or a grouped expression?
    if let Some(Token::Ident(ref s)) = self.peek() {
        if matches!(s.as_str(), "double" | "int" | "size_t") {
            let type_tok = self.advance(); // consume type
            self.expect(&Token::RParen);
            let inner = self.parse_primary(); // cast has high precedence
            return Expr::Cast(type_from_str(&type_tok), Box::new(inner));
        }
    }
    // Otherwise it's a grouped expression
    let expr = self.parse_expr();
    self.expect(&Token::RParen);
    expr
}
```

**Step 8: Add logical operators (`&&`, `||`) as new precedence level**

Expression precedence (lowest to highest):
1. `||` (logical or)
2. `&&` (logical and)
3. `==`, `!=`, `<`, `<=`, `>`, `>=` (comparison)
4. `+`, `-` (additive)
5. `*`, `/` (multiplicative)
6. Unary `!`, casts, primary

Add `parse_logical_or` and `parse_logical_and` between `parse_expr` and `parse_comparison`:
```rust
fn parse_expr(&mut self) -> Expr { self.parse_logical_or() }

fn parse_logical_or(&mut self) -> Expr {
    let mut left = self.parse_logical_and();
    while let Some(Token::Op(ref op)) = self.peek() {
        if op != "||" { break; }
        self.advance();
        let right = self.parse_logical_and();
        left = Expr::BinOp(Box::new(left), BinOp::Or, Box::new(right));
    }
    left
}

fn parse_logical_and(&mut self) -> Expr {
    let mut left = self.parse_comparison();
    while let Some(Token::Op(ref op)) = self.peek() {
        if op != "&&" { break; }
        self.advance();
        let right = self.parse_comparison();
        left = Expr::BinOp(Box::new(left), BinOp::And, Box::new(right));
    }
    left
}
```

**Step 9: Add `!` unary prefix**

In `parse_primary`:
```rust
Token::Bang => {
    let inner = self.parse_primary();
    Expr::Not(Box::new(inner))
}
```

**Step 10: Run tests to verify MULT still parses and generates correctly**

Run: `cd tools/ta_codegen && cargo test 2>&1`
Expected: All 10 tests pass (1 unit + 9 integration)

Run: `bash tests/validate.sh 2>&1 | tail -10`
Expected: All 8 validations pass, Rust byte-identical

**Step 11: Commit**

```bash
git add tools/ta_codegen/src/parser/logic.rs
git commit -m "Update parser for C-like syntax: semicolons, parens, C types, if/else, return, casts"
```

---

### Task 3: Extend IR for new statement/expression types

**Files:**
- Modify: `tools/ta_codegen/src/ir.rs`

**Step 1: Add new Statement variants**

```rust
pub enum Statement {
    VarDecl { var_type: VarType, name: String, init: Option<Expr> },  // init now optional
    Assign { target: Expr, value: Expr },
    While { condition: Expr, body: Vec<Statement> },
    If { condition: Expr, then_body: Vec<Statement>, else_body: Vec<Statement> },
    Return { value: String },  // e.g., "SUCCESS"
}
```

Note: `VarDecl.init` changes from `Expr` to `Option<Expr>` to support declarations without initializer (`double tempReal;`).

**Step 2: Add new Expr variants and BinOp variants**

```rust
pub enum Expr {
    // ... existing variants ...
    Not(Box<Expr>),  // logical negation
}

pub enum BinOp {
    // ... existing variants ...
    NotEq,
    And,  // &&
    Or,   // ||
}
```

**Step 3: Build and verify**

Run: `cd tools/ta_codegen && cargo build 2>&1`
Expected: Compiler errors in backends that match on `Statement` / `BinOp` — this is expected. Fix with placeholder arms:

In each backend's `render_statement`:
```rust
Statement::If { .. } => todo!("if statement"),
Statement::Return { .. } => todo!("return statement"),
```

In each backend's `render_expr` for `BinOp`:
```rust
BinOp::NotEq => "!=",
BinOp::And => "&&",
BinOp::Or => "||",
```

And for `Expr::Not`:
```rust
Expr::Not(inner) => format!("!({})", render_expr(inner, ...)),
```

Run: `cd tools/ta_codegen && cargo test 2>&1`
Expected: All existing tests pass (the `todo!()` arms aren't hit by MULT)

**Step 4: Commit**

```bash
git add tools/ta_codegen/src/ir.rs tools/ta_codegen/src/backends/
git commit -m "Extend IR with If, Return, Not, And, Or, NotEq for SMA support"
```

---

### Task 4: Write SMA definition files

**Files:**
- Create: `ta_func_defs/sma/sma.yaml`
- Create: `ta_func_defs/sma/sma.logic`

**Step 1: Write sma.yaml**

```yaml
name: SMA
group: Overlap Studies
description: Simple Moving Average
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

**Step 2: Write sma.logic**

This is ONLY the algorithm (the `int_sma` body). The generator handles param validation, lookback adjustment, and the public/private split.

```c
double periodTotal = 0.0;
double tempReal;
size_t i;
size_t outIdx;
size_t trailingIdx;
size_t lookbackTotal;

lookbackTotal = (size_t)(optInTimePeriod - 1);

if( startIdx < lookbackTotal ) {
    startIdx = lookbackTotal;
}
if( startIdx > endIdx ) {
    outBegIdx = 0;
    outNBElement = 0;
    return SUCCESS;
}

periodTotal = 0.0;
trailingIdx = startIdx - lookbackTotal;
i = trailingIdx;

if( optInTimePeriod > 1 ) {
    while( i < startIdx ) {
        periodTotal += (double)inReal[i];
        i = i + 1;
    }
}

outIdx = 0;
while( i <= endIdx ) {
    periodTotal += (double)inReal[i];
    i = i + 1;
    tempReal = periodTotal;
    periodTotal -= (double)inReal[trailingIdx];
    trailingIdx = trailingIdx + 1;
    outReal[outIdx] = tempReal / (double)optInTimePeriod;
    outIdx = outIdx + 1;
}

outNBElement = outIdx;
outBegIdx = startIdx;
```

**Step 3: Commit**

```bash
git add ta_func_defs/sma/
git commit -m "Add SMA function definition: sma.yaml + sma.logic"
```

---

### Task 5: Update all 5 backends to handle If and Return

**Files:**
- Modify: `tools/ta_codegen/src/backends/c.rs`
- Modify: `tools/ta_codegen/src/backends/rust_lang.rs`
- Modify: `tools/ta_codegen/src/backends/java.rs`
- Modify: `tools/ta_codegen/src/backends/dotnet.rs`
- Modify: `tools/ta_codegen/src/backends/swig.rs`

**Step 1: Update C backend**

In `render_statement`, replace `todo!()` with actual implementations:

For `Statement::If`:
```rust
Statement::If { condition, then_body, else_body } => {
    let mut out = format!("{}if( {} )\n{}{{\n", pad, render_expr(condition, sp), pad);
    for s in then_body {
        out.push_str(&render_statement(s, indent + 3, sp));
    }
    out.push_str(&format!("{}}}\n", pad));
    if !else_body.is_empty() {
        // Check if else_body is a single If (else-if chain)
        if else_body.len() == 1 && matches!(&else_body[0], Statement::If { .. }) {
            out.push_str(&format!("{}else ", pad));
            out.push_str(&render_statement(&else_body[0], indent, sp).trim_start());
        } else {
            out.push_str(&format!("{}else\n{}{{\n", pad, pad));
            for s in else_body {
                out.push_str(&render_statement(s, indent + 3, sp));
            }
            out.push_str(&format!("{}}}\n", pad));
        }
    }
    out
}
```

For `Statement::Return`:
```rust
Statement::Return { value } => {
    let mapped = match value.as_str() {
        "SUCCESS" => "TA_SUCCESS",
        "BAD_PARAM" => "TA_BAD_PARAM",
        _ => value.as_str(),
    };
    format!("{}return {};\n", pad, mapped)
}
```

Also: the C backend currently appends `return TA_SUCCESS;` unconditionally. For SMA, the logic file already has explicit returns for early exits and the final return is implicit. Update `gen_func` to NOT emit the hardcoded final `return TA_SUCCESS;` if the body already ends with a Return statement — OR keep it and let the logic file omit the final return (since the generator adds it). Keep current behavior: generator always appends `return TA_SUCCESS;` at the end, logic file only uses `return` for early exits.

**Step 2: Update Rust backend**

Same pattern but with Rust syntax:
- `if condition {` (no parens in Rust)
- `return RetCode::Success;`
- Deref pattern for `outBegIdx`/`outNBElement` assignments inside if-bodies

For `Statement::Return`:
```rust
Statement::Return { value } => {
    let mapped = match value.as_str() {
        "SUCCESS" => "RetCode::Success",
        "BAD_PARAM" => "RetCode::BadParam",
        _ => value,
    };
    format!("{}return {};\n", pad, mapped)
}
```

The Rust backend also needs to handle the optional param validation + lookback + startIdx adjustment scaffolding that the generator adds automatically. This requires updating `gen_func` to:
1. Emit param default/range validation (from YAML `optional_inputs`)
2. Emit `self.int_{func}(...)` call in public function
3. Generate `int_{func}` private function with `mut startIdx`
4. The logic body goes inside `int_{func}`

**Step 3: Update Java backend**

Similar to C but: `RetCode.Success`, `MInteger` for outputs, method signatures.

**Step 4: Update .NET backend**

The .NET backend generates header declarations, not full implementations. Needs optional param in signature.

**Step 5: Update SWIG backend**

Needs optional param typemap markers (e.g., `OPT_INT`).

**Step 6: Run MULT tests to verify no regression**

Run: `cd tools/ta_codegen && cargo test 2>&1`
Expected: All existing MULT tests still pass

**Step 7: Commit**

```bash
git add tools/ta_codegen/src/backends/
git commit -m "Update all backends with If/Return rendering + SMA scaffolding"
```

---

### Task 6: Generate SMA and validate against reference

**Files:**
- Modify: `tools/ta_codegen/src/main.rs` (if needed)
- Modify: `tools/ta_codegen/tests/integration_test.rs`
- Modify: `tools/ta_codegen/tests/validate.sh`

**Step 1: Run the generator for SMA**

Run: `cd tools/ta_codegen && cargo run -- generate --func=SMA 2>&1`
Expected: Files created in `ta_codegen_output/rust/sma.rs`, etc.

**Step 2: Diff against Rust reference**

Run: `diff ta_codegen_output/rust/sma.rs rust/src/ta_func/sma.rs`

Iterate on the Rust backend until the diff is clean (or as close as possible). The reference is `rust/src/ta_func/sma.rs` — the file generated by the existing gen_code system.

Key things to get right:
- The public `sma()` function with param validation
- The private `int_sma()` function with the algorithm
- The `sma_s()` / `int_sma_s()` single-precision variants
- `sma_lookback()` with param validation and `optInTimePeriod - 1`
- Doc comments matching the reference format
- `mut startIdx` in private function signature
- `(inReal[i]) as f64` cast pattern
- `(*outBegIdx) = startIdx` deref pattern

**Step 3: Add SMA integration tests**

Add to `integration_test.rs`:
```rust
fn load_sma() -> ir::FuncDef {
    let base = Path::new(env!("CARGO_MANIFEST_DIR"));
    let yaml_path = base.join("../../ta_func_defs/sma/sma.yaml");
    let logic_path = base.join("../../ta_func_defs/sma/sma.logic");
    // ... same pattern as load_mult()
}

#[test]
fn test_parse_sma_yaml() {
    let func = load_sma();
    assert_eq!(func.name, "SMA");
    assert_eq!(func.inputs.len(), 1);
    assert_eq!(func.optional_inputs.len(), 1);
    assert_eq!(func.optional_inputs[0].default, Some(30));
}

#[test]
fn test_sma_rust_backend_matches_reference() {
    // diff against rust/src/ta_func/sma.rs
}

#[test]
fn test_sma_all_backends_generate() {
    let func = load_sma();
    let c = backends::c::generate(&func);
    let rust = backends::rust_lang::generate(&func);
    let java = backends::java::generate(&func);
    assert!(!c.is_empty());
    assert!(!rust.is_empty());
    assert!(!java.is_empty());
}
```

**Step 4: Update validate.sh**

Add SMA reference diff alongside MULT.

**Step 5: Run full validation**

Run: `cd tools/ta_codegen && cargo test && bash tests/validate.sh`
Expected: All tests pass, SMA Rust output matches reference

**Step 6: Commit**

```bash
git add ta_codegen_output/ tools/ta_codegen/tests/
git commit -m "SMA generates for all backends, Rust output matches gen_code reference"
```

---

### Task 7: Add SMA to JSON-RPC server

**Files:**
- Modify: `tools/ta_codegen/src/server.rs`

**Step 1: Add SMA handler**

```rust
"TA_SMA" => handle_sma(&core, params),
"TA_SMA_Lookback" => handle_sma_lookback(&core, params),
```

`handle_sma` reads `startIdx`, `endIdx`, `inReal` (single array), `optInTimePeriod` from params, calls `core.sma(...)`, returns results.

**Step 2: Test JSON-RPC**

Run:
```bash
echo '{"method":"TA_SMA","params":{"startIdx":0,"endIdx":4,"inReal":[1,2,3,4,5],"optInTimePeriod":3}}' | cargo run --release -- serve 2>/dev/null
```
Expected: `{"outBegIdx":2,"outNBElement":3,"outReal":[2.0,3.0,4.0],"retCode":0}`

**Step 3: Commit**

```bash
git add tools/ta_codegen/src/server.rs
git commit -m "Add SMA to JSON-RPC validation server"
```

---

### Task 8: Final validation and cleanup

**Step 1: Run full test suite**

Run: `cd tools/ta_codegen && cargo test && bash tests/validate.sh`
Expected: All tests pass, both MULT and SMA validated

**Step 2: Verify MULT didn't regress**

Run: `diff ta_codegen_output/rust/mult.rs rust/src/ta_func/mult.rs`
Expected: Byte-identical (no diff)

**Step 3: Commit generated output**

```bash
git add ta_codegen_output/
git commit -m "Update generated output: MULT + SMA for all backends"
```

---

## Execution Notes

- **Tasks 2 and 3 are tightly coupled** — the parser needs the new IR types, and the IR changes break backends. Consider doing Tasks 2+3 together.
- **Task 5 is the largest task** — the Rust backend needs the most work because it generates the full public/private function split with param validation scaffolding. The other backends are simpler.
- **Task 6 is iterative** — expect to loop between diffing output and tweaking the Rust backend several times before getting a byte-identical match.
- **The key reference file** is `rust/src/ta_func/sma.rs` — that's what the existing gen_code produces and what we need to match.
