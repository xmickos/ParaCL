#include "main_definitives.hpp"
#include "utils.hpp"

Expression getE_tail(const std::vector<Token>& tokens, size_t& p, Expression expr) {
    Expression tmp;
    while(tokens[p].kind == TokenKind::PlusOperand || tokens[p].kind == TokenKind::MinusOperand) {
        tmp = std::move(expr);
        expr.operands.clear();
        expr.raw_data = std::monostate{};
        expr.operands.push_back(std::move(tmp));
        expr.type = (tokens[p].kind == TokenKind::PlusOperand ? ExpressionType::PlusOp : ExpressionType::MinusOp);
        p++;
        expr.operands.push_back(getT(tokens, p));
    }

    return expr;
}

Expression getE(const std::vector<Token>& tokens, size_t& p) {

    Expression expr = getT(tokens, p);

    return getE_tail(tokens, p, std::move(expr));
}

Expression getStatement(const std::vector<Token>& tokens, size_t& p) {
    Expression expr = getT(tokens, p);
    if(tokens[p].kind == TokenKind::Assign) {
        if(expr.type != ExpressionType::Identifier) {
            REPORT_PARSER_ERROR("wrong lhs is assing op", tokens, p);
        }
        p++;
        Expression assign_expr{ExpressionType::Assign, {expr, getStatement(tokens, p)}, std::monostate{}};
        return assign_expr;
    }
    return getE_tail(tokens, p, std::move(expr));
}

Expression getT(const std::vector<Token>& tokens, size_t& p) {
    Expression expr = getP(tokens, p), tmp;
    while(tokens[p].kind == TokenKind::MultiplyOperand || tokens[p].kind == TokenKind::DivideOperand) {
        tmp = std::move(expr);
        expr.operands.clear();
        expr.raw_data = std::monostate{};
        expr.operands.push_back(std::move(tmp));
        expr.type = (tokens[p].kind == TokenKind::MultiplyOperand ? ExpressionType::MulOp : ExpressionType::DivOp);
        p++;
        expr.operands.push_back(getP(tokens, p));
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
    } else if(tokens[p].kind == TokenKind::Terminal) {
        return (is_a_number(tokens[p].lexem) ? getN(tokens, p) : getI(tokens, p));
    } else {
        REPORT_PARSER_ERROR("terminal token", tokens, p);
    }
}

Expression getI(const std::vector<Token>& tokens, size_t& p) {
    PARACL_ASSERT(!std::isdigit(tokens[p].lexem.front()) || tokens[p].kind != TokenKind::Terminal) << "Wrong literal: " << tokens[p].lexem;
    Expression expr;
    expr.type = ExpressionType::Identifier;
    expr.raw_data = tokens[p].lexem;
    p++;
    return expr;
}

Expression getN(const std::vector<Token>& tokens, size_t& p) {
    if(tokens[p].kind != TokenKind::Terminal || !is_a_number(tokens[p].lexem)) {
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

std::vector<Expression> getG(const std::vector<Token>& tokens) {
    size_t p = 0;
    std::vector<Expression> roots;
    do {
        roots.push_back(getStatement(tokens, p));
        if(tokens[p].kind != TokenKind::Semicolon) {
            REPORT_PARSER_ERROR(';', tokens, p);
        }
        p++;
    } while (tokens[p].kind != TokenKind::EndOfFile);
    return roots;
}


bool do_parser_work(CompilationContext& ctxt) {
    ctxt.ast.roots = getG(ctxt.tokens);
    return true;
}
