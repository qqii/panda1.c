#include "state.h"

State new_state(Vector2i startpos){
    State c = {
        .pos = startpos,
        .pendownpos = new_vector2i(0, 0),
        .pendown = false,
        .rgba = 0x000000FF
    };

    return c;
}

void toggle_pen_state(State *s){
    if(s->pendown){
        s->pendownpos = new_vector2i(0, 0);
    }else if(!s->pendown){
        s->pendownpos = s->pos;
    }

    s->pendown = !(s->pendown);
}

void move_state(State *s, Vector2i vec){
    addip_vector2i(&(s->pos), vec);
}

void setr_state(State *s, unsigned char red){
    int RED_MASK = 0x00FFFFFF;
    s->rgba = (s->rgba & RED_MASK) | (red << 24);
}

void setg_state(State *s, unsigned char green){
    int GREEN_MASK = 0xFF00FFFF;
    s->rgba = (s->rgba & GREEN_MASK) | (green << 16);
}

void setb_state(State *s, unsigned char blue){
    int BLUE_MASK = 0xFFFF00FF;
    s->rgba = (s->rgba & BLUE_MASK) | (blue << 8);
}
void seta_state(State *s, unsigned char alpha){
    int ALPHA_MASK = 0xFFFFFF00;
    s->rgba = (s->rgba & ALPHA_MASK) | alpha;
}
