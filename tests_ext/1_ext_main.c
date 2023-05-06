


// tests using external files and num_unfreed_allocs


#include <assert.h>
#include <stdio.h>

#include "external.h" // includes all external functions

#include "../help/help.h"

#if ENABLE_HELP
long num_unfreed_allocs = 0;
size_t num_allocs = 0;
void *allocs[MAX_NUM_MALLOCS];
#endif

int main(void) {

	// test use of multiple files
	external_malloc();

	n_unfreed(1);

	printf("TEST: PASSED\n");
	
}
