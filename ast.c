#include "ast.h"
#include "symtable.h"
#include "common.h"

extern list *l;

node* mkNode(TYPE type, int tok, int value, node** n){
    /*           funcDecl
        /         |      |     \        \
    returnType Name  param_num param[0] ... param[param_num]
                                  |
                                 ID(name)
    */
    if(tok == "funcDecl"){
        TYPE func_type;
        char *func_name;
        int func_param_cnt;
        TYPE* param_types;

        func_type = n[0]->value;
        func_name = strdup(n[1]->value);
        func_param_cnt = n[2]->value;

        param_types = (TYPE *)malloc(sizeof(TYPE) * func_param_cnt);
        for(int i = 0; i< func_param_cnt; i++){
            param_types[i] = n[i+3]->type;
        }

        SYM_SYMBOL* addr = lookupFunction(l, func_type, FUNCTION, func_name, func_param_cnt, param_types);
        if(addr == nullptr) {
            char *buf;
            sprintf(buf, "Error : Line %d. Function Declaration duplicated.", current_line);
            error_handle(buf);
        }

        list* new_list = addr->address;
        for(int i = 0; i < func_param_cnt; i++){
            int size = 0;
            if(n[i+3]->type == INT_ARRAY){
                size = n[i+3]->size;
            }

            int res = addElement(new_list, param_types[i], VARIABLE, n[i+3]->name, 0, nullptr, size, &n[i+3]->value);
            if(res == false){
                char *buf;
                sprintf(buf, "Error : Line %d. Something wrong with initialize function %s's parameter", current_line, func_name);
                error_handle(buf);
            }
        }

        node* new_node = (node *)malloc(sizeof(node));
        new_node->token = tok;
        new_node->child = (node **)malloc(sizeof(node) * (3 + func_param_cnt));
        for(int i = 0; i< 3 + func_param_cnt; i++)
            new_node->child[i] = n[i];

        return new_node;
    }


}

node* mkLeaf(TYPE type, int tok, int value){
    node *newNode = (node *)malloc(sizeof(node));

    newNode->token = tok;
    newNode->value = value;
    newNode->type = type;

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
