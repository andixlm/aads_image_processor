#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "tree.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow* ui;

  Tree::node* imageTree;
  int* imageArray;

  int imageSize;
  int sizeThreshold;
  int brightnessThreshold;

  void cleanUpImageData();

  void (MainWindow::* processImage)();
  void buildGrid();
  void restoreImage();
  void removeBackground();
  void markStrokes();

private slots:
  // Buttons
  void on_openImageButton_clicked();
  void on_openFileButton_clicked();
  void on_saveToFileButton_clicked();
  void on_closeButton_clicked();
  void on_clearButton_clicked();
  void on_runButton_clicked();

  // Value selectors
  void on_angle_valueChanged(int value);
  void on_sizeThreshold_valueChanged(int value);
  void on_brightnessThreshold_valueChanged(int value);

  // Switchers
  void on_modeSwitcher_currentIndexChanged(int value);
};

#endif // MAINWINDOW_H
