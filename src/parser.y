%glr-parser
%expect 7

%code requires {
    #include "parser_helper.h"
    #include "declaration.h"

    extern int yylex(void);
    extern void yyerror(const char *s, ...);
    extern void yy_accept_ast(vdd::Declaration);
}

%union {
    std::string* name;
    std::unordered_set<std::string>* templateTypenames;
    vdd::Type* type;
    unsigned int numericTypeMask;
    std::string* integer;
    vdd::Declaration* declaration;
    vdd::Declarator* declarator;
    std::vector<vdd::Declaration>* argumentList;
}

%token CHAR LONG SHORT INT FLOAT DOUBLE SIGNED UNSIGNED
%token <name> NAME
%token TEMPLATE OPENING_ANGLE_BRACKET CLOSING_ANGLE_BRACKET TYPENAME COMMA DOUBLE_COLON
%token ASTERISK OPENING_SQUARE_BRACKET CLOSING_SQUARE_BRACKET OPENING_ROUND_BRACKET CLOSING_ROUND_BRACKET
%token <integer> INTEGER
%token END_OF_FILE

%type <type> type class-type local-class-type
%type <numericTypeMask> type-numeric signity
%type <templateTypenames> optional-template typename-list
%type <declarator> declarator noptr-declarator ptr-declarator function-declarator
%type <declarator> argument-declarator noptr-argument-declarator ptr-argument-declarator function-argument-declarator
%type <argumentList> argument-list not-empty-argument-list


%nonassoc LOWER_THAN_OPENING_BRACKET
%nonassoc OPENING_SQUARE_BRACKET
%nonassoc OPENING_ROUND_BRACKET
%nonassoc HIGHER_THAN_OPENING_BRACKET

%nonassoc LOWER_THAN_DOUBLE_COLON
%nonassoc DOUBLE_COLON

%%


declaration:
    optional-template type declarator END_OF_FILE  { yy_accept_ast(vdd::Declaration(ph::unwrap($1), ph::unwrap($2), std::unique_ptr<vdd::Declarator>($3))); YYACCEPT; }


declarator:
    noptr-declarator %prec LOWER_THAN_OPENING_BRACKET  { $$ = $1; }
|   ptr-declarator                                     { $$ = $1; }
|   function-declarator                                { $$ = $1; }

noptr-declarator:
    NAME                                                                    { $$ = new vdd::NameDeclarator(ph::unwrap($1)); }
|   class-type DOUBLE_COLON ASTERISK declarator                             { $$ = new vdd::MemberPointerDeclarator(ph::unwrap($1), std::unique_ptr<vdd::Declarator>($4)); }
|   OPENING_ROUND_BRACKET noptr-declarator CLOSING_ROUND_BRACKET            { $$ = $2; }
|   OPENING_ROUND_BRACKET ptr-declarator CLOSING_ROUND_BRACKET              { $$ = $2; }
|   noptr-declarator OPENING_SQUARE_BRACKET CLOSING_SQUARE_BRACKET          { $$ = new vdd::ArrayDeclarator(std::unique_ptr<vdd::Declarator>($1)); }
|   noptr-declarator OPENING_SQUARE_BRACKET INTEGER CLOSING_SQUARE_BRACKET  { $$ = new vdd::ArrayDeclarator(std::unique_ptr<vdd::Declarator>($1), ph::unwrap($3)); }

ptr-declarator:
    ASTERISK declarator  { $$ = new vdd::PointerDeclarator(std::unique_ptr<vdd::Declarator>($2)); }

function-declarator:
    noptr-declarator OPENING_ROUND_BRACKET argument-list CLOSING_ROUND_BRACKET  { $$ = new vdd::FunctionDeclarator(std::unique_ptr<vdd::Declarator>($1), ph::unwrap($3)); }
|   OPENING_ROUND_BRACKET function-declarator CLOSING_ROUND_BRACKET             { $$ = $2; }

argument-declarator:
    noptr-argument-declarator     { $$ = $1; }
|   ptr-argument-declarator       { $$ = $1; }
|   function-argument-declarator  { $$ = $1; }

noptr-argument-declarator:
    %empty                                                                               { $$ = new vdd::NameDeclarator(""); }
|   NAME                                                                                 { $$ = new vdd::NameDeclarator(ph::unwrap($1)); }
|   class-type DOUBLE_COLON ASTERISK argument-declarator                                 { $$ = new vdd::MemberPointerDeclarator(ph::unwrap($1), std::unique_ptr<vdd::Declarator>($4)); }
|   OPENING_ROUND_BRACKET noptr-argument-declarator CLOSING_ROUND_BRACKET                { $$ = $2; }
|   OPENING_ROUND_BRACKET ptr-argument-declarator CLOSING_ROUND_BRACKET                  { $$ = $2; }
|   noptr-argument-declarator OPENING_SQUARE_BRACKET CLOSING_SQUARE_BRACKET              { $$ = new vdd::ArrayDeclarator(std::unique_ptr<vdd::Declarator>($1)); }
|   noptr-argument-declarator OPENING_SQUARE_BRACKET INTEGER CLOSING_SQUARE_BRACKET      { $$ = new vdd::ArrayDeclarator(std::unique_ptr<vdd::Declarator>($1), ph::unwrap($3)); }

ptr-argument-declarator:
    ASTERISK argument-declarator  { $$ = new vdd::PointerDeclarator(std::unique_ptr<vdd::Declarator>($2)); }

function-argument-declarator:
    noptr-argument-declarator OPENING_ROUND_BRACKET argument-list CLOSING_ROUND_BRACKET  { $$ = new vdd::FunctionDeclarator(std::unique_ptr<vdd::Declarator>($1), ph::unwrap($3)); }
|   OPENING_ROUND_BRACKET function-argument-declarator CLOSING_ROUND_BRACKET             { $$ = $2; }

argument-list:
    %empty                   { $$ = new std::vector<vdd::Declaration>(); }
|   not-empty-argument-list  { $$ = $1; }

not-empty-argument-list:
    type argument-declarator                                { $$ = new std::vector<vdd::Declaration>(); $$->emplace_back(std::unordered_set<std::string>(), ph::unwrap($1), std::unique_ptr<vdd::Declarator>($2)); }
|   not-empty-argument-list COMMA type argument-declarator  { $$ = $1; $$->emplace_back(std::unordered_set<std::string>(), ph::unwrap($3), std::unique_ptr<vdd::Declarator>($4)); }


optional-template:
    %empty                                                              { $$ = new std::unordered_set<std::string>(); }
|   TEMPLATE OPENING_ANGLE_BRACKET typename-list CLOSING_ANGLE_BRACKET  { $$ = $3; }

typename-list:
    TYPENAME NAME                      { $$ = new std::unordered_set<std::string>({ ph::unwrap($2) }); }
|   typename-list COMMA TYPENAME NAME  { $$ = $1; $$->insert(ph::unwrap($4)); }

type:
    type-numeric             { $$ = new vdd::Type($1); }
|   class-type               { $$ = $1; }

class-type:
    local-class-type %prec LOWER_THAN_DOUBLE_COLON  { $$ = $1; }
|   DOUBLE_COLON local-class-type                   { $$ = $2; }

local-class-type:
    NAME                                { $$ = new vdd::Type(ph::unwrap($1)); }
|   local-class-type DOUBLE_COLON NAME  { $$ = $1; $$->anotherTypeName += "::" + ph::unwrap($3); }

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
