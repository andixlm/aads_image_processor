#include <cmath>
#include <QColor>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QSize>
#include "mainwindow.h"

QImage *MainWindow::makeImage()
{
  QImage *image = new QImage(QPixmap(QSize(256, 256)).toImage());

  if (!image)
    throw Exception::outOfMemory();

  image->fill(QColor(Qt::white));

  return image;
}

void MainWindow::makeGrid(QImage *image, QPoint topLeft, QPoint bottomRight,
                          int threshold)
{
  if (!image)
    throw Exception::nullPointer();

  if (isBrightnessThreshold(image, topLeft, bottomRight, threshold) &&
      !isSizeThreshold(topLeft, bottomRight)) {
    int middleWidth = (topLeft.x() + bottomRight.x()) / 2;
    int middleHeight = (topLeft.y() + bottomRight.y()) / 2;

    if (bottomRight.y() - topLeft.y() > bottomRight.x() - topLeft.x()) {
      // Divide by height.
      makeGrid(image, topLeft, QPoint(bottomRight.x(), middleHeight), threshold);
      makeGrid(image, QPoint(topLeft.x(), middleHeight), bottomRight, threshold);
    } else {
      // Divide by width.
      makeGrid(image, topLeft, QPoint(middleWidth, bottomRight.y()), threshold);
      makeGrid(image, QPoint(middleWidth, topLeft.y()), bottomRight, threshold);
    }
  }
}

void MainWindow::drawRectangle(QImage *image, QPoint topLeft, QPoint bottomRight)
{
  QPainter painter;
  painter.begin(image);
  painter.setPen(QColor(Qt::black));
  painter.drawRect(QRect(topLeft, bottomRight));
  painter.end();
}

bool MainWindow::isSizeThreshold(QPoint topLeft, QPoint bottomRight)
{
  // TODO: make checks.

  if (bottomRight.x() - topLeft.x() <= 8 || bottomRight.y() - topLeft.y() <= 8)
    return true;

  return false;
}

bool MainWindow::isBrightnessThreshold(QImage *image,
                                       QPoint topLeft, QPoint bottomRight,
                                       int threshold)
{
  // TODO: make checks.

  for (int x = topLeft.x(); x < bottomRight.x(); ++x)
    for (int y = topLeft.y(); y < bottomRight.y(); ++y)

      for (int innerX = topLeft.x(); innerX < bottomRight.x(); ++innerX)
        for (int innerY = topLeft.y(); innerY < bottomRight.y(); ++innerY)

          if (abs(averagePixelBrightness(image, QPoint(x, y)) -
                  averagePixelBrightness(image, QPoint(innerX, innerY))) >
              threshold)
            return true;

  return false;
}

int MainWindow::averagePixelBrightness(QImage *image, QPoint point)
{
  // TODO: make checks

  return (image->pixelColor(point).red() +
          image->pixelColor(point).green() +
          image->pixelColor(point).blue()) / 3;
}
