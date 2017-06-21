GCC = gcc -std=c99 -O3 -Wall -Werror -pedantic

build: phone.o count.o

count.o: count.c map.o io.o
	$(GCC) count.c io.o map.o binarytree.o wordcount.o -o count.o 

phone.o: phone.c binarytree.o io.o
	$(GCC) phone.c io.o binarytree.o wordcount.o -o phone.o 

map.o: map.h map.c binarytree.o
	$(GCC) -c map.c -o map.o

binarytree.o: binarytree.h binarytree.c wordcount.o
	$(GCC) -c binarytree.c -o binarytree.o 

wordcount.o: wordcount.h wordcount.c
	$(GCC) -c wordcount.c -o wordcount.o 

io.o: io.h io.c
	$(GCC) -c io.c -o io.o

clean:
	rm -f *.o
