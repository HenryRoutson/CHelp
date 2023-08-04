

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <string.h>

#include "../help/help.h"
CHELP_MAIN_MACRO

int main() {

  char *alloc = strdup("A string to copy"); 
  printf("alloc %p\n", alloc);

  #ifdef ENABLE_HELP
  n_unfreed(1);
  #endif

  print_all_allocs(); 

  free(alloc);

  n_unfreed(0);
}