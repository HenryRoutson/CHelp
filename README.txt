
This is a memory debugger I'm writing to make writing c easier

To set it up, just copy all of the files starting with help in your c project
And then read the file help_readme.h to setup and configure


Features

+ Auto assert mallocs and check if the size is negative or zero
+ Auto null after free
+ Assert all memory is freed at the end of a program running
+ Store messages for individual mallocs 
+ Store print functions for each malloc, so you can create generic print functions for debugging

Pros

+ Runs in O(1) overhead (with check functions disabled) 
+ Uses static memory allocation, there is no chance for memory leaks
+ Uses Automated testing 