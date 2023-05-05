
// code by Henry Routson https://github.com/henryroutson/CHelp

#include "help_readme.h"
#include <stdlib.h>

typedef struct {
  char *file_name;
  size_t line_number;
  size_t size;
  char message[MAX_NUM_MESSAGE_CHARS];
  void (*print_func)(void *p);
  size_t mallocs_index;
} malloc_info_t;

extern long num_unfreed_mallocs;
extern size_t num_mallocs;
extern void *mallocs[MAX_NUM_MALLOCS];

