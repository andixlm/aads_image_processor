#include <cmath>
#include <QColor>
#include <QImage>
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

  double polygonArea = 0,  polygonOnPoint = 0;

  for (int x = topLeft.x(); x < bottomRight.x(); ++x)
    for (int y = topLeft.y(); y < bottomRight.y(); ++y) {
      polygonOnPoint += averagePixelBrightness(image, QPoint(x, y));
      ++polygonArea;
    }

  polygonOnPoint /= pow(polygonArea, 2.0);

  double thresholdOnPoint = this->brightnessThreshold / polygonArea;

  for (int x = topLeft.x(); x < bottomRight.x(); ++x)
    for (int y = topLeft.y(); y < bottomRight.y(); ++y) {
      double pointOnPolygon =
          averagePixelBrightness(image, QPoint(x, y)) / polygonArea;

      if (fabs(pointOnPolygon - polygonOnPoint) > thresholdOnPoint)
        return true;
    }

  return false;
}

double MainWindow::averagePixelBrightness(QImage *image, QPoint point)
{
  if (!image)
    throw Exception::nullPointer();

  return (image->pixelColor(point).red() +
          image->pixelColor(point).green() +
          image->pixelColor(point).blue()) / 3.0;
}
