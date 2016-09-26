#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QImage>
#include <QMainWindow>
#include <QStack>
#include <QPoint>
#include <QWidget>

namespace Exception {
  class nullPointer {};
  class outOfMemory {};
}

struct Rgb {
  int red;
  int green;
  int blue;
};

struct Polygon {
  Rgb averageColor;
  QPoint topLeft;
  QPoint bottomRight;
};


namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  int sizeThreshold;
  int brightnessThreshold;

  Ui::MainWindow *ui;

  void (MainWindow::*processImage)();
  // Image grid
  void buildGrid();
  void grid(QImage *originalImage, QImage *stagedImage,
            QPoint topLeft, QPoint bottomRight);
  void drawRectangle(QImage *image, QPoint topLeft, QPoint bottomRight);

  void restoreImage();
  void fillRectangle(QImage *image, Polygon polygon);

  void markStrokes();

  // Image structures
  QStack<Polygon> polygons;

  // Image tools
  QImage *makeImage();
  bool isSizeThreshold(QPoint topLeft, QPoint bottomRight);
  bool isBrightnessThreshold(QImage *image, QPoint topLeft, QPoint bottomRight);
  Rgb getRgb(QImage *image, QPoint point);
  int averagePixelBrightness(QImage *image, QPoint point);
  Rgb averagePolygonBrightness(QImage *image,
                               QPoint topLeft, QPoint bottomRight);

private slots:
  // Button
  void on_openButton_clicked();
  void on_closeButton_clicked();
  void on_clearButton_clicked();
  void on_runButton_clicked();
  // SpinBox
  void on_sizeThreshold_valueChanged(int value);
  void on_brightnessThreshold_valueChanged(int value);
  // ComboBox
  void on_modeSwitcher_currentIndexChanged(int value);
};

#endif // MAINWINDOW_H
