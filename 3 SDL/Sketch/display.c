// You do not need to change this file.
// And you do not need to understand anything in this file.

#include "display.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct display {
    bool testing;
    int width, height;
    SDL_Renderer *renderer;
    char *file;
    FILE *input;
    char *actual;
};

// Fail, including the SDL error message if any, and stop the program.
static void fail(char *s1, char *s2) {
    fprintf(stderr, "%s %s %s\n", s1, s2, SDL_GetError());
    SDL_Quit();
    exit(1);
}

// Check an actual call against the next expected call.
static void check(display *d) {
    char expected[100];
    if (fgets(expected, 100, d->input) == NULL) {
        if (expected == NULL) {
            printf("fgets(expected, 100, d->input) == expected == NULL in check\n");
        }
    }
    expected[strcspn(expected, "\r\n")] = '\0';
    bool ended = feof(d->input);
    if (!ended && strcmp(d->actual, expected) == 0) return;
    fprintf(stderr, "Failure in test file: %s\n", d->file);
    if (ended) fail("Unexpected extra call", d->actual);
    fprintf(stderr, "Bad call  %s\n", d->actual);
    fail("Expecting", expected);
}

// Create a dummy display for testing.
static display *testDisplay(char *file) {
    char *testfile = malloc(100);
    sprintf(testfile, "%s", file);
    int extension = strlen(testfile) - strlen(".sketch");
    testfile[extension] = '\0';
    strcat(testfile, ".test");
    display *d = malloc(sizeof(display));
    d->file = testfile;
    d->testing = true;
    d->actual = malloc(100);
    d->input = fopen(testfile, "r");
    if (d->input == NULL) fail("File not found", testfile);
    return d;
}

display *newDisplay(char *file, int width, int height, bool testing) {
    if (testing) return testDisplay(file);
    display *d = malloc(sizeof(display));
    d->testing = false;
    d->file = file;
    d->width = width;
    d->height = height;
    int result = SDL_Init(SDL_INIT_EVERYTHING);
    if (result < 0) fail("Bad SDL", "");
    SDL_Window *window;
    int x = SDL_WINDOWPOS_UNDEFINED, y = SDL_WINDOWPOS_UNDEFINED;
    window = SDL_CreateWindow(file, x, y, width, height, 0);
    if (window == NULL) fail("Bad window", "");
    d->renderer = SDL_CreateRenderer(window, -1, 0);
    if (d->renderer == NULL) fail("Bad renderer", "");
    SDL_SetRenderDrawColor(d->renderer, 255, 255, 255, 255);
    SDL_RenderClear(d->renderer);
    SDL_RenderPresent(d->renderer);
    return d;
}

void line(display *d, int x0, int y0, int x1, int y1) {
    if (d->testing) {
        sprintf(d->actual, "line(d,%d,%d,%d,%d)", x0, y0, x1, y1);
        check(d);
        return;
    }
    SDL_SetRenderDrawColor(d->renderer, 0, 0, 0, 255);
    int rc = SDL_RenderDrawLine(d->renderer, x0, y0, x1, y1);
    if (rc < 0) fail("Bad line", "");
    SDL_RenderPresent(d->renderer);
}

void cline(display *d, int x0, int y0, int x1, int y1, int rgba) {
    if (d->testing) {
        sprintf(d->actual, "cline(d,%d,%d,%d,%d,%d)", x0, y0, x1, y1, rgba);
        check(d);
        return;
    }
    int r = (rgba >> 24) & 0xFF;
    int g = (rgba >> 16) & 0xFF;
    int b = (rgba >> 8) & 0xFF;
    int a = rgba & 0xFF;
    int rc = SDL_SetRenderDrawColor(d->renderer, r, g, b, a);
    if (rc < 0) fail("Bad set colour", "");
    rc = SDL_RenderDrawLine(d->renderer, x0, y0, x1, y1);
    if (rc < 0) fail("Bad cline", "");
    SDL_RenderPresent(d->renderer);
}

void clear(display *d) {
    if (d->testing) {
        sprintf(d->actual, "clear(d)");
        check(d);
        return;
    }
    SDL_SetRenderDrawColor(d->renderer, 255, 255, 255, 255);
    SDL_RenderClear(d->renderer);
    SDL_RenderPresent(d->renderer);
}

void pause(display *d, int ms) {
    if (d->testing) {
        sprintf(d->actual, "pause(d,%d)", ms);
        check(d);
        return;
    }
    if (ms > 0) SDL_Delay(ms);
}

char key(display *d) {
    if (d->testing) {
        sprintf(d->actual, "key(d)");
        check(d);
        return 0;
    }
    SDL_Event event_structure;
    SDL_Event *event = &event_structure;
    while (true) {
        int r = SDL_WaitEvent(event);
        if (r == 0) fail("Bad event", "");
        if (event->type == SDL_QUIT) {
            SDL_Quit();
            exit(0);
        }
        else if (event->type == SDL_KEYUP) {
            int sym = event->key.keysym.sym;
            return (char)sym;
        }
    }
}

void end(display *d) {
    if (d->testing) {
        char expected[100];
        if (fgets(expected, 100, d->input) == NULL) {
            if (expected == NULL) {
                printf("fgets(expected, 100, d->input) == expected == NULL in end\n");
            }
        }
        if (! feof(d->input)) {
            fprintf(stderr, "Failure in test file: %s\n", d->file);
            fail("Expecting further call", expected);
        }
    } else {
        SDL_Delay(5000);
        SDL_Quit();
        exit(0);
    }
}
