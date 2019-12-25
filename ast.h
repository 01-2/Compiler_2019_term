#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include "common.h"
//#include "y.tab.h"

typedef struct node{
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
node* createFuncDeclNode(int, TYPE, char*, node** );
node* createVarDeclNode(TYPE, int, int, char*, void* ); // val type, token, var size, var_name, value
node* createArithmeticNode(int tok, int type, node* n1, node* n2);
node* createConditionNode(int tok, node* n1, node* n2);
node* createUnaryArithmeticNode(int tok, node* n1);
node* createAffixNode(int tok, node* n1);

// Leafs
node* createConstNode(TYPE type, int tok, int size, void* value);

node* mkNode(node *left, node *right, int tok, TYPE type, int value);
node * mkLeaf(TYPE type, int tok, int value);
void printTree(node *tree, int tctr);

#endif