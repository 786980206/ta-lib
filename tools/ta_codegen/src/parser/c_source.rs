use std::path::Path;

use crate::ir::{BinOp, Expr, Statement, VarType};

// --- Public API ---

#[derive(Debug, Clone)]
pub struct ParsedCSource {
    pub lookback_body: Vec<Statement>,
    pub functions: Vec<ParsedCFunction>,
}

#[derive(Debug, Clone)]
pub struct ParsedCFunction {
    pub name: String,
    pub is_internal: bool,
    pub body: Vec<Statement>,
}

/// Parse a `.c` source file containing TA-Lib function definitions.
pub fn parse_c_source(path: &Path) -> ParsedCSource {
    let input = std::fs::read_to_string(path)
        .unwrap_or_else(|e| panic!("Failed to read {}: {}", path.display(), e));
    parse_c_source_str(&input)
}

/// Parse C source from a string.
pub fn parse_c_source_str(source: &str) -> ParsedCSource {
    let tokens = tokenize(source);
    extract_functions(&tokens)
}

// --- Tokenizer ---

#[derive(Debug, Clone, PartialEq)]
enum Token {
    Ident(String),
    Number(f64),
    IntNumber(i64),
    Op(String),
    Star,
    Ampersand,
    LBrace,
    RBrace,
    LBracket,
    RBracket,
    LParen,
    RParen,
    Bang,
    Semicolon,
    Comma,
    Colon,
    PlusPlus,
    MinusMinus,
    Question,
}

/// Strip #define and #undef lines (including multi-line continuations with \)
fn strip_local_macros(input: &str) -> String {
    let mut result = Vec::new();
    let mut in_macro = false;
    for line in input.lines() {
        let trimmed = line.trim();
        if in_macro {
            // Continue skipping until a line doesn't end with backslash
            in_macro = trimmed.ends_with('\\');
            continue;
        }
        if trimmed.starts_with("#define ")
            || trimmed.starts_with("#define\t")
            || trimmed.starts_with("#undef ")
            || trimmed.starts_with("#undef\t")
        {
            in_macro = trimmed.ends_with('\\');
            continue;
        }
        result.push(line);
    }
    result.join("\n")
}

#[allow(clippy::cognitive_complexity, clippy::too_many_lines)]
fn tokenize(input: &str) -> Vec<Token> {
    let input = strip_local_macros(input);
    let mut tokens = Vec::new();
    let chars: Vec<char> = input.chars().collect();
    let mut i = 0;

    while i < chars.len() {
        let c = chars[i];

        // Skip whitespace
        if c == ' ' || c == '\t' || c == '\n' || c == '\r' {
            i += 1;
            continue;
        }

        // Skip single-line comments
        if c == '/' && i + 1 < chars.len() && chars[i + 1] == '/' {
            while i < chars.len() && chars[i] != '\n' {
                i += 1;
            }
            continue;
        }

        // Skip multi-line comments
        if c == '/' && i + 1 < chars.len() && chars[i + 1] == '*' {
            i += 2;
            while i + 1 < chars.len() && !(chars[i] == '*' && chars[i + 1] == '/') {
                i += 1;
            }
            i += 2;
            continue;
        }

        // Semicolon
        if c == ';' {
            tokens.push(Token::Semicolon);
            i += 1;
            continue;
        }

        // Comma
        if c == ',' {
            tokens.push(Token::Comma);
            i += 1;
            continue;
        }

        // Colon
        if c == ':' {
            tokens.push(Token::Colon);
            i += 1;
            continue;
        }

        // Parentheses
        if c == '(' {
            tokens.push(Token::LParen);
            i += 1;
            continue;
        }
        if c == ')' {
            tokens.push(Token::RParen);
            i += 1;
            continue;
        }

        // Braces and brackets
        if c == '{' {
            tokens.push(Token::LBrace);
            i += 1;
            continue;
        }
        if c == '}' {
            tokens.push(Token::RBrace);
            i += 1;
            continue;
        }
        if c == '[' {
            tokens.push(Token::LBracket);
            i += 1;
            continue;
        }
        if c == ']' {
            tokens.push(Token::RBracket);
            i += 1;
            continue;
        }

        // Bang (!) — check for != first
        if c == '!' {
            if i + 1 < chars.len() && chars[i + 1] == '=' {
                tokens.push(Token::Op("!=".to_string()));
                i += 2;
                continue;
            }
            tokens.push(Token::Bang);
            i += 1;
            continue;
        }

        // Plus: ++, +=, or +
        if c == '+' {
            if i + 1 < chars.len() {
                if chars[i + 1] == '+' {
                    tokens.push(Token::PlusPlus);
                    i += 2;
                    continue;
                }
                if chars[i + 1] == '=' {
                    tokens.push(Token::Op("+=".to_string()));
                    i += 2;
                    continue;
                }
            }
            tokens.push(Token::Op("+".to_string()));
            i += 1;
            continue;
        }

        // Minus: --, -=, or -
        if c == '-' {
            if i + 1 < chars.len() {
                if chars[i + 1] == '-' {
                    tokens.push(Token::MinusMinus);
                    i += 2;
                    continue;
                }
                if chars[i + 1] == '=' {
                    tokens.push(Token::Op("-=".to_string()));
                    i += 2;
                    continue;
                }
            }
            tokens.push(Token::Op("-".to_string()));
            i += 1;
            continue;
        }

        // Star: *=, or *
        if c == '*' {
            if i + 1 < chars.len() && chars[i + 1] == '=' {
                tokens.push(Token::Op("*=".to_string()));
                i += 2;
                continue;
            }
            tokens.push(Token::Star);
            i += 1;
            continue;
        }

        // Slash: /= or /
        if c == '/' {
            if i + 1 < chars.len() && chars[i + 1] == '=' {
                tokens.push(Token::Op("/=".to_string()));
                i += 2;
                continue;
            }
            tokens.push(Token::Op("/".to_string()));
            i += 1;
            continue;
        }

        // Percent: %
        if c == '%' {
            tokens.push(Token::Op("%".to_string()));
            i += 1;
            continue;
        }

        // Two-char operators starting with <, >, =, &, |
        if c == '<' {
            if i + 1 < chars.len() && chars[i + 1] == '=' {
                tokens.push(Token::Op("<=".to_string()));
                i += 2;
            } else if i + 1 < chars.len() && chars[i + 1] == '<' {
                tokens.push(Token::Op("<<".to_string()));
                i += 2;
            } else {
                tokens.push(Token::Op("<".to_string()));
                i += 1;
            }
            continue;
        }
        if c == '>' {
            if i + 1 < chars.len() && chars[i + 1] == '=' {
                tokens.push(Token::Op(">=".to_string()));
                i += 2;
            } else if i + 1 < chars.len() && chars[i + 1] == '>' {
                tokens.push(Token::Op(">>".to_string()));
                i += 2;
            } else {
                tokens.push(Token::Op(">".to_string()));
                i += 1;
            }
            continue;
        }
        if c == '=' {
            if i + 1 < chars.len() && chars[i + 1] == '=' {
                tokens.push(Token::Op("==".to_string()));
                i += 2;
            } else {
                tokens.push(Token::Op("=".to_string()));
                i += 1;
            }
            continue;
        }
        if c == '&' && i + 1 < chars.len() && chars[i + 1] == '&' {
            tokens.push(Token::Op("&&".to_string()));
            i += 2;
            continue;
        }
        if c == '&' {
            tokens.push(Token::Ampersand);
            i += 1;
            continue;
        }
        if c == '|' && i + 1 < chars.len() && chars[i + 1] == '|' {
            tokens.push(Token::Op("||".to_string()));
            i += 2;
            continue;
        }

        // Numbers (including leading-dot floats like .0)
        if c.is_ascii_digit() || (c == '.' && i + 1 < chars.len() && chars[i + 1].is_ascii_digit())
        {
            let start = i;
            let mut is_float = c == '.';
            if c == '.' {
                // Leading-dot float: .0, .5, etc.
                i += 1;
            }
            while i < chars.len() && chars[i].is_ascii_digit() {
                i += 1;
            }
            if !is_float && i < chars.len() && chars[i] == '.' {
                is_float = true;
                i += 1;
                while i < chars.len() && chars[i].is_ascii_digit() {
                    i += 1;
                }
            }
            if is_float {
                // Skip trailing 'f' suffix (e.g., 0.0f)
                if i < chars.len() && chars[i] == 'f' {
                    i += 1;
                }
                let s: String = chars[start..i].iter().collect();
                let cleaned = s.trim_end_matches('f');
                tokens.push(Token::Number(cleaned.parse().unwrap()));
            } else {
                let s: String = chars[start..i].iter().collect();
                tokens.push(Token::IntNumber(s.parse().unwrap()));
            }
            continue;
        }

        // Identifiers
        if c.is_ascii_alphabetic() || c == '_' {
            let start = i;
            while i < chars.len() && (chars[i].is_ascii_alphanumeric() || chars[i] == '_') {
                i += 1;
            }
            let s: String = chars[start..i].iter().collect();
            tokens.push(Token::Ident(s));
            continue;
        }

        // Question mark (ternary operator)
        if c == '?' {
            tokens.push(Token::Question);
            i += 1;
            continue;
        }

        // Hash: skip any remaining preprocessor directives
        if c == '#' {
            while i < chars.len() && chars[i] != '\n' {
                i += 1;
            }
            continue;
        }

        panic!("Unexpected character: {c:?} at position {i}");
    }

    tokens
}

