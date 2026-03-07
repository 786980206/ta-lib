# Rust Regtest FFI Implementation Plan

> **For Claude:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Enable the existing C ta_regtest binary to exercise Rust TA function implementations via FFI link-time swap, with a `--function` CLI filter for tight-loop development.

**Architecture:** Rust functions export `extern "C"` wrappers matching C signatures. A new CMake target (`ta_regtest_rust`) links ta_regtest against the Rust staticlib instead of C. A `--function=CSV` flag lets you run specific test groups only.

**Tech Stack:** Rust (staticlib crate), C (minimal ta_regtest.c changes), CMake

**Design doc:** `docs/plans/2026-03-07-rust-regtest-ffi-design.md`

---

### Task 1: Add `--function=CSV` Filter to ta_regtest.c

**Files:**
- Modify: `src/tools/ta_regtest/ta_regtest.c`

This is the only change to ta_regtest's source code. It adds CLI argument parsing and conditional test dispatch. Zero changes to test logic, tolerance math, or range testing.

**Step 1: Understand the current dispatch**

Read `src/tools/ta_regtest/ta_regtest.c`. The `testTAFunction_ALL()` function (line 225) uses a `DO_TEST(func, str)` macro (line 242) that calls each test group. There are 21 `DO_TEST` calls (lines 255-276).

**Step 2: Add a global filter variable and parsing**

In `ta_regtest.c`, add a global variable after line 84:

```c
/* CSV list of function names to test (NULL = test all) */
static const char *functionFilter = NULL;
```

Modify the `main()` argument parsing section (lines 119-137). Replace with logic that handles both `-p` and `--function=CSV`:

```c
   int i;
   for( i = 1; i < argc; i++ )
   {
      if( (argv[i][0] == '-') && (argv[i][1] == 'p') && (argv[i][2] == '\0') )
      {
         doExtensiveProfiling = 1;
      }
      else if( strncmp(argv[i], "--function=", 11) == 0 )
      {
         functionFilter = argv[i] + 11;
      }
      else
      {
         printUsage();
         return TA_REGTEST_BAD_USER_PARAM;
      }
   }
```

**Step 3: Add a filter-matching helper function**

Add before `testTAFunction_ALL()`:

```c
/* Check if any CSV token in 'filter' appears as a substring in 'tags'.
 * Returns 1 if match found (or filter is NULL), 0 otherwise.
 * Both filter tokens and tags are matched case-insensitively.
 */
static int matchesFilter(const char *filter, const char *tags)
{
   char filterCopy[1024];
   char *token;

   if( filter == NULL )
      return 1; /* No filter = run everything */

   strncpy(filterCopy, filter, sizeof(filterCopy) - 1);
   filterCopy[sizeof(filterCopy) - 1] = '\0';

   token = strtok(filterCopy, ",");
   while( token != NULL )
   {
      if( strstr(tags, token) != NULL )
         return 1;
      token = strtok(NULL, ",");
   }
   return 0;
}
```

**Step 4: Modify DO_TEST macro to use the filter**

Replace the `DO_TEST` macro (line 242) with:

```c
   #define DO_TEST(func,str) \
      { \
      if( matchesFilter(functionFilter, str) ) \
      { \
         printf( "%50s: Testing....", str ); \
         fflush(stdout); \
         showFeedback(); \
         TA_SetCompatibility( TA_COMPATIBILITY_DEFAULT ); \
         retValue = func( &history ); \
         if( retValue != TA_TEST_PASS ) \
            return retValue; \
         hideFeedback(); \
         printf( "done.\n" ); \
         fflush(stdout); \
      } \
      }
```

**Step 5: Update printUsage**

Add to `printUsage()`:

```c
      printf( "   --function=NAME[,NAME,...]\n" );
      printf( "       Only run tests matching the given function name(s).\n" );
      printf( "       Names are matched against test group descriptions.\n" );
      printf( "       Example: --function=RSI or --function=SMA,RSI,BBANDS\n" );
      printf( "\n" );
```

**Step 6: Verify the C ta_regtest still works**

