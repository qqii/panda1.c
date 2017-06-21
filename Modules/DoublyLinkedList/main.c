// Memory Simulator Program

#include <stdio.h>
#include <stdlib.h>

#include "io.h"
#include "memsim.h"

void print_help() {
    printf("Commands:\n");
    printf("  Q: Exit Program\n");
    printf("  H: Print Help\n");
    printf("  P: Toggle Print Memory\n");
    printf("  F: Free All Memory\n");
    printf("  [0-9]P: Print Item [0-9]\n");
    printf("  [0-9]F: Free [0-9]\n");
    printf("  [0-9]M[Int]: Malloc [Int] to [0-9]\n");
    printf("\n");
}

void run(FILE *in) {
    char *uinput;
    int memorysize = 0;
    bool running = true;
    bool printmemory = true;
    FakeMemory *memory[10];

    for (int i = 0; i < 10; i++) {
        memory[i] = NULL;
    }

    print_help();

    while (memorysize < 1) {
        printf("Enter simulation memory size: ");
        uinput = readline(in);

        memorysize = atoi(uinput);

        free(uinput);
    }
    memsim_init(memorysize);

    while (running) {
        printf("> ");
        uinput = readline(in);

        if (uinput[0] == 'q' || uinput[0] == 'Q') {
            running = false;
        } else if (uinput[0] == 'h' || uinput[0] == 'H') {
            print_help();
        } else if (uinput[0] == 'p' || uinput[0] == 'P') {
            printmemory = !printmemory;
            if (printmemory) {
                printf("Printing memory after every instruction.\n");
            } else {
                printf("No longer printing memory after every instruction.\n");
            }
        } else if (uinput[0] == 'f' || uinput[0] == 'F') {
            printf("Freeing all memory...\n");
            fake_free_all();
            for (int i = 0; i < 10; i++) {
                memory[i] = NULL;
            }
        } else if ('0' <= uinput[0] && uinput[0] <= '9') {
            int item = atoi(uinput);

            if (uinput[1] == 'f' || uinput[1] == 'F') {
                printf("Freeing Item %d...\n", item);
                fake_free(&memory[item]);
            } else if (uinput[1] == 'm' || uinput[1] == 'M') {
                if ('0' <= uinput[2] && uinput[2] <= '9') {
                    int size = atoi(uinput + 2);

                    printf("Allocating %d to Item %d...\n", size, item);
                    memory[item] = fake_malloc(size);
                    if (memory[item] == NULL) {
                        printf("Not enough memory, malloc failed.\n");
                    }
                } else {
                    printf("Invalid Command.\n");
                }
            } else if (uinput[1] == 'p' || uinput[1] == 'P') {
                printf("%d: ", item);
                print_item(memory[item]);
            } else {
                printf("Invalid Command.\n");
            }
    	} else {
            printf("Invalid Command.\n");
        }

        if (printmemory) {
            print_memory();
        }

        free(uinput);
    }

    memsim_free();
}

void test() {
    int itemsize = 4;
    item *items[itemsize];

    for (int i = 0; i < itemsize; i++) {
        items[i] = NULL;
    }

    memsim_init(240);
    print_memory();
    printf("Created 240 bits of fake memory.\n\n");


    items[0] = fake_malloc(10);
    print_memory();
    printf("Allocated 10 bits of fake memory to 0.\n\n");
    items[1] = fake_malloc(100);
    print_memory();
    printf("Allocated 100 bits of fake memory to 1.\n\n");
    items[2] = fake_malloc(20);
    print_memory();
    printf("Allocated 20 bits of fake memory to 2.\n\n");

    fake_free(&items[1]);
    print_memory();
    printf("Freed 1.\n\n");

    items[1] = fake_malloc(20);
    print_memory();
    printf("Allocated 20 bits of fake memory to 1.\n\n");

    items[3] = fake_malloc(50);
    print_memory();
    printf("Allocated 50 bits of fake memory to 3.\n\n");

    fake_free(&items[1]);
    print_memory();
    printf("Freed 1.\n\n");

    items[1] = fake_malloc(25);
    print_memory();
    printf("Allocated 25 bits of fake memory to 1.\n\n");

    fake_free(&items[0]);
    print_memory();
    printf("Freed 0.\n\n");

    items[0] = fake_malloc(25);
    print_memory();
    printf("Allocated 25 bits of fake memory to 0.\n\n");


    fake_free_all();
    print_memory();
    printf("Freed all memory.\n\n");

    memsim_free();
}

int main(int argv, char **argc) {
    if (argv == 1) {
        run(stdin);
    } else {
        test();
    }

    return 0;
}
