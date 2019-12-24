#include "common.h"


typedef struct symSymbol{
    char* name;
    enum TYPE type;
    enum SYMBOL sym_type;
    void* address;

    int param_cnt;
    enum TYPE* param_types;
} SYM_SYMBOL;

typedef struct symTable{
    enum TABLE type;
    char* name;

    SYM_SYMBOL** child;
    int child_cnt;
} SYM_TABLE;

typedef struct _list{
    list* prev;
    SYM_TABLE* table;
}list;

SYM_TABLE* createTable(enum TABLE _type, char* _name);
SYM_SYMBOL* createSymbol(enum TYPE _type, enum SYMBOL _sym_type, char* _name, int _param_cnt, enum TYPE* _param_types, void* _address);
int addList(list* current, list* prev);
void* lookupVariable(list* list, enum SYMBOL type, char *name);
void* lookupFunction(list* list, enum TYPE _type, char* _name);

void makeTable(list* list, enum TABLE _type, char* _name);
int addElement(list* list, enum TYPE _type, enum SYMBOL _sym_type, char* _name, int _param_cnt, enum TYPE* _param_types, void* _address);