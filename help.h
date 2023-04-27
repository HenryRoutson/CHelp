
// code by Henry Routson
// Credit https://www.youtube.com/watch?v=443UNeGrFoM


#ifndef HELP
#define HELP

#include "help_readme.h"
#if ENABLE_HELP

// define functions to help with development and debugging

void free_null(void **pp, char*file_name, int line_number);
#define free(pointer) free_null((void **) &pointer, __FILE__, __LINE__ )

void free_without_null(void *pointer);

void *safe_malloc(unsigned long size, char*file_name, int line_number);
#define malloc(size) safe_malloc(size, __FILE__, __LINE__)

#endif
#endif
