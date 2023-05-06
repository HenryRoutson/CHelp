

// test large / negative malloc

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../help/help.h"

#if ENABLE_HELP
long num_unfreed_allocs = 0;
size_t num_allocs = 0;
void *allocs[MAX_NUM_MALLOCS];
#endif

int main(void) {

	// test large malloc failure
	int *l = malloc(-1);
	free(l);
}