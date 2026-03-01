# Rust Integration Changelog

Tracking progress of TA-Lib's Rust code generation pipeline.

> **Note:** Diff links point to commits on the `dev` branch. Push `dev` to GitHub for links to resolve.

---

## 2026-03-01 -- SMA complete with full validation and tests

* [509d6af](https://github.com/TA-Lib/ta-lib/commit/509d6af2) Removed `TA_FUNC_NO_RANGE_CHECK` which was disabling ALL validation for Rust (caused MULT test regressions)
* [509d6af](https://github.com/TA-Lib/ta-lib/commit/509d6af2) Added `CAST_TO_I32` macro to `printOptInputValidation` so `(int)` casts become cross-language
* [509d6af](https://github.com/TA-Lib/ta-lib/commit/509d6af2) Renamed `CAST_TO_USIZE` to `CAST_TO_INDEX` (concept-based naming -- each language maps to its own index type)
* [509d6af](https://github.com/TA-Lib/ta-lib/commit/509d6af2) Removed redundant `OUTPUT_F64` macro, consolidated to `CAST_TO_F64`
* [509d6af](https://github.com/TA-Lib/ta-lib/commit/509d6af2) Added `FUNCTION_CALL` / `FUNCTION_CALL_DOUBLE` macros for Rust (needed for SMA internal dispatch)
* [509d6af](https://github.com/TA-Lib/ta-lib/commit/509d6af2) Split Rust `INT_MIN`/`INT_MAX` from Java (`i32::MIN` vs `Integer.MIN_VALUE`)
* [509d6af](https://github.com/TA-Lib/ta-lib/commit/509d6af2) Added `mut` to lookback function params in gen_rust.c (validation assigns default values)
* [509d6af](https://github.com/TA-Lib/ta-lib/commit/509d6af2) Refactored `RUST_SINGLE_FUNC` to `RUST_SUPPORTED_FUNCS` for multi-function support
* [95f1413](https://github.com/TA-Lib/ta-lib/commit/95f1413d) SMA tests: basic, single precision, lookback, partial range
* [1132d92](https://github.com/TA-Lib/ta-lib/commit/1132d920) Updated CLAUDE.md with `CAST_TO_INDEX` macro docs and SMA status
* [66fd2f8](https://github.com/TA-Lib/ta-lib/commit/66fd2f88) Removed empty `#if defined(_RUST)` wrapper in gen_code.c Section 4 — Rust now goes through `printFunc(validationCode=1)` like all other languages
* [66fd2f8](https://github.com/TA-Lib/ta-lib/commit/66fd2f88) Added `!defined(_RUST)` to null-pointer check guards (alongside `!defined(_JAVA)`) — Rust doesn't need null checks
* [66fd2f8](https://github.com/TA-Lib/ta-lib/commit/66fd2f88) Added `mut` to optional input params in both double and single precision Rust signatures
* [66fd2f8](https://github.com/TA-Lib/ta-lib/commit/66fd2f88) SMA error condition tests: BadParam for period 0/1/100001, OutOfRangeEndIndex, default period via i32::MIN (double + single precision)
* [66fd2f8](https://github.com/TA-Lib/ta-lib/commit/66fd2f88) Replaced `test_sma_period_1` with `test_sma_minimum_period` (period=2, the actual minimum)
* All 13 Rust tests passing (6 MULT + 7 SMA)

## 2026-01-07 -- Document generated code philosophy and macro-first approach

* [Diff: 121b485](https://github.com/TA-Lib/ta-lib/commit/121b4852)
* Major CLAUDE.md update documenting the code generation pipeline
* Macro system reference, type mappings, build commands
* Cross-language development workflow guidelines

## 2026-01-06 -- Remove naked conditionals for Rust compatibility

* [Diff: 02a2d4e](https://github.com/TA-Lib/ta-lib/commit/02a2d4ec)
* Added curly braces to all bare if/else in generated validation code
* Rust requires braces on all conditionals; change is syntactically identical in C/Java/.NET
* Affects all generated `ta_*.c` and `Core.java` files

## 2025-06-22 -- MULT passes all tests

* [Diff: 35a19bb...9ba6d22](https://github.com/TA-Lib/ta-lib/compare/35a19bbc...9ba6d22e)
* Added MULT test suite (double precision, single precision, error conditions, lookback, partial range, usize validation)
* Fixed Rust compilation warnings for unused variables and index validation
* Updated ta_MULT.c with new loop variable macros

## 2025-06-21 -- Rust functions made public, cargo fix/fmt automated

* [Diff: be62763...1562ce8](https://github.com/TA-Lib/ta-lib/compare/be62763a...1562ce87)
* Made generated Rust functions `pub` on `Core` struct
* Added `cargo fix` and `cargo fmt` as post-generation steps in gen_code
* Fixed usize type issues in generated code

## 2025-06-09 -- MULT compiles in Rust

* [Diff: 2c95c85...97e7908](https://github.com/TA-Lib/ta-lib/compare/2c95c858...97e7908d)
* Capital C `Core` struct
* Added FOR_EACH_OUTPUT, VALUE_HANDLE, DECLARE_*_VAR macros
* MULT source updated to use cross-language macros
* First successful `cargo check` on generated Rust code

## 2025-06-08 -- Macro system and Cargo setup

* [Diff: a670254...469f8ed](https://github.com/TA-Lib/ta-lib/compare/a6702544...469f8ed7)
* Added curly braces to all generated if/else (Rust requirement, valid in all languages)
* Created loop and variable declaration macros in ta_defs.h
* Added enum and value handle macros for Rust
* Created `rust/Cargo.toml` and `rust/src/lib.rs`
* Reformatted and re-indented gen_rust.c

## 2025-06-04 -- Claude-assisted development begins

* [Diff: 6d68e4a](https://github.com/TA-Lib/ta-lib/commit/6d68e4a1)
* Added CLAUDE.md project instructions
* Addressed TODOs in gen_rust.c

## 2025-02-15 -- gen_rust.c split and input validation

* [Diff: 722a704...64ed4fd](https://github.com/TA-Lib/ta-lib/compare/722a704c...64ed4fd9)
* Moved Rust code generation to dedicated `gen_rust.c` file
* Added input array validation for Rust
* Start/end index parameters appearing in generated signatures

## 2025-01-22 -- Function name generation

* [Diff: a7299da...66e6507](https://github.com/TA-Lib/ta-lib/compare/a7299da7...66e65076)
* WIP Rust function name generation (snake_case conversion)
* Removed extra memcopy naming for Rust

## 2025-01-05 -- Rust function templating

* [Diff: 470ac69...eabc13b](https://github.com/TA-Lib/ta-lib/compare/470ac693...eabc13b8)
* First pass at templating Rust function output from gen_code
* Added `outputForRust` argument plumbing

## 2024-12-31 -- Initial Rust preprocessor support

* [Diff: 6ec3d77...42bbc3d](https://github.com/TA-Lib/ta-lib/compare/6ec3d779...42bbc3d3)
* Added `_RUST` define to mcpp preprocessor calls
* Regenerated ta_func files with Rust preprocessing support
* Foundation for the entire Rust code generation pipeline
