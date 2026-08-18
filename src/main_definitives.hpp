#include <vector>
#include <string_view>
#include <fstream>
#include <iostream>
#include <cstring>

#pragma once

#define PARACL_ASSERT(condition) \
        if (condition) \
            std::cerr << ""

#define PARACL_UNREACHABLE() \
        std::cerr << ""

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
};

struct TokenStream final {
    std::vector<Token> tokens;
};

struct CompilationContext final {
    std::string src;
    TokenStream token_stream;
    AST ast;
};

void do_lexer_work(CompilationContext& ctxt);
