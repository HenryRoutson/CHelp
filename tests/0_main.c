

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <string.h>

#include "../help/help.h"
CHELP_MAIN_MACRO

int main() {

  char *string = "A string to copy";
  size_t n_string_bytes = strlen(string) + 1;
  printf("n_string_bytes %lu", n_string_bytes); // get rid of ignored warning

  char *unfreed_allocation = strdup(string);
  track_alloc((void **) &unfreed_allocation, n_string_bytes); // <<<< allocation is tracked immediately after creation (pointer value will change)
  // num bytes just has to be bigger, not exact

  n_unfreed(1);

  print_all_allocs(); // should show untracked

  free(unfreed_allocation);

  n_unfreed(0);
}