#ifndef INTERPRET_H
#define INTERPRET_H

#include <stdio.h>
#include <stdlib.h>

#include "display.h"
#include "state.h"

typedef struct Operation{
    unsigned char opcode;
    unsigned char operand;
} Operation;

typedef struct InstructionTable{
    unsigned char opcode;
    void (*function)(Operation op, State *s, display *d, FILE *file);
} InstructionTable;

void print_uchar(unsigned char op, bool newline);
void print_op(Operation op, bool newline);
void print_vector2i(Vector2i vec, bool newline);
void print_state(State c, bool newline);

unsigned char to_opcode(unsigned char operation);
unsigned char to_operand(unsigned char operation);
int to_int(unsigned char operand, bool is_signed);
int extend_to_int(unsigned char op1, FILE *file, bool is_signed);

Operation new_operation(unsigned char ocode, unsigned char orand);
InstructionTable new_instructiontable(unsigned char opcode, void (*f)(Operation op, State *s, display *d, FILE *file));

void dx(Operation op, State *s, display *d, FILE *file);
void dy(Operation op, State *s, display *d, FILE *file);
void pen(Operation op, State *s, display *d, FILE *file);
void dt(Operation op, State *s, display *d, FILE *file);
void clear_screen(Operation op, State *s, display *d, FILE *file);
void wait_for_key(Operation op, State *s, display *d, FILE *file);

void interpret(Operation op, State *s, display *d, FILE *file, InstructionTable table[], int n);

#endif
