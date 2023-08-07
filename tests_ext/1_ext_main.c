


// tests using external files and num_unfreed_allocs


#include <assert.h>
#include <stdio.h>

#include "external.h" // includes all external functions

#include "../help/help.h"
CHELP_MAIN_MACRO

int main(void) {

	// test use of multiple files
	void * i = external_malloc();
  printf("%p\n", i );

	n_unfreed(1);
  free(i);
  n_unfreed(0);

	printf("TEST: PASSED\n");
	
}
