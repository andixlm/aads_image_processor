#include <QColor>
#include <QImage>
#include <QPixmap>
#include <QPoint>
#include <QRgb>
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

  int minimum = 255, maximum = 0;

  for (int x = topLeft.x(); x < bottomRight.x(); ++x)
    for (int y = topLeft.y(); y < bottomRight.y(); ++y) {
      int currentBrightness = averagePixelBrightness(image, QPoint(x, y));

      minimum = (minimum > currentBrightness) ? currentBrightness : minimum;
      maximum = (maximum < currentBrightness) ? currentBrightness : maximum;
    }

  if (qAbs(maximum - minimum) > this->brightnessThreshold)
    return true;

  return false;
}

Rgb MainWindow::getRgb(QImage *image, QPoint point)
{
  Rgb color = { image->pixelColor(point).red(),
                image->pixelColor(point).green(),
                image->pixelColor(point).blue() };

  return color;
}

int MainWindow::averagePixelBrightness(QImage *image, QPoint point)
{
  if (!image)
    throw Exception::nullPointer();

  return (image->pixelColor(point).red() +
          image->pixelColor(point).green() +
          image->pixelColor(point).blue()) / 3;
}
