#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <QPoint>

namespace image {
  // Processing
  void makeGrid(QImage *image, QPoint pointOne, QPoint pointTwo, int threshold);

  // Tools
  bool isSizeThreshold(QPoint pointOne, QPoint pointTwo);
  bool isBrightnessThreshold(QImage *image, QPoint pointOne, QPoint pointTwo,
                           int threshold);
  static int averagePixelBrightness(QImage *image, QPoint point);
}

#endif // IMAGE_H
