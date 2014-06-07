#-------------------------------------------------
#
# Project created by QtCreator 2014-06-07T12:01:43
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Multimedia
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    mainwidget.cpp \
    sceneobject.cpp

RESOURCES = textures.qrc

HEADERS  += window.h \
    mainwidget.h \
    sceneobject.h

FORMS    += window.ui
