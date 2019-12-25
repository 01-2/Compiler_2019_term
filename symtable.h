#include "common.h"

typedef struct symSymbol{
    char* name;
    enum TYPE type;
    enum SYMBOL sym_type;
    void* address;
    int size;
    int initialized;

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
    struct _list* prev;
    SYM_TABLE* table;
}list;

SYM_TABLE* createTable(TABLE _type, char* _name);
SYM_SYMBOL* createSymbol(TYPE _type, SYMBOL _sym_type, char* _name, int _param_cnt, TYPE* _param_types, int _size, void* _address);
int addList(list* current, list* prev);
SYM_SYMBOL* lookupVariable(list* list, TYPE _type, char* _name);
SYM_SYMBOL* lookupFunction(list* list, TYPE _type, char* _name, int _param_cnt, TYPE* _params);

void makeTable(list* list, TABLE _type, char* _name);
int addElement(list* list, TYPE _type, SYMBOL _sym_type, char* _name, int _param_cnt, TYPE* _param_types, int _size, void* _address);
int modifyElement(list* list, TYPE _type, SYMBOL _sym_type, char* _name, void* value);