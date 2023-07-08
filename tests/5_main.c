
//   H o w    t o    u s e    ADD_MESSAGE_TO_ALLOC

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../help/help.h"
CHELP_MAIN_MACRO

int main(void) {
	
	int *p = malloc(100);

	add_message_to_alloc(p,  "This is a number: %i\n", 10); // format strings can be used
	print_alloc_info(p);

    free(p);
}