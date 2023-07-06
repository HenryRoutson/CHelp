

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <string.h>

#include "../help/help.h"

#if ENABLE_HELP
long num_unfreed_allocs = 0;
size_t num_allocs = 0;
void *allocs[MAX_NUM_MALLOCS];
#endif

int main() {

    char *unfreed_allocation = strdup("A string to copy");
    incriment_num_allocs();

    free(unfreed_allocation);

    n_unfreed(0);
}