

// test large / negative malloc

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../help/help.h"
CHELP_MAIN_MACRO

int main(void) {

	// test large malloc failure

	int *l = malloc(-1); // will fail
    free(l);
}