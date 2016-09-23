QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Image_Algorithms
TEMPLATE = app

SOURCES += main.cpp mainwindow.cpp \
        button.cpp \
        grid.cpp \
        image.cpp \
        spinbox.cpp

HEADERS += mainwindow.h

FORMS += mainwindow.ui
