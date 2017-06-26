#include <stdio.h>
#include <stdlib.h>

#include "io.h"
#include "binarytree.h"

// Mobile numbers always start at 07

void help() {
  printf("Commands:\n");
  printf("  Q: Exit Program\n");
  printf("  E: Enter Name and Number\n");
  printf("  S: Search for Name\n");
  printf("  H: Display Help\n");
}

void run(FILE *in) {
  char *uinput;
  bool running = true;
  BinaryTree *tree = new_bt();

  help();

  while (running) {
    printf("> ");
    uinput = readline(in);

    if (uinput[0] == 'q' || uinput[0] == 'Q') {
      running = false;
    } else if (uinput[0] == 'h' || uinput[0] == 'H') {
      help();
    } else if (uinput[0] == 'e' || uinput[0] == 'E') {
      char *name;
      long number = 0;

      printf("Name: ");
      name = readline(in);

      // valid numbers are 07...
      while (number < 7000000000) {
        printf("Number: ");
        free(uinput);
        uinput = readline(in);
        number = atol(uinput);
      }

      WordCount temp = new_wc(name, number);
      free(name);

      if (contains_bt(tree, temp)) {
        find_bt(tree, temp)->count = number;
        free_wc(temp);
      } else {
        insert_bt(tree, temp);
      }
    } else if (uinput[0] == 's' || uinput[0] == 'S') {
      printf("Name: ");
      free(uinput);
      uinput = readline(in);
      WordCount temp = new_wc(uinput, 0);

      if (contains_bt(tree, temp)) {
        printf("\"%s\" has number 0%ld.\n", uinput, find_bt(tree, temp)->count);
      } else {
        printf("\"%s\" no found.\n", uinput);
      }
      free_wc(temp);
    } else {
      printf("Invalid Command.\n");
    }


    free(uinput);
  }

  free_bt(tree);
}

void test() {
  BinaryTree *tree = new_bt();
  WordCount temp;

  insert_bt(tree, new_wc("alex", 7915368822));
  insert_bt(tree, new_wc("james", 7014307625));
  insert_bt(tree, new_wc("sam", 7970089485));
  insert_bt(tree, new_wc("stephen", 7932315463));
  insert_bt(tree, new_wc("james", 7932315463));
  insert_bt(tree, new_wc("john", 7057224422));

  printf("The tree has height %d\n", height_bt(tree));

  temp = new_wc("james", 0);
  printf("Tree contains \"james\"? %s\n", contains_bt(tree, temp) ? "true" : "false");
  free_wc(temp);

  temp = new_wc("alex", 0);
  printf("\"alex\" has the number 0%ld\n", find_bt(tree, temp)->count);
  free_wc(temp);

  temp = new_wc("sam", 0);
  printf("\"sam\" has the number 0%ld\n", find_bt(tree, temp)->count);
  free_wc(temp);

  temp = new_wc("eve", 0);
  printf("Tree contains \"eve\"? %s\n", contains_bt(tree, temp) ? "true" : "false");
  free_wc(temp);

  free_bt(tree);
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    run(stdin);
  } else {
    test();
  }

  return 0;
}