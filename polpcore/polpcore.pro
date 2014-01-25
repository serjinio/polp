#-------------------------------------------------
#
# Project created by QtCreator 2014-01-25T21:10:50
#
#-------------------------------------------------

QT       -= gui

TARGET = polpcore
TEMPLATE = lib

DEFINES += POLPCORE_LIBRARY

SOURCES += polpcore.cpp

HEADERS += polpcore.h\
        polpcore_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
