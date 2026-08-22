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

struct CompilationContext final {
    std::string src;
    std::vector<Token> tokens;
    AST ast;
};

bool do_lexer_work(CompilationContext& ctxt);

bool do_parser_work(CompilationContext& ctxt);
