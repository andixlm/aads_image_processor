#include <cmath>
#include <QPixmap>
#include <QPainter>
#include "mainwindow.h"

QImage *MainWindow::makeImage()
{
  QImage *image = new QImage(QPixmap(QSize(256, 256)).toImage());
  image->fill(QColor(Qt::white));

  return image;
}

void MainWindow::makeGrid(QImage *image, QPoint pointOne, QPoint pointTwo,
                     int threshold)
{
  // TODO: make checks

  if (isBrightnessThreshold(image, pointOne, pointTwo, threshold) &&
      !isSizeThreshold(pointOne, pointTwo)) {
    int middleWidth = (pointOne.x() + pointTwo.x()) / 2;
    int middleHeight = (pointOne.y() + pointTwo.y()) / 2;

    if (middleHeight > middleWidth) {
      // Divide by height.
      makeGrid(image, pointOne, QPoint(pointTwo.x(), middleHeight), threshold);
      makeGrid(image, QPoint(pointOne.x(), middleHeight), pointTwo, threshold);
    } else {
      // Divide by width.
      makeGrid(image, pointOne, QPoint(middleWidth, pointTwo.y()), threshold);
      makeGrid(image, QPoint(middleWidth, pointOne.y()), pointTwo, threshold);
    }
  }
}

void MainWindow::drawRectangle(QImage *image, QPoint pointOne, QPoint pointTwo)
{
  QPainter painter;
  painter.begin(image);
  painter.setPen(QColor(Qt::black));
  painter.drawRect(QRect(pointOne, pointTwo));
  painter.end();
}

bool MainWindow::isSizeThreshold(QPoint pointOne, QPoint pointTwo)
{
  // TODO: make checks.

  if (pointTwo.x() - pointOne.x() <= 8)
    return true;

  return false;
}

bool MainWindow::isBrightnessThreshold(QImage *image,
                                  QPoint pointOne, QPoint pointTwo,
                                  int threshold)
{
  // TODO: make checks.

  for (int x = pointOne.x(); x < pointTwo.x(); ++x)
    for (int y = pointOne.y(); y < pointTwo.y(); ++y)

      for (int innerX = pointOne.x(); innerX < pointTwo.x(); ++innerX)
        for (int innerY = pointOne.y(); innerY < pointTwo.y(); ++innerY)

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
