#include "ast.h"

node* mkNode(node *left, node *right , int tok){
	node *newNode = (node *)malloc(sizeof(node));
	
	newNode->left = left;
	newNode->right = right;
	newNode->token = tok;

	return newNode;
}

void printTree(node *tree, int tctr){
	int i = 0;
	for(i = 0; i < tctr; i++) printf("\t");
	if((tree->token > -1) && (tree->token < 10))
		printf("Int(%d)\n", tree->token);
	else if(tree->token > 100){
		printf("Uop(-)\n");
		printf("\t\tInt(%d)\n", tree->token-100);
	}
	else if(tree->token > 10)
		printf("Op(%c)\n", tree->token);

	if (tree->left)
		printTree(tree->left, tctr+1);
	if (tree->right)
		printTree(tree->right, tctr+1);
}
