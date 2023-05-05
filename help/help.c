
// code by Henry Routson https://github.com/henryroutson/CHelp

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "help_readme.h"
#include "help_structs.h"

#define PRINT_LOCATION \
  printf("on line %zu \nin file %s\n\n", line_number, file_name);
#define PRINT_HEADER \
  printf("#include \"help/help.h\"");

//
// --------------------------------
// Sub Functions
//


void check_null(void *p, char *file_name, size_t line_number) {
  if (p == NULL && FREE_NULL_ERROR) {
    printf("\n	You may be freeing twice, pointer is NULL\n");
    PRINT_LOCATION

    printf("\n\n	exit() program, freeing nulls is not allowed");
    printf("\n		change this bevaviour in help_readme.h\n\n\n");
    exit(1);
  }
}

void check_malloc_is_saved(void *p) {
  for (size_t i = 0; i < num_mallocs; i++) {
    if (p == mallocs[i]) { return; }
  }

  // not in mallocs array
  // file with malloc doesn't contain help.h header

  printf("Error: malloc being freed cannot be found in array");
  printf("  Make sure all files contain the header\n");
  PRINT_HEADER

}

malloc_info_t *info_from_malloc(void *p) {

  check_malloc_is_saved(p);

  assert(p);

  malloc_info_t *info = (malloc_info_t *)p;
  info -= 1;
  return info;
}

void check_pos_unfreed() {

  if (num_unfreed_mallocs < 0) {
    printf("Error: Unfreed_mallocs < 0");
    printf("  There are mallocs in files where the include statement is missing\n");
    PRINT_HEADER
    exit(1);
  }
}



//
// --------------------------------
// #define MACRO functions
// (not called directly)

void *safe_malloc(size_t size, char *file_name, size_t line_number) {
  // always assert after malloc

  assert(file_name);

  if (size == 0) {
    printf("\nError: trying to malloc 0 bytes\n");
    exit(1);
  }

  if ((long)size < 0) {
    printf("\nError: malloc size may be negative, unsigned value was %li\n",
           (long)size);
    PRINT_LOCATION
  }

  malloc_info_t *p = malloc(sizeof(malloc_info_t) + size);

  p->file_name = file_name;
  p->line_number = line_number;
  p->size = size;
  p->message[0] = 0;
  p->print_func = NULL;


  p->mallocs_index = num_mallocs;


  p += 1;


  assert(num_mallocs < MAX_NUM_MALLOCS);
  mallocs[num_mallocs] = p;
  num_mallocs++;

  num_unfreed_mallocs++;

  if (p == NULL) {
    printf("\n\nError: malloc of size %lu failed \n", size);
    PRINT_LOCATION
    exit(1);
  }

  if (PRINT_MALLOC_AND_FREE) {
    printf("MALLOC %p bytes %lu ", (void *)p, size);
    PRINT_LOCATION
  }

  return (void *)p;
}

void free_null(void **pp, char *file_name, size_t line_number) {
  // always null after free
  assert(pp);

  void *p = *pp;

  check_null(p, file_name, line_number);

  if (PRINT_MALLOC_AND_FREE) {
    printf("FREE   %p ", p);
    PRINT_LOCATION
  }

  num_unfreed_mallocs--;
  check_pos_unfreed();

  malloc_info_t *info = info_from_malloc(p);

  if (info->mallocs_index >= MAX_NUM_MALLOCS) {
    printf("Error: mallocs_index is not valid");
    exit(1);
  }

  mallocs[info->mallocs_index] = NULL;

  free(info);
  *pp = NULL;


}

//
// --------------------------------
// Called functions
//

void print_func_malloc(void *p) {
#if ENABLE_HELP

  malloc_info_t *info = info_from_malloc(p);
  (*info->print_func)(p);

#endif
}

void print_malloc_info(void *p) {
#if ENABLE_HELP

  if (p == NULL) {
    printf("  FREED       ---\n");
    return;
  }

  malloc_info_t *info = info_from_malloc(p);
  assert(MAX_NUM_MESSAGE_CHARS != 0);

  printf("UNFREED       ---\n");
  printf("file_name   : %s\n", info->file_name);
  printf("line_number : %zu\n", info->line_number);

  if (info->message[0]) {
    printf("message     : \n%s", info->message);
  }
  if (info->print_func) {
    printf("print_func  : \n");
    (*info->print_func)(p);
  }

  printf("              ---\n");

#endif
}

void add_print_func_to_malloc(void *p, void (*print_func)(void *p)) {
#if ENABLE_HELP

  if (!print_func) {
    printf("Error: NULL function passed into add_print_func_to_malloc");
    exit(1);
  }
  malloc_info_t *info = info_from_malloc(p);

  if (info->print_func) {
    printf("Error: overwriting print function in add_print_func_to_malloc (function already set)");
    exit(1);
  }

  info->print_func = print_func;

#endif
}

void free_without_null(void *p, char *file_name, size_t line_number) {

#if ENABLE_HELP

  check_null(p, file_name, line_number);

  num_unfreed_mallocs--;
  check_pos_unfreed();


  check_malloc_is_saved(p);


#endif

  free(p);
}


void print_all_mallocs(void) {
  assert(num_mallocs > 0);
  int i = num_mallocs;

  while (i--) { // print reverse
    print_malloc_info(mallocs[i]);
  }
}


void assert_n_unfreed_mallocs(long n) {
#if ENABLE_HELP

  if (n != num_unfreed_mallocs) {

    printf("\n\nERROR: wrong number of unfreed mallocs\n");
    printf("	expected : %zu\n", n);
    printf("	found    : %zu\n\n", num_unfreed_mallocs);
    printf("\n");
    printf("	mallocs are listed below,\n	in reverse allocation order\n");

    print_all_mallocs();

    printf("\n\n");

    exit(0);
  }

#endif
}
