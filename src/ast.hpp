#include "main_definitives.hpp"
#include "utils.hpp"

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

struct BinOp : public Statement final {
    OpKind kind;
    Expression lhs, rhs;
};