// --- Function Extraction ---

/// Scan tokens for function definitions and extract their bodies.
fn extract_functions(tokens: &[Token]) -> ParsedCSource {
    let mut lookback_body = Vec::new();
    let mut functions = Vec::new();
    let mut i = 0;

    while i < tokens.len() {
        // Look for lookback function:
        //   Old: int TA_XXX_Lookback ( ... ) { body }
        //   New: int xxx_lookback ( ... ) { body }
        if matches!(&tokens[i], Token::Ident(s) if s == "int") {
            if let Some(Token::Ident(name)) = tokens.get(i + 1) {
                let is_old_lookback = name.contains("_Lookback") && name.starts_with("TA_");
                let is_new_lookback = name.ends_with("_lookback");
                if is_old_lookback || is_new_lookback {
                    // Skip to opening brace
                    if let Some(brace_start) = find_open_brace(tokens, i + 2) {
                        if let Some(brace_end) = find_matching_brace(tokens, brace_start) {
                            let body_tokens = &tokens[brace_start + 1..brace_end];
                            lookback_body = parse_body(body_tokens);
                            i = brace_end + 1;
                            continue;
                        }
                    }
                }
            }
        }

        // Look for implementation function:
        //   Old: TA_RetCode TA_XXX ( ... ) { body }
        //   New: TA_RetCode xxx ( ... ) { body }  (plain indicator name)
        if matches!(&tokens[i], Token::Ident(s) if s == "TA_RetCode") {
            if let Some(Token::Ident(name)) = tokens.get(i + 1) {
                let is_old_func = name.starts_with("TA_");
                let is_new_func = !name.starts_with("TA_") && !name.ends_with("_lookback");
                if is_old_func || is_new_func {
                    let func_name = name.clone();
                    let is_internal = func_name.starts_with("TA_INT_");
                    if let Some(brace_start) = find_open_brace(tokens, i + 2) {
                        if let Some(brace_end) = find_matching_brace(tokens, brace_start) {
                            let body_tokens = &tokens[brace_start + 1..brace_end];
                            functions.push(ParsedCFunction {
                                name: func_name,
                                is_internal,
                                body: parse_body(body_tokens),
                            });
                            i = brace_end + 1;
                            continue;
                        }
                    }
                }
            }
        }

        i += 1;
    }

    ParsedCSource {
        lookback_body,
        functions,
    }
}

/// Find the next `{` token starting from position `start`.
fn find_open_brace(tokens: &[Token], start: usize) -> Option<usize> {
    let mut i = start;
    while i < tokens.len() {
        if tokens[i] == Token::LBrace {
            return Some(i);
        }
        i += 1;
    }
    None
}

/// Given the position of an opening `{`, find the matching `}`.
fn find_matching_brace(tokens: &[Token], open: usize) -> Option<usize> {
    let mut depth = 1;
    let mut i = open + 1;
    while i < tokens.len() {
        match &tokens[i] {
            Token::LBrace => depth += 1,
            Token::RBrace => {
                depth -= 1;
                if depth == 0 {
                    return Some(i);
                }
            }
            _ => {}
        }
        i += 1;
    }
    None
}

/// Parse a slice of tokens (a function body) into statements.
fn parse_body(tokens: &[Token]) -> Vec<Statement> {
    let mut parser = Parser::new(tokens.to_vec());
    parser.parse_statements()
}

// --- Parser ---

struct Parser {
    tokens: Vec<Token>,
    pos: usize,
}

impl Parser {
    fn new(tokens: Vec<Token>) -> Self {
        Self { tokens, pos: 0 }
    }

    fn peek(&self) -> Option<&Token> {
        self.tokens.get(self.pos)
    }

    fn advance(&mut self) -> Token {
        let tok = self.tokens[self.pos].clone();
        self.pos += 1;
        tok
    }

    fn expect_op(&mut self, op: &str) {
        match self.advance() {
            Token::Op(ref s) if s == op => {}
            other => panic!("Expected '{op}', got {other:?}"),
        }
    }

    fn expect(&mut self, expected: &Token) {
        let tok = self.advance();
        assert_eq!(&tok, expected, "Expected {expected:?}, got {tok:?}");
    }

    fn parse_statements(&mut self) -> Vec<Statement> {
        let mut stmts = Vec::new();
        while self.pos < self.tokens.len() {
            if self.peek() == Some(&Token::RBrace) {
                break;
            }
            // Skip stray semicolons
            if self.peek() == Some(&Token::Semicolon) {
                self.advance();
                continue;
            }
            stmts.push(self.parse_statement());
        }
        stmts
    }

    fn parse_statement(&mut self) -> Statement {
        match self.peek().cloned() {
            Some(Token::Ident(ref s)) if s == "do" => self.parse_do_while(),
            Some(Token::Ident(ref s)) if s == "while" => self.parse_while(),
            Some(Token::Ident(ref s)) if s == "for" => self.parse_for(),
            Some(Token::Ident(ref s)) if s == "if" => self.parse_if(),
            Some(Token::Ident(ref s)) if s == "switch" => self.parse_switch(),
            Some(Token::Ident(ref s)) if s == "return" => self.parse_return(),
            Some(Token::Ident(ref s)) if s == "break" => {
                self.advance();
                self.consume_semicolon();
                Statement::Break
            }
            Some(Token::Ident(ref s)) if s == "continue" => {
                self.advance();
                self.consume_semicolon();
                Statement::Continue
            }
            Some(Token::Ident(ref s)) if Self::is_type_keyword(s) => self.parse_var_decl(),
            // `const double name = val;` or `const int name = val;`
            Some(Token::Ident(ref s)) if s == "const" => {
                self.advance(); // consume `const`
                self.parse_var_decl()
            }
            Some(Token::Ident(ref s)) if Self::is_macro_decl(s) => self.parse_macro_decl(),
            Some(Token::Star) => self.parse_pointer_deref_assign(),
            _ => self.parse_assignment_or_expr_stmt(),
        }
    }

    fn consume_semicolon(&mut self) {
        if self.peek() == Some(&Token::Semicolon) {
            self.advance();
        }
    }

    fn is_type_keyword(s: &str) -> bool {
        matches!(s, "int" | "double" | "size_t" | "TA_RetCode")
    }

    /// Check if an identifier is a known macro that acts as a declaration or standalone statement.
    fn is_macro_decl(s: &str) -> bool {
        matches!(
            s,
            "ENUM_DECLARATION"
                | "ARRAY_REF"
                | "ARRAY_ALLOC"
                | "ARRAY_FREE"
                | "CONSTANT_DOUBLE"
                | "CONSTANT_INTEGER"
                | "CIRCBUF_PROLOG"
                | "CIRCBUF_PROLOG_CLASS"
                | "CIRCBUF_CONSTRUCT"
                | "CIRCBUF_INIT_CLASS"
                | "CIRCBUF_DESTROY"
                | "CIRCBUF_NEXT"
                | "HILBERT_VARIABLES"
                | "INIT_HILBERT_VARIABLES"
                | "DO_HILBERT_ODD"
                | "DO_HILBERT_EVEN"
                | "DO_PRICE_WMA"
        )
    }

