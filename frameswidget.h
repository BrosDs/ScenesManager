#ifndef FRAMESWIDGET_H
#define FRAMESWIDGET_H

#include <QWidget>
#include <QtAV>
#include "playerwidget.h"

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

    PlayerWidget *pw;
    QtAV::AVPlayer *player;

    QtAV::VideoPreviewWidget **prev;
    QWidget **tile;

    void calculateFrameNumberAndSize();

public:
    explicit FramesWidget(QWidget *parent = 0);
    ~FramesWidget();

    void setPlayer(PlayerWidget*);

private Q_SLOTS:
    void drawFrames();
    void clearFrames();
    void drawFramesPlayback();

signals:

};


#endif // FRAMESWIDGET_H
