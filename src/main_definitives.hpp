#include <vector>
#include <string_view>
#include <fstream>
#include <iostream>
#include <cstring>

#pragma once

struct Node;

struct AST {
    Node* root;
};

enum class TokenKind {
    OpenBracket,
    CloseBracket,
    OpenRoundBracket,
    CloseRoundBracket,

    Identifier,

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

    bool operator==(Token& rhs) {
        return  (kind == rhs.kind) &&
                (loc == rhs.loc) &&
                (lexem == rhs.lexem);
    }

    bool operator==(const Token& rhs) const {
        return  (kind == rhs.kind) &&
                (loc == rhs.loc) &&
                (lexem == rhs.lexem);
    }
};

struct CompilationContext final {
    std::string src;
    std::vector<Token> tokens;
    AST ast;
};

void do_lexer_work(CompilationContext& ctxt);
