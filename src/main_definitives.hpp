#include <vector>
#include <string_view>
#include <fstream>
#include <iostream>
#include <cstring>
#include "ast.hpp"

#pragma once

struct CompilationContext final {
    std::string src;
    std::vector<Token> tokens;
    AST ast;
};

bool do_lexer_work(CompilationContext& ctxt);

bool do_parser_work(CompilationContext& ctxt);
