#ifndef COMMON_H
#define COMMON_H

#define nullptr ((void *)0)
#define true 1
#define false 0


typedef struct vector {
	void* data;
	size_t size;
	size_t capacity;
}vector;

typedef struct linked_list_node {
	void* data;
	struct linked_list_node* next;
};

struct linked_list {
	struct linked_list_node* start;
	struct linked_list_node* end;
};


int current_line;

// type enum;
typedef enum TYPE { INT, INT_ARRAY, VOID }TYPE;

// symbol type enum
typedef enum SYMBOL{ VARIABLE, FUNCTION, IF, WHILE, ELSE }SYMBOL;

// table type enum
typedef enum TABLE{ GLOBAL, T_FUNCTION, T_IF, T_WHILE, T_ELSE}TABLE;

void error_handle(char *msg);

#endif