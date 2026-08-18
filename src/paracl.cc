#include "main_definitives.hpp"
#include "utils.hpp"

int main(int argc, char* argv[]) {

    CompilationContext ctxt;

    parse_cl_arguments(ctxt, argc, argv);

    do_lexer_work(ctxt);

    return 0;
}
