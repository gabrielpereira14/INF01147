
%{
//Gabriel Antônio Pereira - 00324449
#include <stdlib.h>
#include <stdio.h>
#include "lex.yy.h"
%}

%token KW_CHAR           
%token KW_INT            
%token KW_FLOAT          
%token KW_BOOL           
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
%token TK_IDENTIFIER     
%token LIT_INT           
%token LIT_CHAR          
%token LIT_REAL          
%token LIT_FALSE         
%token LIT_TRUE          
%token LIT_STRING        
%token TOKEN_ERROR     

%left '<' '>' OPERATOR_DIF OPERATOR_EQ OPERATOR_GE OPERATOR_LE '&' '|' '~'
%left '+' '-'
%left '*' '/'

%nonassoc LOWER_THAN_ELSE
%nonassoc KW_ELSE

%%
programa : decl
    ;


lit :  LIT_INT           
    | LIT_CHAR          
    | LIT_REAL          
    | LIT_FALSE         
    | LIT_TRUE          
    ;

decl : dec decl
    | dec
    ;

type: KW_CHAR 
    | KW_INT
    | KW_BOOL
    | KW_FLOAT
    ;

dec : type TK_IDENTIFIER ':' lit ';'
    | type TK_IDENTIFIER '[' LIT_INT ']' vec_init ';'
    | type TK_IDENTIFIER '('paraml')' block
    ;

vec_init: ':' litl
    | 
    ;

litl: lit litl
    | lit
    ;


paraml : param paramr
    |
    ;
paramr : ',' param paramr
    | 
    ;
param : type TK_IDENTIFIER;

block : '{'cmdl '}'

cmdl :  cmd cmdl
    | 
    ;

cmd: block
    | attr ';'
    | flowcc
    | KW_READ type TK_IDENTIFIER ';'
    | KW_PRINT type expr ';'
    | KW_PRINT LIT_STRING ';'
    | KW_RETURN expr';'
    | ';'
    ;

attr: TK_IDENTIFIER '=' expr  
    | TK_IDENTIFIER'[' expr ']' '=' expr
    ;


flowcc: KW_IF '(' expr ')' cmd KW_ELSE cmd 
    | KW_IF '(' expr ')' cmd %prec LOWER_THAN_ELSE ;
    | KW_WHILE '(' expr ')' cmd
    ;
    
expr: expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr '<' expr
    | expr '>' expr
    | expr OPERATOR_DIF expr
    | expr OPERATOR_EQ expr
    | expr OPERATOR_GE expr
    | expr OPERATOR_LE expr
    | expr '&' expr
    | expr '|' expr
    | expr '~' expr
    | '(' expr ')'
    | TK_IDENTIFIER'(' argl ')'
    | TK_IDENTIFIER
    | TK_IDENTIFIER '[' expr ']'
    | lit
    ;

argl: expr argr
    | 
    ;
argr: ',' expr argr
    | ;

%%


//extern int yylex();

int yyerror(){
    fprintf(stderr,"Syntax error on line %d.\n", getLineNumber());
    exit(3);
}
