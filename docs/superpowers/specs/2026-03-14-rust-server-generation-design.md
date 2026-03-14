# Rust JSON-RPC Server Generation

## Problem

The ta_codegen pipeline generates JSON-RPC servers for C, Java, and .NET — all 163 indicators pass regression tests via `ta_regtest --codegen`. Rust is skipped with "no server target". The Rust backend already generates indicator implementations as methods on `Core` in `rust/src/ta_func/`, but there's no server harness to expose them over the JSON-RPC protocol.

## Goal

Generate a Rust JSON-RPC server binary that passes all 163 indicators in `ta_regtest --codegen --language=rust`.

## Reference

- C server: `server_gen.rs::generate_c_server` — the reference architecture
- Java server: `server_gen.rs::generate_java_server` — similar pattern
- Generated Rust indicators: `rust/src/ta_func/*.rs` — the functions to dispatch to
- ta_regtest protocol: `src/tools/ta_regtest/CLAUDE.md` — JSON-RPC format

---

## Architecture

The Rust server is a **binary target** inside the existing `rust/` crate. `ta_codegen` generates `rust/src/bin/ta_codegen_serve.rs` — a single file containing the JSON-RPC dispatch loop. It imports `Core`, `RetCode`, `FuncUnstId`, and `Compatibility` from the library crate.

**Dependencies:** Add `serde_json` to `rust/Cargo.toml`.

**Build:** `cargo build --release --bin ta_codegen_serve` from `rust/`. The `ta_codegen build --backend=rust` command runs this and copies the binary to `bin/ta_codegen_serve_rust`.

---

## Generic Type Dispatch

Rust indicator functions are generic: `fn sma<T: TaFloat>(...)`. The server dispatches with explicit `f64` turbofish: `core.sma::<f64>(...)`. This matches the other servers which only test double precision through the JSON-RPC protocol.

---

## JSON-RPC Protocol

Identical to C/Java/.NET — no protocol changes.

### Request

```json
{"method":"TA_SMA","params":{"startIdx":0,"endIdx":251,"inReal":[...],"optInTimePeriod":30}}
```

### Response

```json
{"retCode":0,"outBegIdx":29,"outNBElement":222,"outReal":[...],"timing_ns":1500}
```

### Multi-output

```json
{"retCode":0,"outBegIdx":14,"outNBElement":50,"outReal":[...],"outReal1":[...],"outReal2":[...],"timing_ns":2000}
```

### Integer output

```json
{"retCode":0,"outBegIdx":14,"outNBElement":50,"outInteger":[...],"timing_ns":1000}
```

### Special methods

- `list_functions` — returns `{"functions":["TA_SMA","TA_RSI",...]}`
- `set_unstable_period` — accepts `{"id":N,"period":N}`. Map `id` (i64) to `FuncUnstId` via `match`. **Must reject** `id >= FuncUnstAll` (value 24) to prevent out-of-bounds panic — `FuncUnstAll` is used only to size the internal array, not as a valid dispatch target. Cast `period` to `i32` before calling `core.set_unstable_period(func_unst_id, period as i32)`.
- `set_compatibility` — accepts `{"mode":N}`. Map integer to enum: `0 => Compatibility::Default`, `1 => Compatibility::Metastock`. Call `core.set_compatibility(compat)`.

### Input naming

Matches what `expand_input_names()` produces and what ta_regtest sends:
- Single real input: `"inReal"`
- Multiple real inputs: `"inReal0"`, `"inReal1"`
- Price-expanded inputs: `"inHigh"`, `"inLow"`, `"inClose"`, etc.

### Output naming

Matches the `output_json_key()` function:
- Real outputs: `"outReal"`, `"outReal1"`, `"outReal2"`
- Integer outputs: `"outInteger"`, `"outInteger1"`

---

## Code Generation

### New function: `generate_rust_server()`

Added to `server_gen.rs`, parallel to `generate_c_server` and `generate_java_server`. Generates a single file: `rust/src/bin/ta_codegen_serve.rs`.

### Generated file structure

```rust
use serde_json::{json, Value};
use std::io::{self, BufRead, Write};
use std::time::Instant;
use ta_lib::{Core, RetCode, FuncUnstId, Compatibility};

fn main() {
    let mut core = Core::new();
    let stdin = io::stdin();
    let stdout = io::stdout();
    for line in stdin.lock().lines() {
        let response = handle_request(&mut core, &line.unwrap());
        writeln!(stdout.lock(), "{}", response).unwrap();
    }
}

fn handle_request(core: &mut Core, json_str: &str) -> String {
    let v: Value = serde_json::from_str(json_str).unwrap();
    let method = v["method"].as_str().unwrap_or("");
    match method {
        "list_functions" => { /* return function list */ }
        "set_unstable_period" => { /* set unstable period on core */ }
        "set_compatibility" => { /* set compatibility mode */ }
        "TA_SMA" => dispatch_sma(core, &v["params"]),
        "TA_RSI" => dispatch_rsi(core, &v["params"]),
        // ... one arm per indicator
        _ => json!({"error": "unknown method"}).to_string(),
    }
}

fn dispatch_sma(core: &mut Core, params: &Value) -> String {
    let start_idx = params["startIdx"].as_i64().unwrap_or(0) as usize;
    let end_idx = params["endIdx"].as_i64().unwrap_or(0) as usize;
    let in_real: Vec<f64> = /* parse from params["inReal"] */;
    let opt_in_time_period = params["optInTimePeriod"].as_i64().unwrap_or(0) as i32;
    let mut out_beg_idx: usize = 0;
    let mut out_nb_element: usize = 0;
    let mut out_real = vec![0.0f64; end_idx - start_idx + 1];
    let start = Instant::now();
    let ret_code = core.sma::<f64>(
        start_idx, end_idx, &in_real, opt_in_time_period,
        &mut out_beg_idx, &mut out_nb_element, &mut out_real,
    );
    let timing_ns = start.elapsed().as_nanos();
    // Build JSON response with retCode, outBegIdx, outNBElement, outReal, timing_ns
}
```

