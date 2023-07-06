

// test num_unfreed_allocs

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../help/help.h"
CHELP_MAIN_MACRO

int main(void) {

	// test num_unfreed_allocs errors
	int *p = malloc(1);
	*p = 10;

	n_unfreed(0); // will fail
}