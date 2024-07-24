#ifndef HASH_HEADER
#define HASH_HEADER

#define HASH_SIZE 997

typedef struct hashNode{
        char *identifier;
        struct hashNode* next;
    } HashNode;
    

void hashInit();
unsigned long getHashAddress(char *str);
HashNode* findHashAddress(char *identifier);
HashNode* insertHashAddress(char *identifier);
void hashPrint();
#endif