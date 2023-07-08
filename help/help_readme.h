
// code by Henry Routson https://github.com/henryroutson/CHelp

// Credit for idea https://www.youtube.com/watch?v=443UNeGrFoM

// This is the config file

// use
// #include help.h
// in your files
// and follow the setup instructions below

#include <stdbool.h>

#define ENABLE_HELP false // enable or disable everything

#define PRINT_ALLOC_SIZE true // print size and count for malloc and calloc
#define PRINT_ALLOC_AND_FREE true // print out malloc and free when called
#define FREE_NULL_ERROR true // will freeing a null pointer throw an error?
#define MAX_NUM_MESSAGE_CHARS 128  // if your messages are being cutoff, increase this value
#define MAX_NUM_MALLOCS 1024  // - Warning:  program may assert crash if this value isn't large enough


/*

REQUIRED

   s e t u p


        Step 1: Include the below code before main()
                (. is current directory of c file)
                (.. is parent directory)
                (... and so on)

#include "../help/help.h" // path to help.h 

#if ENABLE_HELP
long num_unfreed_allocs = 0;
size_t num_allocs = 0;
void *alloc_array[MAX_NUM_MALLOCS];
#endif

int main() {

}

        Step 2: Add the n_unfreed function before the end of main() 
                to check for memory leaks

...

int main() {

    // code

    n_unfreed(0);
}

                Add n_unfreed code anywhere you know 
                the number of unfreed allocs

n_unfreed(size_t n)

...

int main() {

    char *unfreed_allocation = strdup("A string to copy");
    num_allocs++;

    free(unfreed_allocation);

    n_unfreed(0);
}









ALL FUNCTIONS YOU CAN USE

1 void print_alloc_info(void *p); 

    // prints all info in an allocation from the info struct

    typedef struct {
        char *file_name;
        size_t line_number;
        size_t size;
        size_t count; // if calloc
        char message[MAX_NUM_MESSAGE_CHARS];
        void (*print_func)(void *rp);
        size_t allocs_index;
    } alloc_info_t;

    // see test 4
    https://github.com/HenryRoutson/CHelp/blob/main/tests/4_main.c

    UNFREED       ---
    file_name   : tests/4_main.c
    line_number : 22
    size: 100

2 void set_alloc_print_func(void *p, void (*print_func)(void *p));

    // allows you to attatch a custom print function to an allocation

    // see test 6 as a simple example
    https://github.com/HenryRoutson/CHelp/blob/main/tests/6_main.c

    UNFREED       ---
    file_name   : tests/6_main.c
    line_number : 29
    size: 24
    print_func  : 
    1 2 3.000000



3 void n_unfreed(long n);

    // checks there are n unfreed allocations
    // prints error and exits if fails

    // see test 9
    https://github.com/HenryRoutson/CHelp/blob/main/tests/9_main.c

    ERROR: wrong number of unfreed allocs
        expected : 0
        found    : 1


        allocs are listed below,
        in reverse allocation order

    ...



4 void print_all_allocs();

    // prints all allocations 

    >>> print_all_allocs() 
    UNFREED       ---
    file_name   : tests/9_main.c
    line_number : 36
    size: 24
    print_func  : 
    1 s2 3.000000
                ---
    FREED       ---
    >>> 



5 void free_without_null(void *pointer);

    // used where a pointer to be freed isn't stored,
    // but is returned

    // see test 12 
    https://github.com/HenryRoutson/CHelp/blob/main/tests/12_main.c

    free_without_null(echo(p));


6 void add_message_to_alloc(void *p, format_and_args...);

    // allows you to add a message to an allocation,
    // this allows you to add information without changing structure
    // works like printf, with a format string and arguements

    // see test 5
    https://github.com/HenryRoutson/CHelp/blob/main/tests/5_main.c

    add_message_to_alloc(p,  "This is a number: %i\n", 10);

    UNFREED       ---
    file_name   : tests/5_main.c
    line_number : 19
    size: 100
    message     : 
    This is a number: 10

7 void track_alloc(void **p_untracked_alloc, size_t size);

    //          implicit allocations

    These are functions which return a pointer allocated with malloc or calloc
    which the chelp library macros cannot override because the library code is already compiled
    For example strdup() duplicates a string, 
    returing a pointer to memory which needs to be freed

    //

    Using track_alloc will add traacking information to your allocation and incriment the number of unfreed allocations
    if you really don't know how large the allocation is, the size only has to be larger than it, so just make it really big

    See test 0 in the tests file
    https://github.com/HenryRoutson/CHelp/blob/main/tests/0_main.c












Other notes

size_t num_allocs = 0;         // <<< is used to index into allocs
If ENABLE_HELP is disabled, then make test will fail, but make run should pass however

if something is not working, run 
    make clean






*/