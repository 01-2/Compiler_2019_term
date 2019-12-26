#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include "common.h"
//#include "y.tab.h"

typedef enum AST_TYPE{
    FUNCDECL,
    FUNCBODY,
    MAINDECL,
    VARDECL,
    ARITH,
    UNARY,
    CONDITION,
    IFDECL,
    WHILEDECL,
    AFFIX,
    CONSTANT
}AST_TYPE;


typedef struct node{
    AST_TYPE ast_type;
    struct node **child;
	int child_cnt;
	int token;
	SYMBOL sym;

	TYPE type;
	char* name;
	int size;
	int value;
}node;

// Nodes
node* createFuncDeclNode(int, TYPE, char*, int ,node** );
node* createVarDeclNode(TYPE, int, int, char*, void* ); // val type, token, var size, var_name, value
node* createArithmeticNode(int tok, int type, node* n1, node* n2);
node* createConditionNode(int tok, node** );
node* createIfDecl(int tok, int stmt_cnt, node** stmt);
node* createWhileDecl(int tok, int stmt_cnt, node** stmt);
node* createUnaryArithmeticNode(int tok, node* n1);
node* createAffixNode(int tok, node* n1);

// Leafs
node* createConstNode(TYPE type, int tok, int size, void* value);

node* mkNode(node *left, node *right, int tok, TYPE type, int value);
node * mkLeaf(TYPE type, int tok, int value);
void printTree(node *tree);
void printSpace(int cnt);


#endif