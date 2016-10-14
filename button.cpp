#include <QFileDialog>
#include <QPixmap>
#include <QString>
#include <QTextStream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_openButton_clicked()
{
  const QPixmap *image = new QPixmap(
        QFileDialog::getOpenFileName(nullptr, QString("Open image")));

  if (!image)
    throw Exception::outOfMemory();

  if (!image->isNull())
    ui->originalImage->setPixmap(*image);
  else
    delete image;
}

void MainWindow::on_openFileButton_clicked()
{
  QFile file(QFileDialog::getOpenFileName(nullptr, QString("Open text file")));
  file.open(QIODevice::ReadOnly | QIODevice::Text);

  QTextStream input(&file);

  int size = 0;
  while(!input.atEnd()) {
    int temp;
    input >> temp;
    ++size;
  }

  input.seek(0);

  if (this->treeArray)
    delete this->treeArray;

  this->treeArray = new int[size];

  int idx = 0;
  while(!input.atEnd())
    input >> this->treeArray[idx++];

  this->arraySize = size;

  file.close();
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
  if (ui->originalImage->pixmap() == nullptr)
    return;

  (this->*processImage)();
}
