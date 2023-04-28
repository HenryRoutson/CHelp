
#include <stdlib.h>
#include <stdio.h>

#include "../help.h"

long num_unfreed_mallocs = 0;

#if PRINT_UNFREED_MALLOCS
size_t num_mallocs = 0;
void *mallocs[MAX_NUM_MALLOCS];
#endif

int main() {
	
	int *p = malloc(100);
	add_message_to_malloc(p,  "This is a number %i\n", 10);
	print_malloc_info(p);

}