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

  Polygon* getPolygonByPoint(QPoint point, Tree::node *root);
  QQueue<Polygon*> getPolygonsBySize(int size, Tree::node* root);
  QQueue<Polygon*> getAdjacentPolygonsBySize(Polygon polygon, int size, node* root);

  int* toArray(node* root);
  node* toTree(int* array);
}

#endif // TREE_H
