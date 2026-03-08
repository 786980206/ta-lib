use std::path::Path;

use crate::ir::{BinOp, Expr, Statement, VarType};

// --- Tokenizer ---

#[derive(Debug, Clone, PartialEq)]
enum Token {
    Ident(String),
    Number(f64),
    IntNumber(i64),
    Op(String),
    LBrace,
    RBrace,
    LBracket,
    RBracket,
    LParen,
    RParen,
    Bang,
    Semicolon,
    Comma,
    Newline,
}

fn tokenize(input: &str) -> Vec<Token> {
    let mut tokens = Vec::new();
    let chars: Vec<char> = input.chars().collect();
    let mut i = 0;

    while i < chars.len() {
        let c = chars[i];

        // Skip spaces and tabs
        if c == ' ' || c == '\t' {
            i += 1;
            continue;
        }

        // Skip single-line comments: // ...
        if c == '/' && i + 1 < chars.len() && chars[i + 1] == '/' {
            while i < chars.len() && chars[i] != '\n' {
                i += 1;
            }
            continue;
        }

        // Skip multi-line comments: /* ... */
        if c == '/' && i + 1 < chars.len() && chars[i + 1] == '*' {
            i += 2;
            while i + 1 < chars.len() && !(chars[i] == '*' && chars[i + 1] == '/') {
                i += 1;
            }
            i += 2; // skip */
            continue;
        }

        // Newline
        if c == '\n' {
            // Collapse consecutive newlines
            if tokens.last() != Some(&Token::Newline) {
                tokens.push(Token::Newline);
            }
            i += 1;
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

        // Two-char operators: <=, >=, ==, +=, -=, *=, /=, &&, ||, --
        if i + 1 < chars.len() {
            let two = format!("{}{}", c, chars[i + 1]);
            if matches!(
                two.as_str(),
                "<=" | ">=" | "==" | "+=" | "-=" | "*=" | "/=" | "&&" | "||" | "--"
            ) {
                tokens.push(Token::Op(two));
                i += 2;
                continue;
            }
        }

        // Single-char operators
        if matches!(c, '+' | '-' | '*' | '/' | '=' | '<' | '>') {
            tokens.push(Token::Op(c.to_string()));
            i += 1;
            continue;
        }

        // Numbers (including negative literals like -0.00000000000001)
        if c.is_ascii_digit() {
            let start = i;
            while i < chars.len() && chars[i].is_ascii_digit() {
                i += 1;
            }
            if i < chars.len() && chars[i] == '.' {
                i += 1;
                while i < chars.len() && chars[i].is_ascii_digit() {
                    i += 1;
                }
                let s: String = chars[start..i].iter().collect();
                tokens.push(Token::Number(s.parse().unwrap()));
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

        // Skip carriage returns
        if c == '\r' {
            i += 1;
            continue;
        }

        panic!("Unexpected character: {:?} at position {}", c, i);
    }

    tokens
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
            other => panic!("Expected '{}', got {:?}", op, other),
        }
    }

    fn expect(&mut self, expected: &Token) {
        let tok = self.advance();
        assert_eq!(&tok, expected, "Expected {:?}, got {:?}", expected, tok);
    }

    fn skip_newlines(&mut self) {
        while matches!(self.peek(), Some(&Token::Newline) | Some(&Token::Semicolon)) {
            self.advance();
        }
    }

    fn parse_statements(&mut self) -> Vec<Statement> {
        let mut stmts = Vec::new();
        self.skip_newlines();
        while self.pos < self.tokens.len() {
            if self.peek() == Some(&Token::RBrace) {
                break;
            }
            stmts.push(self.parse_statement());
            self.skip_newlines();
        }
        stmts
    }

    fn parse_statement(&mut self) -> Statement {
        match self.peek().cloned() {
            Some(Token::Ident(ref s)) if s == "while" => self.parse_while(),
            Some(Token::Ident(ref s)) if s == "for" => self.parse_for(),
            Some(Token::Ident(ref s)) if s == "if" => self.parse_if(),
            Some(Token::Ident(ref s)) if s == "return" => self.parse_return(),
            Some(Token::Ident(ref s))
                if matches!(
                    s.as_str(),
                    "index" | "real" | "integer" | "double" | "int" | "size_t"
                ) =>
            {
                self.parse_var_decl()
            }
            _ => self.parse_assignment_or_expr_stmt(),
        }
    }

    fn parse_while(&mut self) -> Statement {
        self.advance(); // consume "while"

        // Handle optional parenthesized condition
        let condition = if self.peek() == Some(&Token::LParen) {
            self.advance(); // consume (
            let cond = self.parse_expr();
            self.expect(&Token::RParen);
            cond
        } else {
            self.parse_expr()
        };

        self.skip_newlines();
        self.expect(&Token::LBrace);
        self.skip_newlines();
        let body = self.parse_statements();
        self.expect(&Token::RBrace);
        Statement::While { condition, body }
    }

    /// Parse: `for( var = count; var > 0; var-- ) { body }`
    /// This is the countdown for loop pattern used by TA-Lib.
    fn parse_for(&mut self) -> Statement {
        self.advance(); // consume "for"
        self.expect(&Token::LParen);

        // Parse: var = count
        let var = match self.advance() {
            Token::Ident(s) => s,
            other => panic!("Expected identifier in for loop, got {:?}", other),
        };
        self.expect_op("=");
        let count = self.parse_expr();
        self.expect(&Token::Semicolon);

        // Parse: var > 0 (skip — we know the pattern)
        let _cond_var = self.advance(); // var
        self.advance(); // > operator
        self.advance(); // 0
        self.expect(&Token::Semicolon);

        // Parse: var-- (skip — we know the pattern)
        let _dec_var = self.advance(); // var
        self.advance(); // -- operator
        self.expect(&Token::RParen);

        self.skip_newlines();
        self.expect(&Token::LBrace);
        self.skip_newlines();
        let body = self.parse_statements();
        self.expect(&Token::RBrace);

        Statement::For { var, count, body }
    }

    fn parse_if(&mut self) -> Statement {
        self.advance(); // consume "if"

        // Handle optional parenthesized condition
        let condition = if self.peek() == Some(&Token::LParen) {
            self.advance(); // consume (
            let cond = self.parse_expr();
            self.expect(&Token::RParen);
            cond
        } else {
            self.parse_expr()
        };

        self.skip_newlines();
        self.expect(&Token::LBrace);
        self.skip_newlines();
        let then_body = self.parse_statements();
        self.expect(&Token::RBrace);

        self.skip_newlines();

        let else_body = if let Some(Token::Ident(ref s)) = self.peek() {
            if s == "else" {
                self.advance(); // consume "else"
                self.skip_newlines();
                if let Some(Token::Ident(ref s2)) = self.peek() {
                    if s2 == "if" {
                        // else if — recurse
                        vec![self.parse_if()]
                    } else {
                        // else { ... }
                        self.expect(&Token::LBrace);
                        self.skip_newlines();
                        let body = self.parse_statements();
                        self.expect(&Token::RBrace);
                        body
                    }
                } else {
                    // else { ... }
                    self.expect(&Token::LBrace);
                    self.skip_newlines();
                    let body = self.parse_statements();
                    self.expect(&Token::RBrace);
                    body
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

    fn parse_return(&mut self) -> Statement {
        self.advance(); // consume "return"
        let value = match self.advance() {
            Token::Ident(s) => s,
            other => panic!("Expected identifier after return, got {:?}", other),
        };
        Statement::Return { value }
    }

    fn parse_var_decl(&mut self) -> Statement {
        let type_tok = self.advance();
        let var_type = match type_tok {
            Token::Ident(ref s) => match s.as_str() {
                "index" | "size_t" => VarType::Index,
                "real" | "double" => VarType::Real,
                "integer" | "int" => VarType::Integer,
                _ => panic!("Unknown type: {}", s),
            },
            _ => panic!("Expected type keyword"),
        };
        let name = match self.advance() {
            Token::Ident(s) => s,
            other => panic!("Expected identifier, got {:?}", other),
        };

        // Check for init or bare declaration
        match self.peek() {
            Some(&Token::Semicolon) | Some(&Token::Newline) | None => {
                // No initializer
                Statement::VarDecl {
                    var_type,
                    name,
                    init: None,
                }
            }
            _ => {
                self.expect_op("=");
                let init = self.parse_expr();
                Statement::VarDecl {
                    var_type,
                    name,
                    init: Some(init),
                }
            }
        }
    }

    fn parse_assignment_or_expr_stmt(&mut self) -> Statement {
        // Could be: ident = expr, ident[expr] = expr, ident += expr,
        // or a function call statement like ARRAY_COPY(...)
        let name = match self.advance() {
            Token::Ident(s) => s,
            other => panic!("Expected identifier, got {:?}", other),
        };

        // Check for function call statement: FUNC(args...)
        if self.peek() == Some(&Token::LParen) {
            // Could be a function call used as a statement (like ARRAY_COPY)
            // But also could be a function call in an assignment context
            // Check if this looks like a standalone call (followed by ; or newline after closing paren)
            let save_pos = self.pos;
            self.advance(); // consume (
            let args = self.parse_call_args();
            self.expect(&Token::RParen);

            // If followed by ; or newline, it's a statement-level function call
            // For now, treat it as an assignment to a dummy to get it rendered
            // Actually, we need a proper expression statement or handle it as a special statement.
            // For ARRAY_COPY, it's essentially a statement. Let's create an Assign
            // with the FuncCall as the value and no real target.
            // Actually, let's check if there's an = after
            if matches!(self.peek(), Some(&Token::Semicolon) | Some(&Token::Newline) | None) {
                // Statement-level function call (like ARRAY_COPY)
                return Statement::Assign {
                    target: Expr::Var("_".to_string()),
                    value: Expr::FuncCall(name, args),
                    compound: false,
                };
            }

            // Not a standalone call — backtrack and treat as assignment
            self.pos = save_pos;
        }

        // Check for array access
        if self.peek() == Some(&Token::LBracket) {
            self.advance(); // consume [
            let index_expr = self.parse_expr();
            self.expect(&Token::RBracket);
            self.expect_op("=");
            let value = self.parse_expr();
            return Statement::Assign {
                target: Expr::ArrayAccess(name, Box::new(index_expr)),
                value,
                compound: false,
            };
        }

        // Check for compound assignment or simple assignment
        match self.advance() {
            Token::Op(ref op) if op == "=" => {
                let value = self.parse_expr();
                Statement::Assign {
                    target: Expr::Var(name),
                    value,
                    compound: false,
                }
            }
            Token::Op(ref op) if op == "+=" || op == "-=" || op == "*=" || op == "/=" => {
                let bin_op = match op.as_str() {
                    "+=" => BinOp::Add,
                    "-=" => BinOp::Sub,
                    "*=" => BinOp::Mul,
                    "/=" => BinOp::Div,
                    _ => unreachable!(),
                };
                let rhs = self.parse_expr();
                Statement::Assign {
                    target: Expr::Var(name.clone()),
                    value: Expr::BinOp(Box::new(Expr::Var(name)), bin_op, Box::new(rhs)),
                    compound: true,
                }
            }
            other => panic!("Expected '=' or compound assignment, got {:?}", other),
        }
    }

    /// Parse comma-separated function call arguments.
    fn parse_call_args(&mut self) -> Vec<Expr> {
        let mut args = Vec::new();
        if self.peek() == Some(&Token::RParen) {
            return args;
        }
        args.push(self.parse_expr());
        while self.peek() == Some(&Token::Comma) {
            self.advance(); // consume ,
            args.push(self.parse_expr());
        }
        args
    }

    // Expression parsing with precedence climbing

    fn parse_expr(&mut self) -> Expr {
        self.parse_logical_or()
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
        let mut left = self.parse_additive();
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
        while let Some(Token::Op(ref op)) = self.peek() {
            let bin_op = match op.as_str() {
                "*" => BinOp::Mul,
                "/" => BinOp::Div,
                _ => break,
            };
            self.advance();
            let right = self.parse_unary();
            left = Expr::BinOp(Box::new(left), bin_op, Box::new(right));
        }
        left
    }

    fn parse_unary(&mut self) -> Expr {
        if self.peek() == Some(&Token::Bang) {
            self.advance(); // consume !
            let operand = self.parse_unary();
            return Expr::Not(Box::new(operand));
        }
        // Handle unary minus for negative number literals
        if let Some(Token::Op(ref op)) = self.peek() {
            if op == "-" {
                // Check if this is a unary minus (negative literal)
                let save_pos = self.pos;
                self.advance(); // consume -
                if let Some(Token::Number(n)) = self.peek().cloned() {
                    self.advance();
                    return Expr::Literal(-n);
                } else if let Some(Token::IntNumber(n)) = self.peek().cloned() {
                    self.advance();
                    return Expr::IntLiteral(-n);
                }
                // Not a number — backtrack
                self.pos = save_pos;
            }
        }
        self.parse_primary()
    }

    fn is_type_keyword(s: &str) -> bool {
        matches!(s, "double" | "int" | "size_t" | "real" | "integer" | "index")
    }

    fn parse_primary(&mut self) -> Expr {
        match self.peek().cloned() {
            Some(Token::LParen) => {
                self.advance(); // consume (
                // Check if this is a C-style cast: (double), (int), (size_t)
                if let Some(Token::Ident(ref s)) = self.peek() {
                    if Self::is_type_keyword(s) {
                        let type_name = s.clone();
                        self.advance(); // consume type keyword
                        self.expect(&Token::RParen);
                        let var_type = match type_name.as_str() {
                            "double" | "real" => VarType::Real,
                            "int" | "integer" => VarType::Integer,
                            "size_t" | "index" => VarType::Index,
                            _ => unreachable!(),
                        };
                        let operand = self.parse_unary();
                        return Expr::Cast(var_type, Box::new(operand));
                    }
                }
                // Grouped expression
                let expr = self.parse_expr();
                self.expect(&Token::RParen);
                expr
            }
            _ => {
                let tok = self.advance();
                match tok {
                    Token::IntNumber(n) => Expr::IntLiteral(n),
                    Token::Number(n) => Expr::Literal(n),
                    Token::Ident(name) => {
                        // Check for function call: IDENT(args...)
                        if self.peek() == Some(&Token::LParen) {
                            self.advance(); // consume (
                            let args = self.parse_call_args();
                            self.expect(&Token::RParen);
                            return Expr::FuncCall(name, args);
                        }
                        // Check for array access
                        if self.peek() == Some(&Token::LBracket) {
                            self.advance(); // consume [
                            let index = self.parse_expr();
                            self.expect(&Token::RBracket);
                            Expr::ArrayAccess(name, Box::new(index))
                        } else {
                            Expr::Var(name)
                        }
                    }
                    other => panic!("Unexpected token in expression: {:?}", other),
                }
            }
        }
    }
}

/// Parse a `.logic` pseudocode file into a list of AST statements.
pub fn parse_logic(path: &Path) -> Vec<Statement> {
    let input = std::fs::read_to_string(path)
        .unwrap_or_else(|e| panic!("Failed to read {}: {}", path.display(), e));
    parse_logic_str(&input)
}

/// Parse a logic code string into a list of AST statements.
pub fn parse_logic_str(input: &str) -> Vec<Statement> {
    let tokens = tokenize(input);
    let mut parser = Parser::new(tokens);
    parser.parse_statements()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_parse_mult_logic() {
        let stmts = parse_logic(Path::new("../../ta_func_defs/mult/mult.logic"));
        assert_eq!(stmts.len(), 5);
        // First statement is VarDecl index outIdx
        match &stmts[0] {
            Statement::VarDecl { var_type, name, .. } => {
                assert_eq!(*var_type, VarType::Index);
                assert_eq!(name, "outIdx");
            }
            _ => panic!("Expected VarDecl"),
        }
        // Second statement is VarDecl index i
        match &stmts[1] {
            Statement::VarDecl { var_type, name, .. } => {
                assert_eq!(*var_type, VarType::Index);
                assert_eq!(name, "i");
            }
            _ => panic!("Expected VarDecl"),
        }
        // Third statement is While
        match &stmts[2] {
            Statement::While { body, .. } => {
                assert_eq!(body.len(), 3);
            }
            _ => panic!("Expected While"),
        }
        // Fourth is Assign outNBElement
        match &stmts[3] {
            Statement::Assign { target, .. } => match target {
                Expr::Var(name) => assert_eq!(name, "outNBElement"),
                _ => panic!("Expected Var target"),
            },
            _ => panic!("Expected Assign"),
        }
        // Fifth is Assign outBegIdx
        match &stmts[4] {
            Statement::Assign { target, .. } => match target {
                Expr::Var(name) => assert_eq!(name, "outBegIdx"),
                _ => panic!("Expected Var target"),
            },
            _ => panic!("Expected Assign"),
        }
    }
}
