#include <QFileDialog>
#include <QPixmap>
#include <QString>
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_openButton_clicked()
{
  const QPixmap *image = new QPixmap(
        QFileDialog::getOpenFileName(nullptr, QString("Open image")));

  if (!image->isNull())
    ui->originalImage->setPixmap(*image);
  else
    delete image;
}

void MainWindow::on_closeButton_clicked()
{
  if (ui->originalImage->pixmap() != nullptr) {
    ui->originalImage->clear();
    delete ui->originalImage->pixmap();
  }

  if (ui->stageOneImage->pixmap() != nullptr) {
    ui->stageOneImage->clear();
    delete ui->stageOneImage->pixmap();
  }

  if (ui->stageTwoImage->pixmap() != nullptr) {
    ui->stageTwoImage->clear();
    delete ui->stageTwoImage->pixmap();
  }

  if (ui->finalImage->pixmap() != nullptr) {
    ui->finalImage->clear();
    delete ui->finalImage->pixmap();
  }
}

void MainWindow::on_clearButton_clicked()
{
  if (ui->stageOneImage->pixmap() != nullptr) {
    ui->stageOneImage->clear();
    delete ui->stageOneImage->pixmap();
  }

  if (ui->stageTwoImage->pixmap() != nullptr) {
    ui->stageTwoImage->clear();
    delete ui->stageTwoImage->pixmap();
  }

  if (ui->finalImage->pixmap() != nullptr) {
    ui->finalImage->clear();
    delete ui->finalImage->pixmap();
  }
}

void MainWindow::on_runButton_clicked()
{
  return;
}
