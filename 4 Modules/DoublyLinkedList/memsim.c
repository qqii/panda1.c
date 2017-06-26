//#include <stddef.h>
#include <stdio.h>

#include "memsim.h"

// Global variables to hide DoublyLinkedLists from user.
DoublyLinkedList *fake_mallocd = NULL;
DoublyLinkedList *fake_freed = NULL;

void new_fakemalloc() {
    fake_mallocd = new_dll();
}

void new_fakefree(int size) {
    fake_freed = new_dll();
    insertend_dll(fake_freed, (item) {0, size});
}

void memsim_init(int size) {
    memsim_free();

    new_fakemalloc();
    new_fakefree(size);
}

void memsim_free() {
    if (fake_mallocd != NULL) {
        free_dll(fake_mallocd);
    }
    if (fake_freed != NULL) {
        free_dll(fake_freed);
    }
}

void print_rep(int n, char c) {
    for (int i = 0; i < n; i++) {
        printf("%c", c);
    }
}

void print_memory() {
    printf("Fake Memory:\n");

    int lastaddr = 0;
    for (currstart_dll(fake_freed); curr_dll(fake_freed) != NULL; currnext_dll(fake_freed)) {
        item *curritem = curr_dll(fake_freed);
        print_rep(curritem->addr - lastaddr, 'X');
        print_rep(curritem->size, 'O');
        lastaddr = curritem->addr + curritem->size;
    }

    printf("\n");
}

void print_item(item *x) {
    if (x == NULL) {
        printf("NULL\n");
    } else {
        printf("{.addr = %d, .size = %d}\n", x->addr, x->size);
    }
}

item *fake_malloc(int size) {
    for (currstart_dll(fake_freed); curr_dll(fake_freed) != NULL; currnext_dll(fake_freed)) {
        item *curritem = curr_dll(fake_freed);
        if (curritem->size >= size) {
            insertend_dll(fake_mallocd, (item) {curritem->addr, size});
            curritem->addr += size;
            curritem->size -= size;
            return end_dll(fake_mallocd);
        }
    }

    return NULL;
}

void fake_free(item **x) {
    if (*x == NULL) {
        return;
    }

    for (currstart_dll(fake_mallocd); curr_dll(fake_mallocd) != NULL; currnext_dll(fake_mallocd)) {
        if (curr_dll(fake_mallocd) == *x) {
            removecurr_dll(fake_mallocd);
            break;
        }
    }

    for (currstart_dll(fake_freed); curr_dll(fake_freed) != NULL; currnext_dll(fake_freed)) {
        item *curritem = curr_dll(fake_freed);
        int nextaddr = curritem->addr + curritem->size;

        if ((*x)->addr <= nextaddr){
            if ((*x)->addr == nextaddr) {
                curritem->size += (*x)->size;
            } else if ((*x)->addr < nextaddr) {
                insertbefore_dll(fake_freed, **x);
                currprev_dll(fake_freed);
                curritem = curr_dll(fake_freed);
            }

            currnext_dll(fake_freed);
            nextaddr = curritem->addr + curritem->size;
            item *nextitem = curr_dll(fake_freed);
            if (nextitem != NULL && nextaddr == nextitem->addr) {
                curritem->size += nextitem->size;
                removecurr_dll(fake_freed);
            }

            break;
        }
    }
    
    *x = NULL;
}

void fake_free_all() {
    for (currstart_dll(fake_mallocd); curr_dll(fake_mallocd) != NULL; currnext_dll(fake_mallocd)) {
        item *curritem = curr_dll(fake_mallocd);
        fake_free(&curritem);
    }
}
