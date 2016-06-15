BellState : BellState.o quantum.o
	gcc -g -o BellState BellState.o quantum.o

BellState.o : BellState.c quantum.c quantum.h
	gcc -c -g BellState.c	

quantum.o : quantum.c quantum.h
	gcc -c -g quantum.c

clean:
	rm *.o

run:
	./BellState