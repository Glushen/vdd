%option noyywrap nodefault

%{
#include <parser.h>
%}

%%

void      { return VOID; }
char      { return CHAR; }
long      { return LONG; }
short     { return SHORT; }
int       { return INT; }
float     { return FLOAT; }
double    { return DOUBLE; }
signed    { return SIGNED; }
unsigned  { return UNSIGNED; }

template  { return TEMPLATE; }
\<        { return OPENING_ANGLE_BRACKET; }
\>        { return CLOSING_ANGLE_BRACKET; }
typename  { return TYPENAME; }
,         { return COMMA; }
::        { return DOUBLE_COLON; }
;         { return SEMICOLON; }

\*        { return ASTERISK; }
\[        { return OPENING_SQUARE_BRACKET; }
\]        { return CLOSING_SQUARE_BRACKET; }
\(        { return OPENING_ROUND_BRACKET; }
\)        { return CLOSING_ROUND_BRACKET; }
[0-9]+    { yylval.integer = new std::string(yytext); return INTEGER; }

[a-zA-Z_][a-zA-Z_0-9]*  { yylval.name = new std::string(yytext); return NAME; }

[\r\n ]  /* ignore spaces */
<<EOF>>  { return END_OF_FILE; }
.        { return yytext[0]; }

%%

void yy_set_input_string(const char* in) {
    yy_scan_string(in);
}

void yy_clear_buffer(void) {
    yy_delete_buffer(YY_CURRENT_BUFFER);
}
