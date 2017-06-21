#include "interpret.h"

void print_uchar(unsigned char op, bool newline){
    //printf("%4d = ", op);
    //printf("0x%02x = ", op);
    printf("0b");

    for(int i = 7; i >= 0; i--){
        printf("%d", (op >> i) & 1);
    }

    if(newline){
        printf("\n");
    }
}

void print_op(Operation op, bool newline){
    printf("{ .opcode = ");
    print_uchar(op.opcode, false);
    printf(", .operand = ");
    print_uchar(op.operand, false);
    printf(" }\n");
}

void print_vector2i(Vector2i vec, bool newline){
    printf("{.x = %d, .y = %d}", vec.x, vec.y);

    if(newline){
        printf("\n");
    }
}

void print_state(State c, bool newline){
    printf("{.pos = ");
    print_vector2i(c.pos, false);
    printf(", .pendownpos = ");
    print_vector2i(c.pendownpos, false);
    printf(", .pendown = %s}", c.pendown ? "true" : "false");

    if(newline){
        printf("\n");
    }
}

unsigned char to_opcode(unsigned char operation){
    const unsigned char OPCODE_MASK = 0xC0;
    return (operation & OPCODE_MASK) >> 6;
}

unsigned char to_operand(unsigned char operation){
    const unsigned char OPERAND_MASK = 0x3F;
    return (operation & OPERAND_MASK);
}

int to_int(unsigned char operand, bool is_signed){
    const unsigned char SIGNED_POSITIVE_MASK = 0x1F;

    if(is_signed && operand >> 5){
        return (SIGNED_POSITIVE_MASK & operand) - 32;
    }
    return (int) operand;
}

int extend_to_int(unsigned char op1, FILE *file, bool is_signed){
    int return_int = 0;
    unsigned char op = op1;

    int mul = 1;
    for(int i = 0; i < 6; i++){
        if ((op >> i) & 1){
            return_int += mul;
        }
        mul *= 2;
    }
    if((op >> 6) & 0x1){
        if(is_signed){
            return_int -= 64;
        }else if(!is_signed){
            return_int += 64;
        }
    }

    while(op >> 7){
        if(feof(file)){
            printf("Invalid extended operand.\n");
            exit(1);
        }
        op = fgetc(file);

        return_int *= 128;
        int mul = 1;
        for(int i = 0; i < 7; i++){
            if ((op >> i) & 1){
                return_int += mul;
            }
            mul *= 2;
        }
    }

    return return_int;
}

Operation new_operation(unsigned char ocode, unsigned char orand){
    Operation op = {
        .opcode = ocode,
        .operand = orand
    };

    return op;
}

InstructionTable new_instructiontable(unsigned char oc, void (*f)(Operation op, State *s, display *d, FILE *file)){
    InstructionTable table = {
        .opcode = oc,
        .function = f
    };

    return table;
}

void dx(Operation op, State *s, display *d, FILE *file){
    move_state(s, new_vector2i(to_int(op.operand, true), 0));
}

void dy(Operation op, State *s, display *d, FILE *file){
    move_state(s, new_vector2i(0, to_int(op.operand, true)));
}

void pen(Operation op, State *s, display *d, FILE *file){
    if(s->pendown){
        if(s->rgba == 0x000000FF){
            line(d, (s->pendownpos).x, (s->pendownpos).y, (s->pos).x, (s->pos).y);
        }else{
            cline(d, (s->pendownpos).x, (s->pendownpos).y, (s->pos).x, (s->pos).y, s->rgba);
        }

    }
    toggle_pen_state(s);
}

void dt(Operation op, State *s, display *d, FILE *file){
    if(s->pendown && !eq_vector2i(s->pendownpos, s->pos)){
        pen(op, s, d, file);
        pen(op, s, d, file);
    }
    pause(d, to_int(op.operand, false));
}

void clear_screen(Operation op, State *s, display *d, FILE *file){
    clear(d);
    s->pendown = false;
    s->pendownpos = new_vector2i(0, 0);
}

void wait_for_key(Operation op, State *s, display *d, FILE *file){
    key(d);
}

void interpret(Operation op, State *s, display *d, FILE *file, InstructionTable table[], int n){
    for(int i = 0; i < n; i++){
        if(op.opcode == table[i].opcode){
            table[i].function(op, s, d, file);
        }
    }
}
