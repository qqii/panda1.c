#ifndef ENTITY_H
#define ENTITY_H

#include <stdlib.h>	// for rand() function
#include <time.h>

#include "vector2.h"
#include "rect.h"

typedef struct Entity{
    Rect boundingbox;
    Vector2f velocity;
    char displaychar;
} Entity;
typedef Entity Ball;
typedef Entity Paddle;

//TODO?: Is a stop key needed?
typedef struct Player{
    Paddle paddle;
    char input[4];
    // input[0] = <up>,
    // input[1] = <stop>,
    // input[2] = <down>,
    // input[3] = '\0'
    int score;
} Player;

void init_entity();

Paddle new_paddle(Vector2i center, Vector2i screensize, char display);
Player new_player(Vector2i center, Vector2i screensize, char display, char up, char stop, char down);
Ball new_ball(Vector2i screensize, char display);

void update_ball(Ball *b, clock_t tick_time, Vector2i screensize);
void update_paddle(Paddle *p, clock_t tick_time, Vector2i screensize, Ball *b);
void update_player(Player *p, clock_t tick_time, Vector2i screensize, int ch, Ball *b);

#endif
