
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "../help/help.h"
CHELP_MAIN_MACRO

int main(void) {

  enum {
    UNTYPED,
    TYPE1,
    TYPE2,
  };
	
	int *p = malloc(100);
  set_alloc_type(p, TYPE1, "type1 name");

  int *b = malloc(39);
  set_alloc_type(b, TYPE2, "type2 name");

  print_all_allocs();

  free(b);
  free(p);

  print_all_allocs();
}