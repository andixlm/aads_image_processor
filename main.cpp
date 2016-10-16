#include <QApplication>
#include "mainwindow.h"

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  MainWindow mainWindow;
  mainWindow.setFixedSize(mainWindow.width(), mainWindow.height());
  mainWindow.show();

  return app.exec();
}
