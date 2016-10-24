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
