use std::path::Path;

use serde::Deserialize;

use crate::ir::{FuncDef, Input, OptInput, Output, ParamType};

#[derive(Deserialize)]
struct YamlFunc {
    name: String,
    group: String,
    description: Option<String>,
    camel_case: Option<String>,
    hint: Option<String>,
    #[serde(default)]
    flags: YamlFlags,
    inputs: Vec<YamlInput>,
    optional_inputs: Option<Vec<YamlOptParam>>,
    outputs: Vec<YamlOutput>,
}

/// Flags can be a single string or a list of strings.
#[derive(Deserialize, Default, Clone)]
#[serde(untagged)]
enum YamlFlags {
    #[default]
    None,
    Single(String),
    List(Vec<String>),
}

impl YamlFlags {
    fn into_vec(self) -> Vec<String> {
        match self {
            YamlFlags::None => vec![],
            YamlFlags::Single(s) => vec![s],
            YamlFlags::List(v) => v,
        }
    }
}

#[derive(Deserialize)]
struct YamlInput {
    name: String,
    #[serde(rename = "type")]
    param_type: String,
}

#[derive(Deserialize)]
struct YamlOptParam {
    name: String,
    #[serde(rename = "type")]
    param_type: String,
    range: Option<Vec<f64>>,
    default: Option<f64>,
    display_name: Option<String>,
    hint: Option<String>,
    #[serde(default)]
    flags: YamlFlags,
    /// Optimization hints: [suggested_start, suggested_end, suggested_increment]
    suggested: Option<Vec<f64>>,
}

#[derive(Deserialize)]
struct YamlOutput {
    name: String,
    #[serde(rename = "type")]
    param_type: String,
    #[serde(default)]
    flags: YamlFlags,
}

fn parse_param_type(s: &str) -> ParamType {
    match s {
        "real" => ParamType::Real,
        "integer" => ParamType::Integer,
        other if other.starts_with("enum:") => {
            ParamType::Enum(other["enum:".len()..].to_string())
        }
        other => panic!("Unknown param type: {}", other),
    }
}

pub fn parse_yaml(path: &Path) -> FuncDef {
    let content = std::fs::read_to_string(path)
        .unwrap_or_else(|e| panic!("Failed to read {}: {}", path.display(), e));

    let yaml: YamlFunc = serde_yaml::from_str(&content)
        .unwrap_or_else(|e| panic!("Failed to parse {}: {}", path.display(), e));

    let inputs = yaml
        .inputs
        .into_iter()
        .map(|p| Input {
            name: p.name,
            param_type: parse_param_type(&p.param_type),
        })
        .collect();

    let opt_inputs = yaml
        .optional_inputs
        .unwrap_or_default()
        .into_iter()
        .map(|p| OptInput {
            name: p.name,
            param_type: parse_param_type(&p.param_type),
            range: p.range.map(|r| (r[0] as i32, r[1] as i32)),
            default: p.default,
            display_name: p.display_name,
            hint: p.hint,
            flags: p.flags.into_vec(),
            suggested: p.suggested.map(|s| (s[0], s[1], s[2])),
        })
        .collect();

    let outputs = yaml
        .outputs
        .into_iter()
        .map(|p| Output {
            name: p.name,
            param_type: parse_param_type(&p.param_type),
            flags: p.flags.into_vec(),
        })
        .collect();

    FuncDef {
        name: yaml.name,
        group: yaml.group,
        description: yaml.description,
        camel_case: yaml.camel_case,
        hint: yaml.hint,
        flags: yaml.flags.into_vec(),
        inputs,
        optional_inputs: opt_inputs,
        outputs,
        lookback: None,
        body: vec![],
    }
}
