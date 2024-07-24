#include "semantic.h"
#include "ast.h"
#include <stdlib.h>

int semanticErrorCount;

void checkAndSetDeclarations(AST *node, AST* context){
    int i;
    if (node == 0) return;

    
    if (node->symbol || node->type == AST_RET){
        switch (node->type)
        {
            
        case AST_FUNDEC:
            if(node->symbol->type != SYMBOL_IDENTIFIER){
                fprintf(stderr, "ERROR: redeclaration of function %s \n", node->symbol->identifier);
                semanticErrorCount++;
            }

            node->symbol->type = SYMBOL_FUNCTION;
            node->symbol->datatype = astTypeToDatatype(node->son[0]->type);
            node->symbol->declaration = node;
            break;
        
        case AST_VARDEC:
            if(node->symbol->type != SYMBOL_IDENTIFIER){
                fprintf(stderr, "ERROR: redeclaration of variable %s \n", node->symbol->identifier);
                semanticErrorCount++;
            }
            node->symbol->type = SYMBOL_VARIABLE;
            node->symbol->datatype = astTypeToDatatype(node->son[0]->type);
            break;
        
        case AST_VECDEC:
            if(node->symbol->type != SYMBOL_IDENTIFIER){
                fprintf(stderr, "ERROR: redeclaration of vector %s \n", node->symbol->identifier);
                semanticErrorCount++;
            }

            node->symbol->type = SYMBOL_VECTOR;
            node->symbol->datatype = astTypeToDatatype(node->son[0]->type);
            node->symbol->declaration = node;
            break;

        case AST_PARAM:
            if(node->symbol->type != SYMBOL_IDENTIFIER){
                fprintf(stderr, "ERROR: redeclaration of variable %s \n", node->symbol->identifier);
                semanticErrorCount++;
            }

            node->symbol->type = SYMBOL_VARIABLE;
            node->symbol->datatype = astTypeToDatatype(node->son[0]->type);
            break;

        case AST_SYMBOL:
            node->symbol->datatype = getSymbolDatatype(node->symbol);
            break;

        case AST_RET:
            node->symbol = context->symbol;
            break;

        default:
            break;
        }
    
    }
    for (i=0; i < MAX_SONS; i++){
        if(node->type == AST_FUNDEC){
            checkAndSetDeclarations(node->son[i], node);
        }else{
            checkAndSetDeclarations(node->son[i], context);
        }
    }
     
}

void checkUndeclared(){
    semanticErrorCount += hashCheckUndeclared();
}

int getSemanticErrors(){
    return semanticErrorCount;
}

int getSymbolDatatype(HashNode *symbol){
    switch (symbol->type)
    {
    case SYMBOL_LIT_INT: 
        return DATATYPE_INT;
    case SYMBOL_LIT_CHAR: 
        return DATATYPE_CHAR;
    case SYMBOL_LIT_REAL: 
        return DATATYPE_REAL;
    case SYMBOL_LIT_FALSE: 
        return DATATYPE_BOOL;
    case SYMBOL_LIT_TRUE: 
        return DATATYPE_BOOL;
    case SYMBOL_LIT_STRING: 
        return DATATYPE_STRING;
    default:
        return symbol->datatype;
    }
}

int astTypeToDatatype(int type){
    switch (type)
    {
    case AST_CHAR:
        return DATATYPE_CHAR;
    
    case AST_INT:
        return DATATYPE_INT;
    
    case AST_BOOL:
        return DATATYPE_BOOL;
    
    case AST_FLOAT:
        return DATATYPE_REAL;

    default:
        break;
    }

    fprintf(stderr, "Error converting type to datatype\n");
    exit(5);
}

int areCompatipleTypes(int datatype1, int datatype2){
    if(datatype1 == 0 || datatype2 == 0) 
        return 0;
    if(datatype1 == datatype2 ||
      (datatype1 == DATATYPE_INT && datatype2 == DATATYPE_CHAR) ||
      (datatype1 == DATATYPE_CHAR && datatype2 == DATATYPE_INT)){
        return datatype1;
      }

    return 0;
}

