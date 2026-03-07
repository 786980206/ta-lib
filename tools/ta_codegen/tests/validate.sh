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
cargo run --release -- generate --func=MULT

echo ""
echo "=== Comparing generated output against reference files ==="

# --- Rust comparison ---
RUST_GEN="../../ta_codegen_output/rust/mult.rs"
RUST_REF="../../rust/src/ta_func/mult.rs"
if [ -f "$RUST_REF" ]; then
    if diff -q "$RUST_GEN" "$RUST_REF" > /dev/null 2>&1; then
        pass "Rust: byte-identical match"
    else
        fail "Rust: differences found"
        diff --unified "$RUST_GEN" "$RUST_REF" | head -40 || true
    fi
else
    echo "  SKIP: Rust reference file not found at $RUST_REF"
fi

# --- Check generated files exist and are non-empty ---
for f in \
    "../../ta_codegen_output/c/ta_MULT.c" \
    "../../ta_codegen_output/rust/mult.rs" \
    "../../ta_codegen_output/java/Core_MULT.java" \
    "../../ta_codegen_output/dotnet/Core_MULT.h" \
    "../../ta_codegen_output/swig/ta_MULT.swg"; do
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
