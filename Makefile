
CC=gcc
OBJ= help.o 
CFLAGS= -Wall -g -Werror -O3

TESTS =  tests/1_main tests/2_main tests/3_main tests/4_main tests/5_main tests/6_main tests/7_main tests/8_main tests/9_main tests/10_main
HEADERS = help_structs.h help_readme.h help.h

# executable depends on object files

all: $(TESTS)

tests/1_main: $(OBJ) tests/1_main.o $(HEADERS)
	$(CC) -o tests/1_main tests/1_main.c $(OBJ) $(CFLAGS)

tests/2_main: $(OBJ) tests/2_main.o $(HEADERS)
	$(CC) -o tests/2_main tests/2_main.c $(OBJ) $(CFLAGS)
 
tests/3_main: $(OBJ) tests/3_main.o tests/3_external.o $(HEADERS)
	$(CC) -o tests/3_main tests/3_main.c tests/3_external.o $(OBJ) $(CFLAGS)

tests/4_main: $(OBJ) tests/4_main.o $(HEADERS)
	$(CC) -o tests/4_main tests/4_main.c $(OBJ) $(CFLAGS)

tests/5_main: $(OBJ) tests/5_main.o $(HEADERS)
	$(CC) -o tests/5_main tests/5_main.c $(OBJ) $(CFLAGS)

tests/6_main: $(OBJ) tests/6_main.o $(HEADERS)
	$(CC) -o tests/6_main tests/6_main.c $(OBJ) $(CFLAGS)

tests/7_main: $(OBJ) tests/7_main.o $(HEADERS)
	$(CC) -o tests/7_main tests/7_main.c $(OBJ) $(CFLAGS)

tests/8_main: $(OBJ) tests/8_main.o $(HEADERS)
	$(CC) -o tests/8_main tests/8_main.c $(OBJ) $(CFLAGS)

tests/9_main: $(OBJ) tests/9_main.o $(HEADERS)
	$(CC) -o tests/9_main tests/9_main.c $(OBJ) $(CFLAGS)

tests/10_main: $(OBJ) tests/10_main.o $(HEADERS)
	$(CC) -o tests/10_main tests/10_main.c $(OBJ) $(CFLAGS)

# o depends on c
%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

format:
	clang-format -style=file -i *.c

clean:
	rm -f -rf $(EXE) *.o $(TESTS) tests/*.o tests/*dSYM

RUNWITH = 
# RUNWITH = valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all

test: all
	
	./tests/1_main | grep -q "Error: malloc size may be negative, unsigned value was -1" 
	./tests/2_main | grep -q "TEST: PASSED" 
	./tests/3_main | grep -q "TEST: PASSED" 
	./tests/4_main | grep -q "file_name   : tests/4_main.c" 
	./tests/5_main | grep -q "This is a number: 10" 
	./tests/6_main | grep -q "1 2 3" 
	./tests/7_main | grep -q "ERROR: wrong number of unfreed mallocs" 
	./tests/8_main | grep -q "1 s1 3.000000" 
	./tests/9_main | grep -q "FREED" 
	./tests/10_main | grep -q "TEST: PASSED" 

run: all
	
	-./tests/1_main
	-./tests/2_main
	-./tests/3_main
	-./tests/4_main
	-./tests/5_main
	-./tests/6_main
	-./tests/7_main
	-./tests/8_main
	-./tests/9_main 
	-./tests/10_main 