
// code by Henry Routson https://github.com/henryroutson/CHelp

#include "help_readme.h"
#if ENABLE_HELP



#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define VERIFICATION 123456789 // some unlikely numbder to verify an allocation has info

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


void add_alloc(void *p) {

    assert(num_allocs < MAX_NUM_MALLOCS);
    allocs[num_allocs] = p;

    num_allocs++;
    num_unfreed_allocs++;
}


void check_not_null(void *p, char *file_name, size_t line_number) {
  if (p == NULL && FREE_NULL_ERROR) {
    printf("\n	You may be freeing twice, pointer is NULL\n");
    PRINT_LOCATION

    printf("\n\n	exit() program, freeing nulls is not allowed");
    printf("\n		change this bevaviour in help_readme.h\n\n\n");
    exit(1);
  }
}


alloc_info_t *info_from_alloc(void *p) {

  assert(p);

  alloc_info_t *info = (alloc_info_t *)p;
  info -= 1;

  if (info->verification != VERIFICATION) {
    printf("Error 11: Invalid verification number\n");
    printf("          Trying to get information about allocation but non is there\n");
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
    printf("    There are allocs in files where include is missing\n");
    printf("        Fix: #include #include \"../help/help.h\" // path to help.h \n\n");
    printf("  OR\n\n");
    printf("    There are implicit allocations, such as with strdup().\n");
    printf("    search implicit allocations in help_readme.h if you have tried the other options.\n");
    printf("        Fix: \n");
    exit(1);
  }
}

void free_without_null(void *p, char *file_name, size_t line_number) {

  check_not_null(p, file_name, line_number);

  if (PRINT_ALLOC_AND_FREE) {
    printf("FREE   %p ", p);
    PRINT_LOCATION
  }

  num_unfreed_allocs--;
  check_pos_unfreed();

  alloc_info_t *info = info_from_alloc(p);
  allocs[info->allocs_index] = NULL;

  free(info);

}

void *init_info(alloc_info_t *p, size_t size, size_t count_if_calloc, char *file_name, size_t line_number) {

  if (p == NULL) {
    printf("\n\nError 4: alloc of size %lu and count %lu (0 if calloc) failed \n", size, count_if_calloc);
    PRINT_LOCATION
    exit(1);
  }

  p->verification = VERIFICATION;
  p->file_name = file_name;
  p->line_number = line_number;
  p->size = size;
  p->realloc_count = 0;
  p->count_if_calloc = count_if_calloc;
  p->message[0] = 0;
  p->print_func = NULL;

  p->allocs_index = num_allocs;

  p += 1; // go to start of allocated memory, ignoring data stored before it

  void *memory = p;

  add_alloc(memory);

  if (PRINT_ALLOC_AND_FREE) {
    printf("ALLOC %p bytes %lu ", memory, size);
    PRINT_LOCATION
  }

  return memory;
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


void *safe_realloc(void *old_memory, size_t new_size, char *file_name, size_t line_number) {


  alloc_info_t *old_info = info_from_alloc(old_memory);
  size_t old_size = old_info->size;

  alloc_info_t *new_info = malloc(new_size + sizeof(alloc_info_t));

  // realloc can reduce or increase the size of an allocation
  memcpy(new_info, old_info, sizeof(alloc_info_t) + min2(old_size, new_size));
  new_info->size = new_size;
  new_info->realloc_count ++;

  free(old_info);

  void *new_memory = new_info + 1;

  if (PRINT_ALLOC_AND_FREE) {
    printf("REALLOC %p > %p bytes %lu ", old_memory, new_memory, new_size);
    PRINT_LOCATION
  }

  return new_memory;
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
  void *memory = init_info(info, size, 0, file_name, line_number);
  return memory;
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
  void *memory = init_info(info, size, count, file_name, line_number);
  memset(memory, 0, sizeof(size * count));
  return memory;
}


void free_null(void **pp, char *file_name, size_t line_number) {
  // always null after free
  assert(pp);
  void *p = *pp;
  free_without_null(p, file_name, line_number);
  *pp = NULL;
}


void print_alloc_info(void *p) {

  if (p == NULL) {
    printf("  FREED       ---\n");
    return;
  }

  alloc_info_t *info = info_from_alloc(p);
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
    (*info->print_func)(p);
  }

  printf("              ---\n");

}

void set_alloc_print_func(void *p, void (*print_func)(void *p)) {
  
  assert(p);
  if (!print_func) {
    printf("Error 9: NULL function passed into set_alloc_print_func");
    exit(1);
  }

  alloc_info_t *info = info_from_alloc(p);

  if (info->print_func) {
    printf("Error 10: overwriting print function in set_alloc_print_func (function already set)");
    exit(1);
  }

  info->print_func = print_func;

}

void print_all_allocs(void) {

  assert(num_allocs > 0);
  int i = num_allocs;

  printf(">>> print_all_allocs() \n");

  while (i--) { // print reverse
    print_alloc_info(allocs[i]);
  }

  printf(">>> \n");
}


void n_unfreed(long n) {

  if (n != num_unfreed_allocs) {

    printf("\n\nERROR: wrong number of unfreed allocs\n");
    printf("	expected : %zu\n", n);
    printf("	found    : %zu\n\n", num_unfreed_allocs);
    printf("\n");
    printf("	allocs are listed below,\n	in reverse allocation order\n");

    print_all_allocs();

    printf("\n\n");

    exit(0);
  }

}

#endif