#include "MenuBar.h"
#include <QFileDialog>

MenuBar::MenuBar(QWidget *parent) : QMenuBar(parent)
{
    setObjectName("menubar");
    setStyleSheet(getStyle());

    QMenu* media = new QMenu("Media", this);
    actMediaOpen = new QAction("Open Media",media);
    actMediaPP = new QAction("Play/Pause",media);
    actMediaStop = new QAction("Stop",media);
    actMediaPF = new QAction("Previous Frame",media);
    actMediaNF = new QAction("Next Frame",media);
    actMediaInfo = new QAction("Media Info",media);
    actExit = new QAction("Exit",media);
    media->addAction(actMediaOpen);
    media->addAction(actMediaInfo);
    media->addSeparator();
    media->addAction(actMediaPP);
    media->addAction(actMediaStop);
    media->addAction(actMediaPF);
    media->addAction(actMediaNF);
    media->addSeparator();
    media->addAction(actExit);

    QMenu* markers = new QMenu("Markers", this);
    actMarkersNew = new QAction("New Marker",markers);
    actMarkersOpen = new QAction("Open Marker",markers);
    actMarkersSS = new QAction("Set Scene Start",markers);
    actMarkersSE = new QAction("Set Scene End",markers);
    markers->addAction(actMarkersNew);
    markers->addAction(actMarkersOpen);
    markers->addAction(actMarkersSS);
    markers->addAction(actMarkersSE);

    QMenu* video = new QMenu("Video", this);
    actVideoPM = new QAction("Presentation Mode",video);
    actVideoMax = new QAction("Maximize",video);
    video->addAction(actVideoPM);
    video->addAction(actVideoMax);

    QMenu* help = new QMenu("Help", this);
    actHelp = new QAction("About (credits)",help);
    help->addAction(actHelp);

    addMenu(media);
    addMenu(markers);
    addMenu(video);
    addMenu(help);

    setMinimumHeight(30);
    setMaximumHeight(30);
}

MenuBar::~MenuBar()
{
}

QString MenuBar::getStyle()
{
    return R"(
        /*#menubar*/
        #menubar {background-color:#0088cc;}
        #menubar::item {
            background:transparent;
            padding:5px 10px;
            color:#f0f0f0;}
        #menubar::item::selected,
        #menubar::item:hover,
        #menubar::item:pressed {
            color:#222222;
            background-color: #f6f6f6;}
        /*.QMenu*/
        #menubar QMenu {
            background-color: #f6f6f6;
            color:#222;}
        #menubar QMenu::item {background: transparent;}
        #menubar QMenu::item::selected {
            background-color:#0088cc;
            color: #f0f0f0;}
        #menubar QMenu::separator {
          height: 2px;
          color: #353535;}
    )";
}
