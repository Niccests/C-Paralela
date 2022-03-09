GCC = gcc
FLAGS = -pedantic -Wall
CFLAGS = -lm -pthread

PROGS = MM1c MM1f

MM1c:
	$(GCC) $(FLAGS) modulo.c -c
	$(GCC) $(FLAGS) $@.c -c
	$(GCC) $(FLAGS) $@.c modulo.o -o $@

MM1f:
	$(GCC) $(FLAGS) modulo.c -c
	$(GCC) $(FLAGS) $@.c -c
	$(GCC) $(FLAGS) $@.c modulo.o -o $@

clean:
	$(RM) $(PROGS) *.o
	
