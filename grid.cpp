#include <QImage>
#include <QPixmap>
#include <QPoint>
#include "exception.h"
#include "image.h"
#include "mainwindow.h"
#include "tree.h"
#include "ui_mainwindow.h"

Tree::node* root;

static void grid(QImage* image, QPoint topLeft, QPoint bottomRight,
                        int sizeThreshold, int brightnessThreshold);

void MainWindow::buildGrid()
{
  if (ui->originalImage->pixmap() == nullptr)
    return;

  cleanUpImageData();

  QImage* originalImage = new QImage(ui->originalImage->pixmap()->toImage());
  if (originalImage == nullptr)
    throw Exception::outOfMemory();
  QImage* stagedImage = makeImage(this->imageSize);

  root = nullptr;
  grid(originalImage,
       QPoint(), QPoint(this->imageSize, this->imageSize),
       this->sizeThreshold, this->brightnessThreshold);
  this->imageTree = root;
  this->imageArray = Tree::toArray(this->imageTree);

  drawGridByTree(stagedImage, this->imageTree);
  ui->stagedImage->setPixmap(QPixmap::fromImage(*stagedImage));

  delete originalImage;
  delete stagedImage;
}

static void grid(QImage* image, QPoint topLeft, QPoint bottomRight,
                        int sizeThreshold, int brightnessThreshold)
{
  if (image == nullptr)
    throw Exception::nullPointer();

  root = Tree::add(root, { topLeft, bottomRight,
                   polygonBrightness(image, topLeft, bottomRight)});

  if (!isSizeThreshold(topLeft, bottomRight, sizeThreshold) &&
      isBrightnessThreshold(image, topLeft, bottomRight, brightnessThreshold)) {

    int width = bottomRight.x() - topLeft.x();
    int height = bottomRight.y() - topLeft.y();

    int middleWidth = (topLeft.x() + bottomRight.x()) / 2;
    int middleHeight = (topLeft.y() + bottomRight.y()) / 2;

    if (height > width) {
      // Divide by height with horizontal line.
      grid(image, topLeft, QPoint(bottomRight.x(), middleHeight),
           sizeThreshold, brightnessThreshold);
      grid(image, QPoint(topLeft.x(), middleHeight), bottomRight,
           sizeThreshold, brightnessThreshold);
    } else {
      // Divide by width with vertical line.
      grid(image, topLeft, QPoint(middleWidth, bottomRight.y()),
           sizeThreshold, brightnessThreshold);
      grid(image, QPoint(middleWidth, topLeft.y()), bottomRight,
           sizeThreshold, brightnessThreshold);
    }
  }
}
