

// tests using messages

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../help/help.h"

long num_unfreed_allocs = 0;
size_t num_allocs = 0;
void *allocs[MAX_NUM_MALLOCS];

int main(void) {
	
	int *p = malloc(100);
	assert(info_from_alloc(p)->print_func == NULL);

	add_message_to_alloc(p,  "This is a number: %i\n", 10);
	print_alloc_info(p);
}