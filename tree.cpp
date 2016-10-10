#include <QQueue>
#include "mainwindow.h"

int treeSize(treeNode *root) {
  if (!root->left && !root->right)
    return 1;

  int leftCount, rightCount;

  if (root->left)
    leftCount = treeSize(root->left);
  else
    leftCount = 0;

  if (root->right)
    rightCount = treeSize(root->right);
  else
    rightCount = 0;

  return leftCount + rightCount + 1;
}

int comparePolygonPositions(Polygon alpha, Polygon beta)
{
  int width = beta.bottomRight.x() - beta.topLeft.x();
  int height = beta.bottomRight.y() - beta.topLeft.y();

  int averageWidth = (beta.bottomRight.x() + beta.topLeft.x()) / 2;
  int averageHeight = (beta.bottomRight.y() + beta.topLeft.y()) / 2;

  if (width == height)
    if (alpha.topLeft.x() < averageWidth)
      return -1;
    else
      return 1;
  else
    if (alpha.topLeft.y() < averageHeight)
      return -1;
    else
      return 1;
}

treeNode *treeAdd(treeNode *root, Polygon polygon)
{
  if (!root)
    return new treeNode { polygon, nullptr, nullptr };

  if (comparePolygonPositions(polygon, root->polygon) < 0)
    root->left = treeAdd(root->left, polygon);
  else
    root->right = treeAdd(root->right, polygon);

  return root;
}

int *treeToArray(treeNode *root, int size)
{
  QQueue<treeNode *> processingNode;
  processingNode.enqueue(root);

  int *array = new int[1 + size * 3 + 1];

  const int packageSize = 3;
  int currentIdx = 0, nextEmptyPackageIdx = 1;

  array[currentIdx] = -nextEmptyPackageIdx;
  array[nextEmptyPackageIdx] = currentIdx;

  QQueue<int> emptyPackageIdx;
  emptyPackageIdx.enqueue(nextEmptyPackageIdx);

  nextEmptyPackageIdx += packageSize;

  while (!processingNode.empty()) {
    currentIdx = emptyPackageIdx.dequeue();
    treeNode *currentNode = processingNode.dequeue();

    if (currentNode->left) {
      processingNode.enqueue(currentNode->left);

      array[++currentIdx] = -nextEmptyPackageIdx;
      array[nextEmptyPackageIdx] = currentIdx;

      emptyPackageIdx.enqueue(nextEmptyPackageIdx);

      nextEmptyPackageIdx += packageSize;
    } else
      array[++currentIdx] = 0;

    if (currentNode->right) {
      processingNode.enqueue(currentNode->right);

      array[++currentIdx] = -nextEmptyPackageIdx;
      array[nextEmptyPackageIdx] = currentIdx;

      emptyPackageIdx.enqueue(nextEmptyPackageIdx);

      nextEmptyPackageIdx += packageSize;
    } else
      array[++currentIdx] = 0;
  }

  array[++currentIdx] = 0;

  return array;
}

void treeClear(treeNode *root)
{
  if (!root)
    return;

  treeClear(root->left);
  treeClear(root->right);

  delete root;
}
