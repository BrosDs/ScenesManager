#include "PlayerWidget.h"

#include <StatisticsView.h>

#include <QtAVWidgets>
#include <QSlider>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QShortcut>

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
PlayerWidget::PlayerWidget(QWidget *parent) : QWidget(parent)
{
	m_player = new AVPlayer(this);
    playState = false;
	QVBoxLayout *base = new QVBoxLayout();
	setLayout(base);
	
	/** Add video render to the widget */
	m_vo = new VideoOutput(this);
	Q_ASSERT(m_vo);
	Q_ASSERT(m_vo->widget());
	if (!m_vo->widget()) {
		QMessageBox::warning(0, "QtAV error", "Can not create video renderer");
		return;
	}
	m_player->setRenderer(m_vo);
    base->addWidget(m_vo->widget());

	/** Add slider to the widget just at the bottom of the player */
	m_slider = new QSlider();
	m_slider->setOrientation(Qt::Horizontal);

	/** Connects the slider to the functions*/
	connect(m_slider, SIGNAL(sliderMoved(int)), SLOT(seek(int)));
	connect(m_player, SIGNAL(positionChanged(qint64)), SLOT(updateSlider()));
	connect(m_player, SIGNAL(started()), SLOT(updateSlider()));

    base->addWidget(m_slider);

	/** Player controls layout -> buttons displayed horizontally */
    QHBoxLayout *rows = new QHBoxLayout();
    base->addLayout(rows);

    initializeIcons();

	//TODO: remove this in the final version
	m_openBtn = new QPushButton("Open");

	/* Initialize all buttons values */
    m_playBtn = new QPushButton();
    m_playBtn->setIcon(QIcon(play));
    m_playBtn->setIconSize(play.rect().size());
    m_playBtn->setFixedSize(play.rect().size());

    m_stopBtn = new QPushButton();
    m_stopBtn->setIcon(QIcon(stop));
    m_stopBtn->setIconSize(stop.rect().size());
    m_stopBtn->setFixedSize(stop.rect().size());

    m_prevF = new QPushButton();
    m_prevF->setIcon(QIcon(prevF));
    m_prevF->setIconSize(prevF.rect().size());
    m_prevF->setFixedSize(prevF.rect().size());

    m_nextF = new QPushButton();
    m_nextF->setIcon(QIcon(nextF));
    m_nextF->setIconSize(nextF.rect().size());
    m_nextF->setFixedSize(nextF.rect().size());


    m_info = new QPushButton();
    m_info->setIcon(QIcon(info));
    m_info->setIconSize(info.rect().size());
    m_info->setFixedSize(info.rect().size());

    m_openBtn->setToolTip("Open media file");
	m_playBtn->setToolTip("Play");
	m_stopBtn->setToolTip("Stop");
	m_prevF->setToolTip("Previous Frame");
	m_nextF->setToolTip("Next Frame");
    m_info->setToolTip("Media info");

	//TODO: remove this in the final version
	rows->addWidget(m_openBtn);
    
	rows->addWidget(m_prevF);
    rows->addWidget(m_playBtn);
    rows->addWidget(m_stopBtn);
    rows->addWidget(m_nextF);
    rows->addWidget(m_info);

	//TODO: remove this in the final version
	connect(m_openBtn, SIGNAL(clicked()), SLOT(openMedia()));

	connect(m_prevF, SIGNAL(clicked()), SLOT(previousFrame()));
	connect(m_playBtn, SIGNAL(clicked()), SLOT(playPause()));
    connect(m_stopBtn, SIGNAL(clicked()), SLOT(stopVideo()));
	connect(m_nextF, SIGNAL(clicked()), SLOT(nextFrame()));
    connect(m_info, SIGNAL(clicked()), SLOT(showInfo()));

    QShortcut *s_open = new QShortcut(QKeySequence("Ctrl+O"), parent);
    QShortcut *s_play = new QShortcut(QKeySequence(Qt::Key_Space), parent);
    QShortcut *s_stop = new QShortcut(QKeySequence(Qt::Key_Delete), parent);
    QShortcut *s_prev = new QShortcut(QKeySequence(Qt::Key_Left), parent);
    QShortcut *s_next = new QShortcut(QKeySequence(Qt::Key_Right), parent);
    QShortcut *s_info = new QShortcut(QKeySequence("Ctrl+I"), parent);

    connect(s_open, SIGNAL(activated()), SLOT(openMedia()));
    connect(s_play, SIGNAL(activated()), SLOT(playPause()));
    connect(s_stop, SIGNAL(activated()), SLOT(stopVideo()));
    connect(s_prev, SIGNAL(activated()), SLOT(previousFrame()));
    connect(s_next, SIGNAL(activated()), SLOT(nextFrame()));
    connect(s_info, SIGNAL(activated()), SLOT(showInfo()));

	/** Widget minimum sizes */
    setMinimumSize(480,320);
}

