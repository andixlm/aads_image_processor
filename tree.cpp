#include "mainwindow.h"

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

void treeClear(treeNode *root)
{
  if (!root)
    return;

  treeClear(root->left);
  treeClear(root->right);

  delete root;
}
