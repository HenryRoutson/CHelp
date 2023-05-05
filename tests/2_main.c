

// test num_unfreed_mallocs

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../help/help.h"

long num_unfreed_mallocs = 0;
size_t num_mallocs = 0;
void *mallocs[MAX_NUM_MALLOCS];


int main(void) {

	// test num_unfreed_mallocs errors
	int *p = malloc(1);
	*p = 10;

	assert_n_unfreed_mallocs(0);
}