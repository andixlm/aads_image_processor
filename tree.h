#ifndef TREE_H
#define TREE_H

#include <QQueue>
#include "containers.h"

namespace Tree {
  node* add(node* root, Polygon polygon);
  void clear(node* root);

  bool isLeaf(node* root);

  int size(node* root);
  int leafs(node* root);

  QQueue<Polygon*> getPolygonsBySize(Tree::node* root, int size);

  int* toArray(node* root);
  node* toTree(int* array);
}

#endif // TREE_H
