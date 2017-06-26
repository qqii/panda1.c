#include "entity.h"

void init_entity(){
    srand(time(NULL));
}

Paddle new_paddle(Vector2i center, Vector2i screensize, char display){
    //TODO: Make this depend on screensize.x, screensize.y
    const int paddle_height = screensize.y / 4;

    Paddle p = {
        .boundingbox = new_rect(center.x - 0.5, center.y - paddle_height/2, 1, paddle_height),
        .velocity = {
            .x = 0,
            .y = 0
        },
        .displaychar = display
    };

    return p;
}


Player new_player(Vector2i center, Vector2i screensize, char display, char up, char stop, char down){
    Player p = {
        .paddle = new_paddle(center, screensize, display),
        .input = {up, stop, down},
        .score = 0
    };

    return p;
}

Ball new_ball(Vector2i screensize, char display){
    //TODO: Make this depend on screensize.x, screensize.y
    float vx, vy;
    vx = screensize.x/5 + rand()%(screensize.x/10);
    vy = screensize.y/4 + rand()%(screensize.y/6);

    // generate vy
    if(rand() % 2){
        vy *= -1;
    }
    // calculate vx
    if(rand() % 2){
        vx *= -1;
    }

    //TODO?: make ball bigger if screen is bigger?
    Ball b = {
        .boundingbox = new_rect((screensize.x/2)-0.5, (screensize.y/2)-0.5, 1, 1),
        .velocity = {
            .x = vx,
            .y = vy
        },
        .displaychar = display
    };

    return b;
}

void update_ball(Ball *b, clock_t tick_time, Vector2i screensize){
    float time_passed = (float)tick_time/(float)CLOCKS_PER_SEC;

    //float next_x = (b->boundingbox).x + (b->velocity).x * time_passed;
    float next_y = (b->boundingbox).y + (b->velocity).y * time_passed;


    /* Uncomment this and comment out "erase();" in pong.c for some pretty patterns.
    if(next_x < 0-10){
        (b->boundingbox).x = 0;
        (b->velocity).x *= -1;
    }else if(next_x+(b->boundingbox).w > screensize.x+10){
        (b->boundingbox).x = screensize.x-(b->boundingbox).w;
        (b->velocity).x *= -1;
    }*/
    //TODO: actual collisions instead of this hack
    if(next_y < 0){
        (b->boundingbox).y = 0;
        (b->velocity).y *= -1;
    }else if(next_y+(b->boundingbox).h > screensize.y){
        (b->boundingbox).y = screensize.y-(b->boundingbox).h;
        (b->velocity).y *= -1;
    }

    (b->boundingbox).x += (b->velocity).x * time_passed;
    (b->boundingbox).y += (b->velocity).y * time_passed;
}

void update_paddle(Paddle *p, clock_t tick_time, Vector2i screensize, Ball *b){
    float time_passed = (float)tick_time/(float)CLOCKS_PER_SEC;
    Rect b_next = new_rect(
        (b->boundingbox).x,
        (b->boundingbox).y,
        (b->boundingbox).w,
        (b->boundingbox).h);

    b_next.x += (b->velocity).x * time_passed;
    b_next.y += (b->velocity).y * time_passed;

    //TODO: stop relying on an early bounce
    if(rect_intersect(b_next, p->boundingbox)){
        //TODO?: possibly increase ths velocity every bounce
        (b->velocity).x *= -1;
    }

    if(rect_bottom(p->boundingbox) < 0){
        (p->boundingbox).y = 0;
        p->velocity.y = 0;
    }else if(rect_top(p->boundingbox) > screensize.y){
        (p->boundingbox).y = screensize.y-(p->boundingbox).h;
        p->velocity.y = 0;
    }

    (p->boundingbox).y += (p->velocity).y * time_passed;
}

void update_player(Player *p, clock_t tick_time, Vector2i screensize, int ch, Ball *b){
    //TODO: Make this depend on screensize.x, screensize.y
    const int paddle_velocity = (screensize.y*1.5)/(screensize.x/abs((b->velocity).x));

    if(ch == (p->input)[0]){
        (p->paddle).velocity.y = paddle_velocity;
    }else if(ch == (p->input)[1]){
        (p->paddle).velocity.y = 0;
    }else if(ch == (p->input)[2]){
        (p->paddle).velocity.y = -paddle_velocity;
    }
    update_paddle(&(p->paddle), tick_time, screensize, b);
}
