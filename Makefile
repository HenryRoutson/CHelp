
CC=gcc
OBJ= help.o 
CFLAGS= -Wall -g -Werror -O3

TESTS =  tests/1_main tests/2_main tests/3_main tests/4_main

# executable depends on object files

all: $(TESTS)

tests/1_main: $(OBJ) tests/1_main.o
	$(CC) -o tests/1_main tests/1_main.c $(OBJ) $(CFLAGS)

tests/2_main: $(OBJ) tests/2_main.o
	$(CC) -o tests/2_main tests/2_main.c $(OBJ) $(CFLAGS)

tests/3_main: $(OBJ) tests/3_main.o tests/3_external.o
	$(CC) -o tests/3_main tests/3_main.c tests/3_external.o $(OBJ) $(CFLAGS)

tests/4_main: $(OBJ) tests/4_main.o
	$(CC) -o tests/4_main tests/4_main.c $(OBJ) $(CFLAGS)

# o depends on c
%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

format:
	clang-format -style=file -i *.c

clean:
	rm -f -rf $(EXE) *.o $(TESTS) tests/*.o tests/*dSYM

RUNWITH = 
# RUNWITH = valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all

run: all
	
	./tests/1_main | grep -q "Error: malloc size may be negative, unsigned value was -1" 
	./tests/2_main | grep -q "TEST: PASSED" 
	./tests/3_main | grep -q "TEST: PASSED" 
	./tests/4_main | grep -q "file_name tests/4_main.c\nline_number  11" 
	
