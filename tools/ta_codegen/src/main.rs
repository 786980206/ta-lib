use ta_codegen_lib::backends;
use ta_codegen_lib::ir;
use ta_codegen_lib::parser;
use ta_codegen_lib::server;
use ta_codegen_lib::server_gen;

use std::path::Path;

fn main() {
    let args: Vec<String> = std::env::args().collect();
    let command = args.get(1).map(|s| s.as_str()).unwrap_or("generate");
    match command {
        "generate" => {
            let func_filter = find_arg(&args, "--func");
            let backend_filter = find_arg(&args, "--backend");
            generate(func_filter.as_deref(), backend_filter.as_deref());
        }
        "generate-servers" => {
            let func_filter = find_arg(&args, "--func");
            let backend_filter = find_arg(&args, "--backend");
            generate_servers(func_filter.as_deref(), backend_filter.as_deref());
        }
        "serve" => server::run_server(),
        _ => {
            eprintln!("Usage: ta_codegen <command> [options]");
            eprintln!();
            eprintln!("Commands:");
            eprintln!("  generate         Generate code for all backends (default)");
            eprintln!("  generate-servers  Generate JSON-RPC server wrappers for each language");
            eprintln!("  serve            Start JSON-RPC validation server on stdin/stdout");
            eprintln!();
            eprintln!("Options for 'generate' / 'generate-servers':");
            eprintln!("  --func=NAME[,NAME,...]      Only generate specified functions (default: all)");
            eprintln!("  --backend=NAME[,NAME,...]    Only generate specified backends (default: all)");
            eprintln!("                               Backends: c, rust, java, dotnet, swig");
            std::process::exit(1);
        }
    }
}

fn find_arg(args: &[String], prefix: &str) -> Option<String> {
    let prefix_eq = format!("{}=", prefix);
    args.iter()
        .find(|a| a.starts_with(&prefix_eq))
        .map(|a| a[prefix_eq.len()..].to_string())
}

fn generate(func_filter: Option<&str>, backend_filter: Option<&str>) {
    let base = Path::new("../../ta_func_defs");

    // Discover all function definition directories
    let mut func_dirs: Vec<_> = std::fs::read_dir(base)
        .expect("Cannot read ta_func_defs directory")
        .filter_map(|e| e.ok())
        .filter(|e| e.path().is_dir())
        .collect();
    func_dirs.sort_by_key(|e| e.file_name());

    let filter_names: Option<Vec<String>> = func_filter.map(|f| {
        f.split(',')
            .map(|s| s.trim().to_uppercase())
            .collect()
    });

    let backends_to_run: Vec<&str> = match backend_filter {
        Some(b) => b.split(',').map(|s| s.trim()).collect(),
        None => vec!["c", "rust", "java", "dotnet", "swig"],
    };

    for entry in &func_dirs {
        let dir = entry.path();
        let func_name_lower = entry.file_name().to_string_lossy().to_string();

        // Apply function filter
        if let Some(ref names) = filter_names {
            if !names.iter().any(|n| n == &func_name_lower.to_uppercase()) {
                continue;
            }
        }

        let yaml_path = dir.join(format!("{}.yaml", func_name_lower));
        let c_path = dir.join(format!("{}.c", func_name_lower));

        if !yaml_path.exists() {
            eprintln!("Skipping {}: missing .yaml file", func_name_lower);
            continue;
        }

        if !c_path.exists() {
            eprintln!("Skipping {}: missing .c file", func_name_lower);
            continue;
        }

        let mut func_def = parser::yaml::parse_yaml(&yaml_path);
        let parsed = parser::c_source::parse_c_source(&c_path);
        func_def.body = parsed
            .functions
            .first()
            .expect("C source must contain at least one function")
            .body
            .clone();
        func_def.lookback = Some(ir::LookbackExpr::Code(parsed.lookback_body));

        for backend in &backends_to_run {
            generate_backend(&func_def, backend);
        }
    }
}

fn load_func_defs(func_filter: Option<&str>) -> Vec<ir::FuncDef> {
    let base = Path::new("../../ta_func_defs");

    let mut func_dirs: Vec<_> = std::fs::read_dir(base)
        .expect("Cannot read ta_func_defs directory")
        .filter_map(|e| e.ok())
        .filter(|e| e.path().is_dir())
        .collect();
    func_dirs.sort_by_key(|e| e.file_name());

    let filter_names: Option<Vec<String>> = func_filter.map(|f| {
        f.split(',')
            .map(|s| s.trim().to_uppercase())
            .collect()
    });

    let mut funcs = Vec::new();

    for entry in &func_dirs {
        let dir = entry.path();
        let func_name_lower = entry.file_name().to_string_lossy().to_string();

        if let Some(ref names) = filter_names {
            if !names.iter().any(|n| n == &func_name_lower.to_uppercase()) {
                continue;
            }
        }

        let yaml_path = dir.join(format!("{}.yaml", func_name_lower));
        let c_path = dir.join(format!("{}.c", func_name_lower));

        if !yaml_path.exists() || !c_path.exists() {
            continue;
        }

        let mut func_def = parser::yaml::parse_yaml(&yaml_path);
        let parsed = parser::c_source::parse_c_source(&c_path);
        func_def.body = parsed
            .functions
            .first()
            .expect("C source must contain at least one function")
            .body
            .clone();
        func_def.lookback = Some(ir::LookbackExpr::Code(parsed.lookback_body));
        funcs.push(func_def);
    }

    funcs
}

