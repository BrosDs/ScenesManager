#include "mainwindow.h"

#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    QWidget *pl;
    QWidget *tl;

    QVBoxLayout *base = new QVBoxLayout();
    setLayout(base);

    PlayerWidget *p = new PlayerWidget(pl);
    base->addWidget(pl);


    FramesWidget *f = new FramesWidget(tl);
    base->addWidget(tl);

    //tl->setGeometry(0,320,800,280);
}

