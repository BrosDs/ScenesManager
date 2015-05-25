#ifndef FRAMESWIDGET_H
#define FRAMESWIDGET_H

#include <QWidget>
#include <QtAV>

namespace QtAV{
class VideoPreviewWidget;
}

class QHBoxLayout;
/**
*	FramesWidget class.
*/
class FramesWidget : public QWidget
{
    Q_OBJECT

private:
    static const int frame_num = 4  ;
    QHBoxLayout *base;

    QtAV::AVPlayer *player;

    QtAV::VideoPreviewWidget *prev[frame_num];





public:
    explicit FramesWidget(QWidget *parent = 0);

    void setPlayer(QtAV::AVPlayer*);

private Q_SLOTS:
    void drawFrames();
    void clearFrames();

signals:

};


#endif // FRAMESWIDGET_H
