#include <QtMath>
#include <QVector>
#include "image.h"
#include "mainwindow.h"
#include "tree.h"

const int minimalLineLengthInPolygons = 32;

void MainWindow::markStrokes()
{
  buildGrid();

  QVector<Polygon*> minimalPolygons =
      Tree::getPolygonsBySize(this->sizeThreshold, this->imageTree);

  QVector<QVector<Polygon*>> lines, trash;
  while (!minimalPolygons.empty()) {
    Polygon* currentPolygon = minimalPolygons.takeFirst();

    QVector<Polygon*> object;
    Tree::getAllAdjacentPolygonsBySize(currentPolygon, this->sizeThreshold,
                                       this->imageTree, &object);

    if (object.length() > minimalLineLengthInPolygons)
      lines.append(object);
    else
      trash.append(object);

    for (QVector<Polygon*>::const_iterator itr = object.constBegin(), end = object.constEnd();
         itr != end; ++itr)
      minimalPolygons.removeAll(*itr);
  }

  QVector<QVector<Polygon*>> satisfyingLines, badLines;
  double satisfyingDerivativeInfimum = qTan(qDegreesToRadians(static_cast<double>(this->angle - 30)));
  double satisfyingDerivativeSupremum = qTan(qDegreesToRadians(static_cast<double>(this->angle)));

  while(!lines.empty()) {
    QVector<Polygon*> line = lines.takeFirst();

    Polygon* highestPolygon = line.first();
    Polygon* lowestPolygon = line.last();

    for (QVector<Polygon*>::const_iterator polygon = line.constBegin(), lastPolygon = line.constEnd();
         polygon != lastPolygon; ++polygon) {
      if ((*polygon)->topLeft.y() > highestPolygon->topLeft.y())
        highestPolygon = *polygon;
      else if ((*polygon)->topLeft.y() < lowestPolygon->topLeft.y())
        lowestPolygon = *polygon;
    }

    int deltaArgument = lowestPolygon->bottomRight.x() - highestPolygon->topLeft.x(),
        deltaFunction = lowestPolygon->bottomRight.y() - highestPolygon->topLeft.y();

    double currentDerivative =
        qAbs(static_cast<double>(deltaFunction) / static_cast<double>(deltaArgument));

    if (currentDerivative > satisfyingDerivativeInfimum &&
        currentDerivative < satisfyingDerivativeSupremum)
      satisfyingLines.append(line);
    else
      badLines.append(line);
  }

  while (!badLines.empty()) {
    QVector<Polygon*> line = badLines.takeFirst();

    for (QVector<Polygon*>::const_iterator polygon = line.constBegin(), lastPolygon = line.constEnd();
         polygon != lastPolygon; ++polygon) {
      (*polygon)->color.red = 255;
      (*polygon)->color.green = 255;
      (*polygon)->color.blue = 255;
    }
  }

  while (!trash.empty()) {
    QVector<Polygon*> object = trash.takeFirst();

    for (QVector<Polygon*>::const_iterator polygon = object.constBegin(), lastPolygon = object.constEnd();
         polygon != lastPolygon; ++polygon) {
      (*polygon)->color.red = 255;
      (*polygon)->color.green = 255;
      (*polygon)->color.blue = 255;
    }
  }

  removeBackground();
  restoreImage();

  return;
}
