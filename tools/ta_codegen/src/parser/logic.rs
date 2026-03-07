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

        // Newline
        if c == '\n' {
            // Collapse consecutive newlines
            if tokens.last() != Some(&Token::Newline) {
                tokens.push(Token::Newline);
            }
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

        // Two-char operators: <=, >=, ==, +=, -=, *=, /=
        if i + 1 < chars.len() {
            let two = format!("{}{}", c, chars[i + 1]);
            if matches!(
                two.as_str(),
                "<=" | ">=" | "==" | "+=" | "-=" | "*=" | "/="
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

        // Numbers
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
        while self.peek() == Some(&Token::Newline) {
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
            Some(Token::Ident(ref s))
                if matches!(s.as_str(), "index" | "real" | "integer") =>
            {
                self.parse_var_decl()
            }
            _ => self.parse_assignment(),
        }
    }

    fn parse_while(&mut self) -> Statement {
        self.advance(); // consume "while"
        let condition = self.parse_expr();
        self.expect(&Token::LBrace);
        self.skip_newlines();
        let body = self.parse_statements();
        self.expect(&Token::RBrace);
        Statement::While { condition, body }
    }

    fn parse_var_decl(&mut self) -> Statement {
        let type_tok = self.advance();
        let var_type = match type_tok {
            Token::Ident(ref s) => match s.as_str() {
                "index" => VarType::Index,
                "real" => VarType::Real,
                "integer" => VarType::Integer,
                _ => panic!("Unknown type: {}", s),
            },
            _ => panic!("Expected type keyword"),
        };
        let name = match self.advance() {
            Token::Ident(s) => s,
            other => panic!("Expected identifier, got {:?}", other),
        };
        self.expect_op("=");
        let init = self.parse_expr();
        Statement::VarDecl {
            var_type,
            name,
            init,
        }
    }

    fn parse_assignment(&mut self) -> Statement {
        // Could be: ident = expr, ident[expr] = expr, or ident += expr
        let name = match self.advance() {
            Token::Ident(s) => s,
            other => panic!("Expected identifier, got {:?}", other),
        };

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
            };
        }

        // Check for compound assignment or simple assignment
        match self.advance() {
            Token::Op(ref op) if op == "=" => {
                let value = self.parse_expr();
                Statement::Assign {
                    target: Expr::Var(name),
                    value,
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
                }
            }
            other => panic!("Expected '=' or compound assignment, got {:?}", other),
        }
    }

    // Expression parsing with precedence climbing

    fn parse_expr(&mut self) -> Expr {
        self.parse_comparison()
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
        let mut left = self.parse_primary();
        while let Some(Token::Op(ref op)) = self.peek() {
            let bin_op = match op.as_str() {
                "*" => BinOp::Mul,
                "/" => BinOp::Div,
                _ => break,
            };
            self.advance();
            let right = self.parse_primary();
            left = Expr::BinOp(Box::new(left), bin_op, Box::new(right));
        }
        left
    }

    fn parse_primary(&mut self) -> Expr {
        match self.advance() {
            Token::IntNumber(n) => Expr::IntLiteral(n),
            Token::Number(n) => Expr::Literal(n),
            Token::Ident(name) => {
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

/// Parse a `.logic` pseudocode file into a list of AST statements.
pub fn parse_logic(path: &Path) -> Vec<Statement> {
    let input = std::fs::read_to_string(path)
        .unwrap_or_else(|e| panic!("Failed to read {}: {}", path.display(), e));
    let tokens = tokenize(&input);
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
