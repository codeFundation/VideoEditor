#include "headers/videoclip.h"
#include <QGraphicsScene>
#include <QPen>
#include <QBrush>
#include <QFileInfo>

VideoClip::VideoClip(const QString &filePath, qint64 startTime, qint64 duration, QObject *parent)
    : QObject(parent)
    , m_filePath(filePath)
    , m_startTime(startTime)
    , m_duration(duration)
    , m_timelineItem(nullptr)
    , m_labelItem(nullptr)
    , m_player(new QMediaPlayer(this))
{
    m_player->setMedia(QUrl::fromLocalFile(filePath));
    
    // Crear el elemento visual para la línea de tiempo
    m_timelineItem = new QGraphicsRectItem();
    m_timelineItem->setRect(0, 0, duration / 1000.0 * 100, 30);
    m_timelineItem->setPen(QPen(Qt::black));
    m_timelineItem->setBrush(QBrush(Qt::blue));
    m_timelineItem->setPos(startTime / 1000.0 * 100, 0);
    m_timelineItem->setFlag(QGraphicsItem::ItemIsMovable, true);
    m_timelineItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    
    // Crear la etiqueta con el nombre del archivo
    QFileInfo fileInfo(filePath);
    m_labelItem = new QGraphicsTextItem(fileInfo.fileName());
    m_labelItem->setPos(startTime / 1000.0 * 100, 35);
    m_labelItem->setParentItem(m_timelineItem);
}

VideoClip::~VideoClip()
{
    if (m_timelineItem) {
        delete m_timelineItem;
    }
    if (m_labelItem) {
        delete m_labelItem;
    }
}

QString VideoClip::getFilePath() const
{
    return m_filePath;
}

qint64 VideoClip::getStartTime() const
{
    return m_startTime;
}

qint64 VideoClip::getDuration() const
{
    return m_duration;
}

QGraphicsItem* VideoClip::getTimelineItem() const
{
    return m_timelineItem;
}

void VideoClip::setStartTime(qint64 time)
{
    m_startTime = time;
    updateTimelineItem();
}

void VideoClip::setDuration(qint64 duration)
{
    m_duration = duration;
    updateTimelineItem();
}

void VideoClip::updateTimelineItem()
{
    if (m_timelineItem) {
        m_timelineItem->setRect(0, 0, m_duration / 1000.0 * 100, 30);
        m_timelineItem->setPos(m_startTime / 1000.0 * 100, 0);
    }
    
    if (m_labelItem) {
        m_labelItem->setPos(m_startTime / 1000.0 * 100, 35);
    }
} 