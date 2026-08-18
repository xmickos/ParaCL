#include <cctype>
#include "main_definitives.hpp"

#pragma once

#define PARSE_ONE_CHAR(ch_, operand_name) \
            if((token.kind == TokenKind::Undefined) && (ch == ch_)) {    \
            token.lexem = std::string_view(&src[curr_loc], 1);                          \
            token.kind = operand_name;                                                  \
            token.loc = curr_loc;                                                       \
            tokens.push_back(token);                                                    \
            token = Token();                                                            \
            curr_loc++;                                                                 \
            continue;                                                                   \
        }

void parse_cl_arguments(CompilationContext& ctxt, int argc, char* argv[]);

bool may_be_identifier(char ch);

TokenKind classify_identifier(std::string_view view);
