#include "mainwindow.h"

void MainWindow::on_sizeThreshold_valueChanged(int value)
{
  this->sizeThreshold = value;
}

void MainWindow::on_brightnessThreshold_valueChanged(int value)
{
  this->brightnessThreshold = value;
}

void MainWindow::on_angle_valueChanged(int value)
{
  this->angle = value;
}
