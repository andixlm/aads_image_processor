QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Image_Algorithms
TEMPLATE = app

SOURCES += main.cpp \
        mainwindow.cpp \
        ui/buttons.cpp \
        image/tools.cpp

HEADERS += mainwindow.h \
        image/tools.h

FORMS += mainwindow.ui
