

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <string.h>

#include "../help/help.h"
CHELP_MAIN_MACRO

int main() {

  char *string = "A string to copy";
  size_t n_string_bytes = strlen(string) + 1;
  printf("n_string_bytes %lu", n_string_bytes); // gets rid of warning

  char *alloc = strdup(string);
  track_alloc(&alloc, n_string_bytes); 

  n_unfreed(1);

  print_all_allocs(); 

  free(alloc);

  n_unfreed(0);
}