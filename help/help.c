
// code by Henry Routson https://github.com/henryroutson/CHelp


/*
Notes

       | Allocation |    is replaced by
       ^ start

| Info | Allocation |
^ start

Where info stores information about the allocation

The two important names

Info       : pointer to meta information about an allocation
Allocation : pointer to allocation memory actually being used by the running program

It is possible for Info to be stored after the Allocation,
but this would increase the possibility of the info being overwritten with something like a dynamic array, and it also makes reallocation easier, as info stays in the same location

| Info | Allocation |
| Info |       Allocation       |

but freeing becomes more complex because the pointer to the start of the allocation is not the same as the actual start of the allocation, which is the Info.

*/


#include "help_config.h"
#if ENABLE_HELP

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define VERIFICATION 123456789 // some unlikely number to verify an allocation has info

/* a bit of a hack 
  but i just need a unique address 
  kind of cool how efficient this is */

#include "help_structs.h"

#define PRINT_LOCATION \
  printf("on line %zu \nin file %s\n\n", line_number, file_name);

//
// --------------------------------
// Sub Functions
//


void add_alloc(void *alloc) {

    assert(num_allocs < MAX_NUM_MALLOCS);
    alloc_array[num_allocs] = alloc;

    num_allocs++;
    num_unfreed_allocs++;
}


void check_not_null(void *alloc, char *file_name, size_t line_number) {

  // free_null will set alloc to null on free

  if (alloc == NULL && FREE_NULL_ERROR) {
    printf("\n	You may be freeing twice, pointer is NULL\n");
    PRINT_LOCATION

    printf("\n\n	exit() program, freeing nulls is not allowed");
    printf("\n		change this bevaviour in help_config.h\n\n\n");
    exit(1);
  }
}


alloc_info_t *info_from_alloc(void *alloc) {

  assert(alloc);

  alloc_info_t *info = ((alloc_info_t *) alloc) - 1;

  if (info->verification != VERIFICATION) {
    printf("Error 11: Invalid verification number\n");
    printf("          Trying to get information about allocation, but non is there\n");
    printf("          You might have passed in the wrong allocation\n");
    exit(1);
  }

  assert(info->allocs_index < MAX_NUM_MALLOCS); // if fails, chelp bug
  return info;
}

void check_pos_unfreed() {

  if (num_unfreed_allocs < 0) {
    printf("Error 1: Unfreed_allocs < 0\n");
    printf("\n");
    printf("    There are allocs in files where #include is missing\n");
    printf("        Fix: #include #include \"../help/help.h\" // path to help.h \n\n");
    printf("  OR\n\n");
    printf("    There are implicit allocations, such as with strdup().\n");
    printf("    search implicit allocations in help_config.h if you have tried the other options.\n");
    printf("        Fix: void track_alloc(void **p_untracked_alloc, size_t size)\n");
    exit(1);
  } 
}

void free_without_null(void *alloc, char *file_name, size_t line_number) {

  check_not_null(alloc, file_name, line_number);

  if (PRINT_ALLOC_AND_FREE) {
    printf("FREE   %p ", alloc);
    PRINT_LOCATION
  }

  num_unfreed_allocs--;
  check_pos_unfreed();

  alloc_info_t *info = info_from_alloc(alloc);
  alloc_array[info->allocs_index] = NULL;

  free(info);

}

void *init_info(alloc_info_t *info, size_t size, size_t count_if_calloc, char *file_name, size_t line_number) {

  if (info == NULL) { // as called after allocations 
    printf("\n\nError 4: alloc of size %lu and count %lu (0 if calloc) failed \n", size, count_if_calloc);
    PRINT_LOCATION
    exit(1);
  }

  info->verification = VERIFICATION;
  info->file_name = file_name;
  info->line_number = line_number;
  info->size = size;
  info->realloc_count = 0;
  info->count_if_calloc = count_if_calloc;
  info->message[0] = 0; // NULL end string
  info->print_func = NULL;
  info->allocs_index = num_allocs;

  void *alloc = info + 1; // go to start of allocated memory, ignoring data stored before it

  add_alloc(alloc);

  if (PRINT_ALLOC_AND_FREE) {
    printf("ALLOC %p bytes %lu ", alloc, size);
    PRINT_LOCATION
  }

  return alloc;
}


void track_alloc(void **p_untracked_alloc, size_t size, char *file_name, size_t line_number) {

  alloc_info_t *info = malloc(size + sizeof(alloc_info_t));
  init_info(info, size, 0, file_name, line_number);

  void *tracked_alloc = info + 1;
  memcpy(tracked_alloc, *p_untracked_alloc, size);
  free(*p_untracked_alloc);

  *p_untracked_alloc = tracked_alloc;
}



