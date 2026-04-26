arcfour: arcfour.o
	clang arcfour.o -o arcfour.so -O2 -Wall -fPIC -shared -ldl -D_GNU_SOURCE
arcfour: arcfour.c
	clang -c -O2 -Wall arcfour.c