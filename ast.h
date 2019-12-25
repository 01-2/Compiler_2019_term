#include <stdio.h>
#include <stdlib.h>
#include "common.h"
//#include "y.tab.h"

typedef struct node{
    struct node **left;
	int token;
	int value;
	char *name;
	int size;
	TYPE type;
	SYMBOL sym;
}node;
node* mkNode(node *left, node *right, int tok, TYPE type, int value);
node * mkLeaf(TYPE type, int tok, int value);
void printTree(node *tree, int tctr);

