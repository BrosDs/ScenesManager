#include "playerwidget.h"

#include <QPushButton>
#include <QSlider>
#include <QLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QtAVWidgets>
#include <QLabel>
#include <QHBoxLayout>

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

	m_openBtn->setToolTip("Open media file");
	m_playBtn->setToolTip("Play");
	m_stopBtn->setToolTip("Stop");
	m_prevF->setToolTip("Previous Frame");
	m_nextF->setToolTip("Next Frame");

	//TODO: remove this in the final version
	rows->addWidget(m_openBtn);
    
	rows->addWidget(m_prevF);
    rows->addWidget(m_playBtn);
    rows->addWidget(m_stopBtn);
    rows->addWidget(m_nextF);

	//TODO: remove this in the final version
	connect(m_openBtn, SIGNAL(clicked()), SLOT(openMedia()));

	connect(m_prevF, SIGNAL(clicked()), SLOT(previousFrame()));
	connect(m_playBtn, SIGNAL(clicked()), SLOT(playPause()));
    connect(m_stopBtn, SIGNAL(clicked()), SLOT(stopVideo()));
	connect(m_nextF, SIGNAL(clicked()), SLOT(nextFrame()));

	/** Widget minimum sizes */
    setFixedSize(480,320);
}

//@Override
void PlayerWidget::paintEvent(QPaintEvent*) {
    return;
    QPainter painter(this);

    int width = size().width() - 3;
    int height = size().height() - 5;

    painter.fillRect(0, 0, width, height, QColor(0,0,0));
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
}

//TODO: Check formula
/*! \brief displays previous frame.
*
*	Displays the previous frame from the current player position.
*	The frame number is calculated and may not be correct.
*	@see toPreviousFrame()
*/
void PlayerWidget::previousFrame(){
	m_player->setPosition(m_player->position() - m_player->statistics().video.frame_rate);
}

//TODO: Check formula
/*! \brief displays next frame.
*
*	Displays the next frame from the current player position.
*	The frame number is calculated and may not be correct.
*	@see toNextFrame()
*/
void PlayerWidget::nextFrame(){
	m_player->setPosition(m_player->position() + m_player->statistics().video.frame_rate);
}

/*! \brief Get current frame number.
*
*	This functions is used to get the current frame number.
*	@param frameNumber
*	@return current frame number.
*	@see previousFrameNumber()
*	@see nextFrameNumber()
*/
qint64 PlayerWidget::currentFrameNumber(qint64 ofFrame){
	return ((ofFrame*m_player->statistics().video.frame_rate) / 1000LL);
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

//TODO: Check formula
/*! \brief Get the previous frame number.
*
*	This functions is used to get the previous frame number.
*	@return previous frame number.
*/
qint64 PlayerWidget::previousFrameNumber(){
	qint64 prevFrame = m_player->position() - m_player->statistics().video.frame_rate;
	return currentFrameNumber(prevFrame);
}

//TODO: Check formula
/*! \brief Get the previous frame number.
*
*	This functions is used to get the previous frame number.
*	@param current frame number
*	@return previous frame number.
*/
qint64 PlayerWidget::previousFrameNumber(qint64 ofFrame){
	qint64 prevFrame = ofFrame - m_player->statistics().video.frame_rate;
	return currentFrameNumber(prevFrame);
}

//TODO: Check formula
/*! \brief Get the next frame number.
*
*	This functions is used to get the next frame number.
*	@return next frame number.
*/
qint64 PlayerWidget::nextFrameNumber(){
	qint64 prevFrame = m_player->position() + m_player->statistics().video.frame_rate;
	return currentFrameNumber(prevFrame);
}

//TODO: Check formula
/*! \brief Get the next frame number.
*
*	This functions is used to get the next frame number.
*	@param current frame number
*	@return next frame number.
*/
qint64 PlayerWidget::nextFrameNumber(qint64 ofFrame){
    qint64 prevFrame = ofFrame + m_player->statistics().video.frame_rate;
	return currentFrameNumber(prevFrame);
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
    playState = true;
	m_player->play(file);
}
