#include "vdd.h"
#include "parser.h"
#include "inversion.h"
#include <cstdarg>
#include <sstream>

extern void yy_set_input_string(const char*);
extern void yy_clear_buffer();

static vdd::Result result;

vdd::Result vdd::parseStatement(const std::string& input) {
#if YYDEBUG
    yydebug = 1;
#endif

    yy_set_input_string(input.c_str());
    yyparse();
    yy_clear_buffer();

    return result;
}

void yy_accept_ast(vdd::Declaration declaration) {
    try {
        result.accepted = true;
        auto invertedDeclaration = invertDeclaration(std::move(declaration));
        auto stream = std::stringstream();
        invertedDeclaration.print(stream, 0);
        result.output = stream.str();
    } catch (const std::invalid_argument& exception) {
        result.accepted = false;
        result.output = exception.what();
    }
}

void yyerror(const char* format, ...) {
    result.accepted = false;

    va_list arguments;

    va_start(arguments, format);
    char* result_chars = new char[vsnprintf(nullptr, 0, format, arguments) + 1];
    va_end(arguments);

    va_start(arguments, format);
    vsprintf(result_chars, format, arguments);
    va_end(arguments);

    result.output = result_chars;
    delete[] result_chars;
}
