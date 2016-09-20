#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <QPoint>

namespace image {
  static int averagePixelBrightness(QImage *image, QPoint point);

  bool isThresholdExceeded(QImage *image, QPoint pointOne, QPoint pointTwo,
                           int threshold);
}

#endif // IMAGE_H