fn generate_servers(func_filter: Option<&str>, backend_filter: Option<&str>) {
    let funcs = load_func_defs(func_filter);

    if funcs.is_empty() {
        eprintln!("No function definitions found");
        std::process::exit(1);
    }

    let backends_to_run: Vec<&str> = match backend_filter {
        Some(b) => b.split(',').map(|s| s.trim()).collect(),
        None => vec!["c", "java", "dotnet", "swig"],
    };

    let out_base = Path::new("../../ta_codegen_output");

    for backend in &backends_to_run {
        match *backend {
            "c" => {
                let dir = out_base.join("c");
                std::fs::create_dir_all(&dir).unwrap();

                // Write ta_func.h stub for standalone compilation
                let stub = server_gen::generate_c_header_stub();
                let stub_path = dir.join("ta_func.h");
                std::fs::write(&stub_path, &stub).unwrap();
                println!("  C header stub -> {}", stub_path.display());

                let output = server_gen::generate_c_server(&funcs);
                let path = dir.join("ta_codegen_serve.c");
                std::fs::write(&path, &output).unwrap();
                println!("  C server -> {}", path.display());
            }
            "java" => {
                let dir = out_base.join("java");
                std::fs::create_dir_all(&dir).unwrap();

                let template = server_gen::generate_java_server(&funcs);
                let output = server_gen::inline_java_core_methods(&template, &dir, &funcs);
                let path = dir.join("TaCodegenServe.java");
                std::fs::write(&path, &output).unwrap();
                println!("  Java server -> {}", path.display());
            }
            "dotnet" => {
                let output = server_gen::generate_dotnet_server(&funcs);
                let dir = out_base.join("dotnet");
                std::fs::create_dir_all(&dir).unwrap();
                let path = dir.join("TaCodegenServe.cs");
                std::fs::write(&path, &output).unwrap();
                println!("  .NET server -> {}", path.display());
            }
            "swig" => {
                let output = server_gen::generate_swig_server(&funcs);
                let dir = out_base.join("swig");
                std::fs::create_dir_all(&dir).unwrap();
                let path = dir.join("ta_codegen_serve.py");
                std::fs::write(&path, &output).unwrap();
                println!("  SWIG/Python server -> {}", path.display());
            }
            "rust" => {
                println!("  Rust server is built-in (ta_codegen serve) — skipping");
            }
            _ => {
                eprintln!("Unknown backend: {}", backend);
            }
        }
    }

    println!("Server source files generated for {} function(s).", funcs.len());
}

fn generate_backend(func_def: &ir::FuncDef, backend: &str) {
    let out_base = Path::new("../../ta_codegen_output");

    match backend {
        "c" => {
            let output = backends::c::generate(func_def);
            let dir = out_base.join("c");
            std::fs::create_dir_all(&dir).unwrap();
            let path = dir.join(format!("ta_{}.c", func_def.name));
            std::fs::write(&path, &output).unwrap();
            println!("  {} -> {}", func_def.name, path.display());
        }
        "rust" => {
            let output = backends::rust_lang::generate(func_def);
            let dir = out_base.join("rust");
            std::fs::create_dir_all(&dir).unwrap();
            let path = dir.join(format!("{}.rs", func_def.name.to_lowercase()));
            std::fs::write(&path, &output).unwrap();
            println!("  {} -> {}", func_def.name, path.display());
        }
        "java" => {
            let output = backends::java::generate(func_def);
            let dir = out_base.join("java");
            std::fs::create_dir_all(&dir).unwrap();
            let path = dir.join(format!("Core_{}.java", func_def.name));
            std::fs::write(&path, &output).unwrap();
            println!("  {} -> {}", func_def.name, path.display());
        }
        "dotnet" => {
            let output = backends::dotnet::generate(func_def);
            let dir = out_base.join("dotnet");
            std::fs::create_dir_all(&dir).unwrap();
            let path = dir.join(format!("Core_{}.h", func_def.name));
            std::fs::write(&path, &output).unwrap();
            println!("  {} -> {}", func_def.name, path.display());
        }
        "swig" => {
            let output = backends::swig::generate(func_def);
            let dir = out_base.join("swig");
            std::fs::create_dir_all(&dir).unwrap();
            let path = dir.join(format!("ta_{}.swg", func_def.name));
            std::fs::write(&path, &output).unwrap();
            println!("  {} -> {}", func_def.name, path.display());
        }
        _ => {
            eprintln!("Unknown backend: {}", backend);
        }
    }
}
