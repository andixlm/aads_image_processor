#include <QColor>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QRect>
#include <QStack>
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::restoreImage()
{
  buildGrid();

  QImage *finalImage = makeImage();
  if (!finalImage)
    throw Exception::outOfMemory();

  // TODO: Use tree

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
                   QColor(polygon.color.red,
                          polygon.color.green,
                          polygon.color.blue));
  painter.end();
}
