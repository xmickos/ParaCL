#include "main_definitives.hpp"
#include "utils.hpp"
#include "ast.hpp"

int getE(const std::vector<Token>& tokens, size_t& p) {

    int val = getT(tokens, p);

    while(tokens[p] == '+' || tokens[p] == '-') {
        switch(tokens[p].as_char()) {
            case '+':
                p++;
                val += getT(tokens, p);
                break;
            case '-':
                p++;
                val -= getT(tokens, p);
                break;
            default:
                REPORT_PARSER_ERROR("\'+\' or \'-\'", tokens, p);
        }
    }
    return val;
}

int getT(const std::vector<Token>& tokens, size_t& p) {
    int val = getP(tokens, p);
    while(tokens[p] == '*' || tokens[p] == '/') {
        switch(tokens[p].as_char()) {
            case '*':
                p++;
                val *= getP(tokens, p);
            case '/':
                p++;
                val /= getP(tokens, p);
            default:
                REPORT_PARSER_ERROR("\'*\' or \'/\'", tokens, p);
        }
    }
    return val;
}

int getP(const std::vector<Token>& tokens, size_t& p) {
    int val;
    if(tokens[p].as_char() == '(') {
        p++;
        val = getE(tokens, p);
        if(tokens[p].as_char() != ')') {
            REPORT_PARSER_ERROR("closing bracket", tokens, p);
        }
        p++;
        return val;
    } else {
        return getN(tokens, p);
    }
}

int getN(const std::vector<Token>& tokens, size_t& p) {
    if(!std::isdigit(tokens[p].as_char())) {
        REPORT_PARSER_ERROR("number", tokens, p);
    }
    int val;
    auto [ptr, errc] = std::from_chars(tokens[p].lexem.data(), tokens[p].lexem.data() + tokens[p].lexem.size(), val);
    p++;
    PARACL_ASSERT(errc == std::errc());
    return val;
}

int getG(CompilationContext& ctxt) {
    size_t p = 0;
    int val = getE(ctxt.tokens, p);
    if(ctxt.tokens[p].as_char() != ';') {
        REPORT_PARSER_ERROR(';', ctxt.tokens, p);
    }
    return val;
}


bool  do_parser_work(CompilationContext& ctxt) {
    return getG(ctxt);
}
