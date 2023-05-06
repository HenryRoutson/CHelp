
// code by Henry Routson https://github.com/henryroutson/CHelp

// Credit for idea https://www.youtube.com/watch?v=443UNeGrFoM

// This is the config file

// use
// #include help.h
// in your files
// and follow the setup instructions below

#include <stdbool.h>

#define ENABLE_HELP true // enable or disable everything

#define PRINT_ALLOC_SIZE false // print size and count for malloc and calloc
#define PRINT_ALLOC_AND_FREE true // print out malloc and free when called
#define FREE_NULL_ERROR true // will freeing a null pointer throw an error?
#define MAX_NUM_MESSAGE_CHARS 128  // if your messages are being cutoff, increase this value
#define MAX_NUM_MALLOCS 1024  // - Warning:  program may assert crash if this value isn't large enough


/*

REQUIRED


   s e t u p


        Step 1: Include the below code before main()

#if ENABLE_HELP
long num_unfreed_allocs = 0;
size_t num_allocs = 0;
void *allocs[MAX_NUM_MALLOCS];
#endif

        Step 2: Add the below code before the end of main()
        Step 2: Add the below code anywhere you know 
                the number of unfreed allocs

n_unfreed(size_t n)

        Step 3: Remember not all allocs are explicit
                and you may have to use 
                num_allocs++;
                occasionally





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

                add_print_func_to_alloc(s, print_struct);
                print_alloc_info((void *) s);

        }







































*/
