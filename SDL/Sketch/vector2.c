#include "vector2.h"

Vector2i new_vector2i(int x, int y){
    Vector2i v2i = {
        .x = x,
        .y = y
    };

    return v2i;
}

bool eq_vector2i(Vector2i vec1, Vector2i vec2){
    return vec1.x == vec2.x && vec1.y == vec2.y;
}

Vector2i mul_vector2i(Vector2i vec, int mul){
    return new_vector2i(vec.x*mul, vec.y*mul);
}

Vector2i add_vector2i(Vector2i vec1, Vector2i vec2){
    return new_vector2i(vec1.x+vec2.x, vec1.y+vec2.y);
}

Vector2i sub_vector2i(Vector2i vec1, Vector2i vec2){
    return new_vector2i(vec1.x-vec2.x, vec1.y-vec2.y);
}

void mulip_vector2i(Vector2i *vec, int mul){
    vec->x *= mul;
    vec->y *= mul;
}

void addip_vector2i(Vector2i *vec1, Vector2i vec2){
    vec1->x += vec2.x;
    vec1->y += vec2.y;
}

void subip_vector2i(Vector2i *vec1, Vector2i vec2){
    vec1->x -= vec2.x;
    vec1->y -= vec2.y;
}
