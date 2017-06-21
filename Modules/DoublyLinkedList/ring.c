#include <stdlib.h>
#include <stdio.h>

#include "ring.h"

struct Node {
    item x;
    struct Node *prev;
    struct Node *next;
};
typedef struct Node Node;

struct DoublyLinkedList {
    Node *sent;
    Node *curr;
    Node *free;
};

Node *new_node(item x) {
    Node *n = (Node *) malloc(sizeof(Node));

    n->x = x;
    //n->prev = NULL;
    //n->next = NULL;

    return n;
}

DoublyLinkedList *new_dll() {
    DoublyLinkedList *dll = (DoublyLinkedList *) malloc(sizeof(DoublyLinkedList));

    dll->sent = (Node *) malloc(sizeof(Node));
    dll->sent->prev = dll->sent;
    dll->sent->next = dll->sent;

    dll->curr = dll->sent;

    dll->free = (Node *) malloc(sizeof(Node));
    dll->free->prev = dll->free;
    dll->free->next = dll->free;

    return dll;
}

void free_node(Node *n) {
    // if node->x contains a pointer, free it here
    free(n);
}

void free_nodering(Node *n) {
    for (Node *iter = n->next; iter != n;) {
        Node *curr = iter;
        iter = iter->next;

        free_node(curr);
    }
    free_node(n);
}

void free_dll(DoublyLinkedList *dll) {
    free_nodering(dll->sent);
    free_nodering(dll->free);
    free(dll);
}

void insertafter_node(Node *curr, Node *n) {
    curr->next->prev = n;
    n->next = curr->next;
    n->prev = curr;
    curr->next = n;
}

void insertbefore_node(Node *curr, Node *n) {
    curr->prev->next = n;
    n->prev = curr->prev;
    n->next = curr;
    curr->prev = n;
}

Node *remove_node(Node *n) {
    n->next->prev = n->prev;
    n->prev->next = n->next;
    return n;
}

Node *smart_node(DoublyLinkedList *dll, item i) {
   if (dll->free->next == dll->free) {
       return new_node(i);
   }

   dll->free->next->x = i;
   return remove_node(dll->free->next);
}

void insertend_dll(DoublyLinkedList *dll, item i) {
    Node *n = smart_node(dll, i);

    insertbefore_node(dll->sent, n);
}

void insertstart_dll(DoublyLinkedList *dll, item i) {
    Node *n = smart_node(dll, i);

    insertafter_node(dll->sent, n);
}

void insertafter_dll(DoublyLinkedList *dll, item i) {
    Node *n = smart_node(dll, i);

    insertafter_node(dll->curr, n);
}

void insertbefore_dll(DoublyLinkedList *dll, item i) {
    Node *n = new_node(i);

    insertbefore_node(dll->curr, n);
}

item *end_dll(DoublyLinkedList *dll) {
    return &(dll->sent->prev->x);
}

item *start_dll(DoublyLinkedList *dll) {
    return &(dll->sent->next->x);
}

item *curr_dll(DoublyLinkedList *dll) {
    return dll->curr == dll->sent ? NULL : &(dll->curr->x);
}

item *removeend_dll(DoublyLinkedList *dll) {
    if (dll->sent->prev == dll->sent) {
        return NULL;
    }

    insertbefore_node(dll->free, remove_node(dll->sent->prev));

    return &(dll->free->prev->x);
}

item *removestart_dll(DoublyLinkedList *dll) {
    if (dll->sent->next == dll->sent) {
        return NULL;
    }

    insertbefore_node(dll->free, remove_node(dll->sent->next));

    return &(dll->free->prev->x);
}


item *removecurr_dll(DoublyLinkedList *dll) {
    if (dll->curr == dll->sent) {
        return NULL;
    }

    insertbefore_node(dll->free, remove_node(dll->curr));

    return &(dll->free->prev->x);
}

void currnext_dll(DoublyLinkedList *dll) {
    dll->curr = dll->curr->next;
}

void currprev_dll(DoublyLinkedList *dll) {
    dll->curr = dll->curr->prev;
}

void currstart_dll(DoublyLinkedList *dll) {
    dll->curr = dll->sent->next;
}

void currend_dll(DoublyLinkedList *dll) {
    dll->curr = dll->sent->prev;
}

void map_dll(DoublyLinkedList *dll, item (*f)(item x)) {
    for (currstart_dll(dll); curr_dll(dll) != NULL; currnext_dll(dll)) {
        *curr_dll(dll) = f(*curr_dll(dll));
    }
}
