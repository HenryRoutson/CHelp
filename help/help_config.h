
// code by Henry Routson https://github.com/henryroutson/CHelp

// This is the config file

// use
// #include help.h
// in your files
// and follow the setup instructions below

#include <stdbool.h>

#define ENABLE_HELP true // enable or disable everything

#define PRINT_ALLOC_SIZE true // print size and count for malloc and calloc
#define PRINT_ALLOC_AND_FREE false // print out malloc and free when called
#define FREE_NULL_ERROR true // will freeing a null pointer throw an error?



// - Warning:  program may assert crash if this value isn't large enough
#define MAX_NUM_MALLOCS 1024  
// if your messages are being cutoff, increase this value
#define MAX_NUM_MESSAGE_CHARS 128  
//
#define MAX_NUM_ALLOC_TYPES 128








































#define DEBUG_CHELP false // Adds extra checks, and info, at performance cost
