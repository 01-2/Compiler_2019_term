#include "ast.h"
#include "common.h"
#include "symtable.h"
#include <stdlib.h>
#include <stdio.h>

list l;

int main() {
	makeTable(&l, GLOBAL, "global");
	
	int i = 0;
	addElement(&l, INT, VARIABLE, "i", 0, __nullptr, &i);
	addElement(&l, INT, VARIABLE, "a", 0, __nullptr, &i);

}