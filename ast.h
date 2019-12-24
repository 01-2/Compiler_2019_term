#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	struct node *left;
	struct node *right;
	int token;
}node;
node* mkNode(node *left, node *right, int tok);
void printTree(node *tree, int tctr);
