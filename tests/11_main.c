

// tests using  messages without formatting

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../help/help.h"

#if ENABLE_HELP
long num_unfreed_allocs = 0;
size_t num_allocs = 0;
void *allocs[MAX_NUM_MALLOCS];
#endif

int main(void) {
	
	int *p = malloc(100);

	add_message_to_alloc(p,  "Test no formatting");

	print_alloc_info(p);

    free(p);
}