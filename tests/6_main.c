
// tsets add_print_func_to_malloc

#include <stdlib.h>
#include <stdio.h>

#include "../help/help.h"

long num_unfreed_mallocs = 0;

#if PRINT_UNFREED_MALLOCS
size_t num_mallocs = 0;
void *mallocs[MAX_NUM_MALLOCS];
#endif

typedef struct {
	int i;
	char *c;
	float f;
} struct_t;


void print_struct(void *v) {
	struct_t *s = v;
	printf("%i %s %f\n", s->i, s->c, s->f);
}

int main(void) {
	
	struct_t *s = malloc(sizeof(*s));
	s->i = 1;
	s->c = "2";
	s->f = 3;

	add_print_func_to_malloc(s, print_struct);
	print_malloc_info((void *) s);

}