PlayerWidget::~PlayerWidget(){
    if(m_vo) delete m_vo;
    if(m_player) delete m_player;
    if(m_slider) delete m_slider;


    if(m_openBtn) delete m_openBtn;
    if(m_playBtn) delete m_playBtn;
    if(m_stopBtn) delete m_stopBtn;
    if(m_prevF) delete m_prevF;
    if(m_nextF) delete m_nextF;
    if(m_info)  delete m_info;
}

/*************************************************************************** PRIVATE METHODS ************/
/*! \brief initialize player icons.
*
*	Initialize player icons based on the resources in "playericons.qrc" file.
*/
void PlayerWidget::initializeIcons(){
    play  = QPixmap(":/icons/playB.png");
    pause = QPixmap(":/icons/pauseB.png");
    stop  = QPixmap(":/icons/stopB.png");
    prevF = QPixmap(":/icons/prevFB.png");
    nextF = QPixmap(":/icons/nextFB.png");
    info = QPixmap(":/icons/infoB.png");
}


//TODO: remove in the final version
/*! \brief open media file.
*
*	This functions is used to connect the "open" button.
*	In the final version MUST be removed
*/
void PlayerWidget::openMedia()
{
	QString file = QFileDialog::getOpenFileName(0, "Open a video");
	if (file.isEmpty())
		return;
    m_player->setFile(file);
    playPause();
}

/*! \brief seek media.
*
*	Changes player position with the slider.
*	@param slider position
*/
void PlayerWidget::seek(int pos)
{
	if (!m_player->isPlaying())
		return;
	m_player->seek(pos * 1000LL); // to msecs
    emitterCheck();
}

/*! \brief play/pause functions.
*
*	Change the state of the player.
*	If the player isn't playing starts, otherwhise if it's pause changes it's status to playing
*	and resume the playback of the media.
*/
void PlayerWidget::playPause()
{
    if(m_player->file()!="")
        playState = !playState;
    else return;

    if (!m_player->isPlaying()) {
            m_player->play();
    }
    else{
        m_player->pause(!m_player->isPaused());
    }
    changePlayPause();
    emitterCheck();
}

/*! \brief stops the playback.
*
*	Stops the playback of the media and change the play/pause button to play state.
*/
void PlayerWidget::stopVideo(){
    m_player->stop();
    playState = false;
    changePlayPause();
    m_slider->setValue(0);
    emit playbackStop();
}

/*! \brief change play/pause button icon.
*
*	Changes the icon on the play/pause button based on
*	the player behavior.
*/
void PlayerWidget::changePlayPause(){
    //if(!m_player->isPlaying()) return;

    if(playState){
        m_playBtn->setToolTip("Pause");
        m_playBtn->setIcon(QIcon(pause));
        m_playBtn->setIconSize(pause.rect().size());
        m_playBtn->setFixedSize(pause.rect().size());

    }else{
        m_playBtn->setToolTip("Play");
        m_playBtn->setIcon(QIcon(play));
        m_playBtn->setIconSize(play.rect().size());
        m_playBtn->setFixedSize(play.rect().size());

    }
}

/*! \brief update slider.
*
*	Update the slider position based on player position.
*/
void PlayerWidget::updateSlider()
{
	m_slider->setRange(0, int(m_player->duration() / 1000LL));
	m_slider->setValue(int(m_player->position() / 1000LL));
    emit playbackPlay();
}

