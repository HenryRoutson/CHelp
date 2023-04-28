
This is a memory debugger I'm writing to make writing c easier

Features

+ Auto assert mallocs and check if the size is negative or zero
+ Auto null after free
+ Assert all memory is freed at the end of a program running
+ Store messages for individual mallocs 
+ Store print functions for each malloc, so you can create generic print functions for debugging

Pros

+ Runs in O(1) overhead
+ Uses static memory allocation, there is no chance for memory leaks