    /// Parse macro declarations/statements like:
    ///   `ENUM_DECLARATION(RetCode)` retCode;  -> `VarDecl` { type: `RetCodeType`, name: retCode }
    ///   `ARRAY_REF(buf)`;                      -> `VarDecl` { type: Real, name: buf }
    ///   `ARRAY_ALLOC(buf`, expr);              -> skip (no-op for code generation)
    ///   `ARRAY_FREE(buf)`;                     -> skip (no-op for code generation)
    #[allow(clippy::too_many_lines)]
    fn parse_macro_decl(&mut self) -> Statement {
        let macro_name = match self.advance() {
            Token::Ident(s) => s,
            other => panic!("Expected macro name, got {other:?}"),
        };
        self.expect(&Token::LParen);

        match macro_name.as_str() {
            "ENUM_DECLARATION" => {
                // ENUM_DECLARATION(RetCode) varName;
                let type_name = match self.advance() {
                    Token::Ident(s) => s,
                    other => panic!("Expected type name in ENUM_DECLARATION, got {other:?}"),
                };
                self.expect(&Token::RParen);
                let var_name = match self.advance() {
                    Token::Ident(s) => s,
                    other => panic!(
                        "Expected variable name after ENUM_DECLARATION({type_name}), got {other:?}"
                    ),
                };
                self.consume_semicolon();
                let var_type = if type_name == "RetCode" {
                    VarType::RetCodeType
                } else {
                    VarType::Integer
                };
                Statement::VarDecl {
                    var_type,
                    name: var_name,
                    init: None,
                }
            }
            "ARRAY_REF" => {
                // ARRAY_REF(buf);
                let var_name = match self.advance() {
                    Token::Ident(s) => s,
                    other => panic!("Expected variable name in ARRAY_REF, got {other:?}"),
                };
                self.expect(&Token::RParen);
                self.consume_semicolon();
                Statement::VarDecl {
                    var_type: VarType::Real,
                    name: var_name,
                    init: None,
                }
            }
            "ARRAY_ALLOC"
            | "ARRAY_FREE"
            | "CIRCBUF_PROLOG"
            | "CIRCBUF_PROLOG_CLASS"
            | "CIRCBUF_CONSTRUCT"
            | "CIRCBUF_INIT_CLASS"
            | "CIRCBUF_DESTROY"
            | "CIRCBUF_NEXT" => {
                // Skip all tokens until matching RParen, then semicolon
                let mut depth = 1;
                while depth > 0 {
                    match self.advance() {
                        Token::LParen => depth += 1,
                        Token::RParen => depth -= 1,
                        _ => {}
                    }
                }
                self.consume_semicolon();
                Statement::Assign {
                    target: Expr::Var("_".to_string()),
                    value: Expr::FuncCall(macro_name, vec![]),
                    compound: false,
                }
            }
            "CONSTANT_DOUBLE" => {
                // CONSTANT_DOUBLE(name) = value;
                let var_name = match self.advance() {
                    Token::Ident(s) => s,
                    other => panic!("Expected variable name in CONSTANT_DOUBLE, got {other:?}"),
                };
                self.expect(&Token::RParen);
                self.expect_op("=");
                let init = self.parse_expr();
                self.consume_semicolon();
                Statement::VarDecl {
                    var_type: VarType::Real,
                    name: var_name,
                    init: Some(init),
                }
            }
            "CONSTANT_INTEGER" => {
                // CONSTANT_INTEGER(name) = value;
                let var_name = match self.advance() {
                    Token::Ident(s) => s,
                    other => panic!("Expected variable name in CONSTANT_INTEGER, got {other:?}"),
                };
                self.expect(&Token::RParen);
                self.expect_op("=");
                let init = self.parse_expr();
                self.consume_semicolon();
                Statement::VarDecl {
                    var_type: VarType::Integer,
                    name: var_name,
                    init: Some(init),
                }
            }
            "INIT_HILBERT_VARIABLES" | "DO_HILBERT_ODD" | "DO_HILBERT_EVEN" | "DO_PRICE_WMA" => {
                // Function-like macro call as statement
                let args = self.parse_call_args();
                self.expect(&Token::RParen);
                self.consume_semicolon();
                Statement::Assign {
                    target: Expr::Var("_".to_string()),
                    value: Expr::FuncCall(macro_name, args),
                    compound: false,
                }
            }
            "HILBERT_VARIABLES" => {
                // HILBERT_VARIABLES(prefix); -> declares multiple variables
                let prefix = match self.advance() {
                    Token::Ident(s) => s,
                    other => panic!("Expected identifier in HILBERT_VARIABLES, got {other:?}"),
                };
                self.expect(&Token::RParen);
                self.consume_semicolon();
                // Expand to variable declarations for the Hilbert Transform variables
                Statement::Block {
                    body: vec![
                        Statement::VarDecl {
                            var_type: VarType::Real,
                            name: format!("{prefix}_Odd0"),
                            init: None,
                        },
                        Statement::VarDecl {
                            var_type: VarType::Real,
                            name: format!("{prefix}_Odd1"),
                            init: None,
                        },
                        Statement::VarDecl {
                            var_type: VarType::Real,
                            name: format!("{prefix}_Odd2"),
                            init: None,
                        },
                        Statement::VarDecl {
                            var_type: VarType::Real,
                            name: format!("{prefix}_Even0"),
                            init: None,
                        },
                        Statement::VarDecl {
                            var_type: VarType::Real,
                            name: format!("{prefix}_Even1"),
                            init: None,
                        },
                        Statement::VarDecl {
                            var_type: VarType::Real,
                            name: format!("{prefix}_Even2"),
                            init: None,
                        },
                    ],
                }
            }
            _ => panic!("Unhandled macro: {macro_name}"),
        }
    }

    fn type_from_keyword(s: &str) -> VarType {
        match s {
            "int" => VarType::Integer,
            "double" => VarType::Real,
            "size_t" => VarType::Index,
            "TA_RetCode" => VarType::RetCodeType,
            other => panic!("Unknown type keyword: {other}"),
        }
    }

    fn parse_var_decl(&mut self) -> Statement {
        let type_tok = self.advance();
        let var_type = match type_tok {
            Token::Ident(ref s) => Self::type_from_keyword(s),
            _ => panic!("Expected type keyword"),
        };

        // Consume optional pointer declarator: `double *buf` or `int *ptr`
        if self.peek() == Some(&Token::Star) {
            self.advance();
        }

        let first = self.parse_single_var_decl(var_type.clone());

        // Check for multi-variable declarations: int x, y, z;
        if self.peek() == Some(&Token::Comma) {
            let mut stmts = vec![first];
            while self.peek() == Some(&Token::Comma) {
                self.advance(); // consume ,
                stmts.push(self.parse_single_var_decl(var_type.clone()));
            }
            self.consume_semicolon();
            // Return as a Block containing multiple VarDecl statements
            Statement::Block { body: stmts }
        } else {
            self.consume_semicolon();
            first
        }
    }

    fn parse_single_var_decl(&mut self, var_type: VarType) -> Statement {
        let name = match self.advance() {
            Token::Ident(s) => s,
            other => panic!("Expected identifier in var decl, got {other:?}"),
        };

        // Consume optional array size: `double buf[SIZE]` — discard size expression
        if self.peek() == Some(&Token::LBracket) {
            self.advance(); // consume [
            // Skip tokens until matching ]
            let mut depth = 1;
            while depth > 0 {
                match self.advance() {
                    Token::LBracket => depth += 1,
                    Token::RBracket => depth -= 1,
                    _ => {}
                }
            }
        }

        // Check for init
        if let Some(Token::Op(ref op)) = self.peek() {
            if op == "=" {
                self.advance(); // consume =
                let init = self.parse_expr();
                return Statement::VarDecl {
                    var_type,
                    name,
                    init: Some(init),
                };
            }
        }

        Statement::VarDecl {
            var_type,
            name,
            init: None,
        }
    }

    /// Parse the right-hand side of an assignment, handling chained assignments.
    /// Returns (`preceding_assignments`, `final_value`) where `preceding_assignments`
    /// are the desugared inner assignments. Does NOT consume the trailing semicolon.
    /// Example: for `b = c = 0.0`, returns ([c = 0.0, b = c], Var(c))
    ///          for `expr`, returns ([], expr)
    fn parse_chained_rhs(&mut self) -> (Vec<Statement>, Expr) {
        // Look ahead: if next is Ident followed by Op("="), it's a chain.
        if let Some(Token::Ident(_)) = self.peek() {
            let save = self.pos;
            let chain_name = if let Token::Ident(s) = &self.tokens[self.pos] {
                s.clone()
            } else {
                unreachable!()
            };
            self.advance();
            if matches!(self.peek(), Some(Token::Op(ref o)) if o == "=") {
                self.advance(); // consume =
                let chain_name = strip_ta_prefix(&chain_name);
                // Recursively parse the rest of the chain
                let (mut inner_stmts, inner_val) = self.parse_chained_rhs();
                inner_stmts.push(Statement::Assign {
                    target: Expr::Var(chain_name.clone()),
                    value: inner_val,
                    compound: false,
                });
                return (inner_stmts, Expr::Var(chain_name));
            }
            // Not a chain — backtrack
            self.pos = save;
        }
        // Plain expression
        let expr = self.parse_expr();
        (vec![], expr)
    }

    fn parse_pointer_deref_assign(&mut self) -> Statement {
        self.advance(); // consume *
        let name = match self.advance() {
            Token::Ident(s) => s,
            other => panic!("Expected identifier after *, got {other:?}"),
        };
        self.expect_op("=");
        // Check for chained assignment: *ptr = name2 = expr
        let (chained_stmts, value) = self.parse_chained_rhs();
        self.consume_semicolon();
        let mut stmts = chained_stmts;
        stmts.push(Statement::Assign {
            target: Expr::PointerDeref(name),
            value,
            compound: false,
        });
        if stmts.len() == 1 {
            stmts.remove(0)
        } else {
            Statement::Block { body: stmts }
        }
    }

    fn parse_do_while(&mut self) -> Statement {
        self.advance(); // consume "do"
        self.expect(&Token::LBrace);
        let body = self.parse_statements();
        self.expect(&Token::RBrace);
        // expect "while"
        match self.advance() {
            Token::Ident(s) if s == "while" => {}
            other => panic!("Expected 'while' after do block, got {other:?}"),
        }
        self.expect(&Token::LParen);
        let condition = self.parse_expr();
        self.expect(&Token::RParen);
        self.consume_semicolon();
        Statement::DoWhile { condition, body }
    }

    fn parse_while(&mut self) -> Statement {
        self.advance(); // consume "while"
        self.expect(&Token::LParen);
        let condition = self.parse_expr();
        self.expect(&Token::RParen);
        let body = if self.peek() == Some(&Token::LBrace) {
            self.advance(); // consume {
            let body = self.parse_statements();
            self.expect(&Token::RBrace);
            body
        } else {
            // Braceless while: single statement
            let stmt = self.parse_statement();
            vec![stmt]
        };
        Statement::While { condition, body }
    }

