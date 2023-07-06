
// code by Henry Routson https://github.com/henryroutson/CHelp

// Credit for idea https://www.youtube.com/watch?v=443UNeGrFoM

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
void *allocs[MAX_NUM_MALLOCS];
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

        Step 3: Remember not all allocs are explicit
                and you may have to use 
                num_allocs++;
                occasionally
                for example with functions like strdup

                for simplicity only malloc and calloc increment num_allocs

...

int main() {

    char *unfreed_allocation = strdup("A string to copy");
    num_allocs++;

    free(unfreed_allocation);

    n_unfreed(0);
}



OPTIONAL



H o w    t o    u s e    A D D _ M E S S A G E _ T O _ M A L L O C


        #include <stdlib.h>

        #include "help/help.h"

        long num_unfreed_allocs = 0;
        size_t num_allocs = 0;
        void *allocs[MAX_NUM_MALLOCS];

        int main() {

                int *p = malloc(100);
                add_message_to_alloc(p, "message in malloc, this can be formatted like %s", "this");
                print_alloc_info(p); // this will print out the message

        }




H o w   t o   u s e   A D D _ P R I N T _ F U N C _ T O _ M A L L O C

        #include <stdio.h>
        #include <stdlib.h>

        #include "help.h"

        long num_unfreed_allocs = 0;
        size_t num_allocs = 0;
        void *allocs[MAX_NUM_MALLOCS];

        typedef struct { // some struct
                int i;
                char *c;
                float f;
        } struct_t;

        void print_struct(void *v) { // some print function
                struct_t *s = v;
                printf("%i %s %f\n", s->i, s->c, s->f);
        }

        int main() {

                struct_t *s = malloc(sizeof(*s));
                s->i = 1;
                s->c = "2";
                s->f = 3;

                set_alloc_print_func(s, print_struct);
                print_alloc_info((void *) s);

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
        void (*print_func)(void *p);
        size_t allocs_index;
    } alloc_info_t;

    // see test 4

    UNFREED       ---
    file_name   : tests/4_main.c
    line_number : 22
    size: 100

2 void set_alloc_print_func(void *p, void (*print_func)(void *p));

    // allows you to attatch a custom print function to an allocation

    // see test 6 as a simple example

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

    free_without_null(echo(p));


6 void add_message_to_alloc(void *p, format_and_args...);

    // allows you to add a message to an allocation,
    // this allows you to add information without changing structure
    // works like printf, with a format string and arguements

    // see test 5
    add_message_to_alloc(p,  "This is a number: %i\n", 10);

    UNFREED       ---
    file_name   : tests/5_main.c
    line_number : 19
    size: 100
    message     : 
    This is a number: 10





Other notes

size_t num_allocs = 0;         // <<< is used to index into allocs
If ENABLE_HELP is disabled, then make test will fail, but make run should pass however

if something is not working, run 
    make clean

*/
