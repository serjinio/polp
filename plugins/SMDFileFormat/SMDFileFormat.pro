#-------------------------------------------------
#
# Project created by QtCreator 2014-01-29T21:46:42
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SMDFileFormat
TEMPLATE = lib

DEFINES += SMDFILEFORMAT_LIBRARY

SOURCES += smdfileformat.cpp

HEADERS += smdfileformat.h\
        smdfileformat_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../polpcore/release/ -lpolpcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../polpcore/debug/ -lpolpcore
else:unix: LIBS += -L$$OUT_PWD/../../polpcore/ -lpolpcore

INCLUDEPATH += $$PWD/../../polpcore
DEPENDPATH += $$PWD/../../polpcore

win32 {
    DESTDIR  = OUT_PWD/../../SMDFileFormatTest/debug
}
