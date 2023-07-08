
// code by Henry Routson https://github.com/henryroutson/CHelp

#include "help_readme.h"
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
} alloc_info_t;

#if ENABLE_HELP
extern long num_unfreed_allocs;
extern size_t num_allocs;
extern void *allocs[MAX_NUM_MALLOCS];
#endif
