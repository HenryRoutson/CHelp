
#include <assert.h>
#include <stdio.h>

#include "3_external.h"
#include "../help.h"

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
