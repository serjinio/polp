#-------------------------------------------------
#
# Project created by QtCreator 2014-01-30T01:34:52
#
#-------------------------------------------------

QT       += core gui widgets testlib

TARGET = SMDFileFormatTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    smdfileformattest.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../SMDFileFormat/release/ -lSMDFileFormat
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../SMDFileFormat/debug/ -lSMDFileFormat
else:unix: LIBS += -L$$OUT_PWD/../SMDFileFormat/ -lSMDFileFormat

INCLUDEPATH += $$PWD/../SMDFileFormat
DEPENDPATH += $$PWD/../SMDFileFormat

HEADERS += \
    smdfileformattest.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../polpcore/release/ -lpolpcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../polpcore/debug/ -lpolpcore
else:unix: LIBS += -L$$OUT_PWD/../../polpcore/ -lpolpcore

INCLUDEPATH += $$PWD/../../polpcore
DEPENDPATH += $$PWD/../../polpcore
