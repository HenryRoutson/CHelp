
// tests num_unfreed_mallocs

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../help/help.h"

long num_unfreed_mallocs = 0;
size_t num_mallocs = 0;
void *mallocs[MAX_NUM_MALLOCS];

int main(void) {


	// test num_unfreed_mallocs
	int *p = malloc(1);
	int *c = malloc(1);
	assert_n_unfreed_mallocs(2);
	free(p);
	assert_n_unfreed_mallocs(1);
	free(c);
	assert_n_unfreed_mallocs(0);

	// test nulled memory
	int *n;
	n = malloc(1);
	assert_n_unfreed_mallocs(1);
	free(n);
	
	if (num_unfreed_mallocs == 0) {
		printf("TEST: PASSED\n");
	}
}