    fn parse_for(&mut self) -> Statement {
        self.advance(); // consume "for"
        self.expect(&Token::LParen);

        // Parse init statement(s) — may have comma-separated assignments
        // e.g. todayIdx=startIdx, outIdx=0
        let mut init_stmts = vec![self.parse_for_init()];
        while self.peek() == Some(&Token::Comma) {
            self.advance(); // consume comma
            init_stmts.push(self.parse_for_init());
        }
        self.expect(&Token::Semicolon);

        // Use compound init if multiple, or single if just one
        let init = if init_stmts.len() == 1 {
            init_stmts.remove(0)
        } else {
            Statement::Block { body: init_stmts }
        };

        // Parse condition
        let condition = self.parse_expr();
        self.expect(&Token::Semicolon);

        // Parse update statement(s) — may have comma-separated updates
        // or may be empty (e.g., for(;;))
        let update = if self.peek() == Some(&Token::RParen) {
            // Empty update
            Statement::Block { body: vec![] }
        } else {
            let mut update_stmts = vec![self.parse_for_update()];
            while self.peek() == Some(&Token::Comma) {
                self.advance(); // consume comma
                update_stmts.push(self.parse_for_update());
            }
            if update_stmts.len() == 1 {
                update_stmts.remove(0)
            } else {
                Statement::Block { body: update_stmts }
            }
        };
        self.expect(&Token::RParen);

        // Parse body — may or may not have braces
        let body = if self.peek() == Some(&Token::LBrace) {
            self.advance(); // consume {
            let stmts = self.parse_statements();
            self.expect(&Token::RBrace);
            stmts
        } else {
            // Braceless for: single statement body
            vec![self.parse_statement()]
        };

        Statement::ForC {
            init: Box::new(init),
            condition,
            update: Box::new(update),
            body,
        }
    }

    fn parse_for_init(&mut self) -> Statement {
        // Could be a type keyword (var decl) or an ident (assignment)
        if let Some(Token::Ident(ref s)) = self.peek() {
            if Self::is_type_keyword(s) {
                let type_tok = self.advance();
                let var_type = match type_tok {
                    Token::Ident(ref s) => Self::type_from_keyword(s),
                    _ => unreachable!(),
                };
                return self.parse_single_var_decl(var_type);
            }
        }
        self.parse_assignment_no_semicolon()
    }

    fn parse_for_update(&mut self) -> Statement {
        // Handle pre-increment: ++i
        if self.peek() == Some(&Token::PlusPlus) {
            self.advance();
            let name = match self.advance() {
                Token::Ident(s) => s,
                other => panic!("Expected identifier after ++ in for update, got {other:?}"),
            };
            return Statement::Assign {
                target: Expr::Var(name.clone()),
                value: Expr::BinOp(
                    Box::new(Expr::Var(name)),
                    BinOp::Add,
                    Box::new(Expr::IntLiteral(1)),
                ),
                compound: true,
            };
        }
        // Handle pre-decrement: --i
        if self.peek() == Some(&Token::MinusMinus) {
            self.advance();
            let name = match self.advance() {
                Token::Ident(s) => s,
                other => panic!("Expected identifier after -- in for update, got {other:?}"),
            };
            return Statement::Assign {
                target: Expr::Var(name.clone()),
                value: Expr::BinOp(
                    Box::new(Expr::Var(name)),
                    BinOp::Sub,
                    Box::new(Expr::IntLiteral(1)),
                ),
                compound: true,
            };
        }
        // Usually i++ or i-- or i += 1
        let name = match self.advance() {
            Token::Ident(s) => s,
            other => panic!("Expected identifier in for update, got {other:?}"),
        };

        match self.peek() {
            Some(Token::PlusPlus) => {
                self.advance();
                Statement::Assign {
                    target: Expr::Var(name.clone()),
                    value: Expr::BinOp(
                        Box::new(Expr::Var(name)),
                        BinOp::Add,
                        Box::new(Expr::IntLiteral(1)),
                    ),
                    compound: true,
                }
            }
            Some(Token::MinusMinus) => {
                self.advance();
                Statement::Assign {
                    target: Expr::Var(name.clone()),
                    value: Expr::BinOp(
                        Box::new(Expr::Var(name)),
                        BinOp::Sub,
                        Box::new(Expr::IntLiteral(1)),
                    ),
                    compound: true,
                }
            }
            Some(Token::Op(ref op)) if op == "+=" || op == "-=" || op == "*=" || op == "/=" => {
                let op_str = op.clone();
                self.advance();
                let bin_op = compound_op(&op_str);
                let rhs = self.parse_expr();
                Statement::Assign {
                    target: Expr::Var(name.clone()),
                    value: Expr::BinOp(Box::new(Expr::Var(name)), bin_op, Box::new(rhs)),
                    compound: true,
                }
            }
            _ => {
                // Simple assignment: name = expr
                self.expect_op("=");
                let value = self.parse_expr();
                Statement::Assign {
                    target: Expr::Var(name),
                    value,
                    compound: false,
                }
            }
        }
    }

    fn parse_if(&mut self) -> Statement {
        self.advance(); // consume "if"
        self.expect(&Token::LParen);
        let condition = self.parse_expr();
        self.expect(&Token::RParen);

        let then_body = if self.peek() == Some(&Token::LBrace) {
            self.advance(); // consume {
            let body = self.parse_statements();
            self.expect(&Token::RBrace);
            body
        } else {
            // Braceless if: single statement
            let stmt = self.parse_statement();
            vec![stmt]
        };

        let else_body = if let Some(Token::Ident(ref s)) = self.peek() {
            if s == "else" {
                self.advance(); // consume "else"
                if let Some(Token::Ident(ref s2)) = self.peek() {
                    if s2 == "if" {
                        // else if — recurse
                        vec![self.parse_if()]
                    } else {
                        // else { ... } or braceless else
                        if self.peek() == Some(&Token::LBrace) {
                            self.advance();
                            let body = self.parse_statements();
                            self.expect(&Token::RBrace);
                            body
                        } else {
                            vec![self.parse_statement()]
                        }
                    }
                } else if self.peek() == Some(&Token::LBrace) {
                    self.advance();
                    let body = self.parse_statements();
                    self.expect(&Token::RBrace);
                    body
                } else {
                    vec![self.parse_statement()]
                }
            } else {
                vec![]
            }
        } else {
            vec![]
        };

        Statement::If {
            condition,
            then_body,
            else_body,
        }
    }

    fn parse_switch(&mut self) -> Statement {
        self.advance(); // consume "switch"
        self.expect(&Token::LParen);
        let expr = self.parse_expr();
        self.expect(&Token::RParen);
        self.expect(&Token::LBrace);

        let mut cases: Vec<(String, Vec<Statement>)> = Vec::new();
        let mut default_body: Vec<Statement> = Vec::new();

        while self.peek() != Some(&Token::RBrace) {
            match self.peek().cloned() {
                Some(Token::Ident(ref s)) if s == "case" => {
                    self.advance();
                    let label = match self.advance() {
                        Token::Ident(s) => {
                            // Handle ENUM_CASE(Type, CName, PascalName) macro:
                            // Produce label in "Type_Short" format, e.g. "MAType_SMA"
                            // so lookup_variant can find it in the enum registry.
                            if s == "ENUM_CASE" {
                                self.expect(&Token::LParen);
                                let enum_type = match self.advance() {
                                    Token::Ident(n) => n,
                                    other => {
                                        panic!("Expected ENUM_CASE type name, got {other:?}")
                                    }
                                };
                                self.expect(&Token::Comma);
                                let c_name = match self.advance() {
                                    Token::Ident(n) => n,
                                    other => panic!("Expected ENUM_CASE C name, got {other:?}"),
                                };
                                self.expect(&Token::Comma);
                                let _pascal_name = self.advance(); // e.g. Sma
                                self.expect(&Token::RParen);
                                // Strip "TA_<Type>_" prefix from c_name to get short name
                                let prefix = format!("TA_{enum_type}_");
                                let short = c_name.strip_prefix(&prefix).unwrap_or(&c_name);
                                format!("{enum_type}_{short}")
                            } else {
                                s
                            }
                        }
                        Token::IntNumber(n) => format!("{n}"),
                        other => panic!("Expected case label, got {other:?}"),
                    };
                    self.expect(&Token::Colon);

                    let mut body = Vec::new();
                    loop {
                        match self.peek() {
                            Some(Token::RBrace) => break,
                            Some(Token::Ident(ref s)) if s == "case" || s == "default" => {
                                break;
                            }
                            Some(Token::Ident(ref s)) if s == "break" => {
                                self.advance();
                                self.consume_semicolon();
                                break;
                            }
                            _ => body.push(self.parse_statement()),
                        }
                    }
                    cases.push((label, body));
                }
                Some(Token::Ident(ref s)) if s == "default" => {
                    self.advance();
                    self.expect(&Token::Colon);
                    loop {
                        match self.peek() {
                            Some(Token::RBrace) => break,
                            Some(Token::Ident(ref s)) if s == "break" => {
                                self.advance();
                                self.consume_semicolon();
                                break;
                            }
                            _ => default_body.push(self.parse_statement()),
                        }
                    }
                }
                other => panic!("Expected 'case' or 'default' in switch, got {other:?}"),
            }
        }
        self.expect(&Token::RBrace);

        Statement::Switch {
            expr,
            cases,
            default: default_body,
        }
    }

