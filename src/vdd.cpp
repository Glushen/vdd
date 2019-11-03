#include "vdd.h"
#include "parser.h"

extern void yy_set_input_string(const char*);
extern void yy_clear_buffer();

std::string vdd::parseStatement(const std::string& input) {
    yy_set_input_string(input.c_str());
    yyparse();
    yy_clear_buffer();

    return "temp";
}

void yyerror(const char *s, ...) {
    // stub
}
