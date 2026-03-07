mod backends;
mod ir;
mod parser;
mod server;

use std::path::Path;

fn main() {
    let args: Vec<String> = std::env::args().collect();
    let command = args.get(1).map(|s| s.as_str()).unwrap_or("generate");
    match command {
        "generate" => generate(),
        "serve" => server::run_server(),
        _ => eprintln!("Usage: ta_codegen [generate|serve]"),
    }
}

fn generate() {
    let yaml_path = Path::new("../../ta_func_defs/mult/mult.yaml");
    let (name, group, description, inputs, opt_inputs, outputs, lookback) =
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
        description,
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

    // Generate C backend output
    let c_output = backends::c::generate(&func_def);
    let out_dir = Path::new("../../ta_codegen_output/c");
    std::fs::create_dir_all(out_dir).unwrap();
    std::fs::write(out_dir.join(format!("ta_{}.c", func_def.name)), &c_output).unwrap();
    println!(
        "Generated C: ta_codegen_output/c/ta_{}.c",
        func_def.name
    );

    // Generate Rust backend output
    let rust_output = backends::rust_lang::generate(&func_def);
    let rust_out_dir = Path::new("../../ta_codegen_output/rust");
    std::fs::create_dir_all(rust_out_dir).unwrap();
    std::fs::write(
        rust_out_dir.join(format!("{}.rs", func_def.name.to_lowercase())),
        &rust_output,
    )
    .unwrap();
    println!(
        "Generated Rust: ta_codegen_output/rust/{}.rs",
        func_def.name.to_lowercase()
    );

    // Generate Java backend output
    let java_output = backends::java::generate(&func_def);
    let java_out_dir = Path::new("../../ta_codegen_output/java");
    std::fs::create_dir_all(java_out_dir).unwrap();
    std::fs::write(
        java_out_dir.join(format!("Core_{}.java", func_def.name)),
        &java_output,
    )
    .unwrap();
    println!("Generated Java: ta_codegen_output/java/Core_{}.java", func_def.name);

    // Generate .NET backend output
    let dotnet_output = backends::dotnet::generate(&func_def);
    let dotnet_out_dir = Path::new("../../ta_codegen_output/dotnet");
    std::fs::create_dir_all(dotnet_out_dir).unwrap();
    std::fs::write(
        dotnet_out_dir.join(format!("Core_{}.h", func_def.name)),
        &dotnet_output,
    )
    .unwrap();
    println!("Generated .NET: ta_codegen_output/dotnet/Core_{}.h", func_def.name);

    // Generate SWIG backend output
    let swig_output = backends::swig::generate(&func_def);
    let swig_out_dir = Path::new("../../ta_codegen_output/swig");
    std::fs::create_dir_all(swig_out_dir).unwrap();
    std::fs::write(
        swig_out_dir.join(format!("ta_{}.swg", func_def.name)),
        &swig_output,
    )
    .unwrap();
    println!("Generated SWIG: ta_codegen_output/swig/ta_{}.swg", func_def.name);
}
