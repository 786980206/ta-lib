[![Discord chat](https://img.shields.io/discord/1038616996062953554.svg?logo=discord&style=flat-square)](https://discord.gg/Erb6SwsVbH)

[![main nightly tests](https://github.com/TA-Lib/ta-lib/actions/workflows/main-nightly-tests.yml/badge.svg)](https://github.com/TA-Lib/ta-lib/actions/workflows/main-nightly-tests.yml) [![dev nightly tests](https://github.com/TA-Lib/ta-lib/actions/workflows/dev-nightly-tests.yml/badge.svg)](https://github.com/TA-Lib/ta-lib/actions/workflows/dev-nightly-tests.yml)

# TA-Lib - Technical Analysis Library
This is now the official home for C/C++ TA-Lib (instead of SourceForge).

More info [https://ta-lib.org](https://ta-lib.org)

# You want a new TA Function implemented?
First step is to document the algorithm, with a sample of input/output in the [ta-lib-proposal-drafts]( https://github.com/TA-Lib/ta-lib-proposal-drafts ) repos.

# Development

## Prerequisites

- CMake 3.18+
- C compiler (clang or gcc)
- Rust toolchain (`rustup`)

Optional (for cross-language server testing):
- JDK (`javac` + `java`)
- .NET SDK (`dotnet`)
- Python 3 + SWIG (`swig`, `python3`)

## Building

```bash
make                  # Build library + all tools
make ta_regtest       # Build just the test runner
make gen_code         # Build the legacy C code generator
make ta_codegen       # Build the Rust codegen tool
make servers          # Generate + compile JSON-RPC language servers
```

Built binaries go to `bin/`. CMake is configured automatically on first run.

## Running Tests

```bash
make test             # C reference tests only (quick)
make regtest          # Full pipeline: servers + C tests + cross-language verification
make regtest-only     # Codegen verification only (skip C reference tests)
```

`make regtest` does three things:
1. Generates JSON-RPC server source for C, Java, .NET, and Python
2. Compiles the servers into `bin/`
3. Runs `ta_regtest --codegen` — C reference tests + cross-language comparison

### Filtering

For more control, run `ta_regtest` directly from `bin/`:

```bash
cd bin
./ta_regtest                                               # C reference tests only
./ta_regtest --codegen                                     # C tests + all-language codegen
./ta_regtest --codegen-only                                # Codegen only (all languages)
./ta_regtest --codegen --language=c,rust                   # Filter to specific languages
./ta_regtest --codegen --function=RSI,SMA                  # Filter to specific functions
./ta_regtest --codegen-only --language=c --function=BBANDS # Combine filters
```

## Code Generation

TA-Lib uses two code generation systems:

| Tool | Language | What it generates |
|------|----------|-------------------|
| `gen_code` (C) | C | Regenerates indicator source files, Java bindings, .NET wrappers |
| `ta_codegen` (Rust) | Rust | Rust indicator implementations, JSON-RPC test servers |

```bash
# Legacy C generator (run from bin/)
cd bin && ../cmake-build/bin/gen_code

# Rust codegen tool (run from tools/ta_codegen/)
cd tools/ta_codegen
cargo run -- generate                            # Generate indicator code for all backends
cargo run -- generate --func=SMA --backend=rust  # Specific function + backend
cargo run -- generate-servers                    # Generate JSON-RPC servers
cargo run -- build                               # Compile servers
cargo run -- extract                             # Extract indicators from C source → YAML
```

Generated output goes to `ta_codegen_output/` organized by language.

## Architecture

See [CLAUDE.md](CLAUDE.md) for detailed architecture docs, macro system reference, and cross-language development workflow.
