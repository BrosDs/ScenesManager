#-------------------------------------------------
#
# Project created by QtCreator 2015-05-23T10:59:56
#
#-------------------------------------------------

QT       += core gui avwidgets av

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ScenesManager
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        playerwidget.cpp\
        frameswidget.cpp

HEADERS  += mainwindow.h\
        playerwidget.h\
        frameswidget.h

RESOURCES += \
    playericons.qrc