### Per-indicator dispatch

Each indicator gets a `dispatch_<name>()` function generated from the `FuncDef` IR:
- Extract input arrays from JSON params (using `serde_json`)
- Extract optional params (int, real, enum)
- Allocate output buffers based on `endIdx - startIdx + 1`
- Call `core.<name>::<f64>(...)` with turbofish
- Handle `RetCode` mapping to integer (0 = Success, etc.)
- Serialize output arrays to JSON response

### Parameter type mapping

| IR Type | JSON Parse | Rust Type |
|---------|-----------|-----------|
| `ParamType::Real` | `as_array()` → `Vec<f64>` | `&[f64]` |
| `ParamType::Price` | Expanded to individual arrays | `&[f64]` per component |
| `OptInput::Integer` | `as_i64()` | `i32` |
| `OptInput::Real` | `as_f64()` | `f64` |
| `OptInput::Enum` | `as_i64()` | `i32` (or enum) |
| Output Real | `Vec<f64>` | `&mut [f64]` |
| Output Integer | `Vec<i32>` | `&mut [i32]` |

### RetCode mapping

The generated code maps `RetCode` to integer for JSON:

```rust
fn retcode_to_int(rc: RetCode) -> i32 {
    match rc {
        RetCode::Success => 0,
        RetCode::BadParam => 2,
        RetCode::OutOfRangeStartIndex => 12,
        RetCode::OutOfRangeEndIndex => 13,
        RetCode::AllocErr => 3,
        RetCode::InternalError => 5000,
    }
}
```

Values must match `ta_defs.h` `TA_RetCode` enum.

---

## Build Integration

### `ta_codegen generate-servers --backend=rust`

In `main.rs`:
1. Replace the "skipping" message (lines 256-258) with a call to `generate_rust_server()`.
2. Add `"rust"` to the default backend list (line 198: `None => vec!["c", "java", "dotnet", "swig"]` → add `"rust"`).
3. Add `"rust"` to the `build_servers` default list too (line 274).

**Output path:** Unlike other backends which write to `ta_codegen_output/{lang}/`, the Rust server writes directly into `rust/src/bin/ta_codegen_serve.rs` because it's a binary target in the existing crate. This is an intentional deviation — the server must live inside the `rust/` crate to import `Core` directly.

### `ta_codegen build --backend=rust`

Run `cargo build --release --bin ta_codegen_serve` in the `rust/` directory. Copy the resulting binary to `bin/ta_codegen_serve_rust`.

### Cargo.toml changes

Add to `rust/Cargo.toml`:

```toml
[[bin]]
name = "ta_codegen_serve"
path = "src/bin/ta_codegen_serve.rs"

[dependencies]
serde_json = "1"
```

### ta_regtest integration

`test_codegen.c` currently has:
```c
static const char *const argv_rust[]  = {"./ta_codegen", "serve", NULL};
```

This expects a `serve` subcommand on `ta_codegen`, which is not our approach. **Update** `test_codegen.c` line 28 to:
```c
static const char *const argv_rust[]  = {"./ta_codegen_serve_rust", NULL};
```

This matches the standalone binary pattern used by C (`./ta_codegen_serve_c`) and Java (`java -cp ...`).

---

## Verification

After implementation:

```bash
cd tools/ta_codegen && cargo run -- generate-servers --backend=rust
cd tools/ta_codegen && cargo run -- build --backend=rust
cd bin && ../cmake-build/bin/ta_regtest --codegen-only --language=rust
```

**Success criteria:** All 163 indicators pass — matching C, Java, and .NET.

---

## Risk

**Low-medium.** The indicator implementations already exist and work (the Rust backend generates them). The server is a thin JSON-RPC harness around existing `Core` methods. The main risk is parameter mapping edge cases (MAType enums, unstable periods, candle settings) — but we've already solved all these for the other servers.

**Potential issue:** The Rust `Core` struct may not have all the infrastructure the server needs (e.g., `set_unstable_period` method, `CandleSettings` struct). If so, those need to be added to `rust/src/ta_func/mod.rs` or the relevant module. Check what the Rust `Core` currently exposes before generating the server.
