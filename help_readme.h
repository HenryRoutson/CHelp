
// This is the config file

// use 
// #include help.h 
// in your file 

// code by Henry Routson
// Credit https://www.youtube.com/watch?v=443UNeGrFoM

#include <stdbool.h>

#define ENABLE true  // disable or enable everything
#define SHOW_DEBUG true 
#define CHECK_LEAKS true // setup below

#define MAX_NUM_MALLOC_LOCATIONS 100
#define MAX_NUM_MALLOC_FILES 50          // files  where malloc is called




/*  ----------------

		H o w   t o   s e t u p   C H E C K _ L E A K S

		long unfreed_mallocs = 0;

Before main (to initialise) ----------------

		assert(unfreed_mallocs == 0); 

At the end of main  ----------------
and at any point where you know how many unfreed_mallocs there should be ----------------

*///  ----------------




