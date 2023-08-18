
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
#define UNTYPED_INDX 0

/* a bit of a hack 
  but i just need a unique address 
  kind of cool how efficient this is */

#include "help_structs.h"

#define PRINT_LOCATION \
  printf("on line %zu \nin file %s\n\n", line_number, file_name);

//
// --------------------------------
//




alloc_info_t *info_from_alloc(void *alloc) {

  // can fail, returning NULL

  if (!alloc) {
    printf("Error: Alloc is NULL\n");
    return NULL;
  }

  alloc_info_t *info = ((alloc_info_t *) alloc) - 1;

  bool is_verified = info->verification == VERIFICATION;
  if (!is_verified) {
    printf("Error 11: Invalid verification number for %p\n", alloc);
    printf("          Trying to get information about allocation, but non is there\n");
    printf("          Note: DEBUG_CHELP == %i\n", DEBUG_CHELP);
    printf("\n\n\n");
    return NULL;
  }
  
  assert(info->allocs_index < MAX_NUM_MALLOCS); // if fails, chelp bug

  return info;
}

alloc_info_t *info_from_alloc_dbg(void *alloc, char *file_name, size_t line_number) {

  alloc_info_t *info = info_from_alloc(alloc);
  if (!info) {
    PRINT_LOCATION
    exit(1);
  }

  return info;
}




void print_alloc_info(void *alloc) {

  if (alloc == NULL) {
    printf("  FREED       ---\n");
    return;
  }
  assert(MAX_NUM_MESSAGE_CHARS != 0);

  printf("UNFREED       ---\n");
  printf("pointer     : %p\n", alloc);

  alloc_info_t *info = info_from_alloc(alloc);
  if (!info) {
    exit(1);
  }

  printf("file_name   : %s\n", info->file_name);
  printf("line_number : %zu\n", info->line_number);


  if (PRINT_ALLOC_SIZE) {

    printf("size: %lu\n", info->size);
    if (info->count_if_calloc) {
      printf("calloc count: %lu\n", info->count_if_calloc);
    }
  }


  if (info->realloc_count) {
    printf("realloc_count: %lu\n", info->realloc_count);
  }

  if (info->message[0]) {
    printf("message     : \n%s", info->message);
  }

  if (info->type) {
    printf("type  : %i\n", info->type);
  }
  
  if (info->print_func != UNTYPED_INDX) {
    printf("print_func  : \n");
    (*info->print_func)(alloc); // print alloc data
  }

  printf("              ---\n");

}


bool is_any_typed_allocs() {
  return num_unfreed_allocs != alloc_type_n_unfreed[UNTYPED_INDX]; 
}

void print_typed_allocs_n_unfreed() {

  if (!is_any_typed_allocs()) { return; }

  printf("\nFound typed allocs\n");

  int type;
  for (type = 0; type < MAX_NUM_ALLOC_TYPES; type++) {

    if (alloc_type_name[type] == NULL) { break; }

    printf("n_unfreed: %lu ", alloc_type_n_unfreed[type]);
    printf("type: %s\n", alloc_type_name[type]);
  }

  printf("%i types\n\n", type);
  if (type == MAX_NUM_ALLOC_TYPES) {
    printf("\n\n\nERROR: Increase MAX_NUM_ALLOC_TYPES\n\n\n");
    exit(1);
  }

}


void print_all_allocs() {

  int i = num_allocs;

  printf(">>> print_all_allocs()\n");
  printf("    %zu allocs, %zu unfreed\n", num_allocs, num_unfreed_allocs);
  if (num_unfreed_allocs == 0) {
    printf("    All allocs freed ✅\n");
    printf(">>> \n");
    return;
  }

  print_typed_allocs_n_unfreed();

  printf("\n");

  while (i--) { // print reverse
    print_alloc_info(alloc_array[i]);
  }

  printf(">>> \n");
}





bool is_tracked(void *alloc) {

  for (size_t i = 0; i < num_allocs; i++) {
    if (alloc_array[i] == alloc) {
      return true;
    }
  }
  
  return false;
}

