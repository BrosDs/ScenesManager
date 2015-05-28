#include "FramesWidget.h"

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
    setMinimumSize(800,200);
    setFixedHeight(200);

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
    //TODO: cancellare i frame se ci sono
    if(frame_num!=0)
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
        prev[i]->setFixedSize(frame_w, frame_h);

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
    if(prev!=NULL)
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
    if(frame_num!=0){
        for(int i=0; i < frame_num; i++){
            if(prev[i]) delete prev[i];
            if(tile[i]) delete tile[i];
        }

        delete prev;
        delete tile;
    }
    frame_num = 0;
}


void FramesWidget::calculateFrameNumberAndSize(){
    qDebug() << "Calculating" << endl;

    qint64 w = player->statistics().video_only.coded_width;
    qint64 h = player->statistics().video_only.coded_height;


    frame_h = 140;
    double ratio = (double) ( (double) h / (double) frame_h);   //cast is necessary due to round ups
    frame_w = w / ratio;

    qDebug() << w << "x" << h << endl;
    qDebug() << ratio << endl;
    qDebug() << frame_w << "x" << frame_h << endl;

    frame_num = width()/frame_w;

    prev = new VideoPreviewWidget*[frame_num];
    tile = new QWidget*[frame_num];
}



