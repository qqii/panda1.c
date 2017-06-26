#ifndef RECT_H
#define RECT_H

#include <stdbool.h>

#include "vector2.h"

typedef struct Rect{
    float x;
    float y;
    float w;
    float h;
} Rect;

Rect new_rect(float x, float y, float w, float h);

Vector2f rect_center_f(Rect r);
Vector2i rect_center_i(Rect r);

float rect_left(Rect r);
float rect_right(Rect r);
float rect_top(Rect r);
float rect_bottom(Rect r);

bool rect_intersect(Rect a, Rect b);

#endif