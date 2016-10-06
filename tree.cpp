#include "mainwindow.h"

int comparePolygonSizes(Polygon alpha, Polygon beta)
{
  int widthAlpha = alpha.bottomRight.x() - alpha.topLeft.x();
  int heightAlpha = alpha.bottomRight.y() - alpha.topLeft.y();

  int widthBeta = beta.bottomRight.x() - beta.topLeft.x();
  int heightBeta = beta.bottomRight.y() - beta.topLeft.y();

  if (widthAlpha > widthBeta || heightAlpha > heightBeta)
    return 1;
  else
    return -1;
}

int comparePolygonPositions(Polygon alpha, Polygon beta)
{
  if (alpha.topLeft.x() > beta.topLeft.x() ||
      alpha.topLeft.y() > beta.topLeft.y())
    return 1;
  else
    return -1;
}

treeNode *treeAdd(treeNode *root, Polygon polygon)
{
  if (!root)
    return new treeNode { polygon, nullptr, nullptr };

  if (comparePolygonSizes(polygon, root->polygon) < 0) {
    if (comparePolygonPositions(polygon, root->polygon) < 0)
      root->left = treeAdd(root->left, polygon);
    else
      root->right = treeAdd(root->right, polygon);
  }

  return root;
}
