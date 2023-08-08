

// test large / negative malloc

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../help/help.h"
CHELP_MAIN_MACRO

int main(void) {

	// test large malloc failure

  size_t overflowed = 10*sizeof(int)- 60* sizeof(char);
	int *l = malloc(overflowed); // will fail
  free(l);
}