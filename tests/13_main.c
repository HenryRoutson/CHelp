
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "../help/help.h"
CHELP_MAIN_MACRO

int main(void) {
	
	int *p = malloc(1);
  p = realloc(p, 2);
  p = realloc(p, 3);
  p = realloc(p, 4);
  p = realloc(p, 5);
  free(p);

	printf("TEST: PASSED"); // if didnt crash
}
