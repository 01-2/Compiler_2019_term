#define SYM_TABLE_MAX 500
#define SYM_TABLE_MAX 500

typedef struct symSymbol{
    char* name;
    TYPE type;
    SYMBOL sym_type;
    void* address;

    int param_cnt;
    char **param_types;
} SYM_SYMBOL;

typedef struct symTable{
    TABLE type;
    char* name;

    SYM_SYMBOL* child;
    int child_cnt;
} SYM_TABLE;

typedef struct _list{
    _list* prev;
    SYM_TABLE table;
}list;

int createTable(TABLE type, char* name);
int createSymbol(TYPE *type, SYMBOL sym_type, char* name, int _param_cnt, char** param_types);
int addList(list* current, list* prev);
void* lookupVariable(list* list,  SYMBOL type, char *name,);
void* lookupFunction(list* list, TYPE _type, char* _name);