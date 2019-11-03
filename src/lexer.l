%option noyywrap nodefault

%{
#include <parser.h>
%}

%%

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
