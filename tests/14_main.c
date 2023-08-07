
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../help/help.h"
CHELP_MAIN_MACRO

int main(void) {

  size_t s = 10;
	
  #undef malloc // don't use macro to track alloc
  void *untracked_alloc = malloc(s);

  n_unfreed(0);

  void *tracked_alloc = track_alloc(untracked_alloc, s);

  n_unfreed(1);

  free(tracked_alloc);

  n_unfreed(0);

	printf("TEST: PASSED"); // if didnt crash
}