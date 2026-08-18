#include "utils.hpp"
#include "main_definitives.hpp"

void do_lexer_work(CompilationContext& ctxt) {

    std::string& src = ctxt.src;
    std::vector<Token>& tokens = ctxt.token_stream.tokens;

   Token token;
   size_t curr_loc = 0, curr_len = 0;

    for(char ch : src) {
        if(((token.kind == TokenKind::Undefined) || (token.kind == TokenKind::Identifier)) && may_be_identifier(ch)) {
            curr_len++;
            curr_loc++;
            token.kind = TokenKind::Identifier;
            continue;
        }
        if(token.kind == TokenKind::Identifier && !may_be_identifier(ch)) {
            token.lexem = std::string_view(&src[curr_loc - 1], curr_len);
            token.kind = classify_identifier(token.lexem);
            token.loc = curr_loc - curr_len;
            tokens.push_back(token);
            curr_len = 0;
            token = Token();
        }
        if(ch == ' ' || ch == '\n') {
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
        PARSE_ONE_CHAR('\0', TokenKind::CloseRoundBracket);

        PARACL_UNREACHABLE() << "Lexer error: \'" << ch << "\' at position " << curr_loc << std::endl;
        std::terminate();
    }
}
