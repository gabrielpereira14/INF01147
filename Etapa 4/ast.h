//Gabriel Antônio Pereira 00324449

#ifndef AST_HEADER
#define AST_HEADER

#define MAX_SONS 4

#include "hash.h"
#include <stdio.h>

#define AST_SYMBOL 1
#define AST_ADD 2
#define AST_MINUS 3
#define AST_TIMES 4
#define AST_DIV 5
#define AST_GT 6
#define AST_LT 7
#define AST_DIF 8
#define AST_EQ 9
#define AST_GE 10
#define AST_LE 11
#define AST_AND 12
#define AST_OR 13
#define AST_NOT 14
#define AST_LCMD 15
#define AST_PAREN 16
#define AST_WHILE 17
#define AST_IF 18
#define AST_IFELSE 19
#define AST_ATT 20
#define AST_VECATT 21
#define AST_RET 22
#define AST_PRINT 23
#define AST_PRINTV 24
#define AST_READ 25
#define AST_BLOCK 26
#define AST_PARAM 27
#define AST_LIT 28
#define AST_TYPE 29
#define AST_ARG 30
#define AST_VARDEC 31
#define AST_VECDEC 32
#define AST_VECINIT 33
#define AST_FUNDEC 34
#define AST_DEC 35
#define AST_CHAR 36
#define AST_FLOAT 37
#define AST_BOOL 38
#define AST_INT 39
#define AST_VECACC 40
#define AST_FUNCALL 41

typedef struct astnode{
    int type;
    HashNode *symbol;
    int datatype;
    struct astnode *son[MAX_SONS];
} AST;


AST *astCreate(int type, HashNode *symbol, AST* s0, AST* s1, AST* s2, AST* s3);
void printAST(AST *node, int level);
void printASTToFile(AST *node, const char* filename);
void printNodeToFile(AST *node, FILE *f);
void astTypeToString(AST *node, char *str);
void astTypeToPrettyString(AST *node, char *str);
int isArithmeticOperand(AST *node);
int isLogicOperand(AST *node);

#endif