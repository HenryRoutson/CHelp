


// tests using external files and num_unfreed_mallocs


#include <assert.h>
#include <stdio.h>

#include "external_1.h"
#include "../help/help.h"

long num_unfreed_mallocs = 0;

#if PRINT_UNFREED_MALLOCS
size_t num_mallocs = 0;
void *mallocs[MAX_NUM_MALLOCS];
#endif

int main(void) {

	// test use of multiple files
	tests();

	if (num_unfreed_mallocs != 0) {
		printf("TEST: PASSED\n");
	}
}