    fn parse_return(&mut self) -> Statement {
        self.advance(); // consume "return"

        // Check for bare return (just semicolon)
        if self.peek() == Some(&Token::Semicolon) {
            self.consume_semicolon();
            return Statement::Return { value: None };
        }

        // Parse the return expression, but first handle TA_ prefix stripping
        // for identifiers that look like enum values (e.g., TA_SUCCESS -> SUCCESS)
        let expr = self.parse_return_expr();
        self.consume_semicolon();

        Statement::Return { value: Some(expr) }
    }

    /// Parse a return value expression, stripping TA_ prefixes from identifiers.
    fn parse_return_expr(&mut self) -> Expr {
        // Use the normal expression parser, but we need to handle TA_ prefix stripping.
        // We'll do this by peeking at the tokens and transforming TA_ prefixed idents.
        // The simplest approach: temporarily replace TA_ prefixed idents in-place.
        let start = self.pos;

        // Scan forward to find the semicolon, stripping TA_ prefixes
        let mut end = self.pos;
        while end < self.tokens.len() && self.tokens[end] != Token::Semicolon {
            end += 1;
        }
        // Strip TA_ prefixes in the range [start..end]
        for i in start..end {
            if let Token::Ident(ref s) = self.tokens[i].clone() {
                let stripped = strip_ta_prefix(s);
                if stripped != *s {
                    self.tokens[i] = Token::Ident(stripped);
                }
            }
        }

        self.parse_expr()
    }

    /// Check if an identifier looks like an `ALL_CAPS` macro name.
    fn is_all_caps_macro(name: &str) -> bool {
        name.len() > 1
            && name
                .chars()
                .all(|c| c.is_ascii_uppercase() || c == '_' || c.is_ascii_digit())
            && name.chars().next().is_some_and(|c| c.is_ascii_uppercase())
    }

    #[allow(clippy::too_many_lines)]
    fn parse_assignment_or_expr_stmt(&mut self) -> Statement {
        let name = match self.advance() {
            Token::Ident(s) => s,
            other => panic!("Expected identifier, got {other:?}"),
        };

        // Handle ALL_CAPS macro as standalone statement without args: CALCULATE_AD;
        if Self::is_all_caps_macro(&name) && self.peek() == Some(&Token::Semicolon) {
            self.consume_semicolon();
            return Statement::Assign {
                target: Expr::Var("_".to_string()),
                value: Expr::FuncCall(name, vec![]),
                compound: false,
            };
        }

        // Handle ALL_CAPS macro calls as standalone statements
        // e.g., TRUE_RANGE(a,b,c,d); UNUSED_VARIABLE(x); SAR_ROUNDING(v);
        if Self::is_all_caps_macro(&name)
            && self.peek() == Some(&Token::LParen)
            && !Self::is_type_keyword(&name)
        // not a type keyword
        {
            let save_pos = self.pos;
            self.advance(); // consume (
            let args = self.parse_call_args();
            self.expect(&Token::RParen);
            if matches!(self.peek(), Some(&Token::Semicolon) | None)
                || self.pos >= self.tokens.len()
            {
                self.consume_semicolon();
                return Statement::Assign {
                    target: Expr::Var("_".to_string()),
                    value: Expr::FuncCall(name, args),
                    compound: false,
                };
            }
            // Not a standalone call — might be CONSTANT_DOUBLE(x) = expr or similar
            self.pos = save_pos;
        }

        // Post-increment: i++;
        if self.peek() == Some(&Token::PlusPlus) {
            self.advance();
            self.consume_semicolon();
            return Statement::Assign {
                target: Expr::Var(name.clone()),
                value: Expr::BinOp(
                    Box::new(Expr::Var(name)),
                    BinOp::Add,
                    Box::new(Expr::IntLiteral(1)),
                ),
                compound: true,
            };
        }

        // Post-decrement: i--;
        if self.peek() == Some(&Token::MinusMinus) {
            self.advance();
            self.consume_semicolon();
            return Statement::Assign {
                target: Expr::Var(name.clone()),
                value: Expr::BinOp(
                    Box::new(Expr::Var(name)),
                    BinOp::Sub,
                    Box::new(Expr::IntLiteral(1)),
                ),
                compound: true,
            };
        }

        // Function call as statement: FUNC(args...);
        if self.peek() == Some(&Token::LParen) {
            let save_pos = self.pos;
            self.advance(); // consume (
            let args = self.parse_call_args();
            self.expect(&Token::RParen);

            if matches!(self.peek(), Some(&Token::Semicolon) | None)
                || self.pos >= self.tokens.len()
            {
                self.consume_semicolon();
                let func_name = transform_func_name(&name);
                return Statement::Assign {
                    target: Expr::Var("_".to_string()),
                    value: Expr::FuncCall(func_name, args),
                    compound: false,
                };
            }

            // CIRCBUF_REF(arr[idx])field = expr; or compound assign
            if name == "CIRCBUF_REF" {
                if let Some(Token::Ident(field)) = self.peek().cloned() {
                    self.advance(); // consume field name
                                    // Build synthetic array name: arr_field
                    let target =
                        if let Some(Expr::ArrayAccess(arr_name, idx)) = args.into_iter().next() {
                            Expr::ArrayAccess(format!("{arr_name}_{field}"), idx)
                        } else {
                            Expr::Var(format!("circbuf_{field}"))
                        };
                    // Parse = or compound assignment
                    match self.peek().cloned() {
                        Some(Token::Op(ref op)) if op == "=" => {
                            self.advance();
                            let value = self.parse_expr();
                            self.consume_semicolon();
                            return Statement::Assign {
                                target,
                                value,
                                compound: false,
                            };
                        }
                        Some(Token::Op(ref op))
                            if op == "+=" || op == "-=" || op == "*=" || op == "/=" =>
                        {
                            let op_str = op.clone();
                            self.advance();
                            let bin_op = compound_op(&op_str);
                            let rhs = self.parse_expr();
                            self.consume_semicolon();
                            return Statement::Assign {
                                target: target.clone(),
                                value: Expr::BinOp(Box::new(target), bin_op, Box::new(rhs)),
                                compound: true,
                            };
                        }
                        _ => {} // fall through
                    }
                }
            }

            // Not a standalone call — backtrack
            self.pos = save_pos;
        }

        // Array access assignment: arr[i] = expr;
        if self.peek() == Some(&Token::LBracket) {
            self.advance(); // consume [
            let index_expr = self.parse_expr();
            self.expect(&Token::RBracket);

            // Check for compound assignment on array
            match self.peek().cloned() {
                Some(Token::Op(ref op)) if op == "+=" || op == "-=" || op == "*=" || op == "/=" => {
                    let op_str = op.clone();
                    self.advance();
                    let bin_op = compound_op(&op_str);
                    let rhs = self.parse_expr();
                    self.consume_semicolon();
                    return Statement::Assign {
                        target: Expr::ArrayAccess(name.clone(), Box::new(index_expr.clone())),
                        value: Expr::BinOp(
                            Box::new(Expr::ArrayAccess(name, Box::new(index_expr))),
                            bin_op,
                            Box::new(rhs),
                        ),
                        compound: true,
                    };
                }
                _ => {
                    self.expect_op("=");
                    let value = self.parse_expr();
                    self.consume_semicolon();
                    return Statement::Assign {
                        target: Expr::ArrayAccess(name, Box::new(index_expr)),
                        value,
                        compound: false,
                    };
                }
            }
        }

        // Simple or compound assignment
        match self.peek().cloned() {
            Some(Token::Op(ref op)) if op == "=" => {
                self.advance();
                let (mut chain_stmts, value) = self.parse_chained_rhs();
                self.consume_semicolon();
                chain_stmts.push(Statement::Assign {
                    target: Expr::Var(name),
                    value,
                    compound: false,
                });
                if chain_stmts.len() == 1 {
                    chain_stmts.remove(0)
                } else {
                    Statement::Block { body: chain_stmts }
                }
            }
            Some(Token::Op(ref op)) if op == "+=" || op == "-=" || op == "*=" || op == "/=" => {
                let op_str = op.clone();
                self.advance();
                let bin_op = compound_op(&op_str);
                // Handle embedded assignment: SumY += tempValue1 = inReal[i]
                let (mut chain_stmts, rhs) = self.parse_chained_rhs();
                self.consume_semicolon();
                chain_stmts.push(Statement::Assign {
                    target: Expr::Var(name.clone()),
                    value: Expr::BinOp(Box::new(Expr::Var(name)), bin_op, Box::new(rhs)),
                    compound: true,
                });
                if chain_stmts.len() == 1 {
                    chain_stmts.remove(0)
                } else {
                    Statement::Block { body: chain_stmts }
                }
            }
            other => panic!("Expected '=' or compound assignment after '{name}', got {other:?}"),
        }
    }

    fn parse_assignment_no_semicolon(&mut self) -> Statement {
        let name = match self.advance() {
            Token::Ident(s) => s,
            other => panic!("Expected identifier, got {other:?}"),
        };
        self.expect_op("=");
        let value = self.parse_expr();
        Statement::Assign {
            target: Expr::Var(name),
            value,
            compound: false,
        }
    }

