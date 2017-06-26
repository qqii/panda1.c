GCC = gcc -std=c99 -O3 -Wall -Werror -pedantic

build: clean calc.o

calc.o: calc.c stack.h stack.c
	$(GCC) calc.c stack.c -o calc.o

clean:
	rm calc.o
