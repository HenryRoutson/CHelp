

CFLAGS= -Wall -g  -O3  -Wsign-compare -Wint-conversion # -pedantic -Werror -Wextra 
CC = gcc
OBJ = help/help.o 

# o depends on c
%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

# In plain English:
# using the gcc compiler and the chelp object files, compile main_template.c to produce a main_template executable

template: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) main_template.c -o main_template
	./main_template
	-rm main_template



# run 
# make template














# you can delete below this point if you want

# TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING
# TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING
# TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING



























TESTS = tests/0_main tests/1_main tests/2_main tests/3_main tests/4_main tests/5_main tests/6_main tests/7_main tests/8_main tests/9_main tests/10_main tests/11_main tests/12_main tests/13_main tests/14_main tests/15_main   tests_ext/1_ext_main tests_ext/2_ext_main
HEADERS = help/help_structs.h help/help_config.h help/help.h

# executable depends on object files

all: $(TESTS)


tests/0_main: $(OBJ) tests/0_main.o $(HEADERS)
	$(CC) -o tests/0_main tests/0_main.c $(OBJ) $(CFLAGS)

tests/1_main: $(OBJ) tests/1_main.o $(HEADERS)
	$(CC) -o tests/1_main tests/1_main.c $(OBJ) $(CFLAGS)

tests/2_main: $(OBJ) tests/2_main.o $(HEADERS)
	$(CC) -o tests/2_main tests/2_main.c $(OBJ) $(CFLAGS)

tests/3_main: $(OBJ) tests/3_main.o $(HEADERS)
	$(CC) -o tests/3_main tests/3_main.c $(OBJ) $(CFLAGS)

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

tests/11_main: $(OBJ) tests/11_main.o $(HEADERS)
	$(CC) -o tests/11_main tests/11_main.c $(OBJ) $(CFLAGS)

tests/12_main: $(OBJ) tests/12_main.o $(HEADERS)
	$(CC) -o tests/12_main tests/12_main.c $(OBJ) $(CFLAGS)

tests/13_main: $(OBJ) tests/13_main.o $(HEADERS)
	$(CC) -o tests/13_main tests/13_main.c $(OBJ) $(CFLAGS)

tests/14_main: $(OBJ) tests/14_main.o $(HEADERS)
	$(CC) -o tests/14_main tests/14_main.c $(OBJ) $(CFLAGS)

tests/15_main: $(OBJ) tests/15_main.o $(HEADERS)
	$(CC) -o tests/15_main tests/15_main.c $(OBJ) $(CFLAGS)


# tests with external files

EXTERN = tests_ext/external_1.o tests_ext/external_2.o

tests_ext/1_ext_main: $(OBJ) tests_ext/1_ext_main.o $(EXTERN) $(HEADERS)
	$(CC) -o tests_ext/1_ext_main tests_ext/1_ext_main.c $(EXTERN) $(OBJ) $(CFLAGS)

tests_ext/2_ext_main: $(OBJ) tests_ext/2_ext_main.o $(EXTERN) $(HEADERS)
	$(CC) -o tests_ext/2_ext_main tests_ext/2_ext_main.c $(EXTERN) $(OBJ) $(CFLAGS)

format:
	clang-format -style=file -i *.c  *.h

clean:
	find . -name '*.o' -type f -delete
	rm -f -rf $(EXE) $(TESTS) 
	rm -rf *dSYM tests/*dSYM tests_ext/*dSYM 

VGRIND = 
# VGRIND = valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all

# failing tests with ! can fail valgrind
# other tests can also fail
test: all
	
	$(VGRIND) ./tests/0_main  | grep -q "UNFREED" 
	$(VGRIND) ./tests/1_main  | grep -q "TEST: PASSED" 
	$(VGRIND) ./tests/2_main  | grep -q "wrong number of unfreed allocs" # FAILS VGRIND
	$(VGRIND) ./tests/3_main  | grep -q "malloc size may be negative, unsigned value was" 
	$(VGRIND) ./tests/4_main  | grep -q "file_name   : tests/4_main.c" 
	$(VGRIND) ./tests/5_main  | grep -q "This is a number: 10" 
	$(VGRIND) ./tests/6_main  | grep -q "1 2 3" 
	! $(VGRIND) ./tests/7_main > /dev/null # FAILS VGRIND
	$(VGRIND) ./tests/8_main  | grep -q "1 s1 3.000000" 
	$(VGRIND) ./tests/9_main  | grep -q "FREED" # FAILS VGRIND
	$(VGRIND) ./tests/10_main | grep -q "TEST: PASSED" 
	$(VGRIND) ./tests/11_main | grep -q "Test no formatting" 
	$(VGRIND) ./tests/12_main | grep -q "TEST: PASSED" 
	$(VGRIND) ./tests/13_main | grep -q "TEST: PASSED" 
	$(VGRIND) ./tests/14_main | grep -q "TEST: PASSED" 
	$(VGRIND) ./tests/15_main | grep -q "TEST: PASSED" 

	$(VGRIND) ./tests_ext/1_ext_main  | grep -q "TEST: PASSED" 
	! $(VGRIND) ./tests_ext/2_ext_main > /dev/null 

run: all
	
	-$(VGRIND) ./tests/0_main 
	-$(VGRIND) ./tests/1_main
	-$(VGRIND) ./tests/2_main
	-$(VGRIND) ./tests/3_main
	-$(VGRIND) ./tests/4_main
	-$(VGRIND) ./tests/5_main
	-$(VGRIND) ./tests/6_main
	-$(VGRIND) ./tests/7_main
	-$(VGRIND) ./tests/8_main
	-$(VGRIND) ./tests/9_main 
	-$(VGRIND) ./tests/10_main 
	-$(VGRIND) ./tests/11_main 
	-$(VGRIND) ./tests/12_main 
	-$(VGRIND) ./tests/13_main 
	-$(VGRIND) ./tests/14_main 
	-$(VGRIND) ./tests/15_main 

	-$(VGRIND) ./tests_ext/1_ext_main
	-$(VGRIND) ./tests_ext/2_ext_main


	