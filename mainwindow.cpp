#include "mainwindow.h"

#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    QWidget *pl;
    QWidget *tl;

    QVBoxLayout *base = new QVBoxLayout();
    //setLayout(base);

    QWidget *widget = new QWidget();
    widget->setLayout(base);
    setCentralWidget(widget);

    PlayerWidget *p = new PlayerWidget(pl);
    base->addWidget(p);


    FramesWidget *f = new FramesWidget(tl);
    base->addWidget(f);

    f->setPlayer(p->getAVPlayer());

    connect(p,SIGNAL(frameChanged()),f,SLOT(drawFrames()));
    connect(p,SIGNAL(playbackStop()),f,SLOT(clearFrames()));

}

