
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "help_readme.h"


#if CHECK_LEAKS
extern long unfreed_mallocs;
#endif


void *safe_malloc(long size, char*file_name, int line_number) {
	// always assert after malloc


	if (size == 0) { 
		printf("\nError: trying to malloc 0 bytes\n");  
		exit(1);
	} 

	if ((long) size < 0) {
		printf("\nError: malloc size may be negative, unsigned value was %li\n", (long) size);
		printf("on line %u \nin file %s\n\n", line_number, file_name);
	}

	#if CHECK_OUT_OF_BOUNDS
	size *= 2;
	#endif

	char *p = malloc(size); // char is 1 byte


	#if CHECK_LEAKS
	unfreed_mallocs++;
	#endif

	if (p == NULL) {
		printf("\n\nError: malloc of size %lu failed \n", size);
		printf("on line %u \nin file %s\n\n", line_number, file_name);
		exit(1);
	}

	if (SHOW_DEBUG) {
		printf("MALLOC %p bytes %lu ", p, size);
		printf("on line %u in file %s\n", line_number, file_name);
	}

	return (void *) p;
}


void free_null(void **pp, char*file_name, int line_number) {
	// always null after free

	if (*pp == NULL) { 
		printf("\n	You may be freeing twice\n"); 
		printf("on line %u \nin file %s\n\n", line_number, file_name);
		exit(1);
	}

	if (SHOW_DEBUG) {
		printf("FREE   %p ", pp);
		printf("on line %u in file %s\n", line_number, file_name);
	}

	free(*pp);
	*pp = NULL;

	#if CHECK_LEAKS
	unfreed_mallocs--;
	#endif
}

void free_without_null(void *pointer) {

	#if CHECK_LEAKS
	unfreed_mallocs--;
	#endif 

	free(pointer);
}




void check_memory_leaks() {
	#if CHECK_LEAKS
	if (unfreed_mallocs != 0) {
		printf("\n\n\n\nTHERE ARE MEMORY LEAKS\n\n	unfreed_mallocs == %li\n\n\n\n", unfreed_mallocs);
		exit(1);
	}
	#endif
}



