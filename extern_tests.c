
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "help.h"
#include "globals.h"

void tests() {

	assert(unfreed_mallocs == 0);
	
	void *pointer = malloc(sizeof(char));
	assert(unfreed_mallocs == 1);
	free(pointer);

	assert(unfreed_mallocs == 0);
}