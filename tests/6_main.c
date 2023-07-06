
// tsets set_alloc_print_func

#include <stdlib.h>
#include <stdio.h>

#include "../help/help.h"
CHELP_MAIN_MACRO

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
	print_alloc_info((void *) s);

}