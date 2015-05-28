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
    ~MenuBar();

    /* Media */
    QAction* actMediaOpen;
    QAction* actMediaPP;
    QAction* actMediaStop;
    QAction* actMediaPF;
    QAction* actMediaNF;
    QAction* actMediaInfo;
    QAction* actExit;

    /* Markers */
    QAction* actMarkersNew;
    QAction* actMarkersOpen;
    QAction* actMarkersSS;
    QAction* actMarkersSE;

    /* Video */
    QAction* actVideoPM;
    QAction* actVideoMax;

    /* Help */
    QAction* actHelp;
};

#endif // MENUBAR_H
