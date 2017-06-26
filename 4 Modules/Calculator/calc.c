/* Calculator.  Use by typing e.g.:   ./calc "2 3 + 4 *"
The expression on the command line must be in quotes.  It can contain numbers,
integer or floating point, and the four basic operations.  The numbers and
operators must be separated by spaces.  The expression must be in postfix
form, with no brackets. */
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Take the appropriate action for one token (number or operator).
void act(stack *ns, char *token) {
    if (isdigit(token[0])) {
        double x = atof(token);
        push(ns, x);
    }
    else {
        double y = pop(ns);
        double x = pop(ns);
        double z = 0;
        if (token[0] == '+') z = x + y;
        else if (token[0] == '-') z = x - y;
        else if (token[0] == '*') z = x * y;
        else if (token[0] == '/') z = x / y;
        push(ns, z);
    }
}

// Evaluate an expression string by acting on each token in turn.
double evaluate(stack *ns, char *exp) {
    char *token = strtok(exp, " ");
    while (token != NULL) {
        act(ns, token);
        token = strtok(NULL, " ");
    }
    return pop(ns);
}

// Take a postfix expression from the command line and evaluate it.
int main(int n, char *args[n]) {
    if (n != 2) {
        fprintf(stderr, "Use: ./calc.o \"...\"\n");
        exit(1);
    }
    stack *ns = new_stack();
    char *exp = args[1];
    double answer = evaluate(ns, exp);
    printf("%f\n", answer);
    return 0;
}
