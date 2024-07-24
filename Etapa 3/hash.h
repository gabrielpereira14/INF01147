//Gabriel Antônio Pereira - 0032449
#ifndef HASH_HEADER
#define HASH_HEADER

#define HASH_SIZE 997

typedef struct hashNode{
        char *identifier;
        int type;
        struct hashNode* next;
    } HashNode;
    

void hashInit();
unsigned long getHashAddress(char *str);
HashNode* findHashAddress(char *identifier, int type);
HashNode* insertHashAddress(char *identifier, int type);
void hashPrint();
#endif
