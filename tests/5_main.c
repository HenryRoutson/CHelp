
#include <stdlib.h>
#include <stdio.h>

#include "../help.h"

long unfreed_mallocs = 0;

int main() {
	
	int *p = malloc(100);
	add_message_to_malloc(p,  "This is a number %i", 10);
	print_malloc_info(p);

}