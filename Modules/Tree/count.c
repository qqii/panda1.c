#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "io.h"
#include "map.h"

int main(int argc, char *argv[]) {
  if (argc == 2) {
    BinaryTree *tree;
    int words;
    clock_t timer;
    char *file = readfile(argv[1]);
    char **wordlist = wordarray(file);

    timer = clock();
    tree = insertwordlist_bt(NULL, wordlist);
    timer = clock() - timer;
    printf("Reading into a binary tree took %fs.\n", (double) timer / CLOCKS_PER_SEC);

    for (words = 0; wordlist[words] != '\0'; words++);

    free(file);
    free(wordlist);

    printf("There are %d words, and the binary tree has height %d.\n", words, height_bt(tree));

    bool running = true;
    while (running) {
      char *uinput;
      WordCount *wc;

      printf("\nEnter word for retrieval: ");
      uinput = readline(stdin);

      wc = findword_bt(tree, uinput);
      if (wc == NULL) {
        printf("\"%s\" not found.\n", uinput);
      } else {
        printf("\"%s\" has %ld occurrences.\n", uinput, wc->count);
      }
      free(uinput); // readline allocates memory and we're going to read another line

      printf("Continue? [y/n]: ");
      uinput = readline(stdin);
      if (*uinput != 'y' && *uinput != 'Y') {
        running = false;
      }
      free(uinput);
    }

    free_bt(tree);
  } else {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    exit(1);
  }

  return 0;
}