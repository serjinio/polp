#-------------------------------------------------
#
# Project created by QtCreator 2014-01-25T21:10:50
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = polpcore
TEMPLATE = lib

DEFINES += POLPCORE_LIBRARY

unix {
    target.path = /usr/lib
    INSTALLS += target
}

HEADERS += \
    data.h \
    plugins.h \
    simpleanalyser.h \
    simpleview.h

SOURCES += \
    data.cpp \
    simpleanalyser.cpp \
    simpleview.cpp
