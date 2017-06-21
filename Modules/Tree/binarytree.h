#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <stdbool.h>

#include "wordcount.h"

typedef WordCount item;

struct BinaryTree;
typedef struct BinaryTree BinaryTree;

// The programmer must edit these function in the binarytreec file if he changes item
int cmp_item(item a, item b);
void free_item(item x);

BinaryTree *new_bt();
void free_bt(BinaryTree *tree);
void insert_bt(BinaryTree *tree, item x);
bool contains_bt(BinaryTree *tree, item x);
item *find_bt(BinaryTree *tree, item x);
int height_bt(BinaryTree *tree);

#endif