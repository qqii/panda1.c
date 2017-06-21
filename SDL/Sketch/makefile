GCC = gcc -std=c99 -O3 -Wall -Werror -pedantic
LAB_SDL2 = -I/opt/SDL/2.0.3/include -L/opt/SDL/2.0.3/lib -Wl,-rpath,/opt/SDL/2.0.3/lib
FILES = sketch.c display.c vector2.c state.c interpret.c
OUTFILE = sketch.o

all: sketch_sdl2

sketch_sdl2:
	$(GCC) $(LAB_SDL2) $(FILES) -lSDL2 -o $(OUTFILE)
