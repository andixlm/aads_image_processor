#ifndef TOOLS_H
#define TOOLS_H

#include <QImage>
#include <QPoint>

namespace image {
  namespace tools {
    int averagePixelBrightness(QImage *image, QPoint point);

    bool isThresholdExceeded(QImage *image,
                             QPoint pointOne, QPoint pointTwo,
                             int threshold);
  }
}

#endif // TOOLS_H
