
// This is the config file

// use 
// #include help.h 
// in your file 

// code by Henry Routson
// Credit https://www.youtube.com/watch?v=443UNeGrFoM

#include <stdbool.h>

#define ENABLE_HELP true        // disable or enable everything in the help files

#define SHOW_DEBUG  true        // print out debug information
#define FREE_NULL_ERROR true   // will freeing a null pointer throw an error



/*  ----------------

		H o w   t o   s e t u p   C H E C K _ L E A K S

		long unfreed_mallocs = 0;

Before main (to initialise) ----------------

		assert(unfreed_mallocs == 0); 

At the end of main  ----------------
and at any point where you know how many unfreed_mallocs there should be ----------------

*///  ----------------
