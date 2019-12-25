#ifndef COMMON_H
#define COMMON_H

#define nullptr ((void *)0)
#define true 1
#define false 0

// type enum;
typedef enum TYPE { INT, INT_ARRAY, VOID }TYPE;

// symbol type enum
typedef enum SYMBOL{ VARIABLE, FUNCTION, IF, WHILE, ELSE }SYMBOL;

// table type enum
typedef enum TABLE{ GLOBAL, T_FUNCTION, T_IF, T_WHILE, T_ELSE}TABLE;

#endif