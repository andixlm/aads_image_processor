#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QImage>
#include <QMainWindow>
#include <QPoint>
#include <QStack>
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
  Rgb color;
  QPoint topLeft;
  QPoint bottomRight;
};

struct treeNode {
  Polygon polygon;
  treeNode *left;
  treeNode *right;
};

treeNode *treeAdd(treeNode *root, Polygon polygon);
int comparePolygonPositions(Polygon alpha, Polygon beta);
int* treeToArray(treeNode *);
void treeClear(treeNode *root);

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

  // Image restore
  void restoreImage();
  void restoreImageByTree(treeNode *root, QImage *image);
  void fillRectangle(QImage *image, Polygon polygon);

  // Image mark
  void markStrokes();

  // Image structures
  treeNode *root;
  int *treeArray;

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
