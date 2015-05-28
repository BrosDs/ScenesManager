#include "MarkersWidget.h"

#include <QLayout>
#include <QTextEdit>

using namespace QtAV;

/*! \brief PlayerWidget Constructor.
*
*  Player Widget Constructor.
*  This class creates a complete widget with the following layout.
*	+---------------+
*	|               |
*	|   PLAYER      |
*	|               |
*	+---------------+
*	-----------//----
*	  [|<][>][#][>|]
*/
MarkersWidget::MarkersWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *base = new QVBoxLayout();
    setLayout(base);

    QTextEdit *tmp = new QTextEdit();
    base->addWidget(tmp);

    /** Widget minimum sizes */
    setMinimumSize(480,320);
}

MarkersWidget::~MarkersWidget()
{

}

