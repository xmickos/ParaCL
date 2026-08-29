#include <charconv>

#pragma once

enum class TokenKind {
    OpenBracket,
    CloseBracket,
    OpenRoundBracket,
    CloseRoundBracket,

    Terminal,

    WhileKeyword,
    IfKeyword,
    PrintKeyword,

    Assign,
    PlusOperand,
    MinusOperand,
    MultiplyOperand,
    DivideOperand,

    Input,
    Semicolon,

    Undefined,
    EndOfFile
};

struct Token {
    TokenKind kind = TokenKind::Undefined;
    size_t loc;
    std::string_view lexem;

    bool operator==(const Token& rhs) const {
        return  (kind == rhs.kind) &&
                (loc == rhs.loc) &&
                (lexem == rhs.lexem);
    }

    bool operator==(const char ch) const {
        return (lexem.size() == 1) && (lexem[0] == ch);
    }

    bool operator!=(const Token& rhs) const {
        return !(*this == rhs);
    }

    bool operator!=(const Token& rhs) {
        return !(*this == rhs);
    }

    char as_char() const;
};

enum class ExpressionType {
    PlusOp,
    MinusOp,
    MulOp,
    DivOp,
    Constant,
    Identifier,
    Literal
};

enum class StatementKind {
    AssignStatement,
    PrintStatement,
    IfStatement,
    WhileStatement
};

struct ASTNode {
    virtual ~ASTNode() = default;
};

struct Statement : public ASTNode {
    StatementKind kind;
    std::vector<Statement> args;
};

struct Block : public Statement {
    std::vector<Statement> statements;
};

struct Expression : public ASTNode {
    ExpressionType type;
    std::vector<Expression> operands;
    std::variant<int, std::string_view, std::monostate> raw_data;
};

struct AST {
    Expression root;
};


/*
    Parser grammatic:

    G ::= E;
    E ::= T{[+-]T}*
    T ::= P{[*\]P}*
    P ::= '('E')' | I | N
    N ::= ['0'-'9']+
    I ::= L{L|N}*
    L ::= {['a'-'z'] | ['A'-'Z'] | '_'}+
*/

Expression getG(const std::vector<Token>& tokens);
Expression getE(const std::vector<Token>& tokens, size_t& p);
Expression getT(const std::vector<Token>& tokens, size_t& p);
Expression getP(const std::vector<Token>& tokens, size_t& p);
Expression getI(const std::vector<Token>& tokens, size_t& p);
Expression getN(const std::vector<Token>& tokens, size_t& p);
