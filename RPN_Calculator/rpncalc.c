/* A reverse polish notation calculator with the basic arithmetic functions. */

// The number of StackFunctions in stackfuncarr
// I don't think this is very C but I'd rather not make another struct just for this
#define FUNCTION_ARRAY_LENGTH 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Basic stack implimentation
typedef struct{
    int index;      // Current index of array
    int length;
    double *array;
} Stack;

// Stackfunction allows programmer to easily add more functions
typedef struct{
    char *match_str;            // Call funcptr if this string is found
    void (*funcptr)(Stack *);   // funcptr is given the entire stack when called
} StackFunction;

/*// Utility function to print an entire Stack, used for debugging
void debug_stack(Stack *stack){
    fprintf(stderr, ".index = %d\n", stack->index);
    fprintf(stderr, ".length = %d\n", stack->length);
    for(int i = 0; i < stack->length; i++){
        fprintf(stderr, ".array[%d] = %f", i, stack->array[i]);
        if(i == stack->index){
            fprintf(stderr, "\t <----");
        }
        fprintf(stderr, "\n");
    }
}*/

// Array of
StackFunction stackfuncarr[FUNCTION_ARRAY_LENGTH];

void add(Stack *stack);
void subtract(Stack *stack);
void multiply(Stack *stack);
void divide(Stack *stack);

double decode(char *string);

double pop(Stack *stack);
void dblpush(Stack *stack, double number);
void strpush(Stack *stack, char *string);   //oh how i miss function overloading

double calculate(int argc, char**argv);

// Converts a string to a double, if the entire string cannot be created then
// it returns NAN
double decode(char *string){
    char *endptr;
    double converted = strtod(string, &endptr);

    // Do not accept partial (or no) conversions
    if(strlen(endptr) != 0){
        converted = NAN;
    }

    //printf("decode(%s) = %f\n", string, converted);
    return converted;
}

// Given a stack, removes and returns the item at the top of the stack
double pop(Stack *stack){
    // Stack Underflow
    if(stack->index < 0){
        fprintf(stderr, "Attempted to pop from stack when stack was empty.\n");
        //debug_stack(stack);
        exit(1);
    }

    stack->index--;
    return stack->array[stack->index + 1];
}

// Given a stack and a double, puts a double at the top of the stack
void dblpush(Stack *stack, double number){
    // Stack Overflow
    // This should not happen with the current code
    if(stack->index - 1 > stack->length){
        fprintf(stderr, "Attempted to push \"%f\" to already full stack.\n", number);
        //debug_stack(stack);
        exit(1);
    }

    if(isnan(number)){
        fprintf(stderr, "Calculation resulted in NAN.");
        //debug_stack(stack);
        exit(1);
    }else if(number >= HUGE_VAL){
        fprintf(stderr, "Calculation resulted in HUGE_VAL.");
        //debug_stack(stack);
        exit(1);
    }

    stack->index++;
    stack->array[stack->index] = number;
}

// If the string decodes into a number, puts it on the stack
// If the string does not, attempts to call the function
void strpush(Stack *stack, char *string){
    double converted = decode(string);

    // decode returns NAN for partital or no conversions
    if(isnan(converted)){
        for(int i = 0; i < FUNCTION_ARRAY_LENGTH; i++){
            if(strcmp(string, stackfuncarr[i].match_str) == 0){
                stackfuncarr[i].funcptr(stack);
                return;
            }
        }
        fprintf(stderr, "Function \"%s\" is currently not implimented.\n", string);
        exit(1);
    }else{
        dblpush(stack, converted);
    }
}

// StackFunctions:
void add(Stack *stack){
    // Ordering doesn't actually matter for addition and multiply
    double top = pop(stack);
    double bottom = pop(stack);

    dblpush(stack, bottom + top);
}
void subtract(Stack *stack){
    double top = pop(stack);
    double bottom = pop(stack);

    dblpush(stack, bottom - top);
}
void multiply(Stack *stack){
    double top = pop(stack);
    double bottom = pop(stack);

    dblpush(stack, bottom * top);
}
void divide(Stack *stack){
    double top = pop(stack);
    double bottom = pop(stack);

    dblpush(stack, bottom / top);
}

// Creates a Stack, StackFunctions and calculates the result
// Returns what is at the top of the stack
// TODO?: create error message if stack is not empty after calculation?
double calculate(int argc, char **argv){
    // TODO?: Create a function to add to stackfuncarr?
    // This would require another value to keep track of how many things are added
    StackFunction funcadd = {
        .match_str = "+",
        .funcptr = &add
    };
    StackFunction funcsubtract = {
        .match_str = "-",
        .funcptr = &subtract
    };
    StackFunction funcmultiply = {
        .match_str = "*",
        .funcptr = &multiply
    };
    StackFunction funcdivide = {
        .match_str = "/",
        .funcptr = &divide
    };
    stackfuncarr[0] = funcadd;
    stackfuncarr[1] = funcsubtract;
    stackfuncarr[2] = funcmultiply;
    stackfuncarr[3] = funcdivide;

    Stack stack = {
        .index = -1,
        .length = argc - 1,
        // TODO: smart allocation (only accocate for numbers in the inputs)
        // We're not freeing this as the program terminates as soon as the calculation is over
        .array = (double *) malloc(argc - 1)
    };

    for(int i = 0; i < argc; i++){
        //debug_stack(&stack);
        strpush(&stack, argv[i]);
        //printf("\targv[%d] = %s\n", i, argv[i]);
    }
    //debug_stack(&stack);

    // if(stack.index != 0){
    //     debug_stack(&stack);
    // }
    return stack.array[stack.index];
}

int main(int argc, char **argv){
    if (argc == 1){
        fprintf(stderr, "Use e.g.: ./rpncalc.o 9 4 6 \"*\" +\n");
    }else{
        // argv[0] is the name of the program which is not part of the rpn stack
        for(int i = 1; i < argc; i++){
            // printf("argv[%d] = %s\n", i, argv[i]);
            argv[i-1] = argv[i];
        }

        double result = calculate(argc - 1, argv);

        // Nasty hack to make result look nicer when integer
        // TODO: instead of doing this, trunctate zeros instead
        if((float)(long long int)result == result){
            printf("%lld\n", (long long int)result);
        }else{
            printf("%f\n", result);
        }

    }
}
