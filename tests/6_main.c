
#include <stdlib.h>
#include <stdio.h>

#include "../help.h"

long num_unfreed_mallocs = 0;

typedef struct {
	int i;
	char *c;
	float f;
} struct_t;



void print_struct(void *v) {
	struct_t *s = v;
	printf("%i %s %f\n", s->i, s->c, s->f);
}


int main() {
	
	struct_t *s = malloc(sizeof(*s));
	s->i = 0;
	s->c = "something";
	s->f = 0.0;

	add_print_func_to_malloc(s, print_struct);
	print_malloc_info((void *) s);

}