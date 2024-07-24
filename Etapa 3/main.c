//Gabriel Antônio Pereira 00324449


#include <stdlib.h>
#include <stdio.h>
#include "lex.yy.h"
#include "hash.h"
#include "ast.h"
#include "y.tab.h"

extern int yyparse();

char* outputFileName;

int main(int argc, char **argv)
{
    if( argc == 3){
        yyin = fopen(argv[1],"r");
        outputFileName = argv[2];
    }else{
        fprintf(stderr, "Not enough arguments");
        return 1;
    }
    //int tok;
    yyparse ();
    
    //printf("File has %d lines\n", lineNumber);
    fprintf(stderr,"Finished\n");
    //hashPrint();
    exit(0);
}
