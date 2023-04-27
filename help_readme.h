
// This is the config file

// use 
// #include help.h 
// in your files
// and follow the setup instructions below

// code by Henry Routson
// Credit https://www.youtube.com/watch?v=443UNeGrFoM

#include <stdbool.h>

#define ENABLE_HELP true        // disable or enable everything in the help files

#define SHOW_DEBUG  true        // print out debug information
#define FREE_NULL_ERROR true   // will freeing a null pointer throw an error



/* 



H o w   t o   s e t u p   C H E C K _ L E A K S

	Step 1: Insert long unfreed_mallocs = 0; before main()

long unfreed_mallocs = 0;

	Step 2: Assert unfreed_mallocs where the number is know
					( There should always be no unfreed mallocs at the end of main() )

assert(unfreed_mallocs == 0); 



H o w   t o   u s e   M A L L O C    M E S S A G E














*/
