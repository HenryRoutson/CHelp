
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "help_readme.h"
#include "globals.h"


//

#define PRINT_LOCATION printf("on line %u \nin file %s\n\n", line_number, file_name);



void *safe_malloc(long size, char*file_name, int line_number) {
	// always assert after malloc


	if (size == 0) { 
		printf("\nError: trying to malloc 0 bytes\n");  
		exit(1);
	} 

	if ((long) size < 0) {
		printf("\nError: malloc size may be negative, unsigned value was %li\n", (long) size);
		PRINT_LOCATION
	}


	void *p = malloc(size);

	unfreed_mallocs++;

	if (p == NULL) {
		printf("\n\nError: malloc of size %lu failed \n", size);
		PRINT_LOCATION
		exit(1);
	}

	if (SHOW_DEBUG) {
		printf("MALLOC %p bytes %lu ", p, size);
		printf("on line %u in file %s\n", line_number, file_name);
	}

	return p;
}


void free_null(void **pp, char*file_name, int line_number) {
	// always null after free

	if (*pp == NULL && FREE_NULL_ERROR) { 
		printf("\n	You may be freeing twice, pointer is NULL\n"); 
		PRINT_LOCATION

		printf("\n\n	exit() program, freeing nulls is not allowed"); 
		printf("\n		change this bevaviour in help_readme.h\n\n\n");
		exit(1); 
	}

	if (SHOW_DEBUG) {
		printf("FREE   %p ", pp);
		printf("on line %u in file %s\n", line_number, file_name);
	}

	free(*pp);
	*pp = NULL;

	unfreed_mallocs--;

}

void free_without_null(void *p) {

	if (p == NULL && FREE_NULL_ERROR) { 
		printf("\n	You may be freeing twice, pointer is NULL\n"); 
		printf("\n	in the free_without_null function\n"); 

		printf("\n\n	exit() program, freeing nulls is not allowed"); 
		printf("\n		change this bevaviour in help_readme.h\n\n\n");
		exit(1); 
	}

	unfreed_mallocs--;
	free(p);
}




void check_memory_leaks() {
	if (unfreed_mallocs != 0) {
		printf("\n\n\n\nTHERE ARE MEMORY LEAKS\n\n	unfreed_mallocs == %li\n\n\n\n", unfreed_mallocs);
		exit(1);
	}
}



