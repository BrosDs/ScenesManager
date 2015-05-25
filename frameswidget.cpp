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

    /** Widget minimum sizes */
    setFixedSize(800,280);

    QPalette Pal(palette());

    // set black background
    Pal.setColor(QPalette::Background, Qt::black);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
}


void FramesWidget::setPlayer(QtAV::AVPlayer* p){
    this->player=p;
}

//TODO: check this
void FramesWidget::drawFrames(){
    clearFrames();

    for(int i = 0; i < frame_num; i++){
        prev[i]=new VideoPreviewWidget();
        prev[i]->setFile(player->file());
        prev[i]->setTimestamp(player->position()+i*1000);
        prev[i]->preview();
        prev[i]->resize(200,280);
        base->addWidget(prev[i]);
    }

}

void FramesWidget::clearFrames(){

    if ( base->layout() != NULL )
    {
        QLayoutItem* item;
        while ( ( item = base->layout()->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
    }
}
