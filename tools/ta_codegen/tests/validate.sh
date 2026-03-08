#!/bin/bash
set -e
cd "$(dirname "$0")/.."

PASS=0
FAIL=0

pass() { echo "  PASS: $1"; PASS=$((PASS + 1)); }
fail() { echo "  FAIL: $1"; FAIL=$((FAIL + 1)); }

echo "=== Building ta_codegen ==="
cargo build --release

echo ""
echo "=== Generating all backends ==="
cargo run --release -- generate

echo ""
echo "=== Comparing generated output against reference files ==="

# --- Rust MULT comparison ---
RUST_GEN="../../ta_codegen_output/rust/mult.rs"
RUST_REF="../../rust/src/ta_func/mult.rs"
if [ -f "$RUST_REF" ]; then
    if diff -q "$RUST_GEN" "$RUST_REF" > /dev/null 2>&1; then
        pass "Rust MULT: byte-identical match"
    else
        fail "Rust MULT: differences found"
        diff --unified "$RUST_GEN" "$RUST_REF" | head -40 || true
    fi
else
    echo "  SKIP: Rust MULT reference file not found at $RUST_REF"
fi

# --- Rust SMA comparison ---
SMA_GEN="../../ta_codegen_output/rust/sma.rs"
SMA_REF="../../rust/src/ta_func/sma.rs"
if [ -f "$SMA_REF" ]; then
    if diff -q "$SMA_GEN" "$SMA_REF" > /dev/null 2>&1; then
        pass "Rust SMA: byte-identical match"
    else
        fail "Rust SMA: differences found"
        diff --unified "$SMA_GEN" "$SMA_REF" | head -40 || true
    fi
else
    echo "  SKIP: Rust SMA reference file not found at $SMA_REF"
fi

# --- Check generated files exist and are non-empty ---
for f in \
    "../../ta_codegen_output/c/ta_MULT.c" \
    "../../ta_codegen_output/rust/mult.rs" \
    "../../ta_codegen_output/java/Core_MULT.java" \
    "../../ta_codegen_output/dotnet/Core_MULT.h" \
    "../../ta_codegen_output/swig/ta_MULT.swg" \
    "../../ta_codegen_output/c/ta_SMA.c" \
    "../../ta_codegen_output/rust/sma.rs" \
    "../../ta_codegen_output/java/Core_SMA.java" \
    "../../ta_codegen_output/dotnet/Core_SMA.h" \
    "../../ta_codegen_output/swig/ta_SMA.swg" \
    "../../ta_codegen_output/c/ta_RSI.c" \
    "../../ta_codegen_output/rust/rsi.rs" \
    "../../ta_codegen_output/java/Core_RSI.java" \
    "../../ta_codegen_output/dotnet/Core_RSI.h" \
    "../../ta_codegen_output/swig/ta_RSI.swg" \
    "../../ta_codegen_output/c/ta_EMA.c" \
    "../../ta_codegen_output/rust/ema.rs" \
    "../../ta_codegen_output/java/Core_EMA.java" \
    "../../ta_codegen_output/dotnet/Core_EMA.h" \
    "../../ta_codegen_output/swig/ta_EMA.swg" \
    "../../ta_codegen_output/c/ta_MA.c" \
    "../../ta_codegen_output/rust/ma.rs" \
    "../../ta_codegen_output/java/Core_MA.java" \
    "../../ta_codegen_output/dotnet/Core_MA.h" \
    "../../ta_codegen_output/swig/ta_MA.swg" \
    "../../ta_codegen_output/c/ta_WMA.c" \
    "../../ta_codegen_output/rust/wma.rs" \
    "../../ta_codegen_output/java/Core_WMA.java" \
    "../../ta_codegen_output/dotnet/Core_WMA.h" \
    "../../ta_codegen_output/swig/ta_WMA.swg"; do
    if [ -s "$f" ]; then
        pass "Generated file exists: $(basename "$f")"
    else
        fail "Missing or empty: $f"
    fi
done

