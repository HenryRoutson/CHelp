
#include <stdlib.h>
#include <stdio.h>

#include "../help.h"

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
	
	struct_t *s1 = malloc(sizeof(*s1));
	add_print_func_to_malloc(s1, print_struct);
	s1->i = 1;
	s1->c = "s1";
	s1->f = 3;

	struct_t *s2 = malloc(sizeof(*s2));
	add_print_func_to_malloc(s2, print_struct);
	s2->i = 1;
	s2->c = "s2";
	s2->f = 3;

	
	

	assert_n_unfreed_mallocs(0);
}