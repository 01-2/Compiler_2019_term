#include "ast.h"
#include "common.h"

node* mkNode(node *left, node *right , int tok, enum TYPE type, int value){
	node *newNode = (node *)malloc(sizeof(node));
	
	newNode->token = tok;
	newNode->value = value;
	newNode->left = left;
	newNode->type = type;
	
	if(tok != "[some post / pre / unary affix]") // need fix
		newNode->right = right;	

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
