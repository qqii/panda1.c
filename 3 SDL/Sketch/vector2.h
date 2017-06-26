#ifndef VECTOR2_H
#define VECTOR2_H

#include <stdbool.h>

typedef struct Vector2i{
    int x;
    int y;
} Vector2i;

Vector2i new_vector2i(int x, int y);

bool eq_vector2i(Vector2i vec1, Vector2i vec2);

Vector2i mul_vector2i(Vector2i vec, int mul);
Vector2i add_vector2i(Vector2i vec1, Vector2i vec2);
Vector2i sub_vector2i(Vector2i vec1, Vector2i vec2);

void mulip_vector2i(Vector2i *vec, int mul);
void addip_vector2i(Vector2i *vec1, Vector2i vec2);
void subip_vector2i(Vector2i *vec1, Vector2i vec2);

#endif
