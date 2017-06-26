#ifndef INTERPRET_H
#define INTERPRET_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Operation{
    unsigned char opcode;
    unsigned char operand;
} Operation;

typedef struct InstructionTable{
    unsigned char opcode;
    void (*function)(Operation op, FILE *file);
} InstructionTable;

Operation new_operation(unsigned char ocode, unsigned char orand);
InstructionTable new_instructiontable(unsigned char opcode, void (*f)(Operation op, FILE *file));

unsigned char to_opcode(unsigned char operation);
unsigned char to_operand(unsigned char operation);
int to_int(unsigned char operand, bool is_signed);

void dx(Operation op, FILE *file);
void dy(Operation op, FILE *file);
void pen(Operation op, FILE *file);
void dt(Operation op, FILE *file);
void clear_screen(Operation op, FILE *file);
void wait_for_key(Operation op, FILE *file);

int extend_to_int(unsigned char op1, FILE *file, bool is_signed);
unsigned char extend_get_rgba(unsigned char operand, FILE *file);

void extend_dx(Operation op, FILE *file);
void extend_dy(Operation op, FILE *file);
void extend_dt(Operation op, FILE *file);
void extend_r(Operation op, FILE *file);
void extend_g(Operation op, FILE *file);
void extend_b(Operation op, FILE *file);
void extend_a(Operation op, FILE *file);

void interpret(Operation op, FILE *file, InstructionTable table[], int n);

#endif
