// Defines function prototypes for IO functions.

#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdbool.h>

char *read(FILE *in);
char *readline(FILE *in);
char *readfile(char *filename);

char **wordarray(char *string);

#endif
