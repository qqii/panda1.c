#ifndef VECTOR2_H
#define VECTOR2_H

typedef struct Vector2f{
    float x;
    float y;
} Vector2f;

typedef struct Vector2i{
    int x;
    int y;
} Vector2i;

Vector2f new_vector2f(float x, float y);
Vector2i new_vector2i(int x, int y);

Vector2f vector2i_to_f(Vector2i v2i);
Vector2i vector2f_to_i(Vector2f v2f);

#endif