
#include <stdlib.h>
#include "help_readme.h"

typedef struct {
	char *file_name;
	size_t line_number;
	char message[MAX_NUM_MESSAGE_CHARS];
} malloc_info_t;