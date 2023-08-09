
# How CHELP works

At its core, CHelp counts of how many allocations remain at the end of your program.
If there are more than 0, you have a memory leak.

This is obviously extremely performant.

Done manually the process looks like this.


```C

// done manually

#include <stdlib.h>
#include <assert.h>

long num_unfreed_allocs = 0;

int main() {

  int *allocation = malloc(sizeof(int) * 10);
  num_unfreed_allocs++;
  
  free(allocation);
  num_unfreed_allocs--; 
  
  assert(num_unfreed_allocs == 0); // no memory leaks!
}

```


Tracking the number of unfreed allocations can be automated.


```C

// done automatically

#include <stdlib.h>
#include <assert.h>

#define malloc(s) malloc(s); num_unfreed_allocs++;
#define free(p)     free(p); num_unfreed_allocs--;
// other functions are required ...

long num_unfreed_allocs = 0;

int main() {

  int *allocation = malloc(sizeof(int) * 10);
  free(allocation);
  
  assert(num_unfreed_allocs == 0); // no memory leaks!
}


```

And then extracted into external files and functions used to make error output better.

```C


#include <stdlib.h>
#include <assert.h>
#include "help/help.h"

CHELP_MAIN_MACRO

int main() {

  int *allocation = malloc(sizeof(int) * 10);
  free(allocation);
  
  n_unfreed(0); // no memory leaks!
}


```

And so now we have an easy way of detecting memory leaks.


# Other advanced features of CHELP


Obviously just knowing there is a problem isn't that helpful, so at this point you could probably just use rerun using valgrind, and there is a simple version of CHelp if want to this, However ...


# Valgrind 

Compared to Chelp, Valgrind ... 

```

- Isn’t cross platform

- Is often run only run occasionally, 
  allowing bugs to build up
  and obfuscating what changes caused them.

- Requires you to recreate error contitions.

- Is comparatively slow.

- Provides limited information about leaked memory.

- Doesn't allow you to attatch extra information to allocations.

- Doesn't allow you to print out allocations when they occur.

+ Has functionality for other errors CHelp doesn't have. 
  You should use CHelp and valgrind in conjunction when developing C.


```