size_t min2(size_t n1, size_t n2) {
  if (n1 > n2) { return n2; }
  return n1;
}


void *safe_realloc(void *old_alloc, size_t new_size, char *file_name, size_t line_number) {


  alloc_info_t *old_info = info_from_alloc(old_alloc);
  size_t old_size = old_info->size;

  alloc_info_t *new_info = malloc(new_size + sizeof(alloc_info_t));

  // realloc can reduce or increase the size of an allocation
  memcpy(new_info, old_info, sizeof(alloc_info_t) + min2(old_size, new_size));
  new_info->size = new_size;
  new_info->realloc_count ++;

  free(old_info);

  void *new_alloc = new_info + 1;

  if (PRINT_ALLOC_AND_FREE) {
    printf("REALLOC %p > %p bytes %lu ", old_alloc, new_alloc, new_size);
    PRINT_LOCATION
  }

  return new_alloc;
}


void *safe_malloc(size_t size, char *file_name, size_t line_number) {
  // always assert after malloc

  assert(file_name);

  if (size == 0) {
    printf("\nError 2: trying to malloc 0 bytes\n");
    exit(1);
  }

  if ((long)size < 0) {
    printf("\nError 3: malloc size may be negative, unsigned value was %li\n",
           (long)size);
    PRINT_LOCATION
  }

  alloc_info_t *info = malloc(sizeof(alloc_info_t) + size);
  void *alloc = init_info(info, size, 0, file_name, line_number);
  return alloc;
}


void *safe_calloc(size_t size, size_t count, char *file_name, size_t line_number) {
  // always assert after malloc

  assert(file_name);

  if (size == 0 || count == 0) {
    printf("\nError 5: trying to calloc 0 bytes\n");
    printf(" size: %lu, count: %lu\n", size, count);
    exit(1);
  }

  if ((long)size < 0 || (long)count < 0) {
    printf("\nError 6: calloc size may be negative");
    printf(" size: %lu, count: %lu\n", (long)size, (long)count);
    PRINT_LOCATION
  }

  alloc_info_t *info = malloc(sizeof(alloc_info_t) + size * count);
  void *alloc = init_info(info, size, count, file_name, line_number);
  memset(alloc, 0, sizeof(size * count));
  return alloc;
}


void free_null(void **p_alloc, char *file_name, size_t line_number) {
  // always null after free
  assert(p_alloc);
  void *alloc = *p_alloc;
  free_without_null(alloc, file_name, line_number);
  *p_alloc = NULL;
}


void print_alloc_info(void *alloc) {

  if (alloc == NULL) {
    printf("  FREED       ---\n");
    return;
  }

  alloc_info_t *info = info_from_alloc(alloc);
  assert(MAX_NUM_MESSAGE_CHARS != 0);

  printf("UNFREED       ---\n");
  printf("file_name   : %s\n", info->file_name);
  printf("line_number : %zu\n", info->line_number);


  #if PRINT_ALLOC_SIZE
  printf("size: %lu\n", info->size);
  if (info->count_if_calloc) {
    printf("calloc count: %lu\n", info->count_if_calloc);
  }
  #endif

  if (info->realloc_count) {
    printf("realloc_count: %lu\n", info->realloc_count);
  }

  if (info->message[0]) {
    printf("message     : \n%s", info->message);
  }
  
  if (info->print_func) {
    printf("print_func  : \n");
    (*info->print_func)(alloc); // print alloc data
  }

  printf("              ---\n");

}

void set_alloc_print_func(void *alloc, void (*print_func)(void *p)) {
  
  assert(alloc);
  if (!print_func) {
    printf("Error 9: NULL function passed into set_alloc_print_func");
    exit(1);
  }

  alloc_info_t *info = info_from_alloc(alloc);

  if (info->print_func) {
    printf("Error 10: overwriting print function in set_alloc_print_func (function already set)");
    exit(1);
  }

  info->print_func = print_func;
}

void print_all_allocs() {

  assert(num_allocs > 0);
  int i = num_allocs;

  printf(">>> print_all_allocs() \n");

  while (i--) { // print reverse
    print_alloc_info(alloc_array[i]);
  }

  printf(">>> \n");
}


void n_unfreed(long n_expected) {

  if (n_expected != num_unfreed_allocs) {

    printf("\n\nERROR: wrong number of unfreed allocs\n");
    printf("	expected : %zu\n", n_expected);
    printf("	found    : %zu\n\n", num_unfreed_allocs);
    printf("\n");
    printf("	allocs are listed below,\n	in reverse allocation order\n");

    print_all_allocs();

    printf("\n\n");

    exit(0);
  }

}

#endif