




#include <stdlib.h>

#include "../help/help.h"

int *external_malloc(void) {
	int *p = malloc(10);
	*p = 1;
	return p;
}