#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

struct node {
    item x;
    struct node *next;
};
typedef struct node node;

struct stack {
    node *first;
    node *free;
};

static void fail(char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

stack *new_stack() {
    stack *p = malloc(sizeof(stack));
    p->first = NULL;
    p->free = NULL;
    return p;
}

void push(stack *s, item x) {
    node *n;
    if (s->free != NULL) {
        n = s->free;
        s->free = n->next;
    }
    else n = malloc(sizeof(node));
    n->x = x;
    n->next = s->first;
    s->first = n;
}

item pop(stack *s) {
    if (s->first == NULL) fail("pop of empty stack");
    node *n = s->first;
    s->first = n->next;
    item x = n->x;
    n->next = s->free;
    s->free = n;
    return x;
}

item top(stack *s) {
    if (s->first == NULL) fail("top of empty stack");
    return s->first->x;
}

bool is_empty(stack *s) {
    return s->first == NULL;
}
