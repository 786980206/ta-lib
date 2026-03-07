mod ir;
mod parser;

use std::path::Path;

fn main() {
    let yaml_path = Path::new("../../ta_func_defs/mult/mult.yaml");
    let (name, group, inputs, opt_inputs, outputs, lookback) =
        parser::yaml::parse_yaml(yaml_path);

    println!("Parsed: {} ({})", name, group);
    println!("  Inputs: {:?}", inputs);
    println!("  OptInputs: {:?}", opt_inputs);
    println!("  Outputs: {:?}", outputs);
    println!("  Lookback: {:?}", lookback);

    let logic_path = Path::new("../../ta_func_defs/mult/mult.logic");
    let body = parser::logic::parse_logic(logic_path);

    let func_def = ir::FuncDef {
        name,
        group,
        inputs,
        optional_inputs: opt_inputs,
        outputs,
        lookback,
        body,
    };
    println!(
        "Parsed {} with {} body statements",
        func_def.name,
        func_def.body.len()
    );
    for (i, stmt) in func_def.body.iter().enumerate() {
        println!("  stmt[{}]: {:?}", i, stmt);
    }
}
