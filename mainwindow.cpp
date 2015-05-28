#include "MainWindow.h"

#include "HoverMoveFilter.h"
#include "WindowTitleFilter.h"
#include "TitleBar.h"
#include "MenuBar.h"

#include <QtWidgets/QSizeGrip>
#include <QMouseEvent>

#include <QLayout>
#include <QWidget>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    // Event and hover tricks
    mMousePressed = false;
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);
    installEventFilter(new HoverMoveFilter(this));
    installEventFilter(new WindowTitleFilter(this));

    // General initializations
    resize(1000, 600);
    setMinimumSize(800,500);
    setWindowTitle(APP_TITLE);
    setStyleSheet(getStyle());

    // Main Layout and Widget
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);
    resetMargins(mainLayout);

    QWidget *mainWidget = new QWidget(this);
    mainWidget->setObjectName("mainwidget");
    mainLayout->addWidget(mainWidget,0,0);
    setCentralWidget(mainWidget);

    // Base layout
    QVBoxLayout *base = new QVBoxLayout();
    resetMargins(base);
    base->setMargin(1);

    // Others layout
    QVBoxLayout *menu_title = new QVBoxLayout();
    resetMargins(menu_title);

    /* Player + Markers */
    QHBoxLayout *centralLayout = new QHBoxLayout();

    /* Preview */
    QVBoxLayout *bottomLayout = new QVBoxLayout();

    mainWidget->setLayout(base);
    base->addLayout(menu_title);
    base->addLayout(centralLayout);
    base->addLayout(bottomLayout);

    /* Title and menu bar */
    TitleBar *titlebar = new TitleBar(menu_title->widget(), this);
    MenuBar *menubar = new MenuBar(menu_title->widget());
    menu_title->addWidget(titlebar);
    menu_title->addWidget(menubar);

    // Player, marker and frames widgets
    p = new PlayerWidget(mainWidget);
    centralLayout->addWidget(p);

    m = new MarkersWidget(mainWidget);
    centralLayout->addWidget(m);

    f = new FramesWidget(mainWidget);
    bottomLayout->addWidget(f);

    f->setPlayer(p);

    connect(p,SIGNAL(frameChanged()),f,SLOT(drawFrames()));
    connect(p,SIGNAL(playbackStop()),f,SLOT(clearFrames()));
    //connect(p,SIGNAL(playbackPlay()),f,SLOT(drawFramesPlayback()));           //TODO: is this worth it?

    connect(menubar->actMediaOpen, SIGNAL(triggered()), this, SLOT(openMedia()));
}

MainWindow::~MainWindow()
{
}

/*! \brief open media file.
*
*	This functions is used to connect the "open" button.
*/
void MainWindow::openMedia()
{
    QString file = QFileDialog::getOpenFileName(0, "Open a video");
    if (file.isEmpty())
        return;
    p->openFile(file);
}


void MainWindow::resetMargins(QBoxLayout *obj)
{
    obj->setSpacing(0);
    obj->setMargin(0);
    obj->setContentsMargins(0,0,0,0);
}

