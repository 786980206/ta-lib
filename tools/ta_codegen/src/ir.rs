/// A complete function definition (metadata + logic).
#[derive(Debug, Clone)]
pub struct FuncDef {
    pub name: String,
    pub group: String,
    pub description: Option<String>,
    pub camel_case: Option<String>,
    pub hint: Option<String>,
    pub flags: Vec<String>,
    pub inputs: Vec<Input>,
    pub optional_inputs: Vec<OptInput>,
    pub outputs: Vec<Output>,
    pub lookback: Option<LookbackExpr>,
    pub body: Vec<Statement>,
}

#[derive(Debug, Clone)]
pub struct Input {
    pub name: String,
    pub param_type: ParamType,
}

#[derive(Debug, Clone)]
pub struct OptInput {
    pub name: String,
    pub param_type: ParamType,
    pub range: Option<(i32, i32)>,
    pub default: Option<f64>,
    pub display_name: Option<String>,
    pub hint: Option<String>,
    pub flags: Vec<String>,
    /// Optimization hints: [`suggested_start`, `suggested_end`, `suggested_increment`]
    pub suggested: Option<(f64, f64, f64)>,
}

#[derive(Debug, Clone)]
pub struct Output {
    pub name: String,
    pub param_type: ParamType,
    pub flags: Vec<String>,
}

#[derive(Debug, Clone, PartialEq)]
pub enum ParamType {
    Real,
    Integer,
    /// An enum parameter type, e.g. `Enum("MAType")`.
    /// The string is the enum name as defined in `enums.yaml`.
    Enum(String),
    /// Price input: expands to multiple array parameters (e.g., high, low, close).
    /// The vector contains component names like "open", "high", "low", "close", "volume".
    Price(Vec<String>),
}

/// An enum type definition (loaded from `enums.yaml`).
#[derive(Debug, Clone)]
pub struct EnumDef {
    pub name: String,
    pub variants: Vec<EnumVariant>,
}

/// A single variant of an enum type.
#[derive(Debug, Clone)]
pub struct EnumVariant {
    /// C constant name, e.g. `TA_MAType_SMA`
    pub c_name: String,
    /// `PascalCase` name used in Java/.NET, e.g. `Sma`
    pub pascal_name: String,
    /// `UPPER_CASE` short name used in source labels, e.g. `SMA`
    pub short_name: String,
    /// Integer value
    pub value: i32,
}

#[derive(Debug, Clone)]
pub enum LookbackExpr {
    Literal(i32),
    ParamMinus(String, i32),
    /// Complex lookback body (parsed from multi-line YAML string).
    /// Contains the full lookback function body as statements.
    Code(Vec<Statement>),
}

// --- Logic AST ---

#[derive(Debug, Clone)]
pub enum Statement {
    VarDecl {
        var_type: VarType,
        name: String,
        init: Option<Expr>,
    },
    Assign {
        target: Expr,
        value: Expr,
        /// True if originally written as a compound assignment (+=, -=, etc.)
        compound: bool,
    },
    While {
        condition: Expr,
        body: Vec<Statement>,
    },
    /// do { body } while(condition);
    DoWhile {
        condition: Expr,
        body: Vec<Statement>,
    },
    /// Countdown for loop: `for( var = count; var > 0; var-- ) { body }`
    /// Renders as `for var in (1..=count).rev()` in Rust.
    For {
        var: String,
        count: Expr,
        body: Vec<Statement>,
    },
    If {
        condition: Expr,
        then_body: Vec<Statement>,
        else_body: Vec<Statement>,
    },
    Return {
        value: Option<Expr>,
    },
    Break,
    Continue,
    /// switch(expr) { case Value: stmts; break; ... default: stmts; }
    Switch {
        expr: Expr,
        cases: Vec<(String, Vec<Statement>)>,
        default: Vec<Statement>,
    },
    /// C-style for loop: for(init; cond; update) { body }
    ForC {
        init: Box<Statement>,
        condition: Expr,
        update: Box<Statement>,
        body: Vec<Statement>,
    },
    /// A block of statements (used for `ARRAY_COPY` expansion in some backends).
    Block {
        body: Vec<Statement>,
    },
}

#[derive(Debug, Clone, PartialEq)]
pub enum VarType {
    Real,
    Integer,
    Index,
    RetCodeType,
}

#[derive(Debug, Clone)]
pub enum Expr {
    Literal(f64),
    IntLiteral(i64),
    Var(String),
    ArrayAccess(String, Box<Expr>),
    BinOp(Box<Expr>, BinOp, Box<Expr>),
    Cast(VarType, Box<Expr>),
    Not(Box<Expr>),
    /// Function/builtin call: `UNSTABLE_PERIOD(RSI)`, `IS_ZERO(x)`, `ARRAY_COPY`(...),
    /// `RSI_Lookback(params`...), etc.
    FuncCall(String, Vec<Expr>),
    /// Pointer dereference: *outBegIdx
    PointerDeref(String),
    /// Address-of: &var or &var[idx]
    AddressOf(Box<Expr>),
    /// Post-increment: var++ (evaluates to var, then increments)
    PostIncrement(Box<Expr>),
    /// Post-decrement: var-- (evaluates to var, then decrements)
    PostDecrement(Box<Expr>),
    /// Ternary: condition ? `then_expr` : `else_expr`
    Ternary(Box<Expr>, Box<Expr>, Box<Expr>),
}

#[derive(Debug, Clone)]
pub enum BinOp {
    Add,
    Sub,
    Mul,
    Div,
    Mod, // % operator
    LessEq,
    Less,
    Greater,
    GreaterEq,
    Eq,
    NotEq,
    And,
    Shr, // >> right shift
    Shl, // << left shift
    Or,
}
