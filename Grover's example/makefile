Grovers : Grovers.o quantum.o clinalg.o
	gcc -g -o Grovers Grovers.o quantum.o clinalg.o

Grovers.o : Grovers.c quantum.c quantum.h clinalg.c clinalg.h
	gcc -c -g Grovers.c	

quantum.o : quantum.c quantum.h
	gcc -c -g quantum.c

clinalg.o : clinalg.c clinalg.h
	gcc -c -g clinalg.c

clean:
	rm *.o

run:
	./Grovers