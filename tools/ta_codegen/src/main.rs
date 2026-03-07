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
}
