#include "image.h"
#include "mainwindow.h"
#include "tree.h"

int threshold;
static void editPolygons(Tree::node* root);

void MainWindow::removeBackground()
{
  if (this->imageTree == nullptr)
    return;

  threshold = this->sizeThreshold;

  editPolygons(this->imageTree);
}

static void editPolygons(Tree::node* root)
{
  if (root == nullptr)
    return;

  editPolygons(root->left);
  editPolygons(root->right);

  if (Tree::isLeaf(root) &&
      !isSizeThreshold(root->polygon.topLeft, root->polygon.bottomRight,
                       threshold))
    root->polygon.color.red = root->polygon.color.green =
        root->polygon.color.blue = 255;
}
