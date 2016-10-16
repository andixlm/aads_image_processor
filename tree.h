#ifndef TREE_H
#define TREE_H

#include "containers.h"

namespace Tree {
  node* add(node* root, Polygon polygon);
  void clear(node* root);

  int size(node* root);
  int leafs(node* root);

  int* toArray(node* root);
  node* toTree(int* array);
}

#endif // TREE_H
