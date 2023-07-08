
This is a memory debugger I'm writing to make writing c easier

Features

+ Auto assert allocs and check if the size is negative or zero
+ Auto null after free
+ Assert all memory is freed at the end of a program running
+ Store messages for individual allocs 
+ Store print functions for each alloc, so you can create generic print functions for debugging

Pros

+ Runs in O(1) overhead
+ Uses static memory allocation
+ Uses Automated testing 



Setup

copy 
  help (folder)  
into your repo

see main_template.c to see setup required

config is in test/help_config.h
documentation is in help.h

