#-------------------------------------------------
#
# Project created by QtCreator 2015-10-12T10:58:09
#
#-------------------------------------------------

QT       += core gui

CONFIG += C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RedTriangle
TEMPLATE = app

INCLUDEPATH += ../External/glew-1.13.0/include \
               ../External/glm-0.9.7/

SOURCES +=\
    Main.cpp \
    MVPWindow.cpp

HEADERS  += \
    MVPWindow.hpp

LIBS += ../External/glew-1.13.0/lib/libGLEW.a

RESOURCES += \
    glsl.qrc
