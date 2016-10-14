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

int treeLeafs(treeNode *root)
{
  if (!root)
    return 0;

  if (!root->left && !root->right)
    return 1;

  return treeLeafs(root->left) + treeLeafs(root->right);
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

int *treeToArray(treeNode *root, int fullTreeSize, int leafTreeSize)
{
  QQueue<treeNode *> processingNode;
  processingNode.enqueue(root);

  const int packageSize = 3;
  const int polygonSize = 5;

  int *array = new int[1 + packageSize * fullTreeSize +
      packageSize +
      polygonSize * leafTreeSize + 1];

  int currentIdx = 0, nextEmptyPackageIdx = 1;
  int polygonIdx = packageSize * fullTreeSize + packageSize + 1;

  array[currentIdx] = -nextEmptyPackageIdx;
  array[nextEmptyPackageIdx] = currentIdx;

  QQueue<int> emptyPackageIdx;
  emptyPackageIdx.enqueue(nextEmptyPackageIdx);

  nextEmptyPackageIdx += packageSize;

  while (!processingNode.empty()) {
    currentIdx = emptyPackageIdx.dequeue();
    treeNode *currentNode = processingNode.dequeue();

    if (currentNode->left || currentNode->right) {
      // Left child
      processingNode.enqueue(currentNode->left);

      array[++currentIdx] = -nextEmptyPackageIdx;
      array[nextEmptyPackageIdx] = currentIdx;

      emptyPackageIdx.enqueue(nextEmptyPackageIdx);

      nextEmptyPackageIdx += packageSize;
      // Right child
      processingNode.enqueue(currentNode->right);

      array[++currentIdx] = -nextEmptyPackageIdx;
      array[nextEmptyPackageIdx] = currentIdx;

      emptyPackageIdx.enqueue(nextEmptyPackageIdx);

      nextEmptyPackageIdx += packageSize;
    } else {
      array[++currentIdx] = polygonIdx;
      array[++currentIdx] = polygonIdx;

      array[polygonIdx++] = currentNode->polygon.topLeft.x();
      array[polygonIdx++] = currentNode->polygon.topLeft.y();
      array[polygonIdx++] = currentNode->polygon.bottomRight.x();
      array[polygonIdx++] = currentNode->polygon.bottomRight.y();
      array[polygonIdx++] = (currentNode->polygon.color.red +
                             currentNode->polygon.color.green +
                             currentNode->polygon.color.blue) / 3;
    }
  }

  for (int count = 0; count < packageSize; ++count)
    array[++currentIdx] = 0;

  array[polygonIdx] = 0;

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
