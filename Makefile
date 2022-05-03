GCC = gcc-11
FLAGS = -ansi -pedantic -Wall -std=c99
CFLAGS = -lm -lpthread -fopenmp 
THEPROGS=MM1c MM1f MMPosix MM1cOMP MM1fOMP

PROGS: MM1c MM1f MMPosix MM1cOMP MM1fOMP

MM1c:
	$(GCC) $(FLAGS) module.c -c 
	$(GCC) $(FLAGS) $@.c -c 
	$(GCC) $(FLAGS) module.o $@.o -o $@

MM1cOMP:
	$(GCC) $(FLAGS) module.c -c $(CFLAGS)
	$(GCC) $(FLAGS) $@.c -c $(CFLAGS)
	$(GCC) $(FLAGS) module.o $@.o -o $@ $(CFLAGS)
	
MM1fOMP:
	$(GCC) $(FLAGS) module.c -c $(CFLAGS)
	$(GCC) $(FLAGS) $@.c -c $(CFLAGS)
	$(GCC) $(FLAGS) module.o $@.o -o $@ $(CFLAGS)
	
	
MM1f:
	$(GCC) $(FLAGS) module.c -c 
	$(GCC) $(FLAGS) $@.c -c 
	$(GCC) $(FLAGS) module.o $@.o -o $@
		
MMPosix:
	$(GCC) $(FLAGS) module.c -c $(CFLAGS)
	$(GCC) $(FLAGS) $@.c -c $(CFLAGS) 
	$(GCC) $(FLAGS) module.o $@.o -o $@ $(CFLAGS) 

clean:
	$(RM) $(THEPROGS) *.o
