
// tests n_unfreed


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
	
	struct_t *s1 = malloc(sizeof(*s1));
	set_alloc_print_func(s1, print_struct);
	s1->i = 1;
	s1->c = "s1";
	s1->f = 3;

	struct_t *s2 = malloc(sizeof(*s2));
	set_alloc_print_func(s2, print_struct);
	s2->i = 1;
	s2->c = "s2";
	s2->f = 3;

	n_unfreed(0);
}