/// A complete function definition (metadata + logic).
#[derive(Debug, Clone)]
pub struct FuncDef {
    pub name: String,
    pub group: String,
    pub description: Option<String>,
    pub inputs: Vec<Input>,
    pub optional_inputs: Vec<OptInput>,
    pub outputs: Vec<Output>,
    pub lookback: LookbackExpr,
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
    pub default: Option<i32>,
}

#[derive(Debug, Clone)]
pub struct Output {
    pub name: String,
    pub param_type: ParamType,
}

#[derive(Debug, Clone, PartialEq)]
pub enum ParamType {
    Real,
    Integer,
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
        value: String,
    },
    /// A block of statements (used for ARRAY_COPY expansion in some backends).
    Block {
        body: Vec<Statement>,
    },
}

#[derive(Debug, Clone, PartialEq)]
pub enum VarType {
    Real,
    Integer,
    Index,
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
    /// Function/builtin call: UNSTABLE_PERIOD(RSI), IS_ZERO(x), ARRAY_COPY(...),
    /// RSI_Lookback(params...), etc.
    FuncCall(String, Vec<Expr>),
}

#[derive(Debug, Clone)]
pub enum BinOp {
    Add,
    Sub,
    Mul,
    Div,
    LessEq,
    Less,
    Greater,
    GreaterEq,
    Eq,
    NotEq,
    And,
    Or,
}
