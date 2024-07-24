//Gabriel Antônio Pereira - 0032449
#ifndef HASH_HEADER
#define HASH_HEADER

#define HASH_SIZE 997

#define SYMBOL_LIT_INT 1
#define SYMBOL_LIT_CHAR 2
#define SYMBOL_LIT_STR 3
#define SYMBOL_LIT_REAL 4
#define SYMBOL_LIT_TRUE 5
#define SYMBOL_LIT_FALSE 6
#define SYMBOL_LIT_STRING 7
#define SYMBOL_IDENTIFIER 8
#define SYMBOL_FUNCTION 9
#define SYMBOL_VECTOR 10
#define SYMBOL_VARIABLE 11

#define DATATYPE_INT 1
#define DATATYPE_BOOL 2
#define DATATYPE_REAL 3
#define DATATYPE_CHAR 4
#define DATATYPE_STRING 4

struct astnode;

typedef struct hashNode{
        char *identifier;
        int type;
        int datatype;
        struct astnode* declaration;
        struct hashNode* next;
    } HashNode;
    

void hashInit();
unsigned long getHashAddress(char *str);
HashNode* findHashAddress(char *identifier, int type);
HashNode* insertHashAddress(char *identifier, int type);
void getHashDatatypeAsString(int datatype, char *str);
void hashPrint();
int hashCheckUndeclared();

#endif
