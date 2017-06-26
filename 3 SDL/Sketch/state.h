#ifndef STATE_H
#define STATE_H

#include <stdbool.h>
#include "vector2.h"

typedef struct State{
    Vector2i pos;
    Vector2i pendownpos;
    bool pendown;
    int rgba;
} State;

State new_state(Vector2i startpos);

void toggle_pen_state(State *s);
void move_state(State *s, Vector2i vec);
void setr_state(State *s, unsigned char red);
void setg_state(State *s, unsigned char green);
void setb_state(State *s, unsigned char blue);
void seta_state(State *s, unsigned char alpha);

#endif
