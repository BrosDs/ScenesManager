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
    tile = new QWidget*[frame_num];
}

FramesWidget::~FramesWidget(){
    clearFrames();
    delete this->player;
    delete this->pw;
}


void FramesWidget::setPlayer(PlayerWidget *p){
    this->pw=p;
    this->player=pw->getAVPlayer();
}

void FramesWidget::drawFrames(){
    clearFrames();
    calculateFrameNumberAndSize();

    for(int i = 0; i < frame_num; i++){
        QVBoxLayout *ly = new QVBoxLayout();
        tile[i] = new QWidget();
        tile[i]->setLayout(ly);

        prev[i] = new VideoPreviewWidget();
        prev[i]->setFile(player->file());
        prev[i]->setTimestamp(pw->positionFromFrameNumber(pw->nextFrameNumber()+i-1));

        prev[i]->preview();
        prev[i]->setFixedSize(frame_w,frame_h);

        ly->addWidget(prev[i]);
        QLabel *lbl = new QLabel(QString::number(pw->currentFrameNumber()+i));
        ly->addWidget(lbl);
        lbl->setStyleSheet("QLabel { color : white; }");

        if(i==1){
            //Why is this the current frame?
            tile[i]->setStyleSheet("QWidget{ background-color: grey; }");
        }

        base->addWidget(tile[i]);
    }

}

//TODO: remove blinking effect due to clearFrames();
void FramesWidget::drawFramesPlayback(){
    clearFrames();
    calculateFrameNumberAndSize();

    for(int i = 0; i < frame_num; i++){
        QVBoxLayout *ly = new QVBoxLayout();
        tile[i] = new QWidget();
        tile[i]->setLayout(ly);

        prev[i] = new VideoPreviewWidget();
        prev[i]->setFile(player->file());
        prev[i]->setTimestamp(pw->positionFromFrameNumber(pw->nextFrameNumber()+i-1));

        prev[i]->preview();
        prev[i]->setFixedSize(frame_w,frame_h);

        ly->addWidget(prev[i]);
        QLabel *lbl = new QLabel(QString::number(pw->currentFrameNumber()+i));
        ly->addWidget(lbl);
        lbl->setStyleSheet("QLabel { color : white; }");

        if(i==1){
            //Why is this the current frame?
            tile[i]->setStyleSheet("QWidget{ background-color: grey; }");
        }

        base->addWidget(tile[i]);
    }

}

void FramesWidget::clearFrames(){
    for(int i=0; i< frame_num; i++){
        delete prev[i];
        delete tile[i];
    }
    delete prev;
    delete tile;
}

void FramesWidget::calculateFrameNumberAndSize(){
    int w = player->statistics().video_only.width;
    int h = player->statistics().video_only.height;

    frame_h = 140;
    frame_w = w / (h/frame_h);

    frame_num = width()/frame_w;

    prev = new VideoPreviewWidget*[frame_num];
    tile = new QWidget*[frame_num];
}
