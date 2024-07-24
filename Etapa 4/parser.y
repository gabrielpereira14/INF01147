

%{
    //Gabriel Antônio Pereira - 00324449
    #include <stdlib.h>
    #include <stdio.h>
    #include "semantic.h"
    #include "lex.yy.h"
    #include "hash.h"
    #include "ast.h"
    
    extern void check_and_set_declarations(AST *node);
    extern char* outputFileName;
%}

%union
{
    HashNode *symbol;
    AST *ast;
}

%token<symbol> KW_CHAR           
%token<symbol> KW_INT            
%token<symbol> KW_FLOAT          
%token<symbol> KW_BOOL           
%token KW_IF             
%token KW_ELSE           
%token KW_WHILE          
%token KW_READ           
%token KW_PRINT          
%token KW_RETURN         
%token OPERATOR_LE       
%token OPERATOR_GE       
%token OPERATOR_EQ       
%token OPERATOR_DIF      
%token<symbol> TK_IDENTIFIER     
%token<symbol> LIT_INT           
%token<symbol> LIT_CHAR          
%token<symbol> LIT_REAL          
%token<symbol> LIT_FALSE         
%token<symbol> LIT_TRUE          
%token<symbol> LIT_STRING                
%token TOKEN_ERROR

%type<symbol> lit
%type<ast> type
%type<ast> litl
%type<ast> expr
%type<ast> flowcc
%type<ast> cmd
%type<ast> cmdl
%type<ast> block
%type<ast> param
%type<ast> paraml
%type<ast> paramr
%type<ast> attr
%type<ast> argl
%type<ast> vec_init
%type<ast> argr
%type<ast> dec
%type<ast> decl
%type<ast> programa

%left '|' 
%left '&' 
%left '<' '>' OPERATOR_DIF OPERATOR_EQ OPERATOR_GE OPERATOR_LE '~'
%left '+' '-'
%left '*' '/'

%nonassoc LOWER_THAN_ELSE
%nonassoc KW_ELSE

%%
programa : decl                                             {   
                                                                
                                                                //printASTToFile($1, outputFileName);
                                                                checkAndSetDeclarations($1, 0);
                                                                checkUndeclared();
                                                                setAndCheckOperandsType($1);
                                                                checkVectorAndFunctionUse($1);
                                                                //printAST($1,0);
                                                            }
    ;


lit : LIT_INT           
    | LIT_CHAR          
    | LIT_REAL          
    | LIT_FALSE         
    | LIT_TRUE          
    ;

decl : dec decl                                             { $$ = astCreate(AST_DEC, 0, $1, $2, 0, 0); }
    | dec                                                   { $$ = astCreate(AST_DEC, 0, $1, 0, 0, 0); }
    ;

type: KW_CHAR                                               { $$ = astCreate(AST_CHAR,0, 0, 0, 0, 0); }                         
    | KW_INT                                                { $$ = astCreate(AST_INT, 0, 0, 0, 0, 0); } 
    | KW_BOOL                                               { $$ = astCreate(AST_BOOL,0, 0, 0, 0, 0); } 
    | KW_FLOAT                                              { $$ = astCreate(AST_FLOAT,0, 0,  0, 0, 0); } 
    ;

dec : type TK_IDENTIFIER ':' lit ';'                        { $$ = astCreate(AST_VARDEC, $2, $1, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0), 0, 0 ); }
    | type TK_IDENTIFIER '[' LIT_INT ']' vec_init ';'       { $$ = astCreate(AST_VECDEC, $2, $1, astCreate(AST_SYMBOL, $4, 0, 0, 0, 0), $6, 0 ); }
    | type TK_IDENTIFIER '('paraml')' block                 { $$ = astCreate(AST_FUNDEC, $2, $1, $4, $6, 0); }
    ;

vec_init:  ':' litl                                         { $$ = $2; }
    |                                                       { $$ = 0; }
    ;