    fn parse_call_args(&mut self) -> Vec<Expr> {
        let mut args = Vec::new();
        if self.peek() == Some(&Token::RParen) {
            return args;
        }
        args.push(self.parse_expr());
        while self.peek() == Some(&Token::Comma) {
            self.advance();
            args.push(self.parse_expr());
        }
        args
    }

    // --- Expression parsing (precedence climbing) ---

    fn parse_expr(&mut self) -> Expr {
        let expr = self.parse_logical_or();
        // Ternary: expr ? then_expr : else_expr
        if self.peek() == Some(&Token::Question) {
            self.advance();
            let then_expr = self.parse_expr();
            self.expect(&Token::Colon);
            let else_expr = self.parse_expr();
            return Expr::Ternary(Box::new(expr), Box::new(then_expr), Box::new(else_expr));
        }
        expr
    }

    fn parse_logical_or(&mut self) -> Expr {
        let mut left = self.parse_logical_and();
        while let Some(Token::Op(ref op)) = self.peek() {
            if op != "||" {
                break;
            }
            self.advance();
            let right = self.parse_logical_and();
            left = Expr::BinOp(Box::new(left), BinOp::Or, Box::new(right));
        }
        left
    }

    fn parse_logical_and(&mut self) -> Expr {
        let mut left = self.parse_comparison();
        while let Some(Token::Op(ref op)) = self.peek() {
            if op != "&&" {
                break;
            }
            self.advance();
            let right = self.parse_comparison();
            left = Expr::BinOp(Box::new(left), BinOp::And, Box::new(right));
        }
        left
    }

    fn parse_comparison(&mut self) -> Expr {
        let mut left = self.parse_shift();
        while let Some(Token::Op(ref op)) = self.peek() {
            let bin_op = match op.as_str() {
                "<=" => BinOp::LessEq,
                ">=" => BinOp::GreaterEq,
                "<" => BinOp::Less,
                ">" => BinOp::Greater,
                "==" => BinOp::Eq,
                "!=" => BinOp::NotEq,
                _ => break,
            };
            self.advance();
            let right = self.parse_shift();
            left = Expr::BinOp(Box::new(left), bin_op, Box::new(right));
        }
        left
    }

    fn parse_shift(&mut self) -> Expr {
        let mut left = self.parse_additive();
        while let Some(Token::Op(ref op)) = self.peek() {
            let bin_op = match op.as_str() {
                ">>" => BinOp::Shr,
                "<<" => BinOp::Shl,
                _ => break,
            };
            self.advance();
            let right = self.parse_additive();
            left = Expr::BinOp(Box::new(left), bin_op, Box::new(right));
        }
        left
    }

    fn parse_additive(&mut self) -> Expr {
        let mut left = self.parse_multiplicative();
        while let Some(Token::Op(ref op)) = self.peek() {
            let bin_op = match op.as_str() {
                "+" => BinOp::Add,
                "-" => BinOp::Sub,
                _ => break,
            };
            self.advance();
            let right = self.parse_multiplicative();
            left = Expr::BinOp(Box::new(left), bin_op, Box::new(right));
        }
        left
    }

    fn parse_multiplicative(&mut self) -> Expr {
        let mut left = self.parse_unary();
        loop {
            match self.peek() {
                Some(Token::Star) => {
                    self.advance();
                    let right = self.parse_unary();
                    left = Expr::BinOp(Box::new(left), BinOp::Mul, Box::new(right));
                }
                Some(Token::Op(ref op)) if op == "/" || op == "%" => {
                    let bin_op = match op.as_str() {
                        "/" => BinOp::Div,
                        "%" => BinOp::Mod,
                        _ => unreachable!(),
                    };
                    self.advance();
                    let right = self.parse_unary();
                    left = Expr::BinOp(Box::new(left), bin_op, Box::new(right));
                }
                _ => break,
            }
        }
        left
    }

    fn parse_unary(&mut self) -> Expr {
        if self.peek() == Some(&Token::Bang) {
            self.advance();
            let operand = self.parse_unary();
            return Expr::Not(Box::new(operand));
        }
        // Address-of: &var or &var[idx]
        if self.peek() == Some(&Token::Ampersand) {
            self.advance();
            let operand = self.parse_primary();
            return Expr::AddressOf(Box::new(operand));
        }
        // Unary dereference: *var
        if self.peek() == Some(&Token::Star) {
            self.advance();
            if let Some(Token::Ident(ref name)) = self.peek() {
                let name = name.clone();
                self.advance();
                return Expr::PointerDeref(name);
            }
            // Dereference of a parenthesized expr — fall through to parse_primary
            let operand = self.parse_primary();
            if let Expr::Var(name) = operand {
                return Expr::PointerDeref(name);
            }
            panic!("Cannot dereference non-identifier expression");
        }
        // Pre-increment: ++expr
        if self.peek() == Some(&Token::PlusPlus) {
            self.advance();
            let operand = self.parse_unary();
            // Pre-increment evaluates to the incremented value
            // For simplicity, treat as (expr + 1) — backends handle appropriately
            return Expr::BinOp(Box::new(operand), BinOp::Add, Box::new(Expr::IntLiteral(1)));
        }
        // Pre-decrement: --expr
        if self.peek() == Some(&Token::MinusMinus) {
            self.advance();
            let operand = self.parse_unary();
            return Expr::BinOp(Box::new(operand), BinOp::Sub, Box::new(Expr::IntLiteral(1)));
        }
        // Unary minus or unary plus
        if let Some(Token::Op(ref op)) = self.peek() {
            if op == "-" {
                self.advance();
                let operand = self.parse_unary();
                return Expr::BinOp(Box::new(Expr::IntLiteral(0)), BinOp::Sub, Box::new(operand));
            }
            if op == "+" {
                self.advance();
                // Unary plus is a no-op
                return self.parse_unary();
            }
        }
        self.parse_primary()
    }

    fn parse_primary(&mut self) -> Expr {
        if let Some(Token::LParen) = self.peek().cloned() {
            self.advance(); // consume (
                            // Check for C-style cast: (double), (int), (size_t)
            if let Some(Token::Ident(ref s)) = self.peek() {
                if Self::is_type_keyword(s) {
                    let type_name = s.clone();
                    self.advance();
                    self.expect(&Token::RParen);
                    let var_type = Self::type_from_keyword(&type_name);
                    let operand = self.parse_unary();
                    return Expr::Cast(var_type, Box::new(operand));
                }
            }
            // Parenthesized expression
            let expr = self.parse_expr();
            self.expect(&Token::RParen);
            expr
        } else {
            let tok = self.advance();
            match tok {
                Token::IntNumber(n) => Expr::IntLiteral(n),
                Token::Number(n) => Expr::Literal(n),
                Token::Ident(name) => {
                    // Function call
                    if self.peek() == Some(&Token::LParen) {
                        self.advance(); // consume (
                        let args = self.parse_call_args();
                        self.expect(&Token::RParen);

                        // CIRCBUF_REF(arr[idx])field -> ArrayAccess("arr_field", idx)
                        if name == "CIRCBUF_REF" {
                            if let Some(Token::Ident(field)) = self.peek().cloned() {
                                self.advance();
                                // Extract array name and index from the first arg
                                if let Some(Expr::ArrayAccess(arr_name, idx)) =
                                    args.into_iter().next()
                                {
                                    return Expr::ArrayAccess(format!("{arr_name}_{field}"), idx);
                                }
                            }
                            // Fallback: treat as opaque function call
                            return Expr::FuncCall("CIRCBUF_REF".to_string(), vec![]);
                        }

                        let func_name = transform_func_name(&name);
                        return Expr::FuncCall(func_name, args);
                    }
                    // Array access
                    if self.peek() == Some(&Token::LBracket) {
                        self.advance(); // consume [
                        let index = self.parse_expr();
                        self.expect(&Token::RBracket);
                        let arr_expr = Expr::ArrayAccess(name, Box::new(index));
                        // Check for postfix ++/-- on array access
                        if self.peek() == Some(&Token::PlusPlus) {
                            self.advance();
                            return Expr::PostIncrement(Box::new(arr_expr));
                        }
                        if self.peek() == Some(&Token::MinusMinus) {
                            self.advance();
                            return Expr::PostDecrement(Box::new(arr_expr));
                        }
                        return arr_expr;
                    }
                    // Postfix ++/-- on plain identifier
                    if self.peek() == Some(&Token::PlusPlus) {
                        self.advance();
                        return Expr::PostIncrement(Box::new(Expr::Var(strip_ta_prefix(&name))));
                    }
                    if self.peek() == Some(&Token::MinusMinus) {
                        self.advance();
                        return Expr::PostDecrement(Box::new(Expr::Var(strip_ta_prefix(&name))));
                    }
                    // Plain identifier — strip TA_ from enum-like values
                    Expr::Var(strip_ta_prefix(&name))
                }
                other => panic!("Unexpected token in expression: {other:?}"),
            }
        }
    }
}

// --- Helper functions ---

