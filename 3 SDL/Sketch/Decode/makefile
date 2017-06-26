GCC = gcc -std=c99 -O3 -Wall -Werror -pedantic
FILES = decode.c interpret.c
OUTFILE = decode.o

run: build
	./$(OUTFILE)

build: clean decode

decode:
	$(GCC) $(FILES) -o $(OUTFILE)
	
clean:
		rm -f $(OUTFILE)
