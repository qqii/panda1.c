#ifndef RENDER_H
#define RENDER_H

#include <string.h>

#include <ncurses.h>

#include "vector2.h"
#include "rect.h"
#include "entity.h"

Vector2i screen_size(WINDOW *window);

void print_center(WINDOW *window, char *string);
void print_vertical_string(WINDOW *window, int y, int x, char *string);
void print_vertical_chars(WINDOW *window, int y, int x, char character);

void render_ball(WINDOW *window, Ball b);
void render_paddle(WINDOW *window, Paddle p);

#endif