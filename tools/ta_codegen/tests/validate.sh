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
echo "=== Generating servers ==="
cargo run --release -- generate-servers --backend=c

echo ""
echo "=== Building C server ==="
mkdir -p ../../bin
cargo run --release -- build --backend=c

C_SERVER="../../bin/ta_codegen_serve_c"
if [ ! -x "$C_SERVER" ]; then
    echo "FATAL: C server binary not found at $C_SERVER"
    exit 1
fi

echo ""
echo "=== Checking generated files exist and are non-empty ==="
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
echo "=== Checking generated C files contain all function variants ==="

# Check SMA variants
for variant in "TA_SMA_Logic" "TA_INT_SMA" "TA_SMA_Lookback" "TA_SMA"; do
    if grep -q "$variant" "../../ta_codegen_output/c/ta_SMA.c"; then
        pass "ta_SMA.c contains $variant"
    else
        fail "ta_SMA.c missing $variant"
    fi
done

# Check EMA variants
for variant in "TA_EMA_Logic" "TA_INT_EMA" "TA_EMA_Lookback" "TA_EMA"; do
    if grep -q "$variant" "../../ta_codegen_output/c/ta_EMA.c"; then
        pass "ta_EMA.c contains $variant"
    else
        fail "ta_EMA.c missing $variant"
    fi
done

# Check WMA variants
for variant in "TA_WMA_Logic" "TA_INT_WMA" "TA_WMA_Lookback" "TA_WMA"; do
    if grep -q "$variant" "../../ta_codegen_output/c/ta_WMA.c"; then
        pass "ta_WMA.c contains $variant"
    else
        fail "ta_WMA.c missing $variant"
    fi
done

echo ""
echo "=== Testing JSON-RPC via C server ==="

# Test TA_MULT
REQUEST='{"method":"TA_MULT","params":{"startIdx":0,"endIdx":4,"inReal0":[1,2,3,4,5],"inReal1":[2,3,4,5,6]}}'
RESPONSE=$(echo "$REQUEST" | "$C_SERVER")
EXPECTED='2,6,12,20,30'
if echo "$RESPONSE" | grep -q "$EXPECTED"; then
    pass "JSON-RPC TA_MULT: correct output"
else
    fail "JSON-RPC TA_MULT: unexpected output"
    echo "    Request:  $REQUEST"
    echo "    Response: $RESPONSE"
fi

# Test MULT lookback
REQUEST_LB='{"method":"TA_MULT_Lookback","params":{}}'
RESPONSE_LB=$(echo "$REQUEST_LB" | "$C_SERVER")
if echo "$RESPONSE_LB" | grep -q '"lookback":0'; then
    pass "JSON-RPC TA_MULT_Lookback: correct output"
else
    fail "JSON-RPC TA_MULT_Lookback: unexpected output"
    echo "    Response: $RESPONSE_LB"
fi

# Test TA_SMA
REQUEST_SMA='{"method":"TA_SMA","params":{"startIdx":0,"endIdx":4,"inReal":[1,2,3,4,5],"optInTimePeriod":3}}'
RESPONSE_SMA=$(echo "$REQUEST_SMA" | "$C_SERVER")
EXPECTED_SMA='2,3,4'
if echo "$RESPONSE_SMA" | grep -q "$EXPECTED_SMA"; then
    pass "JSON-RPC TA_SMA: correct output"
else
    fail "JSON-RPC TA_SMA: unexpected output"
    echo "    Request:  $REQUEST_SMA"
    echo "    Response: $RESPONSE_SMA"
fi

# Test SMA lookback
REQUEST_SMA_LB='{"method":"TA_SMA_Lookback","params":{"optInTimePeriod":30}}'
RESPONSE_SMA_LB=$(echo "$REQUEST_SMA_LB" | "$C_SERVER")
if echo "$RESPONSE_SMA_LB" | grep -q '"lookback":29'; then
    pass "JSON-RPC TA_SMA_Lookback: correct output"
