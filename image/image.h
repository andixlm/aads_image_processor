#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <QPoint>

namespace image {
  // Tools
  bool isSizeThreshold(QPoint pointOne, QPoint pointTwo);
  bool isThresholdExceeded(QImage *image, QPoint pointOne, QPoint pointTwo,
                           int threshold);
  static int averagePixelBrightness(QImage *image, QPoint point);
}

#endif // IMAGE_H
