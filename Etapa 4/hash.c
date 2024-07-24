//Gabriel Antônio Pereira 00324449

#include "hash.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

HashNode* hashTable[HASH_SIZE];
void hashInit(){
    int i;
    for (i = 0 ; i < HASH_SIZE; i++){
        hashTable[i] = NULL;
    }
} 

unsigned long getHashAddress(char *str){
    int c;
    unsigned long hash = 5381;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % HASH_SIZE;
}

HashNode* findHashAddress(char *identifier, int type){
    HashNode *aux;
    int address = getHashAddress(identifier);
    for(aux = hashTable[address]; aux; aux = aux->next){
        if (!strcmp(aux->identifier, identifier)){
            return aux;
        }   
    }
    return NULL;
}

HashNode* insertHashAddress(char *identifier, int type){
    HashNode *aux = findHashAddress(identifier, type);
    if(aux != NULL){
        return aux;
    }
    int address = getHashAddress(identifier);
    aux = malloc(sizeof(HashNode));
    aux->identifier = malloc(strlen(identifier) + 1);
    strcpy(aux->identifier,identifier);
    aux->next = hashTable[address];
    aux->type = type;
    aux->datatype = 0;
    hashTable[address] = aux;

    return aux;
}


void getTypeAsString(HashNode *node, char *str){
    switch (node->type)
        {
        case SYMBOL_LIT_INT:
            strcpy(str, "LIT_INT");
            break;
        case SYMBOL_LIT_CHAR:
            strcpy(str, "LIT_CHAR");
            break;
        case SYMBOL_LIT_STR:
            strcpy(str, "LIT_STR");
            break;
        case SYMBOL_LIT_REAL:
            strcpy(str, "LIT_REAL");
            break;
        case SYMBOL_LIT_TRUE:
            strcpy(str, "LIT_TRUE");
            break;
        case SYMBOL_LIT_FALSE:
            strcpy(str, "LIT_FALSE");
            break;
        case SYMBOL_IDENTIFIER:
            strcpy(str, "IDENTIFIER");
            break;
        case SYMBOL_FUNCTION:
            strcpy(str, "FUNCTION");
            break;
        case SYMBOL_VECTOR:
            strcpy(str, "VECTOR");
            break;
        case SYMBOL_VARIABLE :
            strcpy(str, "VARIABLE");
            break;
                    
        default:
            strcpy(str, "UNSET");
            break;
        }
}

void getHashDatatypeAsString(int datatype, char *str){
    switch (datatype)
    {
    case DATATYPE_CHAR:
        strcpy(str, "DATATYPE_CHAR");
        break;

    case DATATYPE_INT:
        strcpy(str, "DATATYPE_INT");
        break;
    
    case DATATYPE_BOOL:
        strcpy(str, "DATATYPE_BOOL");
        break;
    
    case DATATYPE_REAL:
        strcpy(str, "DATATYPE_REAL");
        break;

    default:
        strcpy(str, "UNSET");
        break;
    }
}



void hashPrint(){
    int i; 
    HashNode *aux;
    char type[64] = "";
    char datatypeStr[64] = "";
    for(i = 0; i < HASH_SIZE; i++){
        if (hashTable[i])
            fprintf(stderr,"Hash[%d]: ",i);
        for(aux = hashTable[i]; aux; aux = aux->next){
            getTypeAsString(aux,type);
            getHashDatatypeAsString(aux->datatype,datatypeStr);
            fprintf(stderr, "%s - %s - %s\n",aux->identifier,type, datatypeStr);
        }
    }
}

int hashCheckUndeclared(){
    int i;
    int undeclared = 0;
    HashNode *aux;
    for(i = 0; i < HASH_SIZE; i++){
        for(aux = hashTable[i]; aux; aux = aux->next){
            if(aux->type == SYMBOL_IDENTIFIER){
                fprintf(stderr, "ERROR: undeclared variable %s\n",aux->identifier);
                undeclared++;
            }
        }
    }

    return undeclared;
}