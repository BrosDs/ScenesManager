#include "HoverMoveFilter.h"
#include "MainWindow.h"
#include <QHoverEvent>

HoverMoveFilter::HoverMoveFilter(QObject *parent) :
    QObject(parent)
{
}

HoverMoveFilter::~HoverMoveFilter()
{
}

bool HoverMoveFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::HoverMove) {
        QHoverEvent *mouseHoverEvent = static_cast<QHoverEvent *>(event);
        MainWindow* frame = static_cast<MainWindow *>(obj);
        frame->mouseMove(mouseHoverEvent->pos(), mouseHoverEvent->oldPos());
    }
    // standard event processing
    return QObject::eventFilter(obj, event);
}
