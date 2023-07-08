
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../help/help.h"
CHELP_MAIN_MACRO

int main(void) {
	
	int *p = malloc(100); // keep on line 11

  p = realloc(p, 200);
  p = realloc(p, 200);
  p = realloc(p, 100);
  p = realloc(p, 10);

  print_all_allocs();

	printf("TEST: PASSED"); // if didnt crash
}