QString MainWindow::getStyle() {
    return R"(
        /*FRAME*/
        * {
            color:#ececec;
            font-family: Verdana;
        }
        #mainwidget {
            border:1px solid #0088cc;
        }
        .QFrame {
            background-color:#222;
        }

        .QPushButton {
            color: #222;
        }
        /*FORM
        .QPushButton:hover {
            color: #fff;
            border-color:#fff;
        }
        .QLabel, .Line {
            color:#009dec;
        }
        .QLineEdit, .QTextEdit, .QComboBox, .QPlainTextEdit {
            color: #222;
            background-color: #e1e1e1;
            padding:0 5px 3px 3px;
            border-radius:0;
            border-left:5px solid #e1e1e1;
        }
        .QLineEdit:hover, .QTextEdit:hover, .QComboBox:hover, .QPlainTextEdit:hover {
            border-left:5px solid #009dec;
        }
        .QLineEdit:focus, .QTextEdit:focus, .QComboBox:focus, .QPlainTextEdit:focus {
            border-left:5px solid #009dec;
        }*/

        .QComboBox::drop-down {
            width: 40px;
            height: 35px;
            border:0;
         }
        .QComboBox::down-arrow {image: url(:/icons/arrow_down.png);}
        .QComboBox::down-arrow:on {image: url(:/icons/arrow_left.png);}
        .QComboBox QAbstractItemView {
            color:#222;
            background-color: #e1e1e1;
            padding: 0 8px;
         }
        .QComboBox QAbstractItemView::item:hover {
            background-color:#0088cc;
            color: #f0f0f0;
        }
        .QComboBox QAbstractItemView:focus {
            outline: none;
            border: 0;
        }

        /*QListWidget*/
        .QListWidget{
            color: #eee;
            background-color: #333;
        }
        .QListWidget::item {
            background-color: transparent;
            border:0;
            padding:0;
        }
        .QListWidget::item:hover {
            background-color:#40ACE2;
            color:#222;
        }
        .QListWidget::item:selected {
            background-color:#009DEC;
        }

        /*SPLITTEr*/
        QSplitter,
        QSplitter::handle {
            background-color:#222;
        }
    )";
}


/* MOUSE MOVE EVENTS */
void MainWindow::mousePressEvent(QMouseEvent *e)
{
    // mOldPos = e->pos();

    mMousePressed = e->button() == Qt::LeftButton;
    if (mMousePressed) {
        if (left) {
            mClickedPos.setX(e->pos().x());
        }
        if (right) {
            mClickedPos.setX(width() - e->pos().x());
        }
        if (bottom) {
            mClickedPos.setY(height() - e->pos().y());
        }
    }
    //setWindowTitle("Resizing");
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        mMousePressed = false;
    }
    //setWindowTitle("Borderless window");
}

void MainWindow::mouseMove(QPoint newPos, QPoint oldPos)
{
    if (mMousePressed) {
        int dx = newPos.x() - oldPos.x();
        int dy = newPos.y() - oldPos.y();

        QRect g = geometry();
        QSize minSize = minimumSize();

        // We don't resize if the windows has the minimum size
        if (left) {
            // Fix a bug when you try to resize to less than minimum size and
            // then the mouse goes right again.
            if (dx < 0 && oldPos.x() > mClickedPos.x() ) {
                dx += oldPos.x() - mClickedPos.x();
                if (dx > 0) {
                    dx = 0;
                }
            } else if ( dx > 0 && g.width() - dx < minSize.width()) {
                dx = g.width() - minSize.width();
            }
            g.setLeft(g.left() + dx);
        }

        if (right) {
            // Fix a bug when you try to resize to less than minimum size and
            // then the mouse goes right again.
            if (dx > 0 && (width() - newPos.x() > mClickedPos.x())) {
                dx -= width() - newPos.x() - mClickedPos.x();
                if (dx < 0) {
                    dx = 0;
                }
            }
            g.setRight(g.right() + dx);
        }
        if (bottom) {
            // Fix a bug when you try to resize to less than minimum size and
            // then the mouse goes down again.
            if (dy > 0 && (height() - newPos.y() > mClickedPos.y())) {
                dy -= height() - newPos.y() - mClickedPos.y();
                if (dy < 0) {
                    dy = 0;
                }
            }
            g.setBottom(g.bottom() + dy);
        }

        setGeometry(g);

    } else {
        QRect r = rect();
        left = qAbs(newPos.x()- r.left()) <= WINDOW_MARGIN &&
            newPos.y() > 0;//mTitleBar->height();
        right = qAbs(newPos.x() - r.right()) <= WINDOW_MARGIN &&
            newPos.y() > 0;//mTitleBar->height();
        bottom = qAbs(newPos.y() - r.bottom()) <= WINDOW_MARGIN;
        bool hor = left | right;

        if (hor && bottom) {
            if (left)
                setCursor(Qt::SizeBDiagCursor);
            else
                setCursor(Qt::SizeFDiagCursor);
        } else if (hor) {
            setCursor(Qt::SizeHorCursor);
        } else if (bottom) {
            setCursor(Qt::SizeVerCursor);
        } else {
            setCursor(Qt::ArrowCursor);
        }
    }
}


