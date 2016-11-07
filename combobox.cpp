#include "mainwindow.h"

enum { _buildGrid, _restoreImage, _removeBackground, _markStrokes };

void MainWindow::on_modeSwitcher_currentIndexChanged(int value)
{
  switch (value)
  {
    case _buildGrid:
      this->processImage = &MainWindow::buildGrid;
      break;

    case _restoreImage:
      this->processImage = &MainWindow::restoreImage;
      break;

    case _removeBackground:
      this->processImage = &MainWindow::removeBackground;
      break;

    case _markStrokes:
      processImage = &MainWindow::markStrokes;
      break;
  }
}

enum { _upTo30, _upTo60, _upTo90 };

void MainWindow::on_angleSwitcher_currentIndexChanged(int value)
{
  switch (value)
  {
    case _upTo30:
      this->angle = 30;
      break;

    case _upTo60:
      this->angle = 60;
      break;

    case _upTo90:
      this->angle = 89;
      break;
  }
}
