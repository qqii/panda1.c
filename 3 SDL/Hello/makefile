GCC = gcc -std=c99 -O3 -Wall -Werror -pedantic

run: clean build
	./sky.o

build: sky_sdl2

sky_sdl1:
	$(GCC) sky.c display.c -lSDL -o sky.o

sky_sdl2:
	# One would need to edit sky.c to include display2.c
	$(GCC) sky.c display2.c -lSDL2 -o sky.o

clean:
	rm -f sky.o
