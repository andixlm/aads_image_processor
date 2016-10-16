QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Image_Algorithms
TEMPLATE = app

SOURCES += main.cpp mainwindow.cpp \
    button.cpp \
    combobox.cpp \
    file.cpp \
    grid.cpp \
    image.cpp \
    restore.cpp \
    spinbox.cpp \
    tools.cpp \
    tree.cpp

HEADERS += mainwindow.h \
    containers.h \
    exception.h \
    file.h \
    image.h \
    tree.h

FORMS += mainwindow.ui
