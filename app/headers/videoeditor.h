#ifndef VIDEOEDITOR_H
#define VIDEOEDITOR_H

#include <QObject>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QSlider>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolBar>
#include <QAction>
#include <QTime>
#include <QLabel>
#include "timeline.h"

class VideoEditor : public QObject
{
    Q_OBJECT

public:
    explicit VideoEditor(QWidget *parent = nullptr);
    ~VideoEditor();

    QWidget* getVideoWidget();
    QToolBar* getToolBar();
    void loadVideo(const QString &filePath);
    void play();
    void pause();
    void stop();
    void setPosition(qint64 position);
    void openFile();
    void onOpenFile();
    void addTrack();

private slots:
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void handleError(QMediaPlayer::Error error);
    void updateTimeLabel();

private:
    QMediaPlayer *m_player;
    QVideoWidget *m_videoWidget;
    QSlider *m_positionSlider;
    QPushButton *m_playButton;
    QPushButton *m_stopButton;
    QPushButton *m_openButton;
    QPushButton *m_addTrackButton;
    QLabel *m_timeLabel;
    QToolBar *m_toolBar;
    Timeline *m_timeline;
    QTimer *m_timer;
    QString m_currentFile;
};

#endif // VIDEOEDITOR_H 