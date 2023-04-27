
// code by Henry Routson
// Credit https://www.youtube.com/watch?v=443UNeGrFoM


#ifndef HELP
#define HELP

#include "help_readme.h"
#if ENABLE_HELP

#include <stdlib.h>

// define functions to help with development and debugging

void *safe_malloc(size_t size, char *file_name, size_t line_number);
#define malloc(size) safe_malloc(size, __FILE__, __LINE__)

/*
void *attach_message(void **p, char *message);
#define attach_message(void **p, char *message) attach_message(void **p, char *message, __FILE__, __LINE__)
*/


void add_message_to_malloc(void *p, char *message);
void print_malloc_data(void *p);


void free_null(void **pp, char *file_name, size_t line_number);
#define free(pointer) free_null((void **) &pointer, __FILE__, __LINE__ )

void free_without_null(void *pointer);

extern long unfreed_mallocs;

#endif
#endif
