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
  QImage *originalImage = new QImage(ui->originalImage->pixmap()->toImage());
  if (!originalImage)
    throw Exception::outOfMemory();

  this->polygons.clear();

  QImage *stagedImage = makeImage();
  QImage *finalImage = new QImage(ui->originalImage->pixmap()->toImage());

  grid(originalImage, stagedImage, QPoint(0, 0), QPoint(256, 256));

  ui->stageOneImage->setPixmap(QPixmap::fromImage(*stagedImage));

  for (QStack<Polygon>::iterator itr = polygons.begin(), end = polygons.end();
       itr != end; ++itr)
    fillRectangle(finalImage, *itr);

  ui->finalImage->setPixmap(QPixmap::fromImage(*finalImage));

  delete originalImage;
  delete stagedImage;
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
