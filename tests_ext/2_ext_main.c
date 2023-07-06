


// tests using external files and num_unfreed_allocs


#include <assert.h>
#include <stdio.h>

#include "external.h" // includes all external functions

#include "../help/help.h"
CHELP_MAIN_MACRO

int main(void) {

	// test use of multiple files
	int *i = external_malloc_without_help();
	free(i);

	n_unfreed(0);
}
