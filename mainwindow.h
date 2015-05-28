#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>

#include "PlayerWidget.h"
#include "MarkersWidget.h"
#include "FramesWidget.h"

#define WINDOW_MARGIN 5
#define APP_TITLE "ScenesManager"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QString getStyle();
    void resetMargins(QBoxLayout *obj);

    PlayerWidget *p;
    MarkersWidget *m;
    FramesWidget *f;

    // Titlebar
    QPoint mClickedPos;
    bool mMousePressed;
    bool left;
    bool right;
    bool bottom;

private Q_SLOTS:
    void openMedia();

public:
    MainWindow(QWidget *parent = 0);

    // Mouse events
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMove(QPoint newPos, QPoint oldPos);
};

#endif // MAINWINDOW_H
