#include <QColor>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QRect>
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::buildGrid()
{
  QImage *originalImage = new QImage(ui->originalImage->pixmap()->toImage());
  if (!originalImage)
    throw Exception::outOfMemory();

  QImage *stagedImage = makeImage();

  grid(originalImage, stagedImage, QPoint(0, 0), QPoint(256, 256));

  ui->stageOneImage->setPixmap(QPixmap::fromImage(*stagedImage));

  delete originalImage;
  delete stagedImage;
}

void MainWindow::grid(QImage *originalImage, QImage *stagedImage,
                      QPoint topLeft, QPoint bottomRight)
{
  if (!originalImage || !stagedImage)
    throw Exception::nullPointer();

  if (isBrightnessThreshold(originalImage, topLeft, bottomRight) &&
      !isSizeThreshold(topLeft, bottomRight)) {

    int width = bottomRight.x() - topLeft.x();
    int height = bottomRight.y() - topLeft.y();

    int middleWidth = (topLeft.x() + bottomRight.x()) / 2;
    int middleHeight = (topLeft.y() + bottomRight.y()) / 2;

    if (height > width) {
      // Divide by height with horizontal line.
      grid(originalImage, stagedImage,
           topLeft, QPoint(bottomRight.x(), middleHeight));
      grid(originalImage, stagedImage,
           QPoint(topLeft.x(), middleHeight), bottomRight);
    } else {
      // Divide by width with vertical line.
      grid(originalImage, stagedImage,
           topLeft, QPoint(middleWidth, bottomRight.y()));
      grid(originalImage, stagedImage,
           QPoint(middleWidth, topLeft.y()), bottomRight);
    }
  }

  drawRectangle(stagedImage, topLeft, bottomRight);
}

void MainWindow::drawRectangle(QImage *image, QPoint topLeft, QPoint bottomRight)
{
  if (!image)
    throw Exception::nullPointer();

  QPainter painter;
  painter.begin(image);
  painter.setPen(QColor(Qt::black));
  painter.drawLine(topLeft.x(), topLeft.y(), bottomRight.x(), topLeft.y());
  painter.drawLine(bottomRight.x(), topLeft.y(), bottomRight.x(), bottomRight.y());
  painter.drawLine(bottomRight.x(), bottomRight.y(), topLeft.x(), bottomRight.y());
  painter.drawLine(topLeft.x(), bottomRight.y(), topLeft.x(), topLeft.y());
  painter.end();
}
