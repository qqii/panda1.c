GCC = gcc -std=c99 -O3 -Wall -Werror -pedantic
FILES = sketch.c display.c vector2.c state.c interpret.c
OUTFILE = sketch.o

run: build
	./$(OUTFILE)

build: clean sketch_sdl2

sketch_sdl2:
	$(GCC) $(FILES) -lSDL2 -o $(OUTFILE)

clean:
	rm -f $(OUTFILE)
