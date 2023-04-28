

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../help.h"

long num_unfreed_mallocs = 0;

int main() {

	// test num_unfreed_mallocs errors
	int *p = malloc(1);
	*p = 10;

	if (num_unfreed_mallocs != 0) {
		printf("TEST: PASSED\n");
	}
}