Run:
```bash
cd cmake-build && cmake .. -DCMAKE_BUILD_TYPE=Release && make ta_regtest -j4
cp bin/ta_regtest ../bin/
cd ../bin && ./ta_regtest
```
Expected: All tests pass, identical to before.

**Step 7: Test the filter**

Run:
```bash
cd bin && ./ta_regtest --function=RSI
```
Expected: Only "RSI,CMO" test group runs. Other groups skipped.

Run:
```bash
cd bin && ./ta_regtest --function=RSI,BBANDS
```
Expected: "RSI,CMO" and "BBANDS" groups run.

**Step 8: Commit**

```bash
git add src/tools/ta_regtest/ta_regtest.c
git commit -m "Add --function=CSV filter to ta_regtest for selective test runs"
```

**Important note about test group names:** The DO_TEST descriptions are: `"MATH,VECTOR,DCPERIOD/PHASE,TRENDLINE/MODE"`, `"All Moving Averages"`, `"AROON,CORREL,BETA"`, `"CCI,WILLR,ULTOSC,NATR"`, `"BOP,AVGPRICE"`, `"RSI,CMO"`, `"IMI"`, `"MIN,MAX,MININDEX,MAXINDEX,MINMAX,MINMAXINDEX"`, `"PO,APO"`, `"ADX,ADXR,DI,DM,DX"`, `"SAR,SAREXT"`, `"STOCH,STOCHF,STOCHRSI"`, `"MFI,AD,ADOSC"`, `"PHASOR,SINE"`, `"TRIX"`, `"MACD,MACDFIX,MACDEXT"`, `"MOM,ROC,ROCP,ROCR,ROCR100"`, `"TRANGE,ATR"`, `"STDDEV,VAR"`, `"AVGDEV"`, `"BBANDS"`, `"All Candlesticks"`.

Note: MULT is tested in `"MATH,VECTOR,DCPERIOD/PHASE,TRENDLINE/MODE"` and SMA is tested in `"All Moving Averages"`. To filter for SMA, use `--function="Moving Averages"`. To filter for MULT, use `--function=MATH`. These are substring matches against the description strings.

---

### Task 2: Create the Rust FFI Staticlib Crate

**Files:**
- Create: `rust/ffi/Cargo.toml`
- Create: `rust/ffi/src/lib.rs`

This crate wraps Rust TA functions with `extern "C"` signatures matching `ta_func.h` exactly.

**Step 1: Create the crate structure**

```bash
mkdir -p rust/ffi/src
```

**Step 2: Write Cargo.toml**

Create `rust/ffi/Cargo.toml`:

```toml
[package]
name = "ta-lib-ffi"
version = "0.6.4"
edition = "2021"

[lib]
name = "ta_lib_ffi"
crate-type = ["staticlib"]

[dependencies]
ta-lib = { path = ".." }
```

**Step 3: Write the FFI wrapper — RetCode mapping**

The C `TA_RetCode` enum values differ from Rust `RetCode` discriminants. This mapping is critical:

| C Name | C Value | Rust Name | Rust Discriminant |
|--------|---------|-----------|-------------------|
| TA_SUCCESS | 0 | Success | 0 |
| TA_BAD_PARAM | 2 | BadParam | 1 |
| TA_ALLOC_ERR | 3 | AllocErr | 4 |
| TA_OUT_OF_RANGE_START_INDEX | 12 | OutOfRangeStartIndex | 2 |
| TA_OUT_OF_RANGE_END_INDEX | 13 | OutOfRangeEndIndex | 3 |
| TA_INTERNAL_ERROR | 5000 | InternalError | 5 |

Create `rust/ffi/src/lib.rs`:

