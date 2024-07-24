//Gabriel Antônio Pereira 00324449

#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

AST *astCreate(int type, HashNode *symbol, AST* s0, AST* s1, AST* s2, AST* s3){
    AST *newNode = malloc(sizeof(AST));
    newNode->type = type;
    newNode->symbol = symbol;
    newNode->datatype = 0;
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

    char astType[32];
    astTypeToString(node,astType);
    fprintf(stderr, "ast(%s",astType);

    if (node->symbol != 0) {
        fprintf(stderr, ",%s", node->symbol->identifier);
    }else{
        fprintf(stderr, ",0");
    }

    fprintf(stderr, ",%d)\n", node->datatype);

    for (i = 0; i < MAX_SONS; i++){
        if (node->son[i] != 0 && node->son[i]->type != AST_DEC){
            printAST(node->son[i], level + 1);
        }
        else{
            printAST(node->son[i], level );
        }
    }

    
}

void astTypeToString(AST *node, char *str){
    if (node == 0){
        strcpy(str, "AST_ERROR");
        return;
    }
    switch (node->type)
    {
    case AST_SYMBOL:  strcpy(str,"AST_SYMBOL"); break;
    case AST_ADD: strcpy(str,"AST_ADD"); break;
    case AST_MINUS: strcpy(str,"AST_MINUS"); break;
    case AST_TIMES: strcpy(str,"AST_TIMES"); break;
    case AST_DIV: strcpy(str,"AST_DIV"); break;
    case AST_GT: strcpy(str,"AST_GT"); break;
    case AST_LT: strcpy(str,"AST_LT"); break;
    case AST_DIF: strcpy(str,"AST_DIF"); break;
    case AST_EQ: strcpy(str,"AST_EQ"); break;
    case AST_GE: strcpy(str,"AST_GE"); break;
    case AST_LE: strcpy(str,"AST_LE"); break;
    case AST_AND: strcpy(str,"AST_AND"); break;
    case AST_OR: strcpy(str,"AST_OR"); break;
    case AST_NOT: strcpy(str,"AST_NOT"); break;
    case AST_LCMD: strcpy(str,"AST_LCMD"); break;
    case AST_PAREN: strcpy(str,"AST_PAREN"); break;
    case AST_WHILE: strcpy(str,"AST_WHILE"); break;
    case AST_IF: strcpy(str,"AST_IF"); break;
    case AST_IFELSE: strcpy(str,"AST_IFELSE"); break;
    case AST_ATT: strcpy(str,"AST_ATT"); break;
    case AST_VECATT: strcpy(str,"AST_VECATT"); break;
    case AST_RET: strcpy(str,"AST_RET"); break;
    case AST_PRINT: strcpy(str,"AST_PRINT"); break;
    case AST_PRINTV: strcpy(str,"AST_PRINTV"); break;
    case AST_READ: strcpy(str,"AST_READ"); break;
    case AST_BLOCK: strcpy(str,"AST_BLOCK"); break;
    case AST_PARAM: strcpy(str,"AST_PARAM"); break;
    case AST_LIT: strcpy(str,"AST_LIT"); break;
    case AST_TYPE: strcpy(str,"AST_TYPE"); break;
    case AST_ARG: strcpy(str,"AST_ARG"); break;
    case AST_VARDEC: strcpy(str,"AST_VARDEC"); break;
    case AST_VECDEC: strcpy(str,"AST_VECDEC"); break;
    case AST_VECINIT: strcpy(str,"AST_VECINIT"); break;
    case AST_FUNDEC: strcpy(str,"AST_FUNDEC"); break;
    case AST_DEC: strcpy(str,"AST_DEC"); break;
    case AST_CHAR: strcpy(str,"AST_CHAR"); break;
    case AST_FLOAT: strcpy(str,"AST_FLOAT"); break;
    case AST_BOOL: strcpy(str,"AST_BOOL"); break;
    case AST_INT: strcpy(str,"AST_INT"); break;
    case AST_VECACC: strcpy(str,"AST_VECACC"); break;
    case AST_FUNCALL: strcpy(str,"AST_FUNCALL"); break;
    default: strcpy(str, "AST_UNKOWN"); break;
    }
}

