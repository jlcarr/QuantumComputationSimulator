BB84 : BB84.o quantum.o
	gcc -g -o BB84 BB84.o quantum.o

BB84.o : BB84.c quantum.c quantum.h
	gcc -c -g BB84.c	

quantum.o : quantum.c quantum.h
	gcc -c -g quantum.c

clean:
	rm *.o

run:
	./BB84