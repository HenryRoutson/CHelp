
CC=gcc
EXE=main
OBJ= main.o help.o
CFLAGS= -Wall -g -Werror -O3

# executable depends on object f
$(EXE): $(OBJ) 
	$(CC) $(OBJ) $(CFLAGS) -o $(EXE)

# o depends on c
%.o: %.c %.h
	$(CC) $(CFLAGS) $(CFLAGS) -c -o $@ $<

format:
	clang-format -style=file -i *.c

clean:
	rm -f $(EXE) *.o main

RUNWITH = 
# RUNWITH = valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all

run: $(EXE)
	
	./main | grep -q "Error" 
	
