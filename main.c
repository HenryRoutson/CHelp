

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "help.h"

unsigned long unfreed_mallocs = 0;

int main() {




	// test large malloc failure
	/*
	int *p = malloc(-1);
	free(p);
	*/

	// test unfreed_mallocs
	/*
	int *p;
	p = malloc(1);
	p = malloc(1);
	free(p);
	*/



	
	// test nulled memory
	/*
	int *p;
	p = malloc(1);
	free(p);
	assert(!p);
	*/
	
	


	check_memory_leaks();
}