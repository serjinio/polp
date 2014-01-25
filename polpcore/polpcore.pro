#-------------------------------------------------
#
# Project created by QtCreator 2014-01-25T21:10:50
#
#-------------------------------------------------

TARGET = polpcore
TEMPLATE = lib

DEFINES += POLPCORE_LIBRARY

unix {
    target.path = /usr/lib
    INSTALLS += target
}
