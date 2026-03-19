use std::path::Path;

/// Target language for cross-call resolution.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Lang {
    C,
    Rust,
    Java,
    DotNet,
}

/// Registry of discovered indicators, used for cross-function call resolution.
///
/// Scans `ta_func_defs/` subdirectories to discover indicator names,
/// then translates prefix-free calls (e.g. `sma_lookback`) to
/// language-specific names (e.g. `TA_SMA_Lookback` for C).
pub struct Registry {
    /// Sorted by descending length so longest-match wins in `parse_func_name`.
    indicators: Vec<String>,
}

impl Registry {
    /// Build a registry by scanning `base_dir` for subdirectories containing `.yaml` files.
    pub fn from_dir(base_dir: &Path) -> Self {
        let mut indicators = Vec::new();

        if let Ok(entries) = std::fs::read_dir(base_dir) {
            for entry in entries.filter_map(std::result::Result::ok) {
                let path = entry.path();
                if !path.is_dir() {
                    continue;
                }
                let dir_name = entry.file_name().to_string_lossy().to_string();
                let yaml_path = path.join(format!("{dir_name}.yaml"));
                if yaml_path.exists() {
                    indicators.push(dir_name);
                }
            }
        }

        // Sort by descending length so longest-match wins (e.g. "stochrsi" before "stoch")
        indicators.sort_by(|a, b| b.len().cmp(&a.len()).then(a.cmp(b)));

        Registry { indicators }
    }

    /// Check if an indicator exists in the registry.
    pub fn contains(&self, name: &str) -> bool {
        self.indicators.iter().any(|n| n == name)
    }

    /// Resolve a prefix-free function call to a language-specific name.
    ///
    /// Given `sma_lookback` or bare `sma`, parses out the indicator name
    /// and function type, then maps to the target language's naming convention.
    ///
    /// Bare indicator names (e.g. `sma`) are cross-indicator logic calls
    /// and resolve to the unguarded/internal variant in each language.
    ///
    /// Returns the original name unchanged if the indicator is not found.
    pub fn resolve_call(&self, func_name: &str, lang: Lang) -> String {
        // Handle _unguarded suffix: strip it and resolve the base name
        // (which maps to the Logic/INT variant in all backends)
        if let Some(base) = func_name.strip_suffix("_unguarded") {
            if self.contains(base) {
                return match lang {
                    Lang::Rust => format!("{base}_unguarded"),
                    Lang::C => format!("TA_INT_{}", base.to_uppercase()),
                    Lang::Java => {
                        let camel = self.to_camel_case(base);
                        format!("{camel}Logic")
                    }
                    Lang::DotNet => {
                        let pascal = capitalize(base);
                        format!("{pascal}Logic")
                    }
                };
            }
        }

        // First, check if this is a bare indicator name (no suffix).
        // Bare names resolve to the GUARDED variant (TA_FOO, not TA_INT_FOO).
        // Only _unguarded calls resolve to the Logic/INT variant.
        if self.contains(func_name) {
            return match lang {
                Lang::Rust => func_name.to_string(),
                Lang::C => format!("TA_{}", func_name.to_uppercase()),
                Lang::Java => self.to_camel_case(func_name),
                Lang::DotNet => capitalize(func_name),
            };
        }

        let Some((indicator, suffix)) = self.parse_func_name(func_name) else {
            return func_name.to_string();
        };

        match lang {
            Lang::Rust => func_name.to_string(),
            Lang::C => self.to_c_name(&indicator, &suffix),
            Lang::Java => self.to_camel_case(func_name),
            Lang::DotNet => self.to_pascal_case(func_name),
        }
    }

    /// Resolve a prefix-free type reference to a language-specific name.
    ///
    /// Same logic as `resolve_call` — provided as a separate method
    /// so backends can distinguish calls from type references if needed.
    pub fn resolve_type(&self, func_name: &str, lang: Lang) -> String {
        self.resolve_call(func_name, lang)
    }

    /// Parse a prefix-free function name into (indicator, suffix).
    /// e.g. "`sma_lookback`" -> ("sma", "lookback")
    fn parse_func_name(&self, func_name: &str) -> Option<(String, String)> {
        // Try matching known indicators by checking if func_name starts with
        // an indicator name followed by underscore
        for indicator in &self.indicators {
            let prefix = format!("{indicator}_");
            if func_name.starts_with(&prefix) {
                let suffix = func_name[prefix.len()..].to_string();
                return Some((indicator.clone(), suffix));
            }
        }
        None
    }

    /// Convert to C naming: `sma_lookback` -> `TA_SMA_Lookback`
    #[allow(clippy::unused_self)]
    fn to_c_name(&self, indicator: &str, suffix: &str) -> String {
        let upper = indicator.to_uppercase();
        // Capitalize first letter of suffix
        let cap_suffix = capitalize(suffix);
        format!("TA_{upper}_{cap_suffix}")
    }

