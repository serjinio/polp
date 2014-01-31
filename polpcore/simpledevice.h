#ifndef SIMPLEDEVICE_H
#define SIMPLEDEVICE_H

#include "plugins.h"

#include <QObject>

class SimpleDevice : public QObject, public Device
{
    Q_OBJECT
    Q_INTERFACES(Device)
public:
    explicit SimpleDevice(QObject *parent = 0);
    QStringList devices();
    virtual QWidget *controlPane();

    // Returns non zero value if errors occur(For example: Faild to read device)
    virtual int loadData(Data* data);

    //Returns error message
    virtual QString error();

    virtual QString preferedView();
     virtual QString deviceClass();
signals:

public slots:

private:
    QWidget * pane;

};

#endif // SIMPLEDEVICE_H
