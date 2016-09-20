QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Image_Algorithms
TEMPLATE = app

SOURCES += main.cpp \
        mainwindow.cpp \
        image/image.cpp \
        ui/buttons.cpp

HEADERS += mainwindow.h \
        image/image.h

FORMS += mainwindow.ui
