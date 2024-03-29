
// code by Henry Routson https://github.com/henryroutson/CHelp

#include "help_config.h"
#include <stdlib.h>

typedef struct {
  size_t verification;
  char *file_name;
  size_t line_number;
  size_t size;
  size_t count_if_calloc;
  size_t realloc_count;
  char message[MAX_NUM_MESSAGE_CHARS];
  void (*print_func)(void *p);
  size_t allocs_index;
  int type; // index into type array, 0 by default
} alloc_info_t;

#if ENABLE_HELP
extern long num_unfreed_allocs;
extern size_t num_allocs;
extern void *alloc_array[MAX_NUM_MALLOCS];
long alloc_type_n_unfreed[MAX_NUM_ALLOC_TYPES];
char *alloc_type_name[MAX_NUM_ALLOC_TYPES];

#endif
