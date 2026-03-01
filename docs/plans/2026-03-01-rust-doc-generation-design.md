# Rust Doc Comment Generation

## Goal

Generate comprehensive `///` doc comments for all Rust functions, eliminating `missing_docs` warnings and providing useful API documentation with working code examples (doctests).

## Design

### Doc structure per function

**Main function (`sma`)** gets the full treatment:

```rust
/// Simple Moving Average
///
/// # Arguments
///
/// * `startIdx` - Start index for calculation range
/// * `endIdx` - End index for calculation range (inclusive)
/// * `inReal` - Input price series
/// * `optInTimePeriod` - Number of period (default: 30, range: 2..=100000)
/// * `outBegIdx` - First valid output index
/// * `outNBElement` - Number of valid output elements
/// * `outReal` - Output values
///
/// # Returns
///
/// [`RetCode::Success`] on success, or an error code on failure.
///
/// # Example
///
/// ```
/// use ta_lib::ta_func::{Core, RetCode};
///
/// let input = [1.0_f64; 50];
/// let mut out = [0.0_f64; 50];
/// let mut out_beg_idx: usize = 0;
/// let mut out_nb_element: usize = 0;
///
/// let result = Core::sma(
///     0,
///     49,
///     &input,
///     30, // optInTimePeriod (default)
///     &mut out_beg_idx,
///     &mut out_nb_element,
///     &mut out,
/// );
///
/// assert_eq!(result, RetCode::Success);
/// ```
```

**Single precision (`sma_s`)** gets a cross-reference:

```rust
/// Single-precision variant of [`Core::sma`].
```

**Lookback (`sma_lookback`)** gets a short doc with params:

```rust
/// Lookback period for [`Core::sma`].
///
/// # Arguments
///
/// * `optInTimePeriod` - Number of period (default: 30, range: 2..=100000)
```

### Data sources (all from ta_abstract, no new files)

| Doc element | Source |
|-------------|--------|
| Function description | `funcInfo->hint` ("Simple Moving Average") |
| Input param names | `inputParamInfo->paramName` ("inReal") |
| Input types | `inputParamInfo->type` (Real, Integer, Price) |
| Price flags | `inputParamInfo->flags` (Open, High, Low, Close, Volume) |
| OptInput names | `optInputParamInfo->paramName` ("optInTimePeriod") |
| OptInput hints | `optInputParamInfo->hint` ("Number of period") |
| OptInput defaults | `optInputParamInfo->defaultValue` (30) |
| OptInput range | `dataSet->min`, `dataSet->max` (2..=100000) |
| Output param names | `outputParamInfo->paramName` ("outReal") |
| Output types | `outputParamInfo->type` (Real, Integer) |

### Generated example construction (mechanical)

The generator derives everything for the basic example:

- **Array size**: `max(optInput defaults) + 20`, minimum 50
- **Input arrays**: `[1.0_f64; N]` for Real; for Price inputs, separate arrays per component
- **Output arrays**: `[0.0_f64; N]` for Real, `[0_i32; N]` for Integer
- **OptInput values**: use default value with inline comment showing param name
- **endIdx**: array size - 1
- **Assert**: `RetCode::Success`

### Rich example override

If `src/ta_abstract/rust_examples/<name>.txt` exists (e.g., `sma.txt`), the generator uses its contents instead of the mechanical example. The file contains raw Rust code lines (no `///` prefix — the generator adds those).

Example `src/ta_abstract/rust_examples/sma.txt`:
```
use ta_lib::ta_func::{Core, RetCode};

// Calculate 3-period SMA over a simple price series
let close_prices = [1.0, 2.0, 3.0, 4.0, 5.0_f64];
let mut out = [0.0_f64; 5];
let mut out_beg_idx: usize = 0;
let mut out_nb_element: usize = 0;

let result = Core::sma(
    0,                    // startIdx
    4,                    // endIdx
    &close_prices,
    3,                    // optInTimePeriod
    &mut out_beg_idx,
    &mut out_nb_element,
    &mut out,
);

assert_eq!(result, RetCode::Success);
assert_eq!(out_beg_idx, 2);     // first valid output at index 2
assert_eq!(out_nb_element, 3);   // 3 output values
assert!((out[0] - 2.0).abs() < 1e-10); // avg(1,2,3)
assert!((out[1] - 3.0).abs() < 1e-10); // avg(2,3,4)
assert!((out[2] - 4.0).abs() < 1e-10); // avg(3,4,5)
```

Functions without a rich example file get the generated basic example.

### Static docs (not generated)

These go in the template/hand-maintained files:

- **`mod.rs`**: Module-level `//!` doc for `ta_func` module, `Core` struct, `RetCode` enum and variants
- **`lib.rs`**: Crate-level `//!` doc

### Implementation location

New function `printRustFuncDoc` in `gen_rust.c`, called from `gen_code.c` at three points:

1. Before `printRustDoublePrecisionFunctionSignature` — full doc with example
2. Before `printRustSinglePrecisionFunctionSignature` — cross-reference one-liner
3. Before `printRustLookbackFunctionSignature` — short doc with params

The function takes the same `TA_FuncInfo` pointer that all other print functions use, plus a `docType` enum to select full/cross-ref/lookback.

### Warnings eliminated

All 17 current `missing_docs` warnings will be resolved:
- 2 module warnings (`ta_func`, `mult`, `sma`) — static docs in mod.rs
- 1 struct warning (`Core`) — static doc in mod.rs
- 6 enum warnings (`RetCode` + variants) — static doc in mod.rs
- 8 function warnings (3 per indicator) — generated doc comments
