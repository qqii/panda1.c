GCC = gcc -std=c99 -O3 -Wall -Werror -pedantic

run: build
	./calc.o

build: clean calc.o

calc.o: calc.c stack.h stack.c
	$(GCC) calc.c stack.c -o calc.o

clean:
	rm -r calc.o