void astTypeToPrettyString(AST *node, char *str){
    if (node == 0){
        strcpy(str, "ERROR");
        return;
    }
    switch (node->type)
    {
    case AST_SYMBOL:  strcpy(str,"SYMBOL"); break;
    case AST_ADD: strcpy(str,"Add"); break;
    case AST_MINUS: strcpy(str,"Minus"); break;
    case AST_TIMES: strcpy(str,"Times"); break;
    case AST_DIV: strcpy(str,"Div"); break;
    case AST_GT: strcpy(str,"GT"); break;
    case AST_LT: strcpy(str,"LT"); break;
    case AST_DIF: strcpy(str,"DIF"); break;
    case AST_EQ: strcpy(str,"EQ"); break;
    case AST_GE: strcpy(str,"GE"); break;
    case AST_LE: strcpy(str,"LE"); break;
    case AST_AND: strcpy(str,"AND"); break;
    case AST_OR: strcpy(str,"OR"); break;
    case AST_NOT: strcpy(str,"NOT"); break;
    case AST_LCMD: strcpy(str,"LCMD"); break;
    case AST_PAREN: strcpy(str,"PAREN"); break;
    case AST_WHILE: strcpy(str,"WHILE"); break;
    case AST_IF: strcpy(str,"If"); break;
    case AST_IFELSE: strcpy(str,"If else"); break;
    case AST_ATT: strcpy(str,"Attribution"); break;
    case AST_VECATT: strcpy(str,"Vector attribution"); break;
    case AST_RET: strcpy(str,"Return"); break;
    case AST_PRINT: strcpy(str,"Print"); break;
    case AST_PRINTV: strcpy(str,"Print value"); break;
    case AST_READ: strcpy(str,"READ"); break;
    case AST_BLOCK: strcpy(str,"BLOCK"); break;
    case AST_PARAM: strcpy(str,"Parameter"); break;
    case AST_LIT: strcpy(str,"LIT"); break;
    case AST_TYPE: strcpy(str,"Type"); break;
    case AST_ARG: strcpy(str,"Argument"); break;
    case AST_VARDEC: strcpy(str,"variable declaration"); break;
    case AST_VECDEC: strcpy(str,"Vector declaration"); break;
    case AST_VECINIT: strcpy(str,"Vector init"); break;
    case AST_FUNDEC: strcpy(str,"Funtion declaration"); break;
    case AST_DEC: strcpy(str,"DEC"); break;
    case AST_CHAR: strcpy(str,"CHAR"); break;
    case AST_FLOAT: strcpy(str,"FLOAT"); break;
    case AST_BOOL: strcpy(str,"BOOL"); break;
    case AST_INT: strcpy(str,"INT"); break;
    case AST_VECACC: strcpy(str,"Vector access"); break;
    case AST_FUNCALL: strcpy(str,"Funtion call"); break;
    default: strcpy(str, "UNKOWN"); break;
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
    case AST_NOT: fwrite("~ ", sizeof(char), strlen("+ "), f); break;
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
        snprintf(buffer, sizeof(buffer), "%s: ", node->symbol->identifier);
        fwrite( buffer, sizeof(char), strlen(buffer), f); 
        printNodeToFile(node->son[1], f);
        fwrite(";\n", sizeof(char), strlen(";\n"), f);

        break;

    case AST_VECDEC: 
        printNodeToFile(node->son[0], f);
        snprintf(buffer, sizeof(buffer), "%s[", node->symbol->identifier);
        fwrite( buffer, sizeof(char), strlen(buffer), f); 
        printNodeToFile(node->son[1], f);
        fwrite("]", sizeof(char), strlen("]"), f);
        if(node->son[2] != 0){
            fwrite(": ", sizeof(char), strlen(": "), f);
            printNodeToFile(node->son[2], f);
        }
        fwrite(";\n", sizeof(char), strlen(";\n"), f);
        break;

    case AST_FUNDEC:
        printNodeToFile(node->son[0], f);
        snprintf(buffer, sizeof(buffer), "%s(", node->symbol->identifier);
        fwrite( buffer, sizeof(char), strlen(buffer), f); 
        printNodeToFile(node->son[1], f);
        fwrite(")", sizeof(char), strlen(")"), f);
        printNodeToFile(node->son[2], f);
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

int isIntegerOperand(AST *node){
    if (node == 0) return 0;

    if( node->type == AST_ADD ||
        node->type == AST_MINUS ||
        node->type == AST_TIMES ||
        node->type == AST_DIV ||
        (node->type == AST_SYMBOL && (node->symbol->datatype == DATATYPE_INT || node->symbol->datatype == DATATYPE_CHAR)) ||
        (node->type == AST_VECACC && (node->symbol->datatype == DATATYPE_INT || node->symbol->datatype == DATATYPE_CHAR)) ||
        (node->type == AST_FUNCALL && (node->symbol->datatype == DATATYPE_INT || node->symbol->datatype == DATATYPE_CHAR))
        )
        return 1;

    return 0;
}

int isRealOperand(AST *node){
    if (node == 0) return 0;

    if( node->type == AST_ADD ||
        node->type == AST_MINUS ||
        node->type == AST_TIMES ||
        node->type == AST_DIV ||
        (node->type == AST_SYMBOL && node->symbol->datatype == DATATYPE_REAL) ||
        (node->type == AST_VECACC && node->symbol->datatype == DATATYPE_REAL) ||
        (node->type == AST_FUNCALL && node->symbol->datatype == DATATYPE_REAL)
        )
        return 1;

    return 0;
}


int isLogicOperand(AST *node){
    if( node->datatype == DATATYPE_BOOL)
        return 1;

    return 0;
}

int isArithmeticOperand(AST *node){
    if( node->datatype == DATATYPE_INT || node->datatype==DATATYPE_CHAR)
        return 1;

    return 0;
}