    /// Convert `snake_case` to camelCase: `sma_lookback` -> `smaLookback`
    #[allow(clippy::unused_self)]
    fn to_camel_case(&self, name: &str) -> String {
        let parts: Vec<&str> = name.split('_').collect();
        let mut result = String::new();
        for (i, part) in parts.iter().enumerate() {
            if i == 0 {
                result.push_str(part);
            } else {
                result.push_str(&capitalize(part));
            }
        }
        result
    }

    /// Convert `snake_case` to `PascalCase`: `sma_lookback` -> `SmaLookback`
    #[allow(clippy::unused_self)]
    fn to_pascal_case(&self, name: &str) -> String {
        name.split('_').map(capitalize).collect()
    }
}

/// Capitalize the first letter of a string.
fn capitalize(s: &str) -> String {
    let mut chars = s.chars();
    match chars.next() {
        None => String::new(),
        Some(c) => c.to_uppercase().collect::<String>() + chars.as_str(),
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_registry_discovers_indicators() {
        let base = Path::new(env!("CARGO_MANIFEST_DIR")).join("../../ta_func_defs");
        let registry = Registry::from_dir(&base);
        assert!(registry.contains("sma"));
        assert!(registry.contains("rsi"));
        assert!(registry.contains("ema"));
    }

    #[test]
    fn test_registry_resolves_cross_calls() {
        let base = Path::new(env!("CARGO_MANIFEST_DIR")).join("../../ta_func_defs");
        let registry = Registry::from_dir(&base);

        // C backend: lookback suffixed calls
        assert_eq!(
            registry.resolve_call("sma_lookback", Lang::C),
            "TA_SMA_Lookback"
        );

        // C backend: bare indicator names resolve to guarded TA_<NAME>
        assert_eq!(registry.resolve_call("sma", Lang::C), "TA_SMA");
        assert_eq!(registry.resolve_call("ema", Lang::C), "TA_EMA");

        // C backend: _unguarded suffix resolves to TA_INT_<NAME>
        assert_eq!(registry.resolve_call("sma_unguarded", Lang::C), "TA_INT_SMA");
        assert_eq!(registry.resolve_call("ema_unguarded", Lang::C), "TA_INT_EMA");

        // Rust backend (bare names stay as-is)
        assert_eq!(registry.resolve_call("ema", Lang::Rust), "ema");
        assert_eq!(
            registry.resolve_call("ema_lookback", Lang::Rust),
            "ema_lookback"
        );

        // Java backend (camelCase for lookback, guarded for bare names)
        assert_eq!(
            registry.resolve_call("ema_lookback", Lang::Java),
            "emaLookback"
        );
        assert_eq!(registry.resolve_call("ema", Lang::Java), "ema");
        assert_eq!(registry.resolve_call("ema_unguarded", Lang::Java), "emaLogic");

        // .NET backend (PascalCase for lookback, guarded for bare names)
        assert_eq!(
            registry.resolve_call("sma_lookback", Lang::DotNet),
            "SmaLookback"
        );
        assert_eq!(registry.resolve_call("sma", Lang::DotNet), "Sma");
        assert_eq!(registry.resolve_call("sma_unguarded", Lang::DotNet), "SmaLogic");
    }

    #[test]
    fn test_registry_unknown_func_returns_unchanged() {
        let base = Path::new(env!("CARGO_MANIFEST_DIR")).join("../../ta_func_defs");
        let registry = Registry::from_dir(&base);
        assert_eq!(
            registry.resolve_call("unknown_func", Lang::C),
            "unknown_func"
        );
    }

    #[test]
    fn test_registry_resolve_type_mirrors_resolve_call() {
        let base = Path::new(env!("CARGO_MANIFEST_DIR")).join("../../ta_func_defs");
        let registry = Registry::from_dir(&base);
        assert_eq!(
            registry.resolve_type("sma_lookback", Lang::C),
            registry.resolve_call("sma_lookback", Lang::C)
        );
    }

    #[test]
    fn test_registry_bare_name_resolves_to_guarded() {
        let base = Path::new(env!("CARGO_MANIFEST_DIR")).join("../../ta_func_defs");
        let registry = Registry::from_dir(&base);
        // A bare indicator name resolves to the guarded variant
        assert_eq!(registry.resolve_call("sma", Lang::C), "TA_SMA");
        // _unguarded resolves to internal variant
        assert_eq!(registry.resolve_call("sma_unguarded", Lang::C), "TA_INT_SMA");
        // For Rust, bare names stay as-is
        assert_eq!(registry.resolve_call("sma", Lang::Rust), "sma");
    }

    #[test]
    fn test_registry_does_not_include_non_dirs() {
        let base = Path::new(env!("CARGO_MANIFEST_DIR")).join("../../ta_func_defs");
        let registry = Registry::from_dir(&base);
        // enums.yaml is a file at the top level, not a directory
        assert!(!registry.contains("enums"));
    }
}
