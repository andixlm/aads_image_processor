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

void MainWindow::on_closeButton_clicked()
{
  if (!ui->originalImage->pixmap()) {
    ui->originalImage->clear();
    delete ui->originalImage->pixmap();
  }

  if (!ui->stageOneImage->pixmap()) {
    ui->stageOneImage->clear();
    delete ui->stageOneImage->pixmap();
  }

  if (!ui->stageTwoImage->pixmap()) {
    ui->stageTwoImage->clear();
    delete ui->stageTwoImage->pixmap();
  }

  if (!ui->finalImage->pixmap()) {
    ui->finalImage->clear();
    delete ui->finalImage->pixmap();
  }
}

void MainWindow::on_clearButton_clicked()
{
  if (!ui->stageOneImage->pixmap()) {
    ui->stageOneImage->clear();
    delete ui->stageOneImage->pixmap();
  }

  if (!ui->stageTwoImage->pixmap()) {
    ui->stageTwoImage->clear();
    delete ui->stageTwoImage->pixmap();
  }

  if (!ui->finalImage->pixmap()) {
    ui->finalImage->clear();
    delete ui->finalImage->pixmap();
  }
}