void setAndCheckOperandsType(AST *node){
    int i = 0;

    if(node == 0) return;


    for (i=0; i < MAX_SONS; i++){
        setAndCheckOperandsType(node->son[i]);
    }


    char typeString[32] = "";
    int type = 0;
    switch (node->type)
    {
    case AST_VECACC:
        node->datatype = node->symbol->datatype;
        break;
    case AST_FUNCALL:  
        node->datatype = node->symbol->datatype;
        break;
    case AST_PARAM:
        if(node->son[0]){
            node->datatype = node->son[0]->datatype;
        }
        break;
    case AST_ARG:
        if(node->son[0]){
            node->datatype = node->son[0]->symbol->datatype;
        }
        break;
    case AST_SYMBOL:
        node->datatype = node->symbol->datatype;
        break;
    case AST_ADD:
    case AST_MINUS:
    case AST_DIV:
    case AST_TIMES:
        if(isArithmeticOperand(node->son[0])){
            if(isArithmeticOperand(node->son[1])){
                if((type = areCompatipleTypes(node->son[0]->datatype,node->son[1]->datatype))){
                    node->datatype = type;
                }else{
                    astTypeToPrettyString(node,typeString);
                    fprintf(stderr, "ERROR: incompatible types for %s\n",typeString);
                    semanticErrorCount++;
                }
            }else{
                astTypeToPrettyString(node,typeString);
                fprintf(stderr, "ERROR: invalid right operand for %s\n",typeString);
                semanticErrorCount++;
            }
        }else{
            astTypeToPrettyString(node,typeString);
            fprintf(stderr, "ERROR: invalid left operand for %s\n",typeString);
            semanticErrorCount++;
        }
        break;

    case AST_GE:
    case AST_GT:
    case AST_LT:
    case AST_LE:
    case AST_DIF:
    case AST_EQ:
        if(!isLogicOperand(node->son[0])){
            if(!isLogicOperand(node->son[1])){
                if((type = areCompatipleTypes(node->son[0]->datatype,node->son[1]->datatype))){
                    node->datatype = DATATYPE_BOOL;
                }else{
                    astTypeToPrettyString(node,typeString);
                    fprintf(stderr, "ERROR: incompatible types for %s\n",typeString);
                }
            }else{
                astTypeToPrettyString(node,typeString);
                fprintf(stderr, "ERROR: invalid right operand for %s\n",typeString);
            }
        }else{
            astTypeToPrettyString(node,typeString);
            fprintf(stderr, "ERROR: invalid left operand for %s\n",typeString);
        }
        break;

    case AST_AND:
    case AST_OR:
        if(isLogicOperand(node->son[0])){
            if(isLogicOperand(node->son[1])){
                node->datatype = DATATYPE_BOOL;
            }else{
                astTypeToPrettyString(node,typeString);
                fprintf(stderr, "ERROR: invalid right operand for %s\n",typeString);
                semanticErrorCount++;
            }
        }else{
            astTypeToPrettyString(node,typeString);
            fprintf(stderr, "ERROR: invalid left operand for %s\n",typeString);
            semanticErrorCount++;
        }
        break;
    case AST_WHILE: 
    case AST_IF:
    case AST_IFELSE: 
    case AST_NOT:
        if(isLogicOperand(node->son[0])){
            node->datatype = DATATYPE_BOOL;
        }else{
            astTypeToPrettyString(node,typeString);
            fprintf(stderr, "ERROR: invalid operand for %s\n",typeString);
            semanticErrorCount++;
        }
        break;

    case AST_PAREN:
        if(node->son[0] != 0){
            node->datatype = node->son[0]->datatype;
        }
        break;

    case AST_VECATT: 
        if(node->symbol->type == SYMBOL_VECTOR){
            if(node->son[0] != 0 && areCompatipleTypes(node->son[0]->datatype, DATATYPE_INT)){
                if((type = areCompatipleTypes(node->son[1]->datatype, node->symbol->datatype))){
                    node->datatype = type;
                }else{
                    astTypeToPrettyString(node,typeString);
                    fprintf(stderr, "ERROR: incompatible types for %s" ,typeString);
                    getHashDatatypeAsString(node->symbol->datatype,typeString);
                    fprintf(stderr, ", expected %s " ,typeString);
                    getHashDatatypeAsString(node->son[1]->datatype,typeString);
                    fprintf(stderr, "but received %s\n",typeString);
                    semanticErrorCount++;
                }

                AST *vectorDeclaration = node->symbol->declaration;
                int vectorSize = atoi(vectorDeclaration->son[1]->symbol->identifier);
                int index = atoi(node->son[0]->symbol->identifier);
                if (index >= vectorSize || index < 0){\
                    fprintf(stderr, "ERROR: Index out of range for vector %s with size %d\n",node->symbol->identifier, vectorSize);
                    semanticErrorCount++;
                }

            }else{
                fprintf(stderr, "ERROR: vector index type must be and an integer\n");
                semanticErrorCount++;
            } 
        }
        break;

    case AST_VECDEC: 
        if (node->symbol->type == SYMBOL_VECTOR){
            if(node->son[0]){
                int vecLenght = atoi(node->son[1]->symbol->identifier);
                int vecInitLenght = 0;
                AST *vecInit = node->son[2];
                while (vecInit != NULL)
                {
                    vecInitLenght++;
                    getHashDatatypeAsString(vecInit->symbol->datatype,typeString);
                    if(!areCompatipleTypes(node->son[0]->datatype, vecInit->symbol->datatype)){
                        fprintf(stderr, "ERROR: incompatible value for %s intialization" ,node->symbol->identifier);
                        getHashDatatypeAsString(node->son[0]->datatype,typeString);
                        fprintf(stderr, ", expected %s " ,typeString);
                        getHashDatatypeAsString(vecInit->symbol->datatype,typeString);
                        fprintf(stderr, "but received %s\n",typeString);
                        semanticErrorCount++;
                    }
                    vecInit = vecInit->son[0];
                }
                
                if(vecInitLenght > vecLenght){
                    fprintf(stderr, "ERROR: Too many values in %s initialization, expected %d but received %d\n",node->symbol->identifier,vecLenght,vecInitLenght);
                    semanticErrorCount++;
                }
                
            }else{
                fprintf(stderr, "ERROR: vector index type must be and an integer\n");
                semanticErrorCount++;
            } 
        }
        
        break;

    
    case AST_ATT: 
        if(node->symbol->type == SYMBOL_VARIABLE){
            if((type = areCompatipleTypes(node->son[0]->datatype, node->symbol->datatype))){
                node->datatype = type;
            }else{
                astTypeToPrettyString(node,typeString);
                fprintf(stderr, "ERROR: incompatible types for %s" ,typeString);
                getHashDatatypeAsString(node->symbol->datatype,typeString);
                fprintf(stderr, ", expected %s but " ,typeString);
                getHashDatatypeAsString(node->son[0]->datatype,typeString);
                fprintf(stderr, "received %s) \n",typeString);
                semanticErrorCount++;
            }
        }
        
        break;

    case AST_READ:
        if(node->symbol->type == SYMBOL_VARIABLE){
            if((type = areCompatipleTypes(node->son[0]->datatype, node->symbol->datatype))){
                node->datatype = type;
            }else{
                astTypeToPrettyString(node,typeString);
                fprintf(stderr, "ERROR: incompatible variable or type for %s" ,typeString);
                getHashDatatypeAsString(node->son[0]->datatype,typeString);
                fprintf(stderr, ", expected %s but " ,typeString);
                getHashDatatypeAsString(node->symbol->datatype,typeString);
                fprintf(stderr, "received %s) \n",typeString);
                semanticErrorCount++;
            }
        }else{
            fprintf(stderr, "ERROR: Invalid operand for read, expected a variable\n");
        }
        break;

    case AST_CHAR:
        node->datatype = DATATYPE_CHAR;
        break;
    case AST_INT:
        node->datatype = DATATYPE_INT;
        break;
    case AST_BOOL:
        node->datatype = DATATYPE_BOOL;
        break;
    case AST_FLOAT:
        node->datatype = DATATYPE_REAL;
        break;
    case AST_PRINTV: 
        if((type = areCompatipleTypes(node->son[0]->datatype, node->son[1]->datatype))){
            node->datatype = type;
        }else{
            astTypeToPrettyString(node,typeString);
            fprintf(stderr, "ERROR: incompatible types for %s" ,typeString);
            getHashDatatypeAsString(node->son[0]->datatype,typeString);
            fprintf(stderr, ", expected %s but " ,typeString);
            getHashDatatypeAsString(node->son[1]->datatype,typeString);
            fprintf(stderr, "received %s) \n",typeString);
            semanticErrorCount++;
        }
        break;


    case AST_RET: 
        if((type = areCompatipleTypes(node->son[0]->datatype, node->symbol->datatype))){
            node->datatype = type;
        }else{
            fprintf(stderr, "ERROR: incompatible return type for function %s" ,node->symbol->identifier);
            getHashDatatypeAsString(node->symbol->datatype,typeString);
            fprintf(stderr, ", expected %s but " ,typeString);
            getHashDatatypeAsString(node->son[0]->datatype,typeString);
            fprintf(stderr, "received %s) \n",typeString);
            semanticErrorCount++;
        }
        break;
    
    case AST_VARDEC:
        if((type = areCompatipleTypes(node->son[1]->datatype, node->symbol->datatype))){
            node->datatype = type;
        }else{
            fprintf(stderr, "ERROR: value for initialization of %s" ,node->symbol->identifier);
            getHashDatatypeAsString(node->symbol->datatype,typeString);
            fprintf(stderr, ", expected %s but " ,typeString);
            getHashDatatypeAsString(node->son[1]->datatype,typeString);
            fprintf(stderr, "received %s) \n",typeString);
            semanticErrorCount++;
        }
        break;

    default:
        break;
    }
    
     
}



