#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	struct node *left;
	struct node *right;
	int token;
	int value;
	TYPE type;
}node;
node* mkNode(node *left, node *right, int tok, TYPE type, int value);
void printTree(node *tree, int tctr);

