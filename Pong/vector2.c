#include "vector2.h"

Vector2f new_vector2f(float x, float y){
    Vector2f v2f = {
        .x = x,
        .y = y
    };

    return v2f;
}

Vector2i new_vector2i(int x, int y){
    Vector2i v2i = {
        .x = x,
        .y = y
    };

    return v2i;
}

Vector2f vector2i_to_f(Vector2i v2i){
    return new_vector2f((float)v2i.x, (float)v2i.y);
}

Vector2i vector2f_to_i(Vector2f v2f){
    return new_vector2i((int)v2f.x, (int)v2f.y);
}