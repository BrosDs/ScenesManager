#ifndef MENUBAR_H
#define MENUBAR_H

#include <QtGui>
#include <QtWidgets/QMenuBar>

class MenuBar : public QMenuBar
{
    Q_OBJECT

    QString getStyle();

public:
    MenuBar(QWidget *parent);

    QString openMedia();

    /* File */
    QAction* actionHouses;
    QAction* actionOpen;
    QAction* actionExit;
    /* Others */
    QAction* actionCiaoDario;
    QAction* actionCiaoRava;
    /* Help */
    QAction* actionAbout;
    QAction* action30L;

};

#endif // MENUBAR_H