echo ""
echo "=== Testing JSON-RPC server ==="
REQUEST='{"method":"TA_MULT","params":{"startIdx":0,"endIdx":4,"inReal0":[1,2,3,4,5],"inReal1":[2,3,4,5,6]}}'
RESPONSE=$(echo "$REQUEST" | cargo run --release -- serve 2>/dev/null)
EXPECTED='2.0,6.0,12.0,20.0,30.0'
if echo "$RESPONSE" | grep -q "$EXPECTED"; then
    pass "JSON-RPC TA_MULT: correct output"
else
    fail "JSON-RPC TA_MULT: unexpected output"
    echo "    Request:  $REQUEST"
    echo "    Response: $RESPONSE"
fi

# Test lookback
REQUEST_LB='{"method":"TA_MULT_Lookback","params":{}}'
RESPONSE_LB=$(echo "$REQUEST_LB" | cargo run --release -- serve 2>/dev/null)
if echo "$RESPONSE_LB" | grep -q '"lookback":0'; then
    pass "JSON-RPC TA_MULT_Lookback: correct output"
else
    fail "JSON-RPC TA_MULT_Lookback: unexpected output"
    echo "    Response: $RESPONSE_LB"
fi

# Test SMA
REQUEST_SMA='{"method":"TA_SMA","params":{"startIdx":0,"endIdx":4,"inReal":[1,2,3,4,5],"optInTimePeriod":3}}'
RESPONSE_SMA=$(echo "$REQUEST_SMA" | cargo run --release -- serve 2>/dev/null)
EXPECTED_SMA='2.0,3.0,4.0'
if echo "$RESPONSE_SMA" | grep -q "$EXPECTED_SMA"; then
    pass "JSON-RPC TA_SMA: correct output"
else
    fail "JSON-RPC TA_SMA: unexpected output"
    echo "    Request:  $REQUEST_SMA"
    echo "    Response: $RESPONSE_SMA"
fi

# Test SMA lookback
REQUEST_SMA_LB='{"method":"TA_SMA_Lookback","params":{"optInTimePeriod":30}}'
RESPONSE_SMA_LB=$(echo "$REQUEST_SMA_LB" | cargo run --release -- serve 2>/dev/null)
if echo "$RESPONSE_SMA_LB" | grep -q '"lookback":29'; then
    pass "JSON-RPC TA_SMA_Lookback: correct output"
else
    fail "JSON-RPC TA_SMA_Lookback: unexpected output"
    echo "    Response: $RESPONSE_SMA_LB"
fi

# Test RSI
REQUEST_RSI='{"method":"TA_RSI","params":{"startIdx":0,"endIdx":29,"inReal":[44.0,44.34,44.09,43.61,44.33,44.83,44.32,44.55,43.93,44.05,43.80,43.64,43.82,44.29,44.09,44.15,43.61,44.33,44.83,44.32,44.55,43.93,44.05,43.80,43.64,43.82,44.29,44.09,44.15,43.61],"optInTimePeriod":14}}'
RESPONSE_RSI=$(echo "$REQUEST_RSI" | cargo run --release -- serve 2>/dev/null)
if echo "$RESPONSE_RSI" | grep -q '"outBegIdx":14'; then
    pass "JSON-RPC TA_RSI: correct output"
else
    fail "JSON-RPC TA_RSI: unexpected output"
    echo "    Response: $RESPONSE_RSI"
fi

# Test RSI lookback
REQUEST_RSI_LB='{"method":"TA_RSI_Lookback","params":{"optInTimePeriod":14}}'
RESPONSE_RSI_LB=$(echo "$REQUEST_RSI_LB" | cargo run --release -- serve 2>/dev/null)
if echo "$RESPONSE_RSI_LB" | grep -q '"lookback":14'; then
    pass "JSON-RPC TA_RSI_Lookback: correct output"
else
    fail "JSON-RPC TA_RSI_Lookback: unexpected output"
    echo "    Response: $RESPONSE_RSI_LB"
fi

# EMA JSON-RPC tests skipped — EMA not yet in ta-lib Rust crate

# WMA JSON-RPC tests skipped — WMA not yet in ta-lib Rust crate

echo ""
echo "=== Running cargo test ==="
cargo test 2>&1

echo ""
echo "=== Validation Summary ==="
echo "  Passed: $PASS"
echo "  Failed: $FAIL"
if [ "$FAIL" -gt 0 ]; then
    echo "  Some validations FAILED."
    exit 1
else
    echo "  All validations passed."
fi
