

// tests using oversized messages

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../help/help.h"

long num_unfreed_mallocs = 0;
size_t num_mallocs = 0;
void *mallocs[MAX_NUM_MALLOCS];

int main(void) {
	
	int *p = malloc(100);
	assert(info_from_malloc(p)->print_func == NULL);

	add_message_to_malloc(p,  "This is an extremely long message, longer than the available space his is an extremely long message, longer than the available spacehis is an extremely long message, longer than the available spacehis is an extremely long message, longer than the available spacehis is an extremely long message, longer than the available spacehis is an extremely long message, longer than the available spacehis is an extremely long message, longer than the available spacehis is an extremely long message, longer than the available spacehis is an extremely long message, longer than the available spacehis is an extremely long message, long");


	print_malloc_info(p);


	printf("TEST: PASSED"); // if didnt crash
}