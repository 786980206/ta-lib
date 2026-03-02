#!/usr/bin/env python3
"""Convert C header files to Rust const files for cross-language harness."""

import re
import sys
from pathlib import Path

SCRIPT_DIR = Path(__file__).parent


def parse_c_array(content: str, name: str, source: str) -> list[str]:
    """Extract array values from a C static const double array."""
    pattern = rf'static\s+const\s+double\s+{name}\[\]\s*=\s*\{{([^}}]+)\}}'
    match = re.search(pattern, content, re.DOTALL)
    if not match:
        print(f"ERROR: Could not find array '{name}' in {source}", file=sys.stderr)
        sys.exit(1)
    values_str = match.group(1)
    values = [v.strip() for v in values_str.split(',') if v.strip()]
    return values


def write_rust_array(lines: list[str], name: str, values: list[str], per_line: int = 8):
    """Append a Rust const array definition to lines."""
    lines.append("#[allow(dead_code)]")
    lines.append(f"pub const {name}: [f64; {len(values)}] = [")
    for i in range(0, len(values), per_line):
        chunk = values[i:i + per_line]
        lines.append("    " + ", ".join(f"{v}_f64" for v in chunk) + ",")
    lines.append("];")
    lines.append("")


def generate_test_data():
    """Convert test_data.h → test_data.rs."""
    header_path = SCRIPT_DIR / "test_data.h"
    rust_path = SCRIPT_DIR / "rust" / "src" / "test_data.rs"

    content = header_path.read_text()
    prices = parse_c_array(content, "TEST_PRICES", "test_data.h")
    prices_2 = parse_c_array(content, "TEST_PRICES_2", "test_data.h")

    lines = [
        "// Auto-generated from test_data.h by generate_rust_data.py",
        "// Do not edit manually.",
        "",
    ]
    write_rust_array(lines, "TEST_PRICES", prices)
    write_rust_array(lines, "TEST_PRICES_2", prices_2, per_line=10)

    rust_path.write_text("\n".join(lines))
    print(f"Generated {rust_path} ({len(prices)} prices, {len(prices_2)} prices_2)")


def generate_bench_data():
    """Convert bench_data.h → bench_data.rs."""
    header_path = SCRIPT_DIR / "bench_data.h"
    rust_path = SCRIPT_DIR / "rust" / "src" / "bench_data.rs"

    if not header_path.exists():
        print("bench_data.h not found — run generate_bench_data.py first")
        sys.exit(1)

    content = header_path.read_text()
    prices = parse_c_array(content, "BENCH_PRICES", "bench_data.h")
    prices_2 = parse_c_array(content, "BENCH_PRICES_2", "bench_data.h")

    lines = [
        "// Auto-generated from bench_data.h by generate_rust_data.py",
        "// Do not edit manually.",
        "",
    ]
    write_rust_array(lines, "BENCH_PRICES", prices)
    write_rust_array(lines, "BENCH_PRICES_2", prices_2)

    rust_path.write_text("\n".join(lines))
    print(f"Generated {rust_path} ({len(prices)} bench prices, {len(prices_2)} bench prices_2)")


def main():
    generate_test_data()
    generate_bench_data()


if __name__ == "__main__":
    main()
