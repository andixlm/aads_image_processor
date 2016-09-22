#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QImage>
#include <QMainWindow>
#include <QPoint>
#include <QWidget>

namespace Exception {
  class nullPointer {};
  class outOfMemory {};
}

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;

  void (*processImage)();
  void buildGrid();
  void restoreImage();
  void markStrokes();

  QImage *makeImage();
  void makeGrid(QImage *image, QPoint topLeft, QPoint bottomRight, int threshold);
  void drawRectangle(QImage *image, QPoint topLeft, QPoint bottomRight);
  bool isSizeThreshold(QPoint topLeft, QPoint bottomRight);
  bool isBrightnessThreshold(QImage *image, QPoint topLeft, QPoint bottomRight,
                           int threshold);
  int averagePixelBrightness(QImage *image, QPoint point);

private slots:
  void on_openButton_clicked();
  void on_closeButton_clicked();
  void on_clearButton_clicked();
  void on_runButton_clicked();
};

#endif // MAINWINDOW_H
