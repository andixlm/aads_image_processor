#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <QPoint>
#include "containers.h"
#include "tree.h"

QImage* makeImage(int size);

void drawGridByTree(QImage* image, Tree::node* root);
void restoreImageByTree(QImage* image, Tree::node* root);

void drawRectangle(QImage* image, QPoint topLeft, QPoint bottomRight);
void fillRectangle(QImage* image, Polygon polygon);

int comparePolygonsPositions(Polygon alpha, Polygon beta);

bool isMatchedSize(Polygon polygon, int size);
bool isSizeThreshold(QPoint topLeft, QPoint bottomRight, int threshold);
bool isBrightnessThreshold(QImage* image, QPoint topLeft, QPoint bottomRight,
                           int threshold);
bool polygonHasPoint(Polygon polygon, QPoint point);
bool polygonHasPoint(Polygon polygon, double x, double y);

Rgb pixelColor(QImage* image, QPoint point);
int pixelBrightness(QImage* image, QPoint point);
Rgb polygonBrightness(QImage* image, QPoint topLeft, QPoint bottomRight);

#endif // IMAGE_H
