#include <QImage>
#include <QPixmap>
#include "exception.h"
#include "image.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::restoreImage()
{
  if (this->imageTree == nullptr ||
      this->imageArray == nullptr)
    return;

  QImage* finalImage = makeImage(this->imageSize);
  if (finalImage == nullptr)
    throw Exception::outOfMemory();
  QImage* stagedImage = makeImage(this->imageSize);

  drawGridByTree(stagedImage, this->imageTree);
  restoreImageByTree(finalImage, this->imageTree);

  ui->stagedImage->setPixmap(QPixmap::fromImage(*stagedImage));
  ui->finalImage->setPixmap(QPixmap::fromImage(*finalImage));

  delete stagedImage;
  delete finalImage;
}
