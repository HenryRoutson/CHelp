

// test num_unfreed_allocs

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../help/help.h"

long num_unfreed_allocs = 0;
size_t num_allocs = 0;
void *allocs[MAX_NUM_MALLOCS];


int main(void) {

	// test num_unfreed_allocs errors
	int *p = malloc(1);
	*p = 10;

	assert_n_unfreed_allocs(0);
}