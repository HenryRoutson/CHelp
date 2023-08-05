
// code by Henry Routson https://github.com/henryroutson/CHelp
// Credit https://www.youtube.com/watch?v=443UNeGrFoM at 48:48

// This is the config file

// use
// #include help.h
// in your files
// and follow the setup instructions below

#include <stdbool.h>

#define ENABLE_HELP true // enable or disable everything

#define PRINT_ALLOC_SIZE true // print size and count for malloc and calloc
#define PRINT_ALLOC_AND_FREE true // print out malloc and free when called
#define FREE_NULL_ERROR true // will freeing a null pointer throw an error?
#define MAX_NUM_MESSAGE_CHARS 128  // if your messages are being cutoff, increase this value
#define MAX_NUM_MALLOCS 1024  // - Warning:  program may assert crash if this value isn't large enough
#define ENABLE_CHELP_CHECKS true // Adds extra checks, at performance cost

#define DEBUG_CHELP true


/*

REQUIRED

   s e t u p    -  30 seconds


        Step 1: Include the below code before main()
                (. is current directory of c file)
                (.. is parent directory)
                (... and so on)

#include "../help/help.h" // path to help.h 
CHELP_MAIN_MACRO

int main() {

}

        Step 2: Add the n_unfreed function before the end of main() 
                to check for memory leaks


#include "../help/help.h" // path to help.h 
CHELP_MAIN_MACRO

int main() {

    // code

    n_unfreed(0);
}









Other notes

size_t num_allocs = 0;         // <<< is used to index into alloc_array
If ENABLE_HELP is disabled, then 
  make test 
will fail, but 
  make run 
should pass however

if something is not working, run 
    make clean


*/