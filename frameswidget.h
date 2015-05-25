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
    int frame_num;
    int frame_w;
    int frame_h;

    QHBoxLayout *base;

    QtAV::AVPlayer *player;

    QtAV::VideoPreviewWidget **prev;

    void calculateFrameNumberAndSize();



public:
    explicit FramesWidget(QWidget *parent = 0);

    void setPlayer(QtAV::AVPlayer*);

private Q_SLOTS:
    void drawFrames();
    void clearFrames();

signals:

};


#endif // FRAMESWIDGET_H
