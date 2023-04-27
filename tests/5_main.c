
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../help.h"

long unfreed_mallocs = 0;

int main() {
	int *p = malloc(100);


	
	add_message_to_malloc(p, "TEST: PASSED");
	print_malloc_data(p); // test

	free(p);
	assert(p == NULL);
}