```rust
use std::os::raw::{c_double, c_int};
use ta_lib::ta_func::{Core, RetCode};

/// Map Rust RetCode to C TA_RetCode integer values.
fn retcode_to_c(rc: RetCode) -> c_int {
    match rc {
        RetCode::Success => 0,              // TA_SUCCESS
        RetCode::BadParam => 2,             // TA_BAD_PARAM
        RetCode::OutOfRangeStartIndex => 12, // TA_OUT_OF_RANGE_START_INDEX
        RetCode::OutOfRangeEndIndex => 13,  // TA_OUT_OF_RANGE_END_INDEX
        RetCode::AllocErr => 3,             // TA_ALLOC_ERR
        RetCode::InternalError => 5000,     // TA_INTERNAL_ERROR
    }
}

// ---------------------------------------------------------------------------
// TA_MULT
// ---------------------------------------------------------------------------

#[no_mangle]
pub unsafe extern "C" fn TA_MULT(
    startIdx: c_int,
    endIdx: c_int,
    inReal0: *const c_double,
    inReal1: *const c_double,
    outBegIdx: *mut c_int,
    outNBElement: *mut c_int,
    outReal: *mut c_double,
) -> c_int {
    let core = Core::new();
    let len = (endIdx + 1) as usize;
    let in0 = std::slice::from_raw_parts(inReal0, len);
    let in1 = std::slice::from_raw_parts(inReal1, len);
    let out = std::slice::from_raw_parts_mut(outReal, len);

    let mut beg: usize = 0;
    let mut nb: usize = 0;
    let rc = core.mult(startIdx as usize, endIdx as usize, in0, in1, &mut beg, &mut nb, out);

    *outBegIdx = beg as c_int;
    *outNBElement = nb as c_int;
    retcode_to_c(rc)
}

#[no_mangle]
pub unsafe extern "C" fn TA_S_MULT(
    startIdx: c_int,
    endIdx: c_int,
    inReal0: *const f32,
    inReal1: *const f32,
    outBegIdx: *mut c_int,
    outNBElement: *mut c_int,
    outReal: *mut c_double,
) -> c_int {
    let core = Core::new();
    let len = (endIdx + 1) as usize;
    let in0 = std::slice::from_raw_parts(inReal0, len);
    let in1 = std::slice::from_raw_parts(inReal1, len);
    let out = std::slice::from_raw_parts_mut(outReal, len);

    let mut beg: usize = 0;
    let mut nb: usize = 0;
    let rc = core.mult_s(startIdx as usize, endIdx as usize, in0, in1, &mut beg, &mut nb, out);

    *outBegIdx = beg as c_int;
    *outNBElement = nb as c_int;
    retcode_to_c(rc)
}

#[no_mangle]
pub extern "C" fn TA_MULT_Lookback() -> c_int {
    let core = Core::new();
    core.mult_lookback()
}

// ---------------------------------------------------------------------------
// TA_SMA
// ---------------------------------------------------------------------------

#[no_mangle]
pub unsafe extern "C" fn TA_SMA(
    startIdx: c_int,
    endIdx: c_int,
    inReal: *const c_double,
    optInTimePeriod: c_int,
    outBegIdx: *mut c_int,
    outNBElement: *mut c_int,
    outReal: *mut c_double,
) -> c_int {
    let core = Core::new();
    let len = (endIdx + 1) as usize;
    let input = std::slice::from_raw_parts(inReal, len);
    let out = std::slice::from_raw_parts_mut(outReal, len);

    let mut beg: usize = 0;
    let mut nb: usize = 0;
    let rc = core.sma(startIdx as usize, endIdx as usize, input, optInTimePeriod, &mut beg, &mut nb, out);

    *outBegIdx = beg as c_int;
    *outNBElement = nb as c_int;
    retcode_to_c(rc)
}

#[no_mangle]
pub unsafe extern "C" fn TA_S_SMA(
    startIdx: c_int,
    endIdx: c_int,
    inReal: *const f32,
    optInTimePeriod: c_int,
    outBegIdx: *mut c_int,
    outNBElement: *mut c_int,
    outReal: *mut c_double,
) -> c_int {
    let core = Core::new();
    let len = (endIdx + 1) as usize;
    let input = std::slice::from_raw_parts(inReal, len);
    let out = std::slice::from_raw_parts_mut(outReal, len);

    let mut beg: usize = 0;
    let mut nb: usize = 0;
    let rc = core.sma_s(startIdx as usize, endIdx as usize, input, optInTimePeriod, &mut beg, &mut nb, out);

    *outBegIdx = beg as c_int;
    *outNBElement = nb as c_int;
    retcode_to_c(rc)
}

#[no_mangle]
pub extern "C" fn TA_SMA_Lookback(optInTimePeriod: c_int) -> c_int {
    let core = Core::new();
    core.sma_lookback(optInTimePeriod)
}

// ---------------------------------------------------------------------------
// TA_RSI
// ---------------------------------------------------------------------------

#[no_mangle]
pub unsafe extern "C" fn TA_RSI(
    startIdx: c_int,
    endIdx: c_int,
    inReal: *const c_double,
    optInTimePeriod: c_int,
    outBegIdx: *mut c_int,
    outNBElement: *mut c_int,
    outReal: *mut c_double,
) -> c_int {
    let core = Core::new();
    let len = (endIdx + 1) as usize;
    let input = std::slice::from_raw_parts(inReal, len);
    let out = std::slice::from_raw_parts_mut(outReal, len);

    let mut beg: usize = 0;
    let mut nb: usize = 0;
    let rc = core.rsi(startIdx as usize, endIdx as usize, input, optInTimePeriod, &mut beg, &mut nb, out);

    *outBegIdx = beg as c_int;
    *outNBElement = nb as c_int;
    retcode_to_c(rc)
}

#[no_mangle]
pub unsafe extern "C" fn TA_S_RSI(
    startIdx: c_int,
    endIdx: c_int,
    inReal: *const f32,
    optInTimePeriod: c_int,
    outBegIdx: *mut c_int,
    outNBElement: *mut c_int,
    outReal: *mut c_double,
) -> c_int {
    let core = Core::new();
    let len = (endIdx + 1) as usize;
    let input = std::slice::from_raw_parts(inReal, len);
    let out = std::slice::from_raw_parts_mut(outReal, len);

    let mut beg: usize = 0;
    let mut nb: usize = 0;
    let rc = core.rsi_s(startIdx as usize, endIdx as usize, input, optInTimePeriod, &mut beg, &mut nb, out);

    *outBegIdx = beg as c_int;
    *outNBElement = nb as c_int;
    retcode_to_c(rc)
}

#[no_mangle]
pub extern "C" fn TA_RSI_Lookback(optInTimePeriod: c_int) -> c_int {
    let core = Core::new();
    core.rsi_lookback(optInTimePeriod)
}
```

