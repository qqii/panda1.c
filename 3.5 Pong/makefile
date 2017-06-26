GCC = gcc -O3 -std=c99 -pedantic -Wall -Werror

run: build
	./pong.o

build: clean pong.o

pong.o:
	$(GCC) entity.c pong.c rect.c render.c vector2.c -lncurses -o pong.o

clean:
	rm -f pong.o
