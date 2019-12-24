#include "symtable.h"
#include "common.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern current_line;

SYM_TABLE* createTable(TABLE _type, char* _name){
    SYM_TABLE* table = (SYM_TABLE *)malloc(sizeof(SYM_TABLE));

    table->type = _type;
    table->name = strdup(_name);
    table->child_cnt = 0;

    return table;
}

SYM_SYMBOL* createSymbol( TYPE _type,  SYMBOL _sym_type, char* _name, int _param_cnt, TYPE* _param_types, int _size, void* _address){
    SYM_SYMBOL* symbol = (SYM_SYMBOL *)malloc(sizeof(SYM_SYMBOL));
    
    symbol->type = _type;
    symbol->name = strdup(_name);
    symbol->sym_type = _sym_type;
    symbol->size = _size;

    if(_sym_type == VARIABLE) {
        void *value;
        if(_type == INT)
            value = (int *)malloc(sizeof(int));
        else if(_type == INT_ARRAY){
            int *lv = (int *)malloc(sizeof(int) * _size), *rv = (int *)_address;

            for(int i = 0; i < _size; i++)
                lv[i] = rv[i];

            value = lv;
        }

        symbol->address = _address;
    }
    else
        symbol->address = _address;


    if(_sym_type == T_FUNCTION){
        symbol->param_cnt = _param_cnt;
        symbol->param_types = ( TYPE *)malloc(_param_cnt * sizeof( TYPE *));
        for(int i=0; i < _param_cnt; i++)
            symbol->param_types[i] = _param_types[i];
    }

    return symbol;
}

SYM_SYMBOL* lookupFunction(list* list, TYPE _type, char* _name){
    SYM_TABLE* node = list->table;

    for(int i = 0; i < node->child_cnt; i++){
        if (!strcmp(_name, node->child[i]->name) && node->child[i]->sym_type == T_FUNCTION && node->child[i]->type == _type)
            return node->child[i];
    }

    if(list->prev != nullptr)
        return lookupFunction(list->prev, _type, _name);

    return nullptr;
}

int addList(list* current, list* prev){
    current->prev = prev;

    return true;
}

SYM_SYMBOL* lookupVariable(list* list, TYPE _type, char* _name)
{
    SYM_TABLE* node = list->table;

    for (int i = 0; i < node->child_cnt; i++) {
        if (!strcmp(_name, node->child[i]->name) && node->child[i]->sym_type == VARIABLE && node->child[i]->type == _type)
            return node->child[i];
    }

    if (list->prev != nullptr)
        return lookupVariable(list->prev, _type, _name);

    return nullptr;
}


void makeTable(list* list, TABLE _type, char* _name){
    if(_type == GLOBAL)
        list->prev = nullptr;

    list->table = createTable(_type, _name);
}

int addElement(list *list, TYPE _type, SYMBOL _sym_type, char* _name, int _param_cnt, TYPE* _param_types, int _size, void* _address) {
    SYM_TABLE* table = list->table;
    
    if (_sym_type == VARIABLE) {
        if (lookupVariable(list, _type, _name) != nullptr) return 1;

        if(table->child_cnt == 0)
            table->child = (SYM_SYMBOL *)malloc(sizeof(SYM_SYMBOL));
        else
            realloc(table->child, sizeof(SYM_SYMBOL *) * (table->child_cnt+1));

        if(_type == INT_ARRAY)
            table->child[table->child_cnt] = createSymbol(_type, _sym_type, _name, 0,  nullptr, _size, _address);
        else
            table->child[table->child_cnt] = createSymbol(_type, _sym_type, _name, 0, nullptr, 0, _address);
        table->child_cnt++;
    }
    else if (_sym_type == T_FUNCTION) {
        if (lookupFunction(_name, _sym_type, _name) != nullptr) return 1;

        if(table->child_cnt == 0)
            table->child = (SYM_SYMBOL *)malloc(sizeof(SYM_SYMBOL));
        else
            realloc(table->child, (table->child_cnt+1) * sizeof(SYM_SYMBOL));
        table->child[table->child_cnt] = createSymbol(_type, _sym_type, _name, _param_cnt, _param_types, 0, _address);
        table->child_cnt++;
    }
    else return false;

    return true;
}

int modifyElement(list* list, TYPE _type, SYMBOL _sym_type, char* _name, void *value){
    SYM_SYMBOL* sym;

    if(_sym_type != VARIABLE) return false;

    sym = lookupVariable(list, _type, _name);
    if(sym == nullptr) return false;
    if(_type != sym->type)

    if(_type == INT)
        sym->address = value;
    if(_type == INT_ARRAY){
        int *lv = (int *)sym->address;
        int *rv = (int *)value;

        for(int i=0; i < sym->size; i++)
            lv[i] = rv[i];
    }
}