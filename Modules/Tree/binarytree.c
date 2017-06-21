#include <stdlib.h>

#include "map.h"

int cmp_item(item a, item b) {
  return cmp_wc(a, b);
}

void free_item(item x) {
  free_wc(x);
}

struct Node {
  item x;
  struct Node *left;
  struct Node *right;
};
typedef struct Node Node;

struct BinaryTree {
  Node *root;
};

Node *new_node(item x) {
  Node *n = (Node *) malloc(sizeof(Node));

  n->x = x;
  n->left = NULL;
  n->right = NULL;

  return n;
}

void free_node(Node *n) {
  if (n == NULL) {
    return;
  }
  free_item(n->x);
  free(n);
}

void free_nodes(Node *n) {
  if (n == NULL) {
    return;
  }
  free_nodes(n->left);
  free_nodes(n->right);
  free_node(n);
}

Node *insert_node(Node *n, item x) {
  if (n == NULL) {
    n = new_node(x);
  } else if (cmp_item(n->x, x) < 0) {
    n->left = insert_node(n->left, x);
  } else {
    n->right = insert_node(n->right, x);
  }

  return n;
}

Node *find_node(Node *n, item x) {
  if (n == NULL) {
  
  } else if (cmp_item(n->x, x) < 0) {
    n = find_node(n->left, x);
  } else if (cmp_item(n->x, x) > 0) {
    n = find_node(n->right, x);
  }

  return n;
}

int height_node(Node *n) {
  int height;

  if (n == NULL) {
    height =  0;
  } else {
    int left = height_node(n->left);
    int right = height_node(n->right);

    height = 1 + (left > right ? left : right);
  }

  return height;
}

BinaryTree *new_bt() {
  BinaryTree *t = (BinaryTree *) malloc(sizeof(BinaryTree));

  t->root = NULL;

  return t;
}

void free_bt(BinaryTree *tree) {
  free_nodes(tree->root);
  free(tree);
}

void insert_bt(BinaryTree *tree, item x) {
  tree->root = insert_node(tree->root, x);
}

bool contains_bt(BinaryTree *tree, item x) {
  return find_node(tree->root, x) != NULL;
}

item *find_bt(BinaryTree *tree, item x) {
  Node *n = find_node(tree->root, x);

  if (n == NULL) {
    return NULL;
  } else {
    return &(n->x);
  }
}

int height_bt(BinaryTree *tree) {
  return height_node(tree->root);
}
