#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AST *astCreate(int type, HashNode *symbol, AST* s0, AST* s1, AST* s2, AST* s3){
    AST *newNode = malloc(sizeof(AST));
    newNode->type = type;
    newNode->symbol = symbol;
    newNode->son[0] = s0;
    newNode->son[1] = s1;
    newNode->son[2] = s2;
    newNode->son[3] = s3;
    return newNode;
}

void printAST(AST *node, int level){
    int i = 0;
    if (node == 0) return;


    for(i = 0; i < level; i++){
        fprintf(stderr, "  ");
    }

    fprintf(stderr, "ast(");
    switch (node->type)
    {
    case AST_SYMBOL:  fprintf(stderr, "AST_SYMBOL"); break;
    case AST_ADD: fprintf(stderr, "AST_ADD"); break;
    case AST_MINUS: fprintf(stderr, "AST_MINUS"); break;
    case AST_TIMES: fprintf(stderr, "AST_TIMES"); break;
    case AST_DIV: fprintf(stderr, "AST_DIV"); break;
    case AST_GT: fprintf(stderr, "AST_GT"); break;
    case AST_LT: fprintf(stderr, "AST_LT"); break;
    case AST_DIF: fprintf(stderr, "AST_DIF"); break;
    case AST_EQ: fprintf(stderr, "AST_EQ"); break;
    case AST_GE: fprintf(stderr, "AST_GE"); break;
    case AST_LE: fprintf(stderr, "AST_LE"); break;
    case AST_AND: fprintf(stderr, "AST_AND"); break;
    case AST_OR: fprintf(stderr, "AST_OR"); break;
    case AST_NOT: fprintf(stderr, "AST_NOT"); break;
    case AST_LCMD: fprintf(stderr, "AST_LCMD"); break;
    case AST_PAREN: fprintf(stderr, "AST_PAREN"); break;
    case AST_WHILE: fprintf(stderr, "AST_WHILE"); break;
    case AST_IF: fprintf(stderr, "AST_IF"); break;
    case AST_IFELSE: fprintf(stderr, "AST_IFELSE"); break;
    case AST_ATT: fprintf(stderr, "AST_ATT"); break;
    case AST_VECATT: fprintf(stderr, "AST_VECATT"); break;
    case AST_RET: fprintf(stderr, "AST_RET"); break;
    case AST_PRINT: fprintf(stderr, "AST_PRINT"); break;
    case AST_PRINTV: fprintf(stderr, "AST_PRINTV"); break;
    case AST_READ: fprintf(stderr, "AST_READ"); break;
    case AST_BLOCK: fprintf(stderr, "AST_BLOCK"); break;
    case AST_PARAM: fprintf(stderr, "AST_PARAM"); break;
    case AST_LIT: fprintf(stderr, "AST_LIT"); break;
    case AST_TYPE: fprintf(stderr, "AST_TYPE"); break;
    case AST_ARG: fprintf(stderr, "AST_ARG"); break;
    case AST_VARDEC: fprintf(stderr, "AST_VARDEC"); break;
    case AST_VECDEC: fprintf(stderr, "AST_VECDEC"); break;
    case AST_VECINIT: fprintf(stderr, "AST_VECINIT"); break;
    case AST_FUNDEC: fprintf(stderr, "AST_FUNDEC"); break;
    case AST_DEC: fprintf(stderr, "AST_DEC"); break;
    case AST_CHAR: fprintf(stderr, "AST_CHAR"); break;
    case AST_FLOAT: fprintf(stderr, "AST_FLOAT"); break;
    case AST_BOOL: fprintf(stderr, "AST_BOOL"); break;
    case AST_INT: fprintf(stderr, "AST_INT"); break;
    case AST_VECACC: fprintf(stderr, "AST_VECACC"); break;
    case AST_FUNCALL: fprintf(stderr, "AST_FUNCALL"); break;
    
    default: fprintf(stderr, "AST_UNKOWN"); break;
    }
    if (node->symbol != 0) {
        fprintf(stderr, ",%s)\n", node->symbol->identifier);
    }else{
        fprintf(stderr, ",0)\n");
    }

    for (i = 0; i < MAX_SONS; i++){
        if (node->son[i] != 0 && node->son[i]->type != node->type){
            printAST(node->son[i], level + 1);
        }
        else{
            printAST(node->son[i], level );
        }
    }

    
}

void printASTToFile(AST *node, const char* filename){
    FILE *f = fopen(filename, "w");
    if (!f){
        fprintf(stderr, "Could not create output file (out.txt).");
        return;
    }
    printNodeToFile(node,f);
}


