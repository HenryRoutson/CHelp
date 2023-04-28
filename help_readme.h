
// This is the config file

// use 
// #include help.h 
// in your files
// and follow the setup instructions below

// code by Henry Routson https://github.com/HenryRoutson/CHelp
// Credit https://www.youtube.com/watch?v=443UNeGrFoM

#include <stdbool.h>

#define ENABLE_HELP true             // disable or enable everything in the help files 
                                     // and options below

#define PRINT_MALLOC_FREE  false     // print out malloc and free

#define FREE_NULL_ERROR true         // will freeing a null pointer throw an error?

#define MAX_NUM_MESSAGE_CHARS 128    // if your messages are being cutoff, increase this value

#define PRINT_UNFREED_MALLOCS true   // - Warning: this can make your program assert crash, don't use in deployment. setup below
#define MAX_NUM_MALLOCS 1024         // - Warning: this can make your program assert crash if this value isn't large enough 


/* 



H o w    t o    s e t u p    U N F R E E D _ M A L L O C S

	Step 1: Insert long num_unfreed_mallocs = 0; before main()

long num_unfreed_mallocs = 0;

	Step 2: Assert num_unfreed_mallocs where the number is know
					( There should always be no unfreed mallocs at the end of main() )

assert(num_unfreed_mallocs == 0); 



H o w    t o    u s e    A D D _ M E S S A G E _ T O _ M A L L O C


	#include <stdlib.h>

	#include "help.h"

	long num_unfreed_mallocs = 0;

	int main() {
		
		int *p = malloc(100);
		add_message_to_malloc(p, "message in malloc");
		print_malloc_info(p); // this will print out the message

		// TODO add function to check all free
		// TODO use for loop
	}



H o w   t o   s e t u p   P R I N T _ U N F R E E D 

	// TODO


*/