litl: lit litl                                              { $$ = astCreate(AST_SYMBOL, $1, $2, 0, 0, 0); }
    | lit                                                   { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
    ;


paraml : param paramr                                       { $$ = astCreate(AST_PARAM, 0, $1, $2, 0, 0); }
    |                                                       { $$ = 0; }
    ;
paramr : ',' param paramr                                   { $$ = astCreate(AST_PARAM, 0, $2, $3, 0, 0); }
    |                                                       { $$ = 0; }
    ;
param : type TK_IDENTIFIER                                 { $$ = astCreate(AST_PARAM, $2, $1, 0, 0, 0); }
    ;

block : '{'cmdl '}'                                         { $$ = astCreate(AST_BLOCK, 0, $2, 0, 0, 0); }

cmdl :  cmd cmdl                                            { $$ = astCreate(AST_LCMD, 0, $1, $2, 0, 0); }
    |                                                       { $$ = 0; }
    ;

cmd: block                                                  { $$ = $1; }
    | attr ';'                                              { $$ = $1; }
    | flowcc                                                { $$ = $1; }
    | KW_READ type TK_IDENTIFIER ';'                        { $$ = astCreate(AST_READ, $3, $2, 0, 0, 0); }
    | KW_PRINT type expr ';'                                { $$ = astCreate(AST_PRINTV, 0, $2, $3, 0, 0); }
    | KW_PRINT LIT_STRING ';'                               { $$ = astCreate(AST_PRINT, $2, 0, 0, 0, 0); }
    | KW_RETURN expr';'                                     { $$ = astCreate(AST_RET, 0, $2, 0, 0, 0); }
    | ';'                                                   { $$ = 0; }
    ;

attr: TK_IDENTIFIER '=' expr                                { $$ = astCreate(AST_ATT, $1, $3, 0, 0, 0); }
    | TK_IDENTIFIER '[' expr ']' '=' expr                   { $$ = astCreate(AST_VECATT, $1, $3, $6, 0, 0); }
    ;


flowcc: KW_IF '(' expr ')' cmd KW_ELSE cmd                  { $$ = astCreate(AST_IFELSE, 0, $3, $5, $7, 0); }
    | KW_IF '(' expr ')' cmd %prec LOWER_THAN_ELSE ';'      { $$ = astCreate(AST_IF, 0, $3, $5, 0, 0); }
    | KW_WHILE '(' expr ')' cmd                             { $$ = astCreate(AST_WHILE, 0, $3, $5, 0, 0); }
    ;
    
expr: expr '+' expr                                         { $$ = astCreate(AST_ADD, 0, $1, $3, 0, 0); }
    | expr '-' expr                                         { $$ = astCreate(AST_MINUS, 0, $1, $3, 0, 0); }
    | expr '*' expr                                         { $$ = astCreate(AST_TIMES, 0, $1, $3, 0, 0); }
    | expr '/' expr                                         { $$ = astCreate(AST_DIV, 0, $1, $3, 0, 0); }
    | expr '<' expr                                         { $$ = astCreate(AST_LT, 0, $1, $3, 0, 0); }
    | expr '>' expr                                         { $$ = astCreate(AST_GT, 0, $1, $3, 0, 0); }
    | expr OPERATOR_DIF expr                                { $$ = astCreate(AST_DIF, 0, $1, $3, 0, 0); }
    | expr OPERATOR_EQ expr                                 { $$ = astCreate(AST_EQ, 0, $1, $3, 0, 0); }
    | expr OPERATOR_GE expr                                 { $$ = astCreate(AST_GE, 0, $1, $3, 0, 0); }
    | expr OPERATOR_LE expr                                 { $$ = astCreate(AST_LE, 0, $1, $3, 0, 0); }
    | expr '&' expr                                         { $$ = astCreate(AST_AND, 0, $1, $3, 0, 0); }
    | expr '|' expr                                         { $$ = astCreate(AST_OR, 0, $1, $3, 0, 0); }
    | '~' expr                                              { $$ = astCreate(AST_NOT, 0, $2, 0, 0, 0); }
    | '(' expr ')'                                          { $$ = astCreate(AST_PAREN, 0, $2, 0, 0, 0); }
    | TK_IDENTIFIER'(' argl ')'                             { $$ = astCreate(AST_FUNCALL, $1, $3, 0, 0, 0); }
    | TK_IDENTIFIER                                         { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
    | TK_IDENTIFIER '[' expr ']'                            { $$ = astCreate(AST_VECACC, $1, $3, 0, 0, 0); }
    | lit                                                   { $$ = astCreate(AST_SYMBOL, $1, 0, 0, 0, 0); }
    ;

argl: expr argr                                             { $$ = astCreate(AST_ARG, 0, $1, $2, 0, 0); }
    |                                                       { $$ = 0; }
    ;
argr: ',' expr argr                                         { $$ = astCreate(AST_ARG, 0, $2, $3, 0, 0); }
    |                                                       { $$ = 0; }
    ;                             

%%


int yyerror(){
    fprintf(stderr,"Syntax error on line %d.\n", getLineNumber());
    exit(3);
}
