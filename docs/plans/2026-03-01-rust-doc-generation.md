# Rust Doc Comment Generation - Implementation Plan

> **For Claude:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Generate comprehensive `///` doc comments for all Rust functions from ta_abstract metadata, eliminating `missing_docs` warnings and providing working doctests.

**Architecture:** Add a `printRustFuncDoc` function to `gen_rust.c` that emits `///` doc comments using the same `TA_FuncInfo` metadata that `printFuncHeaderDoc` already uses for C. Call it from `gen_code.c` before each Rust signature. Rich hand-written examples override generated ones when present.

**Tech Stack:** C (generator), Rust (output), ta_abstract metadata structs

---

### Task 1: Add static docs to mod.rs template

Static doc comments for `RetCode`, `Core`, and the module itself. These don't need the generator — they go in the template.

**Files:**
- Modify: `src/ta_abstract/templates/ta_func_mod.rs.template`

**Step 1: Edit the template to add doc comments**

Replace lines 39-51 of `ta_func_mod.rs.template` with:

```rust
/// Return codes for TA-Lib function calls.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RetCode {
    /// Function completed successfully.
    Success,
    /// One or more parameters are invalid.
    BadParam,
    /// The start index is out of range.
    OutOfRangeStartIndex,
    /// The end index is out of range or less than start index.
    OutOfRangeEndIndex,
    /// Memory allocation failed.
    AllocErr,
    /// Internal error occurred.
    InternalError,
}

/// Core struct providing access to all TA-Lib technical analysis functions.
///
/// Functions are implemented as static methods. No state is preserved between calls.
///
/// # Example
///
/// ```
/// use ta_lib::ta_func::{Core, RetCode};
///
/// let lookback = Core::sma_lookback(30);
/// assert_eq!(lookback, 29);
/// ```
pub struct Core {}
```

Keep the `%%%GENCODE%%%` line and everything else unchanged.

**Step 2: Rebuild gen_code and regenerate**

```bash
cd /Users/chadfurman/projects/ta-lib/cmake-build && cmake .. -DCMAKE_BUILD_TYPE=Release && make gen_code -j4
cd /Users/chadfurman/projects/ta-lib/bin && ../cmake-build/bin/gen_code
```

**Step 3: Verify mod.rs has doc comments and warnings decreased**

```bash
cd /Users/chadfurman/projects/ta-lib/rust && cargo check 2>&1 | grep "missing_docs" | wc -l
```

Expected: fewer `missing_docs` warnings (was 17, should drop to ~8 — the function-level ones remain).

**Step 4: Run tests to verify no regressions**

```bash
cd /Users/chadfurman/projects/ta-lib/rust && cargo test
```

Expected: all 13 tests pass.

**Step 5: Commit**

```bash
git add src/ta_abstract/templates/ta_func_mod.rs.template rust/src/ta_func/mod.rs
git commit -m "Add doc comments to RetCode, Core, and module in Rust template"
```

---

### Task 2: Add `printRustFuncDoc` for lookback functions

The simplest variant — short doc with cross-reference and optional params.

**Files:**
- Modify: `src/tools/gen_code/gen_rust.c` (add new function)
- Modify: `src/tools/gen_code/gen_code.c` (call it at line ~3411)

**Step 1: Write the `printRustFuncDoc` function skeleton in gen_rust.c**

Add before `printRustLookbackFunctionSignature` (before line 29). This function will handle all three doc types via a `docType` parameter:

```c
/* Doc types for printRustFuncDoc */
#define RUST_DOC_LOOKBACK 0
#define RUST_DOC_MAIN     1
#define RUST_DOC_SINGLE   2

