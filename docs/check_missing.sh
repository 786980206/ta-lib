#!/bin/bash

# Extract function names from functions.md
grep "^|" functions.md | tail -n +3 | awk -F'|' '{print $2}' | sed 's/^[[:space:]]*//;s/[[:space:]]*$//' | grep -v "^$" > functions_list.txt

# Get existing markdown files (excluding system files)
ls *.md | grep -v "^_" | grep -v "functions.md" | grep -v "index.md" | grep -v "api.md" | grep -v "install.md" | grep -v "wrappers.md" | grep -v "about.md" | grep -v "faq.md" | sed 's/\.md$//' | sort > existing_files.txt

# Find missing functions
echo "=== MISSING FUNCTIONS ==="
comm -23 <(sort functions_list.txt) <(sort existing_files.txt)

echo ""
echo "=== EXTRA FILES (not in functions list) ==="
comm -13 <(sort functions_list.txt) <(sort existing_files.txt)

echo ""
echo "=== SUMMARY ==="
echo "Total functions in list: $(wc -l < functions_list.txt)"
echo "Total documented files: $(wc -l < existing_files.txt)"
echo "Missing functions: $(comm -23 <(sort functions_list.txt) <(sort existing_files.txt) | wc -l)"

# Cleanup
rm functions_list.txt existing_files.txt
