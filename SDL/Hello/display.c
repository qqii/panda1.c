/* Graphics for a blue sky */

#include <SDL/SDL.h>

void run() {
    int w=640, h=480;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface *surface =
        SDL_SetVideoMode(w, h, 32, SDL_SWSURFACE);
    Uint32 skyBlue =
        SDL_MapRGB(surface->format, 100, 149, 237);
    SDL_FillRect(surface, NULL, skyBlue);
    SDL_UpdateRect(surface, 0, 0, 0, 0);
    SDL_Delay(10000);
    SDL_Quit();
}
