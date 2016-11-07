#include <QVector>
#include <QQueue>
#include "exception.h"
#include "image.h"
#include "mainwindow.h"
#include "tree.h"

Tree::node* Tree::add(node* root, Polygon polygon)
{
  if (root == nullptr) {
    node* tempNode = new node { polygon, nullptr, nullptr };
    if (tempNode == nullptr)
      throw Exception::outOfMemory();

    return tempNode;
  }

  if (comparePolygonsPositions(polygon, root->polygon) < 0)
    root->left = add(root->left, polygon);
  else
    root->right = add(root->right, polygon);

  return root;
}

void Tree::clear(node* root)
{
  if (root == nullptr)
    return;

  clear(root->left);
  clear(root->right);

  delete root;
}

bool Tree::isLeaf(node* root)
{
  if (root->left == nullptr && root->right == nullptr)
    return true;

  return false;
}

int Tree::size(node* root) {
  if (root->left == nullptr && root->right == nullptr)
    return 1;

  int leftCount, rightCount;

  if (root->left != nullptr)
    leftCount = size(root->left);
  else
    leftCount = 0;

  if (root->right != nullptr)
    rightCount = size(root->right);
  else
    rightCount = 0;

  return leftCount + rightCount + 1;
}

int Tree::leafs(node* root)
{
  if (root == nullptr)
    return 0;

  if (root->left == nullptr  && root->right == nullptr)
    return 1;

  return leafs(root->left) + leafs(root->right);
}

Polygon* Tree::getPolygonByPoint(QPoint point, Tree::node* root)
{
  if (root == nullptr)
    return nullptr;

  QQueue<node*> nodes;
  nodes.enqueue(root);

  while (!nodes.empty()) {
    node* currentNode = nodes.dequeue();

    if (currentNode->left != nullptr || currentNode->right != nullptr) {
      nodes.enqueue(currentNode->left);
      nodes.enqueue(currentNode->right);
    } else {
      if (polygonHasPoint(currentNode->polygon, point))
        return &currentNode->polygon;
    }
  }

  return nullptr;
}

Polygon* Tree::getPolygonByPoint(double x, double y, Tree::node* root)
{
  if (root == nullptr)
    return nullptr;

  QQueue<node*> nodes;
  nodes.enqueue(root);

  while (!nodes.empty()) {
    node* currentNode = nodes.dequeue();

    if (currentNode->left != nullptr || currentNode->right != nullptr) {
      nodes.enqueue(currentNode->left);
      nodes.enqueue(currentNode->right);
    } else {
      if (polygonHasPoint(currentNode->polygon, x, y))
        return &currentNode->polygon;
    }
  }

  return nullptr;
}

QVector<Polygon*> Tree::getPolygonsBySize(int size, node* root)
{
  QQueue<node*> nodes;
  nodes.enqueue(root);

  QVector<Polygon*> polygons;
  while (!nodes.empty()) {
    node* currentNode = nodes.dequeue();

    if (currentNode->left != nullptr || currentNode->right != nullptr) {
      nodes.enqueue(currentNode->left);
      nodes.enqueue(currentNode->right);
    } else {
      if (isMatchedSize(currentNode->polygon, size))
        polygons.append(&currentNode->polygon);
    }
  }

  return polygons;
}

QVector<Polygon*> Tree::getAdjacentPolygonsBySize(Polygon polygon, int size,
                                                  node* root)
{
  QQueue<Polygon*> adjacentPolygons;
  adjacentPolygons.enqueue(getPolygonByPoint(QPoint(polygon.topLeft.x() - 1, polygon.topLeft.y() - 1),
                                             root));
  adjacentPolygons.enqueue(getPolygonByPoint(QPoint(polygon.topLeft.x() + 1, polygon.topLeft.y() - 1),
                                             root));
  adjacentPolygons.enqueue(getPolygonByPoint(QPoint(polygon.bottomRight.x() + 1, polygon.topLeft.y() - 1),
                                             root));
  adjacentPolygons.enqueue(getPolygonByPoint(QPoint(polygon.bottomRight.x() + 1, polygon.bottomRight.y() - 1),
                                             root));
  adjacentPolygons.enqueue(getPolygonByPoint(QPoint(polygon.bottomRight.x() + 1, polygon.bottomRight.y() + 1),
                                             root));
  adjacentPolygons.enqueue(getPolygonByPoint(QPoint(polygon.bottomRight.x() - 1, polygon.bottomRight.y() + 1),
                                             root));
  adjacentPolygons.enqueue(getPolygonByPoint(QPoint(polygon.topLeft.x() - 1, polygon.bottomRight.y() + 1),
                                             root));
  adjacentPolygons.enqueue(getPolygonByPoint(QPoint(polygon.topLeft.x() - 1, polygon.bottomRight.y() - 1),
                                             root));

  QVector<Polygon*> adjacentSizedPolygons;
  while (!adjacentPolygons.empty()) {
    Polygon* currentPolygon = adjacentPolygons.dequeue();

    if (isSizeThreshold(currentPolygon->topLeft, currentPolygon->bottomRight, size))
      adjacentSizedPolygons.append(currentPolygon);
  }

  return adjacentSizedPolygons;
}