/// Strip `TA_` prefix from enum-like identifiers (all caps after TA_).
/// Also strips `TA_COMPATIBILITY_` prefix to just the enum variant name.
fn strip_ta_prefix(name: &str) -> String {
    // Handle TA_COMPATIBILITY_XXX -> strip to just the variant (METASTOCK, DEFAULT)
    if let Some(rest) = name.strip_prefix("TA_COMPATIBILITY_") {
        if rest
            .chars()
            .all(|c| c.is_ascii_uppercase() || c == '_' || c.is_ascii_digit())
        {
            return rest.to_string();
        }
    }
    if let Some(rest) = name.strip_prefix("TA_") {
        // Only strip if the rest looks like an enum value (uppercase/underscores)
        if rest
            .chars()
            .all(|c| c.is_ascii_uppercase() || c == '_' || c.is_ascii_digit())
        {
            return rest.to_string();
        }
    }
    name.to_string()
}

/// Transform function names: strip TA_ prefix and handle special mappings.
fn transform_func_name(name: &str) -> String {
    if name == "TA_GetUnstablePeriod" {
        return "UNSTABLE_PERIOD".to_string();
    }
    if name == "TA_GetCompatibility" {
        return "COMPATIBILITY".to_string();
    }
    if let Some(rest) = name.strip_prefix("TA_") {
        return rest.to_string();
    }
    name.to_string()
}

