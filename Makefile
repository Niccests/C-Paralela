GCC = gcc 
FLAGS = -std=c99 -pthread
PROGS = Posix01

all: Posix01

Posix01:
		$(GCC) $(FLAGS) $@.c -c
		$(GCC) $(FLAGS) modulo.c -c
		$(GCC) $(FLAGS) modulo.o $@.o -o $@

clean:
		$(RM) $(PROGS) *.o
