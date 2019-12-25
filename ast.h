#include <stdio.h>
#include <stdlib.h>
#include "common.h"
//#include "y.tab.h"

typedef struct node{
    struct node **left;
	int token;
	int value;
	enum TYPE type;
}node;
node* mkNode(node *left, node *right, int tok, enum TYPE type, int value);
void printTree(node *tree, int tctr);

