#include <ctime>
#include <cstdlib>
#include <QFileDialog>
#include <QPixmap>
#include <QString>
#include <QTextStream>
#include "exception.h"
#include "file.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

const QString openImage = "Open image";

void MainWindow::on_openImageButton_clicked()
{
  const QPixmap* image =
      new QPixmap(QFileDialog::getOpenFileName(nullptr, openImage));
  if (image == nullptr)
    throw Exception::outOfMemory();

  if (!image->isNull()) {
    MainWindow::on_closeButton_clicked();
    ui->originalImage->setPixmap(*image);
  }
  else
    delete image;
}

void MainWindow::on_openFileButton_clicked()
{
  cleanUpImageData();

  this->imageArray = readFile();
  this->imageTree = Tree::toTree(this->imageArray);
}

void MainWindow::on_saveToFileButton_clicked()
{
  if (this->imageArray == nullptr)
    return;

  writeFile(this->imageArray);
}

void MainWindow::on_closeButton_clicked()
{
  cleanUpImageData();

  if (ui->originalImage->pixmap() != nullptr) {
    ui->originalImage->clear();
    delete ui->originalImage->pixmap();
  }

  if (ui->stagedImage->pixmap() != nullptr) {
    ui->stagedImage->clear();
    delete ui->stagedImage->pixmap();
  }

  if (ui->finalImage->pixmap() != nullptr) {
    ui->finalImage->clear();
    delete ui->finalImage->pixmap();
  }
}

void MainWindow::on_clearButton_clicked()
{
  cleanUpImageData();

  if (ui->stagedImage->pixmap() != nullptr) {
    ui->stagedImage->clear();
    delete ui->stagedImage->pixmap();
  }

  if (ui->finalImage->pixmap() != nullptr) {
    ui->finalImage->clear();
    delete ui->finalImage->pixmap();
  }
}

void MainWindow::on_runButton_clicked()
{
  ui->wastedTimeLabel->setText(QString());

  int ticksStart = clock();
  (this->*processImage)();
  int ticksEnd = clock();
  double seconds = static_cast<double>(ticksEnd - ticksStart) / CLOCKS_PER_SEC;

  ui->wastedTimeLabel->setNum(seconds);
}