else
    fail "JSON-RPC TA_SMA_Lookback: unexpected output"
    echo "    Response: $RESPONSE_SMA_LB"
fi

# Test TA_EMA
REQUEST_EMA='{"method":"TA_EMA","params":{"startIdx":0,"endIdx":9,"inReal":[1,2,3,4,5,6,7,8,9,10],"optInTimePeriod":3}}'
RESPONSE_EMA=$(echo "$REQUEST_EMA" | "$C_SERVER")
if echo "$RESPONSE_EMA" | grep -q '"retCode":0'; then
    pass "JSON-RPC TA_EMA: returns success"
else
    fail "JSON-RPC TA_EMA: unexpected output"
    echo "    Response: $RESPONSE_EMA"
fi

# Test EMA lookback
REQUEST_EMA_LB='{"method":"TA_EMA_Lookback","params":{"optInTimePeriod":10}}'
RESPONSE_EMA_LB=$(echo "$REQUEST_EMA_LB" | "$C_SERVER")
if echo "$RESPONSE_EMA_LB" | grep -q '"lookback":9'; then
    pass "JSON-RPC TA_EMA_Lookback: correct output"
else
    fail "JSON-RPC TA_EMA_Lookback: unexpected output"
    echo "    Response: $RESPONSE_EMA_LB"
fi

# Test TA_WMA
REQUEST_WMA='{"method":"TA_WMA","params":{"startIdx":0,"endIdx":4,"inReal":[1,2,3,4,5],"optInTimePeriod":3}}'
RESPONSE_WMA=$(echo "$REQUEST_WMA" | "$C_SERVER")
if echo "$RESPONSE_WMA" | grep -q '"retCode":0'; then
    pass "JSON-RPC TA_WMA: returns success"
else
    fail "JSON-RPC TA_WMA: unexpected output"
    echo "    Response: $RESPONSE_WMA"
fi

# Test WMA lookback
REQUEST_WMA_LB='{"method":"TA_WMA_Lookback","params":{"optInTimePeriod":5}}'
RESPONSE_WMA_LB=$(echo "$REQUEST_WMA_LB" | "$C_SERVER")
if echo "$RESPONSE_WMA_LB" | grep -q '"lookback":4'; then
    pass "JSON-RPC TA_WMA_Lookback: correct output"
else
    fail "JSON-RPC TA_WMA_Lookback: unexpected output"
    echo "    Response: $RESPONSE_WMA_LB"
fi

# Test RSI
REQUEST_RSI='{"method":"TA_RSI","params":{"startIdx":0,"endIdx":29,"inReal":[44.0,44.34,44.09,43.61,44.33,44.83,44.32,44.55,43.93,44.05,43.80,43.64,43.82,44.29,44.09,44.15,43.61,44.33,44.83,44.32,44.55,43.93,44.05,43.80,43.64,43.82,44.29,44.09,44.15,43.61],"optInTimePeriod":14}}'
RESPONSE_RSI=$(echo "$REQUEST_RSI" | "$C_SERVER")
if echo "$RESPONSE_RSI" | grep -q '"outBegIdx":14'; then
    pass "JSON-RPC TA_RSI: correct output"
else
    fail "JSON-RPC TA_RSI: unexpected output"
    echo "    Response: $RESPONSE_RSI"
fi

# Test RSI lookback
REQUEST_RSI_LB='{"method":"TA_RSI_Lookback","params":{"optInTimePeriod":14}}'
RESPONSE_RSI_LB=$(echo "$REQUEST_RSI_LB" | "$C_SERVER")
if echo "$RESPONSE_RSI_LB" | grep -q '"lookback":14'; then
    pass "JSON-RPC TA_RSI_Lookback: correct output"
else
    fail "JSON-RPC TA_RSI_Lookback: unexpected output"
    echo "    Response: $RESPONSE_RSI_LB"
fi

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
