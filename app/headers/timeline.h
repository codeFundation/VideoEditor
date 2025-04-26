#ifndef TIMELINE_H
#define TIMELINE_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>
#include "videoclip.h"

class Timeline : public QGraphicsView
{
    Q_OBJECT

public:
    explicit Timeline(QWidget *parent = nullptr);
    ~Timeline();

    void addTrack();
    void removeTrack(int trackIndex);
    void addClipToTrack(int trackIndex, const QString &filePath, qint64 startTime, qint64 duration);
    void updateTimeline();

private:
    QGraphicsScene *m_scene;
    struct Track {
        QList<VideoClip*> clips;
        QGraphicsRectItem *background;
    };
    QList<Track> m_tracks;
    int m_trackHeight;
    int m_trackSpacing;

    void createTrackBackground(int trackIndex);
};

#endif // TIMELINE_H 