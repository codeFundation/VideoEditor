#include "headers/timeline.h"
#include <QBrush>
#include <QPen>

Timeline::Timeline(QWidget *parent)
    : QGraphicsView(parent)
    , m_scene(new QGraphicsScene(this))
    , m_tracks()
    , m_trackHeight(50)
    , m_trackSpacing(10)
{
    setScene(m_scene);
    setMinimumHeight(200);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_scene->setSceneRect(0, 0, 1000, 200);
}

Timeline::~Timeline()
{
    for (const Track &track : m_tracks) {
        qDeleteAll(track.clips);
        delete track.background;
    }
}

void Timeline::addTrack()
{
    Track newTrack;
    newTrack.clips = QList<VideoClip*>();
    newTrack.background = nullptr;
    m_tracks.append(newTrack);
    createTrackBackground(m_tracks.size() - 1);
    updateTimeline();
}

void Timeline::removeTrack(int trackIndex)
{
    if (trackIndex >= 0 && trackIndex < m_tracks.size()) {
        Track &track = m_tracks[trackIndex];
        qDeleteAll(track.clips);
        delete track.background;
        m_tracks.removeAt(trackIndex);
        updateTimeline();
    }
}

void Timeline::addClipToTrack(int trackIndex, const QString &filePath, qint64 startTime, qint64 duration)
{
    if (trackIndex >= 0 && trackIndex < m_tracks.size()) {
        VideoClip *clip = new VideoClip(filePath, startTime, duration, this);
        m_tracks[trackIndex].clips.append(clip);
        m_scene->addItem(clip->getTimelineItem());
        updateTimeline();
    }
}

void Timeline::createTrackBackground(int trackIndex)
{
    if (trackIndex >= 0 && trackIndex < m_tracks.size()) {
        QGraphicsRectItem *background = new QGraphicsRectItem(0, 0, 1000, m_trackHeight);
        background->setBrush(QBrush(Qt::lightGray));
        background->setPos(0, trackIndex * (m_trackHeight + m_trackSpacing));
        m_scene->addItem(background);
        m_tracks[trackIndex].background = background;
    }
}

void Timeline::updateTimeline()
{
    // Actualizar el tamaño de la escena
    qreal totalHeight = m_tracks.size() * (m_trackHeight + m_trackSpacing);
    m_scene->setSceneRect(0, 0, 1000, qMax(totalHeight, 200.0));
    
    // Actualizar la posición de los clips y fondos
    for (int i = 0; i < m_tracks.size(); ++i) {
        Track &track = m_tracks[i];
        if (track.background) {
            track.background->setPos(0, i * (m_trackHeight + m_trackSpacing));
        }
        for (VideoClip *clip : track.clips) {
            if (clip && clip->getTimelineItem()) {
                QGraphicsItem *item = clip->getTimelineItem();
                qreal y = i * (m_trackHeight + m_trackSpacing);
                item->setY(y);
            }
        }
    }
} 