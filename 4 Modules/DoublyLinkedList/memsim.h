#ifndef MEMSIM_H
#define MEMSIM_H

#include "ring.h"

void memsim_init(int size);
void memsim_free();

void print_memory();
void print_item(FakeMemory *x);

FakeMemory *fake_malloc(int size);
void fake_free(FakeMemory **x);
void fake_free_all();

#endif