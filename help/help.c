
// code by Henry Routson https://github.com/henryroutson/CHelp

#include "help_readme.h"
#if ENABLE_HELP



#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNTRACKED_POINTER allocs

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

void add_untracked_alloc() {

    add_alloc(UNTRACKED_POINTER);

    // a bit of a hack as it points to allocs
    // but i just need a unique address 
    // that will identify if something is an untracked 
    // as null is already taken for freed memory
    // and i want to avoid adding too much to the main
    // kind of cool how efficient this is
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

  if (!(info->allocs_index < MAX_NUM_MALLOCS)) {

    printf("Invalid index %li for max %li\n\n\n", info->allocs_index, (long) MAX_NUM_MALLOCS);
    printf("Make sure this allocation is using either malloc or calloc");
    exit(1);
  }

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
    printf("    search implicit allocations in help.h if you have tried the other options.\n\n");
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

void *init_info(alloc_info_t *p, size_t size, size_t count, char *file_name, size_t line_number) {

  if (p == NULL) {
    printf("\n\nError 4: alloc of size %lu and count %lu (0 if malloc) failed \n", size, count);
    PRINT_LOCATION
    exit(1);
  }

  p->file_name = file_name;
  p->line_number = line_number;
  p->size = size;
  p->count = count;
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

  if (p == allocs) {
    printf("  UNTRACKED       ---\n");
    return;
  }

  alloc_info_t *info = info_from_alloc(p);
  assert(MAX_NUM_MESSAGE_CHARS != 0);

  printf("UNFREED       ---\n");
  printf("file_name   : %s\n", info->file_name);
  printf("line_number : %zu\n", info->line_number);


  #if PRINT_ALLOC_SIZE
  printf("size: %lu\n", info->size);
  if (info->count) {
    printf("count: %lu\n", info->count);
  }
  #endif

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