void printNodeToFile(AST *node, FILE *f){
    if (node == 0) return;

    char buffer[256];
    switch (node->type)
    {
    case AST_SYMBOL:  
        fwrite( node->symbol->identifier, sizeof(char), strlen(node->symbol->identifier), f); 
        if (node->son[0] != 0){
            fwrite(" ", sizeof(char), strlen(" "), f); 
            printNodeToFile(node->son[0], f);
        }
        break;
    case AST_ADD: 
        printNodeToFile(node->son[0], f);
        fwrite("+ ", sizeof(char), strlen("+ "), f); 
        printNodeToFile(node->son[1], f);
        break;
    case AST_MINUS: 
        printNodeToFile(node->son[0], f);
        fwrite("- ", sizeof(char), strlen("- "), f);
        printNodeToFile(node->son[1], f);
        break;
    case AST_TIMES: 
        printNodeToFile(node->son[0], f);
        fwrite("* ", sizeof(char), strlen("* "), f);
        printNodeToFile(node->son[1], f);
        break;
    case AST_DIV: 
        printNodeToFile(node->son[0], f);
        fwrite("/ ", sizeof(char), strlen("/ "), f);
        printNodeToFile(node->son[1], f);
        break;
    case AST_GT: 
        printNodeToFile(node->son[0], f);
        fwrite("> ", sizeof(char), strlen("> "), f);
        printNodeToFile(node->son[1], f);
        break;
    case AST_LT: 
        printNodeToFile(node->son[0], f);
        fwrite("< ", sizeof(char), strlen("< "), f);
        printNodeToFile(node->son[1], f);
        break;
    case AST_DIF: 
        printNodeToFile(node->son[0], f);
        fwrite("!= ", sizeof(char), strlen("!= "), f);
        printNodeToFile(node->son[1], f);
        break;
    case AST_EQ: 
        printNodeToFile(node->son[0], f);
        fwrite("== ", sizeof(char), strlen("== "), f);
        printNodeToFile(node->son[1], f);
        break;
    case AST_GE: 
        printNodeToFile(node->son[0], f);
        fwrite(">= ", sizeof(char), strlen(">= "), f);
        printNodeToFile(node->son[1], f);
        break;
    case AST_LE: 
        printNodeToFile(node->son[0], f);
        fwrite("<= ", sizeof(char), strlen("<= "), f);
        printNodeToFile(node->son[1], f);
        break;
    case AST_AND: 
        printNodeToFile(node->son[0], f);
        fwrite("& ", sizeof(char), strlen("& "), f);
        printNodeToFile(node->son[1], f);
        break;
    case AST_OR: 
        printNodeToFile(node->son[0], f);
        fwrite("| ", sizeof(char), strlen("| "), f);
        printNodeToFile(node->son[1], f);
        break;
    case AST_NOT: 
        fwrite("~", sizeof(char), strlen("~"), f); 
        printNodeToFile(node->son[0], f);
        break;
    case AST_LCMD:  
        printNodeToFile(node->son[0], f);
        fwrite( "\n", sizeof(char), strlen("\n"), f);
        printNodeToFile(node->son[1], f);
        break;
    case AST_PAREN: printNodeToFile(node->son[0], f); break;
    case AST_WHILE: 
        fwrite("while (", sizeof(char), strlen("while ("), f); 
        printNodeToFile(node->son[0], f);
        fwrite(") ", sizeof(char), strlen(") "), f); 
        printNodeToFile(node->son[1], f);
        break;
    case AST_IF: 
        fwrite("if (", sizeof(char), strlen("if ("), f); 
        printNodeToFile(node->son[0], f);
        fwrite(") ", sizeof(char), strlen(") "), f); 
        printNodeToFile(node->son[1], f);
        fwrite( ";", sizeof(char), strlen(";"), f);
        break;
    case AST_IFELSE: 
        fwrite("if (", sizeof(char), strlen("if ("), f); 
        printNodeToFile(node->son[0], f);
        fwrite(") ", sizeof(char), strlen(") "), f); 
        printNodeToFile(node->son[1], f);
        fwrite("else ", sizeof(char), strlen("else "), f);
        printNodeToFile(node->son[2], f);
        break;
    case AST_ATT: 
        snprintf(buffer, sizeof(buffer), "%s = ", node->symbol->identifier);
        fwrite( buffer, sizeof(char), strlen(buffer), f);
        printNodeToFile(node->son[0], f);
        fwrite( ";", sizeof(char), strlen(";"), f);
        break;
    case AST_VECATT: 
        snprintf(buffer, sizeof(buffer), "%s[", node->symbol->identifier);
        fwrite( buffer, sizeof(char), strlen(buffer), f); 
        printNodeToFile(node->son[0], f);
        fwrite("] = ", sizeof(char), strlen("] = "), f);
        printNodeToFile(node->son[1], f);
        fwrite( ";", sizeof(char), strlen(";"), f);
        break;
    case AST_RET: 
        fwrite("return ", sizeof(char), strlen("return "), f); 
        printNodeToFile(node->son[0], f);
        fwrite( ";", sizeof(char), strlen(";"), f);
        break;
    case AST_PRINT: 
        fwrite("print ", sizeof(char), strlen("print "), f); 
        fwrite( node->symbol->identifier, sizeof(char), strlen(node->symbol->identifier), f); 
        fwrite( ";", sizeof(char), strlen(";"), f);
        break;
    case AST_PRINTV: 
        fwrite("print ", sizeof(char), strlen("print "), f);
        printNodeToFile(node->son[0], f);
        printNodeToFile(node->son[1], f);
        fwrite( ";", sizeof(char), strlen(";"), f);
        break;
    case AST_READ: 
        fwrite("read ", sizeof(char), strlen("read "), f); 
        printNodeToFile(node->son[0], f);
        fwrite( node->symbol->identifier, sizeof(char), strlen(node->symbol->identifier), f); 
        fwrite( ";", sizeof(char), strlen(";"), f);
        break;
    case AST_BLOCK: 
        fwrite("{", sizeof(char), strlen("{"), f); 
        printNodeToFile(node->son[0], f);
        fwrite("} ", sizeof(char), strlen("}"), f); 
        break;
    case AST_PARAM: 

        printNodeToFile(node->son[0], f);

        if(node->symbol != 0){
            fwrite( node->symbol->identifier, sizeof(char), strlen(node->symbol->identifier), f); 
        }else if(node->son[1] != 0){
            
            fwrite( ", ", sizeof(char), strlen(", "), f); 
            printNodeToFile(node->son[1], f);
        }  
        
        break;
    case AST_ARG: 
        printNodeToFile(node->son[0], f);

        if(node->symbol != 0){
            fwrite( node->symbol->identifier, sizeof(char), strlen(node->symbol->identifier), f); 
        }else if(node->son[1] != 0){
            
            fwrite( ", ", sizeof(char), strlen(", "), f); 
            printNodeToFile(node->son[1], f);
        }  
        break;
    case AST_VARDEC:
        printNodeToFile(node->son[0], f);
        printNodeToFile(node->son[1], f);
        fwrite(": ", sizeof(char), strlen(":"), f);
        printNodeToFile(node->son[2], f);
        fwrite(";\n", sizeof(char), strlen(";\n"), f);

        break;

    case AST_VECDEC: 
        printNodeToFile(node->son[0], f);
        printNodeToFile(node->son[1], f);
        fwrite("[", sizeof(char), strlen("["), f);
        printNodeToFile(node->son[2], f);
        fwrite("]", sizeof(char), strlen("]"), f);
        if(node->son[3] != 0){
            fwrite(": ", sizeof(char), strlen(": "), f);
            printNodeToFile(node->son[3], f);
        }
        fwrite(";\n", sizeof(char), strlen(";\n"), f);
        break;

    case AST_FUNDEC:
        printNodeToFile(node->son[0], f);
        printNodeToFile(node->son[1], f);
        fwrite("(", sizeof(char), strlen(")"), f);
        printNodeToFile(node->son[2], f);
        fwrite(")", sizeof(char), strlen(")"), f);
        printNodeToFile(node->son[3], f);
        break;
    case AST_DEC: 
        printNodeToFile(node->son[0], f);
        printNodeToFile(node->son[1], f);
        break;
    case AST_CHAR: fwrite("char ", sizeof(char), strlen("char "), f); break;
    case AST_FLOAT: fwrite("float ", sizeof(char), strlen("float "), f); break;
    case AST_BOOL: fwrite("bool ", sizeof(char), strlen("bool "), f); break;
    case AST_INT: fwrite("int ", sizeof(char), strlen("int "), f); break;
    case AST_VECACC: 
        snprintf(buffer, sizeof(buffer), "%s[", node->symbol->identifier);
        fwrite( buffer, sizeof(char), strlen(buffer), f); 
        printNodeToFile(node->son[0], f);
        fwrite( "]", sizeof(char), strlen("]"), f);
        break;
    case AST_FUNCALL: 
        snprintf(buffer, sizeof(buffer), "%s(", node->symbol->identifier);
        fwrite( buffer, sizeof(char), strlen(buffer), f); 
        printNodeToFile(node->son[0], f);
        fwrite( ")", sizeof(char), strlen(")"), f); 
        break;
    
    default: fprintf(stderr, "AST_UNKOWN"); break;
    }
}
