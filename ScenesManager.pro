#-------------------------------------------------
#
# Project created by QtCreator 2015-05-23T10:59:56
#
#-------------------------------------------------

QT       += core gui avwidgets av

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ScenesManager
TEMPLATE = app

CONFIG += console

SOURCES += main.cpp\
        MainWindow.cpp\
        PlayerWidget.cpp\
        FramesWidget.cpp\
        StatisticsView.cpp \
        TitleBar.cpp \
        MenuBar.cpp \
        HoverMoveFilter.cpp \
        WindowTitleFilter.cpp \
        MarkersWidget.cpp

HEADERS  += MainWindow.h\
        PlayerWidget.h\
        FramesWidget.h\
        StatisticsView.h \
        TitleBar.h \
        MenuBar.h \
        HoverMoveFilter.h \
        WindowTitleFilter.h \
        MarkersWidget.h

RESOURCES += \
    playericons.qrc \
    titlebar.qrc
