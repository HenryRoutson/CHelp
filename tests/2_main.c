

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../help.h"

long num_unfreed_mallocs = 0;

#if PRINT_UNFREED_MALLOCS
size_t num_mallocs = 0;
void *mallocs[MAX_NUM_MALLOCS];
#endif

int main() {

	// test num_unfreed_mallocs errors
	int *p = malloc(1);
	*p = 10;

	if (num_unfreed_mallocs != 0) {
		printf("TEST: PASSED\n");
	}
}