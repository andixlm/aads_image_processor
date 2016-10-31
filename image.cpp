#include <QColor>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QRect>
#include <QSize>
#include "exception.h"
#include "image.h"
#include "mainwindow.h"
#include "tree.h"

QImage* makeImage(int size)
{
  QImage* image = new QImage(QPixmap(QSize(size, size)).toImage());

  if (image == nullptr)
    throw Exception::outOfMemory();

  image->fill(QColor(Qt::white));

  return image;
}

void drawGridByTree(QImage* image, Tree::node* root)
{
  if (root == nullptr)
    return;

  drawGridByTree(image, root->left);
  drawGridByTree(image, root->right);

  if (root->left == nullptr && root->right == nullptr)
    drawRectangle(image, root->polygon.topLeft, root->polygon.bottomRight);
}

void restoreImageByTree(QImage* image, Tree::node* root)
{
  if (root == nullptr)
    return;

  restoreImageByTree(image, root->left);
  restoreImageByTree(image, root->right);

  if (root->left == nullptr && root->right == nullptr)
    fillRectangle(image, root->polygon);
}

void drawRectangle(QImage* image, QPoint topLeft, QPoint bottomRight)
{
  if (image == nullptr)
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

void fillRectangle(QImage* image, Polygon polygon)
{
  if (image == nullptr)
    throw Exception::nullPointer();

  QPainter painter;
  painter.begin(image);

  painter.fillRect(QRect(polygon.topLeft, polygon.bottomRight),
                   QColor(polygon.color.red, polygon.color.green, polygon.color.blue));

  painter.end();
}

int comparePolygonsPositions(Polygon alpha, Polygon beta)
{
  int width = beta.bottomRight.x() - beta.topLeft.x();
  int height = beta.bottomRight.y() - beta.topLeft.y();

  int averageWidth = (beta.bottomRight.x() + beta.topLeft.x()) / 2;
  int averageHeight = (beta.bottomRight.y() + beta.topLeft.y()) / 2;

  if (width == height)
    if (alpha.topLeft.x() < averageWidth)
      return -1;
    else
      return 1;
  else
    if (alpha.topLeft.y() < averageHeight)
      return -1;
    else
      return 1;
}

bool isMatchedSize(Polygon polygon, int size)
{
  int polygonHeight = polygon.bottomRight.y() - polygon.topLeft.y(),
      polygonWidth = polygon.bottomRight.x() - polygon.topLeft.x();

  return polygonHeight == size && polygonWidth == size;
}

bool isSizeThreshold(QPoint topLeft, QPoint bottomRight, int threshold)
{
  if (bottomRight.x() - topLeft.x() <= threshold &&
      bottomRight.y() - topLeft.y() <= threshold)
    return true;

  return false;
}

bool isBrightnessThreshold(QImage* image, QPoint topLeft, QPoint bottomRight,
                           int threshold)
{
  if (image == nullptr)
    throw Exception::nullPointer();

  int minimum = 255, maximum = 0;

  for (int x = topLeft.x(); x < bottomRight.x(); ++x)
    for (int y = topLeft.y(); y < bottomRight.y(); ++y) {
      int currentBrightness = pixelBrightness(image, QPoint(x, y));

      minimum = (minimum > currentBrightness) ? currentBrightness : minimum;
      maximum = (maximum < currentBrightness) ? currentBrightness : maximum;
    }

  if (qAbs(maximum - minimum) > threshold)
    return true;

  return false;
}

bool polygonHasPoint(Polygon polygon, QPoint point)
{
  return point.x() >= polygon.topLeft.x() &&
      point.x() <= polygon.bottomRight.x() &&
      point.y() >= polygon.topLeft.y() &&
      point.y() <= polygon.bottomRight.y();
}

Rgb pixelColor(QImage *image, QPoint point)
{
  Rgb color = {
    image->pixelColor(point).red(),
    image->pixelColor(point).green(),
    image->pixelColor(point).blue()
  };

  return color;
}

int pixelBrightness(QImage* image, QPoint point)
{
  if (!image)
    throw Exception::nullPointer();

  double red = 0.30 * static_cast<double>(image->pixelColor(point).red());
  double green = 0.59 * static_cast<double>(image->pixelColor(point).green());
  double blue = 0.11 * static_cast<double>(image->pixelColor(point).blue());

  return static_cast<int>(red + green + blue);
}

Rgb polygonBrightness(QImage* image,
                      QPoint topLeft, QPoint bottomRight)
{
  int area = 0;
  Rgb color = { 0, 0, 0 };

  for (int x = topLeft.x(); x < bottomRight.x(); ++x)
    for (int y = topLeft.y(); y < bottomRight.y(); ++y) {
      color.red += image->pixelColor(QPoint(x, y)).red();
      color.green += image->pixelColor(QPoint(x, y)).green();
      color.blue += image->pixelColor(QPoint(x, y)).blue();

      ++area;
    }

  color.red /= area;
  color.green /= area;
  color.blue /= area;

  return color;
}
