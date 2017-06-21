#include "rect.h"

Rect new_rect(float x, float y, float w, float h){
    Rect r = {
        .x = x,
        .y = y,
        .w = w,
        .h = h
    };

    return r;
}

Vector2f rect_center_f(Rect r){
    Vector2f center = {
        .x = (r.x + r.w/2),
        .y = (r.y + r.h/2)
    };

    return center;
}

Vector2i rect_center_i(Rect r){
    return vector2f_to_i(rect_center_f(r));
}

float rect_left(Rect r){
    return r.x;
}

float rect_right(Rect r){
    return rect_left(r) + r.w;
}

float rect_top(Rect r){
    return rect_bottom(r) + r.h;
}

float rect_bottom(Rect r){
    return r.y;
}

bool rect_intersect(Rect a, Rect b){
    return rect_left(a) <= rect_right(b) &&
           rect_right(a) >= rect_left(b) &&
           rect_bottom(a) <= rect_top(b) &&
           rect_top(a) >= rect_bottom(b);
}
