


// tests free null



#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../help/help.h"

long num_unfreed_allocs = 0;
size_t num_allocs = 0;
void *allocs[MAX_NUM_MALLOCS];


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