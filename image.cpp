#include <cmath>
#include <QColor>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QSize>
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::buildGrid()
{
  QImage *originalImage = new QImage(ui->originalImage->pixmap()->toImage());
  if (!originalImage)
    throw Exception::outOfMemory();

  QImage *stagedImage = makeImage();

  grid(originalImage, stagedImage, QPoint(0, 0), QPoint(255, 255));

  ui->stageOneImage->setPixmap(QPixmap::fromImage(*stagedImage));
}

QImage *MainWindow::makeImage()
{
  QImage *image = new QImage(QPixmap(QSize(256, 256)).toImage());

  if (!image)
    throw Exception::outOfMemory();

  image->fill(QColor(Qt::white));

  return image;
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
  painter.drawRect(QRect(topLeft, bottomRight));
  painter.end();
}

bool MainWindow::isSizeThreshold(QPoint topLeft, QPoint bottomRight)
{
  if (bottomRight.x() - topLeft.x() <= this->sizeThreshold ||
      bottomRight.y() - topLeft.y() <= this->sizeThreshold)
    return true;

  return false;
}

bool MainWindow::isBrightnessThreshold(QImage *image,
                                       QPoint topLeft, QPoint bottomRight)
{
  if (!image)
    throw Exception::nullPointer();

  for (int x = topLeft.x(); x < bottomRight.x(); ++x)
    for (int y = topLeft.y(); y < bottomRight.y(); ++y)

      for (int innerX = topLeft.x(); innerX < bottomRight.x(); ++innerX)
        for (int innerY = topLeft.y(); innerY < bottomRight.y(); ++innerY)

          if (abs(averagePixelBrightness(image, QPoint(x, y)) -
                  averagePixelBrightness(image, QPoint(innerX, innerY))) >
              this->brightnessThreshold)
            return true;

  return false;
}

int MainWindow::averagePixelBrightness(QImage *image, QPoint point)
{
  if (!image)
    throw Exception::nullPointer();

  return (image->pixelColor(point).red() +
          image->pixelColor(point).green() +
          image->pixelColor(point).blue()) / 3;
}
