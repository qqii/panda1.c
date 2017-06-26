#include <stdlib.h>

#include "map.h"

WordCount *findword_bt(BinaryTree *tree, char *word) {
  WordCount temp = new_wc(word, 1);
  WordCount *find = find_bt(tree, temp);

  free_wc(temp);
  return find;
}

BinaryTree *insertword_bt(BinaryTree *tree, char *word) {
  if (tree == NULL) {
    tree = new_bt();
  }

  WordCount *find = findword_bt(tree, word);

  // No need to traverse through the tree twice using contains_bt and find_bt
  if (find == NULL) {
    insert_bt(tree, new_wc(word, 1));
  } else {
    find->count++;
  }

  return tree;
}


BinaryTree *insertwordlist_bt(BinaryTree *tree, char **wordlist) {
  if (wordlist == NULL || **wordlist == '\0') {
    return tree;
  }

  for (int i = 0; *(wordlist + i) != '\0'; i++) {
    tree = insertword_bt(tree, wordlist[i]);
  }

  return tree;
}