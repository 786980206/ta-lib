#!/usr/bin/env python3
"""Generate a markdown regression test report from ta_regtest output."""

import subprocess
import sys
import os
import re
from datetime import datetime


def run_regtest(languages=None):
    """Run ta_regtest and capture output."""
    cmd = ["../cmake-build/bin/ta_regtest", "--codegen"]
    if languages:
        cmd.append(f"--language={languages}")
    result = subprocess.run(cmd, capture_output=True, text=True, timeout=600)
    return result.stdout + result.stderr


def parse_results(output):
    """Parse ta_regtest output into structured data with timing."""
    results = {}
    columns = []  # column headers from the timing table

    in_table = False
    for line in output.split("\n"):
        if "Codegen Results + Timing" in line:
            in_table = True
            continue

        if not in_table:
            # Catch failures before the table
            if "CODEGEN FAILED" in line or "CODEGEN MISMATCH" in line:
                m = re.match(r'\s*(\w+)\s+', line.strip())
                if m:
                    func = m.group(1)
                    if func[0].isupper() and func not in ("Codegen", "Server", "Testing", "Exception"):
                        results[func] = {"status": "FAIL", "c_ref": None, "timings": {}}
            continue

        # Parse header line to get column order
        if line.startswith("Function"):
            # "Function                C-ref      Rust         C      Java      .NET"
            parts = line.split()
            columns = parts[2:]  # skip "Function" and "C-ref"
            continue

        if line.startswith("=") or not line.strip():
            continue
        if "All" in line and "passed" in line:
            break

        # Parse data line
        # "SMA                       1.0     0.7ok     2.0ok    30.9ok    40.8ok"
        clean = line.strip()
        m = re.match(r'(\w+)\s+(.*)', clean)
        if not m:
            continue
        func = m.group(1)
        if not func[0].isupper() or func in ("Warning",):
            continue

        rest = m.group(2)
        # Extract all numbers (ignoring "ok" suffix and spinner chars)
        values = [float(x) for x in re.findall(r'([\d.]+)', rest)]

        entry = {"status": "PASS", "c_ref": None, "timings": {}}
        if values:
            entry["c_ref"] = values[0]
        for i, col in enumerate(columns):
            if i + 1 < len(values):
                entry["timings"][col] = values[i + 1]
        results[func] = entry

    return results, columns


def generate_report(languages="c,java,dotnet,rust"):
    """Generate markdown report."""
    lang_display = {"C": "C", "Java": "Java", ".NET": ".NET", "Rust": "Rust"}

    print(f"Running regtest for {languages}...", file=sys.stderr)
    output = run_regtest(languages)
    results, columns = parse_results(output)

    # Get git info
    try:
        sha = subprocess.run(["git", "rev-parse", "--short", "HEAD"],
                             capture_output=True, text=True).stdout.strip()
    except Exception:
        sha = "unknown"

    total = len(results)
    all_pass = all(f["status"] == "PASS" for f in results.values())

    # Compute averages per language
    c_ref_vals = [f["c_ref"] for f in results.values() if f["c_ref"] is not None]
    c_ref_avg = sum(c_ref_vals) / len(c_ref_vals) if c_ref_vals else 0

    col_avgs = {}
    col_pass = {}
    for col in columns:
        vals = [f["timings"].get(col) for f in results.values()
                if f["timings"].get(col) is not None]
        col_avgs[col] = sum(vals) / len(vals) if vals else 0
        col_pass[col] = sum(1 for f in results.values() if f["status"] == "PASS")

    lines = []
    lines.append("# ta_regtest Cross-Language Report")
    lines.append("")
    lines.append(f"**Date:** {datetime.now().strftime('%Y-%m-%d %H:%M')}")
    lines.append(f"**Git:** `{sha}`")
    lines.append(f"**Indicators:** {total}")
    lines.append(f"**Status:** {'ALL PASSING' if all_pass else 'FAILURES DETECTED'}")
    lines.append("")

    # Summary table
    lines.append("## Summary")
    lines.append("")
    lines.append("| Language | Pass | Fail | Avg (us/call) | vs C-ref |")
    lines.append("|----------|------|------|---------------|----------|")
    lines.append(f"| **C-ref** | {total} | 0 | {c_ref_avg:.1f} | - |")
    for col in columns:
        name = lang_display.get(col, col)
        p = col_pass.get(col, 0)
        f = total - p
        avg = col_avgs.get(col, 0)
        if avg > 0 and c_ref_avg > 0:
            ratio = avg / c_ref_avg
            if ratio > 1.1:
                vs = f"{ratio:.1f}x slower"
            elif ratio < 0.9:
                vs = f"{1/ratio:.1f}x faster"
            else:
                vs = "~same"
        else:
            vs = "-"
        lines.append(f"| **{name}** | {p} | {f} | {avg:.1f} | {vs} |")
    lines.append("")

    # Detailed table with timing
    lines.append("## Results (timing in us/call)")
    lines.append("")
    header = "| Function | C-ref |"
    sep = "|----------|------:|"
    for col in columns:
        header += f" {lang_display.get(col, col)} |"
        sep += "------:|"
    lines.append(header)
    lines.append(sep)

    for func in sorted(results.keys()):
        data = results[func]
        c_ref = f"{data['c_ref']:.1f}" if data["c_ref"] is not None else "-"
        row = f"| {func} | {c_ref} |"
        for col in columns:
            if data["status"] == "FAIL":
                row += " **FAIL** |"
            elif col in data["timings"]:
                t = data["timings"][col]
                row += f" {t:.1f} |"
            else:
                row += " - |"
        lines.append(row)

    lines.append("")
    lines.append(f"*Generated by `regtest-report.py` on {datetime.now().strftime('%Y-%m-%d %H:%M')}*")
    return "\n".join(lines)


if __name__ == "__main__":
    languages = sys.argv[1] if len(sys.argv) > 1 else "c,java,dotnet,rust"
    os.chdir(os.path.dirname(os.path.abspath(__file__)))
    report = generate_report(languages)

    outpath = "ta_regtest_report.md"
    with open(outpath, "w") as f:
        f.write(report)
    print(f"Report written to {outpath}", file=sys.stderr)
    print(report)
