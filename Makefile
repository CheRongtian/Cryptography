all: arcfour example

example: example.o
	clang example.o arcfour.o -o example -Wall -O2

example.o: example.c
	clang -c -O2 -Wall example.c

arcfour: arcfour.o
	clang arcfour.o -o arcfour.so -O2 -Wall -fPIC -shared -ldl -D_GNU_SOURCE

arcfour.o: arcfour.c
	clang -c -O2 -Wall arcfour.c

clean:
	rm -f *.o *.so example