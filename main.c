

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "help.h"

long unfreed_mallocs = 0;

int main() {


	// test unfreed_mallocs
	int *p = malloc(1);
	int *c = malloc(1);
	assert(unfreed_mallocs == 2);
	free(p);
	assert(unfreed_mallocs == 1);
	free(c);
	assert(unfreed_mallocs == 0);

	// test nulled memory
	int *n;
	n = malloc(1);
	free(n);
	assert(!n);

	// test large malloc failure
	int *l = malloc(-1);
	free(l);
}