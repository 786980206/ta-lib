use crate::ir::FuncDef;
use std::path::Path;

/// Generate `ta_func_list.txt` from the given function definitions.
///
/// Sorts alphabetically by name, formats as `{name:<20}{hint}\n`,
/// and writes only if content has changed (preserving the file timestamp).
pub fn generate(funcs: &[FuncDef], out_path: &Path) {
    let mut entries: Vec<(&str, &str)> = funcs
        .iter()
        .map(|f| (f.name.as_str(), f.hint.as_deref().unwrap_or("")))
        .collect();
    entries.sort_by(|a, b| a.0.cmp(b.0));

    let mut content = String::new();
    for (name, hint) in &entries {
        content.push_str(&format!("{:<20}{}\n", name, hint));
    }

    let existing = std::fs::read_to_string(out_path).unwrap_or_default();
    if existing == content {
        println!(
            "  ta_func_list.txt is up to date ({} functions)",
            entries.len()
        );
    } else {
        std::fs::write(out_path, &content).unwrap();
        println!("  ta_func_list.txt updated ({} functions)", entries.len());
    }
}
