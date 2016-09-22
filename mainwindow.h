#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

  QImage *makeImage();
  void makeGrid(QImage *image, QPoint pointOne, QPoint pointTwo, int threshold);
  bool isSizeThreshold(QPoint pointOne, QPoint pointTwo);
  bool isBrightnessThreshold(QImage *image, QPoint pointOne, QPoint pointTwo,
                           int threshold);
  int averagePixelBrightness(QImage *image, QPoint point);

private slots:
  void on_openButton_clicked();
  void on_closeButton_clicked();
  void on_clearButton_clicked();
  void on_runButton_clicked();
};

#endif // MAINWINDOW_H
