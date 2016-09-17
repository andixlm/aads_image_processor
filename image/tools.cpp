#include <cmath>

#include "tools.h"

int image::tools::averagePixelBrightness(QImage *image, QPoint point)
{
  // TODO: make checks

  return (image->pixelColor(point).red() +
          image->pixelColor(point).green() +
          image->pixelColor(point).blue()) / 3;
}

bool image::tools::isThresholdExceeded(QImage *image,
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
