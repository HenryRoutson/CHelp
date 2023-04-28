
#include <stdlib.h>
#include "help_readme.h"

typedef struct {
	char *file_name;
	size_t line_number;
	char message[MAX_NUM_MESSAGE_CHARS];
	void (*print_func)(void *p);
} malloc_info_t;