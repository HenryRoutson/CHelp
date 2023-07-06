
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
void print_alloc_info(void *p);
void set_alloc_print_func(void *p, void (*print_func)(void *p));
void n_unfreed(long n);
void print_all_allocs();

// only used in macros    DONT USE
void add_alloc(void *p);
alloc_info_t *info_from_alloc(void *p); 
void *safe_malloc(size_t size, char *file_name, size_t line_number);
void *safe_calloc(size_t size, size_t count, char *file_name, size_t line_number);
void free_without_null(void *pointer, char *file_name, size_t line_number);
void free_null(void **pp, char *file_name, size_t line_number);

// replace macros         CAN USE  (first part)
#define malloc(size) safe_malloc(size, __FILE__, __LINE__)
#define calloc(size, count) safe_calloc(size, count, __FILE__, __LINE__)
#define free(pointer) free_null((void **)&pointer, __FILE__, __LINE__)
#define free_without_null(pointer) free_without_null((void *)pointer, __FILE__, __LINE__)
#define add_message_to_alloc(p, format_and_args...) snprintf((char *)&info_from_alloc(p)->message, MAX_NUM_MESSAGE_CHARS, format_and_args);

#endif

#if !ENABLE_HELP

#define free_without_null(pointer) free(pointer)
#define add_message_to_alloc(p, format_and_args...)
#define print_alloc_info(p);
#define set_alloc_print_func(p, print_func);
#define n_unfreed(n);
#define print_all_allocs();
#define add_alloc();

#endif

#endif
