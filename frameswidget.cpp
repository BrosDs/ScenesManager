#include "frameswidget.h"

#include <QtAVWidgets>
#include <QLabel>
#include <QHBoxLayout>

using namespace QtAV;

/*! \brief Frames Widget Constructor.
*
*  Frames Widget Constructor.
*  This class creates the bottom frame display.
*	+----------------------------------------------------+
*	|       ||       ||       ||       ||       ||       |
* 	|       ||       ||       ||       ||       ||       |
* 	|       ||       ||       ||       ||       ||       |
* 	|       ||       ||       ||       ||       ||       |
*	+----------------------------------------------------+
*
*/
FramesWidget::FramesWidget(QWidget *parent) : QWidget(parent)
{
    base = new QHBoxLayout();
    setLayout(base);

    QPalette Pal(palette());

    /** Widget background color */
    Pal.setColor(QPalette::Background, Qt::black);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);


    /** Widget minimum sizes */
    setMinimumSize(800,180);
    setFixedHeight(180);

    /** Calculate number of frames */

    prev = new VideoPreviewWidget*[frame_num];
}


void FramesWidget::setPlayer(QtAV::AVPlayer* p){
    this->player=p;
}

//TODO: check this
void FramesWidget::drawFrames(){
    calculateFrameNumberAndSize();

    for(int i = 0; i < frame_num; i++){
        prev[i] = new VideoPreviewWidget();
        prev[i]->setFile(player->file());
        prev[i]->setTimestamp(player->position() + (i-1)*42);
        prev[i]->preview();
        prev[i]->setFixedSize(frame_w,frame_h);
        base->addWidget(prev[i]);
    }

}

void FramesWidget::clearFrames(){
    for(int i=0; i< frame_num; i++)
        delete prev[i];
    delete prev;
}

void FramesWidget::calculateFrameNumberAndSize(){
    clearFrames();


    int w = player->statistics().video_only.width;
    int h = player->statistics().video_only.height;

    frame_h = 140;
    frame_w = w / (h/frame_h);

    frame_num = width()/frame_w;

    prev = new VideoPreviewWidget*[frame_num];
}
