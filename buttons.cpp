#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_openButton_clicked()
{
  const QPixmap *image = new QPixmap(
        QFileDialog::getOpenFileName(nullptr, QString("Open image")));

  if (image->isNull()) {
    delete image;
    return;
  } else
    ui->originalImage->setPixmap(*image);
}
