#include "symtable.h"
#include "common.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern current_line;

SYM_TABLE* createTable(enum TABLE _type, char* _name){
    SYM_TABLE* table = (SYM_TABLE *)malloc(sizeof(SYM_TABLE));

    table->type = _type;
    table->name = strdup(_name);
    table->child_cnt = 0;

    return table;
}

SYM_SYMBOL* createSymbol(enum TYPE _type, enum SYMBOL _sym_type, char* _name, int _param_cnt, enum TYPE* _param_types, void* _address){
    SYM_SYMBOL* symbol = (SYM_SYMBOL *)malloc(sizeof(SYM_SYMBOL));
    
    symbol->type = _type;
    symbol->name = _name;
    symbol->sym_type = _sym_type;
    symbol->address= _address;

    if(_sym_type == FUNCTION){
        symbol->param_cnt = _param_cnt;
        symbol->param_types = (enum TYPE *)malloc(_param_cnt * sizeof(enum TYPE *));
        for(int i=0; i < _param_cnt; i++)
            symbol->param_types[i] = _param_types[i];
        
    }

    return symbol;
}


void* lookupFunction(list* list, enum TYPE _type, char* _name){
    SYM_TABLE* node = list->table;

    for(int i = 0; i < node->child_cnt; i++){
        if (!strcmp(_name, node->child[i]->name) && node->child[i]->sym_type == FUNCTION && node->child[i]->type == _type)
            return node->child[i]->address;
    }

    if(list->prev != nullptr)
        return lookupFunction(list->prev, _type, _name);

    return nullptr;
}

int addList(list* current, list* prev){
    current->prev = prev;

    return true;
}

void* lookupVariable(list* list, enum SYMBOL _type, char* _name)
{
    SYM_TABLE* node = list->table;

    for (int i = 0; i < node->child_cnt; i++) {
        if (!strcmp(_name, node->child[i]->name) && node->child[i]->sym_type == VARIABLE && node->child[i]->type == _type)
            return node->child[i]->address;
    }

    if (list->prev != nullptr)
        return lookupVariable(list->prev, _type, _name);

    return nullptr;
}


void makeTable(list* list, enum TABLE _type, char* _name){
    if(_type == GLOBAL)
        list->prev = nullptr;

    list->table = createTable(_type, _name);
}

int addElement(list *list, enum TYPE _type, enum SYMBOL _sym_type, char* _name, int _param_cnt, enum TYPE* _param_types, void* _address) {
    SYM_TABLE* table = list->table;
    
    if (_sym_type == VARIABLE) {
        if (lookupVariable(list, _sym_type, _name) != nullptr) return 1;
        
        table->child_cnt++;
        realloc(table->child, sizeof(SYM_SYMBOL *) * table->child_cnt);
        table->child[table->child_cnt] = createSymbol(_type, _sym_type, _name, 0, nullptr, _address);
    }
    else if (_sym_type == FUNCTION) {
        if (lookupFunction(_name, _sym_type, _name) != nullptr) return 1;

        table->child_cnt++;
        table->child = (SYM_SYMBOL*)realloc((table->child_cnt) * sizeof(SYM_SYMBOL));
        table->child[table->child_cnt] = createSymbol(_type, _sym_type, _name, _param_cnt, _param_types, _address);
    }

    return true;
}