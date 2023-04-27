

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../help.h"

long unfreed_mallocs = 0;

int main() {

	// test unfreed_mallocs errors
	int *p = malloc(1);
	*p = 10;

	if (unfreed_mallocs != 0) {
		printf("TEST: PASSED");
	}
}