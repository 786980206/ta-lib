use std::path::Path;

use serde::Deserialize;

use crate::ir::{Input, LookbackExpr, OptInput, Output, ParamType};

#[derive(Deserialize)]
struct YamlFunc {
    name: String,
    group: String,
    inputs: Vec<YamlParam>,
    optional_inputs: Option<Vec<YamlOptParam>>,
    outputs: Vec<YamlParam>,
    lookback: serde_yaml::Value,
}

#[derive(Deserialize)]
struct YamlParam {
    name: String,
    #[serde(rename = "type")]
    param_type: String,
}

#[derive(Deserialize)]
struct YamlOptParam {
    name: String,
    #[serde(rename = "type")]
    param_type: String,
    range: Option<Vec<i32>>,
    default: Option<i32>,
}

fn parse_param_type(s: &str) -> ParamType {
    match s {
        "real" => ParamType::Real,
        "integer" => ParamType::Integer,
        other => panic!("Unknown param type: {}", other),
    }
}

fn parse_lookback(value: &serde_yaml::Value) -> LookbackExpr {
    match value {
        serde_yaml::Value::Number(n) => {
            LookbackExpr::Literal(n.as_i64().expect("lookback must be an integer") as i32)
        }
        serde_yaml::Value::String(s) => {
            // Parse "optInTimePeriod - 1" style expressions
            let parts: Vec<&str> = s.split_whitespace().collect();
            if parts.len() == 3 && parts[1] == "-" {
                let param = parts[0].to_string();
                let offset: i32 = parts[2].parse().expect("lookback offset must be an integer");
                LookbackExpr::ParamMinus(param, offset)
            } else {
                panic!("Unsupported lookback expression: {}", s);
            }
        }
        _ => panic!("Unsupported lookback value: {:?}", value),
    }
}

pub fn parse_yaml(
    path: &Path,
) -> (
    String,
    String,
    Vec<Input>,
    Vec<OptInput>,
    Vec<Output>,
    LookbackExpr,
) {
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
        })
        .collect();

    let outputs = yaml
        .outputs
        .into_iter()
        .map(|p| Output {
            name: p.name,
            param_type: parse_param_type(&p.param_type),
        })
        .collect();

    let lookback = parse_lookback(&yaml.lookback);

    (yaml.name, yaml.group, inputs, opt_inputs, outputs, lookback)
}
