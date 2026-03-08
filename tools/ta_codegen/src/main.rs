use ta_codegen_lib::backends;
use ta_codegen_lib::ir;
use ta_codegen_lib::parser;
use ta_codegen_lib::registry::Registry;
use ta_codegen_lib::server_gen;

use std::collections::HashMap;
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
        "build" => {
            let backend_filter = find_arg(&args, "--backend");
            build_servers(backend_filter.as_deref());
        }
        _ => {
            eprintln!("Usage: ta_codegen <command> [options]");
            eprintln!();
            eprintln!("Commands:");
            eprintln!("  generate         Generate code for all backends (default)");
            eprintln!("  generate-servers  Generate JSON-RPC server wrappers for each language");
            eprintln!("  build            Compile generated server source into executables");
            eprintln!("  serve            Start JSON-RPC validation server on stdin/stdout");
            eprintln!();
            eprintln!("Options for 'generate' / 'generate-servers' / 'build':");
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

    // Load indicator registry for cross-call resolution
    let registry = Registry::from_dir(base);

    // Load enum definitions
    let enums_path = base.join("enums.yaml");
    let enums = if enums_path.exists() {
        parser::enums::load_enums(&enums_path)
    } else {
        HashMap::new()
    };

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
            generate_backend(&func_def, backend, &enums, &registry);
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
                let dir = out_base.join("swig");
                std::fs::create_dir_all(&dir).unwrap();

                // Generate the SWIG interface file (.i)
                let iface = server_gen::generate_swig_interface(&funcs);
                let iface_path = dir.join("ta_codegen.i");
                std::fs::write(&iface_path, &iface).unwrap();
                println!("  SWIG interface -> {}", iface_path.display());

                // Generate the Python JSON-RPC server script
                let output = server_gen::generate_swig_server(&funcs);
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

fn build_servers(backend_filter: Option<&str>) {
    let backends_to_build: Vec<&str> = match backend_filter {
        Some(b) => b.split(',').map(|s| s.trim()).collect(),
        None => vec!["c", "java", "dotnet", "swig"],
    };

    let out_base = Path::new("../../ta_codegen_output");
    let bin_dir = Path::new("../../bin");

    for backend in &backends_to_build {
        match *backend {
            "c" => {
                print!("  Building C server... ");
                let src = out_base.join("c/ta_codegen_serve.c");
                let dst = bin_dir.join("ta_codegen_serve_c");
                match std::process::Command::new("gcc")
                    .args([
                        "-o",
                        dst.to_str().unwrap(),
                        src.to_str().unwrap(),
                        "-lm",
                        "-O2",
                        "-Wno-parentheses-equality",
                    ])
                    .status()
                {
                    Ok(s) if s.success() => println!("OK"),
                    Ok(s) => println!("FAILED (exit {})", s.code().unwrap_or(-1)),
                    Err(e) => println!("FAILED (gcc not found: {})", e),
                }
            }
            "java" => {
                print!("  Building Java server... ");
                let java_dir = out_base.join("java");
                let class_dir = bin_dir.join("ta_codegen_java");
                std::fs::create_dir_all(&class_dir).ok();
                match std::process::Command::new("javac")
                    .args([
                        "-d",
                        class_dir.to_str().unwrap(),
                        java_dir.join("TaCodegenServe.java").to_str().unwrap(),
                    ])
                    .status()
                {
                    Ok(s) if s.success() => println!("OK"),
                    Ok(s) => println!("FAILED (exit {})", s.code().unwrap_or(-1)),
                    Err(e) => println!("FAILED (javac not found: {})", e),
                }
            }
            "dotnet" => {
                // Build shared library from generated C files (needed by .NET P/Invoke)
                build_shared_lib(out_base, bin_dir);

                print!("  Building .NET server... ");
                let dotnet_dir = out_base.join("dotnet");
                let dotnet_out = bin_dir.join("ta_codegen_dotnet");
                std::fs::create_dir_all(&dotnet_out).ok();

                // Create a minimal .csproj if not present
                let csproj_path = dotnet_dir.join("TaCodegenServe.csproj");
                if !csproj_path.exists() {
                    let csproj = r#"<Project Sdk="Microsoft.NET.Sdk">
  <PropertyGroup>
    <OutputType>Exe</OutputType>
    <TargetFramework>net10.0</TargetFramework>
    <Nullable>enable</Nullable>
  </PropertyGroup>
</Project>"#;
                    std::fs::write(&csproj_path, csproj).unwrap();
                }

                match std::process::Command::new("dotnet")
                    .args([
                        "publish",
                        "-c", "Release",
                        "-o", dotnet_out.to_str().unwrap(),
                        dotnet_dir.to_str().unwrap(),
                    ])
                    .status()
                {
                    Ok(s) if s.success() => {
                        // Copy shared lib into dotnet output dir for P/Invoke discovery
                        let lib_name = if cfg!(target_os = "macos") {
                            "libta_codegen_funcs.dylib"
                        } else {
                            "libta_codegen_funcs.so"
                        };
                        let lib_src = bin_dir.join(lib_name);
                        let lib_dst = dotnet_out.join(lib_name);
                        if lib_src.exists() {
                            std::fs::copy(&lib_src, &lib_dst).ok();
                        }
                        println!("OK");
                    }
                    Ok(s) => println!("FAILED (exit {})", s.code().unwrap_or(-1)),
                    Err(e) => println!("FAILED (dotnet not found: {})", e),
                }
            }
            "swig" => {
                let swig_dir = out_base.join("swig");
                let c_dir = out_base.join("c");

                // Step 1: Run swig to generate wrapper C code + ta_lib.py
                print!("  Running swig... ");
                match std::process::Command::new("swig")
                    .args([
                        "-python",
                        "-o", swig_dir.join("ta_lib_wrap.c").to_str().unwrap(),
                        "-outdir", swig_dir.to_str().unwrap(),
                        swig_dir.join("ta_codegen.i").to_str().unwrap(),
                    ])
                    .status()
                {
                    Ok(s) if s.success() => println!("OK"),
                    Ok(s) => {
                        println!("FAILED (exit {})", s.code().unwrap_or(-1));
                        continue;
                    }
                    Err(e) => {
                        println!("FAILED (swig not found: {})", e);
                        continue;
                    }
                }

                // Step 2: Compile wrapper + generated C functions into _ta_lib.so
                print!("  Compiling SWIG module... ");
                let python_include = std::process::Command::new("python3")
                    .args(["-c", "import sysconfig; print(sysconfig.get_path('include'))"])
                    .output()
                    .map(|o| String::from_utf8_lossy(&o.stdout).trim().to_string())
                    .unwrap_or_default();

                let ext_suffix = std::process::Command::new("python3")
                    .args(["-c", "import sysconfig; print(sysconfig.get_config_var('EXT_SUFFIX'))"])
                    .output()
                    .map(|o| String::from_utf8_lossy(&o.stdout).trim().to_string())
                    .unwrap_or_else(|_| ".so".to_string());

                // Build a unity source that includes the wrapper + all C functions
                let mut unity = String::new();
                unity.push_str("#include \"ta_func.h\"\n");
                let mut c_names: Vec<String> = Vec::new();
                if let Ok(entries) = std::fs::read_dir(&c_dir) {
                    let mut sorted: Vec<_> = entries.filter_map(|e| e.ok()).collect();
                    sorted.sort_by_key(|e| e.file_name());
                    for entry in sorted {
                        let name = entry.file_name().to_string_lossy().to_string();
                        if name.starts_with("ta_") && name.ends_with(".c")
                            && name != "ta_codegen_serve.c"
                            && name != "ta_codegen_funcs.c"
                        {
                            c_names.push(name);
                        }
                    }
                }
                c_names.sort();
                if let Some(pos) = c_names.iter().position(|n| n == "ta_MA.c") {
                    let ma = c_names.remove(pos);
                    c_names.push(ma);
                }
                for name in &c_names {
                    unity.push_str(&format!("#include \"{}\"\n", name));
                }
                let swig_unity_path = swig_dir.join("ta_funcs_unity.c");
                std::fs::write(&swig_unity_path, &unity).unwrap();

                let so_name = format!("_ta_lib{}", ext_suffix);
                let so_path = bin_dir.join(&so_name);

                let shared_flag = if cfg!(target_os = "macos") {
                    "-dynamiclib"
                } else {
                    "-shared"
                };

                match std::process::Command::new("gcc")
                    .args([
                        shared_flag,
                        "-fPIC",
                        "-o", so_path.to_str().unwrap(),
                        swig_dir.join("ta_lib_wrap.c").to_str().unwrap(),
                        swig_unity_path.to_str().unwrap(),
                        &format!("-I{}", python_include),
                        &format!("-I{}", c_dir.to_str().unwrap()),
                        &format!("-I{}", swig_dir.to_str().unwrap()),
                        "-lm", "-O2",
                        "-Wno-parentheses-equality",
                        "-Wno-unused-function",
                        "-undefined", "dynamic_lookup",
                    ])
                    .status()
                {
                    Ok(s) if s.success() => println!("OK"),
                    Ok(s) => {
                        println!("FAILED (exit {})", s.code().unwrap_or(-1));
                        continue;
                    }
                    Err(e) => {
                        println!("FAILED (gcc not found: {})", e);
                        continue;
                    }
                }

                // Step 3: Copy ta_lib.py (SWIG-generated module) and server script to bin/
                let swig_py = swig_dir.join("ta_lib.py");
                if swig_py.exists() {
                    std::fs::copy(&swig_py, bin_dir.join("ta_lib.py")).ok();
                }
                std::fs::copy(
                    swig_dir.join("ta_codegen_serve.py"),
                    bin_dir.join("ta_codegen_serve.py"),
                ).ok();
                println!("  SWIG/Python server installed");
            }
            "rust" => {
                println!("  Rust server: built-in (ta_codegen serve)");
            }
            _ => {
                eprintln!("  Unknown backend: {}", backend);
            }
        }
    }
}

/// Build a shared library from the generated C files.
/// This is used by both the Python (ctypes) and .NET (P/Invoke) servers.
/// The shared lib exports all TA_* functions and is placed in bin/.
fn build_shared_lib(out_base: &Path, bin_dir: &Path) {
    let marker = bin_dir.join(".shared_lib_built");
    if marker.exists() {
        return; // Already built this run
    }

    print!("  Building shared library... ");
    let c_dir = out_base.join("c");
    let lib_name = if cfg!(target_os = "macos") {
        "libta_codegen_funcs.dylib"
    } else {
        "libta_codegen_funcs.so"
    };
    let dst = bin_dir.join(lib_name);

    let shared_flag = if cfg!(target_os = "macos") {
        "-dynamiclib"
    } else {
        "-shared"
    };

    // Generate a unified source file that includes all individual C files.
    // This handles forward declarations (e.g., MA calls SMA/EMA/WMA).
    let mut unity_src = String::new();
    unity_src.push_str("/* Unity build for shared library */\n");
    unity_src.push_str("#include \"ta_func.h\"\n");

    let mut c_names: Vec<String> = Vec::new();
    if let Ok(entries) = std::fs::read_dir(&c_dir) {
        let mut sorted: Vec<_> = entries.filter_map(|e| e.ok()).collect();
        sorted.sort_by_key(|e| e.file_name());
        for entry in sorted {
            let name = entry.file_name().to_string_lossy().to_string();
            if name.starts_with("ta_") && name.ends_with(".c")
                && name != "ta_codegen_serve.c"
                && name != "ta_codegen_funcs.c"
            {
                c_names.push(name);
            }
        }
    }

    if c_names.is_empty() {
        println!("FAILED (no C source files found)");
        return;
    }

    // Sort alphabetically, but move MA to end (it calls SMA/EMA/WMA)
    c_names.sort();
    if let Some(pos) = c_names.iter().position(|n| n == "ta_MA.c") {
        let ma = c_names.remove(pos);
        c_names.push(ma);
    }
    for name in &c_names {
        unity_src.push_str(&format!("#include \"{}\"\n", name));
    }

    let unity_path = c_dir.join("ta_codegen_funcs.c");
    std::fs::write(&unity_path, &unity_src).unwrap();

    let args = vec![
        shared_flag.to_string(),
        "-fPIC".to_string(),
        "-o".to_string(),
        dst.to_str().unwrap().to_string(),
        unity_path.to_str().unwrap().to_string(),
        format!("-I{}", c_dir.to_str().unwrap()),
        "-lm".to_string(),
        "-O2".to_string(),
        "-Wno-parentheses-equality".to_string(),
    ];

    match std::process::Command::new("gcc")
        .args(&args)
        .status()
    {
        Ok(s) if s.success() => {
            println!("OK");
            std::fs::write(&marker, "").ok();
        }
        Ok(s) => println!("FAILED (exit {})", s.code().unwrap_or(-1)),
        Err(e) => println!("FAILED (gcc not found: {})", e),
    }
}

fn generate_backend(func_def: &ir::FuncDef, backend: &str, enums: &HashMap<String, ir::EnumDef>, registry: &Registry) {
    let out_base = Path::new("../../ta_codegen_output");

    match backend {
        "c" => {
            let output = backends::c::generate(func_def, enums, registry);
            let dir = out_base.join("c");
            std::fs::create_dir_all(&dir).unwrap();
            let path = dir.join(format!("ta_{}.c", func_def.name));
            std::fs::write(&path, &output).unwrap();
            println!("  {} -> {}", func_def.name, path.display());
        }
        "rust" => {
            let output = backends::rust_lang::generate(func_def, enums, registry);
            let dir = out_base.join("rust");
            std::fs::create_dir_all(&dir).unwrap();
            let path = dir.join(format!("{}.rs", func_def.name.to_lowercase()));
            std::fs::write(&path, &output).unwrap();
            println!("  {} -> {}", func_def.name, path.display());
        }
        "java" => {
            let output = backends::java::generate(func_def, enums);
            let dir = out_base.join("java");
            std::fs::create_dir_all(&dir).unwrap();
            let path = dir.join(format!("Core_{}.java", func_def.name));
            std::fs::write(&path, &output).unwrap();
            println!("  {} -> {}", func_def.name, path.display());
        }
        "dotnet" => {
            let output = backends::dotnet::generate(func_def, enums);
            let dir = out_base.join("dotnet");
            std::fs::create_dir_all(&dir).unwrap();
            let path = dir.join(format!("Core_{}.h", func_def.name));
            std::fs::write(&path, &output).unwrap();
            println!("  {} -> {}", func_def.name, path.display());
        }
        "swig" => {
            let output = backends::swig::generate(func_def, enums);
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
