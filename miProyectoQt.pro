QT += core gui widgets multimedia multimediawidgets


TARGET = miProyectoQt
TEMPLATE = app

SOURCES += app/main.cpp \
           app/mainwindow.cpp \
           app/videoeditor.cpp \
           app/videoclip.cpp \
           app/timeline.cpp

HEADERS += app/headers/mainwindow.h \
           app/headers/videoeditor.h \
           app/headers/videoclip.h \
           app/headers/timeline.h

FORMS += ui/mainwindow.ui

# Configuración adicional
CONFIG += c++17
