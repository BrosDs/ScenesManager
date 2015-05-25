#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "frameswidget.h"
#include "playerwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

public:
    MainWindow(QWidget *parent = 0);
};

#endif // MAINWINDOW_H
