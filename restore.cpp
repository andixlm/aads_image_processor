#include <QColor>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QRect>
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::restoreImage()
{
  buildGrid();

  QImage *finalImage = makeImage();
  if (!finalImage)
    throw Exception::outOfMemory();

  while (!polygons.isEmpty())
    fillRectangle(finalImage, polygons.pop());

  ui->finalImage->setPixmap(QPixmap::fromImage(*finalImage));
  delete finalImage;
}

void MainWindow::fillRectangle(QImage *image, Polygon polygon)
{
  if (!image)
    throw Exception::nullPointer();

  QPainter painter;
  painter.begin(image);
  painter.fillRect(QRect(polygon.topLeft, polygon.bottomRight),
                   QColor(polygon.averageColor.red,
                          polygon.averageColor.green,
                          polygon.averageColor.blue));
  painter.end();
}
