
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

Chelp compared to Valgrind ... 

```

✅ Is cross platform

✅ Runs in the background, rather than only being run occasionally.

  Which avoids ...
  1 Allowing bugs to build up and obfuscating what changes caused them.
  2 Requiring you to rurun recreate error contitions.

✅ Is comparatively fast.

✅ Provides extra information about leaked memory.

✅ Allows you to attatch extra information to allocations.

✅ Allows you to print out allocations and frees when they occur.

✅ Allows you to have assert the number of allocations you should have across multiple points in your programs execution.

✅ Allows you to print all unfreed allocations at any point in your program.

❌ 
  Valgrind has functionality for other errors CHelp doesn't have,
  and simply cannot support.
  You should use CHelp and valgrind in conjunction when developing C.


```

Chelp has a number of features, which in some aspects make it better than Valgrind.


# Credit

```

The idea for this project was largely inspired by this video:

How i program C, Eskil Steenberg
https://www.youtube.com/watch?v=443UNeGrFoM at 48:48

Although implimentation differs significantly

Codebase
https://gamepipeline.org/forge_Debugging_.html



✅ storing data before allocs to make O(n) pointer search O(1)
✅ storing allocation and free counts to for leak checks O(1)  
✅ retaining allocation order
❌ No overallocation (leaving this to valgrind)
❌ No multithreading (yet)

```