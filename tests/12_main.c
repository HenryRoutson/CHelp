

// tests using oversized messages

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../help/help.h"
CHELP_MAIN_MACRO

void *echo(void *p) {
	return p;
} 

int main(void) {
	
	int *p = malloc(100);

	add_message_to_alloc(p,  "This is an extremely long message, longer than the available space his is an extremely long message, longer than the available spacehis is an extremely long message, longer than the available spacehis is an extremely long message, longer than the available spacehis is an extremely long message, longer than the available spacehis is an extremely long message, longer than the available spacehis is an extremely long message, longer than the available spacehis is an extremely long message, longer than the available spacehis is an extremely long message, longer than the available spacehis is an extremely long message, long");


	print_alloc_info(p);

	free_without_null(echo(p));


	printf("TEST: PASSED"); // if didnt crash
}