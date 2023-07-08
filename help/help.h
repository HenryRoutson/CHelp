
// code by Henry Routson https://github.com/henryroutson/CHelp

#ifndef HELP
#define HELP

#include "help_readme.h"

#include "help_structs.h"

#include <stdlib.h>

// https://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html
// https://cplusplus.com/reference/cstdio/snprintf/

#if ENABLE_HELP


//                       CAN USE
void print_alloc_info(void *alloc);
void set_alloc_print_func(void *alloc, void (*print_func)(void *p));
void n_unfreed(long n_expected);
void print_all_allocs();
void track_alloc(void **p_untracked_alloc, size_t size, char *file_name, size_t line_number);

// only used in macros    DONT USE
void *safe_malloc(size_t size, char *file_name, size_t line_number);
void *safe_calloc(size_t size, size_t count, char *file_name, size_t line_number);
void *safe_realloc(void *old_alloc, size_t new_size, char *file_name, size_t line_number);
void free_without_null(void *alloc, char *file_name, size_t line_number);
void free_null(void **p_alloc, char *file_name, size_t line_number);

void add_alloc(void *alloc);
alloc_info_t *info_from_alloc(void *alloc); 

// replace macros         CAN USE  (first part)
#define malloc(size) safe_malloc(size, __FILE__, __LINE__)
#define calloc(size, count) safe_calloc(size, count, __FILE__, __LINE__)
#define free(alloc) free_null((void **)&alloc, __FILE__, __LINE__)
#define realloc(old_alloc, new_size) safe_realloc(old_alloc, new_size, __FILE__, __LINE__)

#define free_without_null(alloc) free_without_null((void *)alloc, __FILE__, __LINE__)
#define add_message_to_alloc(alloc, format_and_args...) snprintf((char *)&info_from_alloc(alloc)->message, MAX_NUM_MESSAGE_CHARS, format_and_args);
#define track_alloc(p_untracked_alloc, size) track_alloc(p_untracked_alloc, size, __FILE__, __LINE__)

// main macro - to make life easier

#if ENABLE_HELP

#define CHELP_MAIN_MACRO \
long num_unfreed_allocs = 0; \
size_t num_allocs = 0; \
void *alloc_array[MAX_NUM_MALLOCS];

#endif

#endif

#if !ENABLE_HELP

#define free_without_null(pointer) free(pointer)
#define add_message_to_alloc(p, format_and_args...)
#define print_alloc_info(alloc);
#define set_alloc_print_func(p, print_func);
#define n_unfreed(n);
#define print_all_allocs();
#define add_alloc(alloc);
#define CHELP_MAIN_MACRO
#define track_alloc(pp, size)

#endif

#endif
