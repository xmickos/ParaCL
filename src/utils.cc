#include <sstream>
#include "utils.hpp"
#include "main_definitives.hpp"

bool may_be_identifier(char ch) {
    // TODO: Who should check is identifier starts with non-digit? Like 1231abc.
    return std::isalnum(ch) || (ch == '_');
}

TokenKind classify_identifier(std::string_view view) {
    if(view == "while") {
        return TokenKind::WhileKeyword;
    }
    if(view == "if") {
        return TokenKind::IfKeyword;
    }
    if(view == "print") {
        return TokenKind::PrintKeyword;
    }
    return TokenKind::Identifier;
}


void parse_cl_arguments(CompilationContext& ctxt, int argc, char* argv[]) {

    PARACL_ASSERT(argc != 2) << "Wrong arguments, pass \'-h\' for help.\n";

    if(strcmp(argv[1],"-h") == 0) {
        std::cout << "HWPL, ParaCL interpreter\n" <<\
                    "Task author: github.com/tilir\n" <<\
                    "Implemented by github.com/xmickos\n" <<\
                    "Usage: $ paracl [input_file]\n";
        std::exit(0);
    }
    std::ifstream fs(argv[1]);
    PARACL_ASSERT(!fs.is_open()) << "Failed to open input file.";

    std::stringstream buffer;
    buffer << fs.rdbuf();
    ctxt.src = buffer.str();
}
