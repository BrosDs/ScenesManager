#include "MenuBar.h"
#include <QFileDialog>

MenuBar::MenuBar(QWidget *parent) : QMenuBar(parent)
{
    setObjectName("menubar");
    setStyleSheet(getStyle());

    QMenu* menu1 = new QMenu("File", this);
    actionHouses = new QAction("Houses",menu1);
    actionOpen = new QAction("Open Media",menu1);
    actionExit = new QAction("Exit",menu1);
    menu1->addAction(actionHouses);
    menu1->addAction(actionOpen);
    menu1->addAction(actionExit);

    QMenu* menu2 = new QMenu("Others", this);
    actionCiaoDario = new QAction("Ciao Dario",menu2);
    actionCiaoRava = new QAction("Ciao Rava",menu2);
    menu2->addAction(actionCiaoDario);
    menu2->addAction(actionCiaoRava);

    QMenu* menu3 = new QMenu("Help", this);
    actionAbout = new QAction("About",menu3);
    action30L = new QAction("30L easy gg wp",menu3);
    menu3->addAction(actionAbout);
    menu3->addAction(action30L);

    addMenu(menu1);
    addMenu(menu2);
    addMenu(menu3);

    setMaximumHeight(30);
}

QString MenuBar::getStyle(){
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

/*! \brief open media file.
*
*	This functions is used to connect the "open" button.
*/
QString MenuBar::openMedia()
{
    QString file = QFileDialog::getOpenFileName(0, "Open a video");
    if (file.isEmpty())
        return "";
    return file;
}

