#include "TitleBar.h"

TitleBar::TitleBar(QWidget *parent, QWidget *mainw) : QWidget(parent)
{

    mainwin = mainw;
    mMaxNormal = false;

    setObjectName("titlebar");
    setStyleSheet(getStyle());

    /* Init */
    QHBoxLayout *hbox = new QHBoxLayout(this);

    mLabel = new QLabel(this);
    mLabel->setText(mainwin->windowTitle());

    mMinimizeButton = new QToolButton(this);
    mMaximizeButton = new QToolButton(this);
    mCloseButton	= new QToolButton(this);

    QIcon closeicon = QIcon(":/icons/close_normal.png");
    maxicon = QIcon(":/icons/maximize_normal.png");
    QIcon minicon = QIcon(":/icons/minimize_normal.png");
    resticon = QIcon(":/icons/restore_normal.png");


    /* Gui */
    mCloseButton->setIcon(closeicon);
    mMaximizeButton->setIcon(maxicon);
    mMinimizeButton->setIcon(minicon);

    mMinimizeButton->setMinimumHeight(25);
    mCloseButton->setMinimumHeight(25);
    mMaximizeButton->setMinimumHeight(25);


    /* Binding */
    hbox->addWidget(mLabel);
    hbox->addWidget(mMinimizeButton);
    hbox->addWidget(mMaximizeButton);
    hbox->addWidget(mCloseButton);

    //hbox->insertStretch(1, 500);
    hbox->setSpacing(0);
    hbox->setMargin(0);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    connect(mCloseButton, SIGNAL(clicked()), mainwin, SLOT(close()));
    connect(mMinimizeButton, SIGNAL(clicked()), this, SLOT(showSmall()));
    connect(mMaximizeButton, SIGNAL(clicked()), this, SLOT(showMaxRestore()));
}

TitleBar::~TitleBar()
{
}

QString TitleBar::getStyle()
{
    return R"(
        #titlebar {
            background-color:#0088cc;
        }
        #titlebar QLabel {
            color:#fff;
            font-weight:bold;
            margin-left:20px;
        }
        #titlebar QToolButton {
            width:40px;
            border:0px;
        }
        #titlebar QToolButton::selected,
        #titlebar QToolButton:hover,
        #titlebar QToolButton:pressed {
            background:#222 !important;
        }
    )";
}

void TitleBar::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TitleBar::titleChanged()
{
    mLabel->setText(mainwin->windowTitle());
}

void TitleBar::showSmall()
{
    mainwin->showMinimized();
}

void TitleBar::showMaxRestore()
{
    if (mMaxNormal) {
        mainwin->showNormal();
        mMaxNormal = !mMaxNormal;
        mMaximizeButton->setIcon(maxicon);
    } else {
        mainwin->showMaximized();
        mMaxNormal = !mMaxNormal;
        mMaximizeButton->setIcon(resticon);
    }
}

void TitleBar::mousePressEvent(QMouseEvent *me)
{
    mStartPos = me->globalPos();
    mClickPos = mapToParent(me->pos());
}

void TitleBar::mouseMoveEvent(QMouseEvent *me)
{
    if (mMaxNormal)
        return;
    mainwin->move(me->globalPos() - mClickPos);
}
