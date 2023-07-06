

// tests using  messages without formatting

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../help/help.h"
CHELP_MAIN_MACRO

int main(void) {
	
	int *p = malloc(100);

	add_message_to_alloc(p,  "Test no formatting");

	print_alloc_info(p);

    free(p);
}