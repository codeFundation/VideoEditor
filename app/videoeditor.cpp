#include "headers/videoeditor.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTimer>
#include <QTime>
#include <QFileInfo>

VideoEditor::VideoEditor(QWidget *parent) : QObject(parent)
{
    m_player = new QMediaPlayer(this);
    m_videoWidget = new QVideoWidget();
    m_positionSlider = new QSlider(Qt::Horizontal);
    m_playButton = new QPushButton("Reproducir");
    m_stopButton = new QPushButton("Detener");
    m_openButton = new QPushButton("Abrir Video");
    m_addTrackButton = new QPushButton("Agregar Pista");
    m_timeLabel = new QLabel("00:00:00 / 00:00:00");
    m_toolBar = new QToolBar();
    m_timeline = new Timeline();
    m_timer = new QTimer(this);
    m_currentFile = "";

    // Configurar el reproductor
    m_player->setVideoOutput(m_videoWidget);
    m_positionSlider->setRange(0, 0);

    // Configurar la barra de herramientas
    QAction *openAction = m_toolBar->addAction("Abrir");
    QAction *playAction = m_toolBar->addAction("Reproducir");
    QAction *pauseAction = m_toolBar->addAction("Pausar");
    QAction *stopAction = m_toolBar->addAction("Detener");
    m_toolBar->addSeparator();
    QAction *addTrackAction = m_toolBar->addAction("Agregar Pista");

    // Conectar señales
    connect(m_player, &QMediaPlayer::positionChanged, this, &VideoEditor::positionChanged);
    connect(m_player, &QMediaPlayer::durationChanged, this, &VideoEditor::durationChanged);
    connect(m_player, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), this, &VideoEditor::handleError);
    connect(m_positionSlider, &QSlider::sliderMoved, this, &VideoEditor::setPosition);
    connect(m_playButton, &QPushButton::clicked, this, &VideoEditor::play);
    connect(m_stopButton, &QPushButton::clicked, this, &VideoEditor::stop);
    connect(m_openButton, &QPushButton::clicked, this, &VideoEditor::onOpenFile);
    connect(m_addTrackButton, &QPushButton::clicked, this, &VideoEditor::addTrack);
    connect(openAction, &QAction::triggered, this, &VideoEditor::onOpenFile);
    connect(playAction, &QAction::triggered, this, &VideoEditor::play);
    connect(pauseAction, &QAction::triggered, this, &VideoEditor::pause);
    connect(stopAction, &QAction::triggered, this, &VideoEditor::stop);
    connect(addTrackAction, &QAction::triggered, this, &VideoEditor::addTrack);
    connect(m_timer, &QTimer::timeout, this, &VideoEditor::updateTimeLabel);

    m_timer->start(100); // Actualizar cada 100ms
    
    // Crear pista inicial
    addTrack();
}

VideoEditor::~VideoEditor()
{
    delete m_videoWidget;
    delete m_timeline;
    delete m_toolBar;
}

QWidget* VideoEditor::getVideoWidget()
{
    QWidget *container = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(container);
    
    // Agregar el widget de video
    layout->addWidget(m_videoWidget);
    
    // Agregar controles de reproducción
    QHBoxLayout *controlsLayout = new QHBoxLayout();
    controlsLayout->addWidget(m_openButton);
    controlsLayout->addWidget(m_playButton);
    controlsLayout->addWidget(m_stopButton);
    controlsLayout->addWidget(m_positionSlider);
    controlsLayout->addWidget(m_timeLabel);
    
    layout->addLayout(controlsLayout);
    
    // Agregar botón para nueva pista
    QHBoxLayout *trackControlsLayout = new QHBoxLayout();
    trackControlsLayout->addWidget(m_addTrackButton);
    layout->addLayout(trackControlsLayout);
    
    // Agregar la línea de tiempo
    layout->addWidget(m_timeline);
    
    return container;
}

QToolBar* VideoEditor::getToolBar()
{
    return m_toolBar;
}

void VideoEditor::loadVideo(const QString &filePath)
{
    m_currentFile = filePath;
    m_player->setMedia(QUrl::fromLocalFile(filePath));
    m_timeline->addClipToTrack(0, filePath, 0, 10000); // 10 segundos por defecto
}

void VideoEditor::addTrack()
{
    m_timeline->addTrack();
}

void VideoEditor::play()
{
    m_player->play();
    m_playButton->setText("Pausar");
    disconnect(m_playButton, &QPushButton::clicked, this, &VideoEditor::play);
    connect(m_playButton, &QPushButton::clicked, this, &VideoEditor::pause);
}

void VideoEditor::pause()
{
    m_player->pause();
    m_playButton->setText("Reproducir");
    disconnect(m_playButton, &QPushButton::clicked, this, &VideoEditor::pause);
    connect(m_playButton, &QPushButton::clicked, this, &VideoEditor::play);
}

void VideoEditor::stop()
{
    m_player->stop();
    m_playButton->setText("Reproducir");
    disconnect(m_playButton, &QPushButton::clicked, this, &VideoEditor::pause);
    connect(m_playButton, &QPushButton::clicked, this, &VideoEditor::play);
}

void VideoEditor::setPosition(qint64 position)
{
    m_player->setPosition(position);
}

void VideoEditor::positionChanged(qint64 position)
{
    m_positionSlider->setValue(position);
    updateTimeLabel();
}

void VideoEditor::durationChanged(qint64 duration)
{
    m_positionSlider->setRange(0, duration);
    updateTimeLabel();
}

void VideoEditor::handleError(QMediaPlayer::Error error)
{
    Q_UNUSED(error);
    QMessageBox::critical(nullptr, "Error", "Error al reproducir el video: " + m_player->errorString());
}

void VideoEditor::updateTimeLabel()
{
    QTime currentTime(0, 0);
    currentTime = currentTime.addMSecs(m_player->position());
    QTime totalTime(0, 0);
    totalTime = totalTime.addMSecs(m_player->duration());
    
    m_timeLabel->setText(currentTime.toString("hh:mm:ss") + " / " + totalTime.toString("hh:mm:ss"));
}

void VideoEditor::onOpenFile()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Abrir Video", 
                                                  QDir::homePath(), 
                                                  "Archivos de Video (*.mp4 *.avi *.mkv *.mov)");
    if (!filePath.isEmpty()) {
        loadVideo(filePath);
    }
}