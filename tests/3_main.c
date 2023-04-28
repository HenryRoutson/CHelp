
#include <assert.h>
#include <stdio.h>

#include "3_external.h"
#include "../help.h"

long num_unfreed_mallocs = 0;

int main() {

	// test use of multiple files
	tests();

	if (num_unfreed_mallocs != 0) {
		printf("TEST: PASSED\n");
	}
}
