#include <QColor>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QRect>
#include <QStack>
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::restoreImage()
{
  buildGrid();

  QImage *finalImage = makeImage();
  if (!finalImage)
    throw Exception::outOfMemory();

  restoreImageByTree(this->root, finalImage);

  ui->finalImage->setPixmap(QPixmap::fromImage(*finalImage));
  delete finalImage;
}

void MainWindow::restoreImageByTree(treeNode *root, QImage *image)
{
  if (!root)
    return;

  restoreImageByTree(root->left, image);
  restoreImageByTree(root->right, image);

  if (!root->left && !root->right)
    fillRectangle(image, root->polygon);
}

void MainWindow::fillRectangle(QImage *image, Polygon polygon)
{
  if (!image)
    throw Exception::nullPointer();

  QPainter painter;
  painter.begin(image);
  painter.fillRect(QRect(polygon.topLeft, polygon.bottomRight),
                   QColor(polygon.color.red,
                          polygon.color.green,
                          polygon.color.blue));
  painter.end();
}
