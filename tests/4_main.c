
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../help.h"

long unfreed_mallocs = 0;

int main() {
	int *p = malloc(100);
	print_malloc_data(p);
	free(p);
	assert(p == NULL);
}