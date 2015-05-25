#ifndef FRAMESWIDGET_H
#define FRAMESWIDGET_H

#include <QWidget>
#include <QtAV>

class QHBoxLayout;
/**
*	FramesWidget class.
*/
class FramesWidget : public QWidget
{
    Q_OBJECT

private:
    int frame_num;

    QHBoxLayout *base;

    void paintEvent(QPaintEvent *);

public:
    explicit FramesWidget(QWidget *parent = 0);

private Q_SLOTS:

signals:

};


#endif // FRAMESWIDGET_H
