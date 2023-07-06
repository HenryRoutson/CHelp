
#include <stdlib.h>
#include <stdio.h>

#include "../help/help.h"

#if ENABLE_HELP
long num_unfreed_allocs = 0;
size_t num_allocs = 0;
void *allocs[MAX_NUM_MALLOCS];
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

	set_alloc_print_func(s, print_struct);
	set_alloc_print_func(s, NULL);
	print_alloc_info((void *) s);

}