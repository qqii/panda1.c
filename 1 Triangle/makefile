GCC = gcc -std=c99 -O3 -Wall -Werror -pedantic

run: build
	./triangle.o

build: clean triangle.o

triangle.o: triangle.c
	$(GCC) triangle.c -o triangle.o

clean:
	rm -f triangle.o
