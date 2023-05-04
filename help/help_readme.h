
// code by Henry Routson https://github.com/henryroutson/CHelp

// Credit for idea https://www.youtube.com/watch?v=443UNeGrFoM

// This is the config file

// use
// #include help.h
// in your files
// and follow the setup instructions below

#include <stdbool.h>

#define ENABLE_HELP                                                            \
  true // disable or enable everything in the help files
       // and options below

#define PRINT_MALLOC_AND_FREE true // print out malloc and free

#define FREE_NULL_ERROR true // will freeing a null pointer throw an error?

#define MAX_NUM_MESSAGE_CHARS                                                  \
  128 // if your messages are being cutoff, increase this value

#define PRINT_UNFREED_MALLOCS                                                  \
  true // - Warning: this can make your program assert crash,
       // don't use in deployment. setup is below
#define MAX_NUM_MALLOCS                                                        \
  1024 // - Warning:  program may assert crash if this value isn't large enough

/*

REQUIRED


H o w    t o    s e t u p    U N F R E E D _ M A L L O C S

        Step 1: Insert long num_unfreed_mallocs = 0; before main()

long num_unfreed_mallocs = 0;

        Step 2: Assert num_unfreed_mallocs where the number is know
        ( There should always be no unfreed mallocs at the end of main() )

assert(num_unfreed_mallocs == 0); // DONT DO THIS (HARD TO DISABLE)

// do this (will print out all mallocs if not equal value)

assert_n_unfreed_mallocs(0);









OPTIONAL



H o w    t o    u s e    A D D _ M E S S A G E _ T O _ M A L L O C


        #include <stdlib.h>

        #include "help.h"

        long num_unfreed_mallocs = 0;

        int main() {

                int *p = malloc(100);
                add_message_to_malloc(p, "message in malloc");
                print_malloc_info(p); // this will print out the message

        }



H o w   t o   s e t u p   P R I N T _ U N F R E E D


        Step 1: set PRINT_UNFREED_MALLOCS to true

#define PRINT_UNFREED_MALLOCS true

        Step 2: Include the below code before main()

size_t num_mallocs = 0;
void *mallocs[MAX_NUM_MALLOCS];

        Step 3: Add the below code before the end of main()

assert_n_unfreed_mallocs(size_t n)




H o w   t o   u s e   A D D _ P R I N T _ F U N C _ T O _ M A L L O C

        #include <stdio.h>
        #include <stdlib.h>

        #include "help.h"

        long num_unfreed_mallocs = 0;

        typedef struct {
                int i;
                char *c;
                float f;
        } struct_t;


        void print_struct(void *v) {
                struct_t *s = v;
                printf("%i %s %f\n", s->i, s->c, s->f);
        }

        int main() {

                struct_t *s = malloc(sizeof(*s));
                s->i = 1;
                s->c = "2";
                s->f = 3;

                add_print_func_to_malloc(s, print_struct);
                print_malloc_info((void *) s);

        }







































*/
