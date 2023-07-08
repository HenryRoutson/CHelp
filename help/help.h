
// code by Henry Routson https://github.com/henryroutson/CHelp

#ifndef HELP
#define HELP

#include <stdlib.h>

#include "help_readme.h"
#include "help_structs.h"

#if ENABLE_HELP




//
//
// PLEASE NOTE: some functions include char *file_name, size_t line_number as parameters
//              these are added by macros and you can ignore them
//
//







void print_alloc_info(void *alloc);
/**
 * @brief prints all stored info about allocation
 * @see test 4 https://github.com/HenryRoutson/CHelp/blob/main/tests/4_main.c
 * 
 *        UNFREED       ---
 *        file_name   : tests/4_main.c
 *        line_number : 22
 *        size: 100
 */







void set_alloc_print_func(void *alloc, void (*print_func)(void *p));
/**
 * @brief set a custom print function to an allocation
 * @see test 6 https://github.com/HenryRoutson/CHelp/blob/main/tests/6_main.c
 * 
 * 
 *      UNFREED       ---
 *      file_name   : tests/6_main.c
 *      line_number : 29
 *      size: 24
 *      print_func  : 
 *      1 2 3.000000
 * 
 */







void n_unfreed(long n_expected);
/**
 * @brief  checks there are n unfreed allocations, prints error and exits if fails
 * @see test 9 https://github.com/HenryRoutson/CHelp/blob/main/tests/9_main.c
 * 
 * 
 * 
 *      Error: wrong number of unfreed allocs
 * 
 *              expected : 0
 *              found    : 1
 * 
 *              allocs are listed below,
 *              in reverse allocation order
 * 
 * 
 */







void print_all_allocs();
/**
 * @brief prints info from all allocations
 * 
 *      >>> print_all_allocs() 
 *      UNFREED       ---
 *      file_name   : tests/9_main.c
 *      line_number : 36
 *      size: 24
 *      print_func  : 
 *      1 s2 3.000000
 *                  ---
 *      FREED       ---
 *      >>> 
 * 
 */







void free_without_null(void *alloc, char *file_name, size_t line_number);
/**
 * @brief pointer to be freed isn't stored, and cannot be nulled: free_without_null(echo(p));
 * @see test 12  https://github.com/HenryRoutson/CHelp/blob/main/tests/12_main.c
 */







void add_message_to_alloc(void *alloc, char *format_string, ...); // purely for demonstration
/**
 * @brief Allows adding formatted message to allocation, works like printf
 * @see test 5 https://github.com/HenryRoutson/CHelp/blob/main/tests/5_main.c
 * 
 *    Note: function prototype is not in use, macro is used
 * 
 *    add_message_to_alloc(p,  "This is a number: %i\n", 10);
 * 
 *    UNFREED       ---
 *    file_name   : tests/5_main.c
 *    line_number : 19
 *    size: 100
 *    message     : 
 *    This is a number: 10
 */







void track_alloc(void **p_untracked_alloc, size_t size, char *file_name, size_t line_number);
/**
 * @brief Track allocations like strdup which use implicit allocation
 * @see test 0 https://github.com/HenryRoutson/CHelp/blob/main/tests/0_main.c
 * 
 *            implicit allocations
 * 
 *  These are functions which return a pointer allocated with malloc or calloc
 *  which the chelp library macros cannot override because the library code is already compiled
 *  For example strdup() duplicates a string, 
 *  returing a pointer to memory which needs to be freed
 * 
 *                ------------
 * 
 *  Note: if you really don't know how large the allocation is, the size only has to be larger than it, so just make it really big
 * 
 * 
 * Example: 
 * 
 * 
 *        char *alloc = strdup(string);
 *        track_alloc(&alloc, n_string_bytes); 
 * 
 */
































// IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE 
// IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE 
// IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE 















// function definitions

void *safe_malloc(size_t size, char *file_name, size_t line_number);
void *safe_calloc(size_t size, size_t count, char *file_name, size_t line_number);
void *safe_realloc(void *old_alloc, size_t new_size, char *file_name, size_t line_number);
void free_null(void **p_alloc, char *file_name, size_t line_number);
void add_alloc(void *alloc);
alloc_info_t *info_from_alloc(void *alloc); 




// replace macros
// Note: https://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html

#define malloc(size) safe_malloc(size, __FILE__, __LINE__)
#define calloc(size, count) safe_calloc(size, count, __FILE__, __LINE__)
#define free(alloc) free_null((void **)&alloc, __FILE__, __LINE__)
#define realloc(old_alloc, new_size) safe_realloc(old_alloc, new_size, __FILE__, __LINE__)
#define free_without_null(alloc) free_without_null((void *)alloc, __FILE__, __LINE__)
#define add_message_to_alloc(alloc, format_and_args...) snprintf((char *)&info_from_alloc(alloc)->message, MAX_NUM_MESSAGE_CHARS, format_and_args);
#define track_alloc(p_untracked_alloc, size) track_alloc((void **) p_untracked_alloc, size, __FILE__, __LINE__)





// main macro - to make life easier

#define CHELP_MAIN_MACRO \
long num_unfreed_allocs = 0; \
size_t num_allocs = 0; \
void *alloc_array[MAX_NUM_MALLOCS];

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
