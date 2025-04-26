#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // Crear el editor de video
    m_videoEditor = new VideoEditor(this);
    
    // Configurar la ventana principal
    setWindowTitle("Editor de Video");
    resize(1024, 768);
    
    // Crear la barra de menú
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);
    
    // Menú Archivo
    QMenu *fileMenu = menuBar->addMenu("Archivo");
    QAction *openAction = fileMenu->addAction("Abrir");
    fileMenu->addAction("Guardar");
    fileMenu->addSeparator();
    QAction *exitAction = fileMenu->addAction("Salir");
    
    // Menú Edición
    QMenu *editMenu = menuBar->addMenu("Edición");
    editMenu->addAction("Cortar");
    editMenu->addAction("Copiar");
    editMenu->addAction("Pegar");
    
    // Menú Ver
    QMenu *viewMenu = menuBar->addMenu("Ver");
    QAction *fullscreenAction = viewMenu->addAction("Pantalla Completa");
    
    // Conectar acciones
    connect(openAction, &QAction::triggered, m_videoEditor, &VideoEditor::onOpenFile);
    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);
    connect(fullscreenAction, &QAction::triggered, this, &QMainWindow::showFullScreen);
    
    // Agregar la barra de herramientas
    addToolBar(m_videoEditor->getToolBar());
    
    // Crear el widget central
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    // Configurar el layout
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(m_videoEditor->getVideoWidget());
    layout->setContentsMargins(0, 0, 0, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
