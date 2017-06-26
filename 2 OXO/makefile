GCC = gcc -std=c99 -O3 -Wall -Werror -pedantic

run: build
	./oxo.o -t

build: clean oxo.o

oxo.o: oxo.c
	$(GCC) oxo.c -o oxo.o

clean:
	rm -f oxo.o
