#ifndef VIDEOCLIP_H
#define VIDEOCLIP_H

#include <QObject>
#include <QMediaPlayer>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

class VideoClip : public QObject
{
    Q_OBJECT

public:
    explicit VideoClip(const QString &filePath, qint64 startTime, qint64 duration, QObject *parent = nullptr);
    ~VideoClip();

    QString getFilePath() const;
    qint64 getStartTime() const;
    qint64 getDuration() const;
    QGraphicsItem* getTimelineItem() const;
    void setStartTime(qint64 time);
    void setDuration(qint64 duration);
    void updateTimelineItem();

private:
    QString m_filePath;
    qint64 m_startTime;
    qint64 m_duration;
    QGraphicsRectItem *m_timelineItem;
    QGraphicsTextItem *m_labelItem;
    QMediaPlayer *m_player;
};

#endif // VIDEOCLIP_H 