#include <stdlib.h>
#include <stdio.h>
#include "tokens.h"
#include "lex.yy.h"
#include "hash.h"

int main(int argc, char **argv)
{
    if( argc == 2){
        yyin = fopen(argv[1],"r");
    }
    int tok;
    hashInit();
    while(running){
        tok = yylex();
        if(running == 0){
            break;
        }
        switch(tok){
            case KW_INT: printf("KW_INT "); break;
            case KW_CHAR: printf("KW_CHAR "); break;
            case KW_FLOAT: printf("KW_FLOAT "); break;
            case KW_BOOL: printf("KW_BOOL "); break;
            case KW_IF: printf("KW_IF "); break;
            case KW_ELSE: printf("KW_ELSE "); break;
            case KW_WHILE: printf("KW_WHILE "); break;
            case KW_READ: printf("KW_READ "); break;
            case KW_PRINT: printf("KW_PRINT "); break;
            case KW_RETURN: printf("KW_RETURN "); break;
            case OPERATOR_LE: printf("OPERATOR_LE "); break;
            case OPERATOR_GE: printf("OPERATOR_GE "); break;
            case OPERATOR_EQ: printf("OPERATOR_EQ "); break;
            case OPERATOR_DIF: printf("OPERATOR_DIF "); break;
            case TK_IDENTIFIER: printf("TK_IDENTIFIER "); break;
            case LIT_INT: printf("LIT_INT "); break;
            case LIT_CHAR: printf("LIT_CHAR "); break;
            case LIT_REAL: printf("LIT_REAL "); break;
            case LIT_FALSE: printf("LIT_FALSE "); break;
            case LIT_TRUE: printf("LIT_TRUE "); break;
            case LIT_STRING: printf("LIT_STRING "); break;
            case TOKEN_ERROR: printf("TOKEN_ERROR "); break;
            default:  printf("%c ",tok); break;
        }
    }
    printf("File has %d lines\n", lineNumber);
    hashPrint();
    exit(0);
}
