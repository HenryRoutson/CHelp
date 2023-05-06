
// code by Henry Routson https://github.com/henryroutson/CHelp

#ifndef HELP
#define HELP

#include "help_readme.h"

#include "help_structs.h"

#include <stdlib.h>

// https://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html
// https://cplusplus.com/reference/cstdio/snprintf/

#if ENABLE_HELP

alloc_info_t *info_from_alloc(void *p);
void *safe_malloc(size_t size, char *file_name, size_t line_number);
void *safe_calloc(size_t size, size_t count, char *file_name, size_t line_number);
void add_message_to_alloc(void *p, char *message);
void free_null(void **pp, char *file_name, size_t line_number);
void free_without_null(void *pointer, char *file_name, size_t line_number);
void print_alloc_info(void *p);
void add_print_func_to_alloc(void *p, void (*print_func)(void *p));
void print_func_alloc(void *p);
void n_unfreed(long n);
void print_all_allocs();


// replace macro
#define malloc(size) safe_malloc(size, __FILE__, __LINE__)
#define calloc(size, count) safe_calloc(size, count, __FILE__, __LINE__)
#define free(pointer) free_null((void **)&pointer, __FILE__, __LINE__)
#define free_without_null(pointer) free_without_null((void **)&pointer, __FILE__, __LINE__)
#define add_message_to_alloc(p, format_and_args...) snprintf((char *)&info_from_alloc(p)->message, MAX_NUM_MESSAGE_CHARS, format_and_args);

#endif

#if !ENABLE_HELP

// remove macro
#define free_without_null(pointer)
#define add_message_to_alloc(p, format_and_args...)
#define info_from_alloc(p);
#define free_null(pp);
#define print_alloc_info(p);
#define add_print_func_to_alloc(p, print_func);
#define print_func_alloc(p);
#define n_unfreed(n);
#define print_all_allocs();

#endif

#endif
