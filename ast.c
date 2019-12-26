#include "ast.h"
#include "symtable.h"
#include "common.h"

extern list *l;

node* createMainDeclNode(int tok, int stmt_cnt, node** stmt){
    node* new_node = (node *)malloc(sizeof(node));
    new_node->token = tok;
    new_node->sym = FUNCTION;
    new_node->ast_type = MAINDECL;
    new_node->type = VOID;


    new_node->child = (node **)malloc(sizeof(node *) * (func_param_cnt));
    new_node->child_cnt = stmt_cnt;
    for(int i = 0; i< stmt_cnt; i++)
        new_node->child[i] = n[i];

    return new_node;
}


node* createFuncDeclNode(int tok, TYPE type, char* name, node** n){
    /*           funcDecl
    /         |      |     \        \
returnType Name  param_num param[0] ... param[param_num]
                              |
                             ID(name)
*/

 //   if(tok == "funcDecl"){ // must be modified as bison token
        /*
        TYPE func_type;
        char *func_name;
        int func_param_cnt;
        TYPE* param_types;

        func_type = type;
        func_name = strdup(name);
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
        */
        node* new_node = (node *)malloc(sizeof(node));
        new_node->token = tok;
        new_node->sym = FUNCTION;
        new_node->ast_type = FUNCDECL;
        new_node->type = type;

        new_node->child = (node **)malloc(sizeof(node) * (func_param_cnt));
        for(int i = 0; i< 3 + func_param_cnt; i++)
            new_node->child[i] = n[i];

        return new_node;
 //   }
}

node* createFuncBodyNode(int tok, int type, int stmt_cnt, node** stmt){
    node *n = malloc(sizeof(node));
    n->token = tok;
    n->sym = FUNCTION;
    n->type = type;
    n->ast_type = FUNCBODY;

    n->child = malloc(sizeof(node *) * stmt_cnt);
    n->child_cnt = stmt_cnt;
    for(int i = 0; i < stmt_cnt; i++)
        n->child[i] = stmt[i];

    return node;
}

node* createArithmeticNode(int tok, int type, node* n1, node* n2) { // plus, minus, div, mul, assign
    node* n = (node*)malloc(sizeof(node));
    
    n->token = tok;
    n->type = type;
    n->ast_type = ARITH;
    
    n->child = malloc(sizeof(node) * 2);
    n->child[0] = n1;
    n->child[1] = n2;

    return n;
}




node* createUnaryArithmeticNode(int tok, node* n1) {
    node* n = (node*)malloc(sizeof(node));

    n->token = tok;
    n->ast_type = UNARY;

    n->child = malloc(sizeof(node));
    n->ch(node));

    n->token = tok;
    n->type = type;

    n->child = malloc(sizeof(node) * 2);
    n->child[0] = n1;ild[0] = n1;

    return n;
}

node* createAffixNode(int tok, node* n1) {
    node* n = malloc(sizeof(node));

    n->token = tok;
    n->ast_type = AFFIX;

    n->child = malloc(sizeof(node));
    n->child[0] = n1;

    return n;
}

node* createConditionNode(int tok, node* n1, node* n2) { // <, >, ||, &&, ==
    node* n = malloc(sizeof(node));

    n->token = tok;
    n->ast_typt = CONDITION;
    n->child = malloc(sizeof(node *) * 2);
    n->child[0] = n1;
    n->child[1] = n2;

    return n;
}

node* createIfDecl(int tok, int stmt_cnt, node** stmt){
    node* n = malloc(sizeof(node));

    n->token = tok;
    n->ast_type = IFDECL;
    n->child = malloc(sizeof(node *) stmt_cnt);
    n->child_cnt = stmt_cnt;
    for(int i = 0; i < stmt_cnt; i++)
        child[i] = stmt[i];

    return n;
}

node* createWhileDecl(int tok, int stmt_cnt, node** stmt){
    node* n = malloc(sizeof(node));

    n->token = tok;
    n->ast_type = WHILEDECL;
    n->child = malloc(sizeof(node *) stmt_cnt);
    n->child_cnt = stmt_cnt;
    for(int i = 0; i < stmt_cnt; i++)
        child[i] = stmt[i];

    return n;
}


