#include <QMainWindow>
#include <QWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  processImage = &MainWindow::buildGrid;
}

MainWindow::~MainWindow()
{
  delete ui;
}
