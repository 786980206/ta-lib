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
    columns = []

    in_table = False
    for line in output.split("\n"):
        if "Codegen Results + Timing" in line:
            in_table = True
            continue

        if not in_table:
            if "CODEGEN FAILED" in line or "CODEGEN MISMATCH" in line:
                m = re.match(r'\s*(\w+)\s+', line.strip())
                if m:
                    func = m.group(1)
                    if func[0].isupper() and func not in ("Codegen", "Server", "Testing", "Exception"):
                        results[func] = {"status": "FAIL", "c_ref": None, "timings": {}}
            continue

        if line.startswith("Function"):
            parts = line.split()
            columns = parts[2:]
            continue

        if line.startswith("=") or not line.strip():
            continue
        if "All" in line and "passed" in line:
            break

        clean = line.strip()
        m = re.match(r'(\w+)\s+(.*)', clean)
        if not m:
            continue
        func = m.group(1)
        if not func[0].isupper() or func in ("Warning",):
            continue

        rest = m.group(2)
        values = [float(x) for x in re.findall(r'([\d.]+)', rest)]

        entry = {"status": "PASS", "c_ref": None, "timings": {}}
        if values:
            entry["c_ref"] = values[0]
        for i, col in enumerate(columns):
            if i + 1 < len(values):
                entry["timings"][col] = values[i + 1]
        results[func] = entry

    return results, columns


def fmt_us(val):
    """Format microseconds nicely."""
    if val is None:
        return "—"
    if val == 0:
        return "<0.1"
    if val < 0.1:
        return f"{val:.2f}"
    if val < 10:
        return f"{val:.1f}"
    return f"{val:.0f}"


def fmt_ratio(val, ref):
    """Format speed ratio."""
    if val is None or ref is None or ref == 0 or val == 0:
        return "—"
    ratio = val / ref
    if ratio > 1.1:
        return f"{ratio:.1f}× slower"
    if ratio < 0.9:
        return f"{1/ratio:.1f}× faster"
    return "≈ same"


def generate_report(languages="c,java,dotnet,rust"):
    """Generate markdown report."""
    lang_display = {"C": "C", "Java": "Java", ".NET": ".NET", "Rust": "Rust"}

    print(f"Running regtest for {languages}...", file=sys.stderr)
    output = run_regtest(languages)
    results, columns = parse_results(output)

    try:
        sha = subprocess.run(["git", "rev-parse", "--short", "HEAD"],
                             capture_output=True, text=True).stdout.strip()
    except Exception:
        sha = "unknown"

    total = len(results)
    all_pass = all(f["status"] == "PASS" for f in results.values())

    c_ref_vals = [f["c_ref"] for f in results.values() if f["c_ref"] is not None and f["c_ref"] > 0]
    c_ref_avg = sum(c_ref_vals) / len(c_ref_vals) if c_ref_vals else 0

    col_avgs = {}
    col_pass = {}
    col_measured = {}  # how many functions had measurable (>0) timing
    for col in columns:
        all_vals = [f["timings"].get(col) for f in results.values()
                    if f["timings"].get(col) is not None]
        nonzero = [v for v in all_vals if v > 0]
        col_avgs[col] = sum(nonzero) / len(nonzero) if nonzero else 0
        col_pass[col] = sum(1 for f in results.values() if f["status"] == "PASS")
        col_measured[col] = len(nonzero)

    lines = []
    lines.append("# ta_regtest Cross-Language Report")
    lines.append("")
    lines.append(f"> **Date:** {datetime.now().strftime('%Y-%m-%d %H:%M')}  ")
    lines.append(f"> **Git:** `{sha}`  ")
    lines.append(f"> **Indicators:** {total}  ")
    lines.append(f"> **Status:** {'✅ ALL PASSING' if all_pass else '❌ FAILURES DETECTED'}")
    lines.append("")

    # ── Summary ──
    lines.append("## Summary")
    lines.append("")

    # Build summary table with Unicode box drawing
    sum_headers = ["Language", "Pass", "Fail", "Avg (μs)", "vs C-ref"]
    sum_widths = [10, 6, 6, 10, 16]

    def hline(widths, left, mid, right, fill="─"):
        return left + mid.join(fill * w for w in widths) + right

    def row(cells, widths):
        parts = []
        for cell, w in zip(cells, widths):
            parts.append(f" {cell:<{w-1}}")
        return "│" + "│".join(parts) + "│"

    lines.append("```")
    lines.append(hline(sum_widths, "┌", "┬", "┐"))
    lines.append(row(sum_headers, sum_widths))
    lines.append(hline(sum_widths, "├", "┼", "┤"))

    # C-ref row
    lines.append(row(["C-ref", str(total), "0", fmt_us(c_ref_avg), "baseline"], sum_widths))

    for col in columns:
        name = lang_display.get(col, col)
        p = col_pass.get(col, 0)
        f = total - p
        avg = col_avgs.get(col, 0)
        measured = col_measured.get(col, 0)
        if measured < total * 0.5:
            # Most values below timer resolution — flag it
            avg_str = f"~{fmt_us(avg)}*"
            vs = f"*{measured}/{total} measured"
        else:
            avg_str = fmt_us(avg)
            vs = fmt_ratio(avg, c_ref_avg) if avg > 0 else "—"
        lines.append(row([name, str(p), str(f), avg_str, vs], sum_widths))

    lines.append(hline(sum_widths, "└", "┴", "┘"))
    lines.append("```")
    lines.append("")

    # ── Detailed Results ──
    lines.append("## Results (μs/call)")
    lines.append("")

    col_widths = [20, 7] + [7] * len(columns)
    headers = ["Function", "C-ref"] + [lang_display.get(c, c) for c in columns]

    lines.append("```")
    lines.append(hline(col_widths, "┌", "┬", "┐"))
    lines.append(row(headers, col_widths))
    lines.append(hline(col_widths, "├", "┼", "┤"))

    for func in sorted(results.keys()):
        data = results[func]
        cells = [func, fmt_us(data["c_ref"])]
        for col in columns:
            if data["status"] == "FAIL":
                cells.append("FAIL")
            elif col in data["timings"]:
                cells.append(fmt_us(data["timings"][col]))
            else:
                cells.append("—")
        lines.append(row(cells, col_widths))

    lines.append(hline(col_widths, "└", "┴", "┘"))
    lines.append("```")
    lines.append("")
    lines.append(f"*Generated by `regtest-report.py` — {datetime.now().strftime('%Y-%m-%d %H:%M')}*")
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
