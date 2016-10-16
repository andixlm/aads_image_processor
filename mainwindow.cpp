#include <QMainWindow>
#include <QWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  imageTree = nullptr;
  imageArray = nullptr;
  processImage = &MainWindow::buildGrid;
  imageSize = 256;
  sizeThreshold = ui->sizeThreshold->value();
  brightnessThreshold = ui->brightnessThreshold->value();
}

MainWindow::~MainWindow()
{
  delete ui;
}