//TODO: Check formula
/*! \brief displays previous frame.
*
*	Displays the previous frame from the current player position.
*	The frame number is calculated and may not be correct.
*	@see toPreviousFrame()
*/
void PlayerWidget::previousFrame(){
    m_player->setPosition(positionFromFrameNumber(currentFrameNumber()));
    emit frameChanged();
}

//TODO: Check formula
/*! \brief displays next frame.
*
*	Displays the next frame from the current player position.
*	The frame number is calculated and may not be correct.
*	@see toNextFrame()
*/
void PlayerWidget::nextFrame(){

    m_player->setPosition(positionFromFrameNumber(currentFrameNumber()+2));
    emit frameChanged();
}

/*! \brief Get current frame number.
*
*	This functions is used to get the current frame number.
*	@param playerPosition
*	@return current frame number.
*	@see previousFrameNumber()
*	@see nextFrameNumber()
*/
qint64 PlayerWidget::currentFrameNumber(qint64 playerPosition){
    return ((playerPosition*m_player->statistics().video.frame_rate) / 1000LL);
}


void PlayerWidget::showInfo(){
   if (!statistic_viewer)
            statistic_viewer = new StatisticsView();
        if (m_player)
            statistic_viewer->setStatistics(m_player->statistics());
        statistic_viewer->show();


}

void PlayerWidget::emitterCheck(){
    if(playState==false)
        emit frameChanged();
}

/*************************************************************************** PUBLIC METHODS ************/

/*! \brief get AVPlayer pointer.
*
*	This functions is used to get the AVPlayer pointer used for rendering the media.
*	It's necessary to access to the currentFrame image.
*	@return QtAV::AVPlayer*
*/
QtAV::AVPlayer* PlayerWidget::getAVPlayer(){
	return m_player;
}

/*! \brief steps back one frame.
*
*	This functions is used to step back one frame from the current one.
*	@return previous frame number (from the past current).
*/
qint64 PlayerWidget::toPreviousFrame(){
	previousFrame();
	return currentFrameNumber();
}

/*! \brief steps further one frame.
*
*	This functions is used to display the next frame from the current one.
*	@return next frame number (from the past current).
*/
qint64 PlayerWidget::toNextFrame(){
	nextFrame();
	return currentFrameNumber();
}


/*! \brief Get current frame number.
*
*	This functions is used to get the current frame number.
*	@return current frame number.
*/
qint64 PlayerWidget::currentFrameNumber(){
	return ((m_player->position()*m_player->statistics().video.frame_rate) / 1000LL);
}

/*! \brief Get the previous frame number.
*
*	This functions is used to get the previous frame number.
*	@return previous frame number.
*/
qint64 PlayerWidget::previousFrameNumber(){
    return currentFrameNumber()-1;
}

//TODO: Check formula
/*! \brief Get the previous frame number.
*
*	This functions is used to get the previous frame number from the current player position.
*	@param player position
*	@return previous frame number.
*/
qint64 PlayerWidget::previousFrameNumber(qint64 playerPosition){
    return currentFrameNumber(playerPosition)-1;
}

/*! \brief Get the next frame number.
*
*	This functions is used to get the next frame number.
*	@return next frame number.
*/
qint64 PlayerWidget::nextFrameNumber(){
    return currentFrameNumber()+1;
}

/*! \brief Get the next frame number.
*
*	This functions is used to get the next frame number from the current player position.
*	@param player position
*	@return next frame number.
*/
qint64 PlayerWidget::nextFrameNumber(qint64 playerPosition){
    return currentFrameNumber(playerPosition)+1;
}


/*! \brief Get position from frame number.
*
*	This functions is used to get the player position from the frame number given in input.
*	@param frame number
*   @return player position
*/
qint64 PlayerWidget::positionFromFrameNumber(qint64 frame){
    return (frame/m_player->statistics().video.frame_rate) * 1000LL;
}

/*! \brief Set media to display.
*
*	This functions is used to start playing the media in AVPlayer.
*	@see PlayerWidget::openMedia()
*	@param file name of the media
*/
void PlayerWidget::openFile(QString file){
	if (file.isEmpty())
        return;
    m_player->setFile(file);
    playPause();
}
