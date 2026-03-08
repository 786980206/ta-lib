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
    flags: Option<String>,
    inputs: Vec<YamlParam>,
    optional_inputs: Option<Vec<YamlOptParam>>,
    outputs: Vec<YamlParam>,
}

#[derive(Deserialize)]
struct YamlParam {
    name: String,
    #[serde(rename = "type")]
    param_type: String,
    flags: Option<String>,
}

#[derive(Deserialize)]
struct YamlOptParam {
    name: String,
    #[serde(rename = "type")]
    param_type: String,
    range: Option<Vec<i32>>,
    default: Option<i32>,
    display_name: Option<String>,
    hint: Option<String>,
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
            range: p.range.map(|r| (r[0], r[1])),
            default: p.default,
            display_name: p.display_name,
            hint: p.hint,
        })
        .collect();

    let outputs = yaml
        .outputs
        .into_iter()
        .map(|p| Output {
            name: p.name,
            param_type: parse_param_type(&p.param_type),
            flags: p.flags,
        })
        .collect();

    FuncDef {
        name: yaml.name,
        group: yaml.group,
        description: yaml.description,
        camel_case: yaml.camel_case,
        hint: yaml.hint,
        flags: yaml.flags,
        inputs,
        optional_inputs: opt_inputs,
        outputs,
        lookback: None,
        body: vec![],
    }
}
