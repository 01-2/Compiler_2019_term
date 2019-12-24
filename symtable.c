#include "symtable.h"
#include "common.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern current_line;

SYM_TABLE* createTable(TABLE _type, char* _name){
    SYM_TABLE* table = (SYM_TABLE *)malloc(sizeof(SYM_TABLE));

    table->type = type;
    table->name = strdup(_name);
    table->child_cnt = 0;

    return table;
}

SYM_SYMBOL* createSymbol(TYPE _type, SYMBOL _sym_type, char* _name, int _param_cnt, char** _param_types, void* _address){
    SYM_SYMBOL* symbol = (SYM_SYMBOL *)malloc(sizeof(SYM_SYMBOL));
    
    symbol->type = _type;
    symbol->name = _name;
    symbol->syn_type = _sym_type;
    symbol->address= _address;

    if(_sym_type == SYMBOL.FUNCTION){
        symbol->param_cnt = _param_cnt;
        symbol->param_types = malloc(_param_cnt) * sizeof(char *);
        for(int i=0; i<param_cnt; i++){
            symbol->param_types = strdup(_param_types[i]);
        }
    }

    return symbol;
}

void* lookupVariable(list* list,  TYPE _type, char* _name){
    SYM_SYMBOL* node = list->table;

    for(int i = 0; i < node->child_cnt; i++){
        if(!strcmp(_name, node->child[i].name) && node->child[i].sym_type == SYMBOL.VARIABLE && node->child[i].type == _type)
            return node->child[i]->address;
    }

    if(list->prev != nullptr)
        return lookupVariable(list->prev, _type, _name);

    return nullptr;
}

void* lookupFunction(list* list, TYPE _type, char* _name){
    SYM_SYMBOL* node = list->table;

    for(int i = 0; i < node->child_cnt; i++){
        if(!strcmp(_name, node->child[i].name) && node->child[i].sym_type == SYMBOL.FUNCTION && node->child[i].type == _type)
            return node->child[i]->address;
    }

    if(list->prev != nullptr)
        return lookupFunction(list->prev, _type, _name);

    return nullptr;
}

int addList(list* current, list* prev){
    prev->prev = current;

    return 1;
}

void makeTable(list* list, TABLE _type, char* _name){
    if(_type == TABLE.GLOBAL)
        list->prev = nullptr;

    list->table = createTable(_type, _name);
}