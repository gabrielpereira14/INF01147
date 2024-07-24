//Gabriel Antônio Pereira 00324449


#include <stdlib.h>
#include <stdio.h>
#include "lex.yy.h"
#include "hash.h"
#include "ast.h"
#include "y.tab.h"
#include "semantic.h"

extern int yyparse();

char* outputFileName;
int main(int argc, char **argv)
{
    if( argc == 3){
        yyin = fopen(argv[1],"r");
        if (!yyin){
            return 2;
        }
        outputFileName = argv[2];
    }else{
        fprintf(stderr, "Not enough arguments");
        return 1;
    }
    //int tok;
    yyparse ();
    
    //printf("File has %d lines\n", lineNumber);
    
    //hashPrint();
    int semanticErrors = getSemanticErrors();
    if (semanticErrors > 0) exit(4);
    fprintf(stderr,"Finished with no errors\n");


    exit(0);
}
