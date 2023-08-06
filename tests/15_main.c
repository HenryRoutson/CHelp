





#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "../help/help.h"
CHELP_MAIN_MACRO

int main(void) {
	
	int *p = malloc(100);
  print_all_allocs();

  p = realloc(p, 200);
  n_unfreed(1);
  print_all_allocs();

  p = realloc(p, 200);
  n_unfreed(1);
  print_all_allocs();

  p = realloc(p, 100);
  n_unfreed(1);
  print_all_allocs();

  p = realloc(p, 10);
  n_unfreed(1);

  print_all_allocs();

	printf("TEST: PASSED"); // if didnt crash
}