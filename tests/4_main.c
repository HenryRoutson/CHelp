


// tests free null



#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../help/help.h"
CHELP_MAIN_MACRO

int main(void) {
	int *p = malloc(100);
	print_alloc_info(p); // test
	free(p);
	
	#if ENABLE_HELP
	assert(p == NULL);
	#endif

	#if !ENABLE_HELP
	assert(p != NULL);
	#endif
}