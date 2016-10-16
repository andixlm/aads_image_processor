#include "mainwindow.h"
#include "tree.h"

void MainWindow::cleanUpImageData()
{
  Tree::clear(this->imageTree);
  this->imageTree = nullptr;

  if (this->imageArray != nullptr)
    delete this->imageArray;
  this->imageArray = nullptr;
}
