#include "main_definitives.hpp"
#include "utils.hpp"

Expression getE(const std::vector<Token>& tokens, size_t& p) {

    Expression expr = getT(tokens, p), tmp;

    while(tokens[p].kind == TokenKind::PlusOperand || tokens[p].kind == TokenKind::MinusOperand) {
        p++;
        tmp.operands.push_back(std::move(expr));
        tmp.type = tokens[p].kind == TokenKind::PlusOperand ? ExpressionType::PlusOp : ExpressionType::MinusOp;
        tmp.operands.push_back(getT(tokens, p));
        expr = std::move(tmp);
    }

    return expr;
}

Expression getT(const std::vector<Token>& tokens, size_t& p) {
    Expression expr = getP(tokens, p), tmp;
    while(tokens[p].kind == TokenKind::MultiplyOperand || tokens[p].kind == TokenKind::DivideOperand) {
        p++;
        tmp = std::move(expr);
        expr.operands.push_back(std::move(tmp));
        expr.type = tokens[p].kind == TokenKind::MultiplyOperand ? ExpressionType::MulOp : ExpressionType::DivOp;
        expr.operands.push_back(getP(tokens, p));
        expr = std::move(tmp);
    }
    return expr;
}

Expression getP(const std::vector<Token>& tokens, size_t& p) {
    Expression expr;
    if(tokens[p].kind == TokenKind::OpenRoundBracket) {
        p++;
        expr = getE(tokens, p);
        if(tokens[p].kind != TokenKind::CloseRoundBracket) {
            REPORT_PARSER_ERROR("closing bracket", tokens, p);
        }
        p++;
        return expr;
    } else if(tokens[p].kind == TokenKind::Identifier) {
        return getI(tokens, p);
    } else {
        return getN(tokens, p);
    }
}

Expression getI(const std::vector<Token>& tokens, size_t& p) {
    Expression expr;
    expr.type = ExpressionType::Identifier;
    expr.raw_data = tokens[p].lexem;
    return expr;
}

Expression getN(const std::vector<Token>& tokens, size_t& p) {
    if(tokens[p].kind != TokenKind::Identifier || !std::all_of(tokens[p].lexem.begin(), tokens[p].lexem.end(), [](auto ch){ return std::isdigit(ch); })) {
        REPORT_PARSER_ERROR("number", tokens, p);
    }
    Expression expr;
    expr.type = ExpressionType::Constant;
    int val;
    auto [ptr, errc] = std::from_chars(tokens[p].lexem.data(), tokens[p].lexem.data() + tokens[p].lexem.size(), val);
    expr.raw_data = val;
    p++;
    PARACL_ASSERT(errc == std::errc());
    return expr;
}

Expression getG(const std::vector<Token>& tokens) {
    size_t p = 0;
    Expression expr = getE(tokens, p);
    if(tokens[p].kind != TokenKind::Semicolon) {
        REPORT_PARSER_ERROR(';', tokens, p);
    }
    return expr;
}


bool do_parser_work(CompilationContext& ctxt) {
    ctxt.ast.root = getG(ctxt.tokens);
    return true;
}
