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

    frame_num=10;

    /** Widget minimum sizes */
    //setFixedSize(800,280);

    QPalette Pal(palette());

    // set black background
    Pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);

}

void FramesWidget::paintEvent(QPaintEvent*) {
    return;
    QPainter painter(this);

    int width = size().width() - 3;
    int height = size().height() - 5;

    painter.fillRect(0, 0, width, height, QColor(0,0,0));
}
