#include "simpledevice.h"

SimpleDevice::SimpleDevice(QObject *parent) :
    QObject(parent)
{
    pane = new QWidget;
}

QStringList SimpleDevice::devices()
{
    return QStringList()<<"dev1"<< "dev2";
}

QWidget *SimpleDevice::controlPane()
{
    return pane;
}

int SimpleDevice::loadData(Data *data)
{
    return 0;
}

QString SimpleDevice::error()
{
    return "NO ERRORS";
}

QString SimpleDevice::preferedView()
{
    return "nopref";
}

QString SimpleDevice::deviceClass()
{
    return "Simple device";
}
