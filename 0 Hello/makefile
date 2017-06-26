GCC = gcc -std=c99 -O3 -Wall -Werror -pedantic

run: build
	./hello.o

build: clean hello.o

hello.o: hello.c
	$(GCC) hello.c -o hello.o

clean:
	rm -f hello.o
