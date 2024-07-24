//Gabriel Antônio Pereira 00324449


#include <stdlib.h>
#include <stdio.h>
#include "lex.yy.h"
#include "hash.h"
#include "y.tab.h"

extern int yyparse();

int main(int argc, char **argv)
{
    if( argc == 2){
        yyin = fopen(argv[1],"r");
    }
    int tok;
    yyparse ();
    //printf("File has %d lines\n", lineNumber);
    fprintf(stderr,"Finished\n");
    hashPrint();
    exit(0);
}
