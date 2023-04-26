

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "help.h"

long unfreed_mallocs = 0;

int main() {


	// test large malloc failure
	/*
	int *p = malloc(-1);
	free(p);
	*/

	// test unfreed_mallocs

	int *p;
	p = malloc(1);
	printf("\n%zu\n", unfreed_mallocs);
	p = malloc(1);
	printf("\n%zu\n", unfreed_mallocs);
	free(p);
	printf("\n%zu\n", unfreed_mallocs);




	
	// test nulled memory
	/*
	int *p;
	p = malloc(1);
	free(p);
	assert(!p);
	*/
	
	

	printf("\n%zu\n", unfreed_mallocs);
	check_memory_leaks();
}