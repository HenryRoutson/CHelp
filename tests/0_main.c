

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <string.h>

#include "../help/help.h"
CHELP_MAIN_MACRO

int main() {

    char *unfreed_allocation = strdup("A string to copy");

    print_all_allocs(); // should show untracked

    free(unfreed_allocation);

    n_unfreed(0);
}