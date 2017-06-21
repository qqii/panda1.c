#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "display.h"

#include "state.h"
#include "interpret.h"

void extend_dx(Operation op, State *s, display *d, FILE *file){
    move_state(s, new_vector2i(extend_to_int(op.operand, file, true), 0));
}

void extend_dy(Operation op, State *s, display *d, FILE *file){
    move_state(s, new_vector2i(0, extend_to_int(op.operand, file, true)));
}

void extend_dt(Operation op, State *s, display *d, FILE *file){
    if(s->pendown && !eq_vector2i(s->pendownpos, s->pos)){
        pen(op, s, d, file);
        pen(op, s, d, file);
    }
    pause(d, extend_to_int(op.operand, file, false));
}

unsigned char extend_get_rgba(unsigned char operand, FILE *file){
    int c = extend_to_int(operand, file, false);
    if(c > 255){
        printf("Invalid rgba value.\n");
        exit(1);
    }

    return (unsigned char) c;
}

void extend_r(Operation op, State *s, display *d, FILE *file){
    setr_state(s, extend_get_rgba(op.operand, file));
}

void extend_g(Operation op, State *s, display *d, FILE *file){
    setg_state(s, extend_get_rgba(op.operand, file));
}

void extend_b(Operation op, State *s, display *d, FILE *file){
    setb_state(s, extend_get_rgba(op.operand, file));
}

void extend_a(Operation op, State *s, display *d, FILE *file){
    seta_state(s, extend_get_rgba(op.operand, file));
}

void extend(Operation op, State *s, display *d, FILE *file){
    const unsigned char VARIABLE_LENGTH_OPERAND_MASK = 0x1F;

    Operation new_op = new_operation(op.operand & VARIABLE_LENGTH_OPERAND_MASK, 0);
    if(op.operand >> 5){
        new_op.operand = fgetc(file);
    }

    InstructionTable table[10] = {
        new_instructiontable(0, &extend_dx),
        new_instructiontable(1, &extend_dy),
        new_instructiontable(2, &extend_dt),
        new_instructiontable(3, &pen),
        new_instructiontable(4, &clear_screen),
        new_instructiontable(5, &wait_for_key),
        new_instructiontable(6, &extend_r),
        new_instructiontable(7, &extend_g),
        new_instructiontable(8, &extend_b),
        new_instructiontable(9, &extend_a)
    };

    interpret(new_op, s, d, file, table, 10);
}


void run(char *filename, bool testing) {
    FILE *in = fopen(filename, "rb");
    if (in == NULL) {
        printf("Can't open %s\n", filename);
        exit(1);
    }

    display *d = newDisplay(filename, 200, 200, testing);
    State c = new_state(new_vector2i(0, 0));
    InstructionTable table[4] = {
        new_instructiontable(0, &dx),
        new_instructiontable(1, &dy),
        new_instructiontable(2, &dt),
        new_instructiontable(3, &extend),
    };

    unsigned char b = fgetc(in);
    while(!feof(in)){
        Operation op = new_operation(to_opcode(b), to_operand(b));
        interpret(op, &c, d, in, table, 4);
        //print_state(c, true);
        b = fgetc(in);
    }
    fclose(in);

    end(d);

    if (testing) printf("Sketch %s OK\n", filename);
}

// ----------------------------------------------------------------------------
// Nothing below this point needs to be changed.
// ----------------------------------------------------------------------------

void testSketches() {
    // Stage 1
    run("line.sketch", true);
    run("square.sketch", true);
    run("box.sketch", true);
    run("oxo.sketch", true);

    // Stage 2
    run("diag.sketch", true);
    run("cross.sketch", true);

    // Stage 3
    run("clear.sketch", true);
    run("key.sketch", true);

    // Stage 4
    run("pauses.sketch", true);
    run("field.sketch", true);
    run("lawn.sketch", true);
}

int main(int n, char *args[n]) {
    if (n == 1) testSketches();
    else if (n == 2) run(args[1], false);
    else {
        fprintf(stderr, "Usage: sketch [file.sketch]");
        exit(1);
    }
}
