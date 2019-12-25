#include <stdio.h>
#include <stdlib.h>
#include "common.h"

void error_handle(char* str) {
	printf("%s", str);
	exit(1);
}