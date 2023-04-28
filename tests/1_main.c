

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


	// test num_unfreed_mallocs
	int *p = malloc(1);
	int *c = malloc(1);
	assert(num_unfreed_mallocs == 2);
	free(p);
	assert(num_unfreed_mallocs == 1);
	free(c);
	assert(num_unfreed_mallocs == 0);

	// test nulled memory
	int *n;
	n = malloc(1);
	assert(num_unfreed_mallocs == 1);
	free(n);
	assert(num_unfreed_mallocs == 0);
	assert(!n);

	// test large malloc failure
	int *l = malloc(-1);
	free(l);
}