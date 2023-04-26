
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "help_readme.h"
#include "globals.h"


/*
typedef struct {
	size_t file_idx;
	size_t line;
	size_t mallocs;
	size_t frees;
} malloc_location_t;


extern size_t num_malloc_locations;
extern malloc_t malloc_locations_array[MAX_NUM_MALLOC_LOCATIONS];


*/


// files containing malloc
extern size_t num_files;
extern char *file_name_array[MAX_NUM_MALLOC_FILES];


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


	// Add file name

	if (num_files >= MAX_NUM_MALLOC_FILES) {
		printf("\n	You need to allocate more space for file names in help_readme.h\n\n");
		printf("#define MAX_NUM_MALLOC_FILES ...\n");
		printf("INCREASE THE VALUE HERE       ^ \n\n");
		exit(1);
	}

	size_t file_i;
	for (file_i = 0; file_i < num_files; file_i++) {
		if (strcmp(file_name_array[file_i], file_name) == 0) { // if found
			break;
		}
	}

	if (file_i == num_files) { // if didn't find, add
		file_name_array[file_i] = file_name;
		num_files++;
	}

	// Add to malloc location


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

	// Update frees on malloc location



	
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
		exit(3);
	}
	#endif
}