void checkVectorAndFunctionUse(AST *node){
    if(node == 0) return;

    int i;

    switch (node->type)
    {
    case AST_FUNCALL:
        if(node->symbol->type == SYMBOL_FUNCTION){
            AST *argList = node->son[0];
            AST *paramList = node->symbol->declaration->son[1];

            int argCount = 0;
            int paramCount = 0;

            while (argList != 0 && paramList != 0)
            {
                AST *arg = argList->son[0];
                AST *param = paramList->son[0];

                argCount++;
                paramCount++;

                if (!areCompatipleTypes(param->datatype, arg->datatype))
                {
                    
                    fprintf(stderr,"ERROR: function parameter and argument type mismatch on function \"%s\" call\n", node->symbol->identifier);
                    semanticErrorCount++;
                }

                argList = argList->son[1];
                paramList = paramList->son[1];
            }

            while (argList != 0)
            {
                argCount++;
                argList = argList->son[1];
            }
            
            while (paramList != 0)
            {
                paramCount++;
                paramList = paramList->son[1];
            }
            
            if(paramCount > argCount){
                fprintf(stderr,"ERROR: too few arguments on function %s call, expected %d but received %d\n", node->symbol->identifier, paramCount, argCount);
                semanticErrorCount++;
            }else if(paramCount < argCount){
                fprintf(stderr,"ERROR: too many arguments on function %s call, expected %d but received %d\n", node->symbol->identifier, paramCount, argCount);
                semanticErrorCount++;
            }
            
        }else{
            fprintf(stderr, "ERROR: %s is not a function but is being used as such \n", node->symbol->identifier);
            semanticErrorCount++;
        }
        break;
    case AST_VECATT:
    case AST_VECACC:
        if(node->symbol->type != SYMBOL_VECTOR){
            fprintf(stderr, "ERROR: %s is not a vector but is being used as such \n", node->symbol->identifier);
            semanticErrorCount++;
        }
        break;

    case AST_ATT:
        if(node->symbol->type != SYMBOL_VARIABLE){
            fprintf(stderr, "ERROR: %s is not a regular variable but is being used as such \n", node->symbol->identifier);
            semanticErrorCount++;
        }
        break;

    case AST_FUNDEC:
        if(node->son[2] != 0){
            AST *block = node->son[2];
            if(block->son[0] == 0){
                fprintf(stderr, "ERROR: function %s has no implementation\n", node->symbol->identifier);
                semanticErrorCount++;
            }
        }
        break;
    default:
        break;
    }

    for (i=0; i < MAX_SONS; i++){
        checkVectorAndFunctionUse(node->son[i]);
    }
}