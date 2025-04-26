#include "./headers/mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Cargar hoja de estilo desde recurso
    QFile styleFile(":/styles/dark_blender.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QString style = styleFile.readAll();
        app.setStyleSheet(style);
    }

    MainWindow w;
    w.show();
    return app.exec();
}
