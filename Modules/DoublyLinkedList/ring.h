#ifndef RING_H
#define RING_H

#include <stdbool.h>

//TODO: isend function
//true if sentinal
//false if otherwise

typedef struct FakeMemory {
    int addr;
    int size;
} FakeMemory;

typedef FakeMemory item;

struct DoublyLinkedList;
typedef struct DoublyLinkedList DoublyLinkedList;

DoublyLinkedList *new_dll();
void free_dll(DoublyLinkedList *dll);
void insertend_dll(DoublyLinkedList *dll, item i);
void insertstart_dll(DoublyLinkedList *dll, item i);
void insertafter_dll(DoublyLinkedList *dll, item i);
void insertbefore_dll(DoublyLinkedList *dll, item i);

item *end_dll(DoublyLinkedList *dll);
item *start_dll(DoublyLinkedList *dll);
item *curr_dll(DoublyLinkedList *dll);

item *removeend_dll(DoublyLinkedList *dll);
item *removestart_dll(DoublyLinkedList *dll);
item *removecurr_dll(DoublyLinkedList *dll);

void currnext_dll(DoublyLinkedList *dll);
void currprev_dll(DoublyLinkedList *dll);
void currstart_dll(DoublyLinkedList *dll);
void currend_dll(DoublyLinkedList *dll);

void map_dll(DoublyLinkedList *dll, item (*f)(item x));

#endif
