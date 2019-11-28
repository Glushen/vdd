#include "vdd.h"
#include "parser.h"
#include "inversion.h"
#include <cstdarg>
#include <sstream>

extern void yy_set_input_string(const char*);
extern void yy_clear_buffer();

static bool accepted = false;
static std::string result;

std::variant<std::string, std::string> vdd::parseStatement(const std::string& input) {
#if YYDEBUG
    yydebug = 1;
#endif

    yy_set_input_string(input.c_str());
    yyparse();
    yy_clear_buffer();

    if (accepted) {
        return std::variant<std::string, std::string>(std::in_place_index<0>, result);
    } else {
        return std::variant<std::string, std::string>(std::in_place_index<1>, result);
    }
}

void yy_accept_ast(vdd::Declaration declaration) {
    accepted = true;
    auto invertedDeclaration = invertDeclaration(std::move(declaration));
    auto stream = std::stringstream();
    invertedDeclaration.print(stream, 0);
    result = stream.str();
}

void yyerror(const char* format, ...) {
    accepted = false;

    va_list arguments;

    va_start(arguments, format);
    char* result_chars = new char[vsnprintf(nullptr, 0, format, arguments) + 1];
    va_end(arguments);

    va_start(arguments, format);
    vsprintf(result_chars, format, arguments);
    va_end(arguments);

    result = result_chars;
    delete[] result_chars;
}
