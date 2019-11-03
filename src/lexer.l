%option noyywrap nodefault

%{
#include <parser.h>
%}

%%

char      { return CHAR; }
long      { return LONG; }
short     { return SHORT; }
int       { return INT; }
float     { return FLOAT; }
double    { return DOUBLE; }
signed    { return SIGNED; }
unsigned  { return UNSIGNED; }

[a-zA-Z_][a-zA-Z_0-9]*  { yylval.name = new std::string(yytext); return NAME; }

.        { return TEMP; }
\n       { return TEMP; }
<<EOF>>  { return TEMP; }

%%

void yy_set_input_string(const char* in) {
    yy_scan_string(in);
}

void yy_clear_buffer(void) {
    yy_delete_buffer(YY_CURRENT_BUFFER);
}
