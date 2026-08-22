#include "main_definitives.hpp"
#include "utils.hpp"
#include <charconv>

enum class OpKind {
    PlusOp,
    MinusOp,
    MulOp,
    DivOp
};

enum class StatementKind {
    AssignStatement,
    PrintStatement,
    IfStatement,
    WhileStatement
};

struct Operand {};

struct ASTNode {
    virtual ~ASTNode() = default;
};

struct Statement : public ASTNode {
    StatementKind kind;
    std::vector<Operand> args;
};

struct Block : public Statement {
    std::vector<Statement> statements;
};

struct Expression : public ASTNode {
    std::vector<Operand> operands;
};

struct BinOp final : public Statement {
    OpKind kind;
    Expression lhs, rhs;
};


/*
    Parser grammatic:

    G ::= E;
    E ::= T{[+-]T}*
    T ::= P{[*\]P}*
    P ::= '('E')' | N
    N ::= ['0'-'9']+
*/

#define REPORT_PARSER_ERROR(str, tokens, p) PARACL_UNREACHABLE() << "Syntax error at pos " << p << ": expected " << str << " but got "  << tokens[p].lexem;

int getG(CompilationContext& ctxt);
int getE(const std::vector<Token>& tokens, size_t& p);
int getT(const std::vector<Token>& tokens, size_t& p);
int getP(const std::vector<Token>& tokens, size_t& p);
int getN(const std::vector<Token>& tokens, size_t& p);