node* createVarDeclNode(TYPE type, int tok, int size, char *var_name, void* value){ //as leaf
    /*          varDecl
     *    varType   varName    varValue
     *       |         |           |
     *     Type       ID           ...
     */

        /*
        node* n = (node *)malloc(sizeof(node));

        Type var_type;
        char* var_name;

        SYM_SYMBOL* sym = lookupFunction(l, type, FUNCTION, func_name, 0, nullptr);        
        list* table = sym->address;
        int res;
        if (table == nullptr) {
            char* buf;
            sprintf(buf, "Error : Line %d. Can't find function \"%s\".", func_name);
            error_handle(buf);
        }

        res = createSymbol(type, VARIABLE, func_name, 0, nullptr, size, value);
        */
    node* n = (node*)malloc(sizeof(node));
    n->type = type;
    n->sym = VARIABLE;
    n->size = size;
    n->name = strdup(var_name);
    n->value = value;
    n->token = tok;

    return n;
}

node* createConstNode(TYPE type, int tok, int size, void* value) {
    node* n = (node*)malloc(sizeof(node));
    n->type = type;
    n->value = (int *)value;
    n->ast_type = CONSTANT;

    return n;
}

void printSpace(int cnt){
    for(int i = 0; i < cnt ; i++)
        printf("    ");

}

int cnt = 0;

void printTree(node *tree){
    printSpace(cnt);
    cnt++;
    if(tree->ast_type == MAINDECL){
        printf("MainDecl()\n")
        for(int i = 0; i < tree->child_cnt; i++)
            printTree(node[i]);
    }
    if(tree->ast_type == FUNCDECL){
        printf("%s", tree->name); printf("() DECL\n");
        for(int i = 0; i < tree->child_cnt; i++)
            printTree(node[i]);
    }
    if(tree->ast_type == FUNCBODY){
        printf("%s", tree->name); printf("() BODY\n");
        for(int i = 0; i < tree->child_cnt; i++);
    }
    if(tree=>ast_type == VARDECL){
        if (tree->type == INT) {
            printf("Var(");
            printf("%s", tree->name);
            printf(") : ");
            printf("%d\n", tree->value);
        }
        else if (tree->type == INT_ARRAY){
            printf("Var(");
            printf("%s", tree->name);
            printf(") : { ");
            for(int i = 0; i<tree->child_cnt; i++){
                printf("%d, ", tree->child[i]);
            }
            printf("}\n");
        }
    }
    if(tree->ast_type == IFDECL){
        printf("IF\n");
        for(int i = 0; i < tree->child_cnt; i++)
            printTree(tree->child[i]);
    }
    if(tree->ast_type == WHILEDECL){
        printf("WHILE\n");
        for(int i = 0 ; i < tree->child_cnt; i++)
            printTree(tree->child[i]);
    }
    else if(tree->ast_type == ARITH) {
        if (tree->token == _ADD) {
            printf("BINARY(+)\n")
            printTree(tree->child[0]);
            printTree(tree->child[1]);
        } else if (tree->token == _MINUS) {
            printf("BINARY(-)\n");
            printTree(tree->child[0]);
            printTree(tree->child[1]);
        } else if (tree->token == _TIMES) {
            printf("BINARY(*)\n");
            printTree(tree->child[0]);
            printTree(tree->child[1]);
        } else if (tree->token == _DIV) {
            printf("BINARY(/)\n");
            printTree(tree->child[0]);
            printTree(tree->child[1]);
        }
    }
    else if(tree->ast_type == UNARY){
        if(tree->token == _ADD) {
            printf("UOP(+)\n");
            printTree(tree->child[0]);
        }
        if(tree->token == _MINUS){
            printf("UOP(-)\n");
            printTree(tree->child[0]);
        }
        if(tree->token == _NOT){
            printf("UOP(!)\n");
            printTree(tree->child[0]);
        }
    }
    else if(tree->ast_type == CONDITION){
        if(tree->token == _AND){
            printf("COND(&&)\n");
            printTree(tree->child[0]);
            printTree(tree->child[1]);
        }
        else if(tree->token == _OR){
            printf("COND(||)\n");
            printTree(tree->child[0]);
            printTree(tree->child[1]);
        }
        else if(tree->token == _RELOP){
            printf("COND(<)\n");
            printTree(tree->child[0]);
            printTree(tree->child[1]);
        }
        else if(tree->token ==  _LEROP){
            printf("COND(>)\n");
            printTree(tree->child[0]);
            printTree(tree->child[1]);
        }
    }
    else if (tree->ast_type == CONSTANT){
        printf("CONSTANT : %d", tree->value);
    }








    cnt--;
}
