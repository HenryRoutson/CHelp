
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "help_readme.h"
#include "help_structs.h"

extern long unfreed_mallocs;

#define PRINT_LOCATION printf("on line %zu \nin file %s\n\n", line_number, file_name);



void *safe_malloc(size_t size, char *file_name, size_t line_number) {
	// always assert after malloc

	assert(file_name);


	if (size == 0) { 
		printf("\nError: trying to malloc 0 bytes\n");  
		exit(1);
	} 

	if ((long) size < 0) {
		printf("\nError: malloc size may be negative, unsigned value was %li\n", (long) size);
		PRINT_LOCATION
	}

	malloc_info_t *p = malloc(sizeof(malloc_info_t) + size);
	p->file_name = file_name;
	p->line_number = line_number;
	p->message[0] = 0;
	
	p += 1;

	unfreed_mallocs++;

	if (p == NULL) {
		printf("\n\nError: malloc of size %lu failed \n", size);
		PRINT_LOCATION
		exit(1);
	}

	if (SHOW_DEBUG) {
		printf("MALLOC %p bytes %lu ", p, size);
		PRINT_LOCATION
	}

	return (void *) p;
}




void print_malloc_info(void *p) {
	malloc_info_t *info = p;
	info -= 1;

	printf("MALLOC DATA   ---\n");
	printf("file_name   : %s\n", info->file_name);
	printf("line_number : %zu\n", info->line_number);
	printf("message     : %s\n", info->message);
	printf("              ---\n");
}


malloc_info_t *info_from_malloc(void *p) {
	
	malloc_info_t *info = (malloc_info_t *) p;
	info -= 1;
	return info;
}


void free_null(void **pp, char *file_name, size_t line_number) {
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
		PRINT_LOCATION
	}


	// 

	char *free_location = *pp - sizeof(malloc_info_t);
	free(free_location);
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