void Tree::getAllAdjacentPolygonsBySize(Polygon* polygon, int size,
                                        node* root, QVector<Polygon*>* vector)
{
  if (polygon != nullptr &&
      isMatchedSize(*polygon, size) &&
      !vector->contains(polygon))
    vector->append(polygon);
  else
    return;

  Polygon* upperLeft =
      getPolygonByPoint(QPoint(polygon->topLeft.x() - 1, polygon->topLeft.y() - 1), root);
  Polygon* upper =
      getPolygonByPoint(QPoint(polygon->topLeft.x() + 1, polygon->topLeft.y() - 1), root);
  Polygon* upperRight =
      getPolygonByPoint(QPoint(polygon->bottomRight.x() + 1, polygon->topLeft.y() - 1), root);
  Polygon* right =
      getPolygonByPoint(QPoint(polygon->bottomRight.x() + 1, polygon->bottomRight.y() - 1), root);
  Polygon* lowerRight =
      getPolygonByPoint(QPoint(polygon->bottomRight.x() + 1, polygon->bottomRight.y() + 1), root);
  Polygon* lower =
      getPolygonByPoint(QPoint(polygon->bottomRight.x() - 1, polygon->bottomRight.y() + 1), root);
  Polygon* lowerLeft =
      getPolygonByPoint(QPoint(polygon->topLeft.x() - 1, polygon->bottomRight.y() + 1), root);
  Polygon* left =
      getPolygonByPoint(QPoint(polygon->topLeft.x() - 1, polygon->bottomRight.y() - 1), root);

  getAllAdjacentPolygonsBySize(upperLeft, size, root, vector);
  getAllAdjacentPolygonsBySize(upper, size, root, vector);
  getAllAdjacentPolygonsBySize(upperRight, size, root, vector);
  getAllAdjacentPolygonsBySize(right, size, root, vector);
  getAllAdjacentPolygonsBySize(lowerRight, size, root, vector);
  getAllAdjacentPolygonsBySize(lower, size, root, vector);
  getAllAdjacentPolygonsBySize(lowerLeft, size, root, vector);
  getAllAdjacentPolygonsBySize(left, size, root, vector);
}

int* Tree::toArray(node* root)
{ 
  if (root == nullptr)
    return nullptr;

  const int packageSize = 3;
  const int polygonSize = 7;
  const int treeSize = Tree::size(root);
  const int treeLeafs = Tree::leafs(root);

  QQueue<node*> nodes;
  nodes.enqueue(root);

  int idx = 0, packageIdx = 1,
      polygonIdx = packageSize * treeSize + packageSize + 1;

  QQueue<int> indexes;
  indexes.enqueue(packageIdx);

  int* array = new int[
      1 +
      packageSize * treeSize +
      packageSize +
      polygonSize * treeLeafs +
      1];
  if (array == nullptr)
    throw Exception::outOfMemory();

  array[idx] = -packageIdx;
  array[packageIdx] = idx;

  packageIdx += packageSize;

  while (!nodes.empty()) {
    node* currentNode = nodes.dequeue();
    idx = indexes.dequeue();

    if (currentNode->left != nullptr || currentNode->right != nullptr) {
      // Left child.
      nodes.enqueue(currentNode->left);

      indexes.enqueue(packageIdx);

      array[++idx] = -packageIdx;
      array[packageIdx] = idx;

      packageIdx += packageSize;

      // Right child.
      nodes.enqueue(currentNode->right);

      indexes.enqueue(packageIdx);

      array[++idx] = -packageIdx;
      array[packageIdx] = idx;

      packageIdx += packageSize;
    } else {
      // Write link index minimal polygon is stored on.
      for (int count = 0; count < packageSize - 1; ++count)
        array[++idx] = polygonIdx;

      // Write information about minimal polygon.
      array[polygonIdx++] = currentNode->polygon.topLeft.x();
      array[polygonIdx++] = currentNode->polygon.topLeft.y();

      array[polygonIdx++] = currentNode->polygon.bottomRight.x();
      array[polygonIdx++] = currentNode->polygon.bottomRight.y();

      array[polygonIdx++] = currentNode->polygon.color.red;
      array[polygonIdx++] = currentNode->polygon.color.green;
      array[polygonIdx++] = currentNode->polygon.color.blue;
    }
  }

  // Triple zero divider between partition and polygon's information.
  for (int count = 0; count < packageSize; ++count)
    array[++idx] = 0;

  // Last element is -1.
  array[polygonIdx] = -1;

  return array;
}

Tree::node* Tree::toTree(int* array)
{
  if (array == nullptr)
    return nullptr;

  node* root = nullptr;

  QQueue<node*> nodes;
  QQueue<int> indexes;
  int idx = 0;

  if (array[idx] < 0) {
    root = new node { Polygon(), nullptr, nullptr };
    if (root == nullptr)
      throw Exception::outOfMemory();
    nodes.enqueue(root);

    indexes.enqueue(qAbs(array[idx]));
  } else
    return root;

  while (!nodes.empty()) {
    node* currentNode = nodes.dequeue();
    idx = indexes.dequeue();

    if (array[++idx] < 0) {
      // Left child.
      currentNode->left = new node { Polygon(), nullptr, nullptr };
      if (currentNode->left == nullptr)
        throw Exception::outOfMemory();
      nodes.enqueue(currentNode->left);

      indexes.enqueue(qAbs(array[idx++]));

      // Right child.
      currentNode->right = new node { Polygon(), nullptr, nullptr };
      if (currentNode->right == nullptr)
        throw Exception::outOfMemory();
      nodes.enqueue(currentNode->right);

      indexes.enqueue(qAbs(array[idx]));
    } else {
      // Index of polygon we work with.
      int polygonIdx = array[idx];

      // Restore information about polygon.
      currentNode->polygon.topLeft.setX(array[polygonIdx++]);
      currentNode->polygon.topLeft.setY(array[polygonIdx++]);

      currentNode->polygon.bottomRight.setX(array[polygonIdx++]);
      currentNode->polygon.bottomRight.setY(array[polygonIdx++]);

      currentNode->polygon.color.red = array[polygonIdx++];
      currentNode->polygon.color.green = array[polygonIdx++];
      currentNode->polygon.color.blue = array[polygonIdx++];
    }
  }

  return root;
}
