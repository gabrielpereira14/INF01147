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
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % HASH_SIZE;
}

HashNode* findHashAddress(char *identifier){
    HashNode *aux;
    int address = getHashAddress(identifier);
    for(aux = hashTable[address]; aux; aux = aux->next){
        if (!strcmp(aux->identifier, identifier)){
            return aux;
        }   
    }
    return NULL;
}

HashNode* insertHashAddress(char *identifier){
    HashNode *aux = findHashAddress(identifier);
    if(aux != NULL){
        return aux;
    }
    int address = getHashAddress(identifier);
    aux = malloc(sizeof(HashNode));
    aux->identifier = malloc(strlen(identifier) + 1);
    strcpy(aux->identifier,identifier);
    aux->next = hashTable[address];
    hashTable[address] = aux;
}

void hashPrint(){
    int i;
    HashNode *aux;
    for(i = 0; i < HASH_SIZE; i++){
        if (hashTable[i] != NULL)
        {
            printf("Hash[%d]: ",i);
            aux = hashTable[i];
            while (aux != NULL){
                printf("%s ",aux->identifier);
                aux = aux->next;
            }
            printf("\n");
        }
    }
}