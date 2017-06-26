GCC = gcc -std=c99 -O3 -Wall -Werror -pedantic

test: main.o
	./main.o test

build: main.o

run: main.o
	./main.o

main.o: main.c io.o memsim.o ring.o
	$(GCC) main.c io.o memsim.o ring.o -o main.o

memsim.o: memsim.h memsim.c
	$(GCC) -c memsim.c -o memsim.o

ring.o: ring.h ring.c
	$(GCC) -c ring.c -o ring.o 

io.o: io.h io.c
	$(GCC) -c io.c -o io.o

clean:
	rm -f io.o ring.o memsim.o main.o
