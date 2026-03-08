# ta_regtest + ta_codegen Multi-Language Verification Design (v2)

## Goal

Verify ta_codegen's generated code in ALL 5 target languages (C, Rust, Java, .NET, SWIG/Python) against the C reference implementation. Reuse ta_regtest's existing comprehensive test infrastructure (`doRangeTest`) instead of writing separate test cases.

## Architecture

```
ta_regtest --codegen[=lang]
    |
    +-- For each language (or just one if specified):
    |
    |   1. Spawn: ta_codegen serve --lang=<lang>
    |   2. Run full test suite using doRangeTest() callbacks
    |      - Each callback calls C function (reference)
    |      - Also sends same inputs via JSON-RPC to codegen serve
    |      - Compares outputs element-by-element
    |   3. Shut down codegen serve
    |   4. Report results
    |
    +-- Next language (sequential, one at a time)
```

## Two Sides

### ta_regtest side (C, in ta_regtest codebase)

**New file: `test_codegen.c` (replaces current version)**

Defines `RangeTestFunction` callbacks for each supported TA function. Each callback:
1. Calls the C function with the given startIdx/endIdx (fills output buffer for doRangeTest validation)
2. Builds a JSON-RPC request with the same inputs
3. Sends to codegen pipe, reads response
4. Compares C output vs codegen output (retCode, outBegIdx, outNBElement, outReal[])
5. Returns the C retCode (so doRangeTest can do its own range coherency validation)

The opaqueData struct carries: input arrays, optional parameters, function name, AND the CodegenPipe pointer.

**Entry point: `test_codegen()`**

```
for each language in [c, rust, java, dotnet, swig]:
    codegen_pipe_open(&cp, "./ta_codegen", language)
    for each supported function:
        doRangeTest(codegen_range_callback_XXX, unstId, &params, nbOutput, tolerance)
    codegen_pipe_close(&cp)
```

This gives us the FULL doRangeTest coverage (every startIdx/endIdx combination, unstable period testing, coherency checks) PLUS codegen verification at every single call.

**Modification to `codegen_pipe_open()`**: Takes a language parameter, passes `--lang=<lang>` to ta_codegen serve.

### ta_codegen side (Rust, in tools/ta_codegen/)

**`ta_codegen serve --lang=<lang>`**

The serve command becomes a dispatcher:
- `--lang=rust`: Execute functions from the generated Rust code directly (current behavior)
- `--lang=c`: Spawn a compiled C server binary, proxy JSON-RPC to it
- `--lang=java`: Spawn a Java process, proxy JSON-RPC to it
- `--lang=dotnet`: Spawn a dotnet process, proxy JSON-RPC to it
- `--lang=swig`: Spawn a Python process, proxy JSON-RPC to it

OR (simpler): ta_codegen just tells ta_regtest the path to the right binary, and ta_regtest spawns it directly. Each language's server is a standalone executable/script.

**`ta_codegen build [--lang=<lang>]`**

Compiles/packages each language's server:
- **C**: `gcc -o ta_codegen_serve_c serve_main.c ta_SMA.c ta_RSI.c ... -lm`
- **Rust**: `cargo build --release` (current behavior, produces ta_codegen binary with serve)
- **Java**: `javac *.java && jar cf ta_codegen_serve.jar ...`
- **.NET**: `dotnet build`
- **SWIG/Python**: `python setup.py build_ext` (compiles SWIG bindings), server is a generated .py script

**Generated server wrappers per language:**

ta_codegen auto-generates a thin JSON-RPC server for each language since it knows every function's signature. Each server:
1. Reads a JSON line from stdin
2. Parses method name and params
3. Calls the generated function
4. Writes JSON response to stdout
5. Loop

These are generated alongside the function code — one more output file per language.

## JSON-RPC Protocol (unchanged)

Request: `{"method": "TA_SMA", "params": {"startIdx": 0, "endIdx": 251, "inReal": [...], "optInTimePeriod": 30}}\n`

Response: `{"retCode": 0, "outBegIdx": 29, "outNBElement": 223, "outReal": [...]}\n`

Error: `{"error": "Unknown method: TA_XXX"}\n`

All languages speak the same protocol. ta_regtest doesn't know or care which language is on the other end.

## CLI

```
./ta_regtest --codegen           # Test all languages sequentially
./ta_regtest --codegen=rust      # Test just Rust
./ta_regtest --codegen=java      # Test just Java
./ta_regtest --function=SMA --codegen=rust  # Filter by function too
```

## What Changes (from current implementation)

### Keep
- `codegen_pipe.h/c` — subprocess management (add language param)
- `ta_error_number.h` — codegen error codes
- CMake `ta_codegen_bin` target

### Replace
- `test_codegen.c` — rewrite to use doRangeTest callbacks instead of hand-written test cases
- `test_codegen.h` — update signature

### Add (ta_codegen side)
- `--lang` flag to `ta_codegen serve`
- `ta_codegen build` command
- Generated JSON-RPC server wrappers for C, Java, .NET, SWIG/Python
- Server generation code in ta_codegen's backend modules

## Comparison Strategy

Inside each doRangeTest callback:
1. Call C function → fills output buffer (doRangeTest uses this for its own validation)
2. Send same inputs to codegen pipe → get JSON response
3. Compare retCode, outBegIdx, outNBElement, outReal[] with epsilon tolerance
4. If mismatch → print details, return error code
5. If codegen returns `{"error": "Unknown method"}` → skip (don't fail)

This means every (startIdx, endIdx) pair tested by doRangeTest also gets codegen verification. For a function with 252 data points, that's thousands of calls per function per language.

## Performance

Sequential language testing avoids resource contention. Each language gets a full test pass before the next starts. The JSON-RPC overhead (serialization + pipe I/O) is microseconds per call — negligible compared to the computation.

Estimated per-language: ~30 seconds for 3 functions with full range testing. 5 languages = ~2.5 minutes total.

## Constraints

- Zero changes to existing test files (test_ma.c, test_rsi.c, etc.)
- Zero new library dependencies in ta_regtest
- Existing ta_regtest behavior unchanged without `--codegen`
- POSIX only (macOS/Linux)
- Each language server is auto-generated by ta_codegen (not hand-written)
