

// test large / negative malloc

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../help/help.h"

long num_unfreed_mallocs = 0;

#if PRINT_UNFREED_MALLOCS
size_t num_mallocs = 0;
void *mallocs[MAX_NUM_MALLOCS];
#endif

int main(void) {

	// test large malloc failure
	int *l = malloc(-1);
	free(l);
}