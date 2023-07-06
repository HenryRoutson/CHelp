
// tests num_unfreed_allocs

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../help/help.h"
CHELP_MAIN_MACRO

int main(void) {

	// test num_unfreed_allocs
	int *p = malloc(1);
	int *c = calloc(1,1);
	n_unfreed(2);
	free(p);
	n_unfreed(1);
	free(c);
	n_unfreed(0);

	// test nulled memory
	int *n;
	n = malloc(1);
	n_unfreed(1);
	free(n);

	n_unfreed(0);

	printf("TEST: PASSED\n");
	
}