#include "utils.hpp"
#include "main_definitives.hpp"

bool do_lexer_work(CompilationContext& ctxt) {

    std::string& src = ctxt.src;
    std::vector<Token>& tokens = ctxt.tokens;

   Token token;
   size_t curr_loc = 0, curr_len = 0;

    // TODO: rewrite to separate identifiers from literals
    for(char ch : src) {
        if(((token.kind == TokenKind::Undefined) || (token.kind == TokenKind::Terminal)) && may_be_identifier(ch)) {
            curr_len++;
            curr_loc++;
            token.kind = TokenKind::Terminal;
            continue;
        }
        if(token.kind == TokenKind::Terminal && !may_be_identifier(ch)) {
            token.lexem = std::string_view(&src[curr_loc - curr_len], curr_len);
            token.kind = classify_identifier(token.lexem);
            token.loc = curr_loc - curr_len;
            tokens.push_back(token);
            curr_len = 0;
            token = Token();
        }
        if(is_a_whitespace(ch)) {
            curr_loc++;
            continue;
        }
        PARSE_ONE_CHAR('+', TokenKind::PlusOperand);
        PARSE_ONE_CHAR('-', TokenKind::MinusOperand);
        PARSE_ONE_CHAR('*', TokenKind::MultiplyOperand);
        PARSE_ONE_CHAR('/', TokenKind::DivideOperand);
        PARSE_ONE_CHAR(';', TokenKind::Semicolon);
        PARSE_ONE_CHAR('=', TokenKind::Assign);
        PARSE_ONE_CHAR('?', TokenKind::Input);
        PARSE_ONE_CHAR('{', TokenKind::OpenBracket);
        PARSE_ONE_CHAR('}', TokenKind::CloseBracket);
        PARSE_ONE_CHAR('(', TokenKind::OpenRoundBracket);
        PARSE_ONE_CHAR(')', TokenKind::CloseRoundBracket);

        PARACL_UNREACHABLE() << "Lexer error: \'" << ch << "\' at position " << curr_loc;
    }
    if(token.kind == TokenKind::Terminal) {
        token.lexem = std::string_view(&src[curr_loc - curr_len], curr_len);
        token.kind = classify_identifier(token.lexem);
        token.loc = curr_loc - curr_len;
        tokens.push_back(token);
    }

    tokens.push_back(Token{TokenKind::EndOfFile, curr_loc, {}});

    return true;
}
