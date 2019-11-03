%code requires {
    #include "parser_helper.h"
    #include "type.h"

    extern int yylex(void);
    extern void yyerror(const char *s, ...);
}

%union {
    std::string* name;
    std::vector<std::string>* nameList;
    vdd::Type* type;
    unsigned int numericTypeMask;
}

%token TEMP

%token CHAR LONG SHORT INT FLOAT DOUBLE SIGNED UNSIGNED
%token <name> NAME
%token TEMPLATE OPENING_ANGLE_BRACKET CLOSING_ANGLE_BRACKET TYPENAME COMMA

%type <type> type
%type <numericTypeMask> type-numeric signity
%type <nameList> optional-template typename-list


%%


declaration:
    optional-template type


optional-template:
    %empty                                                              { $$ = new std::vector<std::string>(); }
|   TEMPLATE OPENING_ANGLE_BRACKET typename-list CLOSING_ANGLE_BRACKET  { $$ = $3; }

typename-list:
    TYPENAME NAME                      { $$ = new std::vector<std::string>({ ph::unwrap($2) }); }
|   typename-list COMMA TYPENAME NAME  { $$ = $1; $$->push_back(ph::unwrap($4)); }

type:
    type-numeric  { $$ = new vdd::Type($1); }
|   NAME          { $$ = new vdd::Type(ph::unwrap($1)); }

type-numeric:
    CHAR          { $$ = vdd::CHAR; }
|   CHAR signity  { $$ = vdd::CHAR | $2; }
|   signity CHAR  { $$ = vdd::CHAR | $1; }

|   SHORT          { $$ = vdd::SHORT; }
|   SHORT signity  { $$ = vdd::SHORT | $2; }
|   signity SHORT  { $$ = vdd::SHORT | $1; }

|   INT          { $$ = vdd::INT; }
|   INT signity  { $$ = vdd::INT | $2; }
|   signity INT  { $$ = vdd::INT | $1; }

|   LONG          { $$ = vdd::LONG; }
|   LONG signity  { $$ = vdd::LONG | $2; }
|   signity LONG  { $$ = vdd::LONG | $1; }

|   INT LONG          { $$ = vdd::LONG; }
|   INT LONG signity  { $$ = vdd::LONG | $3; }
|   INT signity LONG  { $$ = vdd::LONG | $2; }
|   signity INT LONG  { $$ = vdd::LONG | $1; }

|   LONG INT          { $$ = vdd::LONG; }
|   LONG INT signity  { $$ = vdd::LONG | $3; }
|   LONG signity INT  { $$ = vdd::LONG | $2; }
|   signity LONG INT  { $$ = vdd::LONG | $1; }

|   INT SHORT          { $$ = vdd::SHORT; }
|   INT SHORT signity  { $$ = vdd::SHORT | $3; }
|   INT signity SHORT  { $$ = vdd::SHORT | $2; }
|   signity INT SHORT  { $$ = vdd::SHORT | $1; }

|   SHORT INT          { $$ = vdd::SHORT; }
|   SHORT INT signity  { $$ = vdd::SHORT | $3; }
|   SHORT signity INT  { $$ = vdd::SHORT | $2; }
|   signity SHORT INT  { $$ = vdd::SHORT | $1; }

|   INT LONG LONG          { $$ = vdd::LONG_LONG; }
|   INT LONG LONG signity  { $$ = vdd::LONG_LONG | $4; }
|   INT LONG signity LONG  { $$ = vdd::LONG_LONG | $3; }
|   INT signity LONG LONG  { $$ = vdd::LONG_LONG | $2; }
|   signity INT LONG LONG  { $$ = vdd::LONG_LONG | $1; }

|   LONG INT LONG          { $$ = vdd::LONG_LONG; }
|   LONG INT LONG signity  { $$ = vdd::LONG_LONG | $4; }
|   LONG INT signity LONG  { $$ = vdd::LONG_LONG | $3; }
|   LONG signity INT LONG  { $$ = vdd::LONG_LONG | $2; }
|   signity LONG INT LONG  { $$ = vdd::LONG_LONG | $1; }

|   LONG LONG INT          { $$ = vdd::LONG_LONG; }
|   LONG LONG INT signity  { $$ = vdd::LONG_LONG | $4; }
|   LONG LONG signity INT  { $$ = vdd::LONG_LONG | $3; }
|   LONG signity LONG INT  { $$ = vdd::LONG_LONG | $2; }
|   signity LONG LONG INT  { $$ = vdd::LONG_LONG | $1; }

|   LONG LONG          { $$ = vdd::LONG_LONG; }
|   LONG LONG signity  { $$ = vdd::LONG_LONG | $3; }
|   LONG signity LONG  { $$ = vdd::LONG_LONG | $2; }
|   signity LONG LONG  { $$ = vdd::LONG_LONG | $1; }

|   FLOAT        { $$ = vdd::FLOAT; }
|   DOUBLE       { $$ = vdd::DOUBLE; }
|   LONG DOUBLE  { $$ = vdd::LONG | vdd::DOUBLE; }
|   DOUBLE LONG  { $$ = vdd::LONG | vdd::DOUBLE; }

signity:
    SIGNED    { $$ = vdd::SIGNED; }
|   UNSIGNED  { $$ = vdd::UNSIGNED; }
