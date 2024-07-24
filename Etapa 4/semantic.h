#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

#include "hash.h"
#include "ast.h"

void checkAndSetDeclarations(AST *node, AST* context);
void checkUndeclared();
void setAndCheckOperandsType(AST *node);
void checkVectorAndFunctionUse(AST *node);
int getSemanticErrors();
int astTypeToDatatype(int type);
int getSymbolDatatype(HashNode *symbol);
#endif