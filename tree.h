#ifndef TREE_H
#define TREE_H

#include <QVector>
#include "containers.h"

namespace Tree {
  node* add(node* root, Polygon polygon);
  void clear(node* root);

  bool isLeaf(node* root);

  int size(node* root);
  int leafs(node* root);

  Polygon* getPolygonByPoint(QPoint point, Tree::node* root);
  Polygon* getPolygonByPoint(double x, double y, Tree::node* root);
  QVector<Polygon*> getPolygonsBySize(int size, Tree::node* root);
  QVector<Polygon*> getAdjacentPolygonsBySize(Polygon polygon, int size, node* root);
  void getAllAdjacentPolygonsBySize(Polygon* polygon, int size,
                                    node* root, QVector<Polygon*>* vector);

  int* toArray(node* root);
  node* toTree(int* array);
}

#endif // TREE_H
