
// code by Henry Routson
// Credit https://www.youtube.com/watch?v=443UNeGrFoM


#ifndef HELP
#define HELP

#include "help_readme.h"
#if ENABLE_HELP

#include <stdlib.h>
#include "help_structs.h"

//

void *safe_malloc(size_t size, char *file_name, size_t line_number);
#define malloc(size) safe_malloc(size, __FILE__, __LINE__)

void add_message_to_malloc(void *p, char *message);



void free_null(void **pp, char *file_name, size_t line_number);
#define free(pointer) free_null((void **) &pointer, __FILE__, __LINE__ )

void free_without_null(void *pointer);

malloc_info_t *info_from_malloc(void *p);

void print_malloc_info(void *p);
void add_print_func_to_malloc(void *p, void (*print_func)(void *p));
void print_func_malloc(void *p);

void assert_n_unfreed_mallocs(size_t n);
void print_all_mallocs();

// https://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html
// https://cplusplus.com/reference/cstdio/snprintf/

#define add_message_to_malloc(p, format_str, format_args...) \
				snprintf((char *) &info_from_malloc(p)->message, MAX_NUM_MESSAGE_CHARS, format_str, format_args);


#endif
#endif
