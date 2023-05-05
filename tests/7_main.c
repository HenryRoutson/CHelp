
#include <stdlib.h>
#include <stdio.h>

#include "../help/help.h"

long num_unfreed_allocs = 0;
size_t num_allocs = 0;
void *allocs[MAX_NUM_MALLOCS];

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

	add_print_func_to_alloc(s, print_struct);
	add_print_func_to_alloc(s, NULL);
	print_alloc_info((void *) s);

}