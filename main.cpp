#include "mainwindow.h"
#include <QApplication>
#include <QtAVWidgets>

int main(int argc, char *argv[])
{
    QtAV::Widgets::registerRenderers();
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.show();

    return a.exec();
}
