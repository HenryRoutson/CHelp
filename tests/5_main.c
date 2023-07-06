

// tests using messages

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../help/help.h"
CHELP_MAIN_MACRO

int main(void) {
	
	int *p = malloc(100);

	add_message_to_alloc(p,  "This is a number: %i\n", 10);
	print_alloc_info(p);

    free(p);
}