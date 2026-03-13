use std::collections::HashMap;
use std::path::Path;

use crate::ir::HelperDef;
use crate::parser::c_source::parse_helper_file;

/// Registry of helper functions available for inlining.
pub struct HelperRegistry {
    helpers: HashMap<String, HelperDef>,
}

impl HelperRegistry {
    /// Build the registry by scanning `base_dir/helpers/*.c`.
    pub fn from_dir(base_dir: &Path) -> Self {
        let mut helpers = HashMap::new();
        let helpers_dir = base_dir.join("helpers");

        if let Ok(entries) = std::fs::read_dir(&helpers_dir) {
            for entry in entries.filter_map(Result::ok) {
                let path = entry.path();
                if path.extension().and_then(|e| e.to_str()) == Some("c") {
                    let parsed = parse_helper_file(&path);
                    for helper in parsed {
                        helpers.insert(helper.name.clone(), helper);
                    }
                }
            }
        }

        HelperRegistry { helpers }
    }

    /// Look up a helper by function name.
    pub fn get(&self, name: &str) -> Option<&HelperDef> {
        self.helpers.get(name)
    }
}
