#include <stdio.h>
#include <stdlib.h>
#include "io.h"

int main(int argc, char **argv) {
  char *file = read(stdin);

  printf("file = \n%s", file);

  free(file);

  return 0;
}
