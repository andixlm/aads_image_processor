#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QTextStream>
#include "exception.h"
#include "file.h"

const int packageSize = 3;
const int polygonSize = 7;

const QString openFile = "Open file";
const QString saveFile = "Save file";

int* readFile()
{
  QFile file(QFileDialog::getOpenFileName(nullptr, openFile));
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return nullptr;
  QTextStream input(&file);

  int size = 0;
  while(!input.atEnd()) {
    int null;
    input >> null;
    ++size;
  }
  int* array = new int[size];

  input.seek(0);

  int idx = 0;
  while(!input.atEnd())
    input >> array[idx++];

  file.close();

  return array;
}

void writeFile(int *array)
{
  if (array == nullptr)
    return;

  QFile file(QFileDialog::getSaveFileName(nullptr, saveFile, QString(), QString("*.txt")));
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return;
  QTextStream outStream(&file);

  int idx = 0, polygonsIdx = 0;
  bool isPolygonsFound = false;
  while (array[++idx] != -1)
    if (!isPolygonsFound &&
        array[idx] == 0 && array[idx + 1] == 0 && array[idx + 2] == 0)
      polygonsIdx = idx + 3, isPolygonsFound = true;

  int arraySize = idx + 1;

  idx = 0;
  outStream << array[idx++] << '\n';

  while (idx < polygonsIdx) {
    outStream << array[idx] << ' ';
    if (idx++ % packageSize == 0)
      outStream << '\n';
  }

  idx = 0;
  while (idx + polygonsIdx < arraySize - 1) {
    outStream << array[idx + polygonsIdx] << ' ';
    if (++idx % polygonSize == 0)
      outStream << '\n';
  }

  outStream << array[arraySize - 1];

  file.close();
}
