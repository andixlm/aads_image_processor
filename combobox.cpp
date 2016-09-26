#include "mainwindow.h"

enum { bGrid, rImage, mStrokes };

void MainWindow::on_modeSwitcher_currentIndexChanged(int value)
{
  switch (value)
  {
    case bGrid:
      processImage = &MainWindow::buildGrid;
      break;
    case rImage:
      processImage = &MainWindow::restoreImage;
      break;
/*
    case mStrokes:
      processImage = &MainWindow::markStrokes;
      break;
*/
  }
}
