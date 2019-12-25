#include "ast.h"
#include "common.h"
#include "symtable.h"
#include <stdlib.h>
#include <stdio.h>

list l;

int main() {
	makeTable(&l, GLOBAL, "global");
	
	int i = 0, c[10] = {1,2, 3, 4, 5, 6, 7, 8, 9, 10}, d[10] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
	addElement(&l, INT, VARIABLE, "i", 0, nullptr, 0, &i);
	addElement(&l, INT, VARIABLE, "a", 0, nullptr, 0, &i);
	addElement(&l, INT, VARIABLE, "i", 0, nullptr, 0, &i);
    addElement(&l, INT_ARRAY, VARIABLE, "c", 0, nullptr, 10, &c);
    modifyElement(&l, INT_ARRAY, VARIABLE, "c", &d);

    addElement(&l, INT, FUNCTION, "func", 0, nullptr, 0, nullptr);
    SYM_SYMBOL *addr = lookupFunction(&l, INT, "func", 0, nullptr);
    addElement(&addr->address, INT, VARIABLE, "i", 0, nullptr, 0, &i);

    for(int i = 0 ; i < 10; i++) {
        int *p =

        printf("%d\n", p[i]);
    }

    return 0;
}