/* Graphics for blue sky. */

#include <SDL2/SDL.h>

void run() {
    int w=640, h=480;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window =
        SDL_CreateWindow("Sky", 100, 100, w, h, 0);
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    Uint32 skyBlue =
        SDL_MapRGB(surface->format, 100, 149, 237);
    SDL_FillRect(surface, NULL, skyBlue);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(10000);
    SDL_Quit();
}