static void printRustFuncDoc(FILE *out,
                             const TA_FuncInfo *funcInfo,
                             int docType)
{
    TA_RetCode retCode;
    unsigned int paramNb;
    const TA_InputParameterInfo *inputParamInfo;
    const TA_OptInputParameterInfo *optInputParamInfo;
    const TA_OutputParameterInfo *outputParamInfo;
    char snakeName[500];

    toLowerSnakeCase(funcInfo->name, snakeName);

    if (docType == RUST_DOC_SINGLE)
    {
        /* Single precision: just a cross-reference */
        fprintf(out, "    /// Single-precision variant of [`Core::%s`].\n", snakeName);
        return;
    }

    if (docType == RUST_DOC_LOOKBACK)
    {
        /* Lookback: short doc with params */
        fprintf(out, "    /// Lookback period for [`Core::%s`].\n", snakeName);
    }
    else
    {
        /* Main function: full description */
        fprintf(out, "    /// %s\n", funcInfo->hint);
    }

    fprintf(out, "    ///\n");
    fprintf(out, "    /// # Arguments\n");
    fprintf(out, "    ///\n");

    if (docType == RUST_DOC_MAIN)
    {
        /* startIdx/endIdx for main function only */
        fprintf(out, "    /// * `startIdx` - Start index for calculation range\n");
        fprintf(out, "    /// * `endIdx` - End index for calculation range (inclusive)\n");

        /* Input parameters */
        for (paramNb = 0; paramNb < funcInfo->nbInput; paramNb++)
        {
            retCode = TA_GetInputParameterInfo(funcInfo->handle, paramNb, &inputParamInfo);
            if (retCode != TA_SUCCESS) return;

            switch (inputParamInfo->type)
            {
            case TA_Input_Price:
                {
                    /* Document each price component */
                    #define PRICE_DOC(upperParam, lowerParam, desc) \
                    if (inputParamInfo->flags & TA_IN_PRICE_##upperParam) \
                        fprintf(out, "    /// * `%s` - %s price series\n", lowerParam, desc);

                    PRICE_DOC(OPEN, "inOpen", "Open")
                    PRICE_DOC(HIGH, "inHigh", "High")
                    PRICE_DOC(LOW, "inLow", "Low")
                    PRICE_DOC(CLOSE, "inClose", "Close")
                    PRICE_DOC(VOLUME, "inVolume", "Volume")
                    PRICE_DOC(OPENINTEREST, "inOpenInterest", "Open interest")

                    #undef PRICE_DOC
                }
                break;
            case TA_Input_Real:
                fprintf(out, "    /// * `%s` - Input price series\n", inputParamInfo->paramName);
                break;
            case TA_Input_Integer:
                fprintf(out, "    /// * `%s` - Input integer series\n", inputParamInfo->paramName);
                break;
            }
        }
    }

    /* Optional input parameters (both lookback and main) */
    for (paramNb = 0; paramNb < funcInfo->nbOptInput; paramNb++)
    {
        retCode = TA_GetOptInputParameterInfo(funcInfo->handle, paramNb, &optInputParamInfo);
        if (retCode != TA_SUCCESS) return;

        switch (optInputParamInfo->type)
        {
        case TA_OptInput_IntegerRange:
            fprintf(out, "    /// * `%s` - %s (default: %d, range: %d..=%d)\n",
                    optInputParamInfo->paramName,
                    optInputParamInfo->hint,
                    (int)optInputParamInfo->defaultValue,
                    ((TA_IntegerRange *)(optInputParamInfo->dataSet))->min,
                    ((TA_IntegerRange *)(optInputParamInfo->dataSet))->max);
            break;
        case TA_OptInput_RealRange:
            fprintf(out, "    /// * `%s` - %s (default: %g)\n",
                    optInputParamInfo->paramName,
                    optInputParamInfo->hint,
                    optInputParamInfo->defaultValue);
            break;
        case TA_OptInput_IntegerList:
        case TA_OptInput_RealList:
            fprintf(out, "    /// * `%s` - %s\n",
                    optInputParamInfo->paramName,
                    optInputParamInfo->hint);
            break;
        }
    }

    if (docType == RUST_DOC_MAIN)
    {
        /* Output parameters */
        fprintf(out, "    /// * `outBegIdx` - First valid output index\n");
        fprintf(out, "    /// * `outNBElement` - Number of valid output elements\n");

        for (paramNb = 0; paramNb < funcInfo->nbOutput; paramNb++)
        {
            retCode = TA_GetOutputParameterInfo(funcInfo->handle, paramNb, &outputParamInfo);
            if (retCode != TA_SUCCESS) return;

            fprintf(out, "    /// * `%s` - Output values\n", outputParamInfo->paramName);
        }

        /* Returns section */
        fprintf(out, "    ///\n");
        fprintf(out, "    /// # Returns\n");
        fprintf(out, "    ///\n");
        fprintf(out, "    /// [`RetCode::Success`] on success, or an error code on failure.\n");
    }
}
```

**Step 2: Call `printRustFuncDoc` for lookback in gen_code.c**

At line ~3411 in gen_code.c, right before `printRustLookbackFunctionSignature`, add:

```c
    print( out, "#elif defined( _RUST )\n" );
    printRustFuncDoc(out, funcInfo, RUST_DOC_LOOKBACK);  /* ADD THIS LINE */
    printRustLookbackFunctionSignature(out, NULL, funcInfo);
```

The `print( out, "#elif defined( _RUST )\n" );` line already exists at line 3411 — insert the new call between it and line 3412.

**Step 3: Rebuild and verify**

```bash
cd /Users/chadfurman/projects/ta-lib/cmake-build && make gen_code -j4
cd /Users/chadfurman/projects/ta-lib/bin && ../cmake-build/bin/gen_code
cd /Users/chadfurman/projects/ta-lib/rust && cargo check 2>&1 | grep "sma_lookback" | grep "missing_docs"
```

Expected: no `missing_docs` warning for `sma_lookback` or `mult_lookback`.

**Step 4: Run tests**

```bash
cd /Users/chadfurman/projects/ta-lib/rust && cargo test
```

Expected: all 13 tests pass.

**Step 5: Verify C/Java output unchanged**

```bash
cd /Users/chadfurman/projects/ta-lib && git diff -- java/src/com/tictactec/ta/lib/Core.java
```

Expected: zero diff (Rust doc comments are inside `#elif defined(_RUST)` blocks).

**Step 6: Commit**

```bash
git add src/tools/gen_code/gen_rust.c src/tools/gen_code/gen_code.c rust/src/ta_func/sma.rs rust/src/ta_func/mult.rs
git commit -m "Add Rust doc comments to lookback functions via printRustFuncDoc"
```

---

### Task 3: Add doc comments to main (double precision) functions

Add the full doc block with `# Arguments`, `# Returns`, and the generated example.

**Files:**
- Modify: `src/tools/gen_code/gen_rust.c` (add example generation to `printRustFuncDoc`)
- Modify: `src/tools/gen_code/gen_code.c` (call at line ~3451)

**Step 1: Add generated example to `printRustFuncDoc`**

After the `# Returns` section in the `RUST_DOC_MAIN` branch, add example generation. Insert this code inside the `if (docType == RUST_DOC_MAIN)` block, after the Returns section:

```c
        /* Example section */
        {
            char examplePath[1024];
            FILE *exampleFile;
            int arraySize;
            int defaultOptVal;
            char lowerName[500];

            /* Check for rich hand-written example */
            toLowerSnakeCase(funcInfo->name, lowerName);
            sprintf(examplePath, ".." PATH_SEPARATOR "src" PATH_SEPARATOR "ta_abstract"
                    PATH_SEPARATOR "rust_examples" PATH_SEPARATOR "%s.txt", lowerName);
            exampleFile = fopen(examplePath, "r");

            fprintf(out, "    ///\n");
            fprintf(out, "    /// # Example\n");
            fprintf(out, "    ///\n");
            fprintf(out, "    /// ```\n");
            fprintf(out, "    /// use ta_lib::ta_func::{Core, RetCode};\n");
            fprintf(out, "    ///\n");

            if (exampleFile)
            {
                /* Inject hand-written example */
                char line[1024];
                while (fgets(line, sizeof(line), exampleFile))
                {
                    /* Remove trailing newline */
                    int len = strlen(line);
                    while (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r'))
                        line[--len] = '\0';

                    if (len == 0)
                        fprintf(out, "    ///\n");
                    else
                        fprintf(out, "    /// %s\n", line);
                }
                fclose(exampleFile);
            }
            else
            {
                /* Generate mechanical example */

                /* Calculate array size from largest optInput default + 20, min 50 */
                arraySize = 50;
                for (paramNb = 0; paramNb < funcInfo->nbOptInput; paramNb++)
                {
                    retCode = TA_GetOptInputParameterInfo(funcInfo->handle, paramNb, &optInputParamInfo);
                    if (retCode != TA_SUCCESS) continue;
                    defaultOptVal = (int)optInputParamInfo->defaultValue;
                    if (defaultOptVal + 20 > arraySize)
                        arraySize = defaultOptVal + 20;
                }

                /* Input arrays */
                for (paramNb = 0; paramNb < funcInfo->nbInput; paramNb++)
                {
                    retCode = TA_GetInputParameterInfo(funcInfo->handle, paramNb, &inputParamInfo);
                    if (retCode != TA_SUCCESS) continue;

                    switch (inputParamInfo->type)
                    {
                    case TA_Input_Price:
                        #define PRICE_EXAMPLE(upperParam, lowerParam) \
                        if (inputParamInfo->flags & TA_IN_PRICE_##upperParam) \
                            fprintf(out, "    /// let %s = [1.0_f64; %d];\n", lowerParam, arraySize);

                        PRICE_EXAMPLE(OPEN, "in_open")
                        PRICE_EXAMPLE(HIGH, "in_high")
                        PRICE_EXAMPLE(LOW, "in_low")
                        PRICE_EXAMPLE(CLOSE, "in_close")
                        PRICE_EXAMPLE(VOLUME, "in_volume")
                        PRICE_EXAMPLE(OPENINTEREST, "in_open_interest")

                        #undef PRICE_EXAMPLE
                        break;
                    case TA_Input_Real:
                        fprintf(out, "    /// let input = [1.0_f64; %d];\n", arraySize);
                        break;
                    case TA_Input_Integer:
                        fprintf(out, "    /// let input = [1_i32; %d];\n", arraySize);
                        break;
                    }
                }

                /* Output arrays */
                for (paramNb = 0; paramNb < funcInfo->nbOutput; paramNb++)
                {
                    retCode = TA_GetOutputParameterInfo(funcInfo->handle, paramNb, &outputParamInfo);
                    if (retCode != TA_SUCCESS) continue;

                    switch (outputParamInfo->type)
                    {
                    case TA_Output_Real:
                        if (funcInfo->nbOutput == 1)
                            fprintf(out, "    /// let mut out = [0.0_f64; %d];\n", arraySize);
                        else
                            fprintf(out, "    /// let mut %s = [0.0_f64; %d];\n",
                                    outputParamInfo->paramName, arraySize);
                        break;
                    case TA_Output_Integer:
                        if (funcInfo->nbOutput == 1)
                            fprintf(out, "    /// let mut out = [0_i32; %d];\n", arraySize);
                        else
                            fprintf(out, "    /// let mut %s = [0_i32; %d];\n",
                                    outputParamInfo->paramName, arraySize);
                        break;
                    }
                }

                fprintf(out, "    /// let mut out_beg_idx: usize = 0;\n");
                fprintf(out, "    /// let mut out_nb_element: usize = 0;\n");
                fprintf(out, "    ///\n");

                /* Function call */
                fprintf(out, "    /// let result = Core::%s(\n", snakeName);
                fprintf(out, "    ///     0,\n");
                fprintf(out, "    ///     %d,\n", arraySize - 1);

                /* Input args */
                for (paramNb = 0; paramNb < funcInfo->nbInput; paramNb++)
                {
                    retCode = TA_GetInputParameterInfo(funcInfo->handle, paramNb, &inputParamInfo);
                    if (retCode != TA_SUCCESS) continue;

                    switch (inputParamInfo->type)
                    {
                    case TA_Input_Price:
                        #define PRICE_ARG(upperParam, lowerParam) \
                        if (inputParamInfo->flags & TA_IN_PRICE_##upperParam) \
                            fprintf(out, "    ///     &%s,\n", lowerParam);

                        PRICE_ARG(OPEN, "in_open")
                        PRICE_ARG(HIGH, "in_high")
                        PRICE_ARG(LOW, "in_low")
                        PRICE_ARG(CLOSE, "in_close")
                        PRICE_ARG(VOLUME, "in_volume")
                        PRICE_ARG(OPENINTEREST, "in_open_interest")

                        #undef PRICE_ARG
                        break;
                    case TA_Input_Real:
                        fprintf(out, "    ///     &input,\n");
                        break;
                    case TA_Input_Integer:
                        fprintf(out, "    ///     &input,\n");
                        break;
                    }
                }

                /* OptInput args */
                for (paramNb = 0; paramNb < funcInfo->nbOptInput; paramNb++)
                {
                    retCode = TA_GetOptInputParameterInfo(funcInfo->handle, paramNb, &optInputParamInfo);
                    if (retCode != TA_SUCCESS) continue;
                    fprintf(out, "    ///     %d, // %s\n",
                            (int)optInputParamInfo->defaultValue,
                            optInputParamInfo->paramName);
                }

                /* Output args */
                fprintf(out, "    ///     &mut out_beg_idx,\n");
                fprintf(out, "    ///     &mut out_nb_element,\n");

                for (paramNb = 0; paramNb < funcInfo->nbOutput; paramNb++)
                {
                    retCode = TA_GetOutputParameterInfo(funcInfo->handle, paramNb, &outputParamInfo);
                    if (retCode != TA_SUCCESS) continue;

                    if (funcInfo->nbOutput == 1)
                        fprintf(out, "    ///     &mut out,\n");
                    else
                        fprintf(out, "    ///     &mut %s,\n", outputParamInfo->paramName);
                }

                fprintf(out, "    /// );\n");
                fprintf(out, "    ///\n");
                fprintf(out, "    /// assert_eq!(result, RetCode::Success);\n");
            }

            fprintf(out, "    /// ```\n");
        }
```

**Step 2: Call `printRustFuncDoc` for main function in gen_code.c**

At line ~3451 in gen_code.c, right before `printRustDoublePrecisionFunctionSignature`, add:

```c
    print( out, "#elif defined( _RUST )\n" );
    printRustFuncDoc(out, funcInfo, RUST_DOC_MAIN);  /* ADD THIS LINE */
    printRustDoublePrecisionFunctionSignature(out, NULL, funcInfo);
```

The `#elif defined( _RUST )` is already at line 3451 — insert between it and line 3452.

**Step 3: Rebuild and verify**

```bash
cd /Users/chadfurman/projects/ta-lib/cmake-build && make gen_code -j4
cd /Users/chadfurman/projects/ta-lib/bin && ../cmake-build/bin/gen_code
cd /Users/chadfurman/projects/ta-lib/rust && cargo check 2>&1 | grep "missing_docs"
```

Expected: no `missing_docs` warnings for `sma` or `mult`.

**Step 4: Run tests (including doctests)**

```bash
cd /Users/chadfurman/projects/ta-lib/rust && cargo test
```

Expected: all 13 unit tests pass PLUS new doctests pass. Check the "Doc-tests ta_lib" section — should show >0 tests.

**Step 5: Read generated sma.rs to verify doc quality**

```bash
head -60 /Users/chadfurman/projects/ta-lib/rust/src/ta_func/sma.rs
```

Verify the doc comment looks correct — hint, args, returns, example.

**Step 6: Verify C/Java unchanged**

```bash
cd /Users/chadfurman/projects/ta-lib && git diff -- java/src/com/tictactec/ta/lib/Core.java
```

Expected: zero diff.

**Step 7: Commit**

```bash
git add src/tools/gen_code/gen_rust.c src/tools/gen_code/gen_code.c rust/src/ta_func/sma.rs rust/src/ta_func/mult.rs
git commit -m "Add comprehensive Rust doc comments with generated examples to main functions"
```

---

### Task 4: Add doc comments to single-precision functions

The simplest — just a cross-reference one-liner.

**Files:**
- Modify: `src/tools/gen_code/gen_code.c` (call at line ~3123)

**Step 1: Call `printRustFuncDoc` for single precision in gen_code.c**

At line ~3123 in gen_code.c, right before `printRustSinglePrecisionFunctionSignature`, add:

```c
    print( gOutFunc_C->file, "#elif defined( _RUST )\n" );
    printRustFuncDoc(gOutFunc_C->file, funcInfo, RUST_DOC_SINGLE);  /* ADD THIS LINE */
    printRustSinglePrecisionFunctionSignature(gOutFunc_C->file, NULL, funcInfo);
```

The `#elif defined( _RUST )` is already at line 3123 — insert between it and line 3124.

**Step 2: Rebuild and verify**

```bash
cd /Users/chadfurman/projects/ta-lib/cmake-build && make gen_code -j4
cd /Users/chadfurman/projects/ta-lib/bin && ../cmake-build/bin/gen_code
cd /Users/chadfurman/projects/ta-lib/rust && cargo check 2>&1 | grep "missing_docs"
```

Expected: only module-level warnings remain (if any — Task 1 should have cleared those).

**Step 3: Run tests**

```bash
cd /Users/chadfurman/projects/ta-lib/rust && cargo test
```

Expected: all tests pass.

**Step 4: Commit**

```bash
git add src/tools/gen_code/gen_code.c rust/src/ta_func/sma.rs rust/src/ta_func/mult.rs
git commit -m "Add cross-reference doc comments to single-precision Rust functions"
```

---

### Task 5: Add `pub mod` doc comments in writeRustModLines

The `pub mod sma;` and `pub mod mult;` lines in mod.rs also trigger `missing_docs` warnings.

**Files:**
- Modify: `src/tools/gen_code/gen_rust.c` (update `writeRustModLines`)

**Step 1: Add doc comment before each `pub mod` line**

In `writeRustModLines` at line ~370 in gen_rust.c, change:

```c
    if (params->writePubUse == 1)
        fprintf(out->file, "pub use self::%s::*;\n", buffer);
    else
        fprintf(out->file, "pub mod %s;\n", buffer);
```

To:

```c
    if (params->writePubUse == 1)
        fprintf(out->file, "pub use self::%s::*;\n", buffer);
    else
        fprintf(out->file, "/// %s implementation.\npub mod %s;\n", funcInfo->hint, buffer);
```

**Step 2: Rebuild and verify zero warnings**

```bash
cd /Users/chadfurman/projects/ta-lib/cmake-build && make gen_code -j4
cd /Users/chadfurman/projects/ta-lib/bin && ../cmake-build/bin/gen_code
cd /Users/chadfurman/projects/ta-lib/rust && cargo check 2>&1 | grep "missing_docs" | wc -l
```

Expected: 0 warnings.

**Step 3: Run all tests**

```bash
cd /Users/chadfurman/projects/ta-lib/rust && cargo test
```

Expected: all tests pass (unit + doctests).

**Step 4: Commit**

```bash
git add src/tools/gen_code/gen_rust.c rust/src/ta_func/mod.rs
git commit -m "Add doc comments to pub mod declarations in Rust mod.rs"
```

---

### Task 6: Add rich hand-written example for SMA

Create the first rich example file to demonstrate the override mechanism.

**Files:**
- Create: `src/ta_abstract/rust_examples/sma.txt`

**Step 1: Create the rich example directory and file**

```bash
mkdir -p /Users/chadfurman/projects/ta-lib/src/ta_abstract/rust_examples
```

Write `src/ta_abstract/rust_examples/sma.txt`:

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

**Step 2: Rebuild and regenerate**

```bash
cd /Users/chadfurman/projects/ta-lib/cmake-build && make gen_code -j4
cd /Users/chadfurman/projects/ta-lib/bin && ../cmake-build/bin/gen_code
```

**Step 3: Verify the rich example appears in sma.rs**

```bash
grep -A 5 "Calculate 3-period" /Users/chadfurman/projects/ta-lib/rust/src/ta_func/sma.rs
```

Expected: should see the rich example content, not the mechanical one.

**Step 4: Run tests (doctests verify the example compiles and runs)**

```bash
cd /Users/chadfurman/projects/ta-lib/rust && cargo test
```

Expected: all tests pass including the SMA doctest.

**Step 5: Verify MULT still has the generated example**

```bash
grep -A 3 "# Example" /Users/chadfurman/projects/ta-lib/rust/src/ta_func/mult.rs
```

Expected: shows the mechanical generated example (no `rust_examples/mult.txt` exists).

**Step 6: Commit**

```bash
git add src/ta_abstract/rust_examples/sma.txt rust/src/ta_func/sma.rs
git commit -m "Add rich hand-written doctest example for SMA"
```

---

### Task 7: Add module-level doc to lib.rs for ta_func

The `pub mod ta_func;` line in lib.rs also needs a doc comment. This is hand-maintained, not generated.

**Files:**
- Modify: `rust/src/lib.rs`

**Step 1: Add doc comment before the module declaration**

Change line 10 of `rust/src/lib.rs`:

```rust
/// Generated technical analysis functions.
pub mod ta_func;
```

**Step 2: Verify zero warnings**

```bash
cd /Users/chadfurman/projects/ta-lib/rust && cargo check 2>&1 | grep "missing_docs"
```

Expected: zero warnings.

**Step 3: Run tests**

```bash
cd /Users/chadfurman/projects/ta-lib/rust && cargo test
```

Expected: all tests pass.

**Step 4: Commit**

```bash
git add rust/src/lib.rs
git commit -m "Add doc comment to ta_func module declaration in lib.rs"
```

---

### Task 8: Update changelog and documentation

**Files:**
- Modify: `RUST_CHANGELOG.md`
- Modify: `CLAUDE.md`

**Step 1: Add entry to RUST_CHANGELOG.md**

If today already has an entry, amend it. Otherwise add a new dated entry. Include per-bullet commit links following the established format.

**Step 2: Update CLAUDE.md**

- Update the "Current Status" section to note docs are generated
- Remove or update `missing_docs` references if any

**Step 3: Commit**

```bash
git add RUST_CHANGELOG.md CLAUDE.md
git commit -m "Update changelog and docs for Rust doc comment generation"
```
