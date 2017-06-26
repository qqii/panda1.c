GCC = gcc -std=c99 -O3 -Wall -Werror -pedantic

run: build
	./rpncalc.o

build: clean rpncalc.o

rpncalc.o: rpncalc.c
	$(GCC) rpncalc.c -o rpncalc.o

clean:
	rm -f rpncalc.o
