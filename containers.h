#ifndef IMAGESTRUCTURES_H
#define IMAGESTRUCTURES_H

#include <QPoint>

struct Rgb {
 int red;
 int green;
 int blue;
};

struct Polygon {
  QPoint topLeft;
  QPoint bottomRight;
  Rgb color;
};

namespace Tree {
  struct node {
     Polygon polygon;
     node* left;
     node* right;
  };
}

#endif // IMAGESTRUCTURES_H