void should_be_tracked(void *alloc, bool should_be_tracked, char *file_name, size_t line_number)  {

  if (DEBUG_CHELP) {

    bool alloc_is_tracked = is_tracked(alloc);
    bool track_match = alloc_is_tracked == should_be_tracked;
    if (!track_match) {
      printf("ERROR 12: alloc is tracked        == %i\n", alloc_is_tracked);
      printf("          alloc should be tracked == %i\n", should_be_tracked);
      printf("          alloc == %p\n", alloc);
      PRINT_LOCATION
      print_all_allocs();
      exit(1);
    }

  }
}

void n_unfreed_check() { 

  if (DEBUG_CHELP) {

    long actual_n_unfreed = 0;
    for (size_t i = 0; i < num_allocs; i++) {
      if (alloc_array[i] != NULL) {
        actual_n_unfreed++;
      }
    }

    assert(num_unfreed_allocs == actual_n_unfreed);
  }
}


void alloc_array_index_check() {

  if (DEBUG_CHELP) {

    for (size_t i = 0; i < num_allocs; i++) {

      if (!alloc_array[i]) { continue; }
      alloc_info_t *info = info_from_alloc(alloc_array[i]);

      if (info->allocs_index != i) {

        printf("ERROR: alloc %p found at wrong index\n", alloc_array[i]);
        printf("info->allocs_index == %li\n", info->allocs_index);
        printf("found at index     == %li\n\n\n", i);

        print_all_allocs();
        exit(1);

      }
    }
    
  }
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

void check_pos_unfreed() {

  if (num_unfreed_allocs < 0) {
    printf("Error 1: Unfreed_allocs < 0\n");
    printf("\n");
    printf("    There are allocs in files where #include is missing\n");
    printf("        Fix: #include #include \"../help/help.h\" // path to help.h \n\n");
    printf("  OR\n\n");
    printf("    There are implicit allocations, such as with strdup().\n");
    printf("    search implicit allocations in help_config.h if you have tried the other options.\n");
    printf("        Fix: use track_alloc\n");
    exit(1);
  } 
}

void free_without_null(void *alloc, char *file_name, size_t line_number, bool print_free) {

  check_not_null(alloc, file_name, line_number);
  should_be_tracked(alloc, true, file_name, line_number);
  n_unfreed_check();

  if (print_free) {
    printf("FREE   %p\n", alloc);
    printf("n_unfreed %li -> %li\n", num_unfreed_allocs, num_unfreed_allocs -1);
    PRINT_LOCATION
  }

  num_unfreed_allocs--;
  check_pos_unfreed();

  alloc_info_t *info = info_from_alloc_dbg(alloc, file_name, line_number);
  assert(info->allocs_index < num_allocs);
  assert(alloc_array[info->allocs_index] == info + 1);
  assert(info->type >= 0);

  alloc_type_n_unfreed[info->type]--;
  alloc_array[info->allocs_index] = NULL;

  n_unfreed_check();
  should_be_tracked(alloc, false, file_name, line_number);

  free(info);
}

void *track_info(alloc_info_t *info, size_t size, size_t count_if_calloc, char *file_name, size_t line_number) {
  // track an allocation which has space for info metadata

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
  info->type = 0; // 0 is default type

  void *alloc = info + 1; // go to start of allocated memory, ignoring data stored before it

  should_be_tracked(alloc, false, file_name, line_number); //
  n_unfreed_check();

  assert(num_allocs < MAX_NUM_MALLOCS);
  alloc_array[num_allocs] = alloc;

  num_allocs++;
  num_unfreed_allocs++;
  alloc_type_n_unfreed[info->type]++;

  should_be_tracked(alloc, true, file_name, line_number);
  n_unfreed_check();
  alloc_array_index_check();

  if (PRINT_ALLOC_AND_FREE) {
    printf("ALLOC %p bytes %lu ", alloc, size);
    PRINT_LOCATION
  }

  return alloc;
}


void *track_alloc(void *untracked_alloc, size_t size, char *file_name, size_t line_number) {
  // track an allocation which does not have space for info metadata
  // replace allocation with new allocation with space

  alloc_info_t *info = malloc(size + sizeof(alloc_info_t));
  void *tracked_alloc = track_info(info, size, 0, file_name, line_number);
  
  memcpy(tracked_alloc, untracked_alloc, size);
  free(untracked_alloc);

  if (DEBUG_CHELP) {
    printf("track_alloc: %p -> %p\n", untracked_alloc, tracked_alloc);
  }

  return tracked_alloc; // needs to overwrite original allocation
}



char *safe_strdup(char *string, char *file_name, size_t line_number) {

  size_t size = strlen(string) + 1; // 1 for NULL byte, can inf loop here if missing
  char *alloc = track_alloc(strdup(string), size, file_name, line_number); 
  return alloc;
}



size_t min2(size_t n1, size_t n2) {
  if (n1 > n2) { return n2; }
  return n1;
}


void *safe_realloc(void *old_alloc, size_t new_size, char *file_name, size_t line_number) {

  should_be_tracked(old_alloc, true, file_name, line_number);

  alloc_info_t *old_info = info_from_alloc_dbg(old_alloc, file_name, line_number);
  size_t old_size = old_info->size;

  // realloc may return an old pointer
  alloc_info_t *new_info = malloc(sizeof(alloc_info_t) + new_size);
  void *new_alloc = new_info + 1;
  assert(new_info);

  // realloc can reduce or increase the size of an allocation
  memcpy(new_info, old_alloc, min2(old_size, new_size));

  track_info(new_info, new_size, 0, file_name, line_number);
  new_info->realloc_count = old_info->realloc_count + 1;

  assert(old_info->allocs_index < new_info->allocs_index);

  free_without_null(old_alloc, file_name, line_number, true); // don't print


  if (PRINT_ALLOC_AND_FREE) {
    printf("REALLOC %p > %p bytes %lu ", old_alloc, new_alloc, new_size);
    PRINT_LOCATION
  }

  
  should_be_tracked(new_alloc, true, file_name, line_number);

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
  void *alloc = track_info(info, size, 0, file_name, line_number);
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
  void *alloc = track_info(info, size, count, file_name, line_number);
  memset(alloc, 0, size * count);
  return alloc;
}


void free_null(void **p_alloc, char *file_name, size_t line_number) {
  // always null after free
  assert(p_alloc);
  void *alloc = *p_alloc;
  free_without_null(alloc, file_name, line_number, PRINT_ALLOC_AND_FREE);
  *p_alloc = NULL;
}


void set_alloc_print_func(void *alloc, void (*print_func)(void *p)) {
  
  assert(alloc);
  if (!print_func) {
    printf("Error 9: NULL function passed into set_alloc_print_func");
    exit(1);
  }

  alloc_info_t *info = info_from_alloc(alloc);
  assert(info);

  if (info->print_func) {
    printf("Error 10: overwriting print function in set_alloc_print_func (function already set)");
    exit(1);
  }

  info->print_func = print_func;
}




void n_unfreed(long n_expected) {

  if (n_expected != num_unfreed_allocs) {

    printf("\n\nERROR: wrong number of unfreed allocs ⛔️\n");
    printf("	expected : %zu\n", n_expected);
    printf("	actual    : %zu\n\n", num_unfreed_allocs);
    printf("\n");

    print_all_allocs();

    printf("\n\n");

    exit(0);
  }

}



void set_alloc_type(void *alloc, int type, char *name) {

  assert(type != 0);
  assert(name != NULL);

  alloc_info_t *info = info_from_alloc(alloc);
  info->type = type;

  alloc_type_name[type] = name; 

  alloc_type_n_unfreed[UNTYPED_INDX]--; 
  alloc_type_n_unfreed[type]++; 

  assert(alloc_type_name[type]);

}



void n_unfreed_of_type(int type, long expected_num) {

    long actual_num = alloc_type_n_unfreed[type];

    if (actual_num != expected_num) {

    printf("\n\nERROR: wrong number of unfreed allocs ⛔️\n");
    assert(alloc_type_name[type]);
    printf("           of type %s", alloc_type_name[type]);

    printf("	expected : %zu\n", expected_num);
    printf("	actual    : %zu\n\n", actual_num);
    printf("\n");

    print_all_allocs();

    printf("\n\n");

    exit(1);
  }
}




#endif