**Step 4: Build the FFI crate**

Run:
```bash
cd rust/ffi && cargo build --release
```
Expected: Produces `target/release/libta_lib_ffi.a`

**Step 5: Commit**

```bash
git add rust/ffi/
git commit -m "Add Rust FFI staticlib crate with wrappers for SMA, RSI, MULT"
```

---

### Task 3: Add `ta_regtest_rust` CMake Target

**Files:**
- Modify: `CMakeLists.txt`

**Step 1: Read the existing ta_regtest target**

Read `CMakeLists.txt` and find the `ta_regtest` target definition. Note the source files, include directories, and link libraries.

**Step 2: Add the Rust regtest target**

After the existing `ta_regtest` target section, add:

```cmake
# --- Rust FFI Regression Test Target ---
option(ENABLE_RUST_REGTEST "Build ta_regtest linked against Rust FFI library" OFF)

if(ENABLE_RUST_REGTEST)
    # Build the Rust FFI staticlib via cargo
    set(RUST_FFI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/rust/ffi")
    set(RUST_FFI_LIB "${RUST_FFI_DIR}/target/release/libta_lib_ffi.a")

    add_custom_command(
        OUTPUT ${RUST_FFI_LIB}
        COMMAND cargo build --release --manifest-path ${RUST_FFI_DIR}/Cargo.toml
        WORKING_DIRECTORY ${RUST_FFI_DIR}
        COMMENT "Building Rust FFI staticlib"
    )
    add_custom_target(rust_ffi_lib DEPENDS ${RUST_FFI_LIB})

    add_executable(ta_regtest_rust ${TA_REGTEST_SOURCES})
    target_include_directories(ta_regtest_rust PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src/ta_common"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/tools/ta_regtest"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/ta_func"
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
    )

    # Link against Rust FFI lib instead of ta-lib-static.
    # Also link the C ta_common and ta_abstract objects that ta_regtest needs
    # (test internals, abstract interface tests, reference data, etc.)
    # but NOT the ta_func C implementations (those come from Rust).
    target_link_libraries(ta_regtest_rust PRIVATE
        ${RUST_FFI_LIB}
        ta-lib-static  # Still needed for ta_common, ta_abstract, reference data
        m
    )
    add_dependencies(ta_regtest_rust rust_ffi_lib)

    # Copy to bin directory
    add_custom_command(TARGET ta_regtest_rust POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ta_regtest_rust> "${CMAKE_CURRENT_SOURCE_DIR}/bin/ta_regtest_rust"
    )
endif()
```

