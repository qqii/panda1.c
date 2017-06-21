#ifndef MAP_H
#define MAP_H

#include "wordcount.h"
#include "binarytree.h"

WordCount *findword_bt(BinaryTree *tree, char *word);
// This returns a BinaryTree * to allow it to be used as a constructor
BinaryTree *insertwordlist_bt(BinaryTree *tree, char **wordlist);


#endif