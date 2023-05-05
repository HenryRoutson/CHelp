




#include <stdlib.h>

// HELP.H REMOVED

int *external_malloc_without_help(void) {
	int *p = malloc(10);
	*p = 1;
	return p;
}