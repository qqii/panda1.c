GCC = gcc -std=c99 -O3 -Wall -Werror -pedantic
LAB_SDL2 = -I/opt/SDL/2.0.3/include -L/opt/SDL/2.0.3/lib -Wl,-rpath,/opt/SDL/2.0.3/lib

run: clean build
	./sky.o

build: sky_sdl2

sky_sdl1:
	$(GCC) sky.c display.c -lSDL -o sky.o

sky_sdl2:
	# One would need to edit sky.c to include display2.c
	$(GCC) $(LAB_SDL2) sky.c display2.c -lSDL2 -o sky.o

clean:
	rm -f sky.o
