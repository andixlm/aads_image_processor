#include <QMainWindow>
#include <QWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  // Set up default parameters.
  processImage = &MainWindow::buildGrid;
  sizeThreshold = ui->sizeThreshold->value();
  brightnessThreshold = ui->brightnessThreshold->value();
}

MainWindow::~MainWindow()
{
  delete ui;
}
