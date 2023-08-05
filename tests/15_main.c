
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "../help/help.h"
CHELP_MAIN_MACRO

int main(void) {
	
	int *p = malloc(100);
  p = realloc(p, 200);
  free(p);

	printf("TEST: PASSED"); // if didnt crash
}
