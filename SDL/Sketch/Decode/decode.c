#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "interpret.h"

void extend(Operation op, FILE *file){
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

    interpret(new_op, file, table, 10);
}

void decode(unsigned char b, FILE *file){
    Operation op = new_operation(to_opcode(b), to_operand(b));

    InstructionTable table[4] = {
        new_instructiontable(0, &dx),
        new_instructiontable(1, &dy),
        new_instructiontable(2, &dt),
        new_instructiontable(3, &extend)
    };

    interpret(op, file, table, 4);
}

void decode_file(char *filename){
    FILE *in = fopen(filename, "rb");
    if (in == NULL) {
        fprintf(stderr, "Can't open %s\n", filename);
        exit(1);
    }

    unsigned char b = fgetc(in);
    while(!feof(in)){
        decode(b, in);
        b = fgetc(in);
    }

    fclose(in);
}

int main(int n, char *args[n]){
    if(n == 2){
        decode_file(args[1]);
    }else if(n > 2){
        for(int i = 1; i < n; i++){
            printf("========== %s ==========\n", args[i]);
            decode_file(args[i]);
        }
    }else{
        fprintf(stderr, "Usage: decode.o <file.sketch>\n");
        exit(1);
    }
}