/// Map compound assignment operator string to `BinOp`.
fn compound_op(op: &str) -> BinOp {
    match op {
        "+=" => BinOp::Add,
        "-=" => BinOp::Sub,
        "*=" => BinOp::Mul,
        "/=" => BinOp::Div,
        _ => panic!("Unknown compound operator: {op}"),
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_tokenize_simple() {
        let tokens = tokenize("int x = 0;");
        assert_eq!(
            tokens,
            vec![
                Token::Ident("int".to_string()),
                Token::Ident("x".to_string()),
                Token::Op("=".to_string()),
                Token::IntNumber(0),
                Token::Semicolon,
            ]
        );
    }

    #[test]
    fn test_tokenize_pointer_deref() {
        let tokens = tokenize("*outBegIdx = startIdx;");
        assert_eq!(
            tokens,
            vec![
                Token::Star,
                Token::Ident("outBegIdx".to_string()),
                Token::Op("=".to_string()),
                Token::Ident("startIdx".to_string()),
                Token::Semicolon,
            ]
        );
    }

    #[test]
    fn test_tokenize_increment_decrement() {
        let tokens = tokenize("i++; j--;");
        assert_eq!(
            tokens,
            vec![
                Token::Ident("i".to_string()),
                Token::PlusPlus,
                Token::Semicolon,
                Token::Ident("j".to_string()),
                Token::MinusMinus,
                Token::Semicolon,
            ]
        );
    }

    #[test]
    fn test_tokenize_compound_ops() {
        let tokens = tokenize("x += 1; y -= 2; z *= 3; w /= 4;");
        assert!(tokens.contains(&Token::Op("+=".to_string())));
        assert!(tokens.contains(&Token::Op("-=".to_string())));
        assert!(tokens.contains(&Token::Op("*=".to_string())));
        assert!(tokens.contains(&Token::Op("/=".to_string())));
    }

    #[test]
    fn test_tokenize_float() {
        let tokens = tokenize("0.0 1.5 42");
        assert_eq!(
            tokens,
            vec![Token::Number(0.0), Token::Number(1.5), Token::IntNumber(42),]
        );
    }

    #[test]
    fn test_tokenize_comments() {
        let tokens = tokenize("int x; // comment\n/* block */ int y;");
        assert_eq!(
            tokens,
            vec![
                Token::Ident("int".to_string()),
                Token::Ident("x".to_string()),
                Token::Semicolon,
                Token::Ident("int".to_string()),
                Token::Ident("y".to_string()),
                Token::Semicolon,
            ]
        );
    }

    #[test]
    fn test_tokenize_ta_prefix() {
        let tokens = tokenize("TA_RetCode TA_MULT TA_SUCCESS");
        assert_eq!(
            tokens,
            vec![
                Token::Ident("TA_RetCode".to_string()),
                Token::Ident("TA_MULT".to_string()),
                Token::Ident("TA_SUCCESS".to_string()),
            ]
        );
    }

    #[test]
    fn test_extract_mult_functions() {
        let source = r"
int TA_MULT_Lookback(void)
{
    return 0;
}

TA_RetCode TA_MULT(int startIdx, int endIdx,
                   const double inReal0[],
                   const double inReal1[],
                   int *outBegIdx, int *outNBElement,
                   double outReal[])
{
    size_t outIdx;
    size_t i;
    outIdx = 0;
    *outNBElement = outIdx;
    *outBegIdx = startIdx;
    return TA_SUCCESS;
}
";
        let parsed = parse_c_source_str(source);
        assert!(!parsed.lookback_body.is_empty());
        assert_eq!(parsed.functions.len(), 1);
        assert_eq!(parsed.functions[0].name, "TA_MULT");
        assert!(!parsed.functions[0].is_internal);
    }

    #[test]
    fn test_extract_internal_function() {
        let source = r"
TA_RetCode TA_INT_SMA(int startIdx, int endIdx,
                      const double inReal[],
                      int optInTimePeriod,
                      int *outBegIdx, int *outNBElement,
                      double outReal[])
{
    double periodTotal = 0.0;
    return TA_SUCCESS;
}
";
        let parsed = parse_c_source_str(source);
        assert_eq!(parsed.functions.len(), 1);
        assert_eq!(parsed.functions[0].name, "TA_INT_SMA");
        assert!(parsed.functions[0].is_internal);
    }

    #[test]
    fn test_parse_pointer_deref() {
        let source = r"
TA_RetCode TA_TEST(int startIdx, int endIdx, int *outBegIdx, int *outNBElement)
{
    *outBegIdx = startIdx;
    *outNBElement = 0;
    return TA_SUCCESS;
}
";
        let parsed = parse_c_source_str(source);
        let body = &parsed.functions[0].body;
        match &body[0] {
            Statement::Assign { target, .. } => match target {
                Expr::PointerDeref(name) => assert_eq!(name, "outBegIdx"),
                other => panic!("Expected PointerDeref, got {other:?}"),
            },
            other => panic!("Expected Assign, got {other:?}"),
        }
    }

    #[test]
    fn test_parse_cast() {
        let tokens = tokenize("(size_t)startIdx");
        let mut parser = Parser::new(tokens);
        let expr = parser.parse_expr();
        match expr {
            Expr::Cast(var_type, inner) => {
                assert_eq!(var_type, VarType::Index);
                match *inner {
                    Expr::Var(name) => assert_eq!(name, "startIdx"),
                    other => panic!("Expected Var, got {other:?}"),
                }
            }
            other => panic!("Expected Cast, got {other:?}"),
        }
    }

    #[test]
    fn test_parse_while_loop() {
        let source = r"
TA_RetCode TA_TEST(void)
{
    size_t i;
    i = 0;
    while( i <= 10 ) {
        i += 1;
    }
    return TA_SUCCESS;
}
";
        let parsed = parse_c_source_str(source);
        let body = &parsed.functions[0].body;
        // i decl, i = 0, while loop, return
        assert_eq!(body.len(), 4);
        match &body[2] {
            Statement::While { body, .. } => {
                assert_eq!(body.len(), 1);
            }
            other => panic!("Expected While, got {other:?}"),
        }
    }

    #[test]
    fn test_post_increment() {
        let tokens = tokenize("outIdx += 1;");
        let mut parser = Parser::new(tokens);
        let stmt = parser.parse_statement();
        match stmt {
            Statement::Assign {
                target, compound, ..
            } => {
                assert!(compound);
                match target {
                    Expr::Var(name) => assert_eq!(name, "outIdx"),
                    other => panic!("Expected Var, got {other:?}"),
                }
            }
            other => panic!("Expected Assign, got {other:?}"),
        }

        // Test actual i++ syntax
        let tokens2 = tokenize("i++;");
        let mut parser2 = Parser::new(tokens2);
        let stmt2 = parser2.parse_statement();
        match stmt2 {
            Statement::Assign {
                target, compound, ..
            } => {
                assert!(compound);
                match target {
                    Expr::Var(name) => assert_eq!(name, "i"),
                    other => panic!("Expected Var, got {other:?}"),
                }
            }
            other => panic!("Expected Assign, got {other:?}"),
        }
    }

    #[test]
    fn test_braceless_if() {
        let tokens = tokenize("if( x < y ) x = y;");
        let mut parser = Parser::new(tokens);
        let stmt = parser.parse_statement();
        match stmt {
            Statement::If {
                then_body,
                else_body,
                ..
            } => {
                assert_eq!(then_body.len(), 1);
                assert!(else_body.is_empty());
            }
            other => panic!("Expected If, got {other:?}"),
        }
    }

    #[test]
    fn test_braceless_if_else() {
        let tokens = tokenize("if( x < y ) x = y; else x = z;");
        let mut parser = Parser::new(tokens);
        let stmt = parser.parse_statement();
        match stmt {
            Statement::If {
                then_body,
                else_body,
                ..
            } => {
                assert_eq!(then_body.len(), 1);
                assert_eq!(else_body.len(), 1);
            }
            other => panic!("Expected If, got {other:?}"),
        }
    }

    #[test]
    fn test_multi_var_decl() {
        let tokens = tokenize("size_t i, j, k;");
        let mut parser = Parser::new(tokens);
        let stmt = parser.parse_statement();
        match stmt {
            Statement::Block { body } => {
                assert_eq!(body.len(), 3);
                for s in &body {
                    match s {
                        Statement::VarDecl { var_type, .. } => {
                            assert_eq!(*var_type, VarType::Index);
                        }
                        other => panic!("Expected VarDecl, got {other:?}"),
                    }
                }
            }
            other => panic!("Expected Block for multi-var decl, got {other:?}"),
        }
    }

    #[test]
    fn test_single_var_decl() {
        let tokens = tokenize("double x = 0.0;");
        let mut parser = Parser::new(tokens);
        let stmt = parser.parse_statement();
        match stmt {
            Statement::VarDecl {
                var_type,
                name,
                init,
            } => {
                assert_eq!(var_type, VarType::Real);
                assert_eq!(name, "x");
                assert!(init.is_some());
            }
            other => panic!("Expected VarDecl, got {other:?}"),
        }
    }

    #[test]
    fn test_array_access_assignment() {
        let tokens = tokenize("outReal[outIdx] = inReal0[i] * inReal1[i];");
        let mut parser = Parser::new(tokens);
        let stmt = parser.parse_statement();
        match stmt {
            Statement::Assign {
                target, compound, ..
            } => {
                assert!(!compound);
                match target {
                    Expr::ArrayAccess(name, _) => assert_eq!(name, "outReal"),
                    other => panic!("Expected ArrayAccess, got {other:?}"),
                }
            }
            other => panic!("Expected Assign, got {other:?}"),
        }
    }

    #[test]
    fn test_function_call_expr() {
        let tokens = tokenize("TA_SMA_Lookback(optInTimePeriod)");
        let mut parser = Parser::new(tokens);
        let expr = parser.parse_expr();
        match expr {
            Expr::FuncCall(name, args) => {
                assert_eq!(name, "SMA_Lookback");
                assert_eq!(args.len(), 1);
            }
            other => panic!("Expected FuncCall, got {other:?}"),
        }
    }

    #[test]
    fn test_special_function_names() {
        let tokens = tokenize("TA_GetUnstablePeriod(FuncUnstId_RSI)");
        let mut parser = Parser::new(tokens);
        let expr = parser.parse_expr();
        match expr {
            Expr::FuncCall(name, _) => {
                assert_eq!(name, "UNSTABLE_PERIOD");
            }
            other => panic!("Expected FuncCall, got {other:?}"),
        }

        let tokens2 = tokenize("TA_GetCompatibility()");
        let mut parser2 = Parser::new(tokens2);
        let expr2 = parser2.parse_expr();
        match expr2 {
            Expr::FuncCall(name, args) => {
                assert_eq!(name, "COMPATIBILITY");
                assert!(args.is_empty());
            }
            other => panic!("Expected FuncCall, got {other:?}"),
        }
    }

    #[test]
    fn test_strip_ta_prefix() {
        assert_eq!(strip_ta_prefix("TA_SUCCESS"), "SUCCESS");
        assert_eq!(strip_ta_prefix("TA_INTERNAL_ERROR"), "INTERNAL_ERROR");
        assert_eq!(strip_ta_prefix("startIdx"), "startIdx");
        // Mixed case should NOT be stripped
        assert_eq!(
            strip_ta_prefix("TA_GetUnstablePeriod"),
            "TA_GetUnstablePeriod"
        );
    }

    #[test]
    fn test_for_c_loop() {
        let tokens = tokenize("for( i = 0; i < 10; i++ ) { x = x + 1; }");
        let mut parser = Parser::new(tokens);
        let stmt = parser.parse_statement();
        match stmt {
            Statement::ForC {
                init,
                condition: _,
                update: _,
                body,
            } => {
                match *init {
                    Statement::Assign { ref target, .. } => match target {
                        Expr::Var(name) => assert_eq!(name, "i"),
                        other => panic!("Expected Var, got {other:?}"),
                    },
                    other => panic!("Expected Assign init, got {other:?}"),
                }
                assert_eq!(body.len(), 1);
            }
            other => panic!("Expected ForC, got {other:?}"),
        }
    }

    #[test]
    fn test_full_mult_body() {
        let source = r"
int TA_MULT_Lookback(void)
{
    return 0;
}

TA_RetCode TA_MULT(int startIdx, int endIdx,
                   const double inReal0[],
                   const double inReal1[],
                   int *outBegIdx, int *outNBElement,
                   double outReal[])
{
    size_t outIdx;
    size_t i;

    outIdx = 0;
    i = (size_t)startIdx;
    while( i <= (size_t)endIdx ) {
        outReal[outIdx] = inReal0[i] * inReal1[i];
        outIdx += 1;
        i += 1;
    }

    *outNBElement = outIdx;
    *outBegIdx = startIdx;

    return TA_SUCCESS;
}
";
        let parsed = parse_c_source_str(source);

        // Lookback body
        assert_eq!(parsed.lookback_body.len(), 1);
        match &parsed.lookback_body[0] {
            Statement::Return {
                value: Some(Expr::IntLiteral(0)),
            } => {}
            other => panic!("Expected Return with IntLiteral(0), got {other:?}"),
        }

        // Main function
        assert_eq!(parsed.functions.len(), 1);
        let func = &parsed.functions[0];
        assert_eq!(func.name, "TA_MULT");
        assert!(!func.is_internal);

        let body = &func.body;
        // VarDecl outIdx, VarDecl i, outIdx=0, i=(size_t)startIdx, while, *outNBElement, *outBegIdx, return
        assert_eq!(body.len(), 8);

        // Check while loop body
        match &body[4] {
            Statement::While { body, .. } => {
                assert_eq!(body.len(), 3); // arr assign, outIdx+=1, i+=1
            }
            other => panic!("Expected While, got {other:?}"),
        }

        // Check return
        match &body[7] {
            Statement::Return {
                value: Some(Expr::Var(s)),
            } if s == "SUCCESS" => {}
            other => panic!("Expected Return with Var(SUCCESS), got {other:?}"),
        }
    }

    #[test]
    fn test_switch_statement() {
        let tokens = tokenize(
            r"switch( mode ) {
                case MODE_A:
                    x = 1;
                    break;
                case MODE_B:
                    x = 2;
                    break;
                default:
                    x = 0;
                    break;
            }",
        );
        let mut parser = Parser::new(tokens);
        let stmt = parser.parse_statement();
        match stmt {
            Statement::Switch { cases, default, .. } => {
                assert_eq!(cases.len(), 2);
                assert_eq!(cases[0].0, "MODE_A");
                assert_eq!(cases[1].0, "MODE_B");
                assert_eq!(default.len(), 1);
            }
            other => panic!("Expected Switch, got {other:?}"),
        }
    }

    #[test]
    fn test_logical_operators() {
        let tokens = tokenize("x > 0 && y < 10 || z == 5");
        let mut parser = Parser::new(tokens);
        let expr = parser.parse_expr();
        // Should parse as (x > 0 && y < 10) || (z == 5)
        match expr {
            Expr::BinOp(_, BinOp::Or, _) => {} // top level is Or
            other => panic!("Expected Or at top level, got {other:?}"),
        }
    }

    #[test]
    fn test_not_expression() {
        let tokens = tokenize("!flag");
        let mut parser = Parser::new(tokens);
        let expr = parser.parse_expr();
        match expr {
            Expr::Not(inner) => match *inner {
                Expr::Var(name) => assert_eq!(name, "flag"),
                other => panic!("Expected Var, got {other:?}"),
            },
            other => panic!("Expected Not, got {other:?}"),
        }
    }

    #[test]
    fn test_extract_prefix_free_functions() {
        let source = r"
int sma_lookback(int optInTimePeriod)
{
    return optInTimePeriod - 1;
}

TA_RetCode sma(int startIdx, int endIdx,
                       const double inReal[],
                       int optInTimePeriod,
                       int *outBegIdx, int *outNBElement,
                       double outReal[])
{
    double periodTotal = 0.0;
    *outBegIdx = startIdx;
    *outNBElement = 0;
    return TA_SUCCESS;
}
";
        let parsed = parse_c_source_str(source);
        assert!(
            !parsed.lookback_body.is_empty(),
            "lookback body should be parsed from sma_lookback"
        );
        assert_eq!(parsed.functions.len(), 1);
        assert_eq!(parsed.functions[0].name, "sma");
        assert!(!parsed.functions[0].is_internal);
    }

    #[test]
    fn test_return_expression() {
        let tokens = tokenize("return optInTimePeriod - 1;");
        let mut parser = Parser::new(tokens);
        let stmt = parser.parse_statement();
        match stmt {
            Statement::Return {
                value: Some(Expr::BinOp(left, BinOp::Sub, right)),
            } => {
                match left.as_ref() {
                    Expr::Var(s) => assert_eq!(s, "optInTimePeriod"),
                    other => panic!("Expected Var, got {other:?}"),
                }
                match right.as_ref() {
                    Expr::IntLiteral(1) => {}
                    other => panic!("Expected IntLiteral(1), got {other:?}"),
                }
            }
            other => panic!("Expected Return with BinOp, got {other:?}"),
        }
    }
}
