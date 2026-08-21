#include "main_definitives.hpp"
#include "utils.hpp"

int main(int argc, char* argv[]) {

    CompilationContext ctxt;

    // TODO: rewrite in more precise & pretty way
    PARACL_ASSERT(parse_cl_arguments(ctxt, argc, argv)) << "CL arguments parse phase failed!";

    PARACL_ASSERT(do_lexer_work(ctxt)) << "Lexer phase failed!";

    PARACL_ASSERT(do_parser_work(ctxt)) << "Parser phase failed!";

    return 0;
}
