GCC = gcc -std=c99 -O3 -Wall -Werror -pedantic

all: decode

DECODE_I = decode.c interpret.c
DECODE_O = decode.o
decode:
	$(GCC) $(DECODE_I) -o $(DECODE_O)