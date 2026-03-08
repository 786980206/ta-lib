use std::path::Path;

use serde::Deserialize;

use crate::ir::{FuncDef, Input, LookbackExpr, OptInput, Output, ParamType};
use super::logic::parse_logic_str;

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
    lookback: Option<serde_yaml::Value>,
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
        other => panic!("Unknown param type: {}", other),
    }
}

fn parse_lookback(value: &serde_yaml::Value) -> LookbackExpr {
    match value {
        serde_yaml::Value::Number(n) => {
            LookbackExpr::Literal(n.as_i64().expect("lookback must be an integer") as i32)
        }
        serde_yaml::Value::String(s) => {
            let trimmed = s.trim();
            // Check if this is a multi-line code block (contains semicolons or braces)
            if trimmed.contains(';') || trimmed.contains('{') {
                let stmts = parse_logic_str(trimmed);
                LookbackExpr::Code(stmts)
            } else if trimmed.contains('(') {
                // Expression with function calls (e.g., "optInTimePeriod - 1 + UNSTABLE_PERIOD(EMA)")
                // Wrap as "return <expr>;" and parse as code
                let wrapped = format!("int retValue;\nretValue = {};\nreturn retValue;", trimmed);
                let stmts = parse_logic_str(&wrapped);
                LookbackExpr::Code(stmts)
            } else {
                // Parse "optInTimePeriod - 1" style expressions
                let parts: Vec<&str> = trimmed.split_whitespace().collect();
                if parts.len() == 3 && parts[1] == "-" {
                    let param = parts[0].to_string();
                    let offset: i32 = parts[2].parse().expect("lookback offset must be an integer");
                    LookbackExpr::ParamMinus(param, offset)
                } else {
                    panic!("Unsupported lookback expression: {}", s);
                }
            }
        }
        _ => panic!("Unsupported lookback value: {:?}", value),
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

    let lookback = match &yaml.lookback {
        Some(value) => parse_lookback(value),
        None => LookbackExpr::Literal(0),
    };

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
        lookback,
        body: vec![],
    }
}