**Important linker note:** There's a subtlety here. `ta_regtest_rust` still needs to link against `ta-lib-static` for the ta_common utilities (allocLib, freeLib, test data arrays, etc.) and ta_abstract tests. The Rust FFI lib provides duplicate symbols for `TA_SMA`, `TA_RSI`, `TA_MULT` and their lookback functions. The linker must prefer the Rust symbols. This depends on link order — the Rust lib must come **first** in the link line so its symbols take precedence.

If the linker complains about duplicate symbols, the fix is to either:
- Use `-Wl,--allow-multiple-definition` (GNU ld)
- Or restructure: split ta-lib-static into `ta-lib-func` and `ta-lib-common`, only link `ta-lib-common`

Start with the simple approach (link order) and handle duplicates if they arise.

**Step 3: Test the build**

```bash
cd cmake-build && cmake .. -DCMAKE_BUILD_TYPE=Release -DENABLE_RUST_REGTEST=ON && make ta_regtest_rust -j4
```
Expected: Builds successfully, produces `bin/ta_regtest_rust`

**Step 4: Commit**

```bash
git add CMakeLists.txt
git commit -m "Add ta_regtest_rust CMake target linking against Rust FFI lib"
```

---

### Task 4: Validate — Run ta_regtest_rust Against Ported Functions

**Files:** None (validation only)

**Step 1: Run ta_regtest_rust with the filter**

```bash
cd bin && ./ta_regtest_rust --function=MATH,RSI,"Moving Averages"
```

This runs the MULT tests (via "MATH,VECTOR,..."), RSI tests, and SMA tests (via "All Moving Averages") — all backed by Rust implementations.

Expected: All three test groups pass.

**Step 2: If tests fail, debug**

Common failure modes:
- **Crash/segfault**: FFI calling convention mismatch. Check pointer types, sizes.
- **Wrong values**: RetCode mapping is wrong, or usize/int conversion is losing data.
- **Link errors**: Duplicate symbol issues. See note in Task 3.

**Step 3: Compare against C ta_regtest**

Run the C version to confirm baseline:
```bash
cd bin && ./ta_regtest --function=MATH,RSI,"Moving Averages"
```

Both should produce identical pass/fail results.

**Step 4: Run the full C ta_regtest to confirm no regressions**

```bash
cd bin && ./ta_regtest
```
Expected: All tests pass (this is unchanged C code, should be fine).

**Step 5: Commit any fixes, then tag the milestone**

```bash
git commit -m "Validate: ta_regtest_rust passes SMA, RSI, MULT via Rust FFI"
```

---

### Task 5: Extend gen_code to Generate FFI Wrappers

**Files:**
- Modify: `src/tools/gen_code/gen_rust.c`
- Modify: `src/tools/gen_code/gen_code.c` (to call the new function)

**Step 1: Study the existing generation pattern**

Read `gen_rust.c`. Key functions to understand:
- `printRustDoublePrecisionFunctionSignature()` — generates the Rust method signature
- `printRustSinglePrecisionFunctionSignature()` — generates the `_s` variant
- `printRustLookbackFunctionSignature()` — generates the lookback method
- `writeRustMod()` / `writeRustModLines()` — manages the module file

The generator iterates over all functions via the abstract interface (`TA_ForEachFunc`). For each function, it knows:
- The C name (e.g., "SMA")
- All input parameters (types, names, optional ranges)
- All output parameters
- Optional parameters

**Step 2: Add FFI wrapper generation functions to gen_rust.c**

