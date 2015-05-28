#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QtAV>

class QSlider;
class QPushButton;
class QLabel;
class StatisticsView;
/**
*	PlayerWidget class.
*/
class PlayerWidget : public QWidget
{
    Q_OBJECT

private:
    //	Player objects
    QtAV::VideoRenderer *m_vo;
    QtAV::AVPlayer *m_player;

    //	Slider
    QSlider *m_slider;

    //	Buttons objects
    QPushButton *m_openBtn;		//TODO: remove this in the final version
    QPushButton *m_playBtn;
    QPushButton *m_stopBtn;
    QPushButton *m_prevF;
    QPushButton *m_nextF;
    QPushButton *m_info;

    //	Button's icons objects
    QPixmap play;
    QPixmap pause;
    QPixmap stop;
    QPixmap prevF;
    QPixmap nextF;
    QPixmap info;

    //	Help var
    bool playState;

    // Default stuff
    void initializeIcons();
    void changePlayPause();

    // Signal emitter controller
    void emitterCheck();

    StatisticsView *statistic_viewer;

    qint64 currentFrameNumber(qint64);

public:
	explicit PlayerWidget(QWidget *parent = 0);
	
	QtAV::AVPlayer* getAVPlayer();

	// Set the media to play.
	void openFile(QString);

	// Generic Functions to access all the infos.
	qint64 currentFrameNumber();

	qint64 previousFrameNumber();
	qint64 previousFrameNumber(qint64);
	
	qint64 nextFrameNumber();
	qint64 nextFrameNumber(qint64);
	
	qint64 toNextFrame();
	qint64 toPreviousFrame();

    qint64 positionFromFrameNumber(qint64);

private Q_SLOTS:
	void openMedia();
	void seek(int);
	void playPause();
    void stopVideo();

	void updateSlider();
	void previousFrame();
	void nextFrame();
	
    void showInfo();

signals:
    void playbackStop();
    void frameChanged();
    void playbackPlay();
};

#endif // PLAYERWIDGET_H
