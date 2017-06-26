#include "interpret.h"

Operation new_operation(unsigned char ocode, unsigned char orand){
    Operation op = {
        .opcode = ocode,
        .operand = orand
    };

    return op;
}

InstructionTable new_instructiontable(unsigned char oc, void (*f)(Operation op, FILE *file)){
    InstructionTable table = {
        .opcode = oc,
        .function = f
    };

    return table;
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
    return operand;
}

void dx(Operation op, FILE *file){
	printf("DX %d\n", to_int(op.operand, true));
}

void dy(Operation op, FILE *file){
	printf("DY %d\n", to_int(op.operand, true));
}

void pen(Operation op, FILE *file){
    printf("EXTENDED PEN\n");
}

void dt(Operation op, FILE *file){
    printf("DT %d\n", to_int(op.operand, false));
}

void clear_screen(Operation op, FILE *file){
    printf("CLEAR\n");
}

void wait_for_key(Operation op, FILE *file){
    printf("KEY\n");
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
            fprintf(stderr, "Invalid extended operand.\n");
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

unsigned char extend_get_rgba(unsigned char operand, FILE *file){
    int c = extend_to_int(operand, file, false);
    if(c > 255){
        fprintf(stderr, "Invalid rgba value.\n");
        exit(1);
    }

    return c;
}

void extend_dx(Operation op, FILE *file){
	printf("EXTENDED VARIABLE LENGTH OPERAND DX %d\n", extend_to_int(op.operand, file, true));
}

void extend_dy(Operation op, FILE *file){
    printf("EXTENDED VARIABLE LENGTH OPERAND DY %d\n", extend_to_int(op.operand, file, true));
}

void extend_dt(Operation op, FILE *file){
    printf("EXTENDED VARIABLE LENGTH OPERAND DT %d\n", extend_to_int(op.operand, file, false));
}

void extend_r(Operation op, FILE *file){
    printf("EXTENDED VARIABLE LENGTH OPERAND R %d\n", extend_get_rgba(op.operand, file));
}

void extend_g(Operation op, FILE *file){
    printf("EXTENDED VARIABLE LENGTH OPERAND G %d\n", extend_get_rgba(op.operand, file));
}

void extend_b(Operation op, FILE *file){
    printf("EXTENDED VARIABLE LENGTH OPERAND B %d\n", extend_get_rgba(op.operand, file));
}

void extend_a(Operation op, FILE *file){
    printf("EXTENDED VARIABLE LENGTH OPERAND A %d\n", extend_get_rgba(op.operand, file));
}

void interpret(Operation op, FILE *file, InstructionTable table[], int n){
    for(int i = 0; i < n; i++){
        if(op.opcode == table[i].opcode){
            table[i].function(op, file);
        }
    }
}
