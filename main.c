#include "ast.h"
#include "common.h"
#include "symtable.h"
#include <stdlib.h>
#include <stdio.h>

list l;

int main() {
	makeTable(&l, GLOBAL, "global");
	
	int i = 0, c[10] = {0,}, d[10] = {1,};
	addElement(&l, INT, VARIABLE, "i", 0, nullptr, 0, &i);
	addElement(&l, INT, VARIABLE, "a", 0, nullptr, 0, &i);
	addElement(&l, INT, VARIABLE, "i", 0, nullptr, 0, &i);
    addElement(&l, INT_ARRAY, VARIABLE, "c", 0, nullptr, sizeof(c) / sizeof(int), &c);
    modifyElement(&l, INT_ARRAY, VARIABLE, "c", &d);

}