Add three new functions that mirror the existing signature generators but output `extern "C"` wrappers:

- `printRustFfiDoublePrecisionWrapper()` — generates `#[no_mangle] pub unsafe extern "C" fn TA_XXX(...)` with the type conversion logic
- `printRustFfiSinglePrecisionWrapper()` — generates `TA_S_XXX` variant
- `printRustFfiLookbackWrapper()` — generates the lookback wrapper

Each wrapper follows the exact pattern from the hand-written wrappers in Task 2:
1. Create `Core::new()`
2. Convert C pointers to Rust slices using `from_raw_parts` with `(endIdx + 1)` length
3. Create intermediate `usize` variables for `outBegIdx`/`outNBElement`
4. Call the Rust method
5. Write back `outBegIdx`/`outNBElement` as `c_int`
6. Return `retcode_to_c(rc)`

**Step 3: Add a file-writing function for the FFI crate**

Add `writeRustFfi()` that:
1. Opens `rust/ffi/src/generated.rs` for writing
2. Writes the `use` imports and `retcode_to_c` helper
3. Iterates over all Rust-supported functions
4. Calls the three wrapper generators for each
5. Closes the file

**Step 4: Call from gen_code.c**

In `gen_code.c`, find where `genRustCode()` is called. Add a call to `writeRustFfi()` after it (or at the end of Rust generation).

**Step 5: Update rust/ffi/src/lib.rs to use generated code**

Replace the hand-written wrappers with:

```rust
mod generated;
pub use generated::*;
```

And create `rust/ffi/src/generated.rs` (initially empty — gen_code will populate it).

**Step 6: Rebuild gen_code and run it**

```bash
cd cmake-build && make gen_code -j4
cd ../bin && ../cmake-build/bin/gen_code
```

**Step 7: Verify generated wrappers compile**

```bash
cd rust/ffi && cargo build --release
```

**Step 8: Verify generated wrappers produce identical results**

```bash
cd cmake-build && make ta_regtest_rust -j4
cd ../bin && ./ta_regtest_rust --function=MATH,RSI,"Moving Averages"
```
Expected: All pass, same as with hand-written wrappers.

**Step 9: Remove hand-written wrappers, commit**

```bash
git add src/tools/gen_code/gen_rust.c src/tools/gen_code/gen_code.c rust/ffi/
git commit -m "Generate Rust FFI wrappers from gen_code instead of hand-writing"
```

---

### Task 6: Document the Workflow

**Files:**
- Modify: `CLAUDE.md` (add section about FFI regtest workflow)

**Step 1: Add workflow documentation to CLAUDE.md**

Add a new section documenting:
- How to build and run `ta_regtest_rust`
- The `--function=CSV` filter syntax and test group names
- The AI tight-loop workflow for porting new functions
- How the FFI wrappers are generated

```markdown
## Cross-Language Regression Testing

### Running ta_regtest Against Rust

```bash
# Build (from project root)
cd cmake-build && cmake .. -DCMAKE_BUILD_TYPE=Release -DENABLE_RUST_REGTEST=ON && make ta_regtest_rust -j4

# Run all ported functions
cd ../bin && ./ta_regtest_rust --function=MATH,RSI,"Moving Averages"

# Run a specific function group
./ta_regtest_rust --function=RSI
```

### AI Tight-Loop Workflow

When porting a new function to Rust:
1. Run gen_code to generate Rust code + FFI wrapper
2. Fix compilation errors in the generated Rust
3. Test: `cd bin && ./ta_regtest_rust --function=FUNCTION_NAME`
4. Fix and repeat from step 2 until ta_regtest passes

### Test Group Names for --function Filter

| Filter Value | Test Group |
|-------------|------------|
| MATH | MATH,VECTOR,DCPERIOD/PHASE,TRENDLINE/MODE (includes MULT) |
| Moving Averages | All Moving Averages (includes SMA) |
| RSI | RSI,CMO |
| BBANDS | BBANDS |
| ... | (see full list in ta_regtest.c testTAFunction_ALL) |
```

**Step 2: Commit**

```bash
git add CLAUDE.md
git commit -m "Document cross-language regression testing workflow"
```
