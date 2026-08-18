#include <cctype>
#include <sstream>
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

class AssertHandler final {

    const char* cond_str;
    const char* file;
    int line;
    std::stringstream ss;

    public:
        AssertHandler(const char* cond_str_, const char* file_, int line_) :
            cond_str(cond_str_),  file(file_), line(line_) {}

        template<typename T>
        AssertHandler& operator<<(const T& val) {
            ss << val;
            return *this;
        }

        ~AssertHandler() {
            std::cerr << "Assertion " << cond_str << " failed at " << file << ":" << line << ": " << ss.str() << std::endl;
            std::abort();
        }
};

#define PARACL_ASSERT(condition) \
            if(condition) { ; } else AssertHandler(#condition, __FILE__, __LINE__)

#define PARACL_UNREACHABLE() AssertHandler("unreachable", __FILE